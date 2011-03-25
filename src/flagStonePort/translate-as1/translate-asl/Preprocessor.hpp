#ifndef INC_Preprocessor_hpp_
#define INC_Preprocessor_hpp_

#include <antlr/config.hpp>
/* $ANTLR 2.7.4: "Preprocessor.g" -> "Preprocessor.hpp"$ */
#include <antlr/CommonToken.hpp>
#include <antlr/InputBuffer.hpp>
#include <antlr/BitSet.hpp>
#include "PreprocessorTokenTypes.hpp"
#include <antlr/CharScanner.hpp>
class CUSTOM_API Preprocessor : public ANTLR_USE_NAMESPACE(antlr)CharScanner, public PreprocessorTokenTypes
{
#line 1 "Preprocessor.g"
#line 15 "Preprocessor.hpp"
private:
	void initLiterals();
public:
	bool getCaseSensitiveLiterals() const
	{
		return true;
	}
public:
	Preprocessor(ANTLR_USE_NAMESPACE(std)istream& in);
	Preprocessor(ANTLR_USE_NAMESPACE(antlr)InputBuffer& ib);
	Preprocessor(const ANTLR_USE_NAMESPACE(antlr)LexerSharedInputState& state);
	ANTLR_USE_NAMESPACE(antlr)RefToken nextToken();
	public: void mINCLUDE(bool _createToken);
	public: void mDEFINE(bool _createToken);
	public: void mIFDEF(bool _createToken);
	public: void mIFNDEF(bool _createToken);
	public: void mELSE(bool _createToken);
	public: void mENDIF(bool _createToken);
	public: void mLPAREN(bool _createToken);
	public: void mRPAREN(bool _createToken);
	public: void mLBRACKET(bool _createToken);
	public: void mRBRACKET(bool _createToken);
	public: void mLCURLY(bool _createToken);
	public: void mRCURLY(bool _createToken);
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
	public: void mGT(bool _createToken);
	public: void mLT(bool _createToken);
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
	public: void mWHITESPACE(bool _createToken);
	public: void mLINE_END(bool _createToken);
	public: void mSTRING_LITERAL(bool _createToken);
	protected: void mESC(bool _createToken);
	public: void mQUOTED_LITERAL(bool _createToken);
	public: void mLITERAL(bool _createToken);
	protected: void mHEX_DIGIT(bool _createToken);
	protected: void mEXPONENT(bool _createToken);
	public: void mNUMERIC_LITERAL(bool _createToken);
	public: void mSL_COMMENT(bool _createToken);
	public: void mML_COMMENT(bool _createToken);
private:
	
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
};

#endif /*INC_Preprocessor_hpp_*/
