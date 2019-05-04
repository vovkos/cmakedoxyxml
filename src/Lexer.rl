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

// warning C4065: switch statement contains 'default' but no 'case' labels

#pragma warning(disable: 4065)

//..............................................................................

%%{

machine cmake;
write data;

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# prepush / postpop (for fcall/fret)
#

prepush
{
	stack = prePush();
}

postpop
{
	postPop();
}

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# standard definitions
#

dec    = [0-9];
hex    = [0-9a-fA-F];
oct    = [0-7];
bin    = [01];
id     = [_a-zA-Z] [_a-zA-Z0-9]*;
ws     = [ \t\r]+;
nl     = '\n' @{ newLine(p + 1); };
lc_nl  = '\\' '\r'? nl;
esc    = '\\' [^\n];
lit_dq = '"' ([^"\n\\] | esc)* (["\\] | nl);
lit_sq = "'" ([^'\n\\] | esc)* (['\\] | nl);

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# main machine
#

main := |*

'goto'          { createToken(TokenKind_Goto); };
'break'         { createToken(TokenKind_Break); };
'return'        { createToken(TokenKind_Return); };
'do'            { createToken(TokenKind_Do); };
'end'           { createToken(TokenKind_End); };
'while'         { createToken(TokenKind_While); };
'repeat'        { createToken(TokenKind_Repeat); };
'until'         { createToken(TokenKind_Until); };
'if'            { createToken(TokenKind_If); };
'then'          { createToken(TokenKind_Then); };
'elseif'        { createToken(TokenKind_ElseIf); };
'else'          { createToken(TokenKind_Else); };
'for'           { createToken(TokenKind_For); };
'function'      { createToken(TokenKind_Function); };
'local'         { createToken(TokenKind_Local); };
'in'            { createToken(TokenKind_In); };
'nil'           { createToken(TokenKind_Nil); };
'false'         { createToken(TokenKind_False); };
'true'          { createToken(TokenKind_True); };
'or'            { createToken(TokenKind_Or); };
'and'           { createToken(TokenKind_And); };
'not'           { createToken(TokenKind_Not); };

'::'            { createToken(TokenKind_Context); };
'...'           { createToken(TokenKind_Ellipsis); };
'<='            { createToken(TokenKind_Le); };
'>='            { createToken(TokenKind_Ge); };
'~='            { createToken(TokenKind_Ne); };
'=='            { createToken(TokenKind_Eq); };
'<<'            { createToken(TokenKind_Shl); };
'>>'            { createToken(TokenKind_Shr); };
'..'            { createToken(TokenKind_Concat); };
'//'            { createToken(TokenKind_FloorDiv); };

id              { createStringToken(TokenKind_Identifier); };
lit_sq | lit_dq { createStringToken(TokenKind_String, 1, 1); };
dec+            { createIntegerToken (10); };
'0' [xX] hex+   { createIntegerToken (16, 2); };
dec+ ('.' dec*) | ([eE] [+\-]? dec+)
				{ createFpToken (); };

'--!' [^\n]*    { createDoxyCommentToken(TokenKind_DoxyComment_sl); };

'--[[!' @(Comment, 2) (any | nl)* :>> ']]'
				{ createDoxyCommentToken(TokenKind_DoxyComment_ml); };

'--[[' @(Comment, 1) (any | nl)* :>> ']]'
				;

'--' [^\n]* @(Comment, 0)
				;

ws | nl ;
print           { createToken(ts[0]); };
any             { createErrorToken(ts[0]); };

*|;

}%%

//..............................................................................

void
Lexer::init()
{
	%% write init;
}

void
Lexer::exec()
{
	%% write exec;
}

//..............................................................................
