//
// Created by fakhri on 4/14/19.
//


#include "SystemStats.h"

string SystemStats::monitStatusGetValue(string status, string key) {
    std::istringstream stream{status};
    std::string line;
    while (std::getline(stream, line)) {
        size_t found = line.find(key);
        if (found != string::npos) {
            found += key.size();
            string value = line.substr(found, line.size());
            found += value.find_first_not_of(" ");
            value = line.substr(found, line.size());
            return value;
            }
    }
    return "";
}

void SystemStats::monitStatusParser(string status, StatsParam &statParam) {
    for (string key : systemStatsKeys) {
        GLOG_INF("systemStatsKeys parser, key = "+key);
        if (key == "System")
            statParam.generalParams.setSystem(monitStatusGetValue(status, key));
        else if (key == "version")
            statParam.generalParams.setVersion("NOT Exist/ TODO");
        else if (key == "uptime")
            statParam.generalParams.setUpTime(atoi(monitStatusGetValue(status, key).c_str()));
        else if (key == "boot time")
            statParam.generalParams.setBootTime(UTILS::DATETIME::ConvertToTimeStamp(monitStatusGetValue(status, key)));
        else if (key == "memory usage") {
            string delimiter = " ";
            size_t pos = 0;
            string token, amount;
            GLOG_INF("status: "+status);
            string st = monitStatusGetValue(status, key);
            int count = 0;
            while ((pos = st.find(delimiter)) != std::string::npos) {
                token = st.substr(0, pos);
                if (count == 0)
                    amount = token;
                else if (count == 1) {
                    if (token == "GB")
                        statParam.memoryParams.setUsed(atof(amount.c_str()));
                    if (token == "MB")
                        statParam.memoryParams.setUsed((atof(amount.c_str())) / 1024);
                    if (token == "KB")
                        statParam.memoryParams.setUsed((atof(amount.c_str())) / 1048576);
                    if (token == "B")
                        statParam.memoryParams.setUsed((atof(amount.c_str())) / 1073741824);
                }
                ++count;
                st.erase(0, pos + delimiter.length());
            }
            GLOG_INF("memory usage value: "+st);
            token = st.substr(1, st.size() - 2);
            statParam.memoryParams.setUsage(atof(token.c_str()));
        } else if (key == "swap usage") {
            string delimiter = " ";
            size_t pos = 0;
            string token, amount;
            string st = monitStatusGetValue(status, key);
            int count = 0;
            while ((pos = st.find(delimiter)) != std::string::npos) {
                token = st.substr(0, pos);
                if (count == 0)
                    amount = token;
                else if (count == 1) {
                    if (token == "GB")
                        statParam.swapParams.setUsed(atof(amount.c_str()));
                    if (token == "MB")
                        statParam.swapParams.setUsed((atof(amount.c_str())) / 1024);
                    if (token == "KB")
                        statParam.swapParams.setUsed((atof(amount.c_str())) / 1048576);
                    if (token == "B")
                        statParam.swapParams.setUsed((atof(amount.c_str())) / 1073741824);
                }
                ++count;
                st.erase(0, pos + delimiter.length());
            }
            token = st.substr(1, st.size() - 2);
            statParam.swapParams.setUsage(atof(token.c_str()));
        } else if (key == "cpu") {
            string delimiter = " ";
            size_t pos = 0;
            string token;
            string st = monitStatusGetValue(status, key);
            int count = 0;
            while ((pos = st.find(delimiter)) != std::string::npos) {
                token = st.substr(0, pos - 3);
                if (count == 0)
                    statParam.cpuParams.setUser(atof(token.c_str()));
                else if (count == 1)
                    statParam.cpuParams.setSystem(atof(token.c_str()));
                ++count;
                st.erase(0, pos + delimiter.length());
            }
            token = st.substr(0, st.size() - 3);
            statParam.cpuParams.setWait(atof(token.c_str()));
        }
    }
}


StatsParam SystemStats::get(const AppConfig &cfg) {
    StatsParam statsParam;
    string command = "monit -c /tmp/monitrc status";
    // string command2= "cp "+ cfg.monitConfig +" /tmp/monitrc";
    //UTILS::COMMAND::Execute(command.c_str());  
    string result = UTILS::COMMAND::Execute(command.c_str());
    GLOG_INF("Monit status result: "+result);
    monitStatusParser(result, statsParam);
    GLOG_INF("Status data parsed");
    string disk = UTILS::COMMAND::Execute("df -h |grep ^/dev/sd");
    diskStatusParser(disk, statsParam.diskParams);
    GLOG_INF("Status successfully read");
    return statsParam;
}

void SystemStats::diskStatusParser(string status, vector<DiskParams> &diskStatus) {
    istringstream stream{status};
    string line, found;
    while (std::getline(stream, line)) {
        std::string str = line;
        std::stringstream tokenizer(str);
        string n, deviceName;
        int i = 0;
        DiskParams diskParam;
        while (tokenizer >> n) {
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

SystemStats::SystemStats(const AppConfig &cfg) {
    m_monitRCPath = initMonitRCFile(cfg.monitConfig);
    runMonitProcess();
}


string SystemStats::initMonitRCFile(const string &monitrcPath) {
    string defaultPath = string(getpwuid(getuid())->pw_dir) + "/monitrc";
    string configPath = monitrcPath.empty() ? defaultPath : UTILS::PXFILE::abspath(monitrcPath);
    if (!UTILS::PXFILE::exists(configPath)) {
        ofstream cfgStream(configPath);
        if (!cfgStream.is_open()) {
            //don't have write permission to configPath, use default path instead
            cout << "WRN: don't have write permission to config path: " << configPath << endl;
            cout << "\tuse default path instead: " << defaultPath << endl;
            configPath = defaultPath;
            cfgStream.open(configPath);
        }

        // read default config file from bin
        string inFile = (UTILS::PATH::getExecPath() + "monitrc").c_str();
        std::ifstream configFile(inFile);
        std::string content((std::istreambuf_iterator<char>(configFile)),
                            (std::istreambuf_iterator<char>()));
        cfgStream << content.c_str();
        cfgStream.close();
    }
    return configPath;
}

bool SystemStats::runMonitProcess() {
    string command2 = "cp "+ m_monitRCPath +" /tmp/monitrc";
    string res = UTILS::COMMAND::Execute(command2.c_str()); 
    string res2 = "chmod 700 /tmp/monitrc";  
    UTILS::COMMAND::Execute(res2.c_str());
    string command = "monit -c /tmp/monitrc > /tmp/monitrc.runner.log 2>&1";
    //chmod(m_monitRCPath.c_str(), S_IRWXU);
    
    string result = UTILS::COMMAND::Execute(command.c_str());
    GLOG_INF("monit run successfully " + result );
    return true;
}

string SystemStats::exec(const char* cmd) {
    std::array<char, 128> buffer;
    std::string result;
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}