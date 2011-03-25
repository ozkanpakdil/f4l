/*
 *  FSDefineJPEGImage.cpp
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

#include "FSDefineJPEGImage.h"

#include <stdlib.h>

#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSException.h"

using namespace transform;

namespace transform
{
     FSDefineJPEGImage::FSDefineJPEGImage(FSInputStream* aStream) :
        FSDefineObject(DefineJPEGImage, 0),
        width(0),
        height(0),
        image(0),
        imageLength(0)
    {
        decodeFromStream(aStream);
    }

    FSDefineJPEGImage::FSDefineJPEGImage(int anIdentifier, byte* bytes, size_t numberOfBytes) : 
        FSDefineObject(DefineJPEGImage, anIdentifier), 
        width(0), 
        height(0), 
        image(0), 
        imageLength(0)
    {
        setImage(bytes, numberOfBytes);
    }

   FSDefineJPEGImage::FSDefineJPEGImage(const FSDefineJPEGImage& rhs) : 
        FSDefineObject(rhs), 
        width(rhs.width), 
        height(rhs.height),
        image(0),
        imageLength(rhs.imageLength)
    {
        image = new byte[imageLength];

        if (imageLength > 0 && image == 0)
            throw FSAllocationException("Could not allocate memory to copy an image.");

        memcpy(image, rhs.image, imageLength*sizeof(byte));
    }

    FSDefineJPEGImage::~FSDefineJPEGImage()
    {
        delete [] image;
        image = 0;
    }

    const char* FSDefineJPEGImage::className() const
    {
        const static char _name[] = "FSDefineJPEGImage";

        return _name;
    }    

    FSDefineJPEGImage& FSDefineJPEGImage::operator= (const FSDefineJPEGImage& rhs)
    {
        if (this != &rhs)
        {
            this->FSDefineObject::operator=(rhs);
            
            width = rhs.width;
            height = rhs.height;
            imageLength = rhs.imageLength;

            delete [] image;

            image = new byte[imageLength];

            if (imageLength > 0 && image == 0)
                throw FSAllocationException("Could not allocate memory to copy an image.");

            memcpy(image, rhs.image, imageLength*sizeof(byte));
        }
        return *this;
    }

    void FSDefineJPEGImage::setImage(byte* bytes, size_t numberOfBytes)
    {
        delete [] image;

        imageLength = numberOfBytes;
        image = bytes;

        unsigned int index = 0;
        int marker = 0;
        int size = 0;

        if (image[index++] == 0xff && image[index++] == 0xd8)
        {
            while (index < imageLength)
            {
                marker = (image[index++] & 0xff) << 8;
                marker |= image[index++] & 0xff;

                size = (image[index++] & 0xff) << 8;
                size |= image[index++] & 0xff;

                if (marker >= 0xffc0 && marker <= 0xffcf && marker != 0xffc4 && marker != 0xffc8)
                {
                    height = (image[index+1] & 0xff) << 8 | (image[index+2] & 0xff);
                    width = (image[index+3] & 0xff) << 8 | (image[index+4] & 0xff);
                }
                index += size-2;
            }
        }
    }
    
    int FSDefineJPEGImage::lengthInStream(FSOutputStream* aStream)
    {
        FSDefineObject::lengthInStream(aStream);
    
        length += imageLength;
    
        return length;
    }
    
    void FSDefineJPEGImage::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);
        
        aStream->write(image, imageLength);

        aStream->endEncoding(className());
    }
    
    void FSDefineJPEGImage::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);
        
        int numberOfBytes = getLength()-2;
        byte* bytes = aStream->read(numberOfBytes);

        setImage(bytes, numberOfBytes);

        aStream->endDecoding(className());
    }
}
