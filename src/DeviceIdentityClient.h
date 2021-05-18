//
// Created by Reza Alizadeh Majd
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_DEVICE_IDENTITY_CLIENT_H
#define PX_ORG_REMOTE_STATUS_SERVICE_DEVICE_IDENTITY_CLIENT_H

#include <iostream>
#include <string>
#include <ctime>
#include "Logger.h"

using namespace std;

struct AccessToken {
    string token;
    time_t expiresAt;

    explicit AccessToken() = default;
    AccessToken(const string& token, time_t exp);

    bool isExpired();
};

class DeviceIdentityClient {
private:
    explicit DeviceIdentityClient() = default;

public:
    static DeviceIdentityClient& Instance(); 
    AccessToken getAccessToken();
};

#endif

