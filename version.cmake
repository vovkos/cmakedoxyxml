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

set(CMAKEDOXYXML_VERSION_MAJOR     1)
set(CMAKEDOXYXML_VERSION_MINOR     0)
set(CMAKEDOXYXML_VERSION_REVISION  0)
set(CMAKEDOXYXML_VERSION_TAG        )

set(CMAKEDOXYXML_VERSION_FULL "${CMAKEDOXYXML_VERSION_MAJOR}.${CMAKEDOXYXML_VERSION_MINOR}.${CMAKEDOXYXML_VERSION_REVISION}")

if(NOT "${CMAKEDOXYXML_VERSION_TAG}" STREQUAL "")
	set(CMAKEDOXYXML_VERSION_TAG_SUFFIX  " ${CMAKEDOXYXML_VERSION_TAG}")
	set(CMAKEDOXYXML_VERSION_FILE_SUFFIX "${CMAKEDOXYXML_VERSION_FULL}-${CMAKEDOXYXML_VERSION_TAG}")
else()
	set(CMAKEDOXYXML_VERSION_TAG_SUFFIX)
	set(CMAKEDOXYXML_VERSION_FILE_SUFFIX "${CMAKEDOXYXML_VERSION_FULL}")
endif()

string(TIMESTAMP CMAKEDOXYXML_VERSION_YEAR  "%Y")
string(TIMESTAMP CMAKEDOXYXML_VERSION_MONTH "%m")
string(TIMESTAMP CMAKEDOXYXML_VERSION_DAY   "%d")

set(CMAKEDOXYXML_VERSION_COMPANY "Tibbo Technology Inc")
set(CMAKEDOXYXML_VERSION_YEARS   "2019-${CMAKEDOXYXML_VERSION_YEAR}")

#...............................................................................
