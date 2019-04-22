//
// Created by root on 4/22/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_DISKDBPARAM_H
#define PX_ORG_REMOTE_STATUS_SERVICE_DISKDBPARAM_H
using namespace std;
#include <string>

class DiskDBParam {
public:
    void setName(string name);
    void setFree(float free);
    void setTotal(float total);
    void setUsed(float used);
    void setUsage(float usage);

    string getName();
    float getFree();
    float getTotal();
    float getUsed();
    float getUsage();
private:
    string name;
   float free,total,used,usage;

};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_DISKDBPARAM_H
