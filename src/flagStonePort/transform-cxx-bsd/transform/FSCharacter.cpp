/*
 *  FSCharacter.cpp
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

#include "FSCharacter.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSCharacter::FSCharacter(FSInputStream* aStream) : glyphIndex(0), advance(0)
    {
        decodeFromStream(aStream);
    }

    const char* FSCharacter::className() const
    {
        const static char _name[] = "FSCharacter";

        return _name;
    }

    int FSCharacter::lengthInStream(FSOutputStream* aStream)
    {
        int numberOfGlyphBits = aStream->getContext(FSStream::GlyphBits);
        int numberOfAdvanceBits = aStream->getContext(FSStream::AdvanceBits);
        
        return numberOfGlyphBits + numberOfAdvanceBits;
    }
    
    void FSCharacter::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */

        aStream->write(glyphIndex, FSStream::UnsignedBit, aStream->getContext(FSStream::GlyphBits));
        aStream->write(advance, FSStream::SignedBit, aStream->getContext(FSStream::AdvanceBits));

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSCharacter::decodeFromStream(FSInputStream* aStream)
    {
        int numberOfGlyphBits = aStream->getContext(FSStream::GlyphBits);
        int numberOfAdvanceBits = aStream->getContext(FSStream::AdvanceBits);
        
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        glyphIndex = aStream->read(FSStream::UnsignedBit, numberOfGlyphBits);
        advance = aStream->read(FSStream::SignedBit, numberOfAdvanceBits);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}