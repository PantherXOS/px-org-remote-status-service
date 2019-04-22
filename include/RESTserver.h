//
// Created by root on 4/22/19.
//

#ifndef PX_ORG_REMOTE_STATUS_SERVICE_RESTSERVER_H
#define PX_ORG_REMOTE_STATUS_SERVICE_RESTSERVER_H
#include <pistache/http.h>
#include <pistache/description.h>
#include <pistache/endpoint.h>

#include <pistache/serializer/rapidjson.h>
using namespace std;
using namespace Pistache;

class RestService {
public:
    RestService(Address addr)
            : httpEndpoint(std::make_shared<Http::Endpoint>(addr))
            , desc("STATS REST API", "0.1")
    { }

    void init(size_t thr = 2);
    void start();
    void shutdown();

private:
    void createRestHandler();
    void getAllStats(const Rest::Request &, Http::ResponseWriter response);
    std::shared_ptr<Http::Endpoint> httpEndpoint;
    Rest::Description desc;
    Rest::Router router;
};
#endif //PX_ORG_REMOTE_STATUS_SERVICE_RESTSERVER_H
