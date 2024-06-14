/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/


#pragma once
#include "RouterPipelineStep.hpp"

namespace Lattice {
    class RouteHandler: public RouterPipelineStep {
    protected:
        RouteHandler() = default;

        /**
         * @brief Run the handler
         * @param request the request to be handled
         * @param response the response the handler will write to
         * @return The result of the pipeline step will always be STOP as the handler will always give a response
         * @note This method should not be overridden
         * @since 0.1.0
         */
        [[nodiscard]] PipelineStepResult run(Request &request, Response &response) final;
    public:
        ~RouteHandler() override = default;

        /**
         * @brief Handle the request
         * @param request The request to be handled
         * @return The response produced by the handler
         * @since 0.1.0
         */
        [[nodiscard]] virtual const Response &handle(const Request &request) = 0;
    };
}
