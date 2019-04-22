//
// Created by root on 4/22/19.
//

#include <GeneralDBParam.h>

#include "GeneralDBParam.h"

void GeneralDBParam::setSystem(string system) {
    this->system = system;
}

void GeneralDBParam::setVersion(string verion) {
    this->version = version;

}

void GeneralDBParam::setUpTime(int upTime) {
    this->upTime =upTime;

}

void GeneralDBParam::setBootTime(int bootTime) {
    this->bootTime = bootTime;

}

string GeneralDBParam::getSystem() {
    return this->system;
}

string GeneralDBParam::getVersion() {
    return this->version;
}

int GeneralDBParam::getUptime() {
    return this->upTime;
}

int GeneralDBParam::getootTime() {
    return this->bootTime;
}
