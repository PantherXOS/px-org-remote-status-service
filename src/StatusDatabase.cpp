//
// Created by Fakhri on 4/21/19.
//

#include "StatusDatabase.h"

StatusDatabase & StatusDatabase::instance() {
    string path = (string(getpwuid(getuid())->pw_dir) + USER_DATA);
    mkdir(path.c_str(),0755);
    path += SHARE;
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
            resultGeneralStats.setcpuUsage(query.getColumn("cpuUsage").getDouble());
            resultGeneralStats.setcpuUsed(query.getColumn("cpuUsed").getDouble());
            resultGeneralStats.setHddUsage(query.getColumn("hddUsage").getDouble());
            resultGeneralStats.setHddUsed(query.getColumn("hddUsed").getDouble());
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
                                 to_string(generalStats.getBootTime())+ "\",\""+
                                 to_string(generalStats.getcpuUsage())+ "\",\""+
                                 to_string(generalStats.getcpuUsed()) + "\",\""+
                                 to_string(generalStats.getHddUsage())+ "\",\""+
                                 to_string(generalStats.getHddUsed()) + "\")");
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

bool StatusDatabase::readCpuStats(vector<CpuParams> &resultCpuList, int gid) {
    resultCpuList.clear();
    bool hasResult = false;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM cpu WHERE  gid = \"" + to_string(gid) + "\" ORDER BY id DESC ");        
        while (query.executeStep()) {
            CpuParams cpuParams;
            hasResult = true;
            cpuParams.setNumber(query.getColumn("number").getInt());
            cpuParams.setFrequency(query.getColumn("frequency"));
            cpuParams.setmodel(query.getColumn("model"));
            resultCpuList.push_back(cpuParams);
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

int StatusDatabase::insertCpuStats(vector<CpuParams> cpuList, int gid) {
    for(auto cpu : cpuList) {
        try {
            int res = this->mDb.exec("INSERT INTO cpu VALUES (NULL,\"" +
                                                to_string(cpu.getNumber()) + "\",\"" +
                                                cpu.getFrequency() + "\",\"" +                                                                               
                                                cpu.getmodel() + "\",\"" + 
                                                to_string(gid) + "\")");
            if (res == 0)
                return -2;
            SQLite::Statement query(mDb, "SELECT id FROM cpu ORDER BY id DESC  LIMIT 1");
            while (query.executeStep()) {
                int id = query.getColumn(0).getInt() - MAX_TABLE_RECORD;
                if (id > 0)
                    this->mDb.exec("DELETE FROM cpu WHERE id=" + to_string(id));
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

bool StatusDatabase::readMemoryStats(MemoryParams &resultMemoryStats, int gid) {
    bool hasResult = false;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM memory WHERE  gid = \"" + to_string(gid) + "\" ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            hasResult = true;
            resultMemoryStats.setUsed(query.getColumn("memoryUsed").getDouble());
            resultMemoryStats.setUsage(query.getColumn("memoryUsage").getDouble());
            resultMemoryStats.setTotal(query.getColumn("memorTotal").getDouble());
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
                                 to_string(memoryStats.getTotal()) + ","+
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
            diskParams.setCapacity(query.getColumn("capacity").getDouble());
            diskParams.setType(query.getColumn("type"));
            diskParams.setModel(query.getColumn("model"));
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
                                     to_string(disk.getCapacity()) + "\",\"" +
                                     disk.getType() + "\",\"" +
                                     disk.getModel() + "\",\"" +
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
    insertNetworkParams(statParams.networkParamList,gid);
    insertLoadAverageStats(statParams.loadAverage, gid);
    
}

void StatusDatabase::readAllStats(StatsParam &statsParam) {
    readGeneralStats(statsParam.generalParams);
    int gid = generalId();
    readMemoryStats(statsParam.memoryParams,gid);
    readCpuStats(statsParam.cpuParams,gid);
    readSwapStats(statsParam.swapParams, gid);
    readDiskStats(statsParam.diskParams,gid);
    readNetworkParams(statsParam.networkParamList,gid);
    readLoadAverageStats(statsParam.loadAverage,gid);
}

void StatusDatabase::deletLastStat() {
    int gid =  generalId();
    try {
        SQLite::Statement query(mDb,"DELETE FROM general WHERE id="+to_string(gid));
        SQLite::Statement query1(mDb,"DELETE FROM swap WHERE gid="+to_string(gid));
        SQLite::Statement query2(mDb,"DELETE FROM cpu WHERE gid="+to_string(gid));
        SQLite::Statement query3(mDb,"DELETE FROM memory WHERE gid="+to_string(gid));
        SQLite::Statement query4(mDb,"DELETE FROM disk WHERE gid="+to_string(gid));
        SQLite::Statement query5(mDb,"DELETE FROM network WHERE gid="+to_string(gid));
        SQLite::Statement query6(mDb,"DELETE FROM loadAverage WHERE gid="+to_string(gid));

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

bool StatusDatabase::readNetworkParams(vector<NetworkParam> &resultNetworkParams, int gid){
    
    resultNetworkParams.clear();
    bool hasResult = false;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM network WHERE  gid = \"" + to_string(gid) + "\" ORDER BY id DESC ");        
        while (query.executeStep()) {
            NetworkParam networkParam;
            hasResult = true;
            NetworkAddress IPv4;
            NetworkAddress IPv6;
            networkParam.setName(query.getColumn("name"));
            networkParam.setMac(query.getColumn("mac"));
            networkParam.setDbType(query.getColumn("type"));
            IPv4.ip = query.getColumn("ip4_ip").getString();
            IPv4.extIp = query.getColumn("ip4_extip").getString();
            stringSeprator(query.getColumn("ip4_dns").getString(),",", IPv4.dns);
            networkParam.setIP4(IPv4);
            IPv6.ip = query.getColumn("ip6_ip").getString();
            IPv6.extIp = query.getColumn("ip6_extip").getString();
            stringSeprator(query.getColumn("ip6_dns").getString(),",", IPv6.dns);
            networkParam.setIP6(IPv6);
            if(query.getColumn("active").getInt() == 100){
                networkParam.setActive(true);
                networkParam.connectionStatus = 100;
            }
            else{
                networkParam.setActive(false);
                 networkParam.connectionStatus = 200;
            }
            resultNetworkParams.push_back(networkParam);
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


int StatusDatabase::insertNetworkParams(vector<NetworkParam> networkParams, int gid){    
        for(auto net : networkParams) {
        try {
            int res = this->mDb.exec("INSERT INTO network VALUES (NULL,\"" +
                                                net.getName() + "\",\"" +
                                                net.getMac() + "\",\"" +
                                                net.getType() + "\",\"" +
                                                to_string(net.connectionStatus) + "\",\"" +
                                                net.getIP4().ip + "\",\"" +
                                                net.getIP4().extIp + "\",\"" +
                                                net.getIP4().gateway + "\",\"" +
                                                net.getDbDns(net.getIP4().dns)+ "\",\"" +
                                                net.getIP6().ip + "\",\"" +
                                                net.getIP6().extIp + "\",\"" +
                                                net.getIP6().gateway + "\",\"" +                                 
                                                net.getDbDns(net.getIP6().dns) + "\",\"" + 
                                                to_string(gid) + "\")");
            if (res == 0)
                return -2;
            SQLite::Statement query(mDb, "SELECT id FROM network ORDER BY id DESC  LIMIT 1");
            while (query.executeStep()) {
                int id = query.getColumn(0).getInt() - MAX_TABLE_RECORD;
                if (id > 0)
                    this->mDb.exec("DELETE FROM network WHERE id=" + to_string(id));
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

void StatusDatabase::stringSeprator(std::string source,std::string seprator,vector<string> &resultList){
    size_t pos = 0;
    string token;
    while ((pos = source.find(seprator)) != std::string::npos) {
        token = source.substr(0, pos);
        resultList.push_back(token);
        source.erase(0, pos + seprator.length());
    }
    resultList.push_back(source);
}


bool StatusDatabase::readLoadAverageStats(LoadParams &resultLoadAveargeStats, int gid) {
    bool hasResult = false;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM loadAverage WHERE  gid = \"" + to_string(gid) + "\" ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            hasResult = true;
            resultLoadAveargeStats.setSystem(query.getColumn("system").getDouble());
            resultLoadAveargeStats.setUser(query.getColumn("user").getDouble());
            resultLoadAveargeStats.setWait(query.getColumn("wait").getDouble());
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

int StatusDatabase::insertLoadAverageStats(LoadParams loadAveargeStats, int gid) {
    try {
        int res = this->mDb.exec("INSERT INTO loadAverage VALUES (NULL,"+
                                 to_string(loadAveargeStats.getUser())+ ","+
                                 to_string(loadAveargeStats.getSystem())+ ","+
                                 to_string(loadAveargeStats.getWait()) + ","+
                                 to_string(gid) + ")");
        if(res == 0)
            return -2;
        SQLite::Statement query(mDb, "SELECT id FROM loadAverage ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            int id = query.getColumn(0).getInt()- MAX_TABLE_RECORD;
            if(id>0)
                this->mDb.exec("DELETE FROM loadAverage WHERE id="+to_string(id));
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

