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

#define MAX_TABLE_RECORD 500


using namespace std;
using namespace SQLite;

class StatusDatabase {

#define DB_NAME "db"
#define DB_PATH "/.userdata/status/"

public:

   static StatusDatabase & instance(void);

    bool readGeneralStats(GeneralParams &resultGeneralStats);
    int insertGeneralStats(GeneralParams generalStats);

    bool readCpuStats(CpuParams &resultCpuStats, int gid);
    int insertCpuStats(CpuParams cpuStats, int gid);

    bool readMemoryStats(MemoryParams &resultMemoryStats, int gid);
    int inserMemorytStats(MemoryParams memoryStats, int gid);

    bool readDiskStats(DiskParams &resultDiskStats, int gid);
    int inserDiskStats(DiskParams diskStats, int gid);

    bool readSwapStats(MemoryParams &resultSwapStats, int gid);
    int insertSwaptStats(MemoryParams swapStats, int gid);
    int generalId();

private:
    StatusDatabase() :
            mDb(string(getpwuid(getuid())->pw_dir) + DB_PATH+DB_NAME,SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE)
    {
        try {
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS general (id INTEGER PRIMARY KEY,system TEXT,version TEXT,upTime INTEGER,bootTime INTEGER)");
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS cpu (id INTEGER PRIMARY KEY,user REAL,system REAL,wait REAL,gid INTEGER)");
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS memory (id INTEGER PRIMARY KEY, memoryUsed REAL,memoryUsage REAL,gid INTEGER)");
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS swap (id INTEGER PRIMARY KEY, swapUsed REAL,swapUsage REAL,gid INTEGER)");
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS disk (id INTEGER PRIMARY KEY, name TEXT , free REAL, total REAL, used REAL, usage REAL,gid INTEGER)");
            }
        catch (std::exception& e)
        {
            std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
        }

    }

    SQLite::Database    mDb;    ///< Database connection
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_STATUSDATABASE_H
