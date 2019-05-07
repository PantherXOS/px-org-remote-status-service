//
// Created by Fakhri on 5/6/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_EVENTDATABASE_H
#define PX_ORG_REMOTE_STATUS_SERVICE_EVENTDATABASE_H

#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>
#include <SQLiteCpp/VariadicBind.h>
#include <string>
#include <zconf.h>
#include <pwd.h>
#include <iostream>
#include <vector>
#include <sys/stat.h>
#include "EventObject.h"


#define MAX_TABLE_RECORD 500


using namespace std;
using namespace SQLite;

class EventDatabase  {

#define EVENT_DB_NAME "event.db"
#define DB_PATH "/.userdata/status/"

public:

    static EventDatabase & instance(void);

    bool readEvent(EventObject &eventObject);
    bool readEvents(vector<EventObject> &eventObjects);
    int insertEvent(EventObject eventObject);
    bool deleteEvent(int id);
    bool deleteLastEvent();
    bool deleteEvents();
    bool isDbBusy();
    void setDbFree();
    void setDbBusy();

private:
    EventDatabase() :
            mDb(string(getpwuid(getuid())->pw_dir) + DB_PATH+EVENT_DB_NAME,SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE)
    {
        try {
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS event (id INTEGER PRIMARY KEY,event TEXT,topic TEXT,time INTEGER");
            mDb.exec(
                    "CREATE TABLE IF NOT EXISTS event_param (id INTEGER PRIMARY KEY,key TEXT,value TEXT, eid INTEGER)");
            }
        catch (std::exception& e)
        {
            std::cout << "Err:   SQLite exception: " << e.what() << std::endl;
        }

    }

    bool readParams(map<string,string> &params,int eid);
    int insertParams(map<string,string> params, int eid);
    bool deleteParams(int eid);
    bool dbBusy;
    SQLite::Database    mDb;    ///< Database connection
};



#endif //PX_ORG_REMOTE_STATUS_SERVICE_EVENTDATABASE_H
