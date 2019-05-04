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

class Module;
class Parser;

//..............................................................................

class DoxyHost: public dox::Host
{
protected:
	Module* m_module;
	Parser* m_parser;

public:
	DoxyHost()
	{
		setup(NULL, NULL);
	}

	void
	setup(
		Module* module,
		Parser* parser
		)
	{
		m_module = module;
		m_parser = parser;
	}

	virtual
	dox::Block*
	findItemBlock(handle_t item);

	virtual
	dox::Block*
	getItemBlock(handle_t item);

	virtual
	void
	setItemBlock(
		handle_t item,
		dox::Block* block
		);

	virtual
	sl::String
	createItemRefId(handle_t item);

	virtual
	sl::StringRef
	getItemCompoundElementName(handle_t item)
	{
		return NULL; // no compounds in cmake
	}

	virtual
	handle_t
	findItem(
		const sl::StringRef& name,
		size_t overloadIdx
		);

	virtual
	handle_t
	getCurrentNamespace();

	virtual
	bool
	generateGlobalNamespaceDocumentation(
		const sl::StringRef& outputDir,
		sl::String* itemXml,
		sl::String* indexXml
		);
};

//..............................................................................
