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

#include <algorithm>

#include "SessionManager.h"

SessionManager::SessionManager() {
}

SessionManager::~SessionManager() {
}

void SessionManager::createSession(websocketpp::connection_hdl conHdl) {
    int id;
    unique_lock<mutex> lock(sessionLock);
    {
        id = getNextSessiionId();
        std::shared_ptr<ClientSession> session(new ClientSession());
        session->setConnectionHandler(conHdl);
        session->setId(id);
        session->setServer(*server);
        sessionsByHandler[conHdl] = session;
        sessionsById[id] = session;
    }
};

void SessionManager::removeSession(websocketpp::connection_hdl conHdl) {
    int id;
    unique_lock<mutex> lock(sessionLock);
    {
        int id = sessionsByHandler[conHdl]->getId();
        sessionsByHandler.erase(conHdl);
        sessionsById.erase(id);
    }
};

void SessionManager::setServer(Server& srv) {
    server = &srv;
}

SessionManager::Session SessionManager::getSessionFromId(int id) {
    try {
        return sessionsById[id];
    } catch (...) {
        throw InvalidSessionId(id);
    }

};

SessionManager::Session SessionManager::getsessionFromHandler(websocketpp::connection_hdl conHdl) {
    try {
        return sessionsByHandler[conHdl];
    } catch (...) {
        throw InvalidConnectionHandler();
    }
};

void SessionManager::broadcastMessage(string messageText) {
    try {
        SessionListByIdListType::iterator it;
        for (it = sessionsById.begin(); it != sessionsById.end(); it++) {
            it->second->sendMessage(messageText);
        }
    } catch (...) {
    }
}

void SessionManager::broadcastMessage(Server::message_ptr msg) {
    try {
        SessionListByIdListType::iterator it;
        for (it = sessionsById.begin(); it != sessionsById.end(); it++) {
            it->second->sendMessage(msg);
        }
    } catch (...) {
    }
}

int SessionManager::getNextSessiionId() {
    nextSessionId++;
    return nextSessionId;
}
