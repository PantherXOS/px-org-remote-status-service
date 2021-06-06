//
// Created by Fakhri on 4/22/19.
//

#include "DiskParams.h"

void DiskParams::setType(string type) {
    this->type = type;
}

void DiskParams::setModel(string model) {
    this->model = model;
}

void DiskParams::setCapacity(float capacity) {
    this->capacity = capacity;
}

string DiskParams::getType(){
    return this->type;
}

string DiskParams::getModel() {
    return this->model;
}

float DiskParams::getCapacity() {
    return this->capacity;
}

string DiskParams::toString() {
    return "type  : " + type + "\n" +
           "model : " + model + "\n" +
           "capacity  : " + to_string(capacity);
}
