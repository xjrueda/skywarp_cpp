/*
 * Copyright (c) 2014, Juan Carlos Rueda (juancarlosrueda@icloud.com) All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the skywarp++ or skywarp_cpp  Project nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL JUAN CARLOS RUEDA BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <exception>
#include <json/json.h>
#include <queue>
#include <mutex>

#include "SkywarpServer.h"
#include "JsonSerializer.h"

using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
using websocketpp::lib::thread;
using websocketpp::lib::mutex;
using websocketpp::lib::unique_lock;
using websocketpp::lib::condition_variable;

SkywarpServer::SkywarpServer() {
    // Initialize Asio Transport
    server.init_asio();
    // Register handler callbacks
    server.set_open_handler(bind(&SkywarpServer::onOpen, this, ::_1));
    server.set_close_handler(bind(&SkywarpServer::onClose, this, ::_1));
    server.set_message_handler(bind(&SkywarpServer::onMessage, this, ::_1, ::_2));

    sessionManager.reset(new SessionManager());
    sessionManager->setServer(server);
    pubSubManager.setSessionManager(sessionManager);

    umask(0);
    logfile.open("./skywarppp.log");
    server.get_alog().set_ostream(&logfile);


    //register topic subscription / unsubscription call backs
    this->setMethodHandler(
            "subscribe",
            std::bind(
            &PublishSubscriptionManager::onSubscribe,
            &pubSubManager,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3
            ),
            false
            );
    
    this->setMethodHandler(
            "unsubscribe",
            std::bind(
            &PublishSubscriptionManager::onUnsubscribe,
            &pubSubManager,
            std::placeholders::_1,
            std::placeholders::_2,
            std::placeholders::_3
            ),
            false
            );

}

SkywarpServer::~SkywarpServer() {

}

void SkywarpServer::onOpen(websocketpp::connection_hdl hdl) {
    sessionManager->createSession(hdl);
}

void SkywarpServer::onClose(websocketpp::connection_hdl hdl) {
    pubSubManager.unSubscribeAll(sessionManager->getsessionFromHandler(hdl));
    sessionManager->removeSession(hdl);
    
}

void SkywarpServer::onMessage(websocketpp::connection_hdl hdl, Server::message_ptr msg) {
    unique_lock<mutex> lock(actionLock);
    actions.push(Action(MESSAGE, msg, hdl));
    lock.unlock();
    actionCondition.notify_one();
}

void SkywarpServer::publishingProcessor(std::promise<std::string>& p) {
    try {
        while (1) {
            unique_lock<mutex> lock(publishingQueueLock);

            while (publishingQueue.empty()) {
                publishCondition.wait(lock);
            }
            Publication p = publishingQueue.front();
            publishingQueue.pop();
            lock.unlock();
            JsonSerializer serializer;
            string serializedJsonRPCResult = serializer.serializeRPCResult(p.topicName, p.appMessage);
            pubSubManager.updateTopic(p.topicName, serializedJsonRPCResult);
        }
    } catch (...) {
        p.set_exception(std::current_exception());
    }
}

void SkywarpServer::setMethodHandler(string jsonrcpMethod, MethodDelegatorManager::ApplicationDelegateType methodHandler, bool asynchronous) {
    delegatorManager.subscribeDelegate(jsonrcpMethod, methodHandler, asynchronous);
}

void SkywarpServer::notifyTermination() {
    ConnectionListType::iterator it;
    websocketpp::close::status::value cod = 1;
    for (it = connectionList.begin(); it != connectionList.end(); ++it) {
        try {
            string msg = "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32000, \"message\": \"Server error\"},\"id\":null}";
            server.send(*it, msg, websocketpp::frame::opcode::text);
        } catch (...) {
        }
    }
}

void SkywarpServer::inboundProcessor(std::promise<std::string>& p) {
    try {
        while (1) {
            unique_lock<mutex> lock(actionLock);

            while (actions.empty()) {
                actionCondition.wait(lock);
            }
            Action a = actions.front();
            actions.pop();
            lock.unlock();
            JsonRPCParser msgParser;
            SessionManager::Session session = sessionManager->getsessionFromHandler(a.hdl);
            try {
                msgParser.parseMessage(a.msg->get_payload());
                string requestId = msgParser.getId();
                string version = msgParser.getVersion();
                string method = msgParser.getMethod();
                Json::Value params = msgParser.getParams();
                // delegates the method to it handler
                delegatorManager.callDelegate(method, params, session->getId(), requestId);
            } catch (JsonRPCMethodException& e0) {
                session->sendMessage(e0.what());
            } catch (JsonRPCParseError& e1) {
                session->sendMessage(e1.what());
            } catch (JsonRPCMethodNotFound& e2) {
                session->sendMessage(e2.what());
            } catch (JsonRPCInvalidRequest& e3) {
                session->sendMessage(e3.what());
            }
        }
    } catch (...) {
        notifyTermination();
        usleep(10000);
        server.stop_listening();
        server.stop_perpetual();
        server.stop();
        p.set_exception(std::current_exception());
    }
}

void SkywarpServer::registerTopic(string name) {
    pubSubManager.registerTopic(name);
}

void SkywarpServer::publish(string name, Json::Value value) {
    unique_lock<mutex> lock(publishingQueueLock);
    publishingQueue.push(Publication(name, value));
    lock.unlock();
    publishCondition.notify_one();
}

void SkywarpServer::run(uint16_t port) {
    try {
        std::promise<std::string> p1, p2;

        
        
        // lauch the processor for publications from host application 
        thread t1(bind(&SkywarpServer::publishingProcessor, this, std::ref(p1)));
        std::shared_future<std::string> f1(p1.get_future().share());
    
        // lauch the processor for inbound messages 
        thread t2(bind(&SkywarpServer::inboundProcessor, this, std::ref(p2)));
        std::shared_future<std::string> f2(p2.get_future().share());
    
        // listen on specified port
        server.listen(port);
        
        // Start the server accept loop
        server.start_accept();
        
        // Start the ASIO io_service run loop
        server.run();
        
        t1.join();
        t2.join();
        
    } catch (const std::exception & e) {
        std::cerr << "General Exception: " << e.what() << std::endl;
    } catch (websocketpp::lib::error_code e) {
        std::cerr << "Websocket Exception: " << e.message() << std::endl;
    } catch (...) {
        std::cerr << "Other exception" << std::endl;
    }
}