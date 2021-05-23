//
// Created by Fakhri on 5/12/21.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_NETWORKRAMS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_NETWORKRAMS_H
#include <string>
#include "Logger.h"
#include "NetworkAddress.h"

enum NetworkInterfaceType {
  OTHER,
  WLAN,
  LAN,
  OPENVPN,
  WIREGUARD,
  PPTP,
  TOR,
};


class NetworkParam {
public:
    void    setName(string name);
    string  getName();

    void    setMac(string mac);
    string  getMac();

    void    setActive(bool active);
    bool  isActive();
    
    void    setType(NetworkInterfaceType type);
    string  getType();

    void    setIP4(NetworkAddress type);
    NetworkAddress  getIP4();

    void    setIP6(NetworkAddress type);
    NetworkAddress  getIP6();
    
    string networkTypeConvertor(NetworkInterfaceType netType);


    string toString();

private:
    string name;
    string mac;
    bool active;
    string type;
    NetworkAddress  ip4;
    NetworkAddress  ip6;
};





#endif //PX_ORG_REMOTE_STATUS_SERVICE_NETWORKRAMS_H