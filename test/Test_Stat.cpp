//
// Created by Fakhri Sajajdi on 4/14/19.
//
#include <iostream>
#include <sstream>
#include <SystemStats.h>

using namespace std;

int main(){
    SystemStats sysStat;
    map<string,string> sysStatResult =  sysStat.get();
    for ( const auto &p : sysStatResult )
    {
        std::cout << p.first << '\t' << p.second << std::endl;
    }
}