/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/


#pragma once
#include <vector>
#include "RouterPipeline.hpp"
#include "Middleware.hpp"
#include "RouteHandler.hpp"

namespace Lattice {
    class RouterPipelineBuilder {
    protected:
        struct MiddlewareEntry {
            Middleware *middleware;
            int weight;
            int index;
        };
        std::vector<MiddlewareEntry> _middlewares;
        RouteHandler *_handler;
        PathMatcher _pathMatcher;
        std::vector<Method> _allowedMethods;
    public:
        explicit RouterPipelineBuilder(const std::string &path = "/*");
        ~RouterPipelineBuilder() = default;

        RouterPipeline build();

        RouterPipelineBuilder &addMiddleware(Middleware *middleware, int weight = -1);
        RouterPipelineBuilder &setHandler(RouteHandler *handler);
        RouterPipelineBuilder &setPathMatcher(const PathMatcher &pathMatcher);
        RouterPipelineBuilder &setPath(const std::string &path);
        RouterPipelineBuilder &setAllowedMethods(const std::vector<Method> &allowedMethods);
        RouterPipelineBuilder &addAllowedMethod(Method method);
        RouterPipelineBuilder &addAllowedMethods(const std::vector<Method> &methods);
    };
}
