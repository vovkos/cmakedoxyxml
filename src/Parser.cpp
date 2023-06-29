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
#include "Parser.llk.h"
#include "Parser.llk.cpp"

//..............................................................................

Parser::Parser(Module* module):
	m_doxyParser(&module->m_doxyModule) {
	m_module = module;
	m_lastDeclaredItem = NULL;
	m_scopeLevel = 0;
}

Variable*
Parser::declareVariableEx(
	ModuleItemKind itemKind,
	const Token::Pos& pos,
	const sl::StringRef& name
) {
	if (itemKind == ModuleItemKind_Variable && m_module->m_itemMap.find(name)) // re-declaration
		return NULL;

	Variable* variable = new Variable;
	variable->m_itemKind = itemKind;
	variable->m_name = name;

	finalizeDeclaration(
		pos,
		variable,
		itemKind == ModuleItemKind_Variable ? name : NULL
	);

	return variable;
}

Function*
Parser::declareFunctionEx(
	ModuleItemKind itemKind,
	const Token::Pos& pos,
	const sl::StringRef& name
) {
	if (m_module->m_itemMap.find(name)) // re-declaration
		return NULL;

	Function* function = new Function;
	function->m_itemKind = itemKind;
	function->m_name = name;
	finalizeDeclaration(pos, function, name);
	return function;
}

void
Parser::finalizeDeclaration(
	const Token::Pos& pos,
	ModuleItem* item,
	const sl::StringRef& name
) {
	item->m_module = m_module;
	item->m_fileName = m_fileName;
	item->m_pos = pos;

	dox::Block* block = m_doxyParser.popBlock();
	if (block) {
		item->m_doxyBlock = block;
		block->m_item = item;
	}

	m_module->m_itemList.insertTail(item);

	if (!name.isEmpty())
		m_module->m_itemMap[name] = item;

	m_lastDeclaredItem = item;
}

//..............................................................................
