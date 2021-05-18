//
// Created By: Reza Alizadeh Majd
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_IDP_CLIENT_H
#define PX_ORG_REMOTE_STATUS_SERVICE_IDP_CLIENT_H

#include <map>
#include <string>
#include <DeviceConfig.h>
#include <DeviceIdentityClient.h>
#include <restclient-cpp/restclient.h>
#include <restclient-cpp/connection.h>
#include "Logger.h"

using namespace std;

class IdPClient {
private:
    explicit IdPClient();
    virtual ~IdPClient();

public:
    static IdPClient& Instance();

protected:
    bool updateToken();
    RestClient::Response post(const string& path, const string& data, const map<string, string>& headers = map<string, string>());

public:
    bool submitStatus(const string& status);
    bool submitEvent(const string& event);

protected:
    AccessToken _token;
    DeviceConfig _config;
};

#endif
