//
// Created by Fakhri on 4/28/19.
//

#include "DeviceConfig.h"

DeviceConfig::DeviceConfig() {

    try {
        //mkdir((string(getpwuid(getuid())->pw_dir) + DEVPATH).c_str(),0755);
        YAML::Node config = YAML::LoadFile(string(getpwuid(getuid())->pw_dir) + DEVPATH);
        YAML::Node identifire = config["identifier"][0]["uuid"];
        this->uuId = identifire.as<string>();
        YAML::Node manager = config["manager"][0]["ip"];
        this->managerIp = manager.as<string>();
        YAML::Node token = config["api"][0]["token"];
        this->token= token.as<string>();
    } catch(exception& e) {
        std::cout << e.what() << "\n";
    }

}

string DeviceConfig::getUUID() {
    return this->uuId;
}

string DeviceConfig::getManagerIP() {
    return this->managerIp;
}

string DeviceConfig::getToken() {
    return this->token;
}
