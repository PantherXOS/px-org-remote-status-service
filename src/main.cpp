//
// Created by fakhri on 4/14/19.
//
#include <iostream>
#include "RPCServer.h"
#include "StatChecker.h"
#include "EventHandler.h"
#include <CLI11/CLI11.hpp>
#include <signal.h>
#include <DeviceConfig.h>

using namespace std;

sig_atomic_t running = 1;

void sigIntHandler(int s) {
    running = 0;
}

int init() {
    struct sigaction sigInt;
    sigInt.sa_handler = sigIntHandler;
    sigemptyset(&sigInt.sa_mask);
    sigInt.sa_flags = 0;
    sigaction(SIGINT, &sigInt, NULL);
    return 0;
}


int main(int argc, char *argv[]) {
    init();

    int interval = 300 /* 5 minutes as default interval */;

    CLI::App app{"px-org-remote-status-service: Remote Status Service"};
    app.add_option("-i,--interval", interval, "status report interval", true);

    CLI11_PARSE(app, argc, argv);

    cout << "- Status Report Interval: " << interval << endl;

    RPCServer rpcServer;
    rpcServer.start();
    DeviceConfig deviceConfig;
    StatChecker statChecker(interval);
    EventHandler eventHandler;
    cout << "px-org-remote-status-service is run" << endl;
    statChecker.run();
    eventHandler.run();
    while (running) {
        sleep(1);
    };
    statChecker.stop();
    eventHandler.stop();
    rpcServer.stop();
}