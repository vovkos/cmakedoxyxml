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
#include "Lexer.h"
#include "Lexer.rl.cpp"

//..............................................................................

Token*
Lexer::createStringToken(
	int tokenKind,
	size_t left,
	size_t right
) {
	Token* token = createToken(tokenKind);
	ASSERT(token->m_pos.m_length >= left + right);

	size_t length = token->m_pos.m_length - (left + right);
	token->m_data.m_string = sl::StringRef(ts + left, length);
	return token;
}

Token*
Lexer::createDoxyCommentToken(int tokenKind) {
	ASSERT(te - ts >= 3 && ts[0] == '-' && ts[1] == '-');

	size_t left = 0;
	size_t right = 0;

	switch (tokenKind) {
	case TokenKind_DoxyComment_sl: // --!
		ASSERT(ts[2] == '!');
		left = 3;
		break;

	case TokenKind_DoxyComment_ml: // --[[!
		ASSERT(ts[2] == '[' && ts[3] == '[' && ts[4] == '!');
		ASSERT(te[-1] == ']' && te[-2] == ']');
		left = 5;
		right = 2;
		break;

	default:
		ASSERT(false);
	}

	Token* token = createStringToken(tokenKind, left, right);
	token->m_channelMask = TokenChannelMask_DoxyComment;
	return token;
}

//..............................................................................
