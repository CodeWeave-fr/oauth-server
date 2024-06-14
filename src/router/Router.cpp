/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Router.hpp"
#include "RouterPipelineBuilder.hpp"

using namespace Lattice;

Router::Router(unsigned short port) : _port(port), _defaultPipeline(RouterPipelineBuilder().build()) {

}

Router::~Router() = default;

void Router::addPipeline(const RouterPipeline &pipeline) {
    this->_pipelines.push_back(pipeline);
}

void Router::addRoute(Lattice::Method method, const std::string &path, RouteHandler *handler) {
    auto pipeline = RouterPipelineBuilder(path).setHandler(handler).addAllowedMethod(method).build();
    this->_pipelines.push_back(pipeline);
}

Response Router::handleRequest(Lattice::Request &request) {
    for (auto &pipeline : this->_pipelines) {
        if (pipeline.getPathMatcher().matches(request.getPath())) {
            auto processedPath = pipeline.getPathMatcher().process(request.getPath());
            auto newRequest = request;
            newRequest.setProcessedPath(processedPath);
            return pipeline.launch(newRequest);
        }
    }
    return this->_defaultPipeline.launch(request);
}

unsigned short Router::getPort() const {
    return this->_port;
}

void Router::setDefaultPipeline(RouterPipeline pipeline) {
    this->_defaultPipeline = pipeline;
}

Router &Router::operator=(const Router &other) {
    if (this == &other)
        return *this;
    this->_port = other._port;
    this->_pipelines = other._pipelines;
    this->_defaultPipeline = other._defaultPipeline;
    return *this;
}
