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

#
# app folder
#

set(
	APP_H_LIST
	CmdLine.h
	DoxyHost.h
	Lexer.h
	Module.h
	version.h.in
)

set(
	APP_CPP_LIST
	main.cpp
	CmdLine.cpp
	DoxyHost.cpp
	Lexer.cpp
	Parser.cpp
	Module.cpp
)

set(
	APP_RL_LIST
	Lexer.rl
)

set(
	APP_LLK_LIST
	Parser.llk
)

source_group(
	app
	FILES
	${APP_H_LIST}
	${APP_CPP_LIST}
	${APP_RL_LIST}
	${APP_LLK_LIST}
)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# res folder
#

set(
	RES_RC_LIST
	res.rc
)

source_group(
	res
	FILES
	${RES_RC_LIST}
)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# gen folder
#

set(GEN_DIR ${CMAKE_CURRENT_BINARY_DIR}/gen)
file(MAKE_DIRECTORY ${GEN_DIR})

axl_push_and_set(CMAKE_CURRENT_BINARY_DIR ${GEN_DIR})

configure_file(
	version.h.in
	${GEN_DIR}/version.h
)

add_ragel_step(
	Lexer.rl.cpp
	Lexer.rl
)

add_graco_double_step(
	Parser.llk.h
	Parser.llk.cpp
	CppParser.h.in
	CppParser.cpp.in
	Parser.llk
)

axl_pop(CMAKE_CURRENT_BINARY_DIR)

set(
	GEN_H_LIST
	${GEN_DIR}/version.h
	${GEN_DIR}/Parser.llk.h
)

set(
	GEN_CPP_LIST
	${GEN_DIR}/Lexer.rl.cpp
	# ${GEN_DIR}/Parser.llk.cpp  # currently, cmake can't handle double-file output
)

axl_exclude_from_build(${GEN_CPP_LIST})  # include "*.rl.cpp" & "*.llk.cpp" manually

source_group(
	gen
	FILES
	${GEN_H_LIST}
	${GEN_CPP_LIST}
)

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# pch folder
#

set(PCH_H   pch.h)

source_group(
	pch
	FILES
	${PCH_H}
	REGULAR_EXPRESSION cmake_pch
)

#...............................................................................
#
# cmakedoxyxml (cmake-to-doxygen-xml) documentation comments extraction tool
#

include_directories(
	${GRACO_INC_DIR}
	${AXL_INC_DIR}
	${CMAKE_CURRENT_LIST_DIR}
	${GEN_DIR}
)

link_directories(
	${AXL_LIB_DIR}
)

add_executable(
	cmakedoxyxml
	${PCH_H}
	${APP_H_LIST}
	${APP_CPP_LIST}
	${APP_RL_LIST}
	${APP_LLK_LIST}
	${RES_RC_LIST}
	${GEN_H_LIST}
	${GEN_CPP_LIST}
)

target_precompile_headers(
	cmakedoxyxml
	PRIVATE
	${PCH_H}
)

target_link_libraries(
	cmakedoxyxml
	axl_lex
	axl_io
	axl_dox
	axl_core
)

if(UNIX)
	target_link_libraries(
		cmakedoxyxml
		pthread
		dl
	)

	if(NOT APPLE)
		target_link_libraries(
			cmakedoxyxml
			rt
		)
	endif()
endif()

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

install(
	TARGETS cmakedoxyxml
	DESTINATION ${CMAKEDOXYXML_INSTALL_BIN_SUBDIR}
)

#...............................................................................
