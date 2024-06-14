/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/


#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "Types.hpp"

namespace Lattice {

    typedef struct {
        std::vector<QueryParam> query_params;
        std::unordered_map<std::string, std::string> path_params;
    } ProcessedPath;

    class PathMatcher {
    protected:
        std::string _path;

        static void verifyPath(const std::string &path);
    public:
        explicit PathMatcher(std::string path);
        PathMatcher(const PathMatcher &other) = default;
        ~PathMatcher() = default;

        // ---------- Methods ----------
        bool matches(const std::string &path);
        ProcessedPath process(const std::string &path);

        // ---------- Operator Overloads ----------
        PathMatcher &operator=(const PathMatcher &other);
    };
}
