#include "RESTserver.h"

namespace Generic {
    void handleReady(const Rest::Request&, Http::ResponseWriter response) {
        response.send(Http::Code::Ok, "1");
    }
}

void RestService::init(size_t thr) {
    auto opts = Http::Endpoint::options()
            .threads(thr)
            .flags(Tcp::Options::InstallSignalHandler);
    httpEndpoint->init(opts);
    createRestHandler();
}

void RestService::start() {
    router.initFromDescription(desc);

    Rest::Swagger swagger(desc);
    swagger
            .uiPath("/doc")
            .uiDirectory("/home/octal/code/web/swagger-ui-2.1.4/dist")
            .apiPath("/banker-api.json")
            .serializer(&Rest::Serializer::rapidJson)
            .install(router);

    httpEndpoint->setHandler(router.handler());
    httpEndpoint->serve();
}

void RestService::shutdown() {
    httpEndpoint->shutdown();
}

void RestService::createRestHandler() {
    desc
            .info()
            .license("Apache", "http://www.apache.org/licenses/LICENSE-2.0");

    auto backendErrorResponse =
            desc.response(Http::Code::Internal_Server_Error, "An error occured with the backend");

    desc
            .schemes(Rest::Scheme::Http)
            .basePath("/v1")
            .produces(MIME(Application, Json))
            .consumes(MIME(Application, Json));

    desc
            .route(desc.get("/ready"))
            .bind(&Generic::handleReady)
            .response(Http::Code::Ok, "Response to the /ready call")
            .hide();

    auto versionPath = desc.path("/v1");

    auto statsPath = versionPath.path("/stats");

    statsPath
            .route(desc.get("/all"))
            .bind(&RestService::getAllStats, this)
            .produces(MIME(Application, Json), MIME(Application, Xml))
            .response(Http::Code::Ok, "Total stats information");

}

void RestService::getAllStats(const Rest::Request &, Http::ResponseWriter response) {
    response.headers().add<Http::Header::ContentType>(MIME(Application, Json));
    response.send(Http::Code::Ok, "TODO (JSON)\n\r");
}


