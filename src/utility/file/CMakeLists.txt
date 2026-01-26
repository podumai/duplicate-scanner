add_library(FileLib)
add_library(FileLib::FileLib ALIAS FileLib)
target_sources(
        FileLib
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_SOURCE_DIR}/include"
        FILES "${CMAKE_SOURCE_DIR}/include/duplicate_scanner/utility/file/file.hpp"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/file.cpp"
)
