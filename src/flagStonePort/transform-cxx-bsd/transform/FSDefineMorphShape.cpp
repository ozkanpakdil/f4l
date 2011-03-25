/*
 *  FSDefineMorphShape.cpp
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

#include "FSDefineMorphShape.h"

#include "FSMovie.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

#include "FSLineStyle.h"
#include "FSFillStyle.h"
#include "FSMorphSolidLine.h"
#include "FSMorphSolidFill.h"
#include "FSMorphBitmapFill.h"
#include "FSMorphGradientFill.h"
#include "FSShape.h"

using namespace transform;

namespace transform
{
    FSDefineMorphShape::FSDefineMorphShape(FSInputStream* aStream) :
        FSDefineObject(DefineMorphShape, 0),
        startBounds(),
        endBounds(),
        fillStyles(),
        lineStyles(),
        startShape(),
        endShape()
    {
        decodeFromStream(aStream);
    }
    
    FSDefineMorphShape::FSDefineMorphShape(const FSDefineMorphShape& rhs) :
        FSDefineObject(rhs),
        startBounds(rhs.startBounds),
        endBounds(rhs.endBounds),
        fillStyles(rhs.fillStyles.size()),
        lineStyles(rhs.lineStyles.size()),
        startShape(rhs.startShape),
        endShape(rhs.endShape)
    {
        int index = 0;
            
        for (FSVector<FSFillStyle*>::const_iterator i = rhs.fillStyles.begin(); i != rhs.fillStyles.end(); i++, index++)
            fillStyles[index] = (*i)->clone();

        index = 0;
        
        for (FSVector<FSLineStyle*>::const_iterator i = rhs.lineStyles.begin(); i != rhs.lineStyles.end(); i++, index++)
            lineStyles[index] = (*i)->clone();
    }

    FSDefineMorphShape::~FSDefineMorphShape()
    {
        for (FSVector<FSFillStyle*>::iterator i = fillStyles.begin(); i != fillStyles.end(); i++)
        {
            delete *i;
            *i = 0;
        }
        
        for (FSVector<FSLineStyle*>::iterator i = lineStyles.begin(); i != lineStyles.end(); i++)
        {
            delete *i;
            *i = 0;
        }
    }
    
    const char* FSDefineMorphShape::className() const
    {
        const static char _name[] = "FSDefineMorphShape";

        return _name;
    }

    FSDefineMorphShape& FSDefineMorphShape::operator= (const FSDefineMorphShape& rhs)
    {
        if (this != &rhs)
        {
            this->FSDefineObject::operator=(rhs);

            startBounds = rhs.startBounds;
            endBounds = rhs.endBounds;

            for (FSVector<FSFillStyle*>::iterator i = fillStyles.begin(); i != fillStyles.end(); i++)
            {
                delete *i;
                *i = 0;
            }

            fillStyles = FSVector<FSFillStyle*>(rhs.fillStyles.size());

            int index = 0;
            
            for (FSVector<FSFillStyle*>::const_iterator i = rhs.fillStyles.begin(); i != rhs.fillStyles.end(); i++, index++)
                fillStyles[index] = (*i)->clone();


            for (FSVector<FSLineStyle*>::iterator i = lineStyles.begin(); i != lineStyles.end(); i++)
            {
                delete *i;
                *i = 0;
            }

            lineStyles = FSVector<FSLineStyle*>(rhs.lineStyles.size());

            index = 0;
            
            for (FSVector<FSLineStyle*>::const_iterator i = rhs.lineStyles.begin(); i != rhs.lineStyles.end(); i++, index++)
                lineStyles[index] = (*i)->clone();

            startShape = rhs.startShape;
            endShape = rhs.endShape;
        }
        return *this;
    }

    void FSDefineMorphShape::add(const FSVector<FSFillStyle*>& anArray)
    {
        for (FSVector<FSFillStyle*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            fillStyles.push_back(*i);
    }
    
    void FSDefineMorphShape::add(const FSVector<FSLineStyle*>& anArray)
    {
        for (FSVector<FSLineStyle*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            lineStyles.push_back(*i);
    }
    
    int FSDefineMorphShape::lengthInStream(FSOutputStream* aStream)
    {
        int numberOfFillBits = fillStyles.size() > 0 ? FSStream::FieldSize((int)(fillStyles.size())): 0;
        int numberOfLineBits = lineStyles.size() > 0 ? FSStream::FieldSize((int)(lineStyles.size())): 0;
        
        FSDefineObject::lengthInStream(aStream);

        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        length += startBounds.lengthInStream(aStream);
        length += endBounds.lengthInStream(aStream);
        length += 4;

        length += (fillStyles.size() >= 255) ? 3 : 1;

        for (FSVector<FSFillStyle*>::const_iterator i = fillStyles.begin(); i != fillStyles.end(); ++i)
            length += (*i)->lengthInStream(aStream);
    
        length += (lineStyles.size() >= 255) ? 3 : 1;

        for (FSVector<FSLineStyle*>::const_iterator i = lineStyles.begin(); i != lineStyles.end(); ++i)
            length += (*i)->lengthInStream(aStream);
    
        aStream->setContext(FSStream::FillBits, numberOfFillBits);
        aStream->setContext(FSStream::LineBits, numberOfLineBits);
        aStream->setContext(FSStream::ArrayCountExtended, 1);
    
        length += startShape.lengthInStream(aStream);

        // Number of Fill and Line bits is zero for end shape.
        
        aStream->setContext(FSStream::FillBits, 0);
        aStream->setContext(FSStream::LineBits, 0);

        length += endShape.lengthInStream(aStream);

        aStream->setContext(FSStream::ArrayCountExtended, 0);
        aStream->setContext(FSStream::ColorContainsAlpha, 0);

        return length;
    }
    
    void FSDefineMorphShape::encodeToStream(FSOutputStream* aStream)
    {
        int numberOfFillBits = fillStyles.size() > 0 ? FSStream::FieldSize((int)(fillStyles.size())): 0;
        int numberOfLineBits = lineStyles.size() > 0 ? FSStream::FieldSize((int)(lineStyles.size())): 0;

        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);

        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        startBounds.encodeToStream(aStream);
        endBounds.encodeToStream(aStream);

        int offsetStart = aStream->getCursor();
        aStream->write(0, FSStream::UnsignedWord, 32);

        if (fillStyles.size() >= 255)
        {
            aStream->write(0xFF, FSStream::UnsignedWord, 8);
            aStream->write((int)(fillStyles.size()), FSStream::UnsignedWord, 16);
        }
        else
        {
            aStream->write((int)(fillStyles.size()), FSStream::UnsignedWord, 8);
        }
    
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSFillStyle*>::iterator i = fillStyles.begin(); i != fillStyles.end(); ++i)
            (*i)->encodeToStream(aStream);
    
#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
        if (lineStyles.size() >= 255)
        {
            aStream->write(0xFF, FSStream::UnsignedWord, 8);
            aStream->write((int)(lineStyles.size()), FSStream::UnsignedWord, 16);
        }
        else
        {
            aStream->write((int)(lineStyles.size()), FSStream::UnsignedWord, 8);
        }
                
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSLineStyle*>::iterator i = lineStyles.begin(); i != lineStyles.end(); ++i)
            (*i)->encodeToStream(aStream);
    
#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
        aStream->setContext(FSStream::FillBits, numberOfFillBits);
        aStream->setContext(FSStream::LineBits, numberOfLineBits);
        aStream->setContext(FSStream::ArrayCountExtended, 1);

        aStream->setContext(FSStream::FillStyles, (int)(fillStyles.size()));
        aStream->setContext(FSStream::LineStyles, (int)(lineStyles.size()));

        startShape.encodeToStream(aStream);

        int offsetEnd = (aStream->getCursor() - offsetStart) >> 3;
        int currentCursor = aStream->getCursor();

        aStream->setCursor(offsetStart);
        aStream->write(offsetEnd-4, FSStream::UnsignedWord, 32);
        aStream->setCursor(currentCursor);

        // Number of Fill and Line bits is zero for end shape.

        aStream->setContext(FSStream::FillBits, 0);
        aStream->setContext(FSStream::LineBits, 0);

        aStream->setContext(FSStream::FillStyles, 0);
        aStream->setContext(FSStream::LineStyles, 0);

        endShape.encodeToStream(aStream);

        aStream->setContext(FSStream::ArrayCountExtended, 0);
        aStream->setContext(FSStream::ColorContainsAlpha, 0);

        aStream->endEncoding(className());
    }
    
    void FSDefineMorphShape::decodeFromStream(FSInputStream* aStream)
    {
        int fillStyleCount = 0;
        int lineStyleCount = 0;
        
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);

        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        startBounds.decodeFromStream(aStream);
        endBounds.decodeFromStream(aStream);

        aStream->read(FSStream::UnsignedWord, 32); // offset to end shape.

        fillStyleCount = aStream->read(FSStream::UnsignedWord, 8);

        if (fillStyleCount == 0xFF)
            fillStyleCount = aStream->read(FSStream::UnsignedWord, 16);
        else
            aStream->read(FSStream::UnsignedWord, 0);
            
#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=0; i<fillStyleCount; i++)
            fillStyles.push_back(FSMovie::fillStyleFromStream(aStream));
        
#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        lineStyleCount = aStream->read(FSStream::UnsignedWord, 8);

        if (lineStyleCount == 0xFF)
            lineStyleCount = aStream->read(FSStream::UnsignedWord, 16);
        else
            aStream->read(FSStream::UnsignedWord, 0);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=0; i<lineStyleCount; i++)
            lineStyles.push_back(new FSMorphSolidLine(aStream));

#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        startShape.decodeFromStream(aStream);
        endShape.decodeFromStream(aStream);

        aStream->setContext(FSStream::ColorContainsAlpha, 0);

        aStream->endDecoding(className());
    }
}