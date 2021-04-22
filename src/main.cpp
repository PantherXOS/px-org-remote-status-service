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
#include <AppConfig.h>

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

    AppConfig cfg;

    CLI::App app{"px-org-remote-status-service: Remote Status Service"};
    app.add_option("-i,--interval", cfg.interval, "status report interval", true);
    app.add_option("-m,--monit-config", cfg.monitConfig, "monitrc configuration path");

    CLI11_PARSE(app, argc, argv);
    cfg.printConfig();

    RPCServer rpcServer;
    rpcServer.start();
    DeviceConfig deviceConfig;
    StatChecker statChecker(cfg);
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