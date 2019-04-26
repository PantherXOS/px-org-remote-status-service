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
#include "RESTclient.h"


using namespace std;

int main(){
   RPCServer rpcServer;
   rpcServer.start();
    StatsParam statsParam,result;
    SystemStats sysStat;
    JsonBuilder jsonBuilder;

   while(true){
       sleep(3);
      statsParam = sysStat.get();
       StatusDatabase::instance().insertAllStats(statsParam);
       cout<<statsParam.toString()<<endl;
       sleep(3);
       StatusDatabase::instance().readAllStats(result);
       string js =jsonBuilder.allStatus(result).GetString();
       cout<<js<<endl;
       RESTclient resTclient;
       resTclient.send("http:///localhost:8080//device-stats//",js);

   };


}