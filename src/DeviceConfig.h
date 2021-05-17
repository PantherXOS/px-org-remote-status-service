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

struct DeviceConfig {
    string client_id;       // 05b6913a-90e0-48bb-b26c-15b4a880dd20
    string config_version;  // 0.0.3
    string domain;          // onesid1.com
    string host;            // http://localhost:4000
    string id;              // b76e25f5-3a1d-4d0e-8ac7-ecd3fdfafb70
    string initiated_on;    // '2021-03-13 22:51:06.699495'
    bool is_managed;        // true
    string key_security;    // default
    string key_type;        // RSA:2048
    string location;        // Undefined
    string role;            // desktop
    string title;           // DESKTOP-n4mfgVwWJortSZYJoLFBBW

    bool inited;

    explicit DeviceConfig(const string& path = string());
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_DEVICECONFIG_H
