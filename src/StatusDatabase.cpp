//
// Created by Fakhri on 4/21/19.
//

#include "StatusDatabase.h"

bool StatusDatabase::readStats( StatsParam &resultStats) {
    bool hasResult = false;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM stats ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            hasResult = true;
            resultStats.setBootTime(query.getColumn("bootTime"));
            resultStats.setSystem(query.getColumn("system"));
            resultStats.setCpuSystem(query.getColumn("cpuSystem").getDouble());
            resultStats.setCpuUser(query.getColumn("cpuUser").getDouble());
            resultStats.setCpuWait(query.getColumn("cpuWait").getDouble());
            resultStats.setMemoryUsage(query.getColumn("memoryUsage").getDouble());
            resultStats.setMemoryUsed(query.getColumn("memoryUsed").getDouble());
            resultStats.setUptime(query.getColumn("upTime"));
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
int StatusDatabase::insertStats(StatsParam stats) {
    try {
        int res = this->mDb.exec("INSERT INTO stats VALUES (NULL,\""+
                                 stats.getSystem() + "\",\""+
                                 to_string(stats.getBootTime())+ "\",\""+
                                 to_string(stats.getCpuUser()) + "\",\""+
                                 to_string(stats.getCpuSystem()) + "\",\""+
                                 to_string(stats.getCpuWait()) + "\",\""+
                                 to_string(stats.getMemoryUsed()) + "\",\""+
                                 to_string(stats.getMemoryUsage()) + "\",\""+
                                 to_string(stats.getUpTime()) + "\")");
        if(res == 0)
            return -2;
        SQLite::Statement query(mDb, "SELECT id FROM stats ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            int id = query.getColumn(0).getInt()- MAX_TABLE_RECORD;
            if(id>0)
                this->mDb.exec("DELETE FROM stats WHERE id="+to_string(id));
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

StatusDatabase & StatusDatabase::instance() {
    mkdir((string(getpwuid(getuid())->pw_dir) + DB_PATH).c_str(),0755);
    static StatusDatabase instance;
    return instance;
}

