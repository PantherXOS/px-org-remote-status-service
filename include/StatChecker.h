//
// Created by Fakhri on 4/27/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_STATCHECKER_H
#define PX_ORG_REMOTE_STATUS_SERVICE_STATCHECKER_H

#include <thread>
#include <iostream>
#include <fstream>
#include <array>
#include <bits/unique_ptr.h>
#include <sstream>
#include <StatusDatabase.h>
#include "SystemStats.h"
#include "RPCServer.h"
#include "StatsParam.h"
#include "JsonBuilder.h"
#include "DeviceConfig.h"
#include <yaml-cpp/yaml.h>


class StatChecker {
public:
    void run();
    void stop();
    DeviceConfig deviceConfig;

private:
    volatile int threadMode;
    std::thread thread;
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_STATCHECKER_H
