//
// Created by Fakhri on 4/27/19.
//

#include "StatChecker.h"
#include <IdPClient.h>

void StatChecker::run() {

    thread = std::thread([&]() {
        StatsParam statsParam,result;
        SystemStats sysStat;
        sleep(1);
        JsonBuilder jsonBuilder;
        this->threadMode = 1;
        while(this->threadMode){
            statsParam = sysStat.get();
            sleep(10);
            StatusDatabase::instance().insertAllStats(statsParam);
            StatusDatabase::instance().readAllStats(result);
            string js =jsonBuilder.allStatus(result).GetString();
            if (IdPClient::Instance().submitStatus(js)) {
                cout << "Stat Data sent successfully" << endl;
                StatusDatabase::instance().deletLastStat();
            }
            else {
                cout << "Sent Failed : Not implemented yet" << endl;
            }
        };
    });
}



void StatChecker::stop() {
    this->threadMode=0;
}

