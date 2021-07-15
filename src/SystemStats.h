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
#include <resolv.h>
#include <arpa/inet.h>
#include <QNetworkInterface>
#include <qdebug.h>
#include "resolv.h"
#include <arpa/inet.h>
#include "QDnsLookup"
#include "QHostInfo"
#include "Stats.h"
#include "Utils.h"
#include "StatsParam.h"
#include "Logger.h"
#include "InstalledApplication.h"


class SystemStats {
public:
    SystemStats(const AppConfig &cfg);
    StatsParam get(const AppConfig &cfg);
    vector<InstalledApplication> getApplications();

protected:
    string initMonitRCFile(const string &monitrcPath);
    bool runMonitProcess();

private:
    vector<string> systemStatsKeys = {"System", "version","cpu", "uptime " ,"memory usage", "swap usage", "boot time","load average", "hdd"};
    void monitStatusParser(string status,StatsParam&  statParam);
    string monitStatusGetValue (string status,string key);
    void diskStatusParser(vector<DiskParams> &diskStatus);
    vector<NetworkParam> networkParamsParser();
    string exec(const char* cmd);
    //void networkParamsNmcliParser(vector<NetworkParam> &result);
    void networkParamsFalbackParser(vector<NetworkParam> &result);
    std::string m_monitRCPath;
    void stringSeprator(std::string source,std::string seprator,vector<string> &resultList);
    NetworkParam deviceParamsParser(std::string data, std::string device);
    void readDns(vector<std::string> & allDns);
    

};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_SYSTEMSTATS_H
