/*
 *  FSTabOrder.cpp
 *  Transform SWF
 *
 *  Created by smackay on Fri Apr 30 2004.
 *  Copyright (c) 2001-2004 Flagstone Software Ltd. All rights reserved.
 *
 *  This file contains Original Code and/or Modifications of Original Code as defined in
 *  and that are subject to the Flagstone Software Source License Version 1.0 (the 'License').
 *  You may not use this file except in compliance with the License. Please obtain a copy
 *  of the License at http://www.flagstonesoftware.com/licenses/source.html and read it
 *  before using this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an 
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone 
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY 
 *  RIGHTS. Please see the License for the specific language governing rights and limitations 
 *  under the License.
 */

#include "FSTabOrder.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSTabOrder::FSTabOrder(FSInputStream* aStream) :
        FSMovieObject(TabOrder),
		layer(0),
        index(0)
	{
        decodeFromStream(aStream);
	}
    
    const char* FSTabOrder::className() const
    {
        const static char _name[] = "FSTabOrder";

        return _name;
    }
    
	int FSTabOrder::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);

		length += 4;
        
        return length;
    }
    	
	void FSTabOrder::encodeToStream(FSOutputStream* aStream) 
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        aStream->write(layer, FSStream::UnsignedWord, 16);
        aStream->write(index, FSStream::UnsignedWord, 16);

        aStream->endEncoding(className());
    }
    
	void FSTabOrder::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
		FSMovieObject::decodeFromStream(aStream);

		layer = aStream->read(FSStream::UnsignedWord, 16);
		index = aStream->read(FSStream::UnsignedWord, 16);

        aStream->endDecoding(className());
    }
}
