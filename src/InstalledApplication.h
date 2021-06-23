//
// Created by Fakhri on 6/23/21.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_INSTALLAPPLICATION_H
#define PX_ORG_REMOTE_STATUS_SERVICE_INSTALLAPPLICATION_H
using namespace std;

#include <string>

class InstalledApplication {
public:
    void setName(string name);
    void setVersion(string version);
    void setStoreLocation(string storeLocation);
    

    string getName();
    string getVersion();
    string getStoreLocation();

private:
    string name,version,storeLocation;
};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_INSTALLAPPLICATION_H
