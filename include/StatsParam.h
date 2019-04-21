//
// Created by Fakhri on 4/21/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_STATSPARAM_H
#define PX_ORG_REMOTE_STATUS_SERVICE_STATSPARAM_H
using namespace std;

#include <string>


class StatsParam {
public:
    // Setters
    void setCpuUser(float cpuUser);
    void setCpuWait(float cpuWait);
    void setCpuSystem(float cpuSystem);
    void setMemoryUsage(float memoryUsage);
    void setMemoryUsed(float memoryUsed);
    void setBootTime(int time);
    void setUptime(int time);
    void setSystem(string system);

    void setStatsParam(string system, float cpuUser,float cpuWait,float cpuSystem,float memoryUsage,float memoryUsed, int upTime,int bootTime);


private:
    string system;
    int bootTime,upTime;
    float cpuUser,cpuWait,cpuSystem,memoryUsage,memoryUsed;


};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_STATSPARAM_H
