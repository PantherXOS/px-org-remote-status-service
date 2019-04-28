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
    conn->AppendHeader("Authroization", "Bearer "+token);
    conn->AppendHeader("Content-Type", "application/json");

    RestClient::Response r = conn->post("/", json);
    RestClient::disable();

    return r.code;
}
