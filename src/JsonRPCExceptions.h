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
#ifndef JSONRCPEXCEPTION_H
#define	JSONRCPEXCEPTION_H

#include <boost/format.hpp>
#include <iostream>
#include <sstream>

using namespace std;

namespace skywarp {

    class JsonRPCParseError : public exception {
    public:

        JsonRPCParseError() {
        }

        ~JsonRPCParseError() throw () {
        }

        const string what() throw () {
            return errorTemplate;
        }
    private:
        string _id;
        string errorTemplate = "{\"jsonrpc\": \"2.0\", \"error\": {\"code\": -32700, \"message\": \"Parse error\"},\"id\":null}";
    };

    class JsonRPCInvalidRequest : public exception {
    public:

        JsonRPCInvalidRequest(string id, string data) : _id(id), _data(data) {
        }

        ~JsonRPCInvalidRequest() throw () {
        }

        const string what() throw () {
            string __id = _id.empty() ? "null" : string("\"") + _id + string("\"");
            stringstream _exception;
            _exception << boost::format(errorTemplate) % _data % __id;
            return _exception.str();
        }
    private:
        string _id;
        string _data;
        string errorTemplate = "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32601,\"message\":\"Invalid request\",\"data\":\"%1%\"},\"id\":%2%}";
    };

    class JsonRPCMethodNotFound : public exception {
    public:

        JsonRPCMethodNotFound(string id) : _id(id) {
        }

        ~JsonRPCMethodNotFound() throw () {
        }

        const string what() throw () {
            string __id = _id.empty() ? "null" : string("\"") + _id + string("\"");
            stringstream _exception;
            _exception << boost::format(errorTemplate) % __id;
            return _exception.str();
        }
    private:
        string _id;
        string errorTemplate = "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32601,\"message\":\"Method not found\"},\"id\":%1%}";
    };

    class JsonRPCMethodException : public exception {
    public:

        JsonRPCMethodException(string id, string data) : _id(id), _data(data) {
        }

        ~JsonRPCMethodException() throw () {
        }

        const string what() throw () {
            string __id = _id.empty() ? "null" : string("\"") + _id + string("\"");
            stringstream _exception;
            _exception << boost::format(errorTemplate) % _data % __id;
            return _exception.str();
        }
    private:
        string _id;
        string _data;
        string errorTemplate = "{\"jsonrpc\":\"2.0\",\"error\":{\"code\":-32603,\"message\":\"Internal error\",\"data\":\"%1%\"},\"id\":%2%}";
    };
}
#endif	/* JSONRCPEXCEPTION_H */

