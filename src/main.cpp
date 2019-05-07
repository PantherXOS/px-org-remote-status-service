//
// Created by fakhri on 4/14/19.
//
#include <iostream>
#include "RPCServer.h"
#include "StatChecker.h"
#include "EventHandler.h"
#include <signal.h>
#include <DeviceConfig.h>

using namespace std;

sig_atomic_t running = 1;

void sigIntHandler(int s){
    running = 0;
}

int init () {
    struct sigaction sigInt;
    sigInt.sa_handler = sigIntHandler;
    sigemptyset(&sigInt.sa_mask);
    sigInt.sa_flags = 0;
    sigaction(SIGINT, &sigInt, NULL);
    return 0;
}


int main(){
    init();
    RPCServer rpcServer;
    rpcServer.start();
    DeviceConfig deviceConfig;
    StatChecker statChecker;
    EventHandler eventHandler;
    cout<<"px-org-remote-status-servece is run"<<endl;
    statChecker.run();
    eventHandler.run();
    while (running);
    statChecker.stop();
    eventHandler.stop();
    rpcServer.stop();
}