//
// Created by Fakhri on 5/1/21.
//

#include "LoadParams.h"

void LoadParams::setUser(float user) {
    this->user = user;
}

void LoadParams::setSystem(float system) {
    this->system = system;
}

void LoadParams::setWait(float wait) {
    this->wait = wait;
}

float LoadParams::getUser() {
    return this->user;
}

float LoadParams::getSystem() {
    return this->system;
}

float LoadParams::getWait() {
    return this->wait;
}

string LoadParams::toString() {
    return "cpu User    : "+ to_string(user) +"\n" +
            "cpu System : "+ to_string(system) + "\n" +
            "cpu Wait   : "+ to_string(wait)+ "\n";
}
