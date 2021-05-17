//
// Created by Fakhri on 5/12/21.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_NETWORKADDRESS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_NETWORKADDRESS_H
#include <string>
#include <vector>
#include "Logger.h"


class NetworkAddress {
public:
  string        ip;
  string        extIp;
  string        gateway;
  std::vector<string> dns;
};





#endif //PX_ORG_REMOTE_STATUS_SERVICE_NETWORKADDRESS_H