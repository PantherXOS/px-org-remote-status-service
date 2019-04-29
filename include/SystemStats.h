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

class SystemStats {
public:
    SystemStats();
    StatsParam get();

private:
    vector<string> systemStatsKeys = {"System", "version","cpu", "uptime " ,"memory usage", "swap usage", "boot time"};

    void monitStatusParser(string status,StatsParam&  statParam);
    string monitStatusGetValue (string status,string key);
    void diskStatusParser(string status, vector<DiskParams> &diskStatus);
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_SYSTEMSTATS_H
