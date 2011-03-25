/*
 *  FSLineStyle.h
 *  Transform SWF
 *
 *  Created by Stuart MacKay on Thu Feb 20 2003.
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

#include "FSLineStyle.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSLineStyle::FSLineStyle(FSInputStream* aStream)
    {
        decodeFromStream(aStream);
    }

    FSLineStyle::FSLineStyle()
    {
    }

    int FSLineStyle::lengthInStream(FSOutputStream* aStream)
    {
        return 0;
    }
    
    void FSLineStyle::encodeToStream(FSOutputStream* aStream)
    {
    }

    void FSLineStyle::decodeFromStream(FSInputStream* aStream)
    {
    }
} 
