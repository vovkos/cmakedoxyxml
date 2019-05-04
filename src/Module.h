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

#include "Lexer.h"

class Module;
struct Table;

//..............................................................................

enum ValueKind
{
	ValueKind_Empty,
	ValueKind_Expression,
	ValueKind_Constant,
	ValueKind_Variable,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct Value
{
	Token::Pos m_firstTokenPos;
	Token::Pos m_lastTokenPos;
	ValueKind m_valueKind;
	sl::StringRef m_source;

	Value()
	{
		m_valueKind = ValueKind_Empty;
	}

	bool
	isEmpty() const
	{
		return m_valueKind == ValueKind_Empty;
	}

	void
	clear();

	void
	setFirstToken(
		const Token::Pos& pos,
		ValueKind valueKind = ValueKind_Expression
		);

	void
	appendSource(
		const Token::Pos& pos,
		ValueKind valueKind = ValueKind_Expression
		);
};

//..............................................................................

enum ModuleItemKind
{
	ModuleItemKind_Undefined,
	ModuleItemKind_Variable,
	ModuleItemKind_FunctionParam,
	ModuleItemKind_Function,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct ModuleItem: sl::ListLink
{
	ModuleItemKind m_itemKind;
	Module* m_module;
	sl::String m_fileName;
	Token::Pos m_pos;
	sl::StringRef m_name;
	dox::Block* m_doxyBlock;

	ModuleItem();

	virtual
	~ModuleItem()
	{
	}

	dox::Block*
	ensureDoxyBlock();

	virtual
	sl::String
	createDoxyRefId() = 0;

	virtual
	bool
	generateDocumentation(
		const sl::StringRef& outputDir,
		sl::String* itemXml,
		sl::String* indexXml
		) = 0;

	virtual
	void
	generateDoxygenFilterOutput(const sl::StringRef& indent = "") = 0;

	sl::String
	getLocationString()
	{
		return sl::formatString("<location file='%s' line='%d' col='%d'/>\n",
			m_fileName.sz(),
			m_pos.m_line + 1,
			m_pos.m_col + 1
			);
	}

	void
	printDoxygenFilterComment(const sl::StringRef& indent = "");
};

//..............................................................................

struct Variable: ModuleItem
{
	Value m_index;
	Value m_initializer;

	Variable()
	{
		m_itemKind = ModuleItemKind_Variable;
	}

	virtual
	sl::String
	createDoxyRefId();

	virtual
	bool
	generateDocumentation(
		const sl::StringRef& outputDir,
		sl::String* itemXml,
		sl::String* indexXml
		);

	virtual
	void
	generateDoxygenFilterOutput(const sl::StringRef& indent);
};

//..............................................................................

struct FunctionParamArray
{
	sl::Array<Variable*> m_array;
	bool m_isVarArg;

	FunctionParamArray()
	{
		m_isVarArg = false;
	}
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

struct Function: ModuleItem
{
	FunctionParamArray m_paramArray;

	Function()
	{
		m_itemKind = ModuleItemKind_Variable;
	}

	virtual
	sl::String
	createDoxyRefId();

	virtual
	bool
	generateDocumentation(
		const sl::StringRef& outputDir,
		sl::String* itemXml,
		sl::String* indexXml
		);

	virtual
	void
	generateDoxygenFilterOutput(const sl::StringRef& indent);
};

//..............................................................................

class Module
{
	friend class Parser;

protected:
	sl::List<ModuleItem> m_itemList;
	sl::StringHashTable<ModuleItem*> m_itemMap;
	sl::BoxList<sl::String> m_sourceList;

public:
	dox::Module m_doxyModule;

public:
	Module(dox::Host* doxyHost):
		m_doxyModule(doxyHost)
	{
	}

	dox::Host* getDoxyHost()
	{
		return m_doxyModule.getHost();
	}

	ModuleItem*
	findItem(const sl::StringRef& name)
	{
		return m_itemMap.findValue(name, NULL);
	}

	bool
	addSource(const sl::String& source)
	{
		return m_sourceList.insertTail(source);
	}

	bool
	generateGlobalNamespaceDocumentation(
		const sl::StringRef& outputDir,
		sl::String* itemXml,
		sl::String* indexXml
		);

	void
	generateDoxygenFilterOutput();
};

//..............................................................................
