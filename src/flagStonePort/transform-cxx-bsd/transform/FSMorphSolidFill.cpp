/*
 *  FSMorphSolidFill.cpp
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

#include "FSMorphSolidFill.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSMorphSolidFill::FSMorphSolidFill(FSInputStream* aStream) : FSFillStyle(Solid), startColor(), endColor()
    {
        decodeFromStream(aStream);
    }
    
    const char* FSMorphSolidFill::className() const
    {
        static char* _name = "FSMorphSolidFill";
    
        return _name;
    }

    int FSMorphSolidFill::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = FSFillStyle::lengthInStream(aStream);
    
        tagLength += startColor.lengthInStream(aStream);
        tagLength += endColor.lengthInStream(aStream);
    
        return tagLength;
    }
    
    void FSMorphSolidFill::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */
        FSFillStyle::encodeToStream(aStream);
        
        startColor.encodeToStream(aStream);
        endColor.encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSMorphSolidFill::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSFillStyle::decodeFromStream(aStream);

        startColor.decodeFromStream(aStream);
        endColor.decodeFromStream(aStream);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
