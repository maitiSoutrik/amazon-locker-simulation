cmake_minimum_required(VERSION 3.10)
project(amazon_locker)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable testing
enable_testing()

# Add compiler warnings
if(CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -Wpedantic -Werror)
endif()

# Code coverage option
option(ENABLE_COVERAGE "Enable coverage reporting" OFF)
if(ENABLE_COVERAGE)
    add_compile_options(--coverage -O0 -g)
    add_link_options(--coverage)
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bins)

# Include directories
include_directories(
    ${PROJECT_SOURCE_DIR}/include
)

# Add subdirectories
add_subdirectory(app)
add_subdirectory(tests)

# Deployment configuration
if(DEFINED ENV{REPLIT_DEPLOYMENT})
    message(STATUS "Configuring for Replit deployment")
    set(CMAKE_BUILD_TYPE Release)
    add_compile_definitions(DEPLOYMENT_ENV="replit")
endif()