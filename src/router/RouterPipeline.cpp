/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "RouterPipeline.hpp"

using namespace Lattice;

RouterPipeline::RouterPipeline(const Lattice::PathMatcher &pathMatcher, const std::vector<Method> &allowedMethods, Lattice::RouterPipelineStep *topOfPipeline):
_topOfPipeline(topOfPipeline), _pathMatcher(pathMatcher), _allowedMethods(allowedMethods) {

}
RouterPipeline::~RouterPipeline() {
    delete this->_topOfPipeline;
}

RouterPipelineStep *RouterPipeline::getTopOfPipeline() {
    return this->_topOfPipeline;
}

PathMatcher RouterPipeline::getPathMatcher() const {
    return this->_pathMatcher;
}

const RouterPipelineStep *RouterPipeline::getTopOfPipeline() const {
    return this->_topOfPipeline;
}

PathMatcher &RouterPipeline::getPathMatcher() {
    return this->_pathMatcher;
}

void RouterPipeline::setTopOfPipeline(RouterPipelineStep *topOfPipeline) {
    delete this->_topOfPipeline;
    this->_topOfPipeline = topOfPipeline;
}

void RouterPipeline::setPathMatcher(const PathMatcher &pathMatcher) {
    this->_pathMatcher = pathMatcher;
}

void RouterPipeline::addStep(RouterPipelineStep *step) {
    if (!this->_topOfPipeline) {
        this->_topOfPipeline = step;
        return;
    }
    auto currentStep = this->_topOfPipeline;
    while (currentStep->getNextStep()) {
        currentStep = currentStep->getNextStep();
    }
    currentStep->setNextStep(step);
}

std::vector<Method> RouterPipeline::getAllowedMethods() const {
    return this->_allowedMethods;
}

bool RouterPipeline::isMethodAllowed(Method method) const {
    return std::ranges::any_of(this->_allowedMethods, [method](Method allowedMethod) {
        return allowedMethod == method;
    });
}

Response RouterPipeline::launch(Request &request) {
    auto res = Response(200);
    auto step = this->_topOfPipeline;
    while (step) {
        auto stepRes = step->run(request, res);
        if (stepRes == RouterPipelineStep::PipelineStepResult::STOP) {
            return res;
        }
        step = step->getNextStep();
    }
    // If we reach this point, no step stopped the pipeline
    res.setStatus(500);
    res.setBody(R"({"error": "The pipeline did not stop"})");
    return res;
}
