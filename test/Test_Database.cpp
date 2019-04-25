//
// Created by Fakhri on 4/23/19.
//

#include "StatusDatabase.h"
#include "JsonBuilder.h"

int main(){

    // Test insert/read General
    GeneralParams generalParams;
    generalParams.setSystem("Fakhri");
    generalParams.setVersion("01.03");
    generalParams.setUpTime(13215);
    generalParams.setBootTime(32135);

    StatusDatabase::instance().insertGeneralStats(generalParams);
    GeneralParams result ;
    StatusDatabase::instance().readGeneralStats(result);
    cout<<"---------------- General table r/w test ----------------"<<endl;
    cout<<result.toString()<<endl;

    //Test insert/read CPU
    CpuParams cpuParams,cpuResult;
    cpuParams.setSystem(0.10);
    cpuParams.setUser(5.5);
    cpuParams.setWait(100);

    StatusDatabase::instance().insertCpuStats(cpuParams, 0);
    StatusDatabase::instance().readCpuStats(cpuResult, 0);
    JsonBuilder jsonBuilder;
    jsonBuilder.cpupart(cpuParams);
    cout<<"---------------- CPU table r/w test ----------------"<<endl;
    cout<<cpuResult.toString()<<endl;

    //Test insert/read memory
    MemoryParams memoryParams,memoryResult;
    memoryParams.setUsage(45);
    memoryParams.setUsed(55.9);
    StatusDatabase::instance().inserMemorytStats(memoryParams, 0);
    StatusDatabase::instance().readMemoryStats(memoryResult, 0);
    cout<<"---------------- Memory table r/w test ----------------"<<endl;
    cout<<memoryParams.toString()<<endl;

    //Test insert/read swap
    MemoryParams swapParams,swapResult;
    swapParams.setUsage(555);
    swapParams.setUsed(88.9);
    StatusDatabase::instance().insertSwaptStats(swapParams, 2);
    StatusDatabase::instance().readSwapStats(swapResult, 2);
    cout<<"---------------- Swap table r/w test ----------------"<<endl;
    cout<<swapResult.toString()<<endl;

    //Test insert/read disk
    DiskParams diskParams,diskResult;
    diskParams.setUsed(80);
    diskParams.setUsage(30.59);
    diskParams.setTotal(100);
    diskParams.setFree(20);
    diskParams.setName("sda1");

    StatusDatabase::instance().insertDiskStats(diskParams, 1);
    StatusDatabase::instance().readDiskStats(diskResult, 1);
    cout<<"---------------- Disk table r/w test ----------------"<<endl;
    cout<<diskResult.toString()<<endl;

}