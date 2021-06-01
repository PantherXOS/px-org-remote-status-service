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
        else if (key == "version"){
            //statParam.generalParams.setVersion("NOT Exist/ TODO");
            string versionCommand = "guix --version |grep guix | cut -f 4 -d \" \"";
            string version =UTILS::COMMAND::Execute(versionCommand.c_str());
            version.erase(std::remove(version.begin(), version.end(), '\n'), version.end());
            statParam.generalParams.setVersion(version);
        }
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
                        statParam.memoryParams.setUsed(atof(amount.c_str()) * 1073741824);
                    if (token == "MB")
                        statParam.memoryParams.setUsed((atof(amount.c_str())) * 1048576);
                    if (token == "KB")
                        statParam.memoryParams.setUsed((atof(amount.c_str())) * 1024);
                    if (token == "B")
                        statParam.memoryParams.setUsed((atof(amount.c_str())));
                }
                ++count;
                st.erase(0, pos + delimiter.length());
            }
            GLOG_INF("memory usage value: "+st);
            token = st.substr(1, st.size() - 2);
            statParam.memoryParams.setUsage(atof(token.c_str()));
            string memCommand = "cat /proc/meminfo |grep \"^MemTotal:\" | tr -s \" \" | cut -f 2 -d \" \"";
            string memInfo =UTILS::COMMAND::Execute(memCommand.c_str()); 
            string unitCommand = "cat /proc/meminfo |grep \"^MemTotal:\" | tr -s \" \" | cut -f 3 -d \" \"";
            string unit =UTILS::COMMAND::Execute(unitCommand.c_str()); 
            unit.erase(std::remove(unit.begin(), unit.end(), '\n'), unit.end());
            if (unit == "GB")
                statParam.memoryParams.setTotal(stof(memInfo) * 1073741824);
            if (unit == "MB")
                statParam.memoryParams.setTotal(stof(memInfo)* 1048576);
            if (unit == "kB")
                statParam.memoryParams.setTotal(stof(memInfo) * 1024);
            if (unit == "B")
                statParam.memoryParams.setTotal(stof(memInfo));            

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
                        statParam.swapParams.setUsed(atof(amount.c_str()) * 1073741824);
                    if (token == "MB")
                        statParam.swapParams.setUsed((atof(amount.c_str())) * 1048576);
                    if (token == "KB")
                        statParam.swapParams.setUsed((atof(amount.c_str())) * 1024);
                    if (token == "B")
                        statParam.swapParams.setUsed((atof(amount.c_str())));
                }
                ++count;
                st.erase(0, pos + delimiter.length());
            }
            token = st.substr(1, st.size() - 2);
            statParam.swapParams.setUsage(atof(token.c_str()));
        } else if (key == "cpu") {
            string cpuNumberCommand = "lscpu |grep \"^CPU(s):\" | tr -d \" \" | cut -f 2 -d \":\"";
            string cpuNumber =UTILS::COMMAND::Execute(cpuNumberCommand.c_str());
            string cpumodelCommand = "cat /proc/cpuinfo |grep \"^model name\" | tr -s \" \" | cut -f 5 -d \" \"";
            string cpumodellist =UTILS::COMMAND::Execute(cpumodelCommand.c_str());
            string line;
            istringstream stream{cpumodellist};
            int num = 0;
             while (std::getline(stream, line)) {
                 CpuParams cpuPar;
                 cpuPar.setNumber(num);
                 cpuPar.setmodel(line);
                 statParam.cpuParams.push_back(cpuPar);
                 num++;
             }
            string cpuFrqCommand = "cat /proc/cpuinfo |grep \"^model name\" | tr -s \" \" | cut -f 8 -d \" \"";
            string cpuFrqlist =UTILS::COMMAND::Execute(cpuFrqCommand.c_str());
            string frqline;
            istringstream str{cpuFrqlist};
            num = 0;
            while (std::getline(str, frqline)) {
                statParam.cpuParams.at(num).setFrequency(frqline);
                num++;
            }            
            string cpuInfoCommand = "mpstat | grep -A 5 \"%idle\" | tail -n 1 | awk -F \" \" '{print 100 -  $ 12}'a";
            string cpuInfo =UTILS::COMMAND::Execute(cpuInfoCommand.c_str());                       
            auto use = 100-(stof(cpuInfo.c_str()));            
            statParam.generalParams.setcpuUsage(use);
            statParam.generalParams.setcpuUsed(stof(cpuNumber.c_str())*(stof(cpuInfo.c_str())));
            //version.erase(std::remove(version.begin(), version.end(), '\n'), version.end());
            //statParam.generalParams.setVersion(version);
        } else if (key == "load average") {
            string delimiter = " ";
            size_t pos = 0;
            string token;
            string st = monitStatusGetValue(status, key);
            int count = 0;
            while ((pos = st.find(delimiter)) != std::string::npos) {
                token = st.substr(1, pos-2);
                if (count == 0)
                    statParam.loadAverage.setUser(atof(token.c_str()));
                else if (count == 1)
                    statParam.loadAverage.setSystem(atof(token.c_str()));
                ++count;
                st.erase(0, pos + delimiter.length());
            }
            token = st.substr(1, st.size()-2);
            statParam.loadAverage.setWait(atof(token.c_str()));
        } else if (key == "hdd") {
            string hddUsageCommand = "df --total |grep \"^total\" | tr -s \" \" | cut -f 5 -d \" \" | tr -d \"%\"";
            string _hddUsage =UTILS::COMMAND::Execute(hddUsageCommand.c_str());
            string hddUsedCommand = "df --total |grep \"^total\" | tr -s \" \" | cut -f 2 -d \" \"";
            string _hddUsed =UTILS::COMMAND::Execute(hddUsedCommand.c_str()); 
            statParam.generalParams.setHddUsage(stof(_hddUsage));
            statParam.generalParams.setHddUsed(stof(_hddUsed)*1024);
            
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
    statsParam.networkParamList = networkParamsParser();
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
            GLOG_INF("WRN: don't have write permission to config path: "+ configPath );
            GLOG_INF("\tuse default path instead: " + defaultPath);
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
    string command = "monit -c /tmp/monitrc";
    
    string result = UTILS::COMMAND::Execute(command.c_str());
    GLOG_INF("monit run successfully " + result );
    return true;
}

