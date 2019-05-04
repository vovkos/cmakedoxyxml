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
#include "DoxyHost.h"
#include "Lexer.h"
#include "Parser.llk.h"
#include "Parser.llk.cpp"
#include "version.h"

#define _PRINT_USAGE_IF_NO_ARGUMENTS 1
#define _PRINT_MODULE 0

//..............................................................................

void
printVersion()
{
	printf(
		"cmakedoxyxml v%d.%d.%d (%s%s)\n",
		VERSION_MAJOR,
		VERSION_MINOR,
		VERSION_REVISION,
		AXL_CPU_STRING,
		AXL_DEBUG_SUFFIX
		);
}

void
printUsage()
{
	printVersion();

	sl::String helpString = CmdLineSwitchTable::getHelpString();
	printf("Usage: cmakedoxyxml [options] <source.cmake>...\n%s", helpString.sz());
}

bool
parseFile(
	const sl::StringRef& fileName,
	Module* module
	)
{
	io::SimpleMappedFile file;

	bool result = file.open(fileName, io::FileFlag_ReadOnly);
	if (!result)
		return false;

	Lexer lexer;
	lexer.m_channelMask = TokenChannelMask_All; // include doxygen comments

	Parser parser(module);
	((DoxyHost*)module->getDoxyHost())->setup(module, &parser);

	sl::String source((const char*)file.p(), file.getMappingSize());
	lexer.create(fileName, source);
	parser.create(fileName);
	module->addSource(source); // need to keep sources alive since we use StringRef's in module items

	for (;;)
	{
		const Token* token = lexer.getToken();

		sl::StringRef comment;
		ModuleItem* lastDeclaredItem;

		switch (token->m_token)
		{
		case TokenKind_Error:
			err::setFormatStringError("invalid character '\\x%02x'", (uchar_t) token->m_data.m_integer);
			lex::pushSrcPosError(fileName, token->m_pos);
			return false;

		case TokenKind_DoxyComment_sl:
		case TokenKind_DoxyComment_ml:
			comment = token->m_data.m_string;

			lastDeclaredItem = NULL;

			if (!comment.isEmpty() && comment[0] == '<')
			{
				lastDeclaredItem = parser.m_lastDeclaredItem;
				comment = comment.getSubString(1);
			}

			parser.m_doxyParser.addComment(
				comment,
				token->m_pos,
				token->m_tokenKind == TokenKind_DoxyComment_sl,
				lastDeclaredItem
				);

			break;

		default:
			result = parser.parseToken(token);
			if (!result)
			{
				lex::ensureSrcPosError(fileName, token->m_pos);
				return false;
			}
		}

		if (token->m_token == TokenKind_Eof) // EOF token must be parsed
			break;

		lexer.nextToken();
	}

	return true;
}

bool
run(CmdLine* cmdLine)
{
	static char cmakeSuffix[] = ".cmake";
	static char doxSuffix[] = ".dox";

	bool result;

	DoxyHost doxyHost;
	Module module(&doxyHost);

	sl::ConstBoxIterator<sl::String> it = cmdLine->m_inputFileNameList.getHead();
	for (; it; it++)
	{
		const sl::String& fileName = *it;

		if (!(cmdLine->m_flags & CmdLineFlag_DoxygenFilter))
			printf("Parsing %s...\n", fileName.sz());

		result = parseFile(fileName, &module);
		if (!result)
			return false;
	}

	it = cmdLine->m_sourceDirList.getHead();
	for (; it; it++)
	{
		sl::String dir = *it;
		if (dir.isEmpty())
			continue;

		if (dir[dir.getLength() - 1])
			dir += '/';

		io::FileEnumerator fileEnum;
		bool result = fileEnum.openDir(dir);
		if (!result)
		{
			printf("warning: %s\n", err::getLastErrorDescription().sz());
			continue;
		}

		while (fileEnum.hasNextFile())
		{
			sl::String filePath = dir + fileEnum.getNextFileName();
			if (io::isDir(filePath))
				continue;

			if (filePath.isSuffix(cmakeSuffix) || filePath.isSuffix(doxSuffix))
			{
				result = parseFile(filePath, &module);
				if (!result)
					return false;
			}
		}
	}

	if (cmdLine->m_flags & CmdLineFlag_DoxygenFilter)
		module.generateDoxygenFilterOutput();

	if (cmdLine->m_outputFileName.isEmpty())
		return true;

	sl::String outputFileName = io::getFileName(cmdLine->m_outputFileName);
	sl::String outputDir = io::getDir(cmdLine->m_outputFileName);

	module.m_doxyModule.generateDocumentation(outputDir, outputFileName);

	return true;
}

//..............................................................................

#if (_AXL_OS_WIN)
int
wmain(
	int argc,
	wchar_t* argv[]
	)
#else
int
main(
	int argc,
	char* argv[]
	)
#endif
{
	bool result;

#if _AXL_OS_POSIX
	setvbuf(stdout, NULL, _IOLBF, 1024);
#endif

	g::getModule()->setTag("cmakedoxyxml");
	lex::registerParseErrorProvider();

	CmdLine cmdLine;
	CmdLineParser parser(&cmdLine);

#if _PRINT_USAGE_IF_NO_ARGUMENTS
	if (argc < 2)
	{
		printUsage();
		return 0;
	}
#endif

	result = parser.parse(argc, argv);
	if (!result)
	{
		fprintf(stderr, "error parsing command line: %s\n", err::getLastErrorDescription().sz());
		return -1;
	}

	if (cmdLine.m_flags & CmdLineFlag_Help)
		printUsage();
	else if (cmdLine.m_flags & CmdLineFlag_Version)
		printVersion();
	else
	{
		result = run(&cmdLine);
		if (!result)
		{
			fprintf(stderr, "error: %s\n", err::getLastErrorDescription().sz());
			return -1;
		}
	}

	return 0;
}

//..............................................................................
