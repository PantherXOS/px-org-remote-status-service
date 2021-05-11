//
// Created by Reza Alizadeh Majd on 11/12/18.
//

#include "RPCServer.h"
#include "RPCHandler.h"

#include <capnp/rpc-twoparty.h>
#include <kj/async-unix.h>
#include <Utils.h>

using namespace std;

#define RPC_PATH          "/tmp/" + string(getenv("USER")) + "/rpc"
#define RPC_SOCKET_PATH   RPC_PATH + "/remote-status-service"
#define RPC_MKDIR_CMD     string("mkdir -p ") + RPC_PATH



RPCServer::RPCServer(const std::string &addr) {
    this->address = addr;
    if (addr.empty()) {
        system(string(RPC_MKDIR_CMD).c_str());
        string rpcPath =  UTILS::PXFILE::abspath(RPC_SOCKET_PATH);
        if (UTILS::PXFILE::exists(rpcPath)) {
            UTILS::PXFILE::remove(rpcPath);
        }
        this->address = string("unix:") + rpcPath;
    }
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