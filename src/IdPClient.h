//
// Created By: Reza Alizadeh Majd
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_IDP_CLIENT_H
#define PX_ORG_REMOTE_STATUS_SERVICE_IDP_CLIENT_H

#include <map>
#include <string>
#include <DeviceConfig.h>
#include <px-auth-lib-cpp/DeviceIdentityClient/DeviceIdentityClient.h>
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
    
    PX::AUTH::AccessToken token() const;
    bool updateToken();

protected:
    RestClient::Response post(const string& path, const string& data, const map<string, string>& headers = map<string, string>());

public:
    bool submitStatus(const string& status);
    bool submitEvent(const string& event);

protected:
    PX::AUTH::DeviceIdentityClient _identityClient;
    PX::AUTH::AccessToken _token;
    DeviceConfig _config;
};

#endif
