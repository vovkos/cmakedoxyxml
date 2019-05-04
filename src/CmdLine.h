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

#pragma once

//..............................................................................

enum CmdLineFlag
{
	CmdLineFlag_Help          = 0x0001,
	CmdLineFlag_Version       = 0x0002,
	CmdLineFlag_DoxygenFilter = 0x0004,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct CmdLine
{
	uint_t m_flags;
	sl::String m_outputFileName;
	sl::BoxList<sl::String> m_sourceDirList;
	sl::BoxList<sl::String> m_inputFileNameList;

	CmdLine()
	{
		m_flags = 0;
	}
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

AXL_SELECT_ANY char g_defaultOutputFileName[] = "xml/index.xml";

//..............................................................................

enum CmdLineSwitchKind
{
	CmdLineSwitchKind_Undefined = 0,
	CmdLineSwitchKind_Help,
	CmdLineSwitchKind_Version,
	CmdLineSwitchKind_SourceDir,
	CmdLineSwitchKind_OutputFileName,
	CmdLineSwitchKind_DoxygenFilter,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

AXL_SL_BEGIN_CMD_LINE_SWITCH_TABLE(CmdLineSwitchTable, CmdLineSwitchKind)
	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_Help,
		"h", "help", NULL,
		"Display this help"
		)

	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_Version,
		"v", "version", NULL,
		"Display version of cmakedoxyxml"
		)

	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_SourceDir,
		"S", "source-dir", "<dir>",
		"Add a directory with CMake source files (multiple allowed)"
		)

	AXL_SL_CMD_LINE_SWITCH_2(
		CmdLineSwitchKind_OutputFileName,
		"o", "output", "<file>",
		"Specify master (index) output file"
		)

	AXL_SL_CMD_LINE_SWITCH(
		CmdLineSwitchKind_DoxygenFilter,
		"doxygen-filter", NULL,
		"Specify master (index) output file"
		)
AXL_SL_END_CMD_LINE_SWITCH_TABLE()

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class CmdLineParser: public sl::CmdLineParser<CmdLineParser, CmdLineSwitchTable>
{
	friend class sl::CmdLineParser<CmdLineParser, CmdLineSwitchTable>;

protected:
	CmdLine* m_cmdLine;

public:
	CmdLineParser(CmdLine* cmdLine)
	{
		m_cmdLine = cmdLine;
	}

protected:
	bool
	onValue(const sl::StringRef& value)
	{
		m_cmdLine->m_inputFileNameList.insertTail(value);
		return true;
	}

	bool
	onSwitch(
		SwitchKind switchKind,
		const sl::StringRef& value
		);

	bool
	finalize();
};

//..............................................................................
