/*
 *  FSGetUrl.cpp
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

#include "FSGetUrl.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSGetUrl::FSGetUrl(FSInputStream* aStream) :
        FSActionObject(GetUrl),
        url(),
        target()
    {
        decodeFromStream(aStream);
    }

    const char* FSGetUrl::className() const
    {
        const static char _name[] = "FSGetUrl";
    
        return _name;
    }
    
    int FSGetUrl::lengthInStream(FSOutputStream* aStream)
    { 
        FSActionObject::lengthInStream(aStream);

        length += url.length() + 1;
        length += target.length() + 1;
        
        return length;
    }
        
    void FSGetUrl::encodeToStream(FSOutputStream* aStream) 
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSActionObject::encodeToStream(aStream);

        aStream->write((byte*)url.c_str(), url.length());
        aStream->write(0, FSStream::UnsignedWord, 8);

        aStream->write((byte*)target.c_str(), target.length());
        aStream->write(0, FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSGetUrl::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);

        url = aStream->readString();
        target = aStream->readString();
        
#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
