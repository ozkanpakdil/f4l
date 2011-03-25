/*
 *  FSPlaceObject.java
 *  Transform SWF
 *
 *  Created by smackay on Fri Mar 28 2003.
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

#include "FSPlaceObject.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSPlaceObject::FSPlaceObject(FSInputStream* aStream) :
        FSMovieObject(PlaceObject),
        identifier(0),
        layer(0),
        transform(),
        colorTransform()
    {
        decodeFromStream(aStream);
    }

    const char* FSPlaceObject::className() const
    {
        const static char _name[] = "FSPlaceObject";
    
        return _name;
    }

    int FSPlaceObject::lengthInStream(FSOutputStream* aStream)
    { 
        FSMovieObject::lengthInStream(aStream);
        
        length += 4;
        length += transform.lengthInStream(aStream);
        length += (colorTransform.isUnityTransform(aStream)) ? 0 : colorTransform.lengthInStream(aStream);

        return length;
    }
        
    void FSPlaceObject::encodeToStream(FSOutputStream* aStream) 
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        aStream->write(identifier, FSStream::UnsignedWord, 16);
        aStream->write(layer, FSStream::UnsignedWord, 16);
        transform.encodeToStream(aStream);

        if (!colorTransform.isUnityTransform(aStream))
            colorTransform.encodeToStream(aStream);
        
        aStream->endEncoding(className());
    }
    
    void FSPlaceObject::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);
        
        int lengthRead = aStream->getCursor();

        identifier = aStream->read(FSStream::UnsignedWord, 16);
        layer = aStream->read(FSStream::UnsignedWord, 16);
        transform = FSCoordTransform(aStream);

        lengthRead = (aStream->getCursor() - lengthRead) >> 3;

        if (getLength() > lengthRead)
            colorTransform = FSColorTransform(aStream);
        
        aStream->endDecoding(className());
    }
}
