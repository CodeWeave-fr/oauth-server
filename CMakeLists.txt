cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project("CodeWeave-OAuth2-Server"
        LANGUAGES CXX
        VERSION 0.1.0
        DESCRIPTION "OAuth2 Server for CodeWeave"
        HOMEPAGE_URL "https://github.com/codeweave-inc/oauth-server"
)

add_compile_options(-Wall -Wextra -Wpedantic -Werror)
add_executable(${PROJECT_NAME})

# Add the source directory
add_subdirectory(src)
