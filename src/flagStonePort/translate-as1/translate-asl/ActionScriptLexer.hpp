#ifndef INC_ActionScriptLexer_hpp_
#define INC_ActionScriptLexer_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.4: "ActionScriptParser.g" -> "ActionScriptLexer.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "ActionScriptTokenTypes.hpp"
#include <antlr/CharScanner.hpp>
#line 1 "ActionScriptParser.g"

#include "ASParser.h"
#include "ASNode.h"

#line 17 "ActionScriptLexer.hpp"
class CUSTOM_API ActionScriptLexer : public ANTLR_USE_NAMESPACE(antlr)CharScanner, public ActionScriptTokenTypes
{
#line 1 "ActionScriptParser.g"
#line 21 "ActionScriptLexer.hpp"
private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const
	{
		return true;
	}
public:
	ActionScriptLexer(ANTLR_USE_NAMESPACE(std)istream& in);
	ActionScriptLexer(ANTLR_USE_NAMESPACE(antlr)InputBuffer& ib);
	ActionScriptLexer(const ANTLR_USE_NAMESPACE(antlr)LexerSharedInputState& state);
	ANTLR_USE_NAMESPACE(antlr)RefToken nextToken();
	public: void mLPAREN(bool _createToken);
	public: void mRPAREN(bool _createToken);
	public: void mLCURLY(bool _createToken);
	public: void mRCURLY(bool _createToken);
	public: void mLBRACKET(bool _createToken);
	public: void mRBRACKET(bool _createToken);
	public: void mSEMI(bool _createToken);
	public: void mCOMMA(bool _createToken);
	public: void mSELECT(bool _createToken);
	public: void mALTERNATE(bool _createToken);
	public: void mASSIGN(bool _createToken);
	public: void mASSIGN_ADD(bool _createToken);
	public: void mASSIGN_SUB(bool _createToken);
	public: void mASSIGN_MUL(bool _createToken);
	public: void mASSIGN_DIV(bool _createToken);
	public: void mASSIGN_MOD(bool _createToken);
	public: void mASSIGN_LSL(bool _createToken);
	public: void mASSIGN_ASR(bool _createToken);
	public: void mASSIGN_LSR(bool _createToken);
	public: void mASSIGN_AND(bool _createToken);
	public: void mASSIGN_OR(bool _createToken);
	public: void mASSIGN_XOR(bool _createToken);
	public: void mLOGICAL_AND(bool _createToken);
	public: void mLOGICAL_OR(bool _createToken);
	public: void mLOGICAL_NOT(bool _createToken);
	public: void mEQ(bool _createToken);
	public: void mGTHAN(bool _createToken);
	public: void mLTHAN(bool _createToken);
	public: void mGTE(bool _createToken);
	public: void mLTE(bool _createToken);
	public: void mNE(bool _createToken);
	public: void mBIT_AND(bool _createToken);
	public: void mBIT_OR(bool _createToken);
	public: void mBIT_XOR(bool _createToken);
	public: void mBIT_NOT(bool _createToken);
	public: void mLSL(bool _createToken);
	public: void mLSR(bool _createToken);
	public: void mASR(bool _createToken);
	public: void mPLUS(bool _createToken);
	public: void mMINUS(bool _createToken);
	public: void mMULTIPLY(bool _createToken);
	public: void mDIVIDE(bool _createToken);
	public: void mMOD(bool _createToken);
	public: void mINC(bool _createToken);
	public: void mDEC(bool _createToken);
	public: void mWS(bool _createToken);
	public: void mSTRING_LITERAL(bool _createToken);
	protected: void mESC(bool _createToken);
	public: void mQUOTED_LITERAL(bool _createToken);
	public: void mIDENTIFIER(bool _createToken);
	protected: void mHEX_DIGIT(bool _createToken);
	protected: void mEXPONENT(bool _createToken);
	public: void mNUMERIC_LITERAL(bool _createToken);
private:
	
	static const unsigned long _tokenSet_0_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_0;
	static const unsigned long _tokenSet_1_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_1;
	static const unsigned long _tokenSet_2_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_2;
	static const unsigned long _tokenSet_3_data_[];
	static const ANTLR_USE_NAMESPACE(antlr)BitSet _tokenSet_3;
};

#endif /*INC_ActionScriptLexer_hpp_*/
