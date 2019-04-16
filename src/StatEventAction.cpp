#include <iostream>
#include <fstream>
#include <ctime>
#include <capnp/ez-rpc.h>
#include "StatEvent.capnp.h"

#include "CLI11.hpp"


using namespace std;
#define SERVER_ADDRESS "~/.system/rpc/remote-status-service"

class StateEventAction{
public:
    void sendEvent(string topic,string event){
        capnp::EzRpcClient rpcClient(SERVER_ADDRESS);
        auto &waitScope = rpcClient.getWaitScope();
        Event::Client client = rpcClient.getMain<Event>();
        auto emitReq = client.emitRequest();
        auto eventData = emitReq.initEventData();
        eventData.setTopic(topic);
        eventData.setEvent(event);
        eventData.setTime(time(nullptr));
//        TODO add parameter
        emitReq.send().wait(waitScope);
    }
};




int main ( int argc, char **argv){
    CLI::App app{"Remote Status Event Emitter application"};
    string topic,event;
    app.add_option("-t,--topic", topic, "topic of action ex:CPU")->required();
    app.add_option("-e,--event", event, "action ex:overload")->required();
    CLI11_PARSE(app, argc, argv);
    StateEventAction stateEventAction;
    stateEventAction.sendEvent(topic,event);
    return 0;
}