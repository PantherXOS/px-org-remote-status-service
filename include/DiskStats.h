//
// Created by Fakhri Sajadi on 4/15/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_DISKSTATS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_DISKSTATS_H
using namespace std;

#include "Stats.h"
#include "Utils.h"
#include <iostream>
#include <vector>
#include <sstream>

class DiskStats :  Stats {
public:
    map<string,string> get();
private:
    map<string,string> diskStatusParser(string status);

};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_DISKSTATS_H
