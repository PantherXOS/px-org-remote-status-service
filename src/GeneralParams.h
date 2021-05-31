//
// Created by Fakhri on 4/22/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_GENERALPARAMS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_GENERALPARAMS_H
using namespace std;

#include <string>

class GeneralParams {
public:
    void setSystem(string system);
    void setVersion(string version);
    void setUpTime(int upTime);
    void setBootTime(int bootTime);
    void setcpuUsed(float used);    
    void setcpuUsage(float usage);


    string getSystem();
    string getVersion();

    int getUpTime();
    int getBootTime();

    float getcpuUsed();
    float getcpuUsage();


    string toString ();

private:
    string system,version;
    int upTime,bootTime;
    float cpuUsed,cpuUsage;
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_GENERALPARAMS_H
