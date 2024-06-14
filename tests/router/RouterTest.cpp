/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <catch2/catch_test_macros.hpp>
#include "router/RouterPipelineBuilder.hpp"
#include "router/Router.hpp"

using namespace Lattice;

class TestMiddleware : public Middleware {
public:
    std::optional<Response> handle(Request &request) override {
        if (request.getHeaderOrDefault("test", "false") == "true") {
            return Response(200, "OK");
        }
        return std::nullopt;
    }
};

class TestMiddleware2 : public Middleware {
public:
    std::optional<Response> handle(Request &request) override {
        if (request.getHeaderOrDefault("test2", "false") == "true") {
            return Response(200, "OK");
        }
        return std::nullopt;
    }
};

class TestRouteHandler : public RouteHandler {
public:
    const Response &handle(const Request &request) override {
        return Response(200, "OK");
    }
};

TEST_CASE("Router") {

    SECTION("One route") {
        Router router;
        router.addPipeline(RouterPipelineBuilder()
                                   .setPath("/test")
                                   .addAllowedMethod(Method::GET)
                                   .setHandler(new TestRouteHandler())
                                   .addMiddleware(new TestMiddleware())
                                   .build());
        auto response = router.handleRequest(Request(Method::GET, "/test"));
        REQUIRE(response.getStatus() == 200);
        REQUIRE(response.getBody() == "OK");
    }

}
