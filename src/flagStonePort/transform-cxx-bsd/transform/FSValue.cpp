/*
 *  FSValue.h
 *  Transform SWF
 *
 *  Created by Stuart MacKay on Fri Feb 07 2003.
 *  Copyright (c) 2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file contains Original Code and/or Modifications of Original Code as defined in
 *  and that are subject to the Flagstone Software Source License Version 1.0 (the 'License').
 *  You may not use this file except in compliance with the License. Please obtain a copy
 *  of the License at http://www.flagstonesoftware.com/licenses/source.html and read it
 *  before using this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY
 *  RIGHTS. Please see the License for the specific language governing rights and limitations
 *  under the License.
 */

#include "FSValue.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSValue::FSValue(FSInputStream* aStream) : type(0)
    {
        decodeFromStream(aStream);
    }

    FSValue& FSValue::operator= (const FSValue& rhs)
    {
        if (this != &rhs)
        {
            type = rhs.type;
        }
        return *this;
    }

    int FSValue::lengthInStream(FSOutputStream* aStream)
    {
        return 1;
    }
    
    void FSValue::encodeToStream(FSOutputStream* aStream)
    {
        aStream->write(type, FSStream::UnsignedWord, 8);
    }

    void FSValue::decodeFromStream(FSInputStream* aStream)
    {
        type = aStream->read(FSStream::UnsignedWord, 8);
    }
} 
