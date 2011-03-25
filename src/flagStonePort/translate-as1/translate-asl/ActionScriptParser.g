/*
 *  ActionScriptParser.g
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

header {
#include "ASParser.h"
#include "ASNode.h"
}

options {
    language="Cpp";
}

class ActionScriptParser extends Parser;

options {
    k = 2;
    exportVocab=ActionScript;
    defaultErrorHandler = false;
    buildAST = false;
}

script returns [ translate::ASNode* root] 
{ 
    translate::ASNode* node = 0; 
    root = translate::NewASNode(translate::ASNode::Array); 
} 
:
    ( node=statement 
    { 
    	if (node->getType() == translate::ASNode::OnClipEvent)
    	    root->setType(translate::ASNode::MovieClip);
    	else if (node->getType() == translate::ASNode::On)
    	    root->setType(translate::ASNode::Button);

        root->append(node); 
    } 
    )*
;

statement returns [ translate::ASNode* node ] 
:
(

        ( "{" statement ) => node=blockStatement
      | ( "function" IDENTIFIER ) => node=functionDefinition
      | node=ifStatement
      | node=withStatement
      | node=whileStatement
      | node=doStatement
      | node=forStatement
      | node=onClipEvent
      | node=on
      | node=breakStatement
      | node=continueStatement
      | node=returnStatement
      | node=expressionStatement
);

functionDefinition returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* args = 0;
    translate::ASNode* body = 0;
}
:
(
    "function" t:IDENTIFIER { node = translate::ValueASNode(translate::ASNode::DefineFunction, t->getText().c_str()); }
    "(" ( args=argumentList { node->append(args); } ) ? ")" body=blockStatement { node->append(body); }
);

expressionStatement returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* expr = 0;
    node = translate::NewASNode(translate::ASNode::NoOp); 
}
: 
(
    ( expr=expressionList { delete node; node = expr; } ) ? ";"
);

blockStatement returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* right = 0;
    node = translate::NewASNode(translate::ASNode::List); 
}
: 
(
    "{" ( right=statement { node->append(right); } )* "}"
);

ifStatement returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* expr = 0;

    node = translate::NewASNode(translate::ASNode::If);
}
: 
(
    "if" "(" expr=conditionalExpression ")" { node->append(expr); } 
        expr=statement { node->append(expr); } 
        ( ("else") => "else" expr=statement { node->append(expr); } ) ?
);

withStatement returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* expr = 0;

    node = translate::NewASNode(translate::ASNode::With);
}
: 
(
    "with" "(" expr=conditionalExpression ")" { node->append(expr); } 
    	expr=statement { node->append(expr); }
);

whileStatement returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* expr = 0;

    node = translate::NewASNode(translate::ASNode::While);
}
: 
(
    "while" "(" expr=conditionalExpression ")" { node->append(expr); }
    	expr=statement { node->append(expr); }
); 

doStatement returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* expr = 0;

    node = translate::NewASNode(translate::ASNode::Do);
}
: 
(
    "do" expr=statement { node->append(expr); }
    "while" "(" expr=conditionalExpression ")" ";" { node->append(expr); }
);   

forStatement returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* init = 0;
    translate::ASNode* test = 0;
    translate::ASNode* iter = 0;
    translate::ASNode* body = 0;
    translate::ASNode* value  = 0;
    translate::ASNode* object = 0;
}
: 
(
    "for" "(" 
    (
        (init=expressionList)? ";" (test=conditionalExpression)? ";" (iter=expressionList)? ")" body=statement
        {
            node = translate::NewASNode(translate::ASNode::For);
            
            if (init != 0) node->append(init); else node->append(translate::NewASNode(translate::ASNode::NoOp));
            if (test != 0) node->append(test); else node->append(translate::NewASNode(translate::ASNode::NoOp));
            if (iter != 0) node->append(iter); else node->append(translate::NewASNode(translate::ASNode::NoOp));
            if (body != 0) node->append(body); else node->append(translate::NewASNode(translate::ASNode::NoOp));
        }
        | value=literal "in" object=conditionalExpression ")" body=statement
        {
            node = translate::BinaryASNode(translate::ASNode::ForIn, value, object);
            node->append(body);
        }
    )
);

onClipEvent returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* event = 0;
    translate::ASNode* body = 0;

    node = translate::NewASNode(translate::ASNode::OnClipEvent);
}
: 
(
    "onClipEvent" "(" event=literal { node->append(event); } ( "," event=literal { node->append(event); } )* ")" 
        body=statement { node->append(body); }
);

on returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* event = 0;
    translate::ASNode* body = 0;

    node = translate::NewASNode(translate::ASNode::On);
}
: 
(
    "on" "(" 
        ( event=literal | "keyPress" event=literal ) { node->append(event); } 
        ( "," ( event=literal | "keyPress" event=literal ) { node->append(event); } )* 
    ")" body=statement { node->append(body); }
);

breakStatement returns [ translate::ASNode* node ] 
{ 
    node = translate::NewASNode(translate::ASNode::Break);
}
: 
(
    "break" ";"
);

continueStatement returns [ translate::ASNode* node ] 
{ 
    node = translate::NewASNode(translate::ASNode::Continue);
}
: 
(
    "continue" ";"
);

returnStatement returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* expr = 0;
    node = translate::NewASNode(translate::ASNode::Return);
}
: 
(
    "return" ( expr=conditionalExpression { node->append(expr); } ) ? ";"
);

expressionList returns [ translate::ASNode* block ] 
{ 
    block = translate::NewASNode(translate::ASNode::ExpressionList); 
    translate::ASNode* node = 0; 
}
:
(
    node=expression { block->append(node); } 
    ( "," node=expression { block->append(node); } )*
    { 
        if (block->count() == 1)
        {
            node = block->remove(0);
            delete block;
            block = node;
        }
    }
);

argumentList returns [ translate::ASNode* block ] 
{ 
    block = translate::NewASNode(translate::ASNode::List); 
    translate::ASNode* node = 0; 
}
:
(
    node=conditionalExpression { block->append(node); } ( "," node=conditionalExpression { block->append(node); } )*
    { 
        if (block->count() == 1)
        {
            node = block->remove(0);
            delete block;
            block = node;
        }
    }
);

/*
 * Expression Syntax
 */
 
