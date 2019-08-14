#...............................................................................
#
#  This file is part of the CMakeDoxyXML toolkit.
#
#  CMakeDoxyXML is distributed under the MIT license.
#  For details see accompanying license.txt file,
#  the public copy of which is also available at:
#  http://tibbo.com/downloads/archive/cmakedoxyxml/license.txt
#
#...............................................................................

project(cmakedoxyxml)

cmake_minimum_required(VERSION 3.3)

include(axl_cmake.cmake NO_POLICY_SCOPE)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

include(version.cmake)

set(BIN_BASE_DIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(BIN_DIR      ${CMAKE_CURRENT_BINARY_DIR}/bin/${CONFIGURATION})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BIN_BASE_DIR}/${CONFIGURATION_SCG})
set(CMAKEDOXYXML_INSTALL_BIN_SUBDIR bin)

add_subdirectory(src)

#...............................................................................
