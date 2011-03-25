/*
 *  FSDefineImage.cpp
 *  Transform SWF
 *
 *  Created by smackay on Tue Feb 25 2003.
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

#include "FSDefineImage.h"

#include <stdlib.h>

#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSException.h"

using namespace transform;

namespace transform
{
    FSDefineImage::FSDefineImage(FSInputStream* aStream) :
        FSDefineObject(DefineImage, 0),
        width(0),
        height(0),
        pixelSize(0),
        tableSize(0),
        imageLength(0),
        image(0)
    {
        extendLength = true;
        decodeFromStream(aStream);
    }

    FSDefineImage::FSDefineImage(int anIdentifier, int aWidth, int aHeight, int aTableSize, byte* bytes, size_t numberOfBytes) : 
        FSDefineObject(DefineImage, anIdentifier), 
        width(aWidth), 
        height(aHeight), 
        pixelSize(8), 
        tableSize(aTableSize), 
        imageLength(numberOfBytes), 
        image(bytes)
    {
        extendLength = true;
    }

    FSDefineImage::FSDefineImage(int anIdentifier, int aWidth, int aHeight, byte* bytes, size_t numberOfBytes, int aPixelSize) : 
        FSDefineObject(DefineImage, anIdentifier), 
        width(aWidth), 
        height(aHeight), 
        pixelSize(aPixelSize), 
        tableSize(0), 
        imageLength(numberOfBytes), 
        image(bytes)
    {
        extendLength = true;
    }

    FSDefineImage::FSDefineImage(const FSDefineImage& rhs) :
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

    FSDefineImage::~FSDefineImage()
    {
        delete [] image;
        image = 0;
    }

    const char* FSDefineImage::className() const
    {
        const static char _name[] = "FSDefineImage";

        return _name;
    }

    FSDefineImage& FSDefineImage::operator= (const FSDefineImage& rhs)
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

    int FSDefineImage::lengthInStream(FSOutputStream* aStream)
    {
        FSDefineObject::lengthInStream(aStream);

        length += 5;
        length += (pixelSize == 8) ? 1 : 0;
        length += imageLength;

        return length;
    }
    
    void FSDefineImage::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        aStream->setContext(FSStream::Type, type);

        int word = (getType() << 6) | 0x3F;
    
        aStream->write(word, FSStream::UnsignedWord, 16);
        aStream->write(length, FSStream::UnsignedWord, 32);
        aStream->write(getIdentifier(), FSStream::UnsignedWord, 16);

        switch (pixelSize)
        {
            case 8:
                aStream->write(3, FSStream::UnsignedWord, 8);
                break;
            case 16:
                aStream->write(4, FSStream::UnsignedWord, 8);
                break;
            case 24:
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
    
    void FSDefineImage::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);
        
        switch (aStream->read(FSStream::UnsignedWord, 8))
        {
            case 3:
                pixelSize = 8;
                break;
            case 4:
                pixelSize = 16;
                break;
            case 5:
                pixelSize = 24;
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
