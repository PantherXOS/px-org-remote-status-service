//
// Created by fakhri on 4/14/19.
//
#include <iostream>
#include <array>
#include <bits/unique_ptr.h>
#include <sstream>
#include <SystemStats.h>
#include "DiskStats.h"
#include "RPCServer.h"

using namespace std;

int main(){
   RPCServer rpcServer;
   rpcServer.start();
   while(1);


}