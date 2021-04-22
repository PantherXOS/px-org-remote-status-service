//
// Created by Fakhri on 5/7/19.
//

#include "EventHandler.h"
#include <IdPClient.h>

EventHandler &EventHandler::instance(void) {
    static EventHandler instance;
    return instance;
}

void EventHandler::run() {

    thread = std::thread([&]() {
        StatsParam statsParam,result;
        JsonBuilder jsonBuilder;
        DeviceConfig deviceConfig;
        this->threadMode = 1;
        while(this->threadMode){
//            if(isEventReceived()){
                vector<EventObject> eventObjects;
                if(!EventDatabase::instance().isDbBusy()) {
                    eventReceived = false;
                    EventDatabase::instance().readEvents(eventObjects);
                    if(eventObjects.size()) {
                        string js = jsonBuilder.event(eventObjects).GetString();
                        if (IdPClient::Instance().submitEvent(js)) {
                            for (EventObject ev : eventObjects) {
                                EventDatabase::instance().deleteEvent(ev.getId());
                            }
                            cout << "Event Data sent successfully" << endl;
                        } else {
                            cout << "Sent Failed : Not implemented yet" << endl;
                        }
                    }
                }
//            }
            sleep(1);
        };
    });

}

void EventHandler::stop() {
    this->threadMode=0;
}

bool EventHandler::isEventReceived() {
    return this->eventReceived;
}

void EventHandler::setEventReveived() {
    this->eventReceived=true;
}
