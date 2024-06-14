/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <utility>
#include <iostream>
#include "PathMatcher.hpp"

using namespace Lattice;

PathMatcher::PathMatcher(std::string path) : _path(std::move(path))
{
    verifyPath(_path);
}

bool PathMatcher::matches(const std::string &path)
{
    // if path is not valid return false
    if (path.empty() || path[0] != '/') {
        return false;
    }

    // Split path into parts
    std::vector<std::string> _pathParts;
    std::vector<std::string> pathParts;

    for (size_t i = 0; i < _path.size(); i++) {
        std::string part;
        while (_path[i] != '/' && i < _path.size()) {
            part += _path[i];
            i++;
        }
        if (part.empty()) {
            continue;
        }
        _pathParts.push_back(part);
    }
    for (size_t i = 0; i < path.size(); i++) {
        std::string part;
        while (path[i] != '/' && i < path.size()) {
            part += path[i];
            i++;
        }
        if (part.empty()) {
            continue;
        }
        pathParts.push_back(part);
    }

    // if last path part has query parameters remove them
    if (pathParts[pathParts.size() - 1].find('?') != std::string::npos) {
        pathParts[pathParts.size() - 1] = pathParts[pathParts.size() - 1].substr(0, pathParts[pathParts.size() - 1].find('?'));
    }

    // if path has more parts than the path matcher return false
    if (_pathParts.size() != pathParts.size()) {
        return false;
    }

    // Compare parts
    for (std::size_t partIndex = 0; partIndex < _pathParts.size(); partIndex++) {
        std::size_t i = 0;
        for (; i < _pathParts[partIndex].size(); i++) {
            // if path parameter skip to next part
            if (_pathParts[partIndex][i] == '[') {
                // if we are at the end of the path part then the path does not specify the parameter
                if (i == pathParts[partIndex].size()) {
                    return false;
                }
                break;
            }
            // if wildcard return true
            if (_pathParts[partIndex] == "*") {
                return true;
            }
            // if part is not equal return false
            if (_pathParts[partIndex][i] != pathParts[partIndex][i]) {
                return false;
            }
        }
        // if we ended the part but there are still characters in the path return false
        if (i != pathParts[partIndex].size()) {
            // if path parameter skip to next part
            if (_pathParts[partIndex][i] == '[') {
                continue;
            }
            if (_pathParts[partIndex] == "*") {
                return true;
            }
            return false;
        }
    }
    return true;
}

static void verifyPathParameter(const std::string &path, size_t &i) {
    while (path[i] != ']' && i < path.size()) {
        if (path[i] == '[') {
            throw std::runtime_error(
                    "Path parameter is not closed (Nested path parameters are not allowed)");
        }
        if (path[i] == '?') {
            throw std::runtime_error(
                    "Path parameter is not closed (No query parameters allowed in path parameters)");
        }
        if (path[i] == '/') {
            throw std::runtime_error(
                    "Path parameter is not closed (No nested path parameters allowed)");
        }
        if (path[i] == '*') {
            throw std::runtime_error(
                    "Path parameter is not closed (No wildcard allowed in path parameters)");
        }
        if ((path[i] < 'a' || path[i] > 'z') && path[i] != '-' && (path[i] < '0' || path[i] > '9')) {
            throw std::runtime_error(
                    "Path parameter is not closed (Only lowercase letters, digits and hyphens are allowed in path parameters)");
        }
        i++;
    }
    if (path[i] != ']') {
        throw std::runtime_error("Path parameter is not closed");
    }
    if (i != path.size() - 1 && path[i + 1] != '/') {
        throw std::runtime_error("Path parameter is not closed (Path parameter must be followed by a '/' or the end of the path)");
    }
    if (i != path.size() - 1) {
        i++;
    }
}

void PathMatcher::verifyPath(const std::string &path)
{
    if (path.empty() || path[0] != '/') {
        throw std::runtime_error("Path must start with a '/'");
    }
    if (path[path.size() - 1] == '/') {
        throw std::runtime_error("Path must not end with a '/'");
    }
    for (size_t i = 0; i < path.size(); i++) {
        if (path[i] == '[') { // Detect path parameter start
            i++;
            verifyPathParameter(path, i);
            continue;
        }
        if (path[i] == '?') { // Detect query parameters
            throw std::runtime_error("Query parameters are not allowed in path matcher");
        }
        if (path[i] == '*') { // Detect wildcard
            if (i != path.size() - 1) {
                throw std::runtime_error("Wildcard is only allowed at the end of the path matcher");
            }
            break;
        }
        if ((path[i] < 'a' || path[i] > 'z') && path[i] != '/' && path[i] != '-') {
            throw std::runtime_error("Invalid character in path matcher");
        }
    }
}

static std::string getParamName(const std::string &path, size_t &i)
{
    std::string paramName;
    i++;
    while (path[i] != ']' && i < path.size()) {
        paramName += path[i];
        i++;
    }
    i++;
    return paramName;
}

static void unescape(std::string &str)
{
    for (size_t i = 0; i < str.size(); i++) {
        if (str[i] == '%') {
            if (i + 2 >= str.size()) {
                throw std::runtime_error("Invalid escape sequence");
            }
            str[i] = (char) std::stoi(str.substr(i + 1, 2), nullptr, 16);
            str.erase(i + 1, 2);
        }
    }
}

ProcessedPath PathMatcher::process(const std::string &path)
{
    ProcessedPath processedPath{};
    bool inQuery = false;

    std::size_t i = 0;

    for (size_t j = 0; j < path.size() && (i < _path.size() || inQuery); j++) {
        if (_path[i] == '[') {
            std::string pathParamName = getParamName(_path, i);
            std::string pathParamValue;
            while (j < path.size()) {
                if (path[j] == '?') {
                    inQuery = true;
                    break;
                }
                if (path[j] == '/') {
                    break;
                }
                pathParamValue += path[j];
                j++;
            }
            unescape(pathParamValue);
            processedPath.path_params[pathParamName] = pathParamValue;
        }
        if (_path[i] == '*') {
            break;
        }
        if (path[j] == '?') {
            inQuery = true;
            j++;
        }
        if (inQuery) {
            std::string queryParamName;
            std::string queryParamValue;
            if (path[j] == '&' || path[j] == '?') {
                j++;
            }
            while (path[j] != '=' && j < path.size()) {
                queryParamName += path[j];
                j++;
            }
            j++;
            while (path[j] != '&' && j < path.size()) {
                queryParamValue += path[j];
                j++;
            }
            unescape(queryParamValue);
            processedPath.query_params.push_back({queryParamName, queryParamValue});
        } else {
            i++;
        }
    }
    return processedPath;
}

PathMatcher &PathMatcher::operator=(const PathMatcher &other)
{
    if (this == &other)
        return *this;
    _path = other._path;
    return *this;
}
