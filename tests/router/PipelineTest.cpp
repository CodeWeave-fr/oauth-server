/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <catch2/catch_test_macros.hpp>
#include "router/RouterPipelineBuilder.hpp"

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

TEST_CASE("PipelineBuilder") {
    SECTION("Simple pipeline") {
        RouterPipelineBuilder builder;
        builder.setPath("/test")
                .addAllowedMethod(Method::GET)
                .addMiddleware(new TestMiddleware())
                .addMiddleware(new TestMiddleware2())
                .setHandler(new TestRouteHandler());

        auto pipeline = builder.build();
        REQUIRE(pipeline.getPathMatcher().matches("/test"));
        REQUIRE(pipeline.getAllowedMethods().size() == 1);
        REQUIRE(pipeline.getAllowedMethods()[0] == Method::GET);
        REQUIRE(pipeline.isMethodAllowed(Method::GET));
        REQUIRE(pipeline.getTopOfPipeline() != nullptr);
        REQUIRE(pipeline.getTopOfPipeline()->getNextStep() != nullptr);
        REQUIRE(pipeline.getTopOfPipeline()->getNextStep()->getNextStep() !=
                nullptr);
        REQUIRE(pipeline.getTopOfPipeline()->getNextStep()->getNextStep()->getNextStep() ==
                nullptr);
    }

    SECTION("Multiple methods") {
        RouterPipelineBuilder builder;
        builder.setPath("/test")
                .addAllowedMethods({Method::GET, Method::POST})
                .addMiddleware(new TestMiddleware())
                .addMiddleware(new TestMiddleware2())
                .setHandler(new TestRouteHandler());

        auto pipeline = builder.build();
        REQUIRE(pipeline.getPathMatcher().matches("/test"));
        REQUIRE(pipeline.getAllowedMethods().size() == 2);
        REQUIRE(pipeline.isMethodAllowed(Method::GET));
        REQUIRE(pipeline.isMethodAllowed(Method::POST));
    }

    SECTION("Weighted middlewares") {
        Middleware *middleware = new TestMiddleware();
        Middleware *middleware2 = new TestMiddleware2();

        RouterPipelineBuilder builder;
        builder.setPath("/test")
                .addAllowedMethod(Method::GET)
                .addMiddleware(middleware, 1)
                .addMiddleware(middleware2, 5)
                .setHandler(new TestRouteHandler());

        auto pipeline = builder.build();
        REQUIRE(pipeline.getPathMatcher().matches("/test"));
        REQUIRE(pipeline.getAllowedMethods().size() == 1);
        REQUIRE(pipeline.isMethodAllowed(Method::GET));
        REQUIRE(pipeline.getTopOfPipeline() == middleware2);
        REQUIRE(pipeline.getTopOfPipeline()->getNextStep() == middleware);
        REQUIRE(pipeline.getTopOfPipeline()->getNextStep()->getNextStep() != nullptr);
        REQUIRE(dynamic_cast<RouteHandler *>(pipeline.getTopOfPipeline()->getNextStep()->getNextStep()) != nullptr);
        REQUIRE(pipeline.getTopOfPipeline()->getNextStep()->getNextStep()->getNextStep() == nullptr);
    }
}
