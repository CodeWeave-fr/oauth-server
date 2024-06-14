/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <optional>
#include "RouterPipelineStep.hpp"

namespace Lattice {
    class Middleware: public RouterPipelineStep {
    protected:
        Middleware() = default;

        /**
         * @brief Run the middleware
         * @param request the request to be handled by the middleware
         * @param response the response the middleware will write to (if needed)
         * @return The result of the pipeline step (CONTINUE or STOP) if the middleware gives a response the pipeline will stop
         * @note This method should not be overridden
         * @since 0.1.0
         */
        [[nodiscard]] PipelineStepResult run(Request &request, Response &response) final;
    public:
        ~Middleware() override = default;

        /**
         * @brief Handle the request
         * @param request The request to be handled by the middleware
         * @return An optional response, if the middleware gives it the pipeline will stop
         * @since 0.1.0
         */
        [[nodiscard]] virtual std::optional<Response> handle(Request &request) = 0;
    };
}
