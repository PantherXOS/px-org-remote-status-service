//
// Created by Fakhri on 4/22/19.
//

#include <GeneralParams.h>

#include "GeneralParams.h"

void GeneralParams::setSystem(string system) {
    this->system = system;
}

void GeneralParams::setVersion(string version) {
    this->version = version;

}

void GeneralParams::setUpTime(int upTime) {
    this->upTime =upTime;

}

void GeneralParams::setBootTime(int bootTime) {
    this->bootTime = bootTime;

}

string GeneralParams::getSystem() {
    return this->system;
}

string GeneralParams::getVersion() {
    return this->version;
}

int GeneralParams::getUpTime() {
    return this->upTime;
}

int GeneralParams::getBootTime() {
    return this->bootTime;
}

string GeneralParams::toString() {
    return  "system   : " + system + "\n" +
            "version  : " + version + "\n" +
            "upTime   : " + to_string(upTime)  + "\n" +
            "bootTime : " + to_string(bootTime);
}
