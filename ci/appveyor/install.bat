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

@echo off

set DOWNLOAD_DIR=c:\downloads
set DOWNLOAD_DIR_CMAKE=%DOWNLOAD_DIR:\=/%

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: Ragel

mkdir %DOWNLOAD_DIR%\ragel
appveyor DownloadFile %RAGEL_DOWNLOAD_URL% -FileName %DOWNLOAD_DIR%\ragel.exe

echo set (RAGEL_EXE %DOWNLOAD_DIR_CMAKE%/ragel.exe) >> paths.cmake

:: . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

:: Get rid of Xamarin annoying build warnings

del "c:\Program Files (x86)\MSBuild\14.0\Microsoft.Common.targets\ImportAfter\Xamarin.Common.targets"
del "c:\Program Files (x86)\MSBuild\4.0\Microsoft.Common.targets\ImportAfter\Xamarin.Common.targets"
