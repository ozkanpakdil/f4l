/*
 *  FSActionObject.cpp
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

#include "FSActionObject.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSActionObject::FSActionObject(const FSActionObject& rhs) :
        type(rhs.type),
        length(rhs.length)
    {
    }

    FSActionObject& FSActionObject::operator= (const FSActionObject& rhs)
    {
        if (this != &rhs)
        {
            type = rhs.type;
            length = rhs.length;
        }
        return *this;
    }

    int FSActionObject::lengthInStream(FSOutputStream* aStream)
    {
        length = 0;

        return length;
    }
    
    void FSActionObject::encodeToStream(FSOutputStream* aStream)
    {
        aStream->write(type, FSStream::UnsignedWord, 8);

        if (type >= 128)
            aStream->write(length, FSStream::UnsignedWord, 16);
    }
    
    void FSActionObject::decodeFromStream(FSInputStream* aStream)
    {
        type = aStream->read(FSStream::UnsignedWord, 8);
        
        if (type >= 128)
            length = aStream->read(FSStream::UnsignedWord, 16);
        else
            length = 0;
    }
}
