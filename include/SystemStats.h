//
// Created by fakhri on 4/14/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_SYSTEMSTATS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_SYSTEMSTATS_H
#include "Stats.h"
#include "Utils.h"
#include <iostream>
#include <vector>

class SystemStats : public Stats {
public:
    map<string,string> get();

private:
    vector<string> systemStatsKeys = {"System", "cpu", "uptime " ,"memory usage", "swap usage", "boot time"};

    map<string,string> monitStatusParser(string status);
    string monitStatusGetValue (string status,string key);
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_SYSTEMSTATS_H
