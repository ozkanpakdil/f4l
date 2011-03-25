/*
 *  FSOutputStream.h
 *  Transform
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

#ifndef __FSOutputStream_h__
#define __FSOutputStream_h__ 1

#include "FSStream.h"

namespace transform
{
    class DLL_DECL FSOutputStream : public FSStream
    {
    public:
        FSOutputStream(size_t numberOfBytes = 0);
        
        void startEncoding(const char* aType);
        void endEncoding(const char* aType);

        void log(int location, int numberOfBits, int aValue);
        void log(int location, int numberOfBits, float aValue);
        void log(int location, int numberOfBits, double aValue);
        void log(int location, int numberOfBits, const char* aType, const char* aValue);

        void write(int number, streamType numberType, int numberOfBits);
        void write(float number, float format, int numberOfBits);
        void write(double number);
        void write(const byte* b, int numberOfBytes);

private:
        void writeBits(int number, int numberOfBits);
        void writeWord(int number, int numberOfBits);
    };
}

#endif