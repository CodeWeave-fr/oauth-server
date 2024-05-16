/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "Request.hpp"

#include <utility>

using namespace Lattice;

// Constructors

Request::Request(Method method, std::string path, const std::string &body): AbstractMessage({}, body), _method(method),
                                                                            _path(std::move(path))
{

}

Request::Request(Method method, std::string path, const std::vector<Header> &headers, const std::string &body): AbstractMessage(headers, body), _method(method),
                                                                                                                _path(std::move(path))
{

}

Request::Request(const Request &request): AbstractMessage(request), _method(request._method),
                                         _path(request._path)
{
}

// Getters

Method Request::getMethod() const
{
    return _method;
}

std::string Request::getPath() const
{
    return _path;
}

bool Request::isHandled() const
{
    return _handled;
}

// Setters

void Request::setMethod(Method method)
{
    _method = method;
}

void Request::setPath(std::string path)
{
    _path = std::move(path);
}

void Request::setHandled(bool handled)
{
    _handled = handled;
}

// Serialization

std::string Request::serialize() const
{
    throw std::runtime_error("Not implemented");
}

// Operator Overloads

Request &Request::operator=(const Request &request)
{
    if (this == &request)
        return *this;
    AbstractMessage::operator=(request);
    _method = request._method;
    _path = request._path;
    return *this;
}
