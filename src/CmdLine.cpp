//..............................................................................
//
//  This file is part of the CMakeDoxyXML toolkit.
//
//  CMakeDoxyXML is distributed under the MIT license.
//  For details see accompanying license.txt file,
//  the public copy of which is also available at:
//  http://tibbo.com/downloads/archive/cmakedoxyxml/license.txt
//
//..............................................................................

#include "pch.h"
#include "CmdLine.h"

//..............................................................................

bool
CmdLineParser::onSwitch(
	SwitchKind switchKind,
	const sl::StringRef& value
) {
	switch (switchKind) {
	case CmdLineSwitchKind_Help:
		m_cmdLine->m_flags |= CmdLineFlag_Help;
		break;

	case CmdLineSwitchKind_Version:
		m_cmdLine->m_flags |= CmdLineFlag_Version;
		break;

	case CmdLineSwitchKind_SourceDir:
		m_cmdLine->m_sourceDirList.insertTail(value);
		break;

	case CmdLineSwitchKind_OutputFileName:
		m_cmdLine->m_outputFileName = value;
		break;

	case CmdLineSwitchKind_DoxygenFilter:
		m_cmdLine->m_flags |= CmdLineFlag_DoxygenFilter;
		break;
	}

	return true;
}

bool
CmdLineParser::finalize() {
	if (m_cmdLine->m_inputFileNameList.isEmpty() &&
		m_cmdLine->m_sourceDirList.isEmpty()) {
		if (!m_cmdLine->m_flags)
			m_cmdLine->m_flags = CmdLineFlag_Help;
	} else {
		if (m_cmdLine->m_outputFileName.isEmpty() && (!(m_cmdLine->m_flags & CmdLineFlag_DoxygenFilter)))
			m_cmdLine->m_outputFileName = g_defaultOutputFileName;
	}

	return true;
}

//..............................................................................
