//
// Created by Fakhri on 4/27/19.
//

#include "StatChecker.h"
#include <IdPClient.h>
#include <chrono>


StatChecker::StatChecker(int checkInterval) :
        m_checkInterval(checkInterval) {}

void StatChecker::run() {

    thread = std::thread([&]() {
        StatsParam statsParam, result;
        SystemStats sysStat;
        sleep(1);
        JsonBuilder jsonBuilder;
        this->threadMode = 1;
        auto lastRun = chrono::time_point<chrono::system_clock>{};
        while (this->threadMode) {
            auto now = chrono::system_clock::now();
            if (chrono::duration_cast<chrono::seconds>(now - lastRun).count() < m_checkInterval) {
                std::this_thread::sleep_for(chrono::seconds(1));
                continue;
            }
            lastRun = now;
            auto nowTime = chrono::system_clock::to_time_t(now);
            cout << ">>> check stat on " << std::ctime(&nowTime) << endl;
            statsParam = sysStat.get();
            StatusDatabase::instance().insertAllStats(statsParam);
            StatusDatabase::instance().readAllStats(result);
            string js = jsonBuilder.allStatus(result).GetString();
            if (IdPClient::Instance().submitStatus(js)) {
                cout << "Stat Data sent successfully" << endl;
                StatusDatabase::instance().deletLastStat();
            } else {
                cout << "Stat Sent Failed" << endl;
            }
        };
    });
}


void StatChecker::stop() {
    this->threadMode = 0;
}

