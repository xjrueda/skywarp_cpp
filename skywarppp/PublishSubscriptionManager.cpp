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

#include "PublishSubscriptionManager.h"
#include "SessionManager.h"

PublishSubscriptionManager::PublishSubscriptionManager() {
}

PublishSubscriptionManager::~PublishSubscriptionManager() {
}

void PublishSubscriptionManager::registerTopic(string name) {
    Topic topic;
    AvailableTopics[name] = topic;
}

void PublishSubscriptionManager::updateTopic(string name, string value)  {
    AvailableTopics[name].notify(value);
}

void PublishSubscriptionManager::updateTopic(string name, Server::message_ptr msg)  {
    AvailableTopics[name].notify(msg);
}

void PublishSubscriptionManager::subscribe(SessionManager::Session session, string name) {
    AvailableTopics[name].attach(session);
}

void PublishSubscriptionManager::unSubscribe(SessionManager::Session session, string name) {
    AvailableTopics[name].detach(session);
}

void PublishSubscriptionManager::unSubscribeAll(SessionManager::Session session) {
    map<string,Topic>::iterator it;
    for (it=AvailableTopics.begin();it != AvailableTopics.end(); it++) {
        it->second.detach(session);
    }
}

void PublishSubscriptionManager::onSubscribe(Json::Value params, int sessionId, string requestId) {
    string topicName = params["topic"].asString();
    SessionManager::Session session = sessionManager->getSessionFromId(sessionId);
    AvailableTopics[topicName].attach(session);
}

void PublishSubscriptionManager::onUnsubscribe(Json::Value params, int sessionId, string requestId) {
    string topicName = params["topic"].asString();
    SessionManager::Session session = sessionManager->getSessionFromId(sessionId);
    AvailableTopics[topicName].detach(session);
}
void PublishSubscriptionManager::setSessionManager(shared_ptr<SessionManager> sm) {
    sessionManager = sm;
}