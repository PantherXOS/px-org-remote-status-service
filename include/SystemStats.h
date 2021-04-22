//
// Created by Fakhri on 4/14/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_SYSTEMSTATS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_SYSTEMSTATS_H
#include "Stats.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <sstream>
#include <zconf.h>
#include <pwd.h>
#include <sys/stat.h>
#include "StatsParam.h"
#include <AppConfig.h>

class SystemStats {
public:
    SystemStats(const AppConfig &cfg);
    StatsParam get();

protected:
    string initMonitRCFile(const string &monitrcPath);
    bool runMonitProcess();

private:
    vector<string> systemStatsKeys = {"System", "version","cpu", "uptime " ,"memory usage", "swap usage", "boot time"};

    void monitStatusParser(string status,StatsParam&  statParam);
    string monitStatusGetValue (string status,string key);
    void diskStatusParser(string status, vector<DiskParams> &diskStatus);

private:
    std::string m_monitRCPath;
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_SYSTEMSTATS_H
