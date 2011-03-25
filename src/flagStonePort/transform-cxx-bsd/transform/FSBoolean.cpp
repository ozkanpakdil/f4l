/*
 *  FSBoolean.cpp
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

#include "FSBoolean.h"

#include <stdio.h>

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSBoolean::FSBoolean(FSInputStream* aStream) : FSValue(FSValue::Boolean), value(false)
    {
        decodeFromStream(aStream);
    }

    const char* FSBoolean::className() const
    {
        const static char _name[] = "FSBoolean";

        return _name;
    }

    int FSBoolean::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = FSValue::lengthInStream(aStream);

        tagLength += 1;
        
        return tagLength;
    }
    
    void FSBoolean::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSValue::encodeToStream(aStream);

        aStream->write(value, FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSBoolean::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSValue::decodeFromStream(aStream);
        
        value = aStream->read(FSStream::UnsignedWord, 8) == 1;

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
} 
