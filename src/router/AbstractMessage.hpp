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

namespace Lattice {
    class AbstractMessage {
    protected:
        std::vector<Header> _headers;
        std::string _body;

        AbstractMessage(const std::vector<Header> &headers, std::string body);
        AbstractMessage(const AbstractMessage &message);
    public:
        virtual ~AbstractMessage() = default;

        // ---------- Getters ----------
        /**
         * @brief This method returns the Headers of the object
         * @return The Headers of the object
         * @since 0.1.0
         */
        [[nodiscard]] std::vector<Header> getHeaders() const;
        /**
         * @brief This method returns the Body of the object
         * @return The Body of the object
         * @since 0.1.0
         */
        [[nodiscard]] std::string getBody() const;
        /**
         * @brief This method returns whether the object has a Header with a specific name
         * @param name The name of the Header to check for (case-insensitive)
         * @return Whether the object has a Header with the specific name
         * @since 0.1.0
         */
        [[nodiscard]] bool hasHeader(const std::string &name) const;
        /**
         * @brief This method returns whether the object has a Body (<code>length(body) > 0</code>)
         * @return Whether the object has a Body
         * @since 0.1.0
         */
        [[nodiscard]] bool hasBody() const;
        /**
         * @brief This method returns the Header with a specific name
         * @param name The name of the Header to get (case-insensitive)
         * @param defaultValue The value to return if the Header does not exist
         * @return The Header with the specific name or the default value if it does not exist
         * @since 0.1.0
         */
        [[nodiscard]] std::string getHeaderOrDefault(const std::string &name, const std::string &defaultValue) const;
        /**
         * @brief This method returns the Header with a specific name or an empty string if it does not exist
         * @param name The name of the Header to get (case-insensitive)
         * @return The Header with the specific name or an empty string if it does not exist
         * @since 0.1.0
         * @see getHeaderOrDefault
         */
        [[nodiscard]] std::string getHeader(const std::string &name) const { return getHeaderOrDefault(name, ""); };

        // ---------- Setters ----------
        /**
         * @brief This method sets the Headers of the object
         * @param headers The headers vector to set
         * @since 0.1.0
         */
        void setHeaders(const std::vector<Header> &headers);
        /**
         * @brief This method sets the Body of the object
         * @param body The body to set
         * @since 0.1.0
         */
        void setBody(std::string body);

        // ---------- Modifiers ----------
        /**
         * @brief This method adds a header to the object
         * @param header The header to add
         * @since 0.1.0
         * @warning This function will replace the header if it already exists
         */
        void addHeader(const Header &header);
        /**
         * @brief This method adds a header to the object
         * @param name The name of the header to add
         * @param value The value of the header to add
         * @since 0.1.0
         * @see addHeader(const Header &header)
         * @warning This function will replace the header if it already exists
         */
        void addHeader(std::string name, std::string value);
        /**
         * @brief This method adds a header to the object
         * @param name The name of the header to add
         * @param value The value of the header to add
         * @since 0.1.0
         */
        void removeHeader(const std::string &name);

        // ---------- Serialization ----------
        /**
         * @brief This method serializes the object into a string
         * @return The serialized object
         * @since 0.1.0
         */
        [[nodiscard]] virtual std::string serialize() const = 0;

        // ---------- Operator Overloads ----------
    };
}
