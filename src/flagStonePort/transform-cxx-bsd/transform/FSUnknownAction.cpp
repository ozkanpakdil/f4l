/*
 *  FSUnknownAction.cpp
 *  Transform SWF
 *
 *  Created by smackay on Tue Feb 18 2003.
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

#include "FSUnknownAction.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSException.h"

using namespace transform;

namespace transform
{
    FSUnknownAction::FSUnknownAction(FSInputStream* aStream) : FSActionObject(0) , data(0)
    {
        decodeFromStream(aStream);
    }

    FSUnknownAction::FSUnknownAction(int aType, byte* bytes, size_t numberOfBytes) : FSActionObject(aType), data(0)
    {
        setData(bytes, numberOfBytes);
    }

    FSUnknownAction::FSUnknownAction(const FSUnknownAction& rhs) : FSActionObject(rhs) , data(0)
    {
        if (rhs.data)
        {
            data = new byte[length];

            if (length > 0 && data == 0)
                throw FSAllocationException("Cannot allocate memory to copy and FSUnknownAction.");

            memcpy(data, rhs.data, length*sizeof(byte));
        }
    }

    FSUnknownAction::~FSUnknownAction()
    {
        delete [] data;
        data = 0;
    }

    FSUnknownAction* FSUnknownAction::clone() const
    {
        return new FSUnknownAction(*this);
    }
    
    const char* FSUnknownAction::className() const
    {
        const static char _name[] = "FSUnknownAction";

        return _name;
    }

    FSUnknownAction& FSUnknownAction::operator= (const FSUnknownAction& rhs)
    {
        if (this != &rhs)
        {
            this->FSActionObject::operator=(rhs);
            
            data = new byte[length];

            if (length > 0 && data == 0)
                throw FSAllocationException("Cannot allocate memory to copy and FSUnknownAction.");

            memcpy(data, rhs.data, length*sizeof(byte));
        }
        return *this;
    }

    const byte* FSUnknownAction::getData() const
    {
        return data;
    }
    
    void FSUnknownAction::setData(byte* bytes, size_t numberOfBytes)
    {
        delete [] data;

        length = numberOfBytes;
        data = bytes;
    }
    
    int FSUnknownAction::lengthInStream(FSOutputStream* aStream)
    {
        return length;
    }
    
    void FSUnknownAction::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSActionObject::encodeToStream(aStream);

        aStream->write(data, length);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSUnknownAction::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);
        
        if (length > 0) 
            data = aStream->read(length);
        else
            data = 0;

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
