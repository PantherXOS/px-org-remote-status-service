//
// Created by Fakhri on 4/22/19.
//

#include "DiskParams.h"

void DiskParams::setName(string name) {
    this->name = name;
}

void DiskParams::setFree(float free) {
    this->free = free;
}

void DiskParams::setTotal(float total) {
    this->total = total;
}

void DiskParams::setUsed(float used) {
this->used = used;
}

void DiskParams::setUsage(float usage) {
    this->usage = usage;
}

string DiskParams::getName() {
    return this->name;
}

float DiskParams::getFree() {
    return this->free;
}

float DiskParams::getTotal() {
    return this->total;
}

float DiskParams::getUsed() {
    return this->used;
}

float DiskParams::getUsage() {
    return this->usage;
}

string DiskParams::toString() {
    return "Name  : " + name + "\n" +
           "Total : " + to_string(total) + "\n" +
           "Free  : " + to_string(free) + "\n" +
           "Used  : " + to_string(used) + "\n" +
           "Usage : " + to_string(usage);
}
