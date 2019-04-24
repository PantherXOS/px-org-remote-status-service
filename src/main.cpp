//
// Created by fakhri on 4/14/19.
//
#include <iostream>
#include <array>
#include <bits/unique_ptr.h>
#include <sstream>
#include <StatusDatabase.h>
#include "SystemStats.h"
#include "DiskStats.h"
#include "RPCServer.h"
#include "StatsParam.h"
#include "JsonBuilder.h"

using namespace std;

int main(){
   RPCServer rpcServer;
   rpcServer.start();
    StatsParam statsParam;
    SystemStats sysStat;

   while(true){
      statsParam = sysStat.get();
       StatusDatabase::instance().insertGeneralStats(statsParam.generalParams);
      sleep(50);
   };


}