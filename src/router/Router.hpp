/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <functional>
#include "Method.hpp"
#include "Request.hpp"
#include "Response.hpp"
#include "RouterPipeline.hpp"
#include "RouteHandler.hpp"

namespace Lattice {

    typedef std::function<void(Request &req, Response &res)> Handler;

    class Router {
    protected:
        unsigned short _port;

        std::vector<RouterPipeline> _pipelines{};
        RouterPipeline _defaultPipeline; // 404
    public:
        explicit Router(unsigned short port = 8080);
        Router(const Router &other) = default;
        ~Router();

        // ---------- Methods ----------
        void addRoute(Method method, const std::string &path, RouteHandler *handler);
        void addPipeline(const RouterPipeline &pipeline);
        [[nodiscard]] Response handleRequest(Request &request);

        // ---------- Getters ----------
        [[nodiscard]] unsigned short getPort() const;

        // ---------- Setters ----------
        /**
         * @brief Set the default pipeline for the router
         * This pipeline will be used if no other pipeline matches the request
         * @param pipeline The pipeline to be used as default
         */
        void setDefaultPipeline(RouterPipeline pipeline);

        // ---------- Operator Overloads ----------
        Router &operator=(const Router &other);
    };
}
