//
// Created by Fakhri on 4/23/19.
//

#include "StatusDatabase.h"
#include "JsonBuilder.h"

int main(){
    StatsParam allStats,allresult;

    // Test insert/read General
    allStats.generalParams.setSystem("Fakhri");
    allStats.generalParams.setVersion("01.03");
    allStats.generalParams.setUpTime(13215);
    allStats.generalParams.setBootTime(32135);



    //Test insert/read CPU
    allStats.cpuParams.setSystem(0.10);
    allStats.cpuParams.setUser(5.5);
    allStats.cpuParams.setWait(100);



    //Test insert/read memory
    allStats.memoryParams.setUsage(45);
    allStats.memoryParams.setUsed(55.9);

    //Test insert/read swap
    allStats.swapParams.setUsage(555);
    allStats.swapParams.setUsed(88.9);

    //Test insert/read disk
    DiskParams dp;
    dp.setUsed(80);
    dp.setUsage(30.59);
    dp.setTotal(100);
    dp.setFree(20);
    dp.setName("sda1");
    allStats.diskParams.push_back(dp);


StatusDatabase::instance().insertAllStats(allStats);
StatusDatabase::instance().readAllStats(allresult);


    cout<<"---------------- Swap table r/w test ----------------"<<endl;
    cout<<allresult.swapParams.toString()<<endl;
    cout<<"---------------- Memory table r/w test ----------------"<<endl;
    cout<<allresult.memoryParams.toString()<<endl;
    cout<<"---------------- CPU table r/w test ----------------"<<endl;
    cout<<allresult.cpuParams.toString()<<endl;
    cout<<"---------------- General table r/w test ----------------"<<endl;
    cout<<allresult.generalParams.toString()<<endl;
    cout<<"---------------- Disk table r/w test ----------------"<<endl;
   for(DiskParams d : allresult.diskParams){
    cout<<d.toString()<<endl;
   }
}