//
// Created by Reza Alizadeh Majd on 11/5/18.
//

#ifndef PX_HUB_SERVICE_RPCHANDLER_H
#define PX_HUB_SERVICE_RPCHANDLER_H

#include <StatEvent.capnp.h>
#include <kj/async.h>
#include <string>
#include <kj/debug.h>
#include <iostream>
#include "EventObject.h"
#include "EventDatabase.h"
#include "EventHandler.h"
#include "Logger.h"

class RPCHandler final: public Event::Server {

public:
    kj::Promise<void> emit(EmitContext ctx) override;
protected:
private:


};


#endif //PX_HUB_SERVICE_RPCHANDLER_H
