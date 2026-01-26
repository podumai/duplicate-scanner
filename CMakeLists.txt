cmake_minimum_required(VERSION 4.0)
project(
        DupScanner
        VERSION 1.0.0
        LANGUAGES CXX
        DESCRIPTION "Command line utility that finds duplicate files"
)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})

if ($ENV{DEV})
    include(cmake/ccache.cmake)
    include(cmake/clang_tidy.cmake)
endif ()

find_package(Boost 1.89.0 REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(src)
add_subdirectory(app)
