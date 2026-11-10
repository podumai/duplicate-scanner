add_library(HasherFactoryLib)
add_library(HasherFactoryLib::HasherFactoryLib ALIAS HasherFactoryLib)
target_sources(
        HasherFactoryLib
        PUBLIC
        FILE_SET HEADERS
        BASE_DIRS "${CMAKE_SOURCE_DIR}/include"
        FILES "${CMAKE_SOURCE_DIR}/include/duplicate_scanner/utility/hasher_factory/hasher_factory.hpp"
        PRIVATE
        "${CMAKE_CURRENT_SOURCE_DIR}/hasher_factory.cpp"
)
target_link_libraries(
        HasherFactoryLib
        PUBLIC
        UtilityHasherLib::UtilityHasherLib
)
