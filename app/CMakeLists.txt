add_executable(DuplicateScanner)
target_sources(
        DuplicateScanner
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/duplicate_scanner.cpp"
)
target_link_libraries(
        DuplicateScanner
        PRIVATE
        CmdLineParserLib::CmdLineParserLib
        ScannerLib::ScannerLib
        spdlog::spdlog
        boost::boost
)
set_target_properties(
        DuplicateScanner
        PROPERTIES
        OUTPUT_NAME "duplicate-scanner"
        RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin"
)
