//
// Created by Fakhri Sajajdi on 4/14/19.
//
#include <iostream>
#include <sstream>
#include "SystemStats.h"
#include "DiskStats.h"
#include "StatsParam.h"

using namespace std;

int main(){
    StatsParam statsParam;
    SystemStats sysStat();
    statsParam = sysStat.get();
    cout<<statsParam.toString()<<endl;
}