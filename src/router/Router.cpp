/*
** EPITECH PROJECT, 2024
** CodeWeave-OAuth2-Server
** File description:
** No file there , just an epitech header example .
** You can even have multiple lines if you want !
*/

#include <iostream>
#include <print>
#include <sys/ioctl.h>
#include "Router.hpp"

using namespace Lattice;

Router::Router(unsigned short port) : _port(port) {
    // Get current terminal width
    struct winsize w{};
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    const std::size_t boxWidth = 20;
    const std::size_t boxHeight = 4;
    bool hasSpace = w.ws_col >= boxWidth;
    std::size_t start_x = (w.ws_col - boxWidth) / 2;
    std::size_t end_x = start_x + boxWidth;
    if (hasSpace) {
        for (std::size_t i = 0; i < boxHeight; i++) {
            for (std::size_t j = 0; j < w.ws_col; j++) {
                // Draw box
                if (i == 0 || i == boxHeight - 1) {
                    if (j == start_x || j == end_x) {
                        std::cout << "+";
                    } else if (j > start_x && j < end_x) {
                        std::cout << "-";
                    } else {
                        std::cout << " ";
                    }
                } else {
                    if (j == start_x || j == end_x) {
                        std::cout << "|";
                    } else {
                        std::cout << " ";
                    }
                }

                // Draw text
                if (i == 1 && j == start_x + 2) {
                    std::cout << "Router";
                    j += 6;
                }
                if (i == 2 && j == start_x + 2) {
                    std::cout << "Port: " << port;
                    j += std::to_string(port).length() + 6;
                }
            }
            std::cout << std::endl;
        }
    } else {
        std::cout << "Router started on port " << port << std::endl;
    }
}
