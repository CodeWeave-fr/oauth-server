cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

project("CodeWeave-OAuth2-Server"
        LANGUAGES CXX
        VERSION 0.1.0
        DESCRIPTION "OAuth2 Server for CodeWeave"
        HOMEPAGE_URL "https://github.com/codeweave-inc/oauth-server"
)

# Common compile options for all targets
add_compile_options(-Wall -Wextra -Wpedantic)

# Create an object library for the main sources with coverage flags
add_library(${PROJECT_NAME}_lib)

# Add the source directory and link sources to the object library
add_subdirectory(src)

# Main executable
add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE ${PROJECT_NAME}_lib)

### Testing (CMake Catch2 Integration)
include(CTest)
include(FetchContent)
find_package(Catch2 3 REQUIRED)

# Define coverage flags
set(COVERAGE_COMPILE_FLAGS "-g" "--coverage")

# Test executable
add_executable(${PROJECT_NAME}_test)
add_subdirectory(tests)

# Include directories for the test target
target_include_directories(${PROJECT_NAME}_test PRIVATE src)

# Link the main sources object library and Catch2 to the test target
target_link_libraries(${PROJECT_NAME}_test PRIVATE Catch2::Catch2WithMain ${PROJECT_NAME}_lib)

# Add coverage flags only to the main sources
target_compile_options(${PROJECT_NAME}_lib PRIVATE ${COVERAGE_COMPILE_FLAGS})
target_link_options(${PROJECT_NAME}_test PRIVATE ${COVERAGE_COMPILE_FLAGS})

# Exclude test sources from coverage
set_target_properties(${PROJECT_NAME}_test PROPERTIES EXCLUDE_FROM_ALL TRUE)
