//
// Created by Fakhri on 4/23/19.
//
#include <iostream>
#include "RESTclient.h"

int main(){
    RESTclient client;
    client.send("http:///localhost:8080//device-stats//","{\"fooooo\": \"baaaar\"}");
    sleep(10);
    return 0;
}