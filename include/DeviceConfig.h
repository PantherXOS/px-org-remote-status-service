//
// Created by root on 4/28/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_DEVICECONFIG_H
#define PX_ORG_REMOTE_STATUS_SERVICE_DEVICECONFIG_H
using namespace std;

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <zconf.h>
#include <pwd.h>
#include <sys/stat.h>

#include <yaml-cpp/yaml.h>
#define DEVPATH "/.config/device.conf"

class DeviceConfig {
public:
    DeviceConfig();
    string getUUID();
    string getManagerIP();
    string getToken();
private:
    string uuId;
    string managerIp;
    string token;
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_DEVICECONFIG_H