vector<NetworkParam> SystemStats::networkParamsParser( ){
    vector<NetworkParam> netParList;
    string devCommand = "nmcli -m tabular --terse device";  
    string line, found;
    found = UTILS::COMMAND::Execute(devCommand.c_str());
    istringstream stream{found};
    while (std::getline(stream, line)) {
         vector<string> devices;
        stringSeprator(line, ":", devices);
        if(devices.at(0) != "lo"){
            string netParamCommand ="nmcli --terse device show "+devices.at(0);
            string res = UTILS::COMMAND::Execute(netParamCommand.c_str());
            NetworkParam netParam;
            netParam = deviceParamsParser(res, devices.at(0));
            GLOG_INF("Device information parsed succsessfully");
            netParList.push_back(netParam);
        }
    }
    return netParList;
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

void SystemStats::stringSeprator(std::string source,std::string seprator,vector<string> &resultList){
    size_t pos = 0;
    string token;
    while ((pos = source.find(seprator)) != std::string::npos) {
        token = source.substr(0, pos);
        resultList.push_back(token);
        source.erase(0, pos + seprator.length());
    }
    resultList.push_back(source);
}

NetworkParam SystemStats::deviceParamsParser(std::string data, std::string device){
    NetworkParam networkParam;
    NetworkAddress IP4;
    NetworkAddress IP6;
    size_t pos = 0;
    string line;
    istringstream stream{data};
    while (std::getline(stream, line)) {
        vector<string> params;
        stringSeprator(line,":",params);
        if(params.at(0).find("TYPE")!= string::npos){
            if(params.at(1)== "wifi")
                networkParam.setType(NetworkInterfaceType::WLAN);
            else if (params.at(1)== "ethernet") 
                 networkParam.setType(NetworkInterfaceType::LAN);  
            else if(params.at(1)== "tun")
                networkParam.setType(NetworkInterfaceType::OPENVPN);
            else
                networkParam.setType(NetworkInterfaceType::OTHER);

        }else if(params.at(0).find("HWADDR")!= string::npos){
            std::string macCommand = "nmcli --terse device show "+device+" | grep HWADDR | cut -f 2,3,4,5,6,7 -d \":\"";
            string mac = UTILS::COMMAND::Execute(macCommand.c_str());
            mac.erase(std::remove(mac.begin(), mac.end(), '\n'), mac.end());
            networkParam.setMac(mac);
        }else if(params.at(0).find("STATE")!= string::npos){
            if ((params.at(1).find("100"))!= string::npos) {
                networkParam.setActive(true);
                networkParam.connectionStatus = 100;
            }
            else{
                networkParam.setActive(false);
                networkParam.connectionStatus = 200;
            }
        }else if(params.at(0).find("CONNECTION")!= string::npos){
                networkParam.setName(params.at(1));
        }else if(params.at(0).find("IP4.ADDRESS[1]")!= string::npos){
            IP4.ip = params.at(1);
        }else if(params.at(0).find("IP4.GATEWAY")!= string::npos){
            IP4.gateway = params.at(1);
        }else if(params.at(0).find("IP4.DNS")!= string::npos){
            IP4.dns.push_back(params.at(1));
        }else if(params.at(0).find("IP4.DNS")!= string::npos){
            IP4.dns.push_back(params.at(1));
        }                        

    }
    string cmd = "curl https://my-ip.pantherx.org/";
    IP4.extIp = UTILS::COMMAND::Execute(cmd.c_str());
    IP4.extIp.erase(std::remove(IP4.extIp.begin(), IP4.extIp.end(), '\n'), IP4.extIp.end());
    networkParam.setIP4(IP4);
    string addCmd = "nmcli --terse device show "+device+" | grep \"IP6.ADDRESS\\[1\\]\"  | cut -f 2,3,4,5,6,7 -d \":\"";
    IP6.ip = UTILS::COMMAND::Execute(addCmd.c_str());
    IP6.ip.erase(std::remove(IP6.ip.begin(), IP6.ip.end(), '\n'), IP6.ip.end());
    addCmd = "nmcli --terse device show "+device+" | grep IP6.GATEWAY | cut -f 2,3,4,5,6,7,8 -d \":\"";
    IP6.gateway = UTILS::COMMAND::Execute(addCmd.c_str());
    IP6.gateway.erase(std::remove(IP6.gateway.begin(), IP6.gateway.end(), '\n'), IP6.gateway.end());
    addCmd = "nmcli --terse device show "+device+" | grep IP6.DNS | cut -f 2,3,4,5,6,7 -d \":\"";
    string dns = UTILS::COMMAND::Execute(addCmd.c_str());
    if(!dns.empty()){        
        istringstream st{dns};
        string li;
        while (std::getline(st, li)) {
            li.erase(std::remove(li.begin(), li.end(), '\n'), li.end());
            IP6.dns.push_back(li);
        }
    }
    IP6.extIp = IP4.extIp;
    networkParam.setIP6(IP6);
    return networkParam;
}