expression returns [ translate::ASNode* node ] 
:
(
      node=assignmentExpression
//    | node=conditionalExpression
);

assignmentExpression returns [ translate::ASNode* node ] 
{ 
    translate::ASNode::NodeType type = translate::ASNode::NoOp; 
    translate::ASNode* left = 0;
    translate::ASNode* right = 0;
    bool isVar = false;
}
:
(
    ( "var" { isVar = true; } ) ? node=conditionalExpression  { if (isVar) node->setType(translate::ASNode::DefineVariable); }
    (
        ( ASSIGN     { type = translate::ASNode::Assign; }
        | ASSIGN_ADD { type = translate::ASNode::AssignAdd; }
        | ASSIGN_SUB { type = translate::ASNode::AssignSub; }
        | ASSIGN_MUL { type = translate::ASNode::AssignMul; }
        | ASSIGN_DIV { type = translate::ASNode::AssignDiv; }
        | ASSIGN_MOD { type = translate::ASNode::AssignMod; }
        | ASSIGN_LSL { type = translate::ASNode::AssignLSL; }
        | ASSIGN_ASR { type = translate::ASNode::AssignASR; }
        | ASSIGN_LSR { type = translate::ASNode::AssignLSR; }
        | ASSIGN_AND { type = translate::ASNode::AssignBitAnd; }
        | ASSIGN_OR  { type = translate::ASNode::AssignBitOr; }
        | ASSIGN_XOR { type = translate::ASNode::AssignBitXOr; }
        )
        
        right=assignmentExpression 
        { 
            node = translate::BinaryASNode(type, node, right); 
        }
    ) ?
);

/*
 * The following nodes describe a binary tree which are used to parse expressions containing 
 * the different types of operators. The left branch of the tree descends down one level.
 * The right branch parses the remaining part of the expression starting at the same level. 
 * This allows statements such as a + b * c to be correctly parsed as a + (b * c) which takes
 * into account the level of precendence assigned to different operations. If the right brach 
 * also descended down the tree then the expression would be parsed as (a + b) * c.
 */
 
