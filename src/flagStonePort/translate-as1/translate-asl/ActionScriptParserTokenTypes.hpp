#ifndef INC_ActionScriptParserTokenTypes_hpp_
#define INC_ActionScriptParserTokenTypes_hpp_

/* $ANTLR 2.7.4: "ActionScriptParser.g" -> "ActionScriptParserTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API ActionScriptParserTokenTypes {
#endif
	enum {
		EOF_ = 1,
		// ";" = 4
		// "{" = 5
		// "}" = 6
		IF = 7,
		// "(" = 8
		// ")" = 9
		ELSE = 10,
		WITH = 11,
		WHILE = 12,
		DO = 13,
		FOR = 14,
		ONCLIPEVENT = 15,
		// "," = 16
		ON = 17,
		LITERAL_keyPress = 18,
		BREAK = 19,
		CONTINUE = 20,
		RETURN = 21,
		ASSIGN = 22,
		ASSIGN_ADD = 23,
		ASSIGN_SUB = 24,
		ASSIGN_MUL = 25,
		ASSIGN_DIV = 26,
		ASSIGN_MOD = 27,
		ASSIGN_LSL = 28,
		ASSIGN_ASR = 29,
		ASSIGN_LSR = 30,
		ASSIGN_AND = 31,
		ASSIGN_OR = 32,
		ASSIGN_XOR = 33,
		LOGICAL_OR = 34,
		LOGICAL_AND = 35,
		BIT_OR = 36,
		BIT_XOR = 37,
		BIT_AND = 38,
		EQ = 39,
		NE = 40,
		LTHAN = 41,
		GTHAN = 42,
		LTE = 43,
		GTE = 44,
		LSL = 45,
		LSR = 46,
		ASR = 47,
		PLUS = 48,
		MINUS = 49,
		MULTIPLY = 50,
		DIVIDE = 51,
		MOD = 52,
		INC = 53,
		DEC = 54,
		BIT_NOT = 55,
		LOGICAL_NOT = 56,
		// "[" = 57
		// "]" = 58
		// "." = 59
		NEW = 60,
		IDENTIFIER = 61,
		FUNCTION = 62,
		// ":" = 63
		INTEGER_LITERAL = 64,
		STRING_LITERAL = 65,
		LITERAL_if = 66,
		LITERAL_else = 67,
		LITERAL_while = 68,
		LITERAL_do = 69,
		LITERAL_for = 70,
		LITERAL_in = 71,
		LITERAL_break = 72,
		LITERAL_continue = 73,
		LITERAL_return = 74,
		LITERAL_with = 75,
		LITERAL_new = 76,
		LITERAL_function = 77,
		LITERAL_var = 78,
		LITERAL_onClipEvent = 79,
		LITERAL_on = 80,
		LPAREN = 81,
		RPAREN = 82,
		LCURLY = 83,
		RCURLY = 84,
		WS = 85,
		ESC = 86,
		HEX_DIGIT = 87,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_ActionScriptParserTokenTypes_hpp_*/
