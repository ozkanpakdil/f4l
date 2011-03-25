/*
 *  Preprocessor.g
 *  Translate AS1
 *
 *  Created by smackay on Tue Jun 15 2004.
 *  Copyright (c) 2004 Flagstone Software Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later 
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * For more information please contact:
 * 
 * Stuart MacKay
 * Flagstone Software Ltd
 * 92 High Street
 * Wick, Caithness KW1 4LY
 * Scotland
 * 
 * www.flagstonesoftware.com
*/

options {
    language="Cpp";
}

class Preprocessor extends Lexer;

options {
	testLiterals=false;    // don't automatically test for literals
    charVocabulary='\u0003'..'\u00FF';
    k = 4;
}

INCLUDE     : "#include";
DEFINE      : "#define";
IFDEF       : "#ifdef";
IFNDEF      : "#ifndef";
ELSE        : "#else";
ENDIF       : "#endif";

LPAREN      : '(';
RPAREN      : ')';
LBRACKET    : '[';
RBRACKET    : ']';
LCURLY      : '{';
RCURLY      : '}';
SEMI        : ';';
COMMA       : ',';
//DOT         : '.';

SELECT      : '?';
ALTERNATE   : ':';

ASSIGN      : "=";
ASSIGN_ADD  : "+=";
ASSIGN_SUB  : "-=";
ASSIGN_MUL  : "*=";
ASSIGN_DIV  : "/=";
ASSIGN_MOD  : "%=";
ASSIGN_LSL  : "<<=";
ASSIGN_ASR  : ">>=";
ASSIGN_LSR  : ">>>=";
ASSIGN_AND  : "&=";
ASSIGN_OR   : "|=";
ASSIGN_XOR  : "^=";
LOGICAL_AND : "&&";
LOGICAL_OR  : "||";
LOGICAL_NOT : "!";
EQ          : "==";
GT          : ">";
LT          : "<";
GTE         : ">=";
LTE         : "<=";
NE          : "!=";
BIT_AND     : "&";
BIT_OR      : "|";
BIT_XOR     : "^";
BIT_NOT     : "~";
LSL         : "<<";
LSR         : ">>>";
ASR         : ">>";
PLUS        : "+";
MINUS       : "-";
MULTIPLY    : "*";
DIVIDE      : "/";
MOD         : "%";
INC         : "++";
DEC         : "--";

WHITESPACE :
(
      ' '
    | '\t'
    | '\f'
)
/* { $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); } */
;

LINE_END options {generateAmbigWarnings=false;} :
(
         "\r\n"
    |    '\r'
    |    '\n'
)
{ /* $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); */ newline(); }
;

STRING_LITERAL  : '"' (ESC|~('"'|'\\'|'\n'|'\r'))* '"';
QUOTED_LITERAL  : '\'' (ESC|~('\''|'\\'|'\n'|'\r'))* '\'';

/* 
 * An identifier.  Note that testLiterals is set to true!  This means
 * that after we match the rule, we look in the literals table to see
 * if it's a literal or really an identifer
 */
LITERAL options {testLiterals=false;} : 
    ('a'..'z'|'A'..'Z'|'_'|'$') ('a'..'z'|'A'..'Z'|'_'|'0'..'9'|'$')* ;

 
/*
 * escape sequence -- note that this is protected; it can only be called
 * from another lexer rule -- it will not ever directly return a token to
 * the parser.
 *
 * There are various ambiguities hushed in this rule.  The optional
 * '0'...'9' digit matches should be matched here rather than letting
 * them go back to STRING_LITERAL to be matched.  ANTLR does the
 * right thing by matching immediately; hence, it's ok to shut off
 * the FOLLOW ambig warnings.
 */
protected ESC :
    '\\'
    ( 'n'
    | 'r'
    | 't'
    | 'b'
    | 'f'
    | '"'
    | '\''
    | '\\'
    | ('u')+ HEX_DIGIT HEX_DIGIT HEX_DIGIT HEX_DIGIT
    | '0'..'3'
        ( options { warnWhenFollowAmbig = false; }
            :    '0'..'7'
                ( options { warnWhenFollowAmbig = false; }
                :    '0'..'7'
                )?
            )?
        |    '4'..'7'
            ( options { warnWhenFollowAmbig = false; }
            :    '0'..'7'
            )?
        )
    ;

protected HEX_DIGIT : ('0'..'9'|'A'..'F'|'a'..'f');
protected EXPONENT : ('e'|'E') ('+'|'-')? ('0'..'9')+ ;

NUMERIC_LITERAL { bool isDecimal = false; }
    :   '.' 
            (	('0'..'9')+ (EXPONENT)? 
            )?

	|	(	'0' {isDecimal = true;}
			(	// hex
				('x'|'X') ( options { warnWhenFollowAmbig=false; } : HEX_DIGIT )+
			|	// double with leading zero
				(('0'..'9')+ ('.'|EXPONENT)) => ('0'..'9')+
			)?
		|	('1'..'9') ('0'..'9')*  {isDecimal=true;} // non-zero decimal
		)
		
		
		
		(
			{isDecimal}?
            ( '.' ('0'..'9')* (EXPONENT)?
            |   EXPONENT
            )
        )?
	;

SL_COMMENT :   // Single line comments

    "//" (~('\n'|'\r'))* ('\n'|'\r'('\n')?)?
    {
/*        $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); */
        newline();
    }
;

ML_COMMENT :   // Multiple-line comments

    "/*"
        (    /* '\r' '\n' can be matched in one alternative or by matching
                '\r' in one iteration and '\n' in another.  I am trying to
                handle any flavor of newline that comes in, but the language
                that allows both "\r\n" and "\r" and "\n" to all be valid
                newline is ambiguous.  Consequently, the resulting grammar
                must be ambiguous.  I'm shutting this warning off.
             */
            options {
                generateAmbigWarnings=false;
            }
        :
            { LA(2)!='/' }? '*'
        |    '\r' '\n'       {newline();}
        |    '\r'            {newline();}
        |    '\n'            {newline();}
        |    ~('*'|'\n'|'\r')
        )*
        "*/"
/*        {$setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP);} */
    ;