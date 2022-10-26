# SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
#
# SPDX-License-Identifier: MIT

cmake_minimum_required(VERSION 3.19)

PROJECT(mpbp
    VERSION 1.0.2
    DESCRIPTION "A multi-page bin packing library."
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MPBP_CXX_STANDARD 20)

option(MPBP_BUILD_DOCUMENTATION "Build the documentation using Doxygen." ON)
option(MPBP_BUILD_LIBRARY "Build the mpbp library" ON)
option(MPBP_BUILD_EXAMPLE "Build the mpbp example project. Requires MPBP_BUILD_LIBRARY to be ON." OFF)
option(MPBP_BUILD_TESTS "Build the mpbp automatic test framework. Requires MPBP_BUILD_LIBRARY to be ON." OFF)
option(MPBP_INSTALL "Generate the mpbp installation target. Requires MPBP_BUILD_LIBRARY to be ON." ON)

set(MPBP_CMAKE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}")
set(MPBP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(MPBP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")

configure_file("${MPBP_SOURCE_DIR}/configuration.h.in" "${MPBP_INCLUDE_DIR}/mpbp/configuration.h")

set(MPBP_SOURCE_FILES
    "Packer.cpp"
    "Rect.cpp"
    "Space.cpp"
)
list(
    TRANSFORM MPBP_SOURCE_FILES
    PREPEND "${MPBP_SOURCE_DIR}"
)
source_group("sources"
    FILES ${MPBP_SOURCE_FILES}
)
set(MPBP_INCLUDE_FILES
    "configuration.h"
    "mpbp.hpp"
    "Packer.hpp"
    "Rect.hpp"
    "Space.hpp"
)
list(
    TRANSFORM MPBP_INCLUDE_FILES
    PREPEND "${MPBP_INCLUDE_DIR}mpbp/"
)
source_group("includes"
    FILES ${MPBP_INCLUDE_FILES}
)

add_library(${PROJECT_NAME} STATIC
    ${MPBP_SOURCE_FILES}
    ${MPBP_INCLUDE_FILES}
)

add_library(mpbp::mpbp ALIAS ${PROJECT_NAME})

target_include_directories(${PROJECT_NAME}
    PUBLIC
        "$<BUILD_INTERFACE:${MPBP_INCLUDE_DIR}>"
)

target_precompile_headers(${PROJECT_NAME}
    PUBLIC
        ${MPBP_INCLUDE_FILES}
)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    OUTPUT_NAME "mpbp"
    CXX_STANDARD ${MPBP_CXX_STANDARD}
    CXX_STANDARD_REQUIRED TRUE
)

if (MPBP_BUILD_TESTS)
    if (NOT MPBP_BUILD_LIBRARY)
        message(SEND_ERROR "Unable to generate mpbp test executable: mpbp library not built.")
    endif()
    add_subdirectory(test)
endif()

if (MPBP_BUILD_EXAMPLE)
    if (NOT MPBP_BUILD_LIBRARY)
        message(SEND_ERROR "Unable to generate mpbp example executable: mpbp library not built.")
    endif()
    add_subdirectory(example)
endif()

if (MPBP_BUILD_DOCUMENTATION)
    add_subdirectory(docs)
endif()

if (MPBP_INSTALL)
    if (NOT MPBP_BUILD_LIBRARY)
        message(SEND_ERROR "Unable to install mpbp: mpbp library not built.")
    endif()
    include(GNUInstallDirs)
    target_include_directories(${PROJECT_NAME}
        PUBLIC
            "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
    )
    install(TARGETS ${PROJECT_NAME}
        EXPORT mpbpTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
    install(EXPORT mpbpTargets FILE mpbpConfig.cmake
        EXPORT_LINK_INTERFACE_LIBRARIES
        DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/mpbp/"
        NAMESPACE mpbp::
    )
    install(FILES ${MPBP_INCLUDE_FILES}
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
    )
    export(TARGETS ${PROJECT_NAME}
        NAMESPACE mpbp::
        FILE "${CMAKE_CURRENT_BINARY_DIR}/mpbpConfig.cmake"
    )
endif()
