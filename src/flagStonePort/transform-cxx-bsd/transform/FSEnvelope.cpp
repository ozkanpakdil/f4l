/*
 *  FSEnvelope.cpp
 *  Transform SWF
 *
 *  Created by smackay on Thu Feb 20 2003.
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

#include "FSEnvelope.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSEnvelope::FSEnvelope(FSInputStream* aStream) :
        mark(0),
        left(0),
        right(0)
    {
        decodeFromStream(aStream);
    }

    const char* FSEnvelope::className() const
    {
        const static char _name[] = "FSEnvelope";

        return _name;
    }

    int FSEnvelope::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = 8;
        
        return tagLength;
    }
    
    void FSEnvelope::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */

        aStream->write(mark, FSStream::UnsignedWord, 32);
        aStream->write(left, FSStream::UnsignedWord, 16);
        aStream->write(right, FSStream::UnsignedWord, 16);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSEnvelope::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        mark = aStream->read(FSStream::UnsignedWord, 32);
        left = aStream->read(FSStream::UnsignedWord, 16);
        right = aStream->read(FSStream::UnsignedWord, 16);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
