/*
 *  FSColorTransform.cpp
 *  Transform SWF
 *
 *  Created by smackay on Tue Feb 18 2003.
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

#include "FSColorTransform.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSColorTransform::FSColorTransform(FSInputStream* aStream) :
        multiplyRed(1.0f),
        multiplyGreen(1.0f),
        multiplyBlue(1.0f),
        multiplyAlpha(1.0f),
        addRed(0),
        addGreen(0),
        addBlue(0),
        addAlpha(0)
    {
        decodeFromStream(aStream);
    }    
    
    const char* FSColorTransform::className() const
    {
        const static char _name[] = "FSColorTransform";

        return _name;
    }
                
    bool FSColorTransform::isUnityTransform(FSStream* aStream) const
    {
        return (containsAddTerms(aStream) == false) && (containsMultiplyTerms(aStream) == false);
    }

    int FSColorTransform::lengthInStream(FSOutputStream* aStream)
    {
        int numberOfBits = 6;
        int _fieldSize = fieldSize(aStream);
        
        bool _containsMultiplyTerms = containsMultiplyTerms(aStream);
        bool _containsAddTerms = containsAddTerms(aStream);
    
        if (_containsMultiplyTerms)
            numberOfBits += _fieldSize * ((aStream->getContext(FSStream::ColorContainsAlpha)) ? 4 : 3);
            
        if (_containsAddTerms)
            numberOfBits += _fieldSize * ((aStream->getContext(FSStream::ColorContainsAlpha)) ? 4 : 3);

        numberOfBits += (numberOfBits % 8 > 0) ? 8 - (numberOfBits % 8) : 0;
    
        return numberOfBits>>3;
    }
    
    void FSColorTransform::encodeToStream(FSOutputStream* aStream)
    {
        int numberOfBits = fieldSize(aStream);
        
        bool _containsMultiplyTerms = containsMultiplyTerms(aStream);
        bool _containsAddTerms = containsAddTerms(aStream);
        
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */
            
        aStream->flush();
        
        aStream->write(_containsAddTerms ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(_containsMultiplyTerms ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(numberOfBits, FSStream::UnsignedBit, 4);
    
        if (_containsMultiplyTerms)
        {
            aStream->write(multiplyRed, FSStream::FixedShort, numberOfBits);
            aStream->write(multiplyGreen, FSStream::FixedShort, numberOfBits);
            aStream->write(multiplyBlue, FSStream::FixedShort, numberOfBits);
    
            if (aStream->getContext(FSStream::ColorContainsAlpha))
                aStream->write(multiplyAlpha, FSStream::FixedShort, numberOfBits);
        }
        if (_containsAddTerms)
        {
            aStream->write(addRed, FSStream::SignedBit, numberOfBits);
            aStream->write(addGreen, FSStream::SignedBit, numberOfBits);
            aStream->write(addBlue, FSStream::SignedBit, numberOfBits);
    
            if (aStream->getContext(FSStream::ColorContainsAlpha))
                aStream->write(addAlpha, FSStream::SignedBit, numberOfBits);
        }
        aStream->flush();

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
     
    void FSColorTransform::decodeFromStream(FSInputStream* aStream)
    {
        bool containsAddTerms = false;
        bool containsMultiplyTerms = false;
        int fieldSize = 0;
                
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        aStream->flush();

        containsAddTerms = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        containsMultiplyTerms = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        fieldSize = aStream->read(FSStream::UnsignedBit, 4);
        
        if (containsMultiplyTerms)
        {
            multiplyRed = aStream->read(FSStream::FixedShort, fieldSize);
            multiplyGreen = aStream->read(FSStream::FixedShort, fieldSize);
            multiplyBlue = aStream->read(FSStream::FixedShort, fieldSize);
            
            if (aStream->getContext(FSStream::ColorContainsAlpha))
                multiplyAlpha = aStream->read(FSStream::FixedShort, fieldSize);
            else
                aStream->read(FSStream::SignedBit, 0);
        }
        else
        {
            aStream->read(FSStream::FixedShort, 0);
            aStream->read(FSStream::FixedShort, 0);
            aStream->read(FSStream::FixedShort, 0);
            aStream->read(FSStream::FixedShort, 0);
        }
        
        if (containsAddTerms)
        {
            addRed = aStream->read(FSStream::SignedBit, fieldSize);
            addGreen = aStream->read(FSStream::SignedBit, fieldSize);
            addBlue = aStream->read(FSStream::SignedBit, fieldSize);
            
            if (aStream->getContext(FSStream::ColorContainsAlpha))
                addAlpha = aStream->read(FSStream::SignedBit, fieldSize);
            else
                aStream->read(FSStream::SignedBit, 0);
        }
        else
        {
            aStream->read(FSStream::SignedBit, 0);
            aStream->read(FSStream::SignedBit, 0);
            aStream->read(FSStream::SignedBit, 0);
            aStream->read(FSStream::SignedBit, 0);
        }
        aStream->flush();

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }

    bool FSColorTransform::containsAddTerms(FSStream* aStream) const
    {
        bool containsTerms = addRed != 0 || addGreen != 0 || addBlue != 0;
        
        if (aStream->getContext(FSStream::ColorContainsAlpha))
            containsTerms = containsTerms || addAlpha != 0;
            
        return containsTerms;
    }

    bool FSColorTransform::containsMultiplyTerms(FSStream* aStream)  const
    {
        bool containsTerms = multiplyRed != 1.0 || multiplyGreen != 1.0 || multiplyBlue != 1.0;
        
        if (aStream->getContext(FSStream::ColorContainsAlpha))
            containsTerms = containsTerms || multiplyAlpha != 1.0;
        
        return containsTerms;
    }

    int FSColorTransform::addFieldSize(FSOutputStream* aStream) const
    {
        int size = 0;

        if (aStream->getContext(FSStream::ColorContainsAlpha))
        {
            int values[4] = { addRed, addGreen, addBlue, addAlpha };
            size = FSStream::FieldSize(values, 4, true);
        }
        else
        {
            int values[3] = { addRed, addGreen, addBlue };
            size = FSStream::FieldSize(values, 3, true);
        }
        return size;
    }

    int FSColorTransform::multiplyFieldSize(FSOutputStream* aStream) const
    {
        int size = 0;

        if (aStream->getContext(FSStream::ColorContainsAlpha))
        {
            float values[4] = { multiplyRed, multiplyGreen, multiplyBlue, multiplyAlpha };
            size = FSStream::FieldSize(values, 4, FSStream::FixedShort);
        }
        else
        {
            float values[3] = { multiplyRed, multiplyGreen, multiplyBlue };
            size = FSStream::FieldSize(values, 3, FSStream::FixedShort);
        }
        return size;
    }

    int FSColorTransform::fieldSize(FSOutputStream* aStream) const
    {
        bool _containsMultiplyTerms = containsMultiplyTerms(aStream);
        bool _containsAddTerms = containsAddTerms(aStream);
        int numberOfBits = 0;

        if (_containsAddTerms && !_containsMultiplyTerms)
            numberOfBits = addFieldSize(aStream);
        else if (!_containsAddTerms && _containsMultiplyTerms)
            numberOfBits = multiplyFieldSize(aStream);
        else if (_containsAddTerms && _containsMultiplyTerms)
        {
            int addSize = addFieldSize(aStream);
            int multSize = multiplyFieldSize(aStream);

            numberOfBits = (addSize > multSize) ? addSize : multSize;
        }
        else
            numberOfBits = 0;

        return numberOfBits;
    }    
}