conditionalExpression returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* cond = 0;
    translate::ASNode* left = 0;
    translate::ASNode* right = 0; 
}
:
(
    node=logicalOrExpression ( 
        "?" left=expression ":" right=conditionalExpression
        { cond = node; 
          node = translate::NewASNode(translate::ASNode::Select); 
          node->append(cond);
          node->append(left);
          node->append(right);
        }
    ) ?
);

logicalOrExpression returns [ translate::ASNode* left ] 
{
    translate::ASNode* right = 0;
}
:
(
    left=logicalAndExpression ( LOGICAL_OR right=logicalAndExpression
    { left = translate::BinaryASNode(translate::ASNode::Or, left, right); }
    )*
);

logicalAndExpression returns [ translate::ASNode* left ] 
{ 
    translate::ASNode* right = 0;
}
:
(
    left=inclusiveOrExpression ( LOGICAL_AND right=inclusiveOrExpression    
    { left = translate::BinaryASNode(translate::ASNode::And, left, right); }
    )*
);

inclusiveOrExpression returns [ translate::ASNode* left ] 
{ 
    translate::ASNode* right = 0;
}
:
(
    left=exclusiveOrExpression ( BIT_OR right=exclusiveOrExpression
    { left = translate::BinaryASNode(translate::ASNode::BitOr, left, right); }
    )*
);

exclusiveOrExpression returns [ translate::ASNode* left ] 
{ 
    translate::ASNode* right = 0;
}
:
(
    left=andExpression ( BIT_XOR right=andExpression    
    { left = translate::BinaryASNode(translate::ASNode::BitXOr, left, right); }
    )*
);

andExpression returns [ translate::ASNode* left ] 
{ 
    translate::ASNode* right = 0;
}
:
(
    left=equalityExpression ( BIT_AND right=equalityExpression
    { left = translate::BinaryASNode(translate::ASNode::BitAnd, left, right); }
    )*
);

equalityExpression returns [ translate::ASNode* left ] 
{ 
    translate::ASNode* right = 0;
    translate::ASNode::NodeType type = translate::ASNode::NoOp;
}
:
(
    left=relationalExpression ( 
        ( EQ { type = translate::ASNode::Equal; }
        | NE { type = translate::ASNode::NotEqual; }
        ) 
        right=relationalExpression
 
        { left = translate::BinaryASNode(type, left, right); }
    )*
);

relationalExpression returns [ translate::ASNode* left ] 
{ 
    translate::ASNode* right = 0;
    translate::ASNode::NodeType type = translate::ASNode::NoOp;
}
:
(
    left=instanceExpression ( 
        ( LTHAN { type = translate::ASNode::LessThan; }
        | GTHAN { type = translate::ASNode::GreaterThan; }
        | LTE { type = translate::ASNode::LessThanEqual; }
        | GTE { type = translate::ASNode::GreaterThanEqual; }
        ) 
        right=instanceExpression
 
        { left = translate::BinaryASNode(type, left, right); }
    )*
);

instanceExpression returns [ translate::ASNode* left ] 
{ 
    translate::ASNode* right = 0;
    translate::ASNode::NodeType type = translate::ASNode::NoOp;
}
:
(
    left=shiftExpression ( 
        "instanceof" { type = translate::ASNode::InstanceOf; }
        right=shiftExpression
 
        { left = translate::BinaryASNode(type, left, right); }
    )*
);

shiftExpression returns [ translate::ASNode* left ] 
{ 
    translate::ASNode* right = 0;
    translate::ASNode::NodeType type = translate::ASNode::NoOp;
}
:
(
    left=additiveExpression ( 
        ( LSL { type = translate::ASNode::LSL; }
        | LSR { type = translate::ASNode::LSR; }
        | ASR { type = translate::ASNode::ASR; }
        ) right=additiveExpression
        
        { left = translate::BinaryASNode(type, left, right); }
    )*
);

