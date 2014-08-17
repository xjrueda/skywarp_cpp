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

#include <cstdlib>
#include "SkywarpServer.h"
#include <future>
#include <exception>
#include <stdexcept>
#include <functional>
#include <utility>
#include <json/json.h>
#include "SkywarpExceptions.h"

#include <random>
#include <sstream>
#include <unistd.h>


using namespace std;

void onMilton(Json::Value params, int sessionId, string requestId) {
    cout << "Hola Miltoneladas como estás" << endl;
    throw string("La cagamos");
}

void onJuan(Json::Value params, int sessionId, string requestId) {
    cout << "Hola Juan Carlos como estás" << endl;
}

void lauchTraffic(std::function<void(string, Json::Value)> updateFunction) {
    cout << "generating traffic" << endl;
    std::random_device rd;
    std::default_random_engine generator(rd());
    std::uniform_int_distribution<int> distribution(1, 100);
    std::chrono::milliseconds sleepTime(1000);
    while (1) {
        int randomVal = distribution(generator);
        std::ostringstream s;
        s << randomVal;
        Json::Value message;
        message["data"] = "some=" + s.str(); 
        updateFunction("someTopic", message);
        message["data"] = "other=" + s.str(); 
        updateFunction("otherTopic",message);
        usleep(1000000);
    }
}

/*
 * 
 */
int main(int argc, char** argv) {
    try {   
        SkywarpServer swServer;
        swServer.setMethodHandler("llamaraMilton", &onMilton, true);
        swServer.setMethodHandler("llamaraJuan", &onJuan, true);
        swServer.registerTopic("someTopic");
        swServer.registerTopic("otherTopic");
        
        //defines de publisher function
        std::function<void(string, Json::Value)> publisher = std::bind(&SkywarpServer::publish,&swServer,std::placeholders::_1, std::placeholders::_2);
        std::future<void> f1;
        f1 = std::async(std::launch::async,&lauchTraffic,publisher);
        
        swServer.run(9005);
        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Exception raised: " << e.what();
    }
}

