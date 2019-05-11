//
// Created by root on 5/6/19.
//

#include "EventObject.h"

void EventObject::setEvent(string event) {
    this->event = event;
}

void EventObject::setTopic(string topic) {
    this->topic = topic;
}

void EventObject::setTime(int time) {
    this->time = time;
}

void EventObject::setParam(map <string, string> params) {
    this->params = params;
}

string EventObject::getEvent() {
    return this->event;
}

string EventObject::getTopic() {
    return this->topic;
}

int EventObject::getTime() {
    return this->time;
}

map <string, string> EventObject::getParam() {
    return params;
}

string EventObject::toString() {
    return "Event: { "+event + ", " + topic +", " + to_string(time) + ", "+ "TODO params" + "}";
}

void EventObject::setId(int id) {
    this->id = id;

}

int EventObject::getId() {
    return this->id;
}

