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

enum TokenKind {
	// common tokens

	TokenKind_Eof        = 0,
	TokenKind_Error      = -1,
	TokenKind_Identifier = 256,
	TokenKind_QuotedArg,
	TokenKind_UnquotedArg,
	TokenKind_DoxyComment_sl,
	TokenKind_DoxyComment_ml,

	// special commands

	TokenKind_Function,
	TokenKind_EndFunction,
	TokenKind_Macro,
	TokenKind_EndMacro,
	TokenKind_Set,
	TokenKind_If,
	TokenKind_ElseIf,
	TokenKind_Else,
	TokenKind_EndIf,
	TokenKind_ForEach,
	TokenKind_EndForEach,
	TokenKind_While,
	TokenKind_EndWhile,
};

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

enum TokenChannelMask {
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
	AXL_LEX_TOKEN_NAME(TokenKind_QuotedArg,      "quoted-arg")
	AXL_LEX_TOKEN_NAME(TokenKind_UnquotedArg,    "unquoted-arg")
	AXL_LEX_TOKEN_NAME(TokenKind_DoxyComment_sl, "doxy-comment-sl")
	AXL_LEX_TOKEN_NAME(TokenKind_DoxyComment_ml, "doxy-comment-ml")

	// special commands

	AXL_LEX_TOKEN_NAME(TokenKind_Function,        "function")
	AXL_LEX_TOKEN_NAME(TokenKind_EndFunction,     "endfunction")
	AXL_LEX_TOKEN_NAME(TokenKind_Macro,           "macro")
	AXL_LEX_TOKEN_NAME(TokenKind_EndMacro,        "endmacro")
	AXL_LEX_TOKEN_NAME(TokenKind_Set,             "set")
	AXL_LEX_TOKEN_NAME(TokenKind_If,              "if")
	AXL_LEX_TOKEN_NAME(TokenKind_ElseIf,          "elseif")
	AXL_LEX_TOKEN_NAME(TokenKind_Else,            "else")
	AXL_LEX_TOKEN_NAME(TokenKind_EndIf,           "endif")
	AXL_LEX_TOKEN_NAME(TokenKind_ForEach,         "foreach")
	AXL_LEX_TOKEN_NAME(TokenKind_EndForEach,      "endforeach")
	AXL_LEX_TOKEN_NAME(TokenKind_While,           "while")
	AXL_LEX_TOKEN_NAME(TokenKind_EndWhile,        "endwhile")

AXL_LEX_END_TOKEN_NAME_MAP();

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

typedef lex::RagelToken<TokenKind, TokenName, lex::StdTokenData> Token;

// . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .

class Lexer: public lex::RagelLexer<Lexer, Token> {
	friend class lex::RagelLexer<Lexer, Token>;

protected:
	Token*
	createStringToken(
		int TokenKind,
		size_t left = 0,
		size_t right = 0
	);

	Token*
	createDoxyCommentToken(int tokenKind);

	// implemented in *.rl

	void
	init();

	void
	exec();
};

//..............................................................................
