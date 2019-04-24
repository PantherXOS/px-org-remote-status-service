//
// Created by root on 4/23/19.
//

//
// Created by root on 4/23/19.
//

#include "RESTclient.h"
#include <iostream>

using namespace std;
int RESTclient::send(string path, string json) {
    statThread = std::thread([&]() {
        cout << path << endl;
        RestClient::Response r = RestClient::post("http://localhost:8080/device-stats/", "application/json", json);
        cout << r.code << endl;
        cout << r.body << endl;
    });
    return 0;
}
