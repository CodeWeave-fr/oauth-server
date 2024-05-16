/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include "AbstractMessage.hpp"
#include <utility>

using namespace Lattice;

// Constructors

AbstractMessage::AbstractMessage(const std::vector<Header> &headers, std::string body): _headers(headers), _body(std::move(body))
{

}

AbstractMessage::AbstractMessage(const AbstractMessage &message) = default;

// Getters

std::vector<Header> AbstractMessage::getHeaders() const
{
    return _headers;
}

std::string AbstractMessage::getBody() const
{
    return _body;
}

bool AbstractMessage::hasHeader(const std::string &name) const
{
    return std::ranges::any_of(_headers, [&name](const Header &header) {
        return header.name == name;
    });
}

bool AbstractMessage::hasBody() const
{
    return !_body.empty();
}

std::string AbstractMessage::getHeaderOrDefault(const std::string &name, const std::string &defaultValue) const
{
    for (const auto &header : _headers) {
        if (header.name == name) {
            return header.value;
        }
    }
    return defaultValue;
}

// Setters

void AbstractMessage::setHeaders(const std::vector<Header> &headers)
{
    _headers = headers;
}

void AbstractMessage::setBody(std::string body)
{
    _body = std::move(body);
}

// Modifiers

void AbstractMessage::addHeader(const Header &header)
{
    if (hasHeader(header.name)) {
        for (auto &h : _headers) {
            if (h.name == header.name) {
                h.value = header.value;
            }
        }
        return;
    }
    _headers.push_back(header);
}

void AbstractMessage::addHeader(std::string name, std::string value)
{
    addHeader({std::move(name), std::move(value)});
}

void AbstractMessage::removeHeader(const std::string &name)
{
    for (auto it = _headers.begin(); it != _headers.end(); ++it) {
        if (it->name == name) {
            _headers.erase(it);
            return;
        }
    }
}
