/*
 *  FSMorphSolidLine.cpp
 *  Transform SWF
 *
 *  Created by smackay on Sun Mar 30 2003.
 *  Copyright (c) 2001-2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file is part of the Transform SWF library. You may not use this file except in
 *  compliance with the terms of the license (the 'License') that accompanied this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an 
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone 
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY 
 *  RIGHTS. Please see the License for the specific language governing rights and limitations 
 *  under the License.
 */

#include "FSMorphSolidLine.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSMorphSolidLine::FSMorphSolidLine(FSInputStream* aStream) : startWidth(0), endWidth(0), startColor(), endColor()
    {
        decodeFromStream(aStream);
    }
    
    const char* FSMorphSolidLine::className() const
    {
        static char* _name = "FSMorphSolidLine";
    
        return _name;
    }
    
    int FSMorphSolidLine::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = 4;
    
        tagLength += startColor.lengthInStream(aStream);
        tagLength += endColor.lengthInStream(aStream);
    
        return tagLength;
    }
    
    void FSMorphSolidLine::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */

        aStream->write(startWidth, FSStream::UnsignedWord, 16);
        aStream->write(endWidth, FSStream::UnsignedWord, 16);
        startColor.encodeToStream(aStream);
        endColor.encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSMorphSolidLine::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        startWidth = aStream->read(FSStream::UnsignedWord, 16);
        endWidth = aStream->read(FSStream::UnsignedWord, 16);
        startColor.decodeFromStream(aStream);
        endColor.decodeFromStream(aStream);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}