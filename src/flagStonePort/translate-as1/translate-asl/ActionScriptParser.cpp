/* $ANTLR 2.7.4: "ActionScriptParser.g" -> "ActionScriptParser.cpp"$ */
#include "ActionScriptParser.hpp"
#include <antlr/NoViableAltException.hpp>
#include <antlr/SemanticException.hpp>
#include <antlr/ASTFactory.hpp>
#line 1 "ActionScriptParser.g"
#line 8 "ActionScriptParser.cpp"
ActionScriptParser::ActionScriptParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,k)
{
}

ActionScriptParser::ActionScriptParser(ANTLR_USE_NAMESPACE(antlr)TokenBuffer& tokenBuf)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(tokenBuf,2)
{
}

ActionScriptParser::ActionScriptParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer, int k)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,k)
{
}

ActionScriptParser::ActionScriptParser(ANTLR_USE_NAMESPACE(antlr)TokenStream& lexer)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(lexer,2)
{
}

ActionScriptParser::ActionScriptParser(const ANTLR_USE_NAMESPACE(antlr)ParserSharedInputState& state)
: ANTLR_USE_NAMESPACE(antlr)LLkParser(state,2)
{
}

 translate::ASNode*  ActionScriptParser::script() {
#line 19 "ActionScriptParser.g"
	 translate::ASNode* root;
#line 37 "ActionScriptParser.cpp"
#line 19 "ActionScriptParser.g"
	
	translate::ASNode* node = 0; 
	root = translate::NewASNode(translate::ASNode::Array); 
	
#line 43 "ActionScriptParser.cpp"
	
	{ // ( ... )*
	for (;;) {
		if ((_tokenSet_0.member(LA(1)))) {
			node=statement();
			if ( inputState->guessing==0 ) {
#line 26 "ActionScriptParser.g"
				
					if (node->getType() == translate::ASNode::OnClipEvent)
					    root->setType(translate::ASNode::MovieClip);
					else if (node->getType() == translate::ASNode::On)
					    root->setType(translate::ASNode::Button);
				
				root->append(node); 
				
#line 59 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop3;
		}
		
	}
	_loop3:;
	} // ( ... )*
	return root;
}

 translate::ASNode*  ActionScriptParser::statement() {
#line 37 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 75 "ActionScriptParser.cpp"
	
	{
	switch ( LA(1)) {
	case LITERAL_if:
	{
		node=ifStatement();
		break;
	}
	case LITERAL_with:
	{
		node=withStatement();
		break;
	}
	case LITERAL_while:
	{
		node=whileStatement();
		break;
	}
	case LITERAL_do:
	{
		node=doStatement();
		break;
	}
	case LITERAL_for:
	{
		node=forStatement();
		break;
	}
	case LITERAL_onClipEvent:
	{
		node=onClipEvent();
		break;
	}
	case LITERAL_on:
	{
		node=on();
		break;
	}
	case LITERAL_break:
	{
		node=breakStatement();
		break;
	}
	case LITERAL_continue:
	{
		node=continueStatement();
		break;
	}
	case LITERAL_return:
	{
		node=returnStatement();
		break;
	}
	default:
		bool synPredMatched7 = false;
		if (((LA(1) == 4) && (_tokenSet_1.member(LA(2))))) {
			int _m7 = mark();
			synPredMatched7 = true;
			inputState->guessing++;
			try {
				{
				match(4);
				statement();
				}
			}
			catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& pe) {
				synPredMatched7 = false;
			}
			rewind(_m7);
			inputState->guessing--;
		}
		if ( synPredMatched7 ) {
			node=blockStatement();
		}
		else {
			bool synPredMatched9 = false;
			if (((LA(1) == LITERAL_function) && (LA(2) == IDENTIFIER))) {
				int _m9 = mark();
				synPredMatched9 = true;
				inputState->guessing++;
				try {
					{
					match(LITERAL_function);
					match(IDENTIFIER);
					}
				}
				catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& pe) {
					synPredMatched9 = false;
				}
				rewind(_m9);
				inputState->guessing--;
			}
			if ( synPredMatched9 ) {
				node=functionDefinition();
			}
			else if ((_tokenSet_2.member(LA(1))) && (_tokenSet_3.member(LA(2)))) {
				node=expressionStatement();
			}
	else {
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::blockStatement() {
#line 77 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 185 "ActionScriptParser.cpp"
#line 77 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	node = translate::NewASNode(translate::ASNode::List); 
	
#line 191 "ActionScriptParser.cpp"
	
	{
	match(4);
	{ // ( ... )*
	for (;;) {
		if ((_tokenSet_0.member(LA(1)))) {
			right=statement();
			if ( inputState->guessing==0 ) {
#line 84 "ActionScriptParser.g"
				node->append(right);
#line 202 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop19;
		}
		
	}
	_loop19:;
	} // ( ... )*
	match(10);
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::functionDefinition() {
#line 56 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 220 "ActionScriptParser.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefToken  t = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 56 "ActionScriptParser.g"
	
	translate::ASNode* args = 0;
	translate::ASNode* body = 0;
	
#line 227 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_function);
	t = LT(1);
	match(IDENTIFIER);
	if ( inputState->guessing==0 ) {
#line 63 "ActionScriptParser.g"
		node = translate::ValueASNode(translate::ASNode::DefineFunction, t->getText().c_str());
#line 236 "ActionScriptParser.cpp"
	}
	match(7);
	{
	switch ( LA(1)) {
	case 4:
	case LITERAL_function:
	case IDENTIFIER:
	case 7:
	case PLUS:
	case MINUS:
	case INC:
	case DEC:
	case BIT_NOT:
	case LOGICAL_NOT:
	case LITERAL_delete:
	case 65:
	case LITERAL_new:
	case NUMERIC_LITERAL:
	case STRING_LITERAL:
	case QUOTED_LITERAL:
	{
		args=argumentList();
		if ( inputState->guessing==0 ) {
#line 64 "ActionScriptParser.g"
			node->append(args);
#line 262 "ActionScriptParser.cpp"
		}
		break;
	}
	case 8:
	{
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	match(8);
	body=blockStatement();
	if ( inputState->guessing==0 ) {
#line 64 "ActionScriptParser.g"
		node->append(body);
#line 281 "ActionScriptParser.cpp"
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::ifStatement() {
#line 87 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 290 "ActionScriptParser.cpp"
#line 87 "ActionScriptParser.g"
	
	translate::ASNode* expr = 0;
	
	node = translate::NewASNode(translate::ASNode::If);
	
#line 297 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_if);
	match(7);
	expr=conditionalExpression();
	match(8);
	if ( inputState->guessing==0 ) {
#line 95 "ActionScriptParser.g"
		node->append(expr);
#line 307 "ActionScriptParser.cpp"
	}
	expr=statement();
	if ( inputState->guessing==0 ) {
#line 96 "ActionScriptParser.g"
		node->append(expr);
#line 313 "ActionScriptParser.cpp"
	}
	{
	bool synPredMatched24 = false;
	if (((LA(1) == LITERAL_else) && (_tokenSet_0.member(LA(2))))) {
		int _m24 = mark();
		synPredMatched24 = true;
		inputState->guessing++;
		try {
			{
			match(LITERAL_else);
			}
		}
		catch (ANTLR_USE_NAMESPACE(antlr)RecognitionException& pe) {
			synPredMatched24 = false;
		}
		rewind(_m24);
		inputState->guessing--;
	}
	if ( synPredMatched24 ) {
		match(LITERAL_else);
		expr=statement();
		if ( inputState->guessing==0 ) {
#line 97 "ActionScriptParser.g"
			node->append(expr);
#line 338 "ActionScriptParser.cpp"
		}
	}
	else if ((_tokenSet_4.member(LA(1))) && (_tokenSet_5.member(LA(2)))) {
	}
	else {
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::withStatement() {
#line 100 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 355 "ActionScriptParser.cpp"
#line 100 "ActionScriptParser.g"
	
	translate::ASNode* expr = 0;
	
	node = translate::NewASNode(translate::ASNode::With);
	
#line 362 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_with);
	match(7);
	expr=conditionalExpression();
	match(8);
	if ( inputState->guessing==0 ) {
#line 108 "ActionScriptParser.g"
		node->append(expr);
#line 372 "ActionScriptParser.cpp"
	}
	expr=statement();
	if ( inputState->guessing==0 ) {
#line 109 "ActionScriptParser.g"
		node->append(expr);
#line 378 "ActionScriptParser.cpp"
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::whileStatement() {
#line 112 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 387 "ActionScriptParser.cpp"
#line 112 "ActionScriptParser.g"
	
	translate::ASNode* expr = 0;
	
	node = translate::NewASNode(translate::ASNode::While);
	
#line 394 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_while);
	match(7);
	expr=conditionalExpression();
	match(8);
	if ( inputState->guessing==0 ) {
#line 120 "ActionScriptParser.g"
		node->append(expr);
#line 404 "ActionScriptParser.cpp"
	}
	expr=statement();
	if ( inputState->guessing==0 ) {
#line 121 "ActionScriptParser.g"
		node->append(expr);
#line 410 "ActionScriptParser.cpp"
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::doStatement() {
#line 124 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 419 "ActionScriptParser.cpp"
#line 124 "ActionScriptParser.g"
	
	translate::ASNode* expr = 0;
	
	node = translate::NewASNode(translate::ASNode::Do);
	
#line 426 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_do);
	expr=statement();
	if ( inputState->guessing==0 ) {
#line 132 "ActionScriptParser.g"
		node->append(expr);
#line 434 "ActionScriptParser.cpp"
	}
	match(LITERAL_while);
	match(7);
	expr=conditionalExpression();
	match(8);
	match(9);
	if ( inputState->guessing==0 ) {
#line 133 "ActionScriptParser.g"
		node->append(expr);
#line 444 "ActionScriptParser.cpp"
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::forStatement() {
#line 136 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 453 "ActionScriptParser.cpp"
#line 136 "ActionScriptParser.g"
	
	translate::ASNode* init = 0;
	translate::ASNode* test = 0;
	translate::ASNode* iter = 0;
	translate::ASNode* body = 0;
	translate::ASNode* value  = 0;
	translate::ASNode* object = 0;
	
#line 463 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_for);
	match(7);
	{
	if ((_tokenSet_2.member(LA(1))) && (_tokenSet_6.member(LA(2)))) {
		{
		switch ( LA(1)) {
		case 4:
		case LITERAL_function:
		case IDENTIFIER:
		case 7:
		case LITERAL_var:
		case PLUS:
		case MINUS:
		case INC:
		case DEC:
		case BIT_NOT:
		case LOGICAL_NOT:
		case LITERAL_delete:
		case 65:
		case LITERAL_new:
		case NUMERIC_LITERAL:
		case STRING_LITERAL:
		case QUOTED_LITERAL:
		{
			init=expressionList();
			break;
		}
		case 9:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		match(9);
		{
		switch ( LA(1)) {
		case 4:
		case LITERAL_function:
		case IDENTIFIER:
		case 7:
		case PLUS:
		case MINUS:
		case INC:
		case DEC:
		case BIT_NOT:
		case LOGICAL_NOT:
		case LITERAL_delete:
		case 65:
		case LITERAL_new:
		case NUMERIC_LITERAL:
		case STRING_LITERAL:
		case QUOTED_LITERAL:
		{
			test=conditionalExpression();
			break;
		}
		case 9:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		match(9);
		{
		switch ( LA(1)) {
		case 4:
		case LITERAL_function:
		case IDENTIFIER:
		case 7:
		case LITERAL_var:
		case PLUS:
		case MINUS:
		case INC:
		case DEC:
		case BIT_NOT:
		case LOGICAL_NOT:
		case LITERAL_delete:
		case 65:
		case LITERAL_new:
		case NUMERIC_LITERAL:
		case STRING_LITERAL:
		case QUOTED_LITERAL:
		{
			iter=expressionList();
			break;
		}
		case 8:
		{
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		match(8);
		body=statement();
		if ( inputState->guessing==0 ) {
#line 150 "ActionScriptParser.g"
			
			node = translate::NewASNode(translate::ASNode::For);
			
			if (init != 0) node->append(init); else node->append(translate::NewASNode(translate::ASNode::NoOp));
			if (test != 0) node->append(test); else node->append(translate::NewASNode(translate::ASNode::NoOp));
			if (iter != 0) node->append(iter); else node->append(translate::NewASNode(translate::ASNode::NoOp));
			if (body != 0) node->append(body); else node->append(translate::NewASNode(translate::ASNode::NoOp));
			
#line 582 "ActionScriptParser.cpp"
		}
	}
	else if ((_tokenSet_7.member(LA(1))) && (LA(2) == LITERAL_in)) {
		value=literal();
		match(LITERAL_in);
		object=conditionalExpression();
		match(8);
		body=statement();
		if ( inputState->guessing==0 ) {
#line 159 "ActionScriptParser.g"
			
			node = translate::BinaryASNode(translate::ASNode::ForIn, value, object);
			node->append(body);
			
#line 597 "ActionScriptParser.cpp"
		}
	}
	else {
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::onClipEvent() {
#line 166 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 612 "ActionScriptParser.cpp"
#line 166 "ActionScriptParser.g"
	
	translate::ASNode* event = 0;
	translate::ASNode* body = 0;
	
	node = translate::NewASNode(translate::ASNode::OnClipEvent);
	
#line 620 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_onClipEvent);
	match(7);
	event=literal();
	if ( inputState->guessing==0 ) {
#line 175 "ActionScriptParser.g"
		node->append(event);
#line 629 "ActionScriptParser.cpp"
	}
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == 19)) {
			match(19);
			event=literal();
			if ( inputState->guessing==0 ) {
#line 175 "ActionScriptParser.g"
				node->append(event);
#line 639 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop40;
		}
		
	}
	_loop40:;
	} // ( ... )*
	match(8);
	body=statement();
	if ( inputState->guessing==0 ) {
#line 176 "ActionScriptParser.g"
		node->append(body);
#line 654 "ActionScriptParser.cpp"
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::on() {
#line 179 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 663 "ActionScriptParser.cpp"
#line 179 "ActionScriptParser.g"
	
	translate::ASNode* event = 0;
	translate::ASNode* body = 0;
	
	node = translate::NewASNode(translate::ASNode::On);
	
#line 671 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_on);
	match(7);
	{
	switch ( LA(1)) {
	case IDENTIFIER:
	case NUMERIC_LITERAL:
	case STRING_LITERAL:
	case QUOTED_LITERAL:
	{
		event=literal();
		break;
	}
	case LITERAL_keyPress:
	{
		match(LITERAL_keyPress);
		event=literal();
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	if ( inputState->guessing==0 ) {
#line 189 "ActionScriptParser.g"
		node->append(event);
#line 701 "ActionScriptParser.cpp"
	}
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == 19)) {
			match(19);
			{
			switch ( LA(1)) {
			case IDENTIFIER:
			case NUMERIC_LITERAL:
			case STRING_LITERAL:
			case QUOTED_LITERAL:
			{
				event=literal();
				break;
			}
			case LITERAL_keyPress:
			{
				match(LITERAL_keyPress);
				event=literal();
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 190 "ActionScriptParser.g"
				node->append(event);
#line 732 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop46;
		}
		
	}
	_loop46:;
	} // ( ... )*
	match(8);
	body=statement();
	if ( inputState->guessing==0 ) {
#line 191 "ActionScriptParser.g"
		node->append(body);
#line 747 "ActionScriptParser.cpp"
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::breakStatement() {
#line 194 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 756 "ActionScriptParser.cpp"
#line 194 "ActionScriptParser.g"
	
	node = translate::NewASNode(translate::ASNode::Break);
	
#line 761 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_break);
	match(9);
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::continueStatement() {
#line 203 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 773 "ActionScriptParser.cpp"
#line 203 "ActionScriptParser.g"
	
	node = translate::NewASNode(translate::ASNode::Continue);
	
#line 778 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_continue);
	match(9);
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::returnStatement() {
#line 212 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 790 "ActionScriptParser.cpp"
#line 212 "ActionScriptParser.g"
	
	translate::ASNode* expr = 0;
	node = translate::NewASNode(translate::ASNode::Return);
	
#line 796 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_return);
	{
	switch ( LA(1)) {
	case 4:
	case LITERAL_function:
	case IDENTIFIER:
	case 7:
	case PLUS:
	case MINUS:
	case INC:
	case DEC:
	case BIT_NOT:
	case LOGICAL_NOT:
	case LITERAL_delete:
	case 65:
	case LITERAL_new:
	case NUMERIC_LITERAL:
	case STRING_LITERAL:
	case QUOTED_LITERAL:
	{
		expr=conditionalExpression();
		if ( inputState->guessing==0 ) {
#line 219 "ActionScriptParser.g"
			node->append(expr);
#line 823 "ActionScriptParser.cpp"
		}
		break;
	}
	case 9:
	{
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	match(9);
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::expressionStatement() {
#line 67 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 845 "ActionScriptParser.cpp"
#line 67 "ActionScriptParser.g"
	
	translate::ASNode* expr = 0;
	node = translate::NewASNode(translate::ASNode::NoOp); 
	
#line 851 "ActionScriptParser.cpp"
	
	{
	{
	switch ( LA(1)) {
	case 4:
	case LITERAL_function:
	case IDENTIFIER:
	case 7:
	case LITERAL_var:
	case PLUS:
	case MINUS:
	case INC:
	case DEC:
	case BIT_NOT:
	case LOGICAL_NOT:
	case LITERAL_delete:
	case 65:
	case LITERAL_new:
	case NUMERIC_LITERAL:
	case STRING_LITERAL:
	case QUOTED_LITERAL:
	{
		expr=expressionList();
		if ( inputState->guessing==0 ) {
#line 74 "ActionScriptParser.g"
			delete node; node = expr;
#line 878 "ActionScriptParser.cpp"
		}
		break;
	}
	case 9:
	{
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	match(9);
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::argumentList() {
#line 241 "ActionScriptParser.g"
	 translate::ASNode* block ;
#line 900 "ActionScriptParser.cpp"
#line 241 "ActionScriptParser.g"
	
	block = translate::NewASNode(translate::ASNode::List); 
	translate::ASNode* node = 0; 
	
#line 906 "ActionScriptParser.cpp"
	
	{
	node=conditionalExpression();
	if ( inputState->guessing==0 ) {
#line 248 "ActionScriptParser.g"
		block->append(node);
#line 913 "ActionScriptParser.cpp"
	}
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == 19)) {
			match(19);
			node=conditionalExpression();
			if ( inputState->guessing==0 ) {
#line 248 "ActionScriptParser.g"
				block->append(node);
#line 923 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop61;
		}
		
	}
	_loop61:;
	} // ( ... )*
	if ( inputState->guessing==0 ) {
#line 249 "ActionScriptParser.g"
		
		if (block->count() == 1)
		{
		node = block->remove(0);
		delete block;
		block = node;
		}
		
#line 943 "ActionScriptParser.cpp"
	}
	}
	return block ;
}

 translate::ASNode*  ActionScriptParser::expressionList() {
#line 222 "ActionScriptParser.g"
	 translate::ASNode* block ;
#line 952 "ActionScriptParser.cpp"
#line 222 "ActionScriptParser.g"
	
	block = translate::NewASNode(translate::ASNode::ExpressionList); 
	translate::ASNode* node = 0; 
	
#line 958 "ActionScriptParser.cpp"
	
	{
	node=expression();
	if ( inputState->guessing==0 ) {
#line 229 "ActionScriptParser.g"
		block->append(node);
#line 965 "ActionScriptParser.cpp"
	}
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == 19)) {
			match(19);
			node=expression();
			if ( inputState->guessing==0 ) {
#line 230 "ActionScriptParser.g"
				block->append(node);
#line 975 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop57;
		}
		
	}
	_loop57:;
	} // ( ... )*
	if ( inputState->guessing==0 ) {
#line 231 "ActionScriptParser.g"
		
		if (block->count() == 1)
		{
		node = block->remove(0);
		delete block;
		block = node;
		}
		
#line 995 "ActionScriptParser.cpp"
	}
	}
	return block ;
}

 translate::ASNode*  ActionScriptParser::conditionalExpression() {
#line 311 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 1004 "ActionScriptParser.cpp"
#line 311 "ActionScriptParser.g"
	
	translate::ASNode* cond = 0;
	translate::ASNode* left = 0;
	translate::ASNode* right = 0; 
	
#line 1011 "ActionScriptParser.cpp"
	
	{
	node=logicalOrExpression();
	{
	switch ( LA(1)) {
	case 38:
	{
		match(38);
		left=expression();
		match(39);
		right=conditionalExpression();
		if ( inputState->guessing==0 ) {
#line 321 "ActionScriptParser.g"
			cond = node; 
			node = translate::NewASNode(translate::ASNode::Select); 
			node->append(cond);
			node->append(left);
			node->append(right);
			
#line 1031 "ActionScriptParser.cpp"
		}
		break;
	}
	case 8:
	case 9:
	case 10:
	case 19:
	case ASSIGN:
	case ASSIGN_ADD:
	case ASSIGN_SUB:
	case ASSIGN_MUL:
	case ASSIGN_DIV:
	case ASSIGN_MOD:
	case ASSIGN_LSL:
	case ASSIGN_ASR:
	case ASSIGN_LSR:
	case ASSIGN_AND:
	case ASSIGN_OR:
	case ASSIGN_XOR:
	case 39:
	case 66:
	{
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::literal() {
#line 667 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 1069 "ActionScriptParser.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefToken  a = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  b = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  c = ANTLR_USE_NAMESPACE(antlr)nullToken;
	ANTLR_USE_NAMESPACE(antlr)RefToken  d = ANTLR_USE_NAMESPACE(antlr)nullToken;
	
	{
	switch ( LA(1)) {
	case IDENTIFIER:
	{
		a = LT(1);
		match(IDENTIFIER);
		if ( inputState->guessing==0 ) {
#line 669 "ActionScriptParser.g"
			node = translate::ValueASNode(translate::ASNode::Identifier, a->getText().c_str());
#line 1084 "ActionScriptParser.cpp"
		}
		break;
	}
	case NUMERIC_LITERAL:
	{
		b = LT(1);
		match(NUMERIC_LITERAL);
		if ( inputState->guessing==0 ) {
#line 670 "ActionScriptParser.g"
			node = translate::ValueASNode(translate::ASNode::Number, b->getText().c_str());
#line 1095 "ActionScriptParser.cpp"
		}
		break;
	}
	case STRING_LITERAL:
	{
		c = LT(1);
		match(STRING_LITERAL);
		if ( inputState->guessing==0 ) {
#line 671 "ActionScriptParser.g"
			node = translate::ValueASNode(translate::ASNode::String, c->getText().substr(1, c->getText().length()-2).c_str());
#line 1106 "ActionScriptParser.cpp"
		}
		break;
	}
	case QUOTED_LITERAL:
	{
		d = LT(1);
		match(QUOTED_LITERAL);
		if ( inputState->guessing==0 ) {
#line 672 "ActionScriptParser.g"
			node = translate::ValueASNode(translate::ASNode::String, d->getText().substr(1, d->getText().length()-2).c_str());
#line 1117 "ActionScriptParser.cpp"
		}
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::expression() {
#line 263 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 1133 "ActionScriptParser.cpp"
	
	{
	node=assignmentExpression();
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::assignmentExpression() {
#line 270 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 1144 "ActionScriptParser.cpp"
#line 270 "ActionScriptParser.g"
	
	translate::ASNode::NodeType type = translate::ASNode::NoOp; 
	translate::ASNode* left = 0;
	translate::ASNode* right = 0;
	bool isVar = false;
	
#line 1152 "ActionScriptParser.cpp"
	
	{
	{
	switch ( LA(1)) {
	case LITERAL_var:
	{
		match(LITERAL_var);
		if ( inputState->guessing==0 ) {
#line 279 "ActionScriptParser.g"
			isVar = true;
#line 1163 "ActionScriptParser.cpp"
		}
		break;
	}
	case 4:
	case LITERAL_function:
	case IDENTIFIER:
	case 7:
	case PLUS:
	case MINUS:
	case INC:
	case DEC:
	case BIT_NOT:
	case LOGICAL_NOT:
	case LITERAL_delete:
	case 65:
	case LITERAL_new:
	case NUMERIC_LITERAL:
	case STRING_LITERAL:
	case QUOTED_LITERAL:
	{
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	node=conditionalExpression();
	if ( inputState->guessing==0 ) {
#line 279 "ActionScriptParser.g"
		if (isVar) node->setType(translate::ASNode::DefineVariable);
#line 1196 "ActionScriptParser.cpp"
	}
	{
	switch ( LA(1)) {
	case ASSIGN:
	case ASSIGN_ADD:
	case ASSIGN_SUB:
	case ASSIGN_MUL:
	case ASSIGN_DIV:
	case ASSIGN_MOD:
	case ASSIGN_LSL:
	case ASSIGN_ASR:
	case ASSIGN_LSR:
	case ASSIGN_AND:
	case ASSIGN_OR:
	case ASSIGN_XOR:
	{
		{
		switch ( LA(1)) {
		case ASSIGN:
		{
			match(ASSIGN);
			if ( inputState->guessing==0 ) {
#line 281 "ActionScriptParser.g"
				type = translate::ASNode::Assign;
#line 1221 "ActionScriptParser.cpp"
			}
			break;
		}
		case ASSIGN_ADD:
		{
			match(ASSIGN_ADD);
			if ( inputState->guessing==0 ) {
#line 282 "ActionScriptParser.g"
				type = translate::ASNode::AssignAdd;
#line 1231 "ActionScriptParser.cpp"
			}
			break;
		}
		case ASSIGN_SUB:
		{
			match(ASSIGN_SUB);
			if ( inputState->guessing==0 ) {
#line 283 "ActionScriptParser.g"
				type = translate::ASNode::AssignSub;
#line 1241 "ActionScriptParser.cpp"
			}
			break;
		}
		case ASSIGN_MUL:
		{
			match(ASSIGN_MUL);
			if ( inputState->guessing==0 ) {
#line 284 "ActionScriptParser.g"
				type = translate::ASNode::AssignMul;
#line 1251 "ActionScriptParser.cpp"
			}
			break;
		}
		case ASSIGN_DIV:
		{
			match(ASSIGN_DIV);
			if ( inputState->guessing==0 ) {
#line 285 "ActionScriptParser.g"
				type = translate::ASNode::AssignDiv;
#line 1261 "ActionScriptParser.cpp"
			}
			break;
		}
		case ASSIGN_MOD:
		{
			match(ASSIGN_MOD);
			if ( inputState->guessing==0 ) {
#line 286 "ActionScriptParser.g"
				type = translate::ASNode::AssignMod;
#line 1271 "ActionScriptParser.cpp"
			}
			break;
		}
		case ASSIGN_LSL:
		{
			match(ASSIGN_LSL);
			if ( inputState->guessing==0 ) {
#line 287 "ActionScriptParser.g"
				type = translate::ASNode::AssignLSL;
#line 1281 "ActionScriptParser.cpp"
			}
			break;
		}
		case ASSIGN_ASR:
		{
			match(ASSIGN_ASR);
			if ( inputState->guessing==0 ) {
#line 288 "ActionScriptParser.g"
				type = translate::ASNode::AssignASR;
#line 1291 "ActionScriptParser.cpp"
			}
			break;
		}
		case ASSIGN_LSR:
		{
			match(ASSIGN_LSR);
			if ( inputState->guessing==0 ) {
#line 289 "ActionScriptParser.g"
				type = translate::ASNode::AssignLSR;
#line 1301 "ActionScriptParser.cpp"
			}
			break;
		}
		case ASSIGN_AND:
		{
			match(ASSIGN_AND);
			if ( inputState->guessing==0 ) {
#line 290 "ActionScriptParser.g"
				type = translate::ASNode::AssignBitAnd;
#line 1311 "ActionScriptParser.cpp"
			}
			break;
		}
		case ASSIGN_OR:
		{
			match(ASSIGN_OR);
			if ( inputState->guessing==0 ) {
#line 291 "ActionScriptParser.g"
				type = translate::ASNode::AssignBitOr;
#line 1321 "ActionScriptParser.cpp"
			}
			break;
		}
		case ASSIGN_XOR:
		{
			match(ASSIGN_XOR);
			if ( inputState->guessing==0 ) {
#line 292 "ActionScriptParser.g"
				type = translate::ASNode::AssignBitXOr;
#line 1331 "ActionScriptParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		right=assignmentExpression();
		if ( inputState->guessing==0 ) {
#line 296 "ActionScriptParser.g"
			
			node = translate::BinaryASNode(type, node, right); 
			
#line 1347 "ActionScriptParser.cpp"
		}
		break;
	}
	case 8:
	case 9:
	case 19:
	case 39:
	{
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::logicalOrExpression() {
#line 330 "ActionScriptParser.g"
	 translate::ASNode* left ;
#line 1371 "ActionScriptParser.cpp"
#line 330 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	
#line 1376 "ActionScriptParser.cpp"
	
	{
	left=logicalAndExpression();
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == LOGICAL_OR)) {
			match(LOGICAL_OR);
			right=logicalAndExpression();
			if ( inputState->guessing==0 ) {
#line 337 "ActionScriptParser.g"
				left = translate::BinaryASNode(translate::ASNode::Or, left, right);
#line 1388 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop75;
		}
		
	}
	_loop75:;
	} // ( ... )*
	}
	return left ;
}

 translate::ASNode*  ActionScriptParser::logicalAndExpression() {
#line 341 "ActionScriptParser.g"
	 translate::ASNode* left ;
#line 1405 "ActionScriptParser.cpp"
#line 341 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	
#line 1410 "ActionScriptParser.cpp"
	
	{
	left=inclusiveOrExpression();
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == LOGICAL_AND)) {
			match(LOGICAL_AND);
			right=inclusiveOrExpression();
			if ( inputState->guessing==0 ) {
#line 348 "ActionScriptParser.g"
				left = translate::BinaryASNode(translate::ASNode::And, left, right);
#line 1422 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop79;
		}
		
	}
	_loop79:;
	} // ( ... )*
	}
	return left ;
}

 translate::ASNode*  ActionScriptParser::inclusiveOrExpression() {
#line 352 "ActionScriptParser.g"
	 translate::ASNode* left ;
#line 1439 "ActionScriptParser.cpp"
#line 352 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	
#line 1444 "ActionScriptParser.cpp"
	
	{
	left=exclusiveOrExpression();
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == BIT_OR)) {
			match(BIT_OR);
			right=exclusiveOrExpression();
			if ( inputState->guessing==0 ) {
#line 359 "ActionScriptParser.g"
				left = translate::BinaryASNode(translate::ASNode::BitOr, left, right);
#line 1456 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop83;
		}
		
	}
	_loop83:;
	} // ( ... )*
	}
	return left ;
}

 translate::ASNode*  ActionScriptParser::exclusiveOrExpression() {
#line 363 "ActionScriptParser.g"
	 translate::ASNode* left ;
#line 1473 "ActionScriptParser.cpp"
#line 363 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	
#line 1478 "ActionScriptParser.cpp"
	
	{
	left=andExpression();
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == BIT_XOR)) {
			match(BIT_XOR);
			right=andExpression();
			if ( inputState->guessing==0 ) {
#line 370 "ActionScriptParser.g"
				left = translate::BinaryASNode(translate::ASNode::BitXOr, left, right);
#line 1490 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop87;
		}
		
	}
	_loop87:;
	} // ( ... )*
	}
	return left ;
}

 translate::ASNode*  ActionScriptParser::andExpression() {
#line 374 "ActionScriptParser.g"
	 translate::ASNode* left ;
#line 1507 "ActionScriptParser.cpp"
#line 374 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	
#line 1512 "ActionScriptParser.cpp"
	
	{
	left=equalityExpression();
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == BIT_AND)) {
			match(BIT_AND);
			right=equalityExpression();
			if ( inputState->guessing==0 ) {
#line 381 "ActionScriptParser.g"
				left = translate::BinaryASNode(translate::ASNode::BitAnd, left, right);
#line 1524 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop91;
		}
		
	}
	_loop91:;
	} // ( ... )*
	}
	return left ;
}

 translate::ASNode*  ActionScriptParser::equalityExpression() {
#line 385 "ActionScriptParser.g"
	 translate::ASNode* left ;
#line 1541 "ActionScriptParser.cpp"
#line 385 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	translate::ASNode::NodeType type = translate::ASNode::NoOp;
	
#line 1547 "ActionScriptParser.cpp"
	
	{
	left=relationalExpression();
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == EQ || LA(1) == NE)) {
			{
			switch ( LA(1)) {
			case EQ:
			{
				match(EQ);
				if ( inputState->guessing==0 ) {
#line 393 "ActionScriptParser.g"
					type = translate::ASNode::Equal;
#line 1562 "ActionScriptParser.cpp"
				}
				break;
			}
			case NE:
			{
				match(NE);
				if ( inputState->guessing==0 ) {
#line 394 "ActionScriptParser.g"
					type = translate::ASNode::NotEqual;
#line 1572 "ActionScriptParser.cpp"
				}
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			right=relationalExpression();
			if ( inputState->guessing==0 ) {
#line 398 "ActionScriptParser.g"
				left = translate::BinaryASNode(type, left, right);
#line 1586 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop96;
		}
		
	}
	_loop96:;
	} // ( ... )*
	}
	return left ;
}

 translate::ASNode*  ActionScriptParser::relationalExpression() {
#line 402 "ActionScriptParser.g"
	 translate::ASNode* left ;
#line 1603 "ActionScriptParser.cpp"
#line 402 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	translate::ASNode::NodeType type = translate::ASNode::NoOp;
	
#line 1609 "ActionScriptParser.cpp"
	
	{
	left=instanceExpression();
	{ // ( ... )*
	for (;;) {
		if (((LA(1) >= LTHAN && LA(1) <= GTE))) {
			{
			switch ( LA(1)) {
			case LTHAN:
			{
				match(LTHAN);
				if ( inputState->guessing==0 ) {
#line 410 "ActionScriptParser.g"
					type = translate::ASNode::LessThan;
#line 1624 "ActionScriptParser.cpp"
				}
				break;
			}
			case GTHAN:
			{
				match(GTHAN);
				if ( inputState->guessing==0 ) {
#line 411 "ActionScriptParser.g"
					type = translate::ASNode::GreaterThan;
#line 1634 "ActionScriptParser.cpp"
				}
				break;
			}
			case LTE:
			{
				match(LTE);
				if ( inputState->guessing==0 ) {
#line 412 "ActionScriptParser.g"
					type = translate::ASNode::LessThanEqual;
#line 1644 "ActionScriptParser.cpp"
				}
				break;
			}
			case GTE:
			{
				match(GTE);
				if ( inputState->guessing==0 ) {
#line 413 "ActionScriptParser.g"
					type = translate::ASNode::GreaterThanEqual;
#line 1654 "ActionScriptParser.cpp"
				}
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			right=instanceExpression();
			if ( inputState->guessing==0 ) {
#line 417 "ActionScriptParser.g"
				left = translate::BinaryASNode(type, left, right);
#line 1668 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop101;
		}
		
	}
	_loop101:;
	} // ( ... )*
	}
	return left ;
}

 translate::ASNode*  ActionScriptParser::instanceExpression() {
#line 421 "ActionScriptParser.g"
	 translate::ASNode* left ;
#line 1685 "ActionScriptParser.cpp"
#line 421 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	translate::ASNode::NodeType type = translate::ASNode::NoOp;
	
#line 1691 "ActionScriptParser.cpp"
	
	{
	left=shiftExpression();
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == LITERAL_instanceof)) {
			match(LITERAL_instanceof);
			if ( inputState->guessing==0 ) {
#line 429 "ActionScriptParser.g"
				type = translate::ASNode::InstanceOf;
#line 1702 "ActionScriptParser.cpp"
			}
			right=shiftExpression();
			if ( inputState->guessing==0 ) {
#line 432 "ActionScriptParser.g"
				left = translate::BinaryASNode(type, left, right);
#line 1708 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop105;
		}
		
	}
	_loop105:;
	} // ( ... )*
	}
	return left ;
}

 translate::ASNode*  ActionScriptParser::shiftExpression() {
#line 436 "ActionScriptParser.g"
	 translate::ASNode* left ;
#line 1725 "ActionScriptParser.cpp"
#line 436 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	translate::ASNode::NodeType type = translate::ASNode::NoOp;
	
#line 1731 "ActionScriptParser.cpp"
	
	{
	left=additiveExpression();
	{ // ( ... )*
	for (;;) {
		if (((LA(1) >= LSL && LA(1) <= ASR))) {
			{
			switch ( LA(1)) {
			case LSL:
			{
				match(LSL);
				if ( inputState->guessing==0 ) {
#line 444 "ActionScriptParser.g"
					type = translate::ASNode::LSL;
#line 1746 "ActionScriptParser.cpp"
				}
				break;
			}
			case LSR:
			{
				match(LSR);
				if ( inputState->guessing==0 ) {
#line 445 "ActionScriptParser.g"
					type = translate::ASNode::LSR;
#line 1756 "ActionScriptParser.cpp"
				}
				break;
			}
			case ASR:
			{
				match(ASR);
				if ( inputState->guessing==0 ) {
#line 446 "ActionScriptParser.g"
					type = translate::ASNode::ASR;
#line 1766 "ActionScriptParser.cpp"
				}
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			right=additiveExpression();
			if ( inputState->guessing==0 ) {
#line 449 "ActionScriptParser.g"
				left = translate::BinaryASNode(type, left, right);
#line 1780 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop110;
		}
		
	}
	_loop110:;
	} // ( ... )*
	}
	return left ;
}

 translate::ASNode*  ActionScriptParser::additiveExpression() {
#line 453 "ActionScriptParser.g"
	 translate::ASNode* left ;
#line 1797 "ActionScriptParser.cpp"
#line 453 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	translate::ASNode::NodeType type = translate::ASNode::NoOp;
	
#line 1803 "ActionScriptParser.cpp"
	
	{
	left=multiplicativeExpression();
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == PLUS || LA(1) == MINUS)) {
			{
			switch ( LA(1)) {
			case PLUS:
			{
				match(PLUS);
				if ( inputState->guessing==0 ) {
#line 461 "ActionScriptParser.g"
					type = translate::ASNode::Add;
#line 1818 "ActionScriptParser.cpp"
				}
				break;
			}
			case MINUS:
			{
				match(MINUS);
				if ( inputState->guessing==0 ) {
#line 462 "ActionScriptParser.g"
					type = translate::ASNode::Sub;
#line 1828 "ActionScriptParser.cpp"
				}
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			right=multiplicativeExpression();
			if ( inputState->guessing==0 ) {
#line 465 "ActionScriptParser.g"
				left = translate::BinaryASNode(type, left, right);
#line 1842 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop115;
		}
		
	}
	_loop115:;
	} // ( ... )*
	}
	return left ;
}

 translate::ASNode*  ActionScriptParser::multiplicativeExpression() {
#line 469 "ActionScriptParser.g"
	 translate::ASNode* left ;
#line 1859 "ActionScriptParser.cpp"
#line 469 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	translate::ASNode::NodeType type = translate::ASNode::NoOp;
	
#line 1865 "ActionScriptParser.cpp"
	
	{
	left=unaryExpression();
	{ // ( ... )*
	for (;;) {
		if (((LA(1) >= MULTIPLY && LA(1) <= MOD))) {
			{
			switch ( LA(1)) {
			case MULTIPLY:
			{
				match(MULTIPLY);
				if ( inputState->guessing==0 ) {
#line 477 "ActionScriptParser.g"
					type = translate::ASNode::Mul;
#line 1880 "ActionScriptParser.cpp"
				}
				break;
			}
			case DIVIDE:
			{
				match(DIVIDE);
				if ( inputState->guessing==0 ) {
#line 478 "ActionScriptParser.g"
					type = translate::ASNode::Div;
#line 1890 "ActionScriptParser.cpp"
				}
				break;
			}
			case MOD:
			{
				match(MOD);
				if ( inputState->guessing==0 ) {
#line 479 "ActionScriptParser.g"
					type = translate::ASNode::Mod;
#line 1900 "ActionScriptParser.cpp"
				}
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			right=unaryExpression();
			if ( inputState->guessing==0 ) {
#line 482 "ActionScriptParser.g"
				left = translate::BinaryASNode(type, left, right);
#line 1914 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop120;
		}
		
	}
	_loop120:;
	} // ( ... )*
	}
	return left ;
}

 translate::ASNode*  ActionScriptParser::unaryExpression() {
#line 486 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 1931 "ActionScriptParser.cpp"
#line 486 "ActionScriptParser.g"
	
	translate::ASNode* right = 0;
	
#line 1936 "ActionScriptParser.cpp"
	
	{
	switch ( LA(1)) {
	case PLUS:
	{
		match(PLUS);
		right=unaryExpression();
		if ( inputState->guessing==0 ) {
#line 493 "ActionScriptParser.g"
			node = translate::NewASNode(translate::ASNode::Plus); node->append(right);
#line 1947 "ActionScriptParser.cpp"
		}
		break;
	}
	case MINUS:
	{
		match(MINUS);
		right=unaryExpression();
		if ( inputState->guessing==0 ) {
#line 495 "ActionScriptParser.g"
			node = translate::NewASNode(translate::ASNode::Minus); node->append(right);
#line 1958 "ActionScriptParser.cpp"
		}
		break;
	}
	case INC:
	{
		match(INC);
		right=primaryExpression();
		if ( inputState->guessing==0 ) {
#line 497 "ActionScriptParser.g"
			node = translate::NewASNode(translate::ASNode::PreInc); node->append(right);
#line 1969 "ActionScriptParser.cpp"
		}
		break;
	}
	case DEC:
	{
		match(DEC);
		right=primaryExpression();
		if ( inputState->guessing==0 ) {
#line 499 "ActionScriptParser.g"
			node = translate::NewASNode(translate::ASNode::PreDec); node->append(right);
#line 1980 "ActionScriptParser.cpp"
		}
		break;
	}
	case BIT_NOT:
	{
		match(BIT_NOT);
		right=unaryExpression();
		if ( inputState->guessing==0 ) {
#line 501 "ActionScriptParser.g"
			node = translate::NewASNode(translate::ASNode::BitNot); node->append(right);
#line 1991 "ActionScriptParser.cpp"
		}
		break;
	}
	case LOGICAL_NOT:
	{
		match(LOGICAL_NOT);
		right=unaryExpression();
		if ( inputState->guessing==0 ) {
#line 503 "ActionScriptParser.g"
			node = translate::NewASNode(translate::ASNode::Not); node->append(right);
#line 2002 "ActionScriptParser.cpp"
		}
		break;
	}
	case LITERAL_delete:
	{
		match(LITERAL_delete);
		right=unaryExpression();
		if ( inputState->guessing==0 ) {
#line 505 "ActionScriptParser.g"
			node = translate::NewASNode(translate::ASNode::DeleteObject); node->append(right);
#line 2013 "ActionScriptParser.cpp"
		}
		break;
	}
	case 4:
	case LITERAL_function:
	case IDENTIFIER:
	case 7:
	case 65:
	case LITERAL_new:
	case NUMERIC_LITERAL:
	case STRING_LITERAL:
	case QUOTED_LITERAL:
	{
		node=postfixExpression();
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::primaryExpression() {
#line 532 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 2042 "ActionScriptParser.cpp"
#line 532 "ActionScriptParser.g"
	
	translate::ASNode* expr = 0;
	node = translate::NewASNode(translate::ASNode::Value);
	
#line 2048 "ActionScriptParser.cpp"
	
	{
	expr=primaryPrefix();
	if ( inputState->guessing==0 ) {
#line 539 "ActionScriptParser.g"
		node->append(expr);
#line 2055 "ActionScriptParser.cpp"
	}
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == 7 || LA(1) == 65 || LA(1) == 67)) {
			expr=primarySuffix();
			if ( inputState->guessing==0 ) {
#line 540 "ActionScriptParser.g"
				node->append(expr);
#line 2064 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop131;
		}
		
	}
	_loop131:;
	} // ( ... )*
	if ( inputState->guessing==0 ) {
#line 541 "ActionScriptParser.g"
		
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
		
#line 2103 "ActionScriptParser.cpp"
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::postfixExpression() {
#line 509 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 2112 "ActionScriptParser.cpp"
#line 509 "ActionScriptParser.g"
	
	translate::ASNode* expr = 0;
	translate::ASNode::NodeType type = translate::ASNode::NoOp;
	
#line 2118 "ActionScriptParser.cpp"
	
	{
	node=primaryExpression();
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == INC || LA(1) == DEC)) {
			{
			switch ( LA(1)) {
			case INC:
			{
				match(INC);
				if ( inputState->guessing==0 ) {
#line 517 "ActionScriptParser.g"
					type = translate::ASNode::PostInc;
#line 2133 "ActionScriptParser.cpp"
				}
				break;
			}
			case DEC:
			{
				match(DEC);
				if ( inputState->guessing==0 ) {
#line 518 "ActionScriptParser.g"
					type = translate::ASNode::PostDec;
#line 2143 "ActionScriptParser.cpp"
				}
				break;
			}
			default:
			{
				throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
			}
			}
			}
			if ( inputState->guessing==0 ) {
#line 519 "ActionScriptParser.g"
				expr = node; node = translate::NewASNode(type); node->append(expr);
#line 2156 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop127;
		}
		
	}
	_loop127:;
	} // ( ... )*
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::primaryPrefix() {
#line 570 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 2173 "ActionScriptParser.cpp"
	
	{
	switch ( LA(1)) {
	case 65:
	{
		node=anonymousArray();
		break;
	}
	case 4:
	{
		node=anonymousObject();
		break;
	}
	case LITERAL_function:
	{
		node=methodDefinition();
		break;
	}
	case LITERAL_new:
	{
		node=constructor();
		break;
	}
	case IDENTIFIER:
	case NUMERIC_LITERAL:
	case STRING_LITERAL:
	case QUOTED_LITERAL:
	{
		node=literal();
		break;
	}
	case 7:
	{
		match(7);
		node=conditionalExpression();
		match(8);
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::primarySuffix() {
#line 581 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 2224 "ActionScriptParser.cpp"
#line 581 "ActionScriptParser.g"
	
	translate::ASNode* expr = 0;
	
#line 2229 "ActionScriptParser.cpp"
	
	{
	switch ( LA(1)) {
	case 65:
	{
		match(65);
		expr=conditionalExpression();
		match(66);
		if ( inputState->guessing==0 ) {
#line 588 "ActionScriptParser.g"
			node = translate::NewASNode(translate::ASNode::Subscript); node->append(expr);
#line 2241 "ActionScriptParser.cpp"
		}
		break;
	}
	case 67:
	{
		match(67);
		{
		switch ( LA(1)) {
		case IDENTIFIER:
		case NUMERIC_LITERAL:
		case STRING_LITERAL:
		case QUOTED_LITERAL:
		{
			node=literal();
			if ( inputState->guessing==0 ) {
#line 589 "ActionScriptParser.g"
				node->setType(translate::ASNode::Attribute);
#line 2259 "ActionScriptParser.cpp"
			}
			break;
		}
		case 7:
		{
			node=function();
			if ( inputState->guessing==0 ) {
#line 590 "ActionScriptParser.g"
				node->setType(translate::ASNode::Method);
#line 2269 "ActionScriptParser.cpp"
			}
			break;
		}
		default:
		{
			throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
		}
		}
		}
		break;
	}
	case 7:
	{
		node=function();
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::anonymousArray() {
#line 617 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 2298 "ActionScriptParser.cpp"
#line 617 "ActionScriptParser.g"
	
	node = translate::NewASNode(translate::ASNode::DefineArray);
	translate::ASNode* element = 0;
	
#line 2304 "ActionScriptParser.cpp"
	
	{
	match(65);
	{
	switch ( LA(1)) {
	case 4:
	case LITERAL_function:
	case IDENTIFIER:
	case 7:
	case PLUS:
	case MINUS:
	case INC:
	case DEC:
	case BIT_NOT:
	case LOGICAL_NOT:
	case LITERAL_delete:
	case 65:
	case LITERAL_new:
	case NUMERIC_LITERAL:
	case STRING_LITERAL:
	case QUOTED_LITERAL:
	{
		element=conditionalExpression();
		if ( inputState->guessing==0 ) {
#line 624 "ActionScriptParser.g"
			node->append(element);
#line 2331 "ActionScriptParser.cpp"
		}
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == 19)) {
				match(19);
				element=conditionalExpression();
				if ( inputState->guessing==0 ) {
#line 625 "ActionScriptParser.g"
					node->append(element);
#line 2341 "ActionScriptParser.cpp"
				}
			}
			else {
				goto _loop151;
			}
			
		}
		_loop151:;
		} // ( ... )*
		break;
	}
	case 66:
	{
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	match(66);
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::anonymousObject() {
#line 641 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 2371 "ActionScriptParser.cpp"
#line 641 "ActionScriptParser.g"
	
	translate::ASNode* attr = 0;
	translate::ASNode* expr = 0;
	
	node = translate::NewASNode(translate::ASNode::List); 
	
#line 2379 "ActionScriptParser.cpp"
	
	{
	match(4);
	attr=attribute();
	if ( inputState->guessing==0 ) {
#line 651 "ActionScriptParser.g"
		node->setType(translate::ASNode::DefineObject); node->append(attr);
#line 2387 "ActionScriptParser.cpp"
	}
	{ // ( ... )*
	for (;;) {
		if ((LA(1) == 19)) {
			match(19);
			attr=attribute();
			if ( inputState->guessing==0 ) {
#line 651 "ActionScriptParser.g"
				node->append(attr);
#line 2397 "ActionScriptParser.cpp"
			}
		}
		else {
			goto _loop158;
		}
		
	}
	_loop158:;
	} // ( ... )*
	match(10);
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::methodDefinition() {
#line 630 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 2415 "ActionScriptParser.cpp"
#line 630 "ActionScriptParser.g"
	
	translate::ASNode* args = 0;
	translate::ASNode* body = 0;
	node = translate::NewASNode(translate::ASNode::DefineMethod);
	
#line 2422 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_function);
	match(7);
	{
	switch ( LA(1)) {
	case 4:
	case LITERAL_function:
	case IDENTIFIER:
	case 7:
	case PLUS:
	case MINUS:
	case INC:
	case DEC:
	case BIT_NOT:
	case LOGICAL_NOT:
	case LITERAL_delete:
	case 65:
	case LITERAL_new:
	case NUMERIC_LITERAL:
	case STRING_LITERAL:
	case QUOTED_LITERAL:
	{
		args=argumentList();
		if ( inputState->guessing==0 ) {
#line 638 "ActionScriptParser.g"
			node->append(args);
#line 2450 "ActionScriptParser.cpp"
		}
		break;
	}
	case 8:
	{
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	match(8);
	body=blockStatement();
	if ( inputState->guessing==0 ) {
#line 638 "ActionScriptParser.g"
		node->append(body);
#line 2469 "ActionScriptParser.cpp"
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::constructor() {
#line 605 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 2478 "ActionScriptParser.cpp"
	ANTLR_USE_NAMESPACE(antlr)RefToken  t = ANTLR_USE_NAMESPACE(antlr)nullToken;
#line 605 "ActionScriptParser.g"
	
	node = translate::NewASNode(translate::ASNode::NewObject);
	translate::ASNode* arg = 0;
	
#line 2485 "ActionScriptParser.cpp"
	
	{
	match(LITERAL_new);
	t = LT(1);
	match(IDENTIFIER);
	match(7);
	{
	switch ( LA(1)) {
	case 4:
	case LITERAL_function:
	case IDENTIFIER:
	case 7:
	case PLUS:
	case MINUS:
	case INC:
	case DEC:
	case BIT_NOT:
	case LOGICAL_NOT:
	case LITERAL_delete:
	case 65:
	case LITERAL_new:
	case NUMERIC_LITERAL:
	case STRING_LITERAL:
	case QUOTED_LITERAL:
	{
		arg=conditionalExpression();
		if ( inputState->guessing==0 ) {
#line 612 "ActionScriptParser.g"
			node->append(arg);
#line 2515 "ActionScriptParser.cpp"
		}
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == 19)) {
				match(19);
				arg=conditionalExpression();
				if ( inputState->guessing==0 ) {
#line 612 "ActionScriptParser.g"
					node->append(arg);
#line 2525 "ActionScriptParser.cpp"
				}
			}
			else {
				goto _loop146;
			}
			
		}
		_loop146:;
		} // ( ... )*
		break;
	}
	case 8:
	{
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	match(8);
	if ( inputState->guessing==0 ) {
#line 614 "ActionScriptParser.g"
		node->setValue(t->getText().c_str());
#line 2551 "ActionScriptParser.cpp"
	}
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::function() {
#line 595 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 2560 "ActionScriptParser.cpp"
#line 595 "ActionScriptParser.g"
	
	node = translate::NewASNode(translate::ASNode::Function);
	translate::ASNode* arg = 0;
	
#line 2566 "ActionScriptParser.cpp"
	
	{
	match(7);
	{
	switch ( LA(1)) {
	case 4:
	case LITERAL_function:
	case IDENTIFIER:
	case 7:
	case PLUS:
	case MINUS:
	case INC:
	case DEC:
	case BIT_NOT:
	case LOGICAL_NOT:
	case LITERAL_delete:
	case 65:
	case LITERAL_new:
	case NUMERIC_LITERAL:
	case STRING_LITERAL:
	case QUOTED_LITERAL:
	{
		arg=conditionalExpression();
		if ( inputState->guessing==0 ) {
#line 602 "ActionScriptParser.g"
			node->append(arg);
#line 2593 "ActionScriptParser.cpp"
		}
		{ // ( ... )*
		for (;;) {
			if ((LA(1) == 19)) {
				match(19);
				arg=conditionalExpression();
				if ( inputState->guessing==0 ) {
#line 602 "ActionScriptParser.g"
					node->append(arg);
#line 2603 "ActionScriptParser.cpp"
				}
			}
			else {
				goto _loop141;
			}
			
		}
		_loop141:;
		} // ( ... )*
		break;
	}
	case 8:
	{
		break;
	}
	default:
	{
		throw ANTLR_USE_NAMESPACE(antlr)NoViableAltException(LT(1), getFilename());
	}
	}
	}
	match(8);
	}
	return node ;
}

 translate::ASNode*  ActionScriptParser::attribute() {
#line 655 "ActionScriptParser.g"
	 translate::ASNode* node ;
#line 2633 "ActionScriptParser.cpp"
#line 655 "ActionScriptParser.g"
	
	translate::ASNode* key = 0;
	translate::ASNode* value = 0;
	
#line 2639 "ActionScriptParser.cpp"
	
	{
	key=literal();
	match(39);
	value=conditionalExpression();
	if ( inputState->guessing==0 ) {
#line 664 "ActionScriptParser.g"
		node = translate::BinaryASNode(translate::ASNode::DefineAttribute, key, value);
#line 2648 "ActionScriptParser.cpp"
	}
	}
	return node ;
}

void ActionScriptParser::initializeASTFactory( ANTLR_USE_NAMESPACE(antlr)ASTFactory& )
{
}
const char* ActionScriptParser::tokenNames[] = {
	"<0>",
	"EOF",
	"<2>",
	"NULL_TREE_LOOKAHEAD",
	"\"{\"",
	"\"function\"",
	"IDENTIFIER",
	"\"(\"",
	"\")\"",
	"\";\"",
	"\"}\"",
	"\"if\"",
	"\"else\"",
	"\"with\"",
	"\"while\"",
	"\"do\"",
	"\"for\"",
	"\"in\"",
	"\"onClipEvent\"",
	"\",\"",
	"\"on\"",
	"\"keyPress\"",
	"\"break\"",
	"\"continue\"",
	"\"return\"",
	"\"var\"",
	"ASSIGN",
	"ASSIGN_ADD",
	"ASSIGN_SUB",
	"ASSIGN_MUL",
	"ASSIGN_DIV",
	"ASSIGN_MOD",
	"ASSIGN_LSL",
	"ASSIGN_ASR",
	"ASSIGN_LSR",
	"ASSIGN_AND",
	"ASSIGN_OR",
	"ASSIGN_XOR",
	"\"?\"",
	"\":\"",
	"LOGICAL_OR",
	"LOGICAL_AND",
	"BIT_OR",
	"BIT_XOR",
	"BIT_AND",
	"EQ",
	"NE",
	"LTHAN",
	"GTHAN",
	"LTE",
	"GTE",
	"\"instanceof\"",
	"LSL",
	"LSR",
	"ASR",
	"PLUS",
	"MINUS",
	"MULTIPLY",
	"DIVIDE",
	"MOD",
	"INC",
	"DEC",
	"BIT_NOT",
	"LOGICAL_NOT",
	"\"delete\"",
	"\"[\"",
	"\"]\"",
	"\".\"",
	"\"new\"",
	"NUMERIC_LITERAL",
	"STRING_LITERAL",
	"QUOTED_LITERAL",
	"LPAREN",
	"RPAREN",
	"LCURLY",
	"RCURLY",
	"LBRACKET",
	"RBRACKET",
	"SEMI",
	"COMMA",
	"SELECT",
	"ALTERNATE",
	"WS",
	"ESC",
	"HEX_DIGIT",
	"EXPONENT",
	0
};

const unsigned long ActionScriptParser::_tokenSet_0_data_[] = { 64350960UL, 4051697664UL, 243UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "{" "function" IDENTIFIER "(" ";" "if" "with" "while" "do" "for" "onClipEvent" 
// "on" "break" "continue" "return" "var" PLUS MINUS INC DEC BIT_NOT LOGICAL_NOT 
// "delete" "[" "new" NUMERIC_LITERAL STRING_LITERAL QUOTED_LITERAL 
const ANTLR_USE_NAMESPACE(antlr)BitSet ActionScriptParser::_tokenSet_0(_tokenSet_0_data_,8);
const unsigned long ActionScriptParser::_tokenSet_1_data_[] = { 64351984UL, 4051697664UL, 243UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "{" "function" IDENTIFIER "(" ";" "}" "if" "with" "while" "do" "for" 
// "onClipEvent" "on" "break" "continue" "return" "var" PLUS MINUS INC 
// DEC BIT_NOT LOGICAL_NOT "delete" "[" "new" NUMERIC_LITERAL STRING_LITERAL 
// QUOTED_LITERAL 
const ANTLR_USE_NAMESPACE(antlr)BitSet ActionScriptParser::_tokenSet_1(_tokenSet_1_data_,8);
const unsigned long ActionScriptParser::_tokenSet_2_data_[] = { 33555184UL, 4051697664UL, 243UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "{" "function" IDENTIFIER "(" ";" "var" PLUS MINUS INC DEC BIT_NOT LOGICAL_NOT 
// "delete" "[" "new" NUMERIC_LITERAL STRING_LITERAL QUOTED_LITERAL 
const ANTLR_USE_NAMESPACE(antlr)BitSet ActionScriptParser::_tokenSet_2(_tokenSet_2_data_,8);
const unsigned long ActionScriptParser::_tokenSet_3_data_[] = { 4292738802UL, 4294967167UL, 255UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// EOF "{" "function" IDENTIFIER "(" ";" "}" "if" "else" "with" "while" 
// "do" "for" "onClipEvent" "," "on" "break" "continue" "return" "var" 
// ASSIGN ASSIGN_ADD ASSIGN_SUB ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD ASSIGN_LSL 
// ASSIGN_ASR ASSIGN_LSR ASSIGN_AND ASSIGN_OR ASSIGN_XOR "?" LOGICAL_OR 
// LOGICAL_AND BIT_OR BIT_XOR BIT_AND EQ NE LTHAN GTHAN LTE GTE "instanceof" 
// LSL LSR ASR PLUS MINUS MULTIPLY DIVIDE MOD INC DEC BIT_NOT LOGICAL_NOT 
// "delete" "[" "]" "." "new" NUMERIC_LITERAL STRING_LITERAL QUOTED_LITERAL 
const ANTLR_USE_NAMESPACE(antlr)BitSet ActionScriptParser::_tokenSet_3(_tokenSet_3_data_,8);
const unsigned long ActionScriptParser::_tokenSet_4_data_[] = { 64356082UL, 4051697664UL, 243UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// EOF "{" "function" IDENTIFIER "(" ";" "}" "if" "else" "with" "while" 
// "do" "for" "onClipEvent" "on" "break" "continue" "return" "var" PLUS 
// MINUS INC DEC BIT_NOT LOGICAL_NOT "delete" "[" "new" NUMERIC_LITERAL 
// STRING_LITERAL QUOTED_LITERAL 
const ANTLR_USE_NAMESPACE(antlr)BitSet ActionScriptParser::_tokenSet_4(_tokenSet_4_data_,8);
const unsigned long ActionScriptParser::_tokenSet_5_data_[] = { 4292739058UL, 4294967295UL, 255UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// EOF "{" "function" IDENTIFIER "(" ")" ";" "}" "if" "else" "with" "while" 
// "do" "for" "onClipEvent" "," "on" "break" "continue" "return" "var" 
// ASSIGN ASSIGN_ADD ASSIGN_SUB ASSIGN_MUL ASSIGN_DIV ASSIGN_MOD ASSIGN_LSL 
// ASSIGN_ASR ASSIGN_LSR ASSIGN_AND ASSIGN_OR ASSIGN_XOR "?" ":" LOGICAL_OR 
// LOGICAL_AND BIT_OR BIT_XOR BIT_AND EQ NE LTHAN GTHAN LTE GTE "instanceof" 
// LSL LSR ASR PLUS MINUS MULTIPLY DIVIDE MOD INC DEC BIT_NOT LOGICAL_NOT 
// "delete" "[" "]" "." "new" NUMERIC_LITERAL STRING_LITERAL QUOTED_LITERAL 
const ANTLR_USE_NAMESPACE(antlr)BitSet ActionScriptParser::_tokenSet_5(_tokenSet_5_data_,8);
const unsigned long ActionScriptParser::_tokenSet_6_data_[] = { 4228383472UL, 4294967167UL, 255UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// "{" "function" IDENTIFIER "(" ";" "," ASSIGN ASSIGN_ADD ASSIGN_SUB ASSIGN_MUL 
// ASSIGN_DIV ASSIGN_MOD ASSIGN_LSL ASSIGN_ASR ASSIGN_LSR ASSIGN_AND ASSIGN_OR 
// ASSIGN_XOR "?" LOGICAL_OR LOGICAL_AND BIT_OR BIT_XOR BIT_AND EQ NE LTHAN 
// GTHAN LTE GTE "instanceof" LSL LSR ASR PLUS MINUS MULTIPLY DIVIDE MOD 
// INC DEC BIT_NOT LOGICAL_NOT "delete" "[" "]" "." "new" NUMERIC_LITERAL 
// STRING_LITERAL QUOTED_LITERAL 
const ANTLR_USE_NAMESPACE(antlr)BitSet ActionScriptParser::_tokenSet_6(_tokenSet_6_data_,8);
const unsigned long ActionScriptParser::_tokenSet_7_data_[] = { 64UL, 0UL, 224UL, 0UL, 0UL, 0UL, 0UL, 0UL };
// IDENTIFIER NUMERIC_LITERAL STRING_LITERAL QUOTED_LITERAL 
const ANTLR_USE_NAMESPACE(antlr)BitSet ActionScriptParser::_tokenSet_7(_tokenSet_7_data_,8);


