//
// Created by Reza Alizadeh Majd on 11/12/18.
//

#ifndef PX_HUB_SERVICE_RPCSERVER_H
#define PX_HUB_SERVICE_RPCSERVER_H

#include <thread>
#include <string>

class RPCServer {

public:
    explicit RPCServer(const std::string &addr = std::string());

public:
    void start();
    void stop();
    void restart();

private:
    std::string address;
    std::thread tServer;
    bool isRunning = false;

};


#endif //PX_HUB_SERVICE_RPCSERVER_H
