//
// Created by Fakhri Sajadi on 4/15/19.
//

#include "DiskStats.h"



//map <string, string> DiskStats::diskStatusParser(string status) {
//    map <string, string> diskStatus;
//    istringstream stream{status};
//    string line,found;
//    while (std::getline(stream, line)) {
//        std::string str = line;
//        std::stringstream tokenizer( str );
//        string n,deviceName;
//        int i = 0;
//        while( tokenizer >> n ) {
//            i++;
//            if (i == 1) {
//                diskStatus.insert(std::pair<string, string>("device", n));
//                deviceName = n;
//            } else if (i == 2) diskStatus.insert(std::pair<string, string>(deviceName + ".total", n));
//            else if (i == 3) diskStatus.insert(std::pair<string, string>(deviceName + ".used", n));
//            else if (i == 4) diskStatus.insert(std::pair<string, string>(deviceName + ".free", n));
//            else if (i == 5) {
//                diskStatus.insert(std::pair<string, string>(deviceName + ".usage", n));
//                i = 0;
//            }
//        }
//    }
//    return diskStatus;
//}


//StatsParam DiskStats::get() {
//    string result = UTILS::COMMAND::Execute("df -h |grep ^/dev/sd");
//    return diskStatusParser(result);
//}

