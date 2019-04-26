//
// Created by Fakhri on 4/22/19.
//

#include "MemoryParams.h"

void MemoryParams::setUsed(float used) {
    this->used = used;
}

void MemoryParams::setUsage(float usage) {
    this->usage = usage;
}

float MemoryParams::getUsed() {
    return this->used;
}

float MemoryParams::getUsage() {
    return this->usage;
}

string MemoryParams::toString() {
    return "Memory/swap Used  : " + to_string(used) +"\n" +
            "Memory/swap Usage: " + to_string(usage)+"\n";
}
