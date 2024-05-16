/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/


#pragma once
#include <string>

namespace Lattice {
    enum Method {
        GET,
        POST,
        PUT,
        DELETE,
        PATCH,
        OPTIONS,
        HEAD,
        CONNECT,
        TRACE
    };

    static std::string methodToString(Method method) {
        switch (method) {
            case GET:
                return "GET";
            case POST:
                return "POST";
            case PUT:
                return "PUT";
            case DELETE:
                return "DELETE";
            case PATCH:
                return "PATCH";
            case OPTIONS:
                return "OPTIONS";
            case HEAD:
                return "HEAD";
            case CONNECT:
                return "CONNECT";
            case TRACE:
                return "TRACE";
        }
    }

    static Method stringToMethod(const std::string &method) {
        if (method == "GET") {
            return GET;
        } else if (method == "POST") {
            return POST;
        } else if (method == "PUT") {
            return PUT;
        } else if (method == "DELETE") {
            return DELETE;
        } else if (method == "PATCH") {
            return PATCH;
        } else if (method == "OPTIONS") {
            return OPTIONS;
        } else if (method == "HEAD") {
            return HEAD;
        } else if (method == "CONNECT") {
            return CONNECT;
        } else if (method == "TRACE") {
            return TRACE;
        }
        throw std::invalid_argument("Invalid method");
    }
}
