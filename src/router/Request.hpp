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
#include "Method.hpp"
#include "Types.hpp"
#include "AbstractMessage.hpp"

namespace Lattice {
    class Request: public AbstractMessage {
    protected:
        Method _method;
        std::string _path;
        bool _handled = false;
    public:
        Request(Method method, std::string path, const std::string &body = "");
        Request(Method method, std::string path, const std::vector<Header> &headers, const std::string &body = "");
        Request(const Request &request);
        ~Request() override = default;

        // ---------- Getters ----------
        /**
         * @brief This method returns the Method of the Request object
         * @return The Method of the Request object
         * @since 0.1.0
         */
        [[nodiscard]] Method getMethod() const;
        /**
         * @brief This method returns the Path of the Request object
         * @return The Path of the Request object
         * @since 0.1.0
         */
        [[nodiscard]] std::string getPath() const;
        /**
         * @brief This method returns whether the Request object has been handled
         * @return Whether the Request object has been handled
         * @since 0.1.0
         */
        [[nodiscard]] bool isHandled() const;

        // ---------- Setters ----------
        /**
         * @brief This method sets the Method of the Request object
         * @param method The Method to set
         * @since 0.1.0
         */
        void setMethod(Method method);
        /**
         * @brief This method sets the Path of the Request object
         * @param path The Path to set
         * @since 0.1.0
         */
        void setPath(std::string path);
        /**
         * @brief This method sets whether the Request object has been handled
         * @param handled Whether the Request object has been handled
         * @since 0.1.0
         */
        void setHandled(bool handled);

        // ---------- Modifiers ----------

        // ---------- Serialization ----------
        /**
         * @brief This method serializes the Request object into a string
         * @return The serialized Request object
         * @since 0.1.0
         */
        [[nodiscard]] std::string serialize() const override;

        // ---------- Operator Overloads ----------
        /**
         * @brief This method is used to assign a Request object to another Request object
         * @param request the Request object to "copy"
         * @return The Request object that was assigned
         * @since 0.1.0
         */
        Request &operator=(const Request &request);
    };
}
