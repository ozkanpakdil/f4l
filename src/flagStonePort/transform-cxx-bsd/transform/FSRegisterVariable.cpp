/*
 *  FSRegisterVariable.cpp
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

#include "FSRegisterVariable.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSRegisterVariable::FSRegisterVariable(FSInputStream* aStream) : index(), name()
	{
		decodeFromStream(aStream);
	}

    const char* FSRegisterVariable::className() const
    {
        const static char _name[] = "FSRegisterVariable";
    
        return _name;
    }

	int FSRegisterVariable::lengthInStream(FSOutputStream* aStream)
	{
		int length = 1 + name.length() + 1;

		return length;
	}
	
	void FSRegisterVariable::encodeToStream(FSOutputStream* aStream)
	{
        aStream->startEncoding(className());

        aStream->write(index, FSStream::UnsignedWord, 8);
        aStream->write((byte*)name.c_str(), name.length());
        aStream->write(0, FSStream::UnsignedWord, 8);

        aStream->endEncoding(className());
	}
	
	void FSRegisterVariable::decodeFromStream(FSInputStream* aStream)
	{
        aStream->startDecoding(className());

        index = aStream->read(FSStream::UnsignedWord, 8);

		const char* str = aStream->readString();
        name = str;
        delete [] str;

        aStream->endDecoding(className());
	}
}
