//
// Created by Fakhri on 4/22/19.
//

#include "CpuParams.h"

void CpuParams::setUser(float user) {
    this->user = user;
}

void CpuParams::setSystem(float system) {
    this->system = system;
}

void CpuParams::setWait(float wait) {
    this->wait = wait;
}

float CpuParams::getUser() {
    return this->user;
}

float CpuParams::getSystem() {
    return this->system;
}

float CpuParams::getWait() {
    return this->wait;
}

string CpuParams::toString() {
    return "cpuUser    : "+ to_string(user) +"\n" +
            "cpuSystem : "+ to_string(system) + "\n" +
            "cpuWait   : "+ to_string(wait);
}
