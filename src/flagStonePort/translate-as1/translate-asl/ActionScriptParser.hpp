#ifndef INC_ActionScriptParser_hpp_
#define INC_ActionScriptParser_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.4: "ActionScriptParser.g" -> "ActionScriptParser.hpp"$ */
#include <antlr/TokenStream.hpp>
#include <antlr/TokenBuffer.hpp>
#include "ActionScriptTokenTypes.hpp"
#include <antlr/LLkParser.hpp>

#line 1 "ActionScriptParser.g"

#include "ASParser.h"
#include "ASNode.h"

#line 17 "ActionScriptParser.hpp"
class CUSTOM_API ActionScriptParser : public ANTLR_USE_NAMESPACE(antlr)LLkParser, public ActionScriptTokenTypes
{
#line 1 "ActionScriptParser.g"
#line 21 "ActionScriptParser.hpp"
public:
	void initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& factory );
protected:
	ActionScriptParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k);
public:
	ActionScriptParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf);
protected:
	ActionScriptParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k);
public:
	ActionScriptParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer);
	ActionScriptParser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state);
	int getNumTokens() const
	{
		return ActionScriptParser::NUM_TOKENS;
	}
	const char* getTokenName( int type ) const
	{
		if( type > getNumTokens() ) return 0;
		return ActionScriptParser::tokenNames[type];
	}
	const char* const* getTokenNames() const
	{
		return ActionScriptParser::tokenNames;
	}
	public:  translate::ASNode*  script();
	public:  translate::ASNode*  statement();
	public:  translate::ASNode*  blockStatement();
	public:  translate::ASNode*  functionDefinition();
	public:  translate::ASNode*  ifStatement();
	public:  translate::ASNode*  withStatement();
	public:  translate::ASNode*  whileStatement();
	public:  translate::ASNode*  doStatement();
	public:  translate::ASNode*  forStatement();
	public:  translate::ASNode*  onClipEvent();
	public:  translate::ASNode*  on();
	public:  translate::ASNode*  breakStatement();
	public:  translate::ASNode*  continueStatement();
	public:  translate::ASNode*  returnStatement();
	public:  translate::ASNode*  expressionStatement();
	public:  translate::ASNode*  argumentList();
	public:  translate::ASNode*  expressionList();
	public:  translate::ASNode*  conditionalExpression();
	public:  translate::ASNode*  literal();
	public:  translate::ASNode*  expression();
	public:  translate::ASNode*  assignmentExpression();
	public:  translate::ASNode*  logicalOrExpression();
	public:  translate::ASNode*  logicalAndExpression();
	public:  translate::ASNode*  inclusiveOrExpression();
	public:  translate::ASNode*  exclusiveOrExpression();
	public:  translate::ASNode*  andExpression();
	public:  translate::ASNode*  equalityExpression();
	public:  translate::ASNode*  relationalExpression();
	public:  translate::ASNode*  instanceExpression();
	public:  translate::ASNode*  shiftExpression();
	public:  translate::ASNode*  additiveExpression();
	public:  translate::ASNode*  multiplicativeExpression();
	public:  translate::ASNode*  unaryExpression();
	public:  translate::ASNode*  primaryExpression();
	public:  translate::ASNode*  postfixExpression();
	public:  translate::ASNode*  primaryPrefix();
	public:  translate::ASNode*  primarySuffix();
	public:  translate::ASNode*  anonymousArray();
	public:  translate::ASNode*  anonymousObject();
	public:  translate::ASNode*  methodDefinition();
	public:  translate::ASNode*  constructor();
	public:  translate::ASNode*  function();
	public:  translate::ASNode*  attribute();
public:
	ANTLR_USE_NAMESPACE(antlr)RefAST getAST()
	{
		return returnAST;
	}
	
protected:
	ANTLR_USE_NAMESPACE(antlr)RefAST returnAST;
private:
	static const char* tokenNames[];
#ifndef NO_STATIC_CONSTS
	static const int NUM_TOKENS = 86;
#else
	enum {
		NUM_TOKENS = 86
	};
#endif
	
	static const unsigned long _tokenSet_0_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_0;
	static const unsigned long _tokenSet_1_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_1;
	static const unsigned long _tokenSet_2_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_2;
	static const unsigned long _tokenSet_3_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_3;
	static const unsigned long _tokenSet_4_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_4;
	static const unsigned long _tokenSet_5_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_5;
	static const unsigned long _tokenSet_6_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_6;
	static const unsigned long _tokenSet_7_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_7;
};

#endif /*INC_ActionScriptParser_hpp_*/
