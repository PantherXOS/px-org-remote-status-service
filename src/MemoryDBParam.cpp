//
// Created by root on 4/22/19.
//

#include "MemoryDBParam.h"

void MemoryDBParam::setUsed(float used) {
    this->used = used;
}

void MemoryDBParam::setUsage(float usage) {
    this->usage = usage;
}

float MemoryDBParam::getUsed() {
    return this->used;
}

float MemoryDBParam::getUsage() {
    return this->usage;
}
