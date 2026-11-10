add_library(UtilityConfigLib INTERFACE)
target_sources(
        UtilityConfigLib
        INTERFACE
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_SOURCE_DIR}/include/"
        FILES "${CMAKE_SOURCE_DIR}/include/duplicate_scanner/utility/config/config.hpp"
)
