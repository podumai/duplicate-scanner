add_library(ScannerLib)
add_library(ScannerLib::ScannerLib ALIAS ScannerLib)
target_sources(
        ScannerLib
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_SOURCE_DIR}/include"
        FILES
        "${CMAKE_SOURCE_DIR}/include/duplicate_scanner/core/scanner/scanner.hpp"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/scanner.cpp"
)
target_link_libraries(
        ScannerLib
        PUBLIC
        Boost::boost
        HasherFactoryLib::HasherFactoryLib
        FileLib::FileLib
        UtilityConfigLib
        PRIVATE
        MemoryManagerLib::MemoryManagerLib
        spdlog::spdlog
)
