/*
 *  FSMovieObject.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 10 2003.
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

#include "FSMovieObject.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSMovieObject::FSMovieObject(const FSMovieObject& rhs) :
        type(rhs.type),
        length(rhs.length),
        extendLength(rhs.extendLength)
    {
    }

    FSMovieObject& FSMovieObject::operator= (const FSMovieObject& rhs)
    {
        if (this != &rhs)
        {
            type = rhs.type;
            length = rhs.length;
            extendLength = rhs.extendLength;
        }
        return *this;
    }

    int FSMovieObject::lengthInStream(FSOutputStream* aStream)
    {
        aStream->setContext(FSStream::Type, type);

        length = 0;

        return length;
    }

    void FSMovieObject::encodeToStream(FSOutputStream* aStream)
    {
        aStream->setContext(FSStream::Type, type);
        
        if (extendLength == false && length < 63)
        {
            aStream->write((type << 6) | length, FSStream::UnsignedWord, 16);
        }
        else
        {
            aStream->write((type << 6) | 0x3F, FSStream::UnsignedWord, 16);            
            aStream->write(length, FSStream::UnsignedWord, 32);
        }
    }
    
    void FSMovieObject::decodeFromStream(FSInputStream* aStream)
    {
        /* Read the type and length fields without triggering a stream event.
         * This is done as the order of the type snd length fields are reversed
         * since the data is stored as a 16-bit little endian word.
         */
        int word = aStream->scan(FSStream::UnsignedWord, 16);
        
        type = word >> 6;
        length = word & 0x3F;

        // Log the stream events manually so the type and length fields will
        // be logged correctly.

#ifdef _DEBUG
        aStream->log(aStream->getCursor()-16, 16, type);
        aStream->log(aStream->getCursor()-16, 16, length);
#endif    
        if (length == 0x3F)
        {
            length = aStream->read(FSStream::UnsignedWord, 32);

            /* Remember whether the length was encoded in the 32-bit
             * extension field so that when the object is encoded during 
             * regression testing the encoded representation matches
             * the original.
             */
            extendLength = true;
        }
        else
        {
            aStream->read(FSStream::UnsignedWord, 0);
        }
        aStream->setContext(FSStream::Type, type);
    }
}
