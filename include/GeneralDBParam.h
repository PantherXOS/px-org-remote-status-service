//
// Created by root on 4/22/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_GENERALDBPARAM_H
#define PX_ORG_REMOTE_STATUS_SERVICE_GENERALDBPARAM_H
using namespace std;

#include <string>

class GeneralDBParam {
public:
    void setSystem(string system);
    void setVersion(string verion);
    void setUpTime(int upTime);
    void setBootTime(int bootTime);

    string getSystem();
    string getVersion();

    int getUptime();
    int getootTime();


private:
    string system,version;
    int upTime,bootTime;
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_GENERALDBPARAM_H
