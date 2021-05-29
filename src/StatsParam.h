//
// Created by Fakhri on 4/21/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_STATSPARAM_H
#define PX_ORG_REMOTE_STATUS_SERVICE_STATSPARAM_H
using namespace std;

#include <string>
#include <vector>
#include "CpuParams.h"
#include "MemoryParams.h"
#include "DiskParams.h"
#include "GeneralParams.h"
#include "NetworkParam.h"


class StatsParam {
public:
 CpuParams cpuParams;
 CpuParams loadAverage;
 MemoryParams memoryParams,swapParams;
 vector<DiskParams> diskParams;
 GeneralParams generalParams;
 vector<NetworkParam> networkParamList;
 string toString(){ 
     string networkRes ;
     for(auto net : networkParamList ){
         networkRes += net.toString() + " ";
     }
     return cpuParams.toString()+
            loadAverage.toString()+
            memoryParams.toString()+
            swapParams.toString()+
            generalParams.toString();
 };
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_STATSPARAM_H
