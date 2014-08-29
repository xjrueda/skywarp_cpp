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



#include <json/json.h>

#include "JsonRPCParser.h"

namespace skywarp {

    JsonRPCParser::JsonRPCParser() {
        parsed = false;
    }

    JsonRPCParser::~JsonRPCParser() {
    }

    string JsonRPCParser::getMethod() {
        string method;
        try {
            method = jsonMessage["method"].asString();
        } catch (const exception& e) {
            throw JsonRPCInvalidRequest(this->id, string("Validating method name: ") + e.what());
        }
        if (method.empty())
            throw JsonRPCInvalidRequest(this->id, "Method value not specified");
        const char* c = method.substr(0, 1).c_str();
        if (std::isdigit(*c))
            throw JsonRPCInvalidRequest(this->id, "Invalid method name.");
        return method;
    }

    string JsonRPCParser::getVersion() {
        string version;
        try {
            version = jsonMessage["jsonrpc"].asString();
        } catch (const exception& e) {
            throw JsonRPCInvalidRequest(this->id, string("Validating version: ") + e.what());
        }
        if (version.empty())
            throw JsonRPCInvalidRequest(this->id, "Version value not specified");
        return version;

    }

    Json::Value JsonRPCParser::getParams() {
        Json::Value params;
        try {
            params = jsonMessage["params"];
            return params;
        } catch (...) {
            throw JsonRPCInvalidRequest(this->id, "Params value not specified.");
        }
    }

    string JsonRPCParser::getId() {
        string id;
        try {
            id = jsonMessage["id"].asString();
        } catch (const exception& e) {
            throw JsonRPCInvalidRequest(this->id, string("Validating Id: ") + e.what());
        }
        if (id.empty())
            JsonRPCInvalidRequest(this->id, "Id value not specified");
        return id;
    }

    bool JsonRPCParser::ready() {
        return parsed;
    }

    void JsonRPCParser::parseMessage(string jsonString) {
        try {
            Json::Reader reader;
            bool parsed = reader.parse(jsonString, jsonMessage);
            if (parsed)
                id = jsonMessage["id"].asString();
        } catch (...) {
            throw JsonRPCParseError();
        }
    }
}

