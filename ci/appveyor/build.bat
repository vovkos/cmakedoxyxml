::..............................................................................
::
::  This file is part of the CMakeDoxyXML toolkit.
::
::  CMakeDoxyXML is distributed under the MIT license.
::  For details see accompanying license.txt file,
::  the public copy of which is also available at:
::  http://tibbo.com/downloads/archive/cmakedoxyxml/license.txt
::
::..............................................................................

set THIS_DIR=%CD%
set THIS_DIR_CMAKE=%THIS_DIR:\=/%

mkdir axl\build
cd axl\build
cmake .. %CMAKE_CONFIGURE_FLAGS%
cmake --build . %CMAKE_BUILD_FLAGS%

cd %THIS_DIR%
echo set (AXL_CMAKE_DIR %THIS_DIR_CMAKE%/axl/cmake %THIS_DIR_CMAKE%/axl/build/cmake) >> paths.cmake

mkdir graco\build
cd graco\build
cmake .. %CMAKE_CONFIGURE_FLAGS%
cmake --build . %CMAKE_BUILD_FLAGS%

cd %THIS_DIR%
echo set (GRACO_CMAKE_DIR %THIS_DIR_CMAKE%/graco/cmake %THIS_DIR_CMAKE%/graco/build/cmake) >> paths.cmake

mkdir build
cd build
cmake .. %CMAKE_CONFIGURE_FLAGS%
cmake --build . %CMAKE_BUILD_FLAGS%
