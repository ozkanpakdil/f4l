/*
 *  FSInputStream.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 10 2003.
 *  Copyright (c) 2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file contains Original Code and/or Modifications of Original Code as defined in
 *  and that are subject to the Flagstone Software Source License Version 1.0 (the
 *  'License'). You may not use this file except in compliance with the License. Please
 *  obtain a copy of the License at http://www.flagstonesoftware.com/licenses/source.html
 *  and read it before using this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an 
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone 
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY 
 *  RIGHTS. Please see the License for the specific language governing rights and limitations 
 *  under the License.
 */

#include "FSInputStream.h"

#include <math.h>
#include <stdio.h>

#include "FSMovieListener.h"
#include "FSException.h"

using namespace transform;

namespace transform
{
    FSInputStream::FSInputStream(const byte* bytes, size_t numberOfBytes) : FSStream(bytes, numberOfBytes)
    {
    }
    
    void FSInputStream::startDecoding(const char* aType)
    {
        if (listener != 0)
        {
            FSMovieEvent anEvent(FSMovieEvent::Decode, FSMovieEvent::Begin, cursor, 0, aType, "");

            listener->logEvent(anEvent);
        }
    }
    
    void FSInputStream::endDecoding(const char* aType)
    {
        if (listener != 0)
        {
            FSMovieEvent anEvent(FSMovieEvent::Decode, FSMovieEvent::End, cursor, 0, aType, "");

            listener->logEvent(anEvent);
        }
    }

    void FSInputStream::log(int location, int numberOfBits, int aValue)
    {
        char s[16];

        sprintf(s, "%d", aValue);

        log(location, numberOfBits, "int", s);
    }
    
    void FSInputStream::log(int location, int numberOfBits, float aValue)
    {
        char s[16];

        sprintf(s, "%f", aValue);

        log(location, numberOfBits, "float", s);
    }

    void FSInputStream::log(int location, int numberOfBits, double aValue)
    {
        char s[32];

        sprintf(s, "%-12.6e", aValue);

        log(location, numberOfBits, "double", s);
    }

    void FSInputStream::log(int location, int numberOfBits, const char* aType, const char* aValue)
    {
        if (listener != 0)
        {
            FSMovieEvent anEvent(FSMovieEvent::Decode, FSMovieEvent::Value, location, numberOfBits, aType, aValue);

            listener->logEvent(anEvent);
        }
    }
    
    int FSInputStream::scan(streamType numberType, int numberOfBits)
    {
        int value = 0;

#ifdef _DEBUG
        if (numberOfBits >= 0 && numberOfBits <= 32 == false)
            throw new FSException("Value Out Of Range");
        if ((cursor+numberOfBits)>>3 > length)
            throw new FSException("Read Overflow");
#endif
        switch (numberType)
        {
            case FSStream::UnsignedBit:
                value = readBits(numberOfBits, false);
                break;
            case FSStream::SignedBit:
                value = readBits(numberOfBits, true);
                break;
            case FSStream::UnsignedWord:
                value = readWord(numberOfBits, false);
                break;
            case FSStream::SignedWord:
                value = readWord(numberOfBits, true);
                break;
            default:
#ifdef _DEBUG
                throw new FSException("Invalid Number Type");
#endif
                break;
        }
        return value;
    }
    
    int FSInputStream::read(streamType numberType, int numberOfBits)
    {
        int value = 0;

#ifdef _DEBUG
        if (numberOfBits >= 0 && numberOfBits <= 32 == false)
            throw new FSException("Value Out Of Range");
        if ((cursor+numberOfBits)>>3 > length)
            throw new FSException("Read Overflow");
#endif
                
        if (numberOfBits > 0)
        {
            switch (numberType)
            {
                case FSStream::UnsignedBit:
                    value = readBits(numberOfBits, false);
                    break;
                case FSStream::SignedBit:
                    value = readBits(numberOfBits, true);
                    break;
                case FSStream::UnsignedWord:
                    value = readWord(numberOfBits, false);
                    break;
                case FSStream::SignedWord:
                    value = readWord(numberOfBits, true);
                    break;
                default:
#ifdef _DEBUG
                    throw new FSException("Invalid Number Type");
#endif
                    break;
            }
        }
#ifdef _DEBUG
        log(cursor-numberOfBits, numberOfBits, value);
#endif
        return value;
    }
    
    float FSInputStream::read(float format, int numberOfBits)
    {
        float value = ((float)readBits(numberOfBits, true)) / (float)pow(2.0, (double)format);

#ifdef _DEBUG
        log(cursor-numberOfBits, numberOfBits, value);
#endif
        return value;
    }
    
