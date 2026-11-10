add_library(UtilityHasherMD5 STATIC)
target_sources(
        UtilityHasherMD5
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_SOURCE_DIR}/include/"
        FILES "${CMAKE_SOURCE_DIR}/include/duplicate_scanner/utility/hasher/md5_hasher.hpp"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/md5_hasher.cc"
)
target_link_libraries(
        UtilityHasherMD5
        PRIVATE
        Boost::boost
)

add_library(UtilityHasherSHA3 STATIC)
target_sources(
        UtilityHasherSHA3
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_SOURCE_DIR}/include/"
        FILES "${CMAKE_SOURCE_DIR}/include/duplicate_scanner/utility/hasher/sha3_hasher.hpp"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/sha3_hasher.cc"
)
target_link_libraries(
        UtilityHasherSHA3
        PRIVATE
        Boost::boost
)

add_library(UtilityHasherBlake2B STATIC)
target_sources(
        UtilityHasherBlake2B
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_SOURCE_DIR}/include/"
        FILES "${CMAKE_SOURCE_DIR}/include/duplicate_scanner/utility/hasher/blake2b_hasher.hpp"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/blake2b_hasher.cc"
)
target_link_libraries(
        UtilityHasherBlake2B
        PRIVATE
        Boost::boost
)

add_library(UtilityHasherLib INTERFACE)
add_library(UtilityHasherLib::UtilityHasherLib ALIAS UtilityHasherLib)
target_sources(
        UtilityHasherLib
        INTERFACE
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_SOURCE_DIR}/include/"
        FILES "${CMAKE_SOURCE_DIR}/include/duplicate_scanner/utility/hasher/hasher.hpp"
)
target_link_libraries(
        UtilityHasherLib
        INTERFACE
        UtilityHasherMD5
        UtilityHasherSHA3
        UtilityHasherBlake2B
)
