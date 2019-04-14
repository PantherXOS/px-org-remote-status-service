//
// Created by fakhri on 4/14/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_STATS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_STATS_H
using namespace std;

#include <map>

class Stats {
    virtual map<string,string> get() = 0;

};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_STATS_H
