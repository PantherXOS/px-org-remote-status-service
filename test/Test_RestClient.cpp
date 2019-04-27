//
// Created by Fakhri on 4/23/19.
//
#include <iostream>
#include "RESTclient.h"

int main(){
    RESTclient client;
    client.send("http:///localhost:8080//device-stats//", std::__cxx11::string(), "{\"fooooo\": \"baaaar\"}");
    sleep(10);
    return 0;
}