additiveExpression returns [ translate::ASNode* left ] 
{ 
    translate::ASNode* right = 0;
    translate::ASNode::NodeType type = translate::ASNode::NoOp;
}
:
(
    left=multiplicativeExpression ( 
        ( PLUS { type = translate::ASNode::Add; }
        | MINUS { type = translate::ASNode::Sub; }
        ) right=multiplicativeExpression
        
       { left = translate::BinaryASNode(type, left, right); }
    )*
);

multiplicativeExpression returns [ translate::ASNode* left ] 
{ 
    translate::ASNode* right = 0;
    translate::ASNode::NodeType type = translate::ASNode::NoOp;
}
:
(
    left=unaryExpression ( 
        ( MULTIPLY { type = translate::ASNode::Mul; }
        | DIVIDE { type = translate::ASNode::Div; }
        | MOD { type = translate::ASNode::Mod; }
        ) right=unaryExpression
        
       { left = translate::BinaryASNode(type, left, right); }
    )*
);

unaryExpression returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* right = 0;
}
:
(
      PLUS right=unaryExpression
      { node = translate::NewASNode(translate::ASNode::Plus); node->append(right); }
    | MINUS right=unaryExpression 
      { node = translate::NewASNode(translate::ASNode::Minus); node->append(right); }
    | INC right=primaryExpression 
      { node = translate::NewASNode(translate::ASNode::PreInc); node->append(right); }
    | DEC right=primaryExpression 
      { node = translate::NewASNode(translate::ASNode::PreDec); node->append(right); }
    | BIT_NOT right=unaryExpression 
      { node = translate::NewASNode(translate::ASNode::BitNot); node->append(right); }
    | LOGICAL_NOT right=unaryExpression 
      { node = translate::NewASNode(translate::ASNode::Not); node->append(right); }
    | "delete" right=unaryExpression 
      { node = translate::NewASNode(translate::ASNode::DeleteObject); node->append(right); }
    | node=postfixExpression
);

postfixExpression returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* expr = 0;
    translate::ASNode::NodeType type = translate::ASNode::NoOp;
}
:
(
    node=primaryExpression (
        ( INC { type = translate::ASNode::PostInc; } 
        | DEC { type = translate::ASNode::PostDec; } 
        ) { expr = node; node = translate::NewASNode(type); node->append(expr); }
    )*
);

/*
 * Primary expressions are split into a prefix/suffix pair. This allows some of the more 
 * esoteric features of ActionScript to be handled cleanly, specifically variables and 
 * array elments can contain objects and even functions. The statement a[1](arg) is 
 * valid ActionScript - the first element of the array contains a function which is 
 * executed passing the argument, arg.
 *
 * Suffixing also allows object path names, e.g. a.b.c() to be correctly parsed.
 */
primaryExpression returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* expr = 0;
    node = translate::NewASNode(translate::ASNode::Value);
}
:
(
    expr=primaryPrefix { node->append(expr); } 
    ( expr=primarySuffix { node->append(expr); } )*
    { 
        for (unsigned int i=0; i<node->count()-1; i++)
        {
            translate::ASNode* a = node->get(i);
            translate::ASNode* b = node->get(i+1);
                
            if (a->getType() == translate::ASNode::Identifier && b->getType() == translate::ASNode::Function)
            {
                b->setValue(a->getValue());
                delete node->remove(i);
            }
            else if (a->getType() == translate::ASNode::Attribute  && b->getType() == translate::ASNode::Function)
            {
                a->setType(translate::ASNode::NoOp);
                b->setType(translate::ASNode::Method);
                b->setValue(a->getValue());
//                delete node->remove(i);
            }
        }

        if (node->count() == 1)
        {
            expr = node->remove(0);
            delete node;
            node = expr;
        }
    }
);

primaryPrefix returns [ translate::ASNode* node ] 
:
(
      node=anonymousArray
    | node=anonymousObject
    | node=methodDefinition
    | node=constructor
    | node=literal
    | "(" node=conditionalExpression ")"
);

primarySuffix returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* expr = 0;
}
:
(
      "[" expr=conditionalExpression "]" 
      { node = translate::NewASNode(translate::ASNode::Subscript); node->append(expr); }
      | "." ( node=literal { node->setType(translate::ASNode::Attribute); }
            | node=function { node->setType(translate::ASNode::Method); }
            )
      | node=function
);

