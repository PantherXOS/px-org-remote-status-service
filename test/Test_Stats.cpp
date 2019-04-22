//
// Created by Fakhri Sajajdi on 4/14/19.
//
#include <iostream>
#include <sstream>
#include "SystemStats.h"
#include "DiskStats.h"

using namespace std;

int main(){
    SystemStats sysStat;
    map<string,string> sysStatResult =  sysStat.get();
    for ( const auto &p : sysStatResult )
    {
        std::cout << p.first << '\t' << p.second << std::endl;
    }
    DiskStats diskStats;
    map<string,string> disktatResult =  diskStats.get();
    for ( const auto &p : disktatResult )
    {
        std::cout << p.first << '\t' << p.second << std::endl;
    }
}