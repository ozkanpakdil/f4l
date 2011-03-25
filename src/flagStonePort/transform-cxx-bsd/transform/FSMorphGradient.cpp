/*
 *  FSMorphGradient.cpp
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

#include "FSMorphGradient.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSMorphGradient::FSMorphGradient(FSInputStream* aStream) : startRatio(0), endRatio(0), startColor(), endColor()
    {
        decodeFromStream(aStream);
    }

    const char* FSMorphGradient::className() const
    {
        static char* _name = "FSMorphGradient";
    
        return _name;
    }
    
    int FSMorphGradient::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = 2;
    
        tagLength += startColor.lengthInStream(aStream);
        tagLength += endColor.lengthInStream(aStream);
    
        return tagLength;
    }
    
    void FSMorphGradient::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */

        aStream->write(startRatio, FSStream::UnsignedWord, 8);
        startColor.encodeToStream(aStream);
        aStream->write(endRatio, FSStream::UnsignedWord, 8);
        endColor.encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSMorphGradient::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        startRatio = aStream->read(FSStream::UnsignedWord, 8);
        startColor.decodeFromStream(aStream);
        endRatio = aStream->read(FSStream::UnsignedWord, 8);
        endColor.decodeFromStream(aStream);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}