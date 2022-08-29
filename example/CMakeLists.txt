# SPDX-FileCopyrightText: 2022 Daniel Valcour <fosssweeper@gmail.com>
#
# SPDX-License-Identifier: MIT

# create the executable for the example
set(MPBP_EXAMPLE_SOURCE_FILES
	"main.cpp"
)
list(
    TRANSFORM MPBP_EXAMPLE_SOURCE_FILES
    PREPEND "${CMAKE_CURRENT_SOURCE_DIR}/src/"
)
source_group("sources"
    FILES ${MPBP_EXAMPLE_SOURCE_FILES}
)
add_executable(mpbp_example
    ${MPBP_EXAMPLE_SOURCE_FILES}
)
target_link_libraries(mpbp_example
    PRIVATE
        mpbp
)
set_target_properties(mpbp_example
    PROPERTIES
    OUTPUT_NAME "mpbp example"
    CXX_STANDARD ${MPBP_CXX_STANDARD}
    CXX_STANDARD_REQUIRED TRUE
)
