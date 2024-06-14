/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "RouteHandler.hpp"

using namespace Lattice;

RouterPipelineStep::PipelineStepResult RouteHandler::run(Request &request, Response &response) {
    const Response &res = this->handle(request);
    response = res;
    return PipelineStepResult::STOP;
}
