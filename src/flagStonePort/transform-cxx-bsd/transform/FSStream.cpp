/*
 *  FSStream.cpp
 *  Transform
 *
 *  Created by smackay on Fri Feb 7 2003.
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

#include "FSStream.h"

#include <string.h>
#include <math.h>

#include "FSMovieListener.h"
#include "FSException.h"
#include "FSString.h"

using namespace transform;

namespace transform
{
    int FSStream::FieldSize(int value, bool isSigned)
    {
        int size = 0, i = 0;
        unsigned int mask = 0x80000000;
    
        if (isSigned)
        {
            value = (value < 0) ? -value : value;
            for (i=32; (value & mask) == 0 && i>0; i--)
                mask >>= 1;
            size = (i < 32 && i != 0) ? i+1 : i;
        }
        else
        {
            for (i=32; (value & mask) == 0 && i>0; i--)
                mask >>= 1;
            size = i;
        }
        return size;
    }
    
    int FSStream::FieldSize(int values[], int length, bool isSigned)
    {
        int size = 0;
        
        for (int i=0; i<length; i++)
        {
            int valueSize = FieldSize(values[i], isSigned);
            size = (size > valueSize) ? size : valueSize;
        }
    
        return size;
    }
    
    int FSStream::FieldSize(float aNumber, fixedType width)
    {
        float floatValue = aNumber * (float)pow(2.0, (double)width);
        
        return FieldSize((int)floatValue, true);
    }
    
    int FSStream::FieldSize(float values[], int length, fixedType width)
    {
        int size = 0;
        
        for (int i=0; i<length; i++)
        {
            int valueSize = FieldSize(values[i], width);
            size = (size > valueSize) ? size : valueSize;
        }    
        return size;
    }

    FSStream::FSStream(const byte* bytes, size_t numberOfBytes) :
        listener(0),
        data(0),
        length(0),
        cursor(0)
    {
        for (int i=0; i<16; i++)
            context[i] = 0;
            
        setData(bytes, numberOfBytes);
    }

    FSStream::~FSStream()
    {
        delete [] data;
        data = 0;
    }
    
    int FSStream::getContext(int key)
    {
        return context[key];
    }

    void FSStream::setContext(int key, int value)
    {
        context[key] = value;
    }

    FSMovieListener* FSStream::getListener()
    {
        return listener;
    }
    
    void FSStream::setListener(FSMovieListener* aListener) 
    {
        listener = aListener;
    }
    
    byte* FSStream::getData() const
    {
        byte* bytes = new byte[length];

        memcpy(bytes, data, length*sizeof(byte));

        return bytes;
    }

    void FSStream::setData(const byte* bytes, size_t numberOfBytes)
    {
        delete [] data;

        data = new byte[numberOfBytes];

        if (data == 0)
        {
            const char* message = "Cannot allocate memory for stream data.";

            if (listener != 0)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Encode, FSMovieEvent::Error, 0, 0, "", message));            
            else
                throw FSAllocationException(message);
        }

        memcpy(data, bytes, numberOfBytes*sizeof(byte));
        length = numberOfBytes;
    }

    unsigned int FSStream::getCursor() const
    {
        return cursor;
    }
    
    void FSStream::setCursor(unsigned int aLocation)
    {
        cursor = aLocation;
    }
    
    void FSStream::flush()
    {
        cursor += (cursor % 8 > 0) ? 8 - (cursor % 8) : 0;
    }

    bool FSStream::endOfStream()
    {
        return (cursor/8 < length) ? false : true;
    }

    void FSStream::moveToEnd()
    {
        cursor = length<<3;
    }
}
