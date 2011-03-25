/*
 *  FSNull.h
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

#include "FSNull.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSNull::FSNull(FSInputStream* aStream) : FSValue(Null)
    {
        decodeFromStream(aStream);
    }

    const char* FSNull::className() const
    {
        const static char _name[] = "FSNull";

        return _name;
    }

    int FSNull::lengthInStream(FSOutputStream* aStream)
    {
        return FSValue::lengthInStream(aStream);
    }
    
    void FSNull::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSValue::encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSNull::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSValue::decodeFromStream(aStream);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}