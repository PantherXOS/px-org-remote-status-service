//
// Created by Fakhri on 4/22/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_CPUPARAMS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_CPUPARAMS_H
using namespace std;

#include <string>

class CpuParams {
public:
    void setNumber(int  number);
    void setFrequency(string frequency);
    void setmodel(string model);

    int getNumber();
    string getFrequency();
    string getmodel();

    string toString();

private:
    int number;
    string frequency,model;

};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_CPUPARAMS_H
