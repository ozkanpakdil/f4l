/*
 *  FSQuicktimeMovie.java
 *  Transform SWF
 *
 *  Created by smackay on Tue Apr 27 2004.
 *  Copyright (c) 2001-2004 Flagstone Software Ltd. All rights reserved.
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

#include "FSQuicktimeMovie.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSQuicktimeMovie::FSQuicktimeMovie(FSInputStream* aStream) :
         FSMovieObject(QuicktimeMovie),
         name()
    {
        decodeFromStream(aStream);
    }

    const char* FSQuicktimeMovie::className() const
    {
        const static char _name[] = "FSQuicktimeMovie";
    
        return _name;
    }

    int FSQuicktimeMovie::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);

        length += name.length() + 1;
            
        return length;
    }
    
    void FSQuicktimeMovie::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        aStream->write((byte*)name.c_str(), name.length());
        aStream->write(0, FSStream::UnsignedWord, 8);

        aStream->endEncoding(className());
    }
    
    void FSQuicktimeMovie::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

        const char* str = aStream->readString();
        name = str;
        delete [] str;

        aStream->endDecoding(className());
    }
}
