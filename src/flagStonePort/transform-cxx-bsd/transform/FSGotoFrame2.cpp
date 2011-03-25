/*
 *  FSGotoFrame2.cpp
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

#include "FSGotoFrame2.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{     
    FSGotoFrame2::FSGotoFrame2(FSInputStream* aStream) :
        FSActionObject(GotoFrame2),
        playFrame(false)
    {
        decodeFromStream(aStream);
    }

    const char* FSGotoFrame2::className() const
    {
        const static char _name[] = "FSGotoFrame2";

        return _name;
    }
    
    int FSGotoFrame2::lengthInStream(FSOutputStream* aStream)
    {
        FSActionObject::lengthInStream(aStream);
        
        length += 1 + ((frameOffset > 0) ? 2 : 0);
        
        return length;
    }
    
    void FSGotoFrame2::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSActionObject::encodeToStream(aStream);

        aStream->write(0, FSStream::UnsignedBit, 6);
        aStream->write(frameOffset != 0 ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(playFrame ? 1 : 0, FSStream::UnsignedBit, 1);

        if (frameOffset > 0)
            aStream->write(frameOffset, FSStream::UnsignedWord, 16);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSGotoFrame2::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);

        aStream->read(FSStream::UnsignedBit, 6);

        bool containsOffset = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        playFrame = aStream->read(FSStream::UnsignedBit, 1) == 1 ;
        
        if (containsOffset)
            frameOffset = aStream->read(FSStream::UnsignedWord, 16);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
