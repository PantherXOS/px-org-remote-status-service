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
    this->type = type;
}

NetworkInterfaceType  NetworkParam::getType(){
    return this->type;   
}

void    NetworkParam::setIP4(NetworkAddress ip){
    this->ip4 = ip;
}

NetworkAddress  NetworkParam::getIP4(){
        return this->ip4;
}

void    NetworkParam::setIP6(NetworkAddress ip){
    this->ip6 = ip;
}

NetworkAddress  NetworkParam::getIP6(){
    return ip6;
}
    



string NetworkParam::toString(){
    
}
