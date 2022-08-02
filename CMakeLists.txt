cmake_minimum_required(VERSION 3.19)

PROJECT(mpbp
    VERSION 0.1
    DESCRIPTION "A multi-page bin packing library."
    LANGUAGES CXX
)

set(MPBP_CXX_STANDARD 20)

option(MPBP_BUILD_EXAMPLE "Build the example project" OFF)
option(MPBP_BUILD_TESTS "Build the automatic test framework" OFF)

set(MPBP_SOURCE_FILES
    "Packer.cpp"
)
list(
    TRANSFORM MPBP_SOURCE_FILES
    PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)
source_group("sources"
    FILES ${MPBP_SOURCE_FILES}
)
set(MPBP_INCLUDE_FILES
    "input_rect.hpp"
    "mpbp.hpp"
    "Packer.hpp"
    "pack_rect.hpp"
)
list(
    TRANSFORM MPBP_INCLUDE_FILES
    PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/include/mpbp/"
)
source_group("includes"
    FILES ${MPBP_INCLUDE_FILES}
)

add_library(${PROJECT_NAME} STATIC
    ${MPBP_SOURCE_FILES}
    ${MPBP_INCLUDE_FILES}
)

target_include_directories(${PROJECT_NAME}
    PUBLIC
        "${CMAKE_CURRENT_SOURCE_DIR}/include/"
)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC
    	${MPBP_INCLUDE_FILES}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    CXX_STANDARD ${MPBP_CXX_STANDARD}
    CXX_STANDARD_REQUIRED TRUE
)

if (MPBP_BUILD_TESTS)
	add_subdirectory(test)
endif()

if (MPBP_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()
