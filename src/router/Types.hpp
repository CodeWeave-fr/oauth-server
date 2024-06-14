/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <string>
#include "Method.hpp"

#define HTTP_VERSION "HTTP/1.1"

namespace Lattice {
    typedef struct {
        std::string name;
        std::string value;
    } Header;

    typedef struct {
        std::string name;
        std::string value;
    } QueryParam;

    typedef struct {
        std::string path;
        Method method;
    } Route;
}