    double FSInputStream::read()
    {
        union convert {
            char byte[8];
            double dval;
        };

        convert value;

#ifdef _DEBUG
        if ((cursor+64)>>3 > length)
            throw new FSException("Read Overflow");
#endif

#ifdef WIN32
        for (int i=4; i<8; i++)
            value.byte[i] = readWord(8, false);

        for (int i=0; i<4; i++)
            value.byte[i] = readWord(8, false);
#else
        for (int i=3; i>-1; i--)
            value.byte[i] = readWord(8, false);

        for (int i=7; i>3; i--)
            value.byte[i] = readWord(8, false);
#endif

#ifdef _DEBUG
        log(cursor-64, 64, value.dval);
#endif
        return value.dval;
    }
    
    byte* FSInputStream::read(int numberOfBytes)
    {
        byte* bytes;

#ifdef _DEBUG
        if (cursor % 8 != 0)
            throw new FSException("Not Byte Aligned");
        if (numberOfBytes < 0)
            throw new FSException("Value Negative");
        if ((cursor>>3)+numberOfBytes > length)
            throw new FSException("Read Overflow");
#endif
    
        bytes = readBytes(numberOfBytes);

#ifdef _DEBUG
        int numberOfBits = numberOfBytes << 3;    
        log(cursor-numberOfBits, numberOfBits, "byte", "<data>");
#endif
    
        return bytes;
    }

    void FSInputStream::read(byte* buffer, int numberOfBytes, bool appendNull)
    {
    #ifdef _DEBUG
        if (cursor % 8 != 0)
            throw new FSException("Not Byte Aligned");
        if (numberOfBytes < 0)
            throw new FSException("Value Negative");
        if ((cursor>>3)+numberOfBytes > length)
            throw new FSException("Read Overflow");
    #endif
        
        int i;

        for (i=0; i<numberOfBytes; i++, cursor+=8)
            buffer[i] = data[cursor>>3];

        if (appendNull)
            buffer[i] = '\0';

    #ifdef _DEBUG
        int numberOfBits = numberOfBytes << 3;
        log(cursor-numberOfBits, numberOfBits, "byte", "<data>");
    #endif
    }

    char* FSInputStream::readString()
    {
        char* bytes;
        
        int start = cursor>>3;
        int numberOfBytes = 1;
        
        while (data[start++] != 0) numberOfBytes++;
        
        bytes = (char*)readBytes(numberOfBytes);

#ifdef _DEBUG
        int numberOfBits = numberOfBytes << 3;
        log(cursor-numberOfBits, numberOfBits, "string", bytes);
#endif
        return bytes;
    }

    int FSInputStream::readType()
    {
        unsigned int word = readWord(16, false);
        cursor -= 16;

        return word >> 6;
    }

    int FSInputStream::readBits(int numberOfBits, bool isSigned)
    {
        unsigned int value = 0;
        
        if (numberOfBits > 0)
        {
            int location = cursor >> 3;
            
            for (int i=32; i>0; i-=8, location++)
                value |= (data[location] & 0x000000FF) << (i-8);
                
            value <<= cursor % 8;
        
            if (isSigned)
            {
                value >>= 32 - numberOfBits;
    
                if (value >> (numberOfBits-1))
                    value |= ~0 << numberOfBits;
            }
            else 
                value >>= 32 - numberOfBits;
            
            cursor += numberOfBits;
        }
        return value;
    }
    
    int FSInputStream::readWord(int numberOfBits, bool isSigned)
    {
        unsigned int value = 0;

#ifdef _DEBUG
        if (cursor % 8 != 0)
            throw new FSException("Not Byte Aligned");
#endif
        
        for (int i=0; i<numberOfBits; i+=8, cursor+=8)
            value += (data[cursor>>3] & 0x000000FF) << i;
        
        if (isSigned)
        {
            if (value >> (numberOfBits-1))
                value |= ~0 << numberOfBits;
        }
        return value;
    }

    byte* FSInputStream::readBytes(int numberOfBytes)
    {
        byte* bytes = new byte[numberOfBytes];
        int i = 0;

        if (numberOfBytes > 0 && bytes == 0)
            throw FSAllocationException("Could not allocate memory to read an array of bytes from a stream.");

        for (i=0; i<numberOfBytes; i++, cursor+=8)
            bytes[i] = data[cursor>>3];
    
        return bytes;
    }
} 
