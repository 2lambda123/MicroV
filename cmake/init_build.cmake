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

add_custom_target(run_all_integration_tests)

include(FetchContent)
set(FETCHCONTENT_BASE_DIR ${CMAKE_BINARY_DIR}/depend)

include(${CMAKE_CURRENT_LIST_DIR}/depend/hypervisor.cmake)

include(${bsl_SOURCE_DIR}/cmake/config/all_projects.cmake)
include(${bsl_SOURCE_DIR}/cmake/config/cmake.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/config/default.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/validate.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/target/info.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/target/reload.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/target/shim_build.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/target/shim_load.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/target/shim_unload.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/target/shim_clean.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/target/shim_quick.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/target/shim_reload.cmake)

include(${CMAKE_CURRENT_LIST_DIR}/write_constants.cmake)

include(${bsl_SOURCE_DIR}/cmake/build_types.cmake)
include(${bsl_SOURCE_DIR}/cmake/find_programs.cmake)
