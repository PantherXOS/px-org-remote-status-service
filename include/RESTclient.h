//
// Created by root on 4/23/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_RESTCLIENT_H
#define PX_ORG_REMOTE_STATUS_SERVICE_RESTCLIENT_H

#include <iostream>
#include <thread>
#include <zconf.h>
#include <iostream>
#include <restclient-cpp/restclient.h>
#include <restclient-cpp/connection.h>

using namespace std;

class RESTclient {
public:
    int send (string path, string json);
private:
    string path,json;
    std::thread statThread;
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_RESTCLIENT_H
