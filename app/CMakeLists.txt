add_executable(DuplicateScanner duplicate_scanner.cpp)
target_link_libraries(
        DuplicateScanner
        PRIVATE
        CmdLineParserLib::CmdLineParserLib
        ScannerLib::ScannerLib
        spdlog::spdlog
        Boost::boost
)
set_target_properties(
        DuplicateScanner
        PROPERTIES
        OUTPUT_NAME "duplicate-scanner"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
