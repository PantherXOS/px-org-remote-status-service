//
// Created by Fakhri on 4/23/19.
//

#include "RESTclient.h"

using namespace std;
int RESTclient::send(string path, string token, string json) {
    RestClient::init();
    RestClient::Connection* conn = new RestClient::Connection(path);
    conn->SetTimeout(5);
    RestClient::HeaderFields headers;
    headers["Accept"] = "application/json";
    conn->SetHeaders(headers);
    conn->AppendHeader("Authorization", "Bearer "+token);
    conn->AppendHeader("Content-Type", "application/json");

    RestClient::Response r = conn->post("/", json);
    RestClient::disable();
    cout << "PATH : " << path << endl<< endl;
    cout << "TOKEN: " << token << endl<< endl;
    cout << "JSON : " << json  << endl<< endl;
    cout << "--------------------- " << r.code << endl << endl;
    return r.code;
}
