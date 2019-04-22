//
// Created by Fakhri on 4/22/19.
//

#include "CpuDBParam.h"

void CpuDBParam::setUser(float user) {
    this->user = user;
}

void CpuDBParam::setSystem(float system) {
    this->system = system;
}

void CpuDBParam::setWait(float wait) {
    this->wait = wait;
}

float CpuDBParam::getUser() {
    return this->user;
}

float CpuDBParam::getSystem() {
    return this->system;
}

float CpuDBParam::getWait() {
    return this->wait;
}
