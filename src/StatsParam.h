//
// Created by Fakhri on 4/21/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_STATSPARAM_H
#define PX_ORG_REMOTE_STATUS_SERVICE_STATSPARAM_H
using namespace std;

#include <string>
#include "CpuParams.h"
#include "MemoryParams.h"
#include "DiskParams.h"
#include "GeneralParams.h"
#include <vector>


class StatsParam {
public:
 CpuParams cpuParams;
 MemoryParams memoryParams,swapParams;
 vector<DiskParams> diskParams;
 GeneralParams generalParams;
 string toString(){
     return cpuParams.toString()+
            memoryParams.toString()+
            swapParams.toString()+
            generalParams.toString();
 };
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_STATSPARAM_H
