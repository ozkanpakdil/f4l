/*
 *  FSDefineImage2.cpp
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

#include "FSDefineImage2.h"

#include <stdlib.h>

#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSException.h"

using namespace transform;

namespace transform
{
    FSDefineImage2::FSDefineImage2(FSInputStream* aStream) :
        FSDefineObject(DefineImage2, 0),
        width(0),
        height(0),
        pixelSize(0),
        tableSize(0),
        imageLength(0),
        image(0)
    {
        decodeFromStream(aStream);
    }

    FSDefineImage2::FSDefineImage2(int anIdentifier, int aWidth, int aHeight, int aTableSize, byte* bytes, size_t numberOfBytes) : 
        FSDefineObject(DefineImage2, anIdentifier), 
        width(aWidth), 
        height(aHeight), 
        pixelSize(8), 
        tableSize(aTableSize), 
        imageLength(numberOfBytes), 
        image(bytes)
    {
    }

    FSDefineImage2::FSDefineImage2(int anIdentifier, int aWidth, int aHeight, byte* bytes, size_t numberOfBytes) : 
        FSDefineObject(DefineImage2, anIdentifier), 
        width(aWidth), 
        height(aHeight), 
        pixelSize(32), 
        tableSize(0), 
        imageLength(numberOfBytes), 
        image(bytes)
    {
    }

    FSDefineImage2::FSDefineImage2(const FSDefineImage2& rhs) :
        FSDefineObject(rhs),
        width(rhs.width),
        height(rhs.height),
        pixelSize(rhs.pixelSize),
        tableSize(rhs.tableSize),
        imageLength(rhs.imageLength),
        image(0)
    {
        image = new byte[imageLength];

        if (imageLength > 0 && image == 0)
            throw FSAllocationException("Cannot allocate memory for image.");

        memcpy(image, rhs.image, imageLength*sizeof(byte));
    }

    const char* FSDefineImage2::className() const
    {
        const static char _name[] = "FSDefineImage2";

        return _name;
    }

    FSDefineImage2& FSDefineImage2::operator= (const FSDefineImage2& rhs)
    {
        if (this != &rhs)
        {
            this->FSDefineObject::operator=(rhs);
            
            width = rhs.width;
            height = rhs.height;
            pixelSize = rhs.pixelSize;
            tableSize = rhs.tableSize;

            imageLength = rhs.imageLength;

            delete [] image;

            image = new byte[imageLength];

            if (imageLength > 0 && image == 0)
                throw FSAllocationException("Cannot allocate memory for image.");

            memcpy(image, rhs.image, imageLength*sizeof(byte));
        }
        return *this;
    }

    int FSDefineImage2::lengthInStream(FSOutputStream* aStream)
    {
        FSDefineObject::lengthInStream(aStream);
    
        length += 5;
        length += (pixelSize == 8) ? 1 : 0;
        length += imageLength;

        return length;
    }
    
    void FSDefineImage2::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        
        FSDefineObject::encodeToStream(aStream);

        switch (pixelSize)
        {
            case 8:
                aStream->write(3, FSStream::UnsignedWord, 8);
                break;
            case 32:
                aStream->write(5, FSStream::UnsignedWord, 8);
                break;
        }
    
        aStream->write(width, FSStream::UnsignedWord, 16);
        aStream->write(height, FSStream::UnsignedWord, 16);

        if (pixelSize == 8)
            aStream->write(tableSize-1, FSStream::UnsignedWord, 8);

        aStream->write(image, imageLength);

        aStream->endEncoding(className());
    }
    
    void FSDefineImage2::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);
    
        switch (aStream->read(FSStream::UnsignedWord, 8))
        {
            case 3:
                pixelSize = 8;
                break;
            case 5:
                pixelSize = 32;
                break;
        }
    
        width = aStream->read(FSStream::UnsignedWord, 16);
        height = aStream->read(FSStream::UnsignedWord, 16);

        if (pixelSize == 8)
        {
            tableSize = aStream->read(FSStream::UnsignedWord, 8) + 1;
            imageLength = getLength() - 8;
            image = aStream->read(imageLength);
        }
        else
        {
            imageLength = getLength() - 7;
            image = aStream->read(imageLength);
        }
        aStream->endDecoding(className());
    }
}
