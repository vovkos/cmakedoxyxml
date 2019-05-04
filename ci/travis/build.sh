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

THIS_DIR=`pwd`

mkdir axl/build
pushd axl/build
cmake .. -DTARGET_CPU=$TARGET_CPU -DCMAKE_BUILD_TYPE=$BUILD_CONFIGURATION
make
popd

echo "set (AXL_CMAKE_DIR $THIS_DIR/axl/cmake $THIS_DIR/axl/build/cmake)" >> paths.cmake

mkdir graco/build
pushd graco/build
cmake .. -DTARGET_CPU=$TARGET_CPU -DCMAKE_BUILD_TYPE=$BUILD_CONFIGURATION
make
popd

echo "set (GRACO_CMAKE_DIR $THIS_DIR/graco/cmake $THIS_DIR/graco/build/cmake)" >> paths.cmake

mkdir build
pushd build
cmake .. -DTARGET_CPU=$TARGET_CPU -DCMAKE_BUILD_TYPE=$BUILD_CONFIGURATION
make

# ctest --output-on-failure
