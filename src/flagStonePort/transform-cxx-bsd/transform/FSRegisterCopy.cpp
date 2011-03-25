/*
 *  FSRegisterCopy.cpp
 *  Transform SWF
 *
 *  Created by smackay on Sat Mar 29 2003.
 *  Copyright (c) 2001-2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file is part of the Transform SWF library. You may not use this file except in
 *  compliance with the terms of the license (the 'License') that accompanied this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an 
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone 
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY 
 *  RIGHTS. Please see the License for the specific language governing rights and limitations 
 *  under the License.
 */

#include "FSRegisterCopy.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSRegisterCopy::FSRegisterCopy(FSInputStream* aStream) : FSActionObject(RegisterCopy), registerNumber(0)
    {
        decodeFromStream(aStream);
    }

    const char* FSRegisterCopy::className() const
    {
        const static char _name[] = "FSRegisterCopy";
    
        return _name;
    }
    
    int FSRegisterCopy::lengthInStream(FSOutputStream* aStream)
    {
        FSActionObject::lengthInStream(aStream);
        
        length += 1;
        
        return length;
    }
    
    void FSRegisterCopy::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSActionObject::encodeToStream(aStream);

        aStream->write(registerNumber, FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSRegisterCopy::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);

        registerNumber = aStream->read(FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
