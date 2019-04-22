//
// Created by root on 4/22/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_MEMORYDBPARAM_H
#define PX_ORG_REMOTE_STATUS_SERVICE_MEMORYDBPARAM_H


class MemoryDBParam {
public:
    void setUsed(float used);
    void setUsage(float usage);

    float getUsed();
    float getUsage();

private:
    float used,usage;
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_MEMORYDBPARAM_H
