/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Middleware.hpp"

using namespace Lattice;

RouterPipelineStep::PipelineStepResult Middleware::run(Request &request, Response &response) {
    auto res = handle(request);

    if (res.has_value()) {
        response = res.value();
        return RouterPipelineStep::PipelineStepResult::STOP;
    }
    return RouterPipelineStep::PipelineStepResult::CONTINUE;
}
