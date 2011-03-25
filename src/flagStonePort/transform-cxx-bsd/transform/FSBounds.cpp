/*
 *  FSBounds.cpp
 *  Transform
 *
 *  Created by Stuart MacKay on Fri Feb 07 2003.
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

#include "FSBounds.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform {

    FSBounds::FSBounds(FSInputStream* aStream) :
        minX(0),
        minY(0),
        maxX(0),
        maxY(0)
    {
        decodeFromStream(aStream);
    }

    const char* FSBounds::className() const
    {
        const static char _name[] = "FSBounds";

        return _name;
    }
                    
    int FSBounds::lengthInStream(FSOutputStream* aStream)
    {
        int numberOfBits = 0;
        
        numberOfBits = 5 + fieldSize()*4;
        numberOfBits += (numberOfBits % 8 > 0) ? 8 - (numberOfBits % 8) : 0;
        
        return  numberOfBits>>3; 
    }
        
    void FSBounds::encodeToStream(FSOutputStream* aStream)
    {
        int numberOfBits = fieldSize();
    
    #ifdef _DEBUG
        aStream->startEncoding(className());
    #endif
        
        /*
        * The parent object decides whether to perform validation since
        * there are situations where the bounds objects will all zeroes
        * are valid - FSDefoneFont2 is an example.
        */
        aStream->flush();
    
        aStream->write(numberOfBits, FSStream::UnsignedBit, 5);
        aStream->write(minX, FSStream::SignedBit, numberOfBits);
        aStream->write(maxX, FSStream::SignedBit, numberOfBits);
        aStream->write(minY, FSStream::SignedBit, numberOfBits);
        aStream->write(maxY, FSStream::SignedBit, numberOfBits);
    
        aStream->flush();
    
    #ifdef _DEBUG
        aStream->endEncoding(className());
    #endif
    }
        
    void FSBounds::decodeFromStream(FSInputStream* aStream)
    {
        int fieldSize = 0;
    
    #ifdef _DEBUG
        aStream->startDecoding(className());
    #endif
    
        aStream->flush();
    
        fieldSize = aStream->read(FSStream::UnsignedBit, 5);
        minX = aStream->read(FSStream::SignedBit, fieldSize);
        maxX = aStream->read(FSStream::SignedBit, fieldSize);
        minY = aStream->read(FSStream::SignedBit, fieldSize);
        maxY = aStream->read(FSStream::SignedBit, fieldSize);
    
        aStream->flush();
    
    #ifdef _DEBUG
        aStream->endDecoding(className());
    #endif
    }
    
    int FSBounds::fieldSize() const
    {
        int values[4] = { minX, maxX, minY, maxY };
    
        return FSStream::FieldSize(values, 4, true);
    }
}