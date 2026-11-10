cmake_minimum_required(VERSION 4.0)

file(STRINGS PROJECT_VERSION PINNED_PROJECT_VERSION LIMIT_COUNT 1)
project(
        DupScanner
        VERSION "${PINNED_PROJECT_VERSION}"
        LANGUAGES CXX
        DESCRIPTION "Command line utility that finds duplicate files"
)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

set(CACHE{CMAKE_CXX_STANDARD} TYPE INTERNAL HELP "" FORCE VALUE 23)
set(CACHE{CMAKE_CXX_STANDARD_REQUIRED} TYPE BOOL HELP "" FORCE VALUE ON)
set(CACHE{CMAKE_CXX_EXTENSIONS} TYPE BOOL HELP "" FORCE VALUE OFF)

if(CMAKE_CXX_COMPILER_ID MATCHES "Clang|GNU|AppleClang")
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64")
        add_compile_options(-mtune=generic -march=x86-64)
    elseif(CMAKE_SYSTEM_PROCESSOR MATCHES "arm64|aarch64|ARM64")
        add_compile_options(-mtune=generic -march=armv8-a)
    else()
        message(FATAL_ERROR "[${PROJECT_NAME}] Unknown processor: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
elseif(CMAKE_CXX_COMPILER_ID MATCHES "MSVC")
    if (CMAKE_SYSTEM_PROCESSOR MATCHES "x86_64|amd64")
        set(CACHE{CMAKE_MSVC_RUNTIME_LIBRARY} TYPE STRING HELP "" FORCE VALUE "MultiThreaded$<$<CONFIG:Debug>:Debug>")
    else()
        message(FATAL_ERROR "[${PROJECT_NAME}] Unknown processor for msvc build: ${CMAKE_SYSTEM_PROCESSOR}")
    endif()
else()
    message(FATAL_ERROR "[${PROJECT_NAME}] Unsupported compiler: ${CMAKE_CXX_COMPILER_ID}")
endif()

if ($ENV{DEV})
    include(cmake/ccache.cmake)
    include(cmake/clang_tidy.cmake)
endif ()

find_package(Boost CONFIG REQUIRED)
find_package(spdlog REQUIRED)

add_subdirectory(src)
add_subdirectory(app)
