//
// Created By: Reza Alizadeh Majd
//

#include <IdPClient.h>
#include <iostream>

using namespace std;

IdPClient::IdPClient() {
    RestClient::init();
}

IdPClient::~IdPClient() {
    RestClient::disable();
}

IdPClient& IdPClient::Instance() {
    static IdPClient instance;
    return instance;
}

bool IdPClient::updateToken() {
    try {
        this->_token = DeviceIdentityClient::Instance().getAccessToken();
    } catch(std::runtime_error* err) {
        GLOG_WRN ("ERROR: Could not refresh device access token: " + string(err->what()));
        return false;
    }
    return true;
}

RestClient::Response IdPClient::post(const string& path, const string& data, const map<string, string>& headers) {
    if (_token.isExpired()) {
        this->updateToken();
    }
    RestClient::Connection conn(_config.host);
    conn.SetTimeout(5);
    RestClient::HeaderFields requestHeaders; 
    requestHeaders["content-type"] = "application/json";
    requestHeaders["authorization"] = "Bearer " + _token.token;
    for (const auto& kv : headers) {
        requestHeaders[kv.first] = kv.second;
    }
    conn.SetHeaders(requestHeaders);
    return conn.post(path, data);
}


bool IdPClient::submitStatus(const string& status) {
    auto resp = this->post("/devices/stats", status);
    GLOG_INF("Server response: "+to_string(resp.code));
    if (resp.code != 200 && resp.code != 201) {
        GLOG_WRN("ERROR: Status submission failed: " + resp.body );
        return false;
    }
    return true;
}

bool IdPClient::submitEvent(const string& event) {
    auto resp = this->post("/devices/events", event);
    if (resp.code != 200 && resp.code != 201) {
        GLOG_WRN("ERROR: Event submission failed: " + resp.body );
        return false;
    }
    return true;
}
