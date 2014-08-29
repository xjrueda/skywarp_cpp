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

#ifndef SESSIONMANAGER_H
#define	SESSIONMANAGER_H


#include <websocketpp/connection.hpp>
#include "globalDatatypes.h"
#include "SkywarpExceptions.h"
#include "ClientSession.h"
#include <memory>


using namespace std;

namespace skywarp {

    class SessionManager {
    public:
        typedef std::shared_ptr<ClientSession> Session;
        SessionManager();
        virtual ~SessionManager();
        void setServer(Server&);
        void createSession(websocketpp::connection_hdl);
        void removeSession(websocketpp::connection_hdl);
        Session getSessionFromId(int);
        Session getsessionFromHandler(websocketpp::connection_hdl);
        void broadcastMessage(string);
        void broadcastMessage(Server::message_ptr);
    private:
        int getNextSessiionId();
        Server* server;
        int nextSessionId;

        typedef std::map<websocketpp::connection_hdl, shared_ptr<ClientSession>, std::owner_less<websocketpp::connection_hdl>> SessionListByHandlerListType;
        typedef std::map<int, shared_ptr<ClientSession>> SessionListByIdListType;
        SessionListByHandlerListType sessionsByHandler;
        SessionListByIdListType sessionsById;

        mutex sessionLock;
    };
}
#endif	/* SESSIONMANAGER_H */

