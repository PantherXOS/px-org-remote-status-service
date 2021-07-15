//
// Created by fakhri on 4/14/19.
//

#include <CLI11/CLI11.hpp>
#include <DeviceConfig.h>
#include <AppConfig.h>
#include <QObject>
#include <QCoreApplication>
#include <QTimer>

#include <iostream>
#include "RPCServer.h"
#include "StatChecker.h"
#include "EventHandler.h"
#include "Logger.h"

Logger gLogger("px-org-remote-status-service");



using namespace std;

void logInit(bool debugMode)
{
    /// Initialize the logger
    LogTarget logTarget = LogTarget::SYSLOG;
    LogLevel logLevel = LogLevel::INF;
    if(debugMode)
        logTarget = LogTarget::CONSOLE;

    GLOG_INIT(logTarget, logLevel);
    GLOG_INF("Starting PantherX Organization Remote Status Service ...");
}

int main(int argc, char *argv[]) {
    QCoreApplication *qtApp = new QCoreApplication(argc,argv);
    bool debugMode = false;
    AppConfig cfg;

    CLI::App app{"px-org-remote-status-service: Remote Status Service"};
    app.add_option("-i,--interval", cfg.interval, "status report interval", true);
    app.add_option("-m,--monit-config", cfg.monitConfig, "monitrc configuration path");
    app.add_option("-d,--debug", debugMode, "Active debug mode");
    
   
    CLI11_PARSE(app, argc, argv);
    cfg.printConfig();
    logInit(debugMode);
    GLOG_INF("PATH: "+string(getenv("PATH")));   
    RPCServer rpcServer;
    rpcServer.start();
    DeviceConfig deviceConfig;
    StatChecker statChecker(cfg);
    EventHandler eventHandler;
    GLOG_INF("Initializing ...");
    statChecker.run();
    eventHandler.run();
    qtApp->exec();
    statChecker.stop();
    eventHandler.stop();
    rpcServer.stop();
}