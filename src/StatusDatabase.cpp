//
// Created by Fakhri on 4/21/19.
//

#include "StatusDatabase.h"

StatusDatabase & StatusDatabase::instance() {
    string path = (string(getpwuid(getuid())->pw_dir) + USER_DATA);
    mkdir(path.c_str(),0755);
    path += STATUS_DATA;
    mkdir(path.c_str(),0755);

    static StatusDatabase instance;
    return instance;
}

bool StatusDatabase::readGeneralStats(GeneralParams &resultGeneralStats) {
    bool hasResult = false;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM general ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            hasResult = true;
            resultGeneralStats.setBootTime(query.getColumn("bootTime"));
            resultGeneralStats.setUpTime(query.getColumn("upTime"));
            resultGeneralStats.setSystem(query.getColumn("system"));
            resultGeneralStats.setVersion(query.getColumn("version"));
        }
        // Reset the query to use it again
        query.reset();
    }
    catch(std::exception& e)
    {
        std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
    }
    return hasResult;
}

int StatusDatabase::insertGeneralStats(GeneralParams generalStats) {
    try {
        int res = this->mDb.exec("INSERT INTO general VALUES (NULL,\""+
                                 generalStats.getSystem() + "\",\""+
                                 generalStats.getVersion() + "\",\""+
                                 to_string(generalStats.getUpTime())+ "\",\""+
                                 to_string(generalStats.getBootTime()) + "\")");
        if(res == 0)
            return -2;
        SQLite::Statement query(mDb, "SELECT id FROM general ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            int id = query.getColumn(0).getInt()- MAX_TABLE_RECORD;
            if(id>0)
                this->mDb.exec("DELETE FROM general WHERE id="+to_string(id));
        }
        query.reset();
    }
    catch(std::exception& e)
    {
        std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}

bool StatusDatabase::readCpuStats(CpuParams &resultCpuStats, int gid) {
    bool hasResult = false;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM cpu WHERE  gid = \"" + to_string(gid) + "\" ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            hasResult = true;
            resultCpuStats.setSystem(query.getColumn("system").getDouble());
            resultCpuStats.setUser(query.getColumn("user").getDouble());
            resultCpuStats.setWait(query.getColumn("wait").getDouble());
        }
        // Reset the query to use it again
        query.reset();
    }
    catch(std::exception& e)
    {
        std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
    }
    return hasResult;
}

int StatusDatabase::insertCpuStats(CpuParams cpuStats, int gid) {
    try {
        int res = this->mDb.exec("INSERT INTO cpu VALUES (NULL,"+
                                 to_string(cpuStats.getUser())+ ","+
                                 to_string(cpuStats.getSystem())+ ","+
                                 to_string(cpuStats.getWait()) + ","+
                                 to_string(gid) + ")");
        if(res == 0)
            return -2;
        SQLite::Statement query(mDb, "SELECT id FROM cpu ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            int id = query.getColumn(0).getInt()- MAX_TABLE_RECORD;
            if(id>0)
                this->mDb.exec("DELETE FROM cpu WHERE id="+to_string(id));
        }
        query.reset();
    }
    catch(std::exception& e)
    {
        std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}

bool StatusDatabase::readMemoryStats(MemoryParams &resultMemoryStats, int gid) {
    bool hasResult = false;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM memory WHERE  gid = \"" + to_string(gid) + "\" ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            hasResult = true;
            resultMemoryStats.setUsed(query.getColumn("memoryUsed").getDouble());
            resultMemoryStats.setUsage(query.getColumn("memoryUsage").getDouble());
        }
        // Reset the query to use it again
        query.reset();
    }
    catch(std::exception& e)
    {
        std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
    }
    return hasResult;
}

int StatusDatabase::inserMemorytStats(MemoryParams memoryStats, int gid) {
    try {
        int res = this->mDb.exec("INSERT INTO memory VALUES (NULL,"+
                                 to_string(memoryStats.getUsed())+","+
                                 to_string(memoryStats.getUsage()) + ","+
                                 to_string(gid) + ")");
        if(res == 0)
            return -2;
        SQLite::Statement query(mDb, "SELECT id FROM memory ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            int id = query.getColumn(0).getInt()- MAX_TABLE_RECORD;
            if(id>0)
                this->mDb.exec("DELETE FROM memory WHERE id="+to_string(id));
        }
        query.reset();
    }
    catch(std::exception& e)
    {
        std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}

bool StatusDatabase::readDiskStats(vector<DiskParams> &resultDiskStats, int gid) {
    DiskParams diskParams;
    resultDiskStats.clear();
    bool hasResult = false;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM disk WHERE  gid = \"" + to_string(gid) + "\" ORDER BY id DESC ");

        while (query.executeStep()) {
            hasResult = true;
            diskParams.setName(query.getColumn("name"));
            diskParams.setFree(query.getColumn("free").getDouble());
            diskParams.setTotal(query.getColumn("total").getDouble());
            diskParams.setUsage(query.getColumn("usage").getDouble());
            diskParams.setUsed(query.getColumn("used").getDouble());
            resultDiskStats.push_back(diskParams);
        }
        // Reset the query to use it again
        query.reset();
    }
    catch(std::exception& e)
    {
        std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
    }
    return hasResult;
}

