/*
 *  FSSolidLine.cpp
 *  Transform SWF
 *
 *  Created by smackay on Thu Feb 20 2003.
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

#include "FSSolidLine.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSSolidLine::FSSolidLine(FSInputStream* aStream) :
        width(0),
        color()
    {
        decodeFromStream(aStream);
    }
    
    const char* FSSolidLine::className() const
    {
        const static char _name[] = "FSSolidLine";

        return _name;
    }
    
    int FSSolidLine::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = 2;
    
        tagLength += color.lengthInStream(aStream);
    
        return tagLength;
    }
    
    void FSSolidLine::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */

        aStream->write(width, FSStream::UnsignedWord, 16);
        color.encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSSolidLine::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        width = aStream->read(FSStream::UnsignedWord, 16);
        color.decodeFromStream(aStream);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
