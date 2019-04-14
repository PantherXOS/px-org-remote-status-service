//
// Created by fakhri on 4/14/19.
//

#include <sstream>
#include <vector>
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

map<string, string> SystemStats::monitStatusParser(string status) {
    map <string, string> systemStatus;
    for(string key : systemStatsKeys){
        string value = monitStatusGetValue(status,key);
        systemStatus.insert(std::pair<string,string>(key,value));
    }
    return systemStatus;
}

map<string,string> SystemStats::get() {
    string result = UTILS::COMMAND::Execute("monit status");
    return monitStatusParser(result);
}


