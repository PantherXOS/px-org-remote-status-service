//
// Created by Fakhri  on 4/21/19.
//


#include "StatsParam.h"

void StatsParam::setCpuUser(float cpuUser) {
    this->cpuUser = cpuUser;

}

void StatsParam::setCpuWait(float cpuWait) {
    this->cpuWait = cpuWait;

}

void StatsParam::setCpuSystem(float cpuSystem) {
    this->cpuSystem = cpuSystem;

}

void StatsParam::setMemoryUsage(float memoryUsage) {
    this->memoryUsage = memoryUsage;
}

void StatsParam::setMemoryUsed(float memoryUsed) {
    this->memoryUsed = memoryUsed;

}

void StatsParam::setStatsParam(string system, float cpuUser, float cpuWait, float cpuSystem, float memoryUsage,
                               float memoryUsed, int upTime,int bootTime) {
    this->memoryUsed = memoryUsed;
    this->memoryUsage = memoryUsage;
    this->cpuSystem = cpuSystem;
    this->cpuWait = cpuWait;
    this->cpuUser = cpuUser;
    this->upTime = upTime;
    this->bootTime = bootTime;
}

void StatsParam::setBootTime(int time) {
    this->bootTime = time;
}

void StatsParam::setUptime(int time) {
    this->upTime = time;
}

void StatsParam::setSystem(string system) {
    this->system = system;

}

string StatsParam::getSystem() {
    return this->system;
}

int StatsParam::getBootTime() {
    return this->bootTime;
}

int StatsParam::getUpTime() {
    return this->upTime;
}

float StatsParam::getCpuUser() {
    return this->cpuUser;
}

float StatsParam::getCpuWait() {
    return this->cpuWait;
}

float StatsParam::getCpuSystem() {
    return this->cpuSystem;
}

float StatsParam::getMemoryUsage() {
    return this->memoryUsage;
}

float StatsParam::getMemoryUsed() {
    return this->memoryUsed;
}
