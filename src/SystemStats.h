//
// Created by Fakhri on 4/14/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_SYSTEMSTATS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_SYSTEMSTATS_H

#include <iostream>
#include <vector>
#include <sstream>
#include <zconf.h>
#include <pwd.h>
#include <sys/stat.h>
#include <AppConfig.h>
#include "Stats.h"
#include "Utils.h"
#include "StatsParam.h"
#include "Logger.h"


class SystemStats {
public:
    SystemStats(const AppConfig &cfg);
    StatsParam get(const AppConfig &cfg);

protected:
    string initMonitRCFile(const string &monitrcPath);
    bool runMonitProcess();

private:
    vector<string> systemStatsKeys = {"System", "version","cpu", "uptime " ,"memory usage", "swap usage", "boot time"};

    void monitStatusParser(string status,StatsParam&  statParam);
    string monitStatusGetValue (string status,string key);
    void diskStatusParser(string status, vector<DiskParams> &diskStatus);
    string exec(const char* cmd);

private:
    std::string m_monitRCPath;
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_SYSTEMSTATS_H
