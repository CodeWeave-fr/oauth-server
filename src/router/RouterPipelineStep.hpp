/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/


#pragma once
#include "Request.hpp"
#include "Response.hpp"

namespace Lattice {
    class RouterPipelineStep {
    public:
        enum PipelineStepResult {
            CONTINUE,
            STOP
        };
    protected:
        RouterPipelineStep *_nextStep = nullptr;
        RouterPipelineStep *_prevStep = nullptr;
        PipelineStepResult _result = CONTINUE;

        RouterPipelineStep() = default;
    public:
        virtual ~RouterPipelineStep();

        // ---------- Methods ----------
        [[nodiscard]] virtual PipelineStepResult run(Request &request, Response &response) = 0;

        // ---------- Setters ----------
        /**
         * Set the next step
         * @param step The next step
         * @return void
         * @warning This will overwrite the current next step (destroying it if any)
         * @note This will also set the previous step of the next step to this step
         * @since 0.1.0
         */
        void setNextStep(RouterPipelineStep *step);

        // ---------- Getters ----------
        /**
         * Get the next step
         * @return The next step
         * @since 0.1.0
         */
        RouterPipelineStep *getNextStep();
        /**
         * Get the previous step
         * @return The previous step
         * @since 0.1.0
         */
        RouterPipelineStep *getPrevStep();
    };
}
