/*
 *  FSCurve.cpp
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

#include "FSCurve.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSCurve::FSCurve(FSInputStream* aStream) :
        FSShapeObject(Curve),
        controlX(0),
        controlY(0),
        anchorX(0),
        anchorY(0) 
    {
        decodeFromStream(aStream);
    }
    
    const char* FSCurve::className() const
    {
        const static char _name[] = "FSCurve";

        return _name;
    }

    int FSCurve::lengthInStream(FSOutputStream* aStream)
    {
        int numberOfBits = 6;
    
        numberOfBits += fieldSize()*4;
    
        aStream->setCursor(aStream->getCursor()+numberOfBits);

        return numberOfBits;
    }
    
    void FSCurve::encodeToStream(FSOutputStream* aStream)
    {
        int _fieldSize = fieldSize();
        
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */

        aStream->write(1, FSStream::UnsignedBit, 1);
        aStream->write(0, FSStream::UnsignedBit, 1);
        aStream->write(_fieldSize-2, FSStream::UnsignedBit, 4);
        aStream->write(controlX, FSStream::SignedBit, _fieldSize);
        aStream->write(controlY, FSStream::SignedBit, _fieldSize);
        aStream->write(anchorX, FSStream::SignedBit, _fieldSize);
        aStream->write(anchorY, FSStream::SignedBit, _fieldSize);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSCurve::decodeFromStream(FSInputStream* aStream)
    {
        int shapeType = 0;
        int edgeType = 0;
        int fieldSize = 0;
        
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        shapeType = aStream->read(FSStream::UnsignedBit, 1);
        edgeType = aStream->read(FSStream::UnsignedBit, 1);
        fieldSize = aStream->read(FSStream::UnsignedBit, 4) + 2;
        controlX = aStream->read(FSStream::SignedBit, fieldSize);
        controlY = aStream->read(FSStream::SignedBit, fieldSize);
        anchorX = aStream->read(FSStream::SignedBit, fieldSize);
        anchorY = aStream->read(FSStream::SignedBit, fieldSize);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }

    int FSCurve::fieldSize() const
    {
        int values[4] = { controlX, controlY, anchorX, anchorY };
        int size = FSStream::FieldSize(values, 4, true);

        return (size < 2) ? 2 : size;
    }
}
