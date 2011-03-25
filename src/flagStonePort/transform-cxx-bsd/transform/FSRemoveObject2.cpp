/*
 *  FSRemoveObject2.cpp
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

#include "FSRemoveObject2.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSRemoveObject2::FSRemoveObject2(FSInputStream* aStream) : FSMovieObject(RemoveObject2), layer(0)
    {
        decodeFromStream(aStream);
    }

    const char* FSRemoveObject2::className() const
    {
        const static char _name[] = "FSRemoveObject2";

        return _name;
    }
    
    int FSRemoveObject2::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);
        
        length += 2;
        
        return length;
    }
    
    void FSRemoveObject2::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        aStream->write(layer, FSStream::UnsignedWord, 16);

        aStream->endEncoding(className());
    }
    
    void FSRemoveObject2::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);
        
        layer = aStream->read(FSStream::UnsignedWord, 16);

        aStream->endDecoding(className());
    }
}