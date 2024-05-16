/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#pragma once
#include <vector>
#include "Types.hpp"
#include "AbstractMessage.hpp"

namespace Lattice {

    class Response: public AbstractMessage {
    protected:
        short _status;
    public:
        explicit Response(short status, const std::string& body = "");
        Response(short status, const std::vector<Header> &headers, const std::string& body = "");
        Response(const Response &response);
        ~Response() override = default;

        /**
         * @brief This method returns the message that goes with a status
         * @param status The status code
         * @return The message that goes with the status code
         * @example Response::statusToString(200) // "OK"
         */
        [[nodiscard]] static std::string statusToString(short status);

        // ---------- Getters ----------
        /**
         * @brief This method returns the status of the Response object
         * @return The status of the Response object
         */
        [[nodiscard]] short getStatus() const;

        // ---------- Setters ----------
        /**
         * @brief This method sets the status of the Response object
         * @param status The status to set
         */
        void setStatus(short status);

        // ---------- Serialization ----------
        /**
         * @brief This method serializes the Response object into a string
         * @return The serialized Response object
         */
        [[nodiscard]] std::string serialize() const override;

        // ---------- Operator Overloads ----------
        /**
         * @brief This method is used to assign a Response object to another Response object
         * @param response the Response object to "copy"
         * @return The Response object that was assigned
         */
        Response &operator=(const Response &response);

        // ---------- Template Response ----------
        const static Response OK;
        const static Response CREATED;
        const static Response ACCEPTED;
        const static Response NO_CONTENT;
        const static Response MOVED_PERMANENTLY;
        const static Response BAD_REQUEST;
        const static Response UNAUTHORIZED;
        const static Response FORBIDDEN;
        const static Response NOT_FOUND;
        const static Response METHOD_NOT_ALLOWED;
        const static Response INTERNAL_SERVER_ERROR;
        const static Response NOT_IMPLEMENTED;
        const static Response BAD_GATEWAY;
        const static Response SERVICE_UNAVAILABLE;
    };
}
