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

void SystemStats::monitStatusParser(string status,StatsParam&  statParam) {
    for(string key : systemStatsKeys){
        if(key == "System")
            statParam.generalParams.setSystem(monitStatusGetValue(status,key));
        else if(key == "version")
            statParam.generalParams.setVersion("NOT Exist/ TODO");
        else if(key == "uptime")
            statParam.generalParams.setUpTime(atoi(monitStatusGetValue(status,key).c_str()));
        else if(key == "boot time")
            statParam.generalParams.setBootTime(UTILS::DATETIME::ConvertToTimeStamp(monitStatusGetValue(status,key)));
        else if(key == "memory usage"){
            string delimiter = " ";
            size_t pos = 0;
            string token,amount;
            string st = monitStatusGetValue(status,key);
            int count = 0;
            while ((pos = st.find(delimiter)) != std::string::npos) {
                token = st.substr(0, pos);
                if(count == 0)
                    amount = token;
                else if(count == 1){
                    if(token == "GB")
                        statParam.memoryParams.setUsed(atof(amount.c_str()));
                    if(token == "MB")
                        statParam.memoryParams.setUsed((atof(amount.c_str()))/1024);
                    if(token == "KB")
                        statParam.memoryParams.setUsed((atof(amount.c_str()))/1048576);
                    if(token == "B")
                        statParam.memoryParams.setUsed((atof(amount.c_str()))/1073741824);
                }
                ++count;
                st.erase(0, pos + delimiter.length());
            }
            token = st.substr(1, st.size()-2);
            statParam.memoryParams.setUsage(atof(token.c_str()));
        }
         else if(key == "swap usage"){
            string delimiter = " ";
            size_t pos = 0;
            string token,amount;
            string st = monitStatusGetValue(status,key);
            int count = 0;
            while ((pos = st.find(delimiter)) != std::string::npos) {
                token = st.substr(0, pos);
                if(count == 0)
                    amount = token;
                else if(count == 1){
                    if(token == "GB")
                        statParam.swapParams.setUsed(atof(amount.c_str()));
                    if(token == "MB")
                        statParam.swapParams.setUsed((atof(amount.c_str()))/1024);
                    if(token == "KB")
                        statParam.swapParams.setUsed((atof(amount.c_str()))/1048576);
                    if(token == "B")
                        statParam.swapParams.setUsed((atof(amount.c_str()))/1073741824);
                }
                ++count;
                st.erase(0, pos + delimiter.length());
            }
            token = st.substr(1, st.size()-2);
            statParam.swapParams.setUsage(atof(token.c_str()));
        }
        else if(key == "cpu"){
           string delimiter = " ";
            size_t pos = 0;
            string token;
            string st = monitStatusGetValue(status,key);
            int count = 0;
            while ((pos = st.find(delimiter)) != std::string::npos) {
                token = st.substr(0, pos-3);
                if(count == 0)
                    statParam.cpuParams.setUser(atof(token.c_str()));
                else if(count == 1)
                    statParam.cpuParams.setSystem(atof(token.c_str()));
                ++count;
                st.erase(0, pos + delimiter.length());
            }
            token = st.substr(0, st.size()-3);
            statParam.cpuParams.setWait(atof(token.c_str()));
        }
    }
}


StatsParam SystemStats::get() {
    StatsParam statsParam;
    string command = "monit -c "+string(getpwuid(getuid())->pw_dir)+"/monitrc status";
    string result = UTILS::COMMAND::Execute(command.c_str());
    monitStatusParser(result, statsParam);
    string disk = UTILS::COMMAND::Execute("df -h |grep ^/dev/sd");
    diskStatusParser(disk,statsParam.diskParams);
    return statsParam;
}

void SystemStats::diskStatusParser(string status, vector<DiskParams> &diskStatus) {
    istringstream stream{status};
    string line,found;
    while (std::getline(stream, line)) {
        std::string str = line;
        std::stringstream tokenizer( str );
        string n,deviceName;
        int i = 0;
        DiskParams diskParam;
        while( tokenizer >> n ) {
            i++;
            if (i == 1)
                diskParam.setName(n);
            else if (i == 2) diskParam.setTotal(atof(n.c_str()));
            else if (i == 3) diskParam.setUsed(atof(n.c_str()));
            else if (i == 4) diskParam.setFree(atof(n.c_str()));
            else if (i == 5) {
                diskParam.setUsage(atof(n.c_str()));
                i = 0;
                diskStatus.push_back(diskParam);
            }
        }
    }
}

SystemStats::SystemStats() {
    // read file from bin
    string inFile = (UTILS::PATH::getExecPath() + "monitrc").c_str();
    std::ifstream configFile(inFile);
    std::string content( (std::istreambuf_iterator<char>(configFile) ),
                         (std::istreambuf_iterator<char>()));

    // save to ~/
    ofstream outConfigFile;
    outConfigFile.open ((string(getpwuid(getuid())->pw_dir) + "/monitrc"));
    outConfigFile << content.c_str();
    outConfigFile.close();

    string command = "monit -c "+string(getpwuid(getuid())->pw_dir)+"/monitrc";
    chmod((string(getpwuid(getuid())->pw_dir) + "/monitrc").c_str(),S_IRWXU);
    string result = UTILS::COMMAND::Execute(command.c_str());
    cout<<"monit run successfully " << result <<endl;
}
