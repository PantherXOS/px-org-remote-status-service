//
// Created by Fakhri on 4/22/19.
//

#include "CpuParams.h"

void CpuParams::setNumber(int  number){
    this->number = number;
}

void CpuParams::setFrequency(string frequency) {
    this->frequency = frequency;
}

void CpuParams::setmodel(string model) {
    this->model = model;
}

int CpuParams::getNumber() {
    return this->number;
}

string CpuParams::getFrequency() {
    return this->frequency;
}

string CpuParams::getmodel() {
    return this->model;
}

string CpuParams::toString() {
    return "cpu number    : "+ to_string(number) +"\n" +
            "cpu frequency : "+ frequency + "\n" +
            "cpu model   : "+ model + "\n";
}
