//
// Created by Fakhri on 5/6/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_EVENTOBJECT_H
#define PX_ORG_REMOTE_STATUS_SERVICE_EVENTOBJECT_H
using namespace std;

#include <string>
#include <map>


class EventObject {
public:
    void setEvent(string event);
    void setTopic(string topic);
    void setTime(int time);
    void setParam(map<string,string> params);

    string getEvent();
    string getTopic();
    int getTime();
    map<string,string> getParam();

    string toString();
private:
string event;
string topic;
int time;
map<string,string> params;

};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_EVENTOBJECT_H
