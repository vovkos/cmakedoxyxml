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

enum TokenKind
{
	// common tokens

	TokenKind_Eof        = 0,
	TokenKind_Error      = -1,
	TokenKind_Identifier = 256,
	TokenKind_Number,
	TokenKind_String,
	TokenKind_DoxyComment_sl,
	TokenKind_DoxyComment_ml,

	// keywords

	TokenKind_Goto,
	TokenKind_Break,
	TokenKind_Return,
	TokenKind_Do,
	TokenKind_End,
	TokenKind_While,
	TokenKind_Repeat,
	TokenKind_Until,
	TokenKind_If,
	TokenKind_Then,
	TokenKind_ElseIf,
	TokenKind_Else,
	TokenKind_For,
	TokenKind_Function,
	TokenKind_Local,
	TokenKind_In,
	TokenKind_Nil,
	TokenKind_False,
	TokenKind_True,
	TokenKind_Or,
	TokenKind_And,
	TokenKind_Not,

	// special tokens

	TokenKind_Context,
	TokenKind_Ellipsis,
	TokenKind_Le,
	TokenKind_Ge,
	TokenKind_Ne,
	TokenKind_Eq,
	TokenKind_Shl,
	TokenKind_Shr,
	TokenKind_Concat,
	TokenKind_FloorDiv,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

enum TokenChannelMask
{
	TokenChannelMask_Main        = lex::TokenChannelMask_Main, // 0x01,
	TokenChannelMask_DoxyComment = 0x02,
	TokenChannelMask_All         = -1,
};


// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

AXL_LEX_BEGIN_TOKEN_NAME_MAP(TokenName)

	// common tokens

	AXL_LEX_TOKEN_NAME(TokenKind_Eof,            "eof")
	AXL_LEX_TOKEN_NAME(TokenKind_Error,          "error")
	AXL_LEX_TOKEN_NAME(TokenKind_Identifier,     "identifier")
	AXL_LEX_TOKEN_NAME(TokenKind_Number,         "number")
	AXL_LEX_TOKEN_NAME(TokenKind_String,         "string")
	AXL_LEX_TOKEN_NAME(TokenKind_DoxyComment_sl, "doxy-comment-sl")
	AXL_LEX_TOKEN_NAME(TokenKind_DoxyComment_ml, "doxy-comment-ml")

	// keywords

	AXL_LEX_TOKEN_NAME(TokenKind_Goto,     "goto")
	AXL_LEX_TOKEN_NAME(TokenKind_Break,    "break")
	AXL_LEX_TOKEN_NAME(TokenKind_Return,   "return")
	AXL_LEX_TOKEN_NAME(TokenKind_Do,       "do")
	AXL_LEX_TOKEN_NAME(TokenKind_End,      "end")
	AXL_LEX_TOKEN_NAME(TokenKind_While,    "while")
	AXL_LEX_TOKEN_NAME(TokenKind_Repeat,   "repeat")
	AXL_LEX_TOKEN_NAME(TokenKind_Until,    "until")
	AXL_LEX_TOKEN_NAME(TokenKind_If,       "if")
	AXL_LEX_TOKEN_NAME(TokenKind_Then,     "then")
	AXL_LEX_TOKEN_NAME(TokenKind_ElseIf,   "elseif")
	AXL_LEX_TOKEN_NAME(TokenKind_Else,     "else")
	AXL_LEX_TOKEN_NAME(TokenKind_For,      "for")
	AXL_LEX_TOKEN_NAME(TokenKind_Function, "function")
	AXL_LEX_TOKEN_NAME(TokenKind_Local,    "local")
	AXL_LEX_TOKEN_NAME(TokenKind_In,       "in")
	AXL_LEX_TOKEN_NAME(TokenKind_Nil,      "nil")
	AXL_LEX_TOKEN_NAME(TokenKind_False,    "false")
	AXL_LEX_TOKEN_NAME(TokenKind_True,     "true")
	AXL_LEX_TOKEN_NAME(TokenKind_Or,       "or")
	AXL_LEX_TOKEN_NAME(TokenKind_And,      "and")
	AXL_LEX_TOKEN_NAME(TokenKind_Not,      "not")

	// special tokens

	AXL_LEX_TOKEN_NAME(TokenKind_Context,  "::")
	AXL_LEX_TOKEN_NAME(TokenKind_Ellipsis, "...")
	AXL_LEX_TOKEN_NAME(TokenKind_Le,       "<=")
	AXL_LEX_TOKEN_NAME(TokenKind_Ge,       ">=")
	AXL_LEX_TOKEN_NAME(TokenKind_Ne,       "~=")
	AXL_LEX_TOKEN_NAME(TokenKind_Eq,       "==")
	AXL_LEX_TOKEN_NAME(TokenKind_Shl,      "<<")
	AXL_LEX_TOKEN_NAME(TokenKind_Shr,      ">>")
	AXL_LEX_TOKEN_NAME(TokenKind_Concat,   "..")
	AXL_LEX_TOKEN_NAME(TokenKind_FloorDiv, "//")

AXL_LEX_END_TOKEN_NAME_MAP();

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

typedef lex::RagelToken<TokenKind, TokenName, lex::StdTokenData> Token;

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class Lexer: public lex::RagelLexer<Lexer, Token>
{
	friend class lex::RagelLexer<Lexer, Token>;

protected:
	Token*
	createStringToken(
		int TokenKind,
		size_t left = 0,
		size_t right = 0
		);

	Token*
	createIntegerToken(
		int radix = 10,
		size_t left = 0
		);

	Token*
	createFpToken();

	Token*
	createDoxyCommentToken(int tokenKind);

	// implemented in *.rl

	void
	init();

	void
	exec();
};

//..............................................................................
