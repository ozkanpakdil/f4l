/*
 *  FSGotoFrame.java
 *  Transform SWF
 *
 *  Created by smackay on Fri Mar 28 2003.
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

#include "FSGotoFrame.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSGotoFrame::FSGotoFrame(FSInputStream* aStream) :
        FSActionObject(GotoFrame),
        frameNumber(1)
    {
        decodeFromStream(aStream);
    }

    const char* FSGotoFrame::className() const
    {
        const static char _name[] = "FSGotoFrame";
    
        return _name;
    }
    
    int FSGotoFrame::lengthInStream(FSOutputStream* aStream)
    { 
        FSActionObject::lengthInStream(aStream);
        
        length += 2;
        
        return length;
    }
        
    void FSGotoFrame::encodeToStream(FSOutputStream* aStream) 
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSActionObject::encodeToStream(aStream);

        aStream->write(frameNumber, FSStream::UnsignedWord, 16);
            
#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSGotoFrame::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);

        frameNumber = aStream->read(FSStream::UnsignedWord, 16);
        
#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
