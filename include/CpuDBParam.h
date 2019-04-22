//
// Created by Fakhri on 4/22/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_CPUDBPARAM_H
#define PX_ORG_REMOTE_STATUS_SERVICE_CPUDBPARAM_H


class CpuDBParam {
public:
    void setUser(float user);
    void setSystem(float system);
    void setWait(float wait);

    float getUser();
    float getSystem();
    float getWait();

private:
    float user,system,wait;

};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_CPUDBPARAM_H
