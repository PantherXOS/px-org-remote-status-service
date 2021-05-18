//
// Created by Fakhri on 5/6/19.
//

#include "EventDatabase.h"

EventDatabase &EventDatabase::instance(void) {
    string path = (string(getpwuid(getuid())->pw_dir) + USER_DATA);
    mkdir(path.c_str(),0755);
    path += SHARE;
    mkdir(path.c_str(),0755);
    path += STATUS_DATA;
    mkdir(path.c_str(),0755);
    static EventDatabase instance;
    return instance;
}

bool EventDatabase::readEvent(EventObject &eventObject) {
    bool hasResult = false;
    int id;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM event ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            hasResult = true;
            eventObject.setTime(query.getColumn("time").getInt());
            eventObject.setEvent(query.getColumn("event").getString());
            eventObject.setTopic(query.getColumn("topic").getString());
            id = query.getColumn(0).getInt();
        }
        // Reset the query to use it again
        query.reset();
        map<string,string> param;
        this->readParams(param,id);
        eventObject.setParam(param);

    }
    catch(std::exception& e)
    {
        GLOG_ERR("Err:   SQLite exception: " + string(e.what()));
    }
    return hasResult;
}

int EventDatabase::insertEvent(EventObject eventObject) {
    this->setDbBusy();
    try {
        int res = this->mDb.exec("INSERT INTO event VALUES (NULL,\""+
                                         eventObject.getEvent() + "\",\""+
                                         eventObject.getTopic() + "\",\""+
                                 to_string(eventObject.getTime()) + "\")");
        if(res == 0) {
            this->setDbFree();
            return -2;
        }
        SQLite::Statement query(mDb, "SELECT id FROM event ORDER BY id DESC  LIMIT 1");
        while (query.executeStep()) {
            int id = query.getColumn(0).getInt();
            this->insertParams(eventObject.getParam(),id);
        }
        query.reset();
    }
    catch(std::exception& e)
    {
        GLOG_ERR("Err:   SQLite exception: " + string(e.what()));
        this->setDbFree();
        return -1;
    }
    this->setDbFree();
    return 0;
}

bool EventDatabase::deleteEvent(int id) {
    EventDatabase::instance().setDbBusy();
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, "DELETE FROM event WHERE id="+to_string(id));
        deleteParams(id);
        query.reset();

    }
    catch(std::exception& e)
    {
        GLOG_ERR("Err:   SQLite exception: " + string(e.what()));
    }
    EventDatabase::instance().setDbFree();
    return false;
}

bool EventDatabase::readParams(map<string, string> &params,int eid) {
    bool hasResult = false;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM event_param WHERE eid="+to_string(eid));
        while (query.executeStep()) {
            params.insert(pair<string,string> (query.getColumn("key").getString(),query.getColumn("value").getString()));
        }
        query.reset();
    }
    catch(std::exception& e)
    {
        GLOG_ERR("Err:   SQLite exception: " + string(e.what()));
    }
    return hasResult;
}

int EventDatabase::insertParams(map<string, string> params, int eid) {
    try {
        map<string,string>::iterator itr;
        for(itr=params.begin();itr!=params.end();++itr){
            int res = this->mDb.exec("INSERT INTO event_param VALUES (NULL,"+
                                     itr->first+","+
                                     itr->second + ","+
                                     to_string(eid) + ")");
            if(res == 0)
                return -2;
            SQLite::Statement query(mDb, "SELECT id FROM event_param ORDER BY id DESC  LIMIT 1");
            while (query.executeStep()) {
                int id = query.getColumn(0).getInt()- MAX_TABLE_RECORD;
                if(id>0)
                    this->mDb.exec("DELETE FROM event_param WHERE id="+to_string(id));
            }
            query.reset();
        }

    }
    catch(std::exception& e)
    {
        GLOG_ERR("Err:   SQLite exception: " + string(e.what()));
        return -1;
    }
    return 0;
}

bool EventDatabase::deleteParams(int eid) {
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " DELETE * FROM event_param WHERE eid="+to_string(eid));
        query.reset();
    }
    catch(std::exception& e)
    {
        GLOG_ERR("Err:   SQLite exception: " + string(e.what()));
    }
	return true;
}

bool EventDatabase::deleteLastEvent() {
    return false;
}

bool EventDatabase::deleteEvents() {
    this->setDbBusy();
    // TODO
    this->setDbFree();
    return false;
}

bool EventDatabase::readEvents(vector<EventObject> &eventObjects) {
    this->setDbBusy();
    EventObject eventObject;
    bool hasResult = false;
    int id;
    try {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query(mDb, " SELECT * FROM event ORDER BY id");
        while (query.executeStep()) {
            map<string,string> param;
            hasResult = true;
            eventObject.setTime(query.getColumn("time").getInt());
            eventObject.setEvent(query.getColumn("event").getString());
            eventObject.setTopic(query.getColumn("topic").getString());
            eventObject.setId(query.getColumn(0).getInt());
            this->readParams(param, eventObject.getId());
            eventObject.setParam(param);
            eventObjects.push_back(eventObject);
        }
        // Reset the query to use it again
        query.reset();
    }
    catch(std::exception& e)
    {
        GLOG_ERR("Err:   SQLite exception: " + string(e.what()));
    }
    this->setDbFree();
    return hasResult;
}

bool EventDatabase::isDbBusy() {
    return this->dbBusy;
}

void EventDatabase::setDbBusy() {
    this->dbBusy=true;
}

void EventDatabase::setDbFree() {
    this->dbBusy=false;
}
