//
// Created by Reza Alizadeh Majd on 11/12/18.
//


#include <capnp/rpc-twoparty.h>
#include <kj/async-unix.h>
#include <Utils.h>
#include "RPCServer.h"
#include "RPCHandler.h"
#include "Logger.h"

using namespace std;

RPCServer::RPCServer() {
    string username = getUser();
    assert(username != "");
    string rpcBasePath = "/tmp/" + username + "/rpc";
    string mkdir_cmd = "mkdir -p "+rpcBasePath;
    system(mkdir_cmd.c_str());
    GLOG_INF("Making directory in "+rpcBasePath);
    if (addrExists(rpcBasePath + "/remote-status-service")) {
        addrRemove(rpcBasePath + "/remote-status-service");
    }
    this->address = string("unix:") + rpcBasePath + "/remote-status-service";
}

void RPCServer::start() {
    if (!isRunning) {
        tServer = std::thread([](void* param){
            auto instance = static_cast<RPCServer*>(param);

            kj::AsyncIoContext asyncIO = kj::setupAsyncIo();
            auto &waitScope = asyncIO.waitScope;
            auto &ioProvider = *asyncIO.provider;
            auto &network = ioProvider.getNetwork();
            auto addr = network.parseAddress(instance->address).wait(waitScope);
            auto listner = addr->listen();
            GLOG_INF("Listen to "+instance->address);
            capnp::TwoPartyServer server(kj::heap<RPCHandler>());
            auto serverPromise = server.listen(*listner);

            instance->isRunning = true;
            while (instance->isRunning) {
                waitScope.poll();
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
            }
        }, this);
    }

}

void RPCServer::stop() {
    if (isRunning) {
        isRunning = false;
        tServer.join();
    }
}

void RPCServer::restart() {
    stop();
    start();
}

string RPCServer::getUser() {
    uid_t uid = geteuid();
    struct passwd *pwd = getpwuid(uid);
    if (pwd) {
        return string(pwd->pw_name);
    }
    return string();
}

bool RPCServer::exists(const string &fpath) {
    struct stat buff{};
    return (stat(fpath.c_str(), &buff) == 0);
}

/**
 * @param path full path
 *
 * @return base directory part of input path
 */
string RPCServer::basedir(const string &path) {
    string dir;
    size_t lastpos = path.rfind('/');
//    cout << " - PATH: " << path << " - POS: " << lastpos << endl;
    if (lastpos > 0) {
        dir = path.substr(0, lastpos);
    } else if (lastpos == 0) {
        // base directory is "/"
        dir = "/";
    }
    return dir;
}

bool RPCServer::addrExists(const string &fpath) {
    struct stat buff{};
    return (stat(fpath.c_str(), &buff) == 0);
}

bool RPCServer::addrRemove(const string &path) {
    return (::remove(path.c_str()) == 0);
}

