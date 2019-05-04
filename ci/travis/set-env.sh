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

if [ "$TRAVIS_OS_NAME" == "linux" ]; then
	CMAKE_VERSION=3.3.2
	CMAKE_VERSION_DIR=v3.3
	CMAKE_OS=Linux-x86_64

	export CMAKE_TAR=cmake-$CMAKE_VERSION-$CMAKE_OS.tar.gz
	export CMAKE_URL=http://www.cmake.org/files/$CMAKE_VERSION_DIR/$CMAKE_TAR
	export CMAKE_DIR=$TRAVIS_BUILD_DIR/cmake-$CMAKE_VERSION
	export PATH=$CMAKE_DIR/bin:$PATH
elif [ "$TRAVIS_OS_NAME" == "osx" ]; then

	# it's not as easy to install lua-5.2 side-by-side with lua-5.3 on OSX
	# we better use static linking to lua as to avoid versioning issues

	LUA_VERSION=5.3.4
	LUA_LIB_NAME=lua53
	LUA_OS=MacOS1011

	export LUA_TAR=lua-${LUA_VERSION}_${LUA_OS}_lib.tar.gz
	export LUA_URL=https://sourceforge.net/projects/luabinaries/files/$LUA_VERSION/Other%20Libraries/${LUA_TAR}/download
	export LUA_DIR=$TRAVIS_BUILD_DIR/lua-$LUA_VERSION
fi
