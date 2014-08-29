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

#ifndef METHODDELEGATORMANAGER_H
#define	METHODDELEGATORMANAGER_H

#include <string>
#include <map>
#include <functional>
#include <json/json.h>
#include "JsonRPCExceptions.h"
#include "SessionManager.h"

using namespace std;

namespace skywarp {

    class MethodDelegatorManager {
    public:
        typedef std::function<void(Json::Value, SessionManager::Session, string) > ApplicationDelegateType;
        MethodDelegatorManager();
        virtual ~MethodDelegatorManager();
        void subscribeDelegate(string, ApplicationDelegateType, bool);
        void unSubscribeDelegate(string);
        void callDelegate(string, Json::Value, SessionManager::Session, string);
    private:

        struct Delegate {

            void setDelegate(ApplicationDelegateType delegate, bool async) {
                _delegate = delegate;
                launchAsync = async;
            }

            ApplicationDelegateType getDelegate() {
                return _delegate;
            }

            bool getlaunchAsync() {
                return launchAsync;
            }
        private:
            ApplicationDelegateType _delegate;
            bool launchAsync;
        };
        std::map<string, Delegate> applicationDelegatesMap;
    };
}
#endif	/* METHODDELEGATORMANAGER_H */

