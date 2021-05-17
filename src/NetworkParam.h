//
// Created by Fakhri on 5/12/21.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_NETWORKRAMS_H
#define PX_ORG_REMOTE_STATUS_SERVICE_NETWORKRAMS_H
#include <string>
#include "Logger.h"
#include "NetworkAddress.h"

enum NetworkInterfaceType {
  OTHER = 'other',
  WLAN = 'wlan',
  LAN = 'lan',
  OPENVPN = 'openvpn',
  WIREGUARD = 'wireguard',
  PPTP = 'pptp',
  TOR = 'tor',
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
    NetworkInterfaceType  getType();

    void    setIP4(NetworkAddress type);
    NetworkAddress  getIP4();

    void    setIP6(NetworkAddress type);
    NetworkAddress  getIP6();
    



    string toString();

private:
    string name,mac;
    bool active;
    NetworkInterfaceType type;
    NetworkAddress  ip4;
    NetworkAddress  ip6;
};





#endif //PX_ORG_REMOTE_STATUS_SERVICE_NETWORKRAMS_H