/*
 *  FSDefineObject.cpp
 *  Transform SWF
 *
 *  Created by smackay on Wed Feb 12 2003.
 *  Copyright (c) 2001-2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file contains Original Code and/or Modifications of Original Code as defined in
 *  and that are subject to the Flagstone Software Source License Version 1.0 (the
 * 'License'). You may not use this file except in compliance with the License. Please
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

#include "FSDefineObject.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSDefineObject::FSDefineObject(const FSDefineObject& rhs) :
        FSMovieObject(rhs),
        identifier(rhs.identifier)
    {
    }

    FSDefineObject& FSDefineObject::operator= (const FSDefineObject& rhs)
    {
        if (this != &rhs)
        {
            this->FSMovieObject::operator=(rhs);
            
            identifier = rhs.identifier;
        }
        return *this;
    }
    
    int FSDefineObject::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);
        
        length += 2;
        
        return length;
    }
    
    void FSDefineObject::encodeToStream(FSOutputStream* aStream)
    {
        FSMovieObject::encodeToStream(aStream);

        aStream->write(identifier, FSStream::UnsignedWord, 16);
    }
    
    void FSDefineObject::decodeFromStream(FSInputStream* aStream)
    {
        FSMovieObject::decodeFromStream(aStream);

        identifier = aStream->read(FSStream::UnsignedWord, 16);
    }
}
