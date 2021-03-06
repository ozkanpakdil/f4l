/*
 *  FSGotoLabel.cpp
 *  Transform SWF
 *
 *  Created by smackay on Sat Mar 29 2003.
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

#include "FSGotoLabel.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSGotoLabel::FSGotoLabel(FSInputStream* aStream) :
        FSActionObject(GotoLabel),
        label()
    {
        decodeFromStream(aStream);
    }

    const char* FSGotoLabel::className() const
    {
        const static char _name[] = "FSGotoLabel";
    
        return _name;
    }
    
    int FSGotoLabel::lengthInStream(FSOutputStream* aStream)
    { 
        FSActionObject::lengthInStream(aStream);
        
        length += label.length() + 1;
        
        return length;
    }
        
    void FSGotoLabel::encodeToStream(FSOutputStream* aStream) 
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSActionObject::encodeToStream(aStream);

        aStream->write((byte*)label.c_str(), label.length());
        aStream->write(0, FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSGotoLabel::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);

        label = aStream->readString();
        
#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
