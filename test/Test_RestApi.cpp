#include "RESTserver.h"
#include <pistache/http.h>
#include <pistache/description.h>
#include <pistache/endpoint.h>

#include <pistache/serializer/rapidjson.h>

int main(int argc, char *argv[]) {
    Port port(80);
    Address addr(Ipv4::any(), port);
    RestService restService(addr);
    restService.init(2); // TODO
    restService.start();
    restService.shutdown();
}