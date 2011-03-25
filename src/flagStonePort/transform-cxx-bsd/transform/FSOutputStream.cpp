/*
 *  FSOutputStream.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 10 2003.
 *  Copyright (c) 2001-2003 Flagstone Software Ltd. All rights reserved.
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

#include "FSOutputStream.h"

#include <stdio.h>
#include <math.h>

#include "FSMovieListener.h"
#include "FSException.h"

using namespace transform;

namespace transform
{
    FSOutputStream::FSOutputStream(size_t numberOfBytes) : FSStream(0, 0)
    {
        byte* bytes = new byte[numberOfBytes];

        if (numberOfBytes > 0 && bytes == 0)
            throw FSAllocationException("Cannot allocate memory for the output stream data.");

        memset(bytes, 0, numberOfBytes*sizeof(byte));

        setData(bytes, numberOfBytes);

        delete [] bytes;
    }

    void FSOutputStream::startEncoding(const char* aType)
    {
        if (listener != 0)
        {
            FSMovieEvent anEvent(FSMovieEvent::Encode, FSMovieEvent::Begin, cursor, 0, aType, "");

            listener->logEvent(anEvent);
        }
    }
    
    void FSOutputStream::endEncoding(const char* aType)
    {
        if (listener != 0)
        {
            FSMovieEvent anEvent(FSMovieEvent::Encode, FSMovieEvent::End, cursor, 0, aType, "");

            listener->logEvent(anEvent);
        }
    }

    void FSOutputStream::log(int location, int numberOfBits, int aValue)
    {
        char s[16];

        sprintf(s, "%d", aValue);

        log(location, numberOfBits, "int", s);
    }

    void FSOutputStream::log(int location, int numberOfBits, float aValue)
    {
        char s[32];
    
        sprintf(s, "%f", aValue);
    
        log(location, numberOfBits, "float", s);
    }

    void FSOutputStream::log(int location, int numberOfBits, double aValue)
    {
        char s[32];
    
        sprintf(s, "%f", aValue);
    
        log(location, numberOfBits, "double", s);
    }

    void FSOutputStream::log(int location, int numberOfBits, const char* aType, const char* aValue)
    {
        if (listener != 0)
        {
            FSMovieEvent anEvent(FSMovieEvent::Encode, FSMovieEvent::Value, location, numberOfBits, aType, aValue);

            listener->logEvent(anEvent);
        }
    }

    void FSOutputStream::write(int number, streamType numberType, int numberOfBits)
    {
#ifdef _DEBUG
        if (numberOfBits >= 0 && numberOfBits <= 32 == false)
            throw new FSException("Value Out Of Range");
        if ((cursor+numberOfBits)>>3 > length)
            throw new FSException("Write Overflow");
#endif        
        switch (numberType)
        {
            case FSStream::UnsignedBit:
            case FSStream::SignedBit:
                writeBits(number, numberOfBits);
                break;
            case FSStream::UnsignedWord:
            case FSStream::SignedWord:
                writeWord(number, numberOfBits);
                break;
            default:
                break;
        }

#ifdef _DEBUG
        log(cursor-numberOfBits, numberOfBits, number);
#endif
    }
    
    void FSOutputStream::write(float number, float format, int numberOfBits)
    {
#ifdef _DEBUG
        if ((cursor+numberOfBits)>>3 > length)
            throw new FSException("Write Overflow");
#endif
        float floatValue = number * (float)pow(2.0, (double)format);

        writeBits((int)floatValue, numberOfBits);

#ifdef _DEBUG
        log(cursor-numberOfBits, numberOfBits, number);
#endif
    }

    void FSOutputStream::write(double number)
    {
        union convert {
            char byte[8];
            double dval;
        };

        convert value;

        value.dval = number;
        
#ifdef _DEBUG
        if ((cursor+64)>>3 > length)
            throw new FSException("Write Overflow");
#endif

#ifdef WIN32
        for (int i=4; i<8; i++)
            writeWord(value.byte[i], 8);

        for (int i=0; i<4; i++)
            writeWord(value.byte[i], 8);
#else
        for (int i=3; i>-1; i--)
            writeWord(value.byte[i], 8);

        for (int i=7; i>3; i--)
            writeWord(value.byte[i], 8);
#endif
        
#ifdef _DEBUG
        log(cursor-64, 64, number);
#endif
    }

    void FSOutputStream::write(const byte* b, int numberOfBytes)
    {
        int bytesLeft = length - (cursor >> 3);
        int count = (bytesLeft < numberOfBytes) ? bytesLeft : numberOfBytes;

#ifdef _DEBUG
        if (b == NULL && numberOfBytes > 0)
            throw new FSException("Null Object");
        if (bytesLeft < numberOfBytes)
            throw new FSException("Write Overflow");
#endif

        for (int i=0; i<count; i++, cursor+=8)
            data[cursor>>3] = b[i];

#ifdef _DEBUG
        log(cursor-(length<<3), numberOfBytes<<3, "byte", "<data>");
#endif
    }

    void FSOutputStream::writeBits(int number, int numberOfBits)
    {
        if (numberOfBits > 0)
        {
            int location = cursor >> 3;
            unsigned int value = number << (32 - numberOfBits);
        
            value = value >> (cursor % 8);
            value = value | (data[location] << 24);
    
            for (int i=24; i>=0; i-=8, location++)
                data[location] = value >> i;
                
            cursor += numberOfBits;
        }
    }
    
    void FSOutputStream::writeWord(int number, int numberOfBits)
    {
#ifdef _DEBUG
        if (cursor % 8 != 0)
            throw new FSException("Not Byte Aligned");
#endif
        unsigned int val = number;

        int bitsLeft = (length << 3) - cursor;
        int size = (bitsLeft < numberOfBits) ? bitsLeft : numberOfBits;

        for (int i=0; i<size; i+=8, cursor+=8, val >>= 8)
            data[cursor>>3] = val;
    }
}
