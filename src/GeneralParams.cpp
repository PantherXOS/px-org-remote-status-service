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

void GeneralParams::setcpuUsed(float used){
    this->cpuUsed = used;
}    
void GeneralParams::setcpuUsage(float usage){
    this->cpuUsage = usage;
}

float GeneralParams::getcpuUsed(){
    return this->cpuUsed;
}

float GeneralParams::getcpuUsage(){
    return this->cpuUsage;
}

void GeneralParams::setHddUsed(float used){
    this->hddUsed = used;
}    
void GeneralParams::setHddUsage(float usage){
    this->hddUsage = usage;
}

float GeneralParams::getHddUsed(){
    return this->hddUsed;
}

float GeneralParams::getHddUsage(){
    return this->hddUsage;
}


string GeneralParams::toString() {
    return  "system   : " + system + "\n" +
            "version  : " + version + "\n" +
            "upTime   : " + to_string(upTime)  + "\n" +
            "Cpu Usage   : " + to_string(cpuUsage)  + "\n" +
            "Cpu Used   : " + to_string(cpuUsed)  + "\n" +
            "bootTime : " + to_string(bootTime)+ "\n";
}
