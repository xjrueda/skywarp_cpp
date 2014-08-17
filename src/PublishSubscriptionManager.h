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

#ifndef PUBLISHSUBSCRIPTIONMANAGER_H
#define	PUBLISHSUBSCRIPTIONMANAGER_H
#include <map>
#include <string>
#include "Topic.h"
#include "SessionManager.h"

using namespace std;
class PublishSubscriptionManager {
public:
    PublishSubscriptionManager();
    virtual ~PublishSubscriptionManager();
    void registerTopic(string);
    void updateTopic(string,string);    
    void updateTopic(string,Server::message_ptr); 
    void subscribe(SessionManager::Session,string);
    void unSubscribe(SessionManager::Session,string);
    void unSubscribeAll(SessionManager::Session);
    void onSubscribe(Json::Value, int, string);
    void onUnsubscribe(Json::Value, int, string);
    void setSessionManager(shared_ptr<SessionManager>);
private:
    map<string,Topic> AvailableTopics;
    shared_ptr<SessionManager> sessionManager;
};

#endif	/* PUBLISHSUBSCRIPTIONMANAGER_H */

