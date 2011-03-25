/*
 *  FSIf.cpp
 *  Transform SWF
 *
 *  Created by smackay on Wed Feb 19 2003.
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

#include "FSIf.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSIf::FSIf(FSInputStream* aStream) :
        FSActionObject(If),
        offset(0)
    {
        decodeFromStream(aStream);
    }

    const char* FSIf::className() const
    {
        const static char _name[] = "FSIf";

        return _name;
    }

    int FSIf::lengthInStream(FSOutputStream* aStream)
    {
        FSActionObject::lengthInStream(aStream);
        
        length += 2;
        
        return length;
    }
    
    void FSIf::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSActionObject::encodeToStream(aStream);

        aStream->write(offset, FSStream::SignedWord, 16);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSIf::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);

        offset = aStream->read(FSStream::SignedWord, 16);
        
#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
