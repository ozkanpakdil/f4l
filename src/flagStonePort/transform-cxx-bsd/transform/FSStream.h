/*
 *  FSStream.h
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

#ifndef __FSStream_h__
#define __FSStream_h__ 1

#include "FSTransform.h"

namespace transform
{
    class FSMovieListener;

    class DLL_DECL FSStream
    {
    public:
        enum streamType { UnsignedBit, SignedBit, UnsignedWord, SignedWord };
        enum fixedType  { FixedShort = 8, FixedInt = 16 };
        
        enum contextType { 
            Version, Type, ColorContainsAlpha, ArrayCountExtended, 
            WideCodes, FillBits, LineBits, AdvanceBits, 
            GlyphBits, FillStyles, LineStyles, 
            ReservedA, ReservedB, ReservedC, ReservedD 
        };

        static int FieldSize(int value, bool isSigned = false);
        static int FieldSize(int values[], int length, bool isSigned = false);
        
        static int FieldSize(float aNumber, fixedType width);
        static int FieldSize(float values[], int length, fixedType width);

        FSStream(const byte* bytes, size_t numberOfBytes);

        ~FSStream();

        FSMovieListener* getListener();
        void setListener(FSMovieListener* aListener);
        
        int getContext(int key);
        void setContext(int key, int value);

        byte* getData() const;
        void setData(const byte* bytes, size_t numberOfBytes);

        unsigned int getCursor() const;
        void setCursor(unsigned int aLocation);

        void flush();

        bool endOfStream();
        void moveToEnd();

protected:
        FSMovieListener* listener;
        int context[16];

        byte* data;
        size_t length;
        unsigned int cursor;
    };
} 

#endif
