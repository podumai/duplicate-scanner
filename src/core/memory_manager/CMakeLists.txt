add_library(MemoryManagerLib)
add_library(MemoryManagerLib::MemoryManagerLib ALIAS MemoryManagerLib)
target_sources(
        MemoryManagerLib
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_SOURCE_DIR}/include"
        FILES "${CMAKE_SOURCE_DIR}/include/duplicate_scanner/core/memory_manager/memory_manager.hpp"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/memory_manager.cpp"
)
target_link_libraries(
        MemoryManagerLib
        PRIVATE
        spdlog::spdlog
)
