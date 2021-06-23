//
// Created by Fakhri on 6/23/21.
//

#include "InstalledApplication.h"

void InstalledApplication::setName(string name){
    this->name = name;
}

void InstalledApplication::setVersion(string version){
    this->version = version;
}

void InstalledApplication::setStoreLocation(string storeLocation){
    this->storeLocation = storeLocation;
}


string InstalledApplication::getName(){
    return name;
}

string InstalledApplication::getVersion(){
    return version;
}

string InstalledApplication::getStoreLocation(){
    return storeLocation;
}