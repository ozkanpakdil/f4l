/*
 *  FSButton.cpp
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

#include "FSButton.h"

#include <string.h>
#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSMovieObject.h"

using namespace transform;

namespace transform
{
    FSButton::FSButton(FSInputStream* aStream) :
        state(0),
        identifier(0),
        layer(0),
        transform(),
        colorTransform() 
    {
        decodeFromStream(aStream);
    }

    const char* FSButton::className() const
    {
        const static char _name[] = "FSButton";

        return _name;
    }
    
    int FSButton::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = 0;
    
        tagLength += 5;
        tagLength += transform.lengthInStream(aStream);

        if (aStream->getContext(FSStream::Type) == FSMovieObject::DefineButton2)
            tagLength += colorTransform.lengthInStream(aStream);
    
        return tagLength;
    }
    
    void FSButton::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        aStream->write(0, FSStream::UnsignedBit, 4);
        aStream->write(state, FSStream::UnsignedBit, 4);
        aStream->write(identifier, FSStream::UnsignedWord, 16);
        aStream->write(layer, FSStream::UnsignedWord, 16);

        transform.encodeToStream(aStream);

        if (aStream->getContext(FSStream::Type) == FSMovieObject::DefineButton2)
            colorTransform.encodeToStream(aStream);
                   
#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSButton::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        aStream->read(FSStream::UnsignedBit, 4);
        state = aStream->read(FSStream::UnsignedBit, 4);
        identifier = aStream->read(FSStream::UnsignedWord, 16);
        layer = aStream->read(FSStream::UnsignedWord, 16);

        transform.decodeFromStream(aStream);

        if (aStream->getContext(FSStream::Type) == FSMovieObject::DefineButton2)
            colorTransform.decodeFromStream(aStream);            

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
