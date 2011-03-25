#ifndef INC_ActionScriptTokenTypes_hpp_
#define INC_ActionScriptTokenTypes_hpp_

/* $ANTLR 2.7.4: "ActionScriptParser.g" -> "ActionScriptTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API ActionScriptTokenTypes {
#endif
	enum {
		EOF_ = 1,
		// "{" = 4
		LITERAL_function = 5,
		IDENTIFIER = 6,
		// "(" = 7
		// ")" = 8
		// ";" = 9
		// "}" = 10
		LITERAL_if = 11,
		LITERAL_else = 12,
		LITERAL_with = 13,
		LITERAL_while = 14,
		LITERAL_do = 15,
		LITERAL_for = 16,
		LITERAL_in = 17,
		LITERAL_onClipEvent = 18,
		// "," = 19
		LITERAL_on = 20,
		LITERAL_keyPress = 21,
		LITERAL_break = 22,
		LITERAL_continue = 23,
		LITERAL_return = 24,
		LITERAL_var = 25,
		ASSIGN = 26,
		ASSIGN_ADD = 27,
		ASSIGN_SUB = 28,
		ASSIGN_MUL = 29,
		ASSIGN_DIV = 30,
		ASSIGN_MOD = 31,
		ASSIGN_LSL = 32,
		ASSIGN_ASR = 33,
		ASSIGN_LSR = 34,
		ASSIGN_AND = 35,
		ASSIGN_OR = 36,
		ASSIGN_XOR = 37,
		// "?" = 38
		// ":" = 39
		LOGICAL_OR = 40,
		LOGICAL_AND = 41,
		BIT_OR = 42,
		BIT_XOR = 43,
		BIT_AND = 44,
		EQ = 45,
		NE = 46,
		LTHAN = 47,
		GTHAN = 48,
		LTE = 49,
		GTE = 50,
		LITERAL_instanceof = 51,
		LSL = 52,
		LSR = 53,
		ASR = 54,
		PLUS = 55,
		MINUS = 56,
		MULTIPLY = 57,
		DIVIDE = 58,
		MOD = 59,
		INC = 60,
		DEC = 61,
		BIT_NOT = 62,
		LOGICAL_NOT = 63,
		LITERAL_delete = 64,
		// "[" = 65
		// "]" = 66
		// "." = 67
		LITERAL_new = 68,
		NUMERIC_LITERAL = 69,
		STRING_LITERAL = 70,
		QUOTED_LITERAL = 71,
		LPAREN = 72,
		RPAREN = 73,
		LCURLY = 74,
		RCURLY = 75,
		LBRACKET = 76,
		RBRACKET = 77,
		SEMI = 78,
		COMMA = 79,
		SELECT = 80,
		ALTERNATE = 81,
		WS = 82,
		ESC = 83,
		HEX_DIGIT = 84,
		EXPONENT = 85,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_ActionScriptTokenTypes_hpp_*/
