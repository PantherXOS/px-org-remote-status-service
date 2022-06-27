//
// Created by Fakhri on 6/23/21.
//

#include "InstalledApplication.h"
#include "Utils.h"

void InstalledApplication::setName(string name){
    auto trimmed_name = UTILS::STRING::trim(name);
    this->name = trimmed_name;
}

void InstalledApplication::setVersion(string version){
    auto trimmed_version = UTILS::STRING::trim(version);
    this->version = trimmed_version;
}

void InstalledApplication::setStoreLocation(string storeLocation){
    auto trimmed_location = UTILS::STRING::trim(storeLocation);
    this->storeLocation = trimmed_location;
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