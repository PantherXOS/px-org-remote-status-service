//
// Created by Fakhri Sajadi on 01/3/18.
//

#include <RPCHandler.h>

using namespace std;


kj::Promise<void> RPCHandler::emit(Event::Server::EmitContext ctx) {
    KJ_REQUIRE(ctx.getParams().hasEventData(), "Event Data structure not set");
    EventObject eventObject;
    auto eventData = ctx.getParams().getEventData();
    eventObject.setTopic(eventData.getTopic());
    eventObject.setEvent(eventData.getEvent());
    eventObject.setTime(eventData.getTime());
    //TODO add params
    GLOG_INF("Event: eventObject.toString()");
    if(!EventDatabase::instance().isDbBusy()) {
        EventDatabase::instance().insertEvent(eventObject);
        EventHandler::instance().setEventReveived();
    }
    return kj::READY_NOW;
}


