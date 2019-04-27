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
    this->path = path;
    this->json = json;
    statThread = std::thread([&]() {
        RestClient::Response r = RestClient::post(this->path, "application/json", this->json);
        cout << r.code << endl;
        // TODO check
    });
    statThread.join();
    return 0;
}
