//
// Created by Fakhri on 4/27/19.
//

#include "StatChecker.h"


void StatChecker::run() {
    DeviceConfig deviceConfig;
    thread = std::thread([&]() {
        StatsParam statsParam,result;
        SystemStats sysStat;
        JsonBuilder jsonBuilder;
        this->threadMode = 1;
        while(this->threadMode){
            statsParam = sysStat.get();
            StatusDatabase::instance().insertAllStats(statsParam);
//            cout<<statsParam.toString()<<endl;
            sleep(1);
            StatusDatabase::instance().readAllStats(result);
            string js =jsonBuilder.allStatus(result).GetString();
            cout<<js<<endl;
            RESTclient resTclient;
            int result = resTclient.send(getRestApiPath()+"/devices/" + deviceConfig.getUUID() + "/stats",
                                         deviceConfig.getToken(), js);
            if (result == 200) {
                cout << "Stat Data sent successfully" << endl;
                StatusDatabase::instance().deletLastStat();
            }
            else
                cout << "Sent Failed : Not implemented yet" << endl;
        };
    });
}


string StatChecker::getRestApiPath() {
    // TODO
    return "http://localhost:8080";
}

void StatChecker::stop() {
    this->threadMode=0;
}
