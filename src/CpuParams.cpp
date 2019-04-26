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
    return "cpu User    : "+ to_string(user) +"\n" +
            "cpu System : "+ to_string(system) + "\n" +
            "cpu Wait   : "+ to_string(wait)+ "\n";
}
