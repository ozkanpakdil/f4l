/*
 *  FSMorphBitmapFill.cpp
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

#include "FSMorphBitmapFill.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSMorphBitmapFill::FSMorphBitmapFill(FSInputStream* aStream) : FSFillStyle(TiledBitmap), identifier(0), startTransform(), endTransform()
    {
        decodeFromStream(aStream);
    }

    const char* FSMorphBitmapFill::className() const
    {
        static char* _name = "FSMorphBitmapFill";

        return _name;
    }
    
    int FSMorphBitmapFill::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = FSFillStyle::lengthInStream(aStream);

        tagLength += 2;
        tagLength += startTransform.lengthInStream(aStream);
        tagLength += endTransform.lengthInStream(aStream);
    
        return tagLength;
    }
    
    void FSMorphBitmapFill::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */
        FSFillStyle::encodeToStream(aStream);
        
        aStream->write(identifier, FSStream::UnsignedWord, 16);
        
        startTransform.encodeToStream(aStream);
        endTransform.encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSMorphBitmapFill::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSFillStyle::decodeFromStream(aStream);

        identifier = aStream->read(FSStream::UnsignedWord, 16);
        
        startTransform.decodeFromStream(aStream);
        endTransform.decodeFromStream(aStream);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
