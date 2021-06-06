//
// Created by Fakhri on 5/1/21.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_LOADPARAMS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_LOADPARAMS_H
using namespace std;

#include <string>

class LoadParams {
public:
    void setUser(float user);
    void setSystem(float system);
    void setWait(float wait);

    float getUser();
    float getSystem();
    float getWait();

    string toString();

private:
    float user,system,wait;

};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_LOADPARAMS_H
