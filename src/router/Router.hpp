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

namespace Lattice {

    typedef std::function<void(Request &req, Response &res)> Handler;

    class Router {
    protected:
        unsigned short _port;
    public:
        explicit Router(unsigned short port = 8080);
        ~Router() = default;
    };
}
