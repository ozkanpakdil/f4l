/*
 *  FSDefineJPEGImage2.cpp
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

#include "FSDefineJPEGImage2.h"

#include <stdlib.h>

#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSException.h"

using namespace transform;

namespace transform
{
    int lengthOfJPEGStream2(FSInputStream* aStream)
    {
        int start = aStream->getCursor();
        int word = aStream->scan(FSStream::UnsignedBit, 16);

        int eoi = (word == 0xFFD8) ? 0xFFD9 : 0xFFD8;
        int length = 2;

        do {
            word = aStream->scan(FSStream::UnsignedBit, 16);
            aStream->setCursor(aStream->getCursor()-8);
            length++;

        } while (word != eoi);

        aStream->setCursor(start);

        return length+1;
    }
    
    byte* readJPEGStream2(FSInputStream* aStream)
    {
        byte* bytes = 0;

        int start = aStream->getCursor();
        int word = aStream->scan(FSStream::UnsignedBit, 16);

        int eoi = (word == 0xFFD8) ? 0xFFD9 : 0xFFD8;
        int length = 2;

        do {
            word = aStream->scan(FSStream::UnsignedBit, 16);
            aStream->setCursor(aStream->getCursor()-8);
            length++;

        } while (word != eoi);

        aStream->setCursor(start);

        bytes = aStream->read(length+1);

        return bytes;
    }

     FSDefineJPEGImage2::FSDefineJPEGImage2(FSInputStream* aStream) :
        FSDefineObject(DefineJPEGImage2, 0),
        width(0),
        height(0),
        image(0),
        imageLength(0),
        encodingTable(0),
        encodingLength(0)
    {
        decodeFromStream(aStream);
    }
    
    FSDefineJPEGImage2::FSDefineJPEGImage2(int anIdentifier, byte* imageBytes, size_t imageLength, byte* encodingBytes, size_t encodingLength) : 
        FSDefineObject(DefineJPEGImage2, anIdentifier), 
        width(0), 
        height(0), 
        image(0), 
        imageLength(0), 
        encodingTable(0), 
        encodingLength(0)
    {
        setImage(imageBytes, imageLength);
        setEncodingTable(encodingBytes, encodingLength);
    }

    FSDefineJPEGImage2::FSDefineJPEGImage2(int anIdentifier, byte* imageBytes, size_t imageLength) : 
        FSDefineObject(DefineJPEGImage2, anIdentifier), 
        width(0), 
        height(0), 
        image(0), 
        imageLength(0), 
        encodingTable(0), 
        encodingLength(0)
    {
        setImage(imageBytes, imageLength);
    }

    FSDefineJPEGImage2::FSDefineJPEGImage2(const FSDefineJPEGImage2& rhs) : FSDefineObject(rhs), width(rhs.width), height(rhs.height)
    {
        image = new byte[rhs.imageLength];
        imageLength = rhs.imageLength;

        if (imageLength > 0 && image == 0)
            throw FSAllocationException("Cannot allocate memory for image.");

        memcpy(image, rhs.image, imageLength*sizeof(byte));

        encodingTable = new byte[rhs.encodingLength];
        encodingLength = rhs.encodingLength;

        if (encodingLength > 0 && encodingTable == 0)
            throw FSAllocationException("Cannot allocate memory for encoding table.");

        memcpy(encodingTable, rhs.encodingTable, encodingLength*sizeof(byte));
    }

    FSDefineJPEGImage2::~FSDefineJPEGImage2()
    {
        delete [] image;
        image = 0;

        delete [] encodingTable;
        encodingTable = 0;
    }

    const char* FSDefineJPEGImage2::className() const
    {
        const static char _name[] = "FSDefineJPEGImage2";

        return _name;
    }    

    FSDefineJPEGImage2& FSDefineJPEGImage2::operator= (const FSDefineJPEGImage2& rhs)
    {
        if (this != &rhs)
        {
            this->FSDefineObject::operator=(rhs);

            width = rhs.width;
            height = rhs.height;

            imageLength = rhs.imageLength;
            encodingLength = rhs.encodingLength;

            delete [] image;

            image = new byte[imageLength];

            if (imageLength > 0 && image == 0)
                throw FSAllocationException("Cannot allocate memory for image.");

            memcpy(image, rhs.image, imageLength*sizeof(byte));

            delete [] encodingTable;
            
            encodingTable = new byte[encodingLength];

            if (encodingLength > 0 && encodingTable == 0)
                throw FSAllocationException("Cannot allocate memory for encoding table.");

            memcpy(encodingTable, rhs.encodingTable, encodingLength*sizeof(byte));
        }
        return *this;
    }

    void FSDefineJPEGImage2::setImage(byte* bytes, size_t numberOfBytes)
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

    void FSDefineJPEGImage2::setEncodingTable(byte* bytes, size_t numberOfBytes)
    {
        delete [] encodingTable;

        encodingTable = bytes;
        encodingLength = numberOfBytes;
    }
    
    int FSDefineJPEGImage2::lengthInStream(FSOutputStream* aStream)
    {
        FSDefineObject::lengthInStream(aStream);
    
        length += encodingLength;
        length += imageLength;
        
        return length;
    }
    
    void FSDefineJPEGImage2::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);

        aStream->write(encodingTable, encodingLength);
        aStream->write(image, imageLength);

        aStream->endEncoding(className());
    }
    
    void FSDefineJPEGImage2::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);

        encodingLength = lengthOfJPEGStream2(aStream);
        encodingTable = readJPEGStream2(aStream);

        int numberOfBytes = getLength()-encodingLength-2;
        byte* bytes = aStream->read(numberOfBytes);

        setImage(bytes, numberOfBytes);

        aStream->endDecoding(className());
    }
}
