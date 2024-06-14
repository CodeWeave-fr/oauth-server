/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "RouterPipelineBuilder.hpp"

using namespace Lattice;

RouterPipelineBuilder::RouterPipelineBuilder(const std::string &path): _pathMatcher(path) {

}

RouterPipelineBuilder &RouterPipelineBuilder::addAllowedMethod(Lattice::Method method) {
    this->_allowedMethods.push_back(method);
    return *this;
}

RouterPipelineBuilder &RouterPipelineBuilder::addAllowedMethods(const std::vector<Method> &methods) {
    for (const auto &method : methods) {
        this->_allowedMethods.push_back(method);
    }
    return *this;
}

RouterPipelineBuilder &RouterPipelineBuilder::addMiddleware(Middleware *middleware, int weight) {
    this->_middlewares.push_back({middleware, weight, static_cast<int>(this->_middlewares.size())});
    return *this;
}

RouterPipelineBuilder &RouterPipelineBuilder::setAllowedMethods(const std::vector<Method> &allowedMethods) {
    this->_allowedMethods = allowedMethods;
    return *this;
}

RouterPipelineBuilder &RouterPipelineBuilder::setHandler(RouteHandler *handler) {
    this->_handler = handler;
    return *this;
}

RouterPipelineBuilder &RouterPipelineBuilder::setPath(const std::string &path) {
    this->_pathMatcher = PathMatcher(path);
    return *this;
}

RouterPipelineBuilder &RouterPipelineBuilder::setPathMatcher(const PathMatcher &pathMatcher) {
    this->_pathMatcher = pathMatcher;
    return *this;
}

RouterPipeline RouterPipelineBuilder::build() {
    auto pipeline = RouterPipeline(this->_pathMatcher, this->_allowedMethods, nullptr);
    // Sort middlewares by weight (first) and index (second)
    std::sort(this->_middlewares.begin(), this->_middlewares.end(), [](const MiddlewareEntry &a, const MiddlewareEntry &b) {
        if (a.weight == b.weight) {
            return a.index < b.index;
        }
        return a.weight > b.weight;
    });
    for (const auto &middlewareEntry : this->_middlewares) {
        pipeline.addStep(middlewareEntry.middleware);
    }
    pipeline.addStep(this->_handler);
    return pipeline;
}
