/*
 *  FSUnknownObject.cpp
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

#include "FSUnknownObject.h"

#include <stdlib.h>

#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSException.h"

using namespace transform;

namespace transform
{
    FSUnknownObject::FSUnknownObject(FSInputStream* aStream) : FSMovieObject(0), data(0)
    {
        decodeFromStream(aStream);
    }

    FSUnknownObject::FSUnknownObject(int aType, byte* bytes, size_t numberOfBytes) : FSMovieObject(aType), data(0)
    {
        setData(bytes, numberOfBytes);
    }

    FSUnknownObject::FSUnknownObject(const FSUnknownObject& rhs) : FSMovieObject(rhs), data(0)
    {
        if (rhs.data)
        {
            data = new byte[length];

            if (length > 0 && data == 0)
                throw FSAllocationException("Cannot allocate memory to copy an FSUnknownObject.");

            memcpy(data, rhs.data, length*sizeof(byte));
        }
    }

     FSUnknownObject::~FSUnknownObject()
    {
        delete [] data;
        data = 0;
    }

    FSUnknownObject* FSUnknownObject::clone() const
    {
        return new FSUnknownObject(*this);
    }
    
    const char* FSUnknownObject::className() const
    {
        const static char _name[] = "FSUnknownObject";

        return _name;
    }

    FSUnknownObject& FSUnknownObject::operator= (const FSUnknownObject& rhs)
    {
        if (this != &rhs)
        {
            this->FSMovieObject::operator=(rhs);

            delete [] data;

            data = new byte[length];

            if (length > 0 && data == 0)
                throw FSAllocationException("Cannot allocate memory to copy FSUnknownObject.");

            memcpy(data, rhs.data, length*sizeof(byte));
        }
        return *this;
    }
    
    const byte* FSUnknownObject::getData() const
    {
        return data;
    }
    
    void FSUnknownObject::setData(byte* bytes, size_t numberOfBytes)
    {
        delete [] data;

        data = bytes;
        length = numberOfBytes;
    }

    int FSUnknownObject::lengthInStream(FSOutputStream* aStream)
    {
        return length;
    }
    
    void FSUnknownObject::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        aStream->write(data, length);

        aStream->endEncoding(className());
    }
    
    void FSUnknownObject::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

        data = aStream->read(length);

        aStream->endDecoding(className());
    }
}
