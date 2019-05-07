//
// Created by Fakhri on 5/7/19.
//


#ifndef PX_ORG_REMOTE_STATUS_SERVICE_EVENTHANDLER_H
#define PX_ORG_REMOTE_STATUS_SERVICE_EVENTHANDLER_H
using namespace std;

#include <thread>
#include <iostream>
#include <fstream>
#include <array>
#include <bits/unique_ptr.h>
#include <sstream>
#include "EventDatabase.h"
#include "SystemStats.h"
#include "RPCServer.h"
#include "EventObject.h"
#include "JsonBuilder.h"
#include "RESTclient.h"
#include "DeviceConfig.h"
#include <yaml-cpp/yaml.h>



class EventHandler {
public:
    static EventHandler & instance(void);
    void run();
    void stop();
    bool isEventReceived();
    void setEventReveived();
private:
    volatile bool eventReceived;
    volatile int threadMode;
    std::thread thread;
};
#endif //PX_ORG_REMOTE_STATUS_SERVICE_EVENTHANDLER_H
