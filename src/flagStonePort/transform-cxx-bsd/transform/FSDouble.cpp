/*
 *  FSDouble.cpp
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

#include "FSDouble.h"

#include <stdio.h>

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSDouble::FSDouble(FSInputStream* aStream) : FSValue(FSValue::Double), value(0.0)
    {
        decodeFromStream(aStream);
    }
    
    const char* FSDouble::className() const
    {
        const static char _name[] = "FSDouble";

        return _name;
    }

    int FSDouble::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = FSValue::lengthInStream(aStream);

        tagLength += 8;
        
        return tagLength;
    }
    
    void FSDouble::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSValue::encodeToStream(aStream);
        
        aStream->write(value);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSDouble::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSValue::decodeFromStream(aStream);
        
        value = aStream->read();

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
} 
