//
// Created by fakhri on 4/14/19.
//
#include <iostream>
#include <array>
#include <bits/unique_ptr.h>
#include <sstream>
#include <SystemStats.h>
#include "DiskStats.h"

using namespace std;

int main(){
    DiskStats diskStats;
    map<string,string> disktatResult =  diskStats.get();
    for ( const auto &p : disktatResult )
    {
        std::cout << p.first << '\t' << p.second << std::endl;
    }
}