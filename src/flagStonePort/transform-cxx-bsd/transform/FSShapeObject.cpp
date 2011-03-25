/*
 *  FSShapeObject.h
 *  Transform SWF
 *
 *  Created by Stuart MacKay on Fri Feb 07 2003.
 *  Copyright (c) 2003 Flagstone Software Ltd. All rights reserved.
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

#include "FSShapeObject.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSShapeObject::FSShapeObject(FSInputStream* aStream) : type(0)
    {
        decodeFromStream(aStream);
    }

    FSShapeObject::FSShapeObject(const FSShapeObject& rhs) : type(rhs.type)
    {
    }

    FSShapeObject& FSShapeObject::operator= (const FSShapeObject& rhs)
    {
        if (this != &rhs)
        {
            type = rhs.type;
        }
        return *this;
    }

    int FSShapeObject::lengthInStream(FSOutputStream* aStream)
    {
        return 0;
    }
    
    void FSShapeObject::encodeToStream(FSOutputStream* aStream)
    {
    }

    void FSShapeObject::decodeFromStream(FSInputStream* aStream)
    {
    }
} 
