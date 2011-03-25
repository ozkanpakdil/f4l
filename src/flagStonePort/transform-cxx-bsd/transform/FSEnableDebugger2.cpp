/*
 *  FSEnableDebugger2.java
 *  Transform SWF
 *
 *  Created by smackay on Fri Apr 30 2004.
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

#include "FSEnableDebugger2.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSEnableDebugger2::FSEnableDebugger2(FSInputStream* aStream) :
         FSMovieObject(EnableDebugger2),
         password()
	{
		decodeFromStream(aStream);
	}

    const char* FSEnableDebugger2::className() const
    {
        const static char _name[] = "FSEnableDebugger2";
    
        return _name;
    }

	int FSEnableDebugger2::lengthInStream(FSOutputStream* aStream)
	{
		FSMovieObject::lengthInStream(aStream);

		length += 2 + password.length() + 1;
			
		return length;
	}
	
	void FSEnableDebugger2::encodeToStream(FSOutputStream* aStream)
	{
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

		aStream->write(0, FSStream::UnsignedWord, 16);
        aStream->write((byte*)password.c_str(), password.length());
        aStream->write(0, FSStream::UnsignedWord, 8);

        aStream->endEncoding(className());
	}
	
	void FSEnableDebugger2::decodeFromStream(FSInputStream* aStream)
	{
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

		aStream->read(FSStream::UnsignedWord, 16);
        const char* str = aStream->readString();
        password = str;
        delete [] str;

        aStream->endDecoding(className());
	}
}