int StatusDatabase::insertDiskStats(vector<DiskParams> diskStats, int gid) {
    for(DiskParams disk : diskStats) {
        try {
            int res = this->mDb.exec("INSERT INTO disk VALUES (NULL,\"" +
                                             disk.getName() + "\",\"" +
                                     to_string(disk.getFree()) + "\",\"" +
                                     to_string(disk.getTotal()) + "\",\"" +
                                     to_string(disk.getUsed()) + "\",\"" +
                                     to_string(disk.getUsage()) + "\",\"" +
                                     to_string(gid) + "\")");
            if (res == 0)
                return -2;
            SQLite::Statement query(mDb, "SELECT id FROM disk ORDER BY id DESC  LIMIT 1");
            while (query.executeStep()) {
                int id = query.getColumn(0).getInt() - MAX_TABLE_RECORD;
                if (id > 0)
                    this->mDb.exec("DELETE FROM disk WHERE id=" + to_string(id));
            }
            query.reset();
        }
        catch (std::exception &e) {
            std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
            return -1;
        }
    }
    return 0;
}

bool StatusDatabase::readSwapStats(MemoryParams &resultSwapStats, int gid) {
    bool hasResult = false;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM swap WHERE  gid = \"" + to_string(gid) + "\" ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            hasResult = true;
            resultSwapStats.setUsed(query.getColumn("swapUsed").getDouble());
            resultSwapStats.setUsage(query.getColumn("swapUsage").getDouble());
        }
        // Reset the query to use it again
        query.reset();
    }
    catch(std::exception& e)
    {
        std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
    }
    return hasResult;
}

int StatusDatabase::insertSwaptStats(MemoryParams swapStats, int gid) {
    try {
        int res = this->mDb.exec("INSERT INTO swap VALUES (NULL,\""+
                                 to_string(swapStats.getUsed())+ "\",\""+
                                 to_string(swapStats.getUsage()) + "\",\""+
                                 to_string(gid) + "\")");
        if(res == 0)
            return -2;
        SQLite::Statement query(mDb, "SELECT id FROM swap ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            int id = query.getColumn(0).getInt()- MAX_TABLE_RECORD;
            if(id>0)
                this->mDb.exec("DELETE FROM swap WHERE id="+to_string(id));
        }
        query.reset();
    }
    catch(std::exception& e)
    {
        std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
        return -1;
    }
    return 0;
}

int StatusDatabase::generalId() {
    try {
        SQLite::Statement query(mDb, "SELECT id FROM general ORDER BY id DESC  LIMIT 1");
        int id;
        while (query.executeStep()) {
           id = query.getColumn(0).getInt();
        }
        query.reset();
        return id;
    }
        catch(std::exception& e)
        {
            std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
            return -1;
        }
}

void StatusDatabase::insertAllStats(StatsParam statParams) {
    insertGeneralStats(statParams.generalParams);
    int gid = generalId();
    inserMemorytStats(statParams.memoryParams,gid);
    insertSwaptStats(statParams.swapParams,gid);
    insertCpuStats(statParams.cpuParams,gid);
    insertDiskStats(statParams.diskParams,gid);
}

void StatusDatabase::readAllStats(StatsParam &statsParam) {
    readGeneralStats(statsParam.generalParams);
    int gid = generalId();
    readMemoryStats(statsParam.memoryParams,gid);
    readCpuStats(statsParam.cpuParams,gid);
    readSwapStats(statsParam.swapParams, gid);
    readDiskStats(statsParam.diskParams,gid);
}

void StatusDatabase::deletLastStat() {
    int gid =  generalId();
    try {
        SQLite::Statement query(mDb,"DELETE FROM general WHERE id="+to_string(gid));
        SQLite::Statement query1(mDb,"DELETE FROM swap WHERE gid="+to_string(gid));
        SQLite::Statement query2(mDb,"DELETE FROM cpu WHERE gid="+to_string(gid));
        SQLite::Statement query3(mDb,"DELETE FROM memory WHERE gid="+to_string(gid));
        SQLite::Statement query4(mDb,"DELETE FROM disk WHERE gid="+to_string(gid));

        query.reset();
        query1.reset();
        query2.reset();
        query3.reset();
        query4.reset();
    }
    catch(std::exception& e)
    {
        std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
    }

}

