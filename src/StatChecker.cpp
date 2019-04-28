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
            sleep(10);
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
    // TODO
    return "http://localhost:8080";
}

string StatChecker::getUUID() {
    // TODO yaml
    return "4357ca36-68cf-11e9-a923-1681be663d3e";
}

string StatChecker::getToken() {
    // TODO yaml
    return "eyJpc3MiOiJ0b3B0YWwuY29tIiwiZXhwIjoxNDI2NDIwODAwLCJodHRwOi8vdG9wdGFsLmNvbS9qd3RfY2xhaW1zL2lzX2FkbWluIjp0cnVlLCJjb21wYW55IjoiVG9wdGFsIiwiYXdlc29tZSI6dHJ1ZX0";
}

void StatChecker::stop() {
    this->threadMode=0;
}

