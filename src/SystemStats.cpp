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
        if (key == "System")
            statParam.generalParams.setSystem(monitStatusGetValue(status, key));
        else if (key == "version"){
            try
            {               
                //statParam.generalParams.setVersion("NOT Exist/ TODO");
                string versionCommand = "guix --version |grep guix | cut -f 4 -d \" \"";
                string version =UTILS::COMMAND::Execute(versionCommand.c_str());
                if(!version.empty()){
                    version.erase(std::remove(version.begin(), version.end(), '\n'), version.end());
                    statParam.generalParams.setVersion(version);
                }
            }
            catch(const std::exception& e)
            {      
                std::cerr << e.what() << '\n';         
                GLOG_ERR("Could not retrieve system version.");
            }            
        }
        else if (key == "uptime")
            statParam.generalParams.setUpTime(atoi(monitStatusGetValue(status, key).c_str()));
        else if (key == "boot time")
            statParam.generalParams.setBootTime(UTILS::DATETIME::ConvertToTimeStamp(monitStatusGetValue(status, key)));
        else if (key == "memory usage") {
            try
            {
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
                            statParam.memoryParams.setUsed(atof(amount.c_str()) * 1073741824);
                        else if (token == "MB")
                            statParam.memoryParams.setUsed((atof(amount.c_str())) * 1048576);
                        else if (token == "KB")
                            statParam.memoryParams.setUsed((atof(amount.c_str())) * 1024);
                        else 
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
                if(!memInfo.empty() && !unit.empty()){ 
                    unit.erase(std::remove(unit.begin(), unit.end(), '\n'), unit.end());
                    if (unit == "GB")
                        statParam.memoryParams.setTotal(stof(memInfo) * 1073741824);
                    else if (unit == "MB")
                        statParam.memoryParams.setTotal(stof(memInfo)* 1048576);
                    else if (unit == "kB")
                        statParam.memoryParams.setTotal(stof(memInfo) * 1024);
                    else 
                        statParam.memoryParams.setTotal(stof(memInfo));  
                }   
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                GLOG_ERR("Could not retrieve information about memory.");
            }   
        } else if (key == "swap usage") {
            try
            {                  
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
                        else if (token == "MB")
                            statParam.swapParams.setUsed((atof(amount.c_str())) * 1048576);
                        else if (token == "KB")
                            statParam.swapParams.setUsed((atof(amount.c_str())) * 1024);
                        else 
                            statParam.swapParams.setUsed((atof(amount.c_str())));
                    }
                    ++count;
                    st.erase(0, pos + delimiter.length());
                }
                token = st.substr(1, st.size() - 2);
                statParam.swapParams.setUsage(atof(token.c_str()));
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                GLOG_ERR("Could not get information about swap space.");
            }
         
        } else if (key == "cpu") {
            try
            {
                string cpuNumberCommand = "lscpu |grep \"^CPU(s):\" | tr -d \" \" | cut -f 2 -d \":\"";
                string cpuNumber =UTILS::COMMAND::Execute(cpuNumberCommand.c_str());
                string cpumodelCommand = "cat /proc/cpuinfo |grep \"^model name\" | tr -s \" \" | cut -f 2 -d \":\"";
                string cpumodellist =UTILS::COMMAND::Execute(cpumodelCommand.c_str());
                if(!cpumodellist.empty()){
                    string line;
                    istringstream stream{cpumodellist};
                    int num = 0;
                    while (std::getline(stream, line)) {
                        CpuParams cpuPar;
                        line.erase(std::remove(line.begin(), line.end(), '\n'), line.end());
                        cpuPar.setNumber(num);
                        cpuPar.setmodel(line);
                        statParam.cpuParams.push_back(cpuPar);
                        num++;
                    }
                }
                string cpuFrqCommand = "cat /proc/cpuinfo |grep \"^cpu MHz\" | cut -f 2 -d \":\"";
                string cpuFrqlist =UTILS::COMMAND::Execute(cpuFrqCommand.c_str());
                if(!cpuFrqlist.empty()){
                    string frqline;
                    istringstream str{cpuFrqlist};
                    int num = 0;
                    while (std::getline(str, frqline)) {
                        statParam.cpuParams.at(num).setFrequency(frqline);
                        num++;
                    }  
                }                      
                string cpuInfoCommand = "mpstat | grep -A 5 \"%idle\" | tail -n 1 | awk -F \" \" '{print 100 -  $ 12}'a";
                string cpuInfo =UTILS::COMMAND::Execute(cpuInfoCommand.c_str());                       
                if(!cpuInfo.empty()){
                    auto use = 100-(stof(cpuInfo.c_str()));            
                    statParam.generalParams.setcpuUsage(use);
                    if(!cpuNumber.empty())
                        statParam.generalParams.setcpuUsed(stof(cpuNumber.c_str())*(stof(cpuInfo.c_str())));
                    //version.erase(std::remove(version.begin(), version.end(), '\n'), version.end());
                    //statParam.generalParams.setVersion(version);
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                GLOG_ERR("Could not get information about CPU.");
            }            
            
        } else if (key == "load average") {
            try
            {
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
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                GLOG_ERR("Could not get information about average load.");
            }            
            
        } else if (key == "hdd") {
            try
            {
                string hddUsageCommand = "df --total |grep \"^total\" | tr -s \" \" | cut -f 5 -d \" \" | tr -d \"%\"";
            string _hddUsage =UTILS::COMMAND::Execute(hddUsageCommand.c_str());
            string hddUsedCommand = "df --total |grep \"^total\" | tr -s \" \" | cut -f 2 -d \" \"";
            string _hddUsed =UTILS::COMMAND::Execute(hddUsedCommand.c_str()); 
            if(!_hddUsage.empty())
                statParam.generalParams.setHddUsage(stof(_hddUsage));
            if(!_hddUsed.empty())    
                statParam.generalParams.setHddUsed(stof(_hddUsed)*1024);
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
                GLOG_ERR("Could not get information about HDD.");
            }
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
    diskStatusParser(statsParam.diskParams);
    GLOG_INF("Status successfully read");
    statsParam.networkParamList = networkParamsParser();
    return statsParam;
}

void SystemStats::diskStatusParser( vector<DiskParams> &diskStatus) {
    try
    {
        string modelCommand= "lshw -class disk |grep product: | cut -f 2 -d \":\"";
        string models = UTILS::COMMAND::Execute(modelCommand.c_str()); 
        if(!models.empty()){
            istringstream stream{models};
            string line, found;
            while (std::getline(stream, line)) {
                DiskParams disk;
                disk.setModel(line);
                if(line.find("SSD") != string::npos){
                    disk.setType("ssd");
                }
                else{
                    disk.setType("hdd");
                }
            diskStatus.push_back(disk);
            line.clear();
            }
        }
        string capCommand= "lshw -class disk |grep size: | cut -f 2 -d \":\" | cut -f 3 -d \" \" | cut -f 2 -d \"(\" | cut -f 1 -d \")\"";
        string capacities = UTILS::COMMAND::Execute(capCommand.c_str()); 
        if(!capacities.empty()){
            istringstream stream{capacities};
            string cpline, found;
            int count = 0;
            while (std::getline(stream, cpline)) {
                if(cpline.find("GB")!= string::npos)
                {
                    string s = cpline.erase (cpline.length(),(cpline.length()-2));
                    float f = stof(s)*1073741824;
                    diskStatus.at(count).setCapacity(stof(s)*1073741824);
                }
                else if(cpline.find("MB")!= string::npos)
                {
                    string s = cpline.erase (cpline.length(),(cpline.length()-2));
                    diskStatus.at(count).setCapacity(stof(s)*1048576);
                }
                else if(cpline.find("kB")!= string::npos)
                {
                    string s = cpline.erase (cpline.length(),(cpline.length()-2));
                    diskStatus.at(count).setCapacity(stof(s)*1024);
                }
                else                
                    diskStatus.at(count).setCapacity(stof(cpline.erase (cpline.length(),(cpline.length()-2))));
                count++;
            }
        }     
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
        GLOG_ERR("Could not get information about disks.");
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
    GLOG_INF("Monit started successfully: " + result );
    return true;
}

vector<NetworkParam> SystemStats::networkParamsParser( ){
    vector<NetworkParam> netParList;
    // if(!system("nmcli")){
    //     GLOG_INF("Network Manager Found");
    //     networkParamsNmcliParser(netParList);
    // }else{
     //   GLOG_INF("Network Manager Not Found");
        networkParamsFalbackParser(netParList);
    //}   
    
    return netParList;
}

void SystemStats::networkParamsFalbackParser(vector<NetworkParam> &result){
    QNetworkInterface qn;
    string IP4Gateway,IP6Gateway;
    auto interface_list = qn.allInterfaces();
    string devCommand = "ip -4 route show | cut -f 3 -d \" \"";  
    string line, found;
    found = UTILS::COMMAND::Execute(devCommand.c_str());
            if(!found.empty())
            {
                istringstream stream{found};
                bool find;
                while (std::getline(stream, line)) { 
                    for(auto l :interface_list) {
                        if(l.name().toStdString().find(line) != std::string::npos)
                            find = true;
                    } 
                     if(!find)
                        IP4Gateway = line;
                }               
            }
    string gCommand = "ip -6 route show | cut -f 3 -d \" \"";  
    string line6, found6;
    found6 = UTILS::COMMAND::Execute(gCommand.c_str());
            if(!found6.empty())
            {
                istringstream stream{found6};
                bool find;
                while (std::getline(stream, line6)) { 
                    for(auto l :interface_list) {
                        if(l.name().toStdString().find(line6) != std::string::npos)
                            find = true;
                    } 
                     if(!find)
                        IP6Gateway = line6;
                    find =false;
                }               
            }
    for(auto interface : interface_list){        
        NetworkParam netParam;
        if(interface.humanReadableName().toStdString()!= "lo"){
            netParam.setName(interface.humanReadableName().toStdString());
        //netParam.setType(interface.type().toStdString());
        netParam.setMac(interface.hardwareAddress().toStdString());
        if(interface.flags() & 0x1){

           netParam.setActive(true); 
           netParam.connectionStatus = 100;
        }else{
            netParam.setActive(false); 
           netParam.connectionStatus = 200;
        }
        switch (interface.type())
        {
                case QNetworkInterface::Wifi:
                    netParam.setType(NetworkInterfaceType::WLAN);
                    break;
                case QNetworkInterface::Ethernet:
                    netParam.setType(NetworkInterfaceType::LAN);  
                    break;
                case QNetworkInterface::Virtual:
                    netParam.setType(NetworkInterfaceType::OPENVPN);
                    break;
                default:
                    netParam.setType(NetworkInterfaceType::OTHER);
                    break;
        } 
        NetworkAddress IP4,IP6;
         if(!interface.addressEntries().empty()){
            if(interface.addressEntries().at(0).ip().protocol() == QAbstractSocket::IPv4Protocol)
                IP4.ip = interface.addressEntries().at(0).ip().toString().toStdString();
                if(netParam.isActive()){
                    readDns(IP4.dns);
                    IP4.gateway = IP4Gateway;
                    IP6.gateway = IP6Gateway;
                }                    
            for(auto i:interface.addressEntries()){
                if (i.ip().protocol() == QAbstractSocket::IPv6Protocol){
                    IP6.ip = i.ip().toString().toStdString();
                    if(netParam.isActive())
                        readDns(IP6.dns);
                }
            }
        }
        string cmd = "curl https://my-ip.pantherx.org/";
        IP4.extIp = UTILS::COMMAND::Execute(cmd.c_str());        
        IP4.extIp.erase(std::remove(IP4.extIp.begin(), IP4.extIp.end(), '\n'), IP4.extIp.end());        
        IP6.extIp = IP4.extIp;
        
        netParam.setIP4(IP4);
        netParam.setIP6(IP6);

        result.push_back(netParam);

        }
    }
}


// void SystemStats::networkParamsNmcliParser(vector<NetworkParam> &result){
// string devCommand = "nmcli -m tabular --terse device";  
// string line, found;
// found = UTILS::COMMAND::Execute(devCommand.c_str());
//     if(!found.empty())
//     {
//           istringstream stream{found};
//         while (std::getline(stream, line)) {            
//             vector<string> devices;
//             stringSeprator(line, ":", devices);
//             if(devices.at(0) != "lo"){
//                 string netParamCommand ="nmcli --terse device show "+devices.at(0);
//                 string res = UTILS::COMMAND::Execute(netParamCommand.c_str());
//                 NetworkParam netParam;
//                 if(!res.empty()){
//                     netParam = deviceParamsParser(res, devices.at(0));
//                     GLOG_INF("Device information parsed succsessfully.");
//                 }else{
//                     GLOG_ERR("nmcli command has no value");
//                 } 
//                 result.push_back(netParam);
//             }
//         }
//     } 
// }

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

// NetworkParam SystemStats::deviceParamsParser(std::string data, std::string device){
//     NetworkParam networkParam;
//     try
//     {            
//         NetworkAddress IP4;
//         NetworkAddress IP6;
//         size_t pos = 0;
//         string line;
//         istringstream stream{data};
//         while (std::getline(stream, line)) {
//             vector<string> params;
//             stringSeprator(line,":",params);
//             if(params.at(0).find("TYPE")!= string::npos){
//                 if(params.at(1)== "wifi")
//                     networkParam.setType(NetworkInterfaceType::WLAN);
//                 else if (params.at(1)== "ethernet") 
//                     networkParam.setType(NetworkInterfaceType::LAN);  
//                 else if(params.at(1)== "tun")
//                     networkParam.setType(NetworkInterfaceType::OPENVPN);
//                 else
//                     networkParam.setType(NetworkInterfaceType::OTHER);

//             }else if(params.at(0).find("HWADDR")!= string::npos){
//                 std::string macCommand = "nmcli --terse device show "+device+" | grep HWADDR | cut -f 2,3,4,5,6,7 -d \":\"";
//                 string mac = UTILS::COMMAND::Execute(macCommand.c_str());
//                 if(!mac.empty()){
//                     mac.erase(std::remove(mac.begin(), mac.end(), '\n'), mac.end());
//                     networkParam.setMac(mac);
//                 }else{
//                     GLOG_WRN("mac parameter has no value");
//                 }
                
//             }else if(params.at(0).find("STATE")!= string::npos){
//                 if ((params.at(1).find("100"))!= string::npos) {
//                     networkParam.setActive(true);
//                     networkParam.connectionStatus = 100;
//                 }
//                 else{
//                     networkParam.setActive(false);
//                     networkParam.connectionStatus = 200;
//                 }
//             }else if(params.at(0).find("CONNECTION")!= string::npos){
//                     networkParam.setName(params.at(1));
//             }else if(params.at(0).find("IP4.ADDRESS[1]")!= string::npos){
//                 IP4.ip = params.at(1);
//             }else if(params.at(0).find("IP4.GATEWAY")!= string::npos){
//                 IP4.gateway = params.at(1);
//             }else if(params.at(0).find("IP4.DNS")!= string::npos){
//                 IP4.dns.push_back(params.at(1));
//             }else if(params.at(0).find("IP4.DNS")!= string::npos){
//                 IP4.dns.push_back(params.at(1));
//             }                      

//         }
//         string cmd = "curl https://my-ip.pantherx.org/";
//         IP4.extIp = UTILS::COMMAND::Execute(cmd.c_str());        
//         IP4.extIp.erase(std::remove(IP4.extIp.begin(), IP4.extIp.end(), '\n'), IP4.extIp.end());
//         networkParam.setIP4(IP4);
//         string addCmd = "nmcli --terse device show "+device+" | grep \"IP6.ADDRESS\\[1\\]\"  | cut -f 2,3,4,5,6,7 -d \":\"";
//         IP6.ip = UTILS::COMMAND::Execute(addCmd.c_str());
//         IP6.ip.erase(std::remove(IP6.ip.begin(), IP6.ip.end(), '\n'), IP6.ip.end());
//         addCmd = "nmcli --terse device show "+device+" | grep IP6.GATEWAY | cut -f 2,3,4,5,6,7,8 -d \":\"";
//         IP6.gateway = UTILS::COMMAND::Execute(addCmd.c_str());
//         IP6.gateway.erase(std::remove(IP6.gateway.begin(), IP6.gateway.end(), '\n'), IP6.gateway.end());
//         addCmd = "nmcli --terse device show "+device+" | grep IP6.DNS | cut -f 2,3,4,5,6,7 -d \":\"";
//         string dns = UTILS::COMMAND::Execute(addCmd.c_str());        
//         if(!dns.empty()){        
//             istringstream st{dns};
//             string li;
//             while (std::getline(st, li)) {
//                 li.erase(std::remove(li.begin(), li.end(), '\n'), li.end());
//                 IP6.dns.push_back(li);
//             }
//         }
//         IP6.extIp = IP4.extIp;
//         networkParam.setIP6(IP6);
//     }
//     catch(const std::exception& e)
//     {
//         std::cerr << e.what() << '\n';
//         GLOG_ERR("Could not retrieve information about network.");
//     }   

//     return networkParam;
// }

vector<InstalledApplication> SystemStats::getApplications(){
   vector<InstalledApplication> applicationList;

    string appCommand = "guix package --list-installed --profile=/run/current-system/profile | tr -s '\t' ','";  
    string line, found;
    found = UTILS::COMMAND::Execute(appCommand.c_str());
    if(!found.empty())
    {
          istringstream stream{found};
        while (std::getline(stream, line)) {            
            vector<string> appInfo;
            InstalledApplication apps;
            stringSeprator(line, ",", appInfo);
            if(!appInfo.empty()){
                apps.setName(appInfo.at(0));
                apps.setVersion(appInfo.at(1));
                apps.setStoreLocation(appInfo.at(3));
                applicationList.push_back(apps);
            }        
        }
    } 
    return applicationList;
}

   #include "resolv.h"
    #include <arpa/inet.h>
void SystemStats::readDns(vector<std::string> & allDns){
    res_init();
    char dns[20];
    auto dnsList =     _res.nsaddr_list;
    for(int i = 0; i < MAXNS; i++){
        inet_ntop(AF_INET, &(_res.nsaddr_list[i].sin_addr), dns, 20);
        allDns.push_back(dns);
    }
}
    