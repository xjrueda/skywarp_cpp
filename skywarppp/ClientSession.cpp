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

#include "ClientSession.h"

ClientSession::ClientSession(){
}

ClientSession::ClientSession(websocketpp::connection_hdl conHdl, Server& srv, int id) : connectionHdl(conHdl), server(&srv), sessionId(id) {

}

ClientSession::~ClientSession() {
}

void ClientSession::setId(int id) {
    sessionId = id;
}

void ClientSession::setConnectionHandler(websocketpp::connection_hdl conHdl) {
    connectionHdl = conHdl;
}

void ClientSession::setServer(Server& srv) {
    server = &srv;
}

void ClientSession::sendMessage(string messageText) {
    server->send(connectionHdl, messageText, websocketpp::frame::opcode::text);
}

void ClientSession::sendMessage(Server::message_ptr msg) {
    server->send(connectionHdl, msg);
}

int ClientSession::getId() {
    return sessionId;
}

websocketpp::connection_hdl ClientSession::getConnectionHandler() {
    return connectionHdl;
}

