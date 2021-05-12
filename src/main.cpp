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
#include "Logger.h"

Logger gLogger("px-org-remote-status-service");



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
void logInit(bool debugMode)
{
    /// Initialize the logger
    LogTarget logTarget = LogTarget::SYSLOG;
    LogLevel logLevel = LogLevel::INF;
    if(debugMode)
        logTarget = LogTarget::CONSOLE;

    GLOG_INIT(logTarget, logLevel);
    GLOG_INF("=> Starting Remote status Service");
}

int main(int argc, char *argv[]) {
    init();
    bool debugMode = false;
    AppConfig cfg;

    CLI::App app{"px-org-remote-status-service: Remote Status Service"};
    app.add_option("-i,--interval", cfg.interval, "status report interval", true);
    app.add_option("-m,--monit-config", cfg.monitConfig, "monitrc configuration path");
    app.add_option("-d,--debug", debugMode, "Active debug mode");
    
   
    CLI11_PARSE(app, argc, argv);
    cfg.printConfig();

    logInit(debugMode);

    RPCServer rpcServer;
    rpcServer.start();
    DeviceConfig deviceConfig;
    StatChecker statChecker(cfg);
    EventHandler eventHandler;
    GLOG_INF("Initializing ...");
    statChecker.run();
    eventHandler.run();
    while (running) {
        sleep(1);
    };
    statChecker.stop();
    eventHandler.stop();
    rpcServer.stop();
}