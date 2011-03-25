/*
 *  FSString.h
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

#ifndef __FSString_h__
#define __FSString_h__ 1

#include "FSValue.h"

namespace transform
{
    /** 
     * FSString is a wrapper class for characters strings that will added to objects used to generate Flash files.
     *
     * Strings are mostly commonly used from the Transform SWF5 Edition onwards where strings are pushed onto 
     * the Flash Players stack to execute object methods and other calculations.
     *
     * Every object which uses the FSString class provides accessor methods which pass and return C-strings so
     * create FSString objects directly is not necessary. To support localization the array of bytes comprising
     * the characters is terminated by a null character '\\0'. No encoding scheme is assumed so the objects can
     * safely be used with most coding sets such as ASCII, SJIS or Unicode (UTF8).
     */
    class DLL_DECL FSString : public FSValue
    {
public:
        FSString(FSInputStream* aStream);
        
        /** Constructs and FSString object with the specified string.

        @param aValue a c-string.
        */
        FSString(const char* aValue = "");

        FSString(const FSString& rhs);

        ~FSString();

        const FSString& operator= (const FSString& rhs);

        FSString* clone() const { return new FSString(*this); }

        const char* className() const;

        int length() const { return strLength; }

        /** Append operator.

            @param rhs an FSString object containing a string that will be appended to this object.
            @return a reference to this object.
            */
        const FSString& operator+= (const FSString& rhs);

        /** Returns the array of bytes containing the character data.

            @return the bytes representing the characters.
            */
        const char* c_str() const { return buffer; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        char* buffer;
        int strLength;
        int bufferLength;
    };

    FSString operator+ (const FSString& lhs, const FSString& rhs); // Concatenation
} 

#endif
