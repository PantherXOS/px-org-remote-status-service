//
// Created by root on 4/22/19.
//

#include "DiskDBParam.h"

void DiskDBParam::setName(string name) {
    this->name = name;
}

void DiskDBParam::setFree(float free) {
    this->free = free;
}

void DiskDBParam::setTotal(float total) {
    this->total = total;
}

void DiskDBParam::setUsed(float used) {
this->used = used;
}

void DiskDBParam::setUsage(float usage) {
    this->usage = usage;
}

string DiskDBParam::getName() {
    return this->name;
}

float DiskDBParam::getFree() {
    return this->free;
}

float DiskDBParam::getTotal() {
    return this->total;
}

float DiskDBParam::getUsed() {
    return this->used;
}

float DiskDBParam::getUsage() {
    return this->usage;
}
