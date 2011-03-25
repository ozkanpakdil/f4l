/*
 *  FSLine.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 10 2003.
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

#include "FSLine.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSLine::FSLine(FSInputStream* aStream) : FSShapeObject(Line), x(0), y(0)
    {
        decodeFromStream(aStream);
    }
    
    const char* FSLine::className() const
    {
        const static char _name[] = "FSLine";

        return _name;
    }
    
    int FSLine::lengthInStream(FSOutputStream* aStream)
    {
        int numberOfBits = 7;
    
        if (containsGeneralLine())
            numberOfBits += fieldSize() * 2;
        else
        {
            numberOfBits += 1 + fieldSize();
        }
    
        aStream->setCursor(aStream->getCursor()+numberOfBits);

        return numberOfBits;
    }
    
    void FSLine::encodeToStream(FSOutputStream* aStream)
    {
        bool _containsGeneralLine = containsGeneralLine();
        bool _containsVerticalLine = containsVerticalLine();
        
        int _fieldSize = fieldSize();

#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */

        aStream->write(1, FSStream::UnsignedBit, 1);
        aStream->write(1, FSStream::UnsignedBit, 1);
        aStream->write(_fieldSize-2, FSStream::UnsignedBit, 4);
        aStream->write(_containsGeneralLine ? 1 : 0, FSStream::UnsignedBit, 1);
            
        if (_containsGeneralLine)
        {
            aStream->write(x, FSStream::SignedBit, _fieldSize);
            aStream->write(y, FSStream::SignedBit, _fieldSize);
        }
        else
        {
            aStream->write(_containsVerticalLine ? 1 : 0, FSStream::UnsignedBit, 1);
            aStream->write(_containsVerticalLine ? y : x, FSStream::SignedBit, _fieldSize);
        } 
#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSLine::decodeFromStream(FSInputStream* aStream)
    {
        bool _containsGeneralLine = false;
        bool _containsVerticalLine = false;
        
        int shapeType = 0;
        int edgeType = 0;
        int fieldSize = 0;
        
#ifdef _DEBUG
            aStream->startDecoding(className());
#endif
        shapeType = aStream->read(FSStream::UnsignedBit, 1);
        edgeType = aStream->read(FSStream::UnsignedBit, 1);
        fieldSize = aStream->read(FSStream::UnsignedBit, 4)+2;

        _containsGeneralLine = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;

        // Dummy reads are used so event logging registers fields in the correct order
        // Fields are recorded in the following order: containsVerticalLine, x, y.
        if (_containsGeneralLine)
        {
            aStream->read(FSStream::SignedBit, 0);  
                       
            x = aStream->read(FSStream::SignedBit, fieldSize);
            y = aStream->read(FSStream::SignedBit, fieldSize);
        }
        else
        {
            _containsVerticalLine = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;

            if (_containsVerticalLine)
            {
                aStream->read(FSStream::SignedBit, 0);  
                y = aStream->read(FSStream::SignedBit, fieldSize);
            }
            else
            {
                x = aStream->read(FSStream::SignedBit, fieldSize);
                aStream->read(FSStream::SignedBit, 0);  
            }
        }
#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
    
    bool FSLine::containsGeneralLine() const
    {
        return x != 0 && y != 0;
    }
    
    bool FSLine::containsVerticalLine() const
    {
        return x == 0 && y != 0;
    }
    
    int FSLine::fieldSize() const
    {
        int values[2] = { x, y };
        int size = FSStream::FieldSize(values, 2, true);

        return (size < 2) ? 2 : size;
    }
}