function returns [ translate::ASNode* node ] 
{ 
    node = translate::NewASNode(translate::ASNode::Function);
    translate::ASNode* arg = 0;
}
:
(
    "(" ( arg=conditionalExpression { node->append(arg); } ( "," arg=conditionalExpression { node->append(arg); } )* ) ? ")"
);

constructor returns [ translate::ASNode* node ] 
{ 
    node = translate::NewASNode(translate::ASNode::NewObject);
    translate::ASNode* arg = 0;
}
:
(
    "new" t:IDENTIFIER "(" ( arg=conditionalExpression { node->append(arg); } ( "," arg=conditionalExpression { node->append(arg); } )* ) ? ")"
    
    { node->setValue(t->getText().c_str()); }
);

anonymousArray returns [ translate::ASNode* node ] 
{ 
    node = translate::NewASNode(translate::ASNode::DefineArray);
    translate::ASNode* element = 0;
}
:
(
    "[" ( element=conditionalExpression { node->append(element); } 
        ( "," element=conditionalExpression { node->append(element); } )*
        ) ?
    "]"
);

methodDefinition returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* args = 0;
    translate::ASNode* body = 0;
    node = translate::NewASNode(translate::ASNode::DefineMethod);
}
:
(
    "function" "(" ( args=argumentList { node->append(args); } ) ? ")" body=blockStatement { node->append(body); }
);

anonymousObject returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* attr = 0;
    translate::ASNode* expr = 0;
    
    node = translate::NewASNode(translate::ASNode::List); 
}
:
(
    "{" 
        attr=attribute { node->setType(translate::ASNode::DefineObject); node->append(attr); } ( "," attr=attribute { node->append(attr); } )*
    "}"
);

attribute returns [ translate::ASNode* node ] 
{ 
    translate::ASNode* key = 0;
    translate::ASNode* value = 0;
}
:
(
    key=literal ":" value=conditionalExpression
    
    { node = translate::BinaryASNode(translate::ASNode::DefineAttribute, key, value); }
);

literal returns [ translate::ASNode* node ] :
(
      a:IDENTIFIER { node = translate::ValueASNode(translate::ASNode::Identifier, a->getText().c_str()); }
    | b:NUMERIC_LITERAL { node = translate::ValueASNode(translate::ASNode::Number, b->getText().c_str()); }
    | c:STRING_LITERAL { node = translate::ValueASNode(translate::ASNode::String, c->getText().substr(1, c->getText().length()-2).c_str()); }
    | d:QUOTED_LITERAL { node = translate::ValueASNode(translate::ASNode::String, d->getText().substr(1, d->getText().length()-2).c_str()); }
);

/*
 * ActionScript Lexer
 */

{
    #include "ActionScriptParser.hpp"
}

class ActionScriptLexer extends Lexer;

options {
    exportVocab = ActionScript;
    charVocabulary='\u0003'..'\u00FF';
    k = 4;
}

LPAREN      : '(';
RPAREN      : ')';
LCURLY      : '{';
RCURLY      : '}';
LBRACKET    : '[';
RBRACKET    : ']';
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
GTHAN       : ">";
LTHAN       : "<";
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

WS : // Whitespace
(
      ' '
    | '\t'
    | '\f'
    | ( options {generateAmbigWarnings=false;}
        :    "\r\n"
        |    '\r'
        |    '\n'
       ) { newline(); }
)+
{ $setType(ANTLR_USE_NAMESPACE(antlr)Token::SKIP); }
;
/*
INTEGER_LITERAL : 
    ( '0' ( ( 'x'|'X' ) ( options { warnWhenFollowAmbig=false; } : HEX_DIGIT )+ )?
    | ('1'..'9') ('0'..'9')*
    );
*/
STRING_LITERAL  : '"' (ESC|~('"'|'\\'|'\n'|'\r'))* '"';
QUOTED_LITERAL  : '\'' (ESC|~('\''|'\\'|'\n'|'\r'))* '\'';

/* 
 * An identifier.  Note that testLiterals is set to true!  This means
 * that after we match the rule, we look in the literals table to see
 * if it's a literal or really an identifer
 */
IDENTIFIER options {testLiterals=true;} : 
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
