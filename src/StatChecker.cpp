//
// Created by Fakhri on 4/27/19.
//

#include "StatChecker.h"


void StatChecker::run() {

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
            int result = resTclient.send(getRestApiPath()+"/devices/" + getUUID() + "/stats",
                                         getToken(), js);

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
    return deviceConfig.getManagerIP();
}
string StatChecker::getUUID() {
    return deviceConfig.getUUID();
}

string StatChecker::getToken() {
    return deviceConfig.getToken();
}

void StatChecker::stop() {
    this->threadMode=0;
}

