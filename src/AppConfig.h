//
// Created by panther on 4/22/21.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_APPCONFIG_H
#define PX_ORG_REMOTE_STATUS_SERVICE_APPCONFIG_H

#include <iostream>
#include <string>

#define DEFAULT_STAT_INTERVAL 300

struct AppConfig {
    int interval;
    std::string monitConfig;

    explicit AppConfig() : interval(DEFAULT_STAT_INTERVAL) {}

    inline void printConfig() {
        std::cout << "Application Config:" << std::endl;
        std::cout << " - Status check interval: \t" << this->interval << std::endl;
        std::cout << " - Monit config path: \t" << this->monitConfig << std::endl;
        std::cout << "-----" << std::endl;
    }
};

#endif //PX_ORG_REMOTE_STATUS_SERVICE_APPCONFIG_H
