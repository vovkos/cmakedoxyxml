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
#include "Module.h"

//..............................................................................

ModuleItem::ModuleItem()
{
	m_itemKind = ModuleItemKind_Undefined;
	m_module = NULL;
	m_doxyBlock = NULL;
}

dox::Block*
ModuleItem::ensureDoxyBlock()
{
	dox::Block* block = m_module->getDoxyHost()->getItemBlock(this);
	ASSERT(block == m_doxyBlock);
	return block;
}

void
ModuleItem::printDoxygenFilterComment(const sl::StringRef& indent)
{
	if (m_doxyBlock)
		printf("%s/*! %s */\n", indent.sz(), m_doxyBlock->getSource().getTrimmedString().sz());
}

//..............................................................................

sl::String
Variable::createDoxyRefId()
{
	sl::String refId = m_itemKind == ModuleItemKind_FunctionParam ? "param_" : "variable_";
	refId += m_name;
	refId.makeLowerCase();

	return m_module->m_doxyModule.adjustRefId(refId);
}

bool
Variable::generateDocumentation(
	const sl::StringRef& outputDir,
	sl::String* itemXml,
	sl::String* indexXml
	)
{
	ensureDoxyBlock();

	itemXml->format("<memberdef kind='variable' id='%s'>\n", m_doxyBlock->getRefId ().sz());
	itemXml->appendFormat("<name>%s</name>\n", m_name.sz());
	itemXml->append(m_doxyBlock->getImportString());
	itemXml->append(m_doxyBlock->getDescriptionString());
	itemXml->append(getLocationString());
	itemXml->append("</memberdef>\n");

	return true;
}

void
Variable::generateDoxygenFilterOutput(const sl::StringRef& indent)
{
	printDoxygenFilterComment();
	printf("%sint %s", indent.sz(), m_name.sz());

	if (m_itemKind != ModuleItemKind_FunctionParam)
		printf(";\n");
}

//..............................................................................

sl::String
Function::createDoxyRefId()
{
	sl::String refId = "function_" + m_name;
	refId.replace('.', '_');
	refId.replace(':', '_');
	refId.makeLowerCase();

	return m_module->m_doxyModule.adjustRefId(refId);
}

bool
Function::generateDocumentation(
	const sl::StringRef& outputDir,
	sl::String* itemXml,
	sl::String* indexXml
	)
{
	ensureDoxyBlock();

	itemXml->format("<memberdef kind='function' id='%s'>\n", m_doxyBlock->getRefId ().sz());
	itemXml->appendFormat("<name>%s</name>\n", m_name.sz());

	size_t count = m_paramArray.getCount();
	for (size_t i = 0; i < count; i++)
	{
		Variable* arg = m_paramArray[i];

		itemXml->appendFormat(
			"<param>\n"
			"<declname>%s</declname>\n",
			arg->m_name.sz()
			);

		if (arg->m_doxyBlock)
			itemXml->append(arg->m_doxyBlock->getDescriptionString());

		itemXml->append("</param>\n");
	}

	itemXml->append(m_doxyBlock->getImportString());
	itemXml->append(m_doxyBlock->getDescriptionString());
	itemXml->append(getLocationString());
	itemXml->append("</memberdef>\n");
	return true;
}

void
Function::generateDoxygenFilterOutput(const sl::StringRef& indent)
{
	printDoxygenFilterComment();
	printf("int %s(\n", m_name.sz());

	if (!m_paramArray.isEmpty())
	{
		m_paramArray[0]->generateDoxygenFilterOutput("\t");

		size_t count = m_paramArray.getCount();
		for (size_t i = 1; i < count; i++)
		{
			printf(",\n");
			m_paramArray[i]->generateDoxygenFilterOutput("\t");
		}

		printf("\n\t");
	}

	printf(");\n\n");
}

//..............................................................................

bool
Module::generateGlobalNamespaceDocumentation(
	const sl::StringRef& outputDir,
	sl::String* itemXml,
	sl::String* indexXml
	)
{
	bool result;

	dox::Host* host = m_doxyModule.getHost();

	*indexXml = "<compound kind='file' refid='global'><name>global</name></compound>\n";

	*itemXml =
		"<compounddef kind='file' id='global' language='Lua'>\n"
		"<compoundname>global</compoundname>\n";

	static char compoundFileHdr[] =
		"<?xml version='1.0' encoding='UTF-8' standalone='no'?>\n"
		"<doxygen>\n";

	static char compoundFileTerm[] = "</doxygen>\n";

	sl::String sectionDef;
	sl::String memberXml;

	sl::StringHashTableIterator<ModuleItem*> it = m_itemMap.getHead();
	for (; it; it++)
	{
		ModuleItem* item = it->m_value;

		result = item->generateDocumentation(outputDir, &memberXml, indexXml);
		if (!result)
			return false;

		if (memberXml.isEmpty())
			continue;

		dox::Block* doxyBlock = host->getItemBlock(item);
		dox::Group* doxyGroup = doxyBlock->getGroup();
		if (doxyGroup)
			doxyGroup->addItem(item);

		sectionDef.append(memberXml);
	}

	itemXml->append("<sectiondef>\n");
	itemXml->append(sectionDef);
	itemXml->append("</sectiondef>\n");
	itemXml->append("</compounddef>\n");
	return true;
}

void
Module::generateDoxygenFilterOutput()
{
	sl::StringHashTableIterator<ModuleItem*> it = m_itemMap.getHead();
	for (; it; it++)
		it->m_value->generateDoxygenFilterOutput();
}

//..............................................................................
