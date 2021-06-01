//
// Created by Fakhri on 4/22/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_MEMORYPARAMS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_MEMORYPARAMS_H
using namespace std;

#include <string>

class MemoryParams {
public:
    void setUsed(float used);
    void setUsage(float usage);
    void setTotal(float total);

    float getUsed();
    float getUsage();
    float getTotal();

    string toString();

private:
    float used,usage;
    float total;
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_MEMORYPARAMS_H
