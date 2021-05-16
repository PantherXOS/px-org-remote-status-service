//
// Created by Reza Alizadeh Majd on 11/12/18.
//

#ifndef PX_HUB_SERVICE_RPCSERVER_H
#define PX_HUB_SERVICE_RPCSERVER_H

#include <thread>
#include <string>
#include <cassert>

class RPCServer {

public:
    explicit RPCServer();

public:
    void        start();
    void        stop();
    void        restart();
    

private:
    std::string address;
    std::thread tServer;
    bool isRunning = false;
    std::string  getUser();
    bool        mkpath(const std::string &path);
    std::string basedir(const std::string &path);
    bool        exists(const std::string &fpath);
    bool        addrExists(const std::string &fpath);
    bool        addrRemove(const std::string &path);

};


#endif //PX_HUB_SERVICE_RPCSERVER_H
