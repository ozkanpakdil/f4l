/*
 *  FSSerialNumber.cpp
 *  Transform SWF
 *
 *  Created by smackay on Sat Mar 29 2003.
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

#include "FSSerialNumber.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSSerialNumber::FSSerialNumber(FSInputStream* aStream) :
        FSMovieObject(SerialNumber),
        serialNumber()
    {
        decodeFromStream(aStream);
    }

    const char* FSSerialNumber::className() const
    {
        const static char _name[] = "FSSerialNumber";
    
        return _name;
    }
    
    int FSSerialNumber::lengthInStream(FSOutputStream* aStream)
    { 
        FSMovieObject::lengthInStream(aStream);
        
        length += serialNumber.length() + 1;
        
        return length;
    }
        
    void FSSerialNumber::encodeToStream(FSOutputStream* aStream) 
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        aStream->write((byte*)serialNumber.c_str(), serialNumber.length());
        aStream->write(0, FSStream::UnsignedWord, 8);

        aStream->endEncoding(className());
    }
    
    void FSSerialNumber::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

        char* str = aStream->readString();

        serialNumber = str;
        delete [] str;
        
        aStream->endDecoding(className());
    }
}
