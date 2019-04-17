//
// Created by Fakhri Sajadi on 01/3/18.
//

#include <RPCHandler.h>

using namespace std;


kj::Promise<void> RPCHandler::emit(Event::Server::EmitContext ctx) {
    KJ_REQUIRE(ctx.getParams().hasEventData(), "Event Data structure not set");
    auto eventData = ctx.getParams().getEventData();
    auto topic = eventData.getTopic();
    auto event = eventData.getEvent();
    auto time  = eventData.getTime();
    cout << topic.cStr() << endl;
    cout << event.cStr() << endl;

    return kj::READY_NOW;
}


