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
#include <iostream>
#include <exception>

#include "JsonSerializer.h"

namespace skywarp {

    JsonSerializer::JsonSerializer() {
    }

    JsonSerializer::~JsonSerializer() {
    }

    string JsonSerializer::serializeRPCResult(string requestId, Json::Value appMessage) {
        try {
            Json::Value JsonRPCResult = generateResultEnvelope(requestId, appMessage);
            Json::FastWriter writer;
            string serializedJsonRPCResult = writer.write(JsonRPCResult);
            return serializedJsonRPCResult;
        } catch (std::exception& e) {
            cout << "Exception serializing: " << e.what() << endl;
            std::cerr << "Exception serializing: " << e.what();
        }

    }

    string JsonSerializer::serializeRPCError(string requestId, int errCode, string errMessage) {
        try {
            Json::Value jsonRPCError;
            Json::Value errorData;

            errorData["code"] = errCode;
            errorData["message"] = errMessage;

            jsonRPCError["jsonrpc"] = "2.0";
            jsonRPCError["error"] = errorData;
            jsonRPCError["id"] = requestId;

            Json::FastWriter writer;
            string serializedJsonRPCError = writer.write(jsonRPCError);
            return serializedJsonRPCError;
        } catch (...) {
            // pending exception handling
        }
    }

    Json::Value JsonSerializer::generateResultEnvelope(string requestId, Json::Value appMessage) {
        try {
            Json::Value JsonRPCResult;
            JsonRPCResult["jsonrpc"] = "2.0";
            JsonRPCResult["result"] = appMessage;
            JsonRPCResult["id"] = requestId;
            return JsonRPCResult;
        } catch (...) {
            // pending exception handling
        }
    }
}