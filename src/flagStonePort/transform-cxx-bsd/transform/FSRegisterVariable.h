/*
 *  FSRegisterVariable.h
 *  Transform SWF
 * 
 * Copyright (c) 2001-2004 Flagstone Software Ltd.. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *  * Neither the name of Flagstone Software Ltd. nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSRegisterVariable_h__
#define __FSRegisterVariable_h__

#include "FSTransformObject.h"

#include "FSString.h"

namespace transform
{
	/**
	 * %FSRegisterVariable is a lightweight class used to identify the register that an argument 
	 * defined in the %FSNewFunction2 class is mapped into when executing the function.
	 *
<p>Register numbers up to 255 may be specified. If the number is zero then the 
argument is defined as a local variable.</p>

	 */  
    class DLL_DECL FSRegisterVariable : public FSTransformObject
    {
public:
        FSRegisterVariable(FSInputStream* aStream);

		FSRegisterVariable() : index(0), name() {}

		/**
		 * Constructs a new FSRegisterVariable object specifying the name of the argument and 
		 * the number of the register it will be mapped to. If the index is 0 then the 
		 * argument will be stored in a local variable.
		 *
		 * @param anIndex the number of the register, 1..255, 0 if the argument will be stored in a local variable.
		 * @param aString the name of the argument.
		 */
        FSRegisterVariable(int anIndex, const char* aString) : index(anIndex), name(aString) {}

        FSRegisterVariable* clone() const { return new FSRegisterVariable(*this); }

        const char* className() const;

		/**
		 * Gets the number of the register that will contain the function argument.
		 *
		 * @return the number of the register, 1..255, in which the function argument will be stored, 0 if the argument will be stored in a local variable.
		 */
		int getIndex() { return index; }

		/**
		 * Gets the name of the function argument.
		 *
		 * @return the name of the argument.
		 */
		 const char* getName() { return name.c_str(); }

		/**
		 * Sets the number of the register that will contain the function argument.
		 *
		 * @param anIndex the number of the register, 1..255, in which the function argument will be stored, 0 if the argument will be stored in a local variable.
		 */
		void setIndex(int anIndex) { index = anIndex; }

		/**
		 * Sets the name of the function argument.
		 *
		 * @param aString the name of the argument.
		 */
 		void setName(const char* aString) { name = aString; }

		int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
		int index;
        FSString name;
    };
}

#endif
