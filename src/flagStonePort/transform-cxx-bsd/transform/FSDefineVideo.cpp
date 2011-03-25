/*
 *  FSDefineVideo.cpp
 *  Transform SWF
 *
 *  Created by smackay on Fri Apr 30 2004.
 *  Copyright (c) 2001-2004 Flagstone Software Ltd. All rights reserved.
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

#include "FSDefineVideo.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
	FSDefineVideo::FSDefineVideo(FSInputStream* aStream) :
		FSDefineObject(DefineVideo, 0),
		count(0),
		width(0),
		height(0),
		deblocking(0),
		smoothing(false),
		codec(0)
	{
		decodeFromStream(aStream);
	}

    const char* FSDefineVideo::className() const
    {
        const static char _name[] = "FSDefineVideo";

        return _name;
    }

	int FSDefineVideo::lengthInStream(FSOutputStream* aStream)
	{
		FSDefineObject::lengthInStream(aStream);

		length += 8;

		return length;
	}
	
	void FSDefineVideo::encodeToStream(FSOutputStream* aStream)
	{
        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);
	
		aStream->write(count, FSStream::UnsignedWord, 16);
		aStream->write(width, FSStream::UnsignedWord, 16);
		aStream->write(height, FSStream::UnsignedWord, 16);
		aStream->write(0, FSStream::UnsignedBit, 5);
		aStream->write(deblocking, FSStream::UnsignedBit, 2);
		aStream->write(smoothing ? 1:0, FSStream::UnsignedBit, 1);
		aStream->write(codec, FSStream::UnsignedWord, 8);

		aStream->endEncoding(className());
	}
	
	void FSDefineVideo::decodeFromStream(FSInputStream* aStream)
	{
        aStream->startDecoding(className());
		FSDefineObject::decodeFromStream(aStream);
		
		count = aStream->read(FSStream::UnsignedWord, 16);
		width = aStream->read(FSStream::UnsignedWord, 16);
		height = aStream->read(FSStream::UnsignedWord, 16);
		aStream->read(FSStream::UnsignedBit, 5);
		deblocking = aStream->read(FSStream::UnsignedBit, 2);
		smoothing = aStream->read(FSStream::UnsignedBit, 1) == 1 ? true : false;
		codec = aStream->read(FSStream::UnsignedWord, 8);

        aStream->endDecoding(className());
	}
}
