cmake_minimum_required(VERSION 3.19)

PROJECT(mpbp
    VERSION 0.1
    DESCRIPTION "A multi-page bin packing library."
    LANGUAGES CXX
)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(MPBP_CXX_STANDARD 20)

option(MPBP_BUILD_EXAMPLE "Build the mpbp example project" OFF)
option(MPBP_BUILD_TESTS "Build the mpbp automatic test framework" OFF)
option(MPBP_INSTALL "Generate the mpbp installation target." ON)

set(MPBP_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(MPBP_INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include/")

configure_file("${MPBP_SOURCE_DIR}/configuration.h.in" "${MPBP_INCLUDE_DIR}/mpbp/configuration.h")

set(MPBP_SOURCE_FILES
    "Packer.cpp"
)
list(
    TRANSFORM MPBP_SOURCE_FILES
    PREPEND "${MPBP_SOURCE_DIR}"
)
source_group("sources"
    FILES ${MPBP_SOURCE_FILES}
)
set(MPBP_INCLUDE_FILES
    "input_rect.hpp"
    "mpbp.hpp"
    "Packer.hpp"
    "pack_rect.hpp"
    "configuration.h"
)
list(
    TRANSFORM MPBP_INCLUDE_FILES
    PREPEND "${MPBP_INCLUDE_DIR}/mpbp/"
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
        "$<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>"
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
	add_subdirectory(test)
endif()

if (MPBP_BUILD_EXAMPLE)
    add_subdirectory(example)
endif()

if (MPBP_INSTALL)
    	include(GNUInstallDirs)
	install(TARGETS ${PROJECT_NAME}
       		EXPORT ${PROJECT_NAME}
		LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
		ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
		RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
	)
   	install(FILES ${MPBP_INCLUDE_FILES} 
   		DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
   	)
endif()
