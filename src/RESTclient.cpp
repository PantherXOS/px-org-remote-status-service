//
// Created by root on 4/23/19.
//

#include "RESTclient.h"

int RESTclient::send(string path, string json) {
    statThread = std::thread([&]() {
        RestClient::init();
        RestClient::Connection* conn = new RestClient::Connection(path);
        conn->SetBasicAuth("WarMachine68", "WARMACHINEROX");
        conn->SetTimeout(5);
        conn->SetUserAgent("foo/cool");
        conn->FollowRedirects(true);
        conn->FollowRedirects(true, 3);
        RestClient::HeaderFields headers;
        headers["Accept"] = "application/json";
        conn->SetHeaders(headers);
        conn->AppendHeader("X-MY-HEADER", "foo");
        conn->SetCAInfoFilePath("/etc/custom-ca.crt");

        RestClient::Response r = conn->get("/get");
        cout << r.code << endl;
        cout << r.body << endl;
// set different content header for POST, PUT and PATCH
        conn->AppendHeader("Content-Type", "application/json");
        r = conn->post("/device-stats", "{\"foo\": \"bla\"}");
        cout << r.code << endl;
        cout << r.body << endl;
        RestClient::disable();
    });
    return 0;
}
