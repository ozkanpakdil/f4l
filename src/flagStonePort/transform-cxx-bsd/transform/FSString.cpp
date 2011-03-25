/*
 *  FSString.cpp
 *  Transform SWF
 *
 *  Created by Stuart MacKay on Thu Feb 13 2003.
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

#include "FSString.h"

#include <string.h>

#include "FSException.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSString::FSString(FSInputStream* aStream) : FSValue(FSValue::String), buffer(0), strLength(0), bufferLength(0) 
    {
        strLength = 0;
        bufferLength = strLength + 1;
        buffer = new char[bufferLength];

        if (bufferLength > 0 && buffer == 0)
            throw FSAllocationException("Cannot allocate memory to copy an FSString.");

        buffer[0] = '\0';
        
        decodeFromStream(aStream);
    }
    
    FSString::FSString(const char* aValue) : FSValue(FSValue::String), buffer(0), strLength(0), bufferLength(0)
    {
        if (aValue == 0)
            aValue = "";
        
        strLength = (int)strlen(aValue);
        bufferLength = strLength + 1;
        buffer = new char[bufferLength];

        if (bufferLength > 0 && buffer == 0)
            throw FSAllocationException("Cannot allocate memory to copy an FSString.");

        strcpy(buffer, aValue);
    }

    FSString::FSString(const FSString& rhs) : FSValue(rhs), buffer(0), strLength(0), bufferLength(0)
    {
        strLength = rhs.length();
        bufferLength = strLength + 1;
        buffer = new char[bufferLength];

        if (bufferLength > 0 && buffer == 0)
            throw FSAllocationException("Cannot allocate memory to copy an FSString.");

        strcpy(buffer, rhs.buffer);
    }

    FSString::~FSString()
    {
        delete [] buffer;
        buffer = 0;
    }

    const char* FSString::className() const
    {
        const static char _name[] = "FSString";

        return _name;
    }

    const FSString& FSString::operator= (const FSString& rhs)
    {
        if (this != &rhs)
        {
            this->FSValue::operator=(rhs);
            
            if (bufferLength < rhs.length() + 1)
            {
                delete [] buffer;
                bufferLength = rhs.length() + 1;
                buffer = new char[bufferLength];

                if (bufferLength > 0 && buffer == 0)
                    throw FSAllocationException("Cannot allocate memory to copy an FSString.");
            }
            strLength = rhs.length();
            strcpy(buffer, rhs.buffer);
        }
        return *this;
    }
    
    const FSString& FSString::operator+=(const FSString& rhs)
    {
        if (this == &rhs)
        {
            FSString copy(rhs);
            return *this += copy;
        }
    
        int newLength = length() + rhs.length();
        
        if (newLength >= bufferLength)
        {
            bufferLength = 2 * (newLength + 1);
    
            char* oldBuffer = buffer;
            buffer = new char[ bufferLength ];

            if (bufferLength > 0 && buffer == 0)
                throw FSAllocationException("Cannot allocate memory to copy an FSString.");

            strcpy(buffer, oldBuffer );
            delete [] oldBuffer;
        }
    
        strcpy(buffer+length(), rhs.buffer);
        strLength = newLength;
        
        return *this;
    }
    
    int FSString::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = FSValue::lengthInStream(aStream);

        tagLength += strLength+1;
        
        return tagLength;
    }
    
    void FSString::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSValue::encodeToStream(aStream);

        aStream->write((byte*)buffer, strLength+1);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSString::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSValue::decodeFromStream(aStream);
        
        buffer = aStream->readString();
        strLength = (int)strlen(buffer);
        bufferLength = strLength+1;

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }

    /*
     * Overloaded operations that can be performed on strings
     */ 

    FSString operator+(const FSString& lhs, const FSString& rhs)
    {
        FSString result = lhs;
        result += rhs;
        return result;
    }
} 
