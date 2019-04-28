//
// Created by Fakhri on 4/27/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_STATCHECKER_H
#define PX_ORG_REMOTE_STATUS_SERVICE_STATCHECKER_H

#include <thread>
#include <iostream>
#include <array>
#include <bits/unique_ptr.h>
#include <sstream>
#include <StatusDatabase.h>
#include "SystemStats.h"
#include "RPCServer.h"
#include "StatsParam.h"
#include "JsonBuilder.h"
#include "RESTclient.h"

class StatChecker {
public:
    void run();
    void stop();
private:
    volatile int threadMode;
    std::thread thread;
    string getRestApiPath();
    string getUUID();
    string getToken();
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_STATCHECKER_H
