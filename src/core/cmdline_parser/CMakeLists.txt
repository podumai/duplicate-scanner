add_library(CmdLineParserLib)
add_library(CmdLineParserLib::CmdLineParserLib ALIAS CmdLineParserLib)
target_sources(
        CmdLineParserLib
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_SOURCE_DIR}/include"
        FILES "${CMAKE_SOURCE_DIR}/include/duplicate_scanner/core/cmdline_parser/cmdline_parser.hpp"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/cmdline_parser.cpp"
)
target_link_libraries(
        CmdLineParserLib
        PUBLIC
        Boost::boost
        UtilityConfigLib
        ScannerLib
)
