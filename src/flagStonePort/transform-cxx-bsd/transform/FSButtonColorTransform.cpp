/*
 *  FSButtonColorTransform.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 24 2003.
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

#include "FSButtonColorTransform.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSButtonColorTransform::FSButtonColorTransform(FSInputStream* aStream) :
        FSMovieObject(ButtonColorTransform),
        identifier(0),
        colorTransform()
    {
        decodeFromStream(aStream);
    }

    const char* FSButtonColorTransform::className() const
    {
        const static char _name[] = "FSButtonColorTransform";

        return _name;
    }
    
    int FSButtonColorTransform::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);
    
        length += 2;
        length += colorTransform.lengthInStream(aStream);
    
        return length;
    }
    
    void FSButtonColorTransform::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSMovieObject::encodeToStream(aStream);
        
        aStream->write(identifier, FSStream::UnsignedWord, 16);
        colorTransform.encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSButtonColorTransform::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSMovieObject::decodeFromStream(aStream);
        
        identifier = aStream->read(FSStream::UnsignedWord, 16);
        colorTransform.decodeFromStream(aStream);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
