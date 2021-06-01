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

void MemoryParams::setTotal(float total) {
    this->total = total;
}

float MemoryParams::getUsed() {
    return this->used;
}

float MemoryParams::getUsage() {
    return this->usage;
}

float MemoryParams::getTotal() {
    return this->total;
}

string MemoryParams::toString() {
    return "Memory/swap Used  : " + to_string(used) +"\n" +
            "Memory/swap Usage: " + to_string(usage)+"\n";
}
