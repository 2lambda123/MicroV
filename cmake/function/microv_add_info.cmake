#
# Copyright (C) 2020 Assured Information Security, Inc.
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

include(${bsl_SOURCE_DIR}/cmake/colors.cmake)
include(${bsl_SOURCE_DIR}/cmake/build_command.cmake)

# Add Info
#
# Adds MicroV specific info to the info target
#
macro(microv_add_info)
    add_custom_command(TARGET info
        COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_GRN} MicroV Configuration:${BF_COLOR_RST}"
        VERBATIM
    )

    if(MICROV_BUILD_HYPERCALL)
        add_custom_command(TARGET info
            COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_BUILD_HYPERCALL         ${BF_COLOR_GRN}enabled${BF_COLOR_RST}"
            VERBATIM
        )
    else()
        add_custom_command(TARGET info
            COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_BUILD_HYPERCALL         ${BF_COLOR_RED}disabled${BF_COLOR_RST}"
            VERBATIM
        )
    endif()

    if(MICROV_BUILD_SHIM)
        add_custom_command(TARGET info
            COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_BUILD_SHIM              ${BF_COLOR_GRN}enabled${BF_COLOR_RST}"
            VERBATIM
        )
    else()
        add_custom_command(TARGET info
            COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_BUILD_SHIM              ${BF_COLOR_RED}disabled${BF_COLOR_RST}"
            VERBATIM
        )
    endif()

    if(MICROV_BUILD_VMM)
        add_custom_command(TARGET info
            COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_BUILD_VMM               ${BF_COLOR_GRN}enabled${BF_COLOR_RST}"
            VERBATIM
        )
    else()
        add_custom_command(TARGET info
            COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_BUILD_VMM               ${BF_COLOR_RED}disabled${BF_COLOR_RST}"
            VERBATIM
        )
    endif()

    add_custom_command(TARGET info
        COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_MAX_PP_MAPS             ${BF_COLOR_CYN}${MICROV_MAX_PP_MAPS}${BF_COLOR_RST}"
        VERBATIM
    )

    add_custom_command(TARGET info
        COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_MAX_VMS                 ${BF_COLOR_CYN}${MICROV_MAX_VMS}${BF_COLOR_RST}"
        VERBATIM
    )

    add_custom_command(TARGET info
        COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_MAX_VCPUS               ${BF_COLOR_CYN}${MICROV_MAX_VCPUS}${BF_COLOR_RST}"
        VERBATIM
    )

    add_custom_command(TARGET info
        COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_MAX_GPA_SIZE            ${BF_COLOR_CYN}${MICROV_MAX_GPA_SIZE}${BF_COLOR_RST}"
        VERBATIM
    )

    add_custom_command(TARGET info
        COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_MAX_SLOTS               ${BF_COLOR_CYN}${MICROV_MAX_SLOTS}${BF_COLOR_RST}"
        VERBATIM
    )

    add_custom_command(TARGET info
        COMMAND ${CMAKE_COMMAND} -E echo "${BF_COLOR_YLW}   MICROV_INTERRUPT_QUEUE_SIZE    ${BF_COLOR_CYN}${MICROV_INTERRUPT_QUEUE_SIZE}${BF_COLOR_RST}"
        VERBATIM
    )

    add_custom_command(TARGET info
        COMMAND ${CMAKE_COMMAND} -E echo " "
        VERBATIM
    )
endmacro(microv_add_info)
