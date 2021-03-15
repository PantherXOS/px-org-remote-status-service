//
// Created by Reza Alizadeh Majd
//

#include <DeviceIdentityClient.h>

#include <sstream>
#include <array>
#include <memory>
#include <vector>
#include "rapidjson/document.h"

#define IDENTITY_PROCESS "px-device-identity --operation GET_ACCESS_TOKEN"
#define ACCESS_TOKEN_KEY "access_token"
#define EXPIRES_AT_KEY "expires_at"


// ============================================================================
AccessToken::AccessToken(const string& token, time_t exp) : 
    token(token), 
    expiresAt(exp) {}

bool AccessToken::isExpired() {
    time_t now = std::time(nullptr);
    return now > this->expiresAt;
}
// ============================================================================

DeviceIdentityClient& DeviceIdentityClient::Instance() {
    static DeviceIdentityClient client; 
    return client;
}

/**
 * request for access_token from px-device-identity 
 **/
AccessToken DeviceIdentityClient::getAccessToken() {
    array<char, 1228> buffer;
    string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(IDENTITY_PROCESS, "r"), pclose);
    if (!pipe) {
        throw new std::runtime_error("popen() failed");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    vector<string> lines;
    std::stringstream ss(result);
    string line;
    rapidjson::Document doc;
    while (std::getline(ss, line)) {
        lines.push_back(line);
        cout << line << endl;
    }
    if (lines.size() == 0 
        || doc.Parse(lines[lines.size() - 1].c_str()).HasParseError()
        || !doc.HasMember(ACCESS_TOKEN_KEY)) {
        std::cout << line << std::endl;
        throw new std::runtime_error("invalid response");
    }

    return AccessToken(
        doc[ACCESS_TOKEN_KEY].GetString(),
        doc[EXPIRES_AT_KEY].GetInt());
}
