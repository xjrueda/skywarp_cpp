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

#if !defined(EA_759A8338_AA08_495b_9E78_7A4268A4B573__INCLUDED_)
#define EA_759A8338_AA08_495b_9E78_7A4268A4B573__INCLUDED_



#include "globalDatatypes.h"
#include <websocketpp/server.hpp>
#include <future>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>
#include "SessionManager.h"
#include "ClientSession.h"
#include "MethodDelegatorManager.h"
#include "PublishSubscriptionManager.h"
#include "JsonRPCParser.h"


using websocketpp::connection_hdl;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;
using websocketpp::lib::thread;
using websocketpp::lib::mutex;
using websocketpp::lib::unique_lock;
using websocketpp::lib::condition_variable;

using namespace std;

class SkywarpServer {
public:
    SkywarpServer();
    virtual ~SkywarpServer();
    void onClose(websocketpp::connection_hdl);
    void onMessage(websocketpp::connection_hdl, Server::message_ptr msg);
    void onOpen(websocketpp::connection_hdl);
    void setMethodHandler(string, MethodDelegatorManager::ApplicationDelegateType, bool);
    void registerTopic(string name);
    void publish(string, Json::Value);
    void run(uint16_t port);
    void notifyTermination();
private:
    enum ActionType {
        SUBSCRIBE,
        UNSUBSCRIBE,
        MESSAGE
    };
    struct Action {
        Action(ActionType t, websocketpp::connection_hdl h) : type(t), hdl(h) {
        }
        Action(ActionType t, Server::message_ptr m, websocketpp::connection_hdl h) : type(t), msg(m), hdl(h) {
        }
        ActionType type;
        websocketpp::connection_hdl hdl;
        Server::message_ptr msg;
    };
    struct Publication {
        Publication(string name, Json::Value value): appMessage(value), topicName(name) {}
        Json::Value appMessage;
        string topicName;
    };
    typedef std::set<connection_hdl, std::owner_less<connection_hdl>> ConnectionListType;
    Server server;
    condition_variable actionCondition;
    condition_variable publishCondition;
    mutex actionLock;
    mutex publishingQueueLock;
    mutex connectionLock;
    std::queue<Action> actions;
    ConnectionListType connectionList;
    std::queue<Publication> publishingQueue;
    void inboundProcessor(std::promise<std::string>&);
    void publishingProcessor(std::promise<std::string>&);
    shared_ptr<SessionManager> sessionManager;
    PublishSubscriptionManager pubSubManager;
    MethodDelegatorManager delegatorManager;
    std::ofstream logfile;
};
#endif // !defined(EA_759A8338_AA08_495b_9E78_7A4268A4B573__INCLUDED_)
