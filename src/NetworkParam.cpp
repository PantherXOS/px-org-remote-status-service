//
// Created by Fakhri on 5/12/21.
//

#include "NetworkParam.h"

void    NetworkParam::setName(string name){
   this->name = name;

}
string  NetworkParam::getName(){
    return this->name;
}

void    NetworkParam::setMac(string mac){
    this->mac = mac;
}

string  NetworkParam::getMac(){
        return this->mac;
}

void    NetworkParam::setActive(bool active){
    this->active = active;
}

bool    NetworkParam::isActive(){
 return this->active;
}

void    NetworkParam::setType(NetworkInterfaceType type){
    this->type = networkTypeConvertor(type);
}

void    NetworkParam::setDbType(string type){
    this->type = type;
}

string  NetworkParam::getType(){
    return this->type;   
}

void    NetworkParam::setIP4(NetworkAddress ip){
    this->ip4 = ip;
}

NetworkAddress  NetworkParam::getIP4(){
        return this->ip4;
}

string  NetworkParam::getDbDns(vector<string> inputDns){
    string dns;
    //NetworkAddress ipv4 = inputDns;
    for(int i=0;i<inputDns.size();i++){
        if(i!=(inputDns.size()-1))
            dns += inputDns.at(i)+",";
        else
            dns += inputDns.at(i);
    } 
    GLOG_INF("XXXXXXXXXXXXXXXXXXX dns"+dns); 
    return dns; 
}

void    NetworkParam::setIP6(NetworkAddress ip){
    this->ip6 = ip;
}

NetworkAddress  NetworkParam::getIP6(){
    return ip6;
}
    
string NetworkParam::networkTypeConvertor(NetworkInterfaceType netType){
    string result;
    switch ( netType )
      {
       case NetworkInterfaceType::LAN :
            result = "lan";
            break;
        case NetworkInterfaceType::WLAN :
            result = "wlan";
            break;
        case NetworkInterfaceType::OPENVPN :
            result = "openvpn";
            break;
        case NetworkInterfaceType::WIREGUARD :
            result = "wireguard";
            break;
        case NetworkInterfaceType::PPTP :
            result = "pptp";
            break;
        case NetworkInterfaceType::TOR :
            result = "tor";
            break;
        default:
            result = "other";
      } 
      return result;
}


string NetworkParam::toString(){
    string s =  this->getName() + " ,"+
                this->getType() + " ,"+
                this->getMac() + " ,"+
                this->getIP4().ip + " ,"+
                this->getIP4().extIp + " ,"+
                this->getIP4().gateway+" '"+
                this->getIP6().ip + " ,"+
                this->getIP6().extIp + " ,"+
                this->getIP6().gateway+" '";
    return s;    
}
