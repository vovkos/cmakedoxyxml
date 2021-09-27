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

prepush {
	stack = prePush();
}

postpop {
	postPop();
}

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# standard definitions
#

id     = [_a-zA-Z] [_a-zA-Z0-9]*;
atom   = [^ \t\r\n\\()#"];
ws     = [ \t\r]+;
nl     = '\n' @{ newLine(p + 1); };
esc    = '\\' [^\n];
lit_dq = '"' ([^"\n\\] | esc)* (["\\] | nl);

#. . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . . .
#
# main machine
#

main := |*

'function'      { createToken(TokenKind_Function); };
'endfunction'   { createToken(TokenKind_EndFunction); };
'macro'         { createToken(TokenKind_Macro); };
'endmacro'      { createToken(TokenKind_EndMacro); };
'set'           { createToken(TokenKind_Set); };
'if'            { createToken(TokenKind_If); };
'elseif'        { createToken(TokenKind_ElseIf); };
'else'          { createToken(TokenKind_Else); };
'endif'         { createToken(TokenKind_EndIf); };
'foreach'       { createToken(TokenKind_ForEach); };
'endforeach'    { createToken(TokenKind_EndForEach); };
'while'         { createToken(TokenKind_While); };
'endwhile'      { createToken(TokenKind_EndWhile); };

id              { createStringToken(TokenKind_Identifier); };
atom+           { createStringToken(TokenKind_UnquotedArg); };
lit_dq          { createStringToken(TokenKind_QuotedArg, 1, 1); };

'#!' [^\n]*     { createDoxyCommentToken(TokenKind_DoxyComment_sl); };

'#' ws* '[[!' @(Comment, 2) (any | nl)* :>> ']]'
				{ createDoxyCommentToken(TokenKind_DoxyComment_ml); };

'#' ws* '[[' @(Comment, 1) (any | nl)* :>> ']]'
				;

'#' [^\n]* @(Comment, 0)
				;

ws | nl         ;
print           { createToken(ts[0]); };
any             { createErrorToken(ts[0]); };

*|;

}%%

//..............................................................................

void
Lexer::init() {
	%% write init;
}

void
Lexer::exec() {
	%% write exec;
}

//..............................................................................
