#ifndef INC_PreprocessorTokenTypes_hpp_
#define INC_PreprocessorTokenTypes_hpp_

/* $ANTLR 2.7.4: "Preprocessor.g" -> "PreprocessorTokenTypes.hpp"$ */

#ifndef CUSTOM_API
# define CUSTOM_API
#endif

#ifdef __cplusplus
struct CUSTOM_API PreprocessorTokenTypes {
#endif
	enum {
		EOF_ = 1,
		INCLUDE = 4,
		DEFINE = 5,
		IFDEF = 6,
		IFNDEF = 7,
		ELSE = 8,
		ENDIF = 9,
		LPAREN = 10,
		RPAREN = 11,
		LBRACKET = 12,
		RBRACKET = 13,
		LCURLY = 14,
		RCURLY = 15,
		SEMI = 16,
		COMMA = 17,
		SELECT = 18,
		ALTERNATE = 19,
		ASSIGN = 20,
		ASSIGN_ADD = 21,
		ASSIGN_SUB = 22,
		ASSIGN_MUL = 23,
		ASSIGN_DIV = 24,
		ASSIGN_MOD = 25,
		ASSIGN_LSL = 26,
		ASSIGN_ASR = 27,
		ASSIGN_LSR = 28,
		ASSIGN_AND = 29,
		ASSIGN_OR = 30,
		ASSIGN_XOR = 31,
		LOGICAL_AND = 32,
		LOGICAL_OR = 33,
		LOGICAL_NOT = 34,
		EQ = 35,
		GT = 36,
		LT = 37,
		GTE = 38,
		LTE = 39,
		NE = 40,
		BIT_AND = 41,
		BIT_OR = 42,
		BIT_XOR = 43,
		BIT_NOT = 44,
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
		WHITESPACE = 55,
		LINE_END = 56,
		STRING_LITERAL = 57,
		QUOTED_LITERAL = 58,
		LITERAL = 59,
		ESC = 60,
		HEX_DIGIT = 61,
		EXPONENT = 62,
		NUMERIC_LITERAL = 63,
		SL_COMMENT = 64,
		ML_COMMENT = 65,
		NULL_TREE_LOOKAHEAD = 3
	};
#ifdef __cplusplus
};
#endif
#endif /*INC_PreprocessorTokenTypes_hpp_*/
