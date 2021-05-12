//
// Created by Fakhri on 4/27/19.
//

#include "StatChecker.h"
#include <IdPClient.h>
#include <chrono>


StatChecker::StatChecker(const AppConfig& config) :
        m_appConfig(config) {}

void StatChecker::run() {

    thread = std::thread([&]() {
        StatsParam statsParam, result;
        SystemStats sysStat(m_appConfig);
        sleep(1);
        JsonBuilder jsonBuilder;
        this->threadMode = 1;
        auto lastRun = chrono::time_point<chrono::system_clock>{};
        while (this->threadMode) {
            auto now = chrono::system_clock::now();
            if (chrono::duration_cast<chrono::seconds>(now - lastRun).count() < m_appConfig.interval) {
                std::this_thread::sleep_for(chrono::seconds(1));
                continue;
            }
            lastRun = now;
            auto nowTime = chrono::system_clock::to_time_t(now);
            GLOG_INF("check stat on " + string(std::ctime(&nowTime)));
            statsParam = sysStat.get(m_appConfig);
            StatusDatabase::instance().insertAllStats(statsParam);
            StatusDatabase::instance().readAllStats(result);
            string js = jsonBuilder.allStatus(result).GetString();
            GLOG_INF( "JSON RESULT: "+ js);
            if (IdPClient::Instance().submitStatus(js)) {
                GLOG_INF( "Stat Data sent successfully");
                StatusDatabase::instance().deletLastStat();
            } else {
               GLOG_ERR( "Stat Sent Failed" );
            }
        };
    });
}


void StatChecker::stop() {
    this->threadMode = 0;
}

