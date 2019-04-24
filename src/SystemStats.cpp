//
// Created by fakhri on 4/14/19.
//


#include "SystemStats.h"

string SystemStats::monitStatusGetValue(string status, string key) {
    std::istringstream stream{status};
    std::string line;
    while (std::getline(stream, line)) {
        size_t found = line.find(key);
        if (found != string::npos)
        {
            found+=key.size();
            string value  = line.substr(found, line.size());
            found+=value.find_first_not_of(" ");
            value  = line.substr(found, line.size());
            return value;
        }
    }
    return "";
}

StatsParam SystemStats::monitStatusParser(string status) {
    StatsParam statParam;
    for(string key : systemStatsKeys){
        if(key == "System")
            statParam.generalParams.setSystem(monitStatusGetValue(status,key));
        else if(key == "version")
            statParam.generalParams.setVersion("NOT Exist/ TODO");
        else if(key == "uptime")
            statParam.generalParams.setUpTime(atoi(monitStatusGetValue(status,key).c_str()));
        else if(key == "boot time")
            statParam.generalParams.setBootTime(atoi(monitStatusGetValue(status,key).c_str()));
        else if(key == "memory usage")
            //TODO split memory
            statParam.memoryParams;
         else if(key == "swap usage")
             //TODO split swap
            statParam.swapParams;
        else if(key == "cpu")
            //TODO split cpu
            statParam.cpuParams;
    }
    return statParam;
}

StatsParam SystemStats::get() {
    string result = UTILS::COMMAND::Execute("monit status");
    return monitStatusParser(result);
}
