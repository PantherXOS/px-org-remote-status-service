//
// Created by Fakhri Sajadi on 4/20/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_APIHANDLER_H
#define PX_ORG_REMOTE_STATUS_SERVICE_APIHANDLER_H
using namespace Net;

#include "pistache/endpoint.h"

class ApiHandler: public Http::Handler {
public:

HTTP_PROTOTYPE(HelloHandler)

    void onRequest(const Http::Request& request, Http::ResponseWriter response) {
        response.send(Http::Code::Ok, "Hello, World");
    }
};

};


#endif //PX_ORG_REMOTE_STATUS_SERVICE_APIHANDLER_H
