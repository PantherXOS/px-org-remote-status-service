//
// Created by Fakhri on 4/22/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_DISKPARAMS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_DISKPARAMS_H
using namespace std;
#include <string>

class DiskParams {
public:
    void setType(string type);
    void setModel(string model);
    void setCapacity(float capacity);

    string getType();
    string getModel();
    float getCapacity();

    string toString();

private:
    string type,model;
    float capacity;

};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_DISKPARAMS_H
