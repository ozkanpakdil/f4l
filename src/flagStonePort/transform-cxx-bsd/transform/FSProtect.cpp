/*
 *  FSProtect.cpp
 *  Transform SWF
 *
 *  Created by smackay on Wed Feb 12 2003.
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

#include "FSProtect.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSProtect::FSProtect(FSInputStream* aStream) : FSMovieObject(Protect), password()
    {
        decodeFromStream(aStream);
    }

    const char* FSProtect::className() const
    {
        const static char _name[] = "FSProtect";

        return _name;
    }

    int FSProtect::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);

        if ((aStream->getContext(FSStream::Version) >= 5) && (password.length() > 0))
            length += 2 + password.length() + 1;
            
        return length;
    }    

    void FSProtect::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        if ((aStream->getContext(FSStream::Version) >= 5) && (password.length() > 0))
        {
            aStream->write(0, FSStream::UnsignedWord, 16);
            aStream->write((byte*)password.c_str(), password.length());
            aStream->write(0, FSStream::UnsignedWord, 8);
        }
        aStream->endEncoding(className());
    }

    void FSProtect::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

        if ((aStream->getContext(FSStream::Version) >= 5) && (length > 0))
        {
            aStream->read(FSStream::UnsignedWord, 16);

            const char* str = aStream->readString();
            password = str;
            delete [] str;
        }
        aStream->endDecoding(className());
    }
}
