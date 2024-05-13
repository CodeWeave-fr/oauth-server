cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project("CodeWeave-OAuth2-Server"
        LANGUAGES CXX
        VERSION 0.1.0
        DESCRIPTION "OAuth2 Server for CodeWeave"
        HOMEPAGE_URL "https://github.com/codeweave-inc/oauth-server"
)

# Add the source directory
add_subdirectory(src)
