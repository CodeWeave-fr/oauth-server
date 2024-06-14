/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/


#pragma once
#include <string>
#include "RouterPipelineStep.hpp"
#include "PathMatcher.hpp"

namespace Lattice {
    class RouterPipeline {
    protected:
        RouterPipelineStep *_topOfPipeline = nullptr;
        PathMatcher _pathMatcher;
        std::vector<Method> _allowedMethods;
    public:
        RouterPipeline(const PathMatcher &pathMatcher, const std::vector<Method>& allowedMethods, RouterPipelineStep *topOfPipeline = nullptr);
        ~RouterPipeline();

        // ---------- Methods ----------
        [[nodiscard]] Response launch(Request &request);

        // ---------- Getters ----------
        /**
         * Get the top of the pipeline (const)
         * @return The top of the pipeline
         * @since 0.1.0
         */
        [[nodiscard]] const RouterPipelineStep *getTopOfPipeline() const;
        /**
         * Get the path matcher
         * @return The path matcher
         * @since 0.1.0
         */
        RouterPipelineStep *getTopOfPipeline();
        /**
         * Get the path matcher (const)
         * @return The path matcher
         * @since 0.1.0
         */
        [[nodiscard]] PathMatcher getPathMatcher() const;
        /**
         * Get the path matcher
         * @return The path matcher
         * @since 0.1.0
         */
        PathMatcher &getPathMatcher();
        /**
         * Get the allowed methods
         * @return The allowed methods
         * @since 0.1.0
         */
        [[nodiscard]] std::vector<Method> getAllowedMethods() const;
        /**
         * Check if a method is allowed
         * @param method The method to check
         * @return Whether the method is allowed
         * @since 0.1.0
         */
        [[nodiscard]] bool isMethodAllowed(Method method) const;

        // ---------- Setters ----------
        /**
         * Set the top of the pipeline
         * @param topOfPipeline The top of the pipeline
         * @since 0.1.0
         * @warning This will destroy the old top of the pipeline (cascading down the pipeline)
         * @note This will also set the previous step of the top of the pipeline to nullptr
         */
        void setTopOfPipeline(RouterPipelineStep *topOfPipeline);
        /**
         * Set the path matcher
         * @param pathMatcher The path matcher
         * @since 0.1.0
         */
        void setPathMatcher(const PathMatcher &pathMatcher);


        // ---------- Modifiers ----------
        /**
         * Add a step to the pipeline
         * @param step The step to add
         * @since 0.1.0
         */
        void addStep(RouterPipelineStep *step);
    };
}
