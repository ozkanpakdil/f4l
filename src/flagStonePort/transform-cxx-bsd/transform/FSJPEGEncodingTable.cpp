/*
 *  FSJPEGEncodingTable.cpp
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

#include "FSJPEGEncodingTable.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSException.h"

using namespace transform;

namespace transform
{
    FSJPEGEncodingTable::FSJPEGEncodingTable(FSInputStream* aStream) :
        FSMovieObject(JPEGEncodingTable),
        encodingTable(0)
    {
        decodeFromStream(aStream);
    }

    FSJPEGEncodingTable::FSJPEGEncodingTable(byte* bytes, size_t numberOfBytes) : 
        FSMovieObject(JPEGEncodingTable), encodingTable(0)
    {
        setEncodingTable(bytes, numberOfBytes);
    }

    FSJPEGEncodingTable::FSJPEGEncodingTable(const FSJPEGEncodingTable& rhs) :
        FSMovieObject(rhs),
        encodingTable(0)
    {
        if (rhs.encodingTable != 0)
        {
            encodingTable = new byte[length];

            if (length > 0 && encodingTable == 0)
                throw FSAllocationException("Could not allocate memory to copy a JPEG encoding table.");
        
            memcpy(encodingTable, rhs.encodingTable, length*sizeof(byte));
        }
        else
        {
            encodingTable = 0;
            length = 2;
        }
    }

    FSJPEGEncodingTable::~FSJPEGEncodingTable()
    {
        delete [] encodingTable;
        encodingTable = 0;
    }

    const char* FSJPEGEncodingTable::className() const
    {
        const static char _name[] = "FSJPEGEncodingTable";

        return _name;
    }    

    FSJPEGEncodingTable& FSJPEGEncodingTable::operator= (const FSJPEGEncodingTable& rhs)
    {
        if (this != &rhs)
        {
            this->FSMovieObject::operator=(rhs);

            if (rhs.encodingTable != 0)
            {
                delete [] encodingTable;

                encodingTable = new byte[length];

                if (length > 0 && encodingTable == 0)
                    throw FSAllocationException("Could not allocate memory to copy a JPEG encoding table.");

                for (int i=0; i<rhs.length; i++)
                    encodingTable[i] = rhs.encodingTable[i];
            }
            else
            {
                encodingTable = 0;
                length = 2;
            }
        }
        return *this;
    }

    void FSJPEGEncodingTable::setEncodingTable(byte* bytes, size_t numberOfBytes)
    {
        delete [] encodingTable;

        if (bytes != 0)
        {
            length = numberOfBytes;
            encodingTable = bytes;
        }
        else
        {
            length = 2;
            encodingTable = 0;
        }
    }
    
    int FSJPEGEncodingTable::lengthInStream(FSOutputStream* aStream)
    {
        return length;
    }
    
    void FSJPEGEncodingTable::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);
        
        if (encodingTable == 0)
        {
            aStream->write(0xFF, FSStream::UnsignedWord, 8);
            aStream->write(0xD9, FSStream::UnsignedWord, 8);
        }
        else
        {
            aStream->write(encodingTable, length);
        }
        
        aStream->endEncoding(className());
    }
    
    void FSJPEGEncodingTable::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

        encodingTable = aStream->read(length);

        aStream->endDecoding(className());
    }
}
