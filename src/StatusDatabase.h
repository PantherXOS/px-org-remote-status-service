//
// Created by Fakhri on 4/21/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_STATUSDATABASE_H
#define PX_ORG_REMOTE_STATUS_SERVICE_STATUSDATABASE_H

#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>
#include <string>
#include <zconf.h>
#include <pwd.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include "StatsParam.h"
#include "GeneralParams.h"
#include "CpuParams.h"
#include "MemoryParams.h"
#include "DiskParams.h"
#include "NetworkParam.h"
#include "Logger.h"

#define MAX_TABLE_RECORD 100


using namespace std;
using namespace SQLite;

class StatusDatabase {

#define DB_NAME "/status-database"
#define USER_DATA "/.local"
#define SHARE "/share"
#define STATUS_DATA "/px-org-remote-status-service"
#define DB_PATH  USER_DATA+SHARE+STATUS_DATA

public:

   static StatusDatabase & instance(void);

    bool readGeneralStats(GeneralParams &resultGeneralStats);
    int insertGeneralStats(GeneralParams generalStats);

    bool readCpuStats(vector<CpuParams> &resultCpuList, int gid);
    int insertCpuStats(vector<CpuParams> cpuList, int gid);

    bool readMemoryStats(MemoryParams &resultMemoryStats, int gid);
    int inserMemorytStats(MemoryParams memoryStats, int gid);

    bool readDiskStats(vector<DiskParams> &resultDiskStats, int gid);
    int insertDiskStats(vector<DiskParams> diskStats, int gid);

    bool readNetworkParams(vector<NetworkParam> &resultNetworkParams, int gid);
    int insertNetworkParams(vector<NetworkParam> networkParams, int gid);

    bool readSwapStats(MemoryParams &resultSwapStats, int gid);
    int insertSwaptStats(MemoryParams swapStats, int gid);
    int generalId();

    void insertAllStats(StatsParam statParams);
    void readAllStats(StatsParam &statsParam);

    bool readLoadAverageStats(LoadParams &resultLoadAveargeStats, int gid);
    int insertLoadAverageStats(LoadParams loadAveargeStats, int gid);

    void deletLastStat();

    void stringSeprator(std::string source,std::string seprator,vector<string> &resultList);

private:
    StatusDatabase() :
            mDb(string(getpwuid(getuid())->pw_dir) + DB_PATH+DB_NAME,SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE)
    {
        try {
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS general (id INTEGER PRIMARY KEY,system TEXT,version TEXT,upTime INTEGER,bootTime INTEGER, cpuUsage REAL, cpuUsed REAL, hddUsage REAL, hddUsed REAL)");
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS cpu (id INTEGER PRIMARY KEY,number INTEGER,frequency TEXT,model TEXT,gid INTEGER)");
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS memory (id INTEGER PRIMARY KEY, memoryUsed REAL,memoryUsage REAL,memorTotal REAL,gid INTEGER)");
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS swap (id INTEGER PRIMARY KEY, swapUsed REAL,swapUsage REAL,gid INTEGER)");
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS disk (id INTEGER PRIMARY KEY, capacity  REAL, type TEXT, model TEXT,gid INTEGER)");
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS network (id INTEGER PRIMARY KEY, name TEXT , mac TEXT, type Text, active INTEGER, ip4_ip TEXT, ip4_extip TEXT,ip4_gateway TEXT, ip4_dns Text,ip6_ip TEXT, ip6_extip TEXT, ip6_gateway TEXT,ip6_dns Text,gid INTEGER)");        
           mDb.exec(
                    "CREATE TABLE IF NOT EXISTS loadAverage (id INTEGER PRIMARY KEY,user REAL,system REAL,wait REAL,gid INTEGER)");
            }
        catch (std::exception& e)
        {
            GLOG_WRN("Err:   SQLite exception: " + string(e.what()));
        }

    }

    SQLite::Database    mDb;    ///< Database connection
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_STATUSDATABASE_H
