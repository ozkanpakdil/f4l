/*
 *  FSTableIndex.cpp
 *  Transform SWF
 *
 *  Created by smackay on Wed Feb 19 2003.
 *  Copyright (c) 2001-2003 Flagstone Software Ltd. All rights reserved.
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

#include "FSTableIndex.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSTableIndex::FSTableIndex(FSInputStream* aStream) :
        FSValue(FSValue::TableIndex),
        index(0)
    {
        decodeFromStream(aStream);
    }
    
    const char* FSTableIndex::className() const
    {
        const static char _name[] = "FSTableIndex";

        return _name;
    }
    
    int FSTableIndex::length() const { return index < 256 ? 2 : 3; }

    int FSTableIndex::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = FSValue::lengthInStream(aStream);

        tagLength += index < 256 ? 1 : 2;
        
        return tagLength;
    }
        
    void FSTableIndex::encodeToStream(FSOutputStream* aStream) 
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        type = index < 256 ? 8 : 9;
        
        aStream->write(type, FSStream::UnsignedWord, 8);
        aStream->write(index, FSStream::UnsignedWord, type == 8 ? 8 : 16);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSTableIndex::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSValue::decodeFromStream(aStream);

        index = aStream->read(FSStream::UnsignedWord, type == 8 ? 8 : 16);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
