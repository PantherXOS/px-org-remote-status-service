//
// Created by f.sajadi on 4/23/19.
//
#include <iostream>
#include "RESTclient.h"

int main(){
    RESTclient client;
    client.send("http://localhost:4030","{\"fooooo\": \"baaaar\"}");
    sleep(10);
    return 0;
}