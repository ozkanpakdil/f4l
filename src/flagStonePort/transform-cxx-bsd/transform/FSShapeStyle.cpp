/*
 *  FSShapeStyle.cpp
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

#include "FSShapeStyle.h"

#include "FSMovie.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

#include "FSLineStyle.h"
#include "FSSolidLine.h"
#include "FSFillStyle.h"

using namespace transform;

namespace transform
{
    FSShapeStyle::FSShapeStyle(FSInputStream* aStream) :
        FSShapeObject(Style),
        moveX(Transform::VALUE_NOT_SET),
        moveY(Transform::VALUE_NOT_SET),
        fillStyle(Transform::VALUE_NOT_SET),
        altFillStyle(Transform::VALUE_NOT_SET),
        lineStyle(Transform::VALUE_NOT_SET),
        fillStyles(),
        lineStyles()
    {
        decodeFromStream(aStream);
    }
    
    FSShapeStyle::FSShapeStyle(const FSShapeStyle& rhs) :
        FSShapeObject(Style) ,
        moveX(rhs.moveX),
        moveY(rhs.moveY),
        fillStyle(rhs.fillStyle),
        altFillStyle(rhs.altFillStyle),
        lineStyle(rhs.lineStyle),
        fillStyles(rhs.fillStyles.size()),
        lineStyles(rhs.lineStyles.size())
    {
        int index = 0;
            
        for (FSVector<FSFillStyle*>::const_iterator i = rhs.fillStyles.begin(); i != rhs.fillStyles.end(); i++, index++)
            fillStyles[index] = (*i)->clone();

        index = 0;
        
        for (FSVector<FSLineStyle*>::const_iterator i = rhs.lineStyles.begin(); i != rhs.lineStyles.end(); i++, index++)
            lineStyles[index] = (*i)->clone();
    }

    FSShapeStyle::~FSShapeStyle()
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

    const char* FSShapeStyle::className() const
    {
        const static char _name[] = "FSShapeStyle";

        return _name;
    }

    FSShapeStyle& FSShapeStyle::operator= (const FSShapeStyle& rhs)
    {
        if (this != &rhs)
        {
            this->FSShapeObject::operator=(rhs);

            moveX = rhs.moveX;
            moveY = rhs.moveY;

            fillStyle = rhs.fillStyle;
            altFillStyle = rhs.altFillStyle;
            lineStyle = rhs.lineStyle;

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
                lineStyles[0] = (*i)->clone();
        }
        return *this;
    }

    void FSShapeStyle::add(const FSVector<FSFillStyle*>& anArray)
    {
        for (FSVector<FSFillStyle*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            fillStyles.push_back(*i);
    }

    void FSShapeStyle::add(const FSVector<FSLineStyle*>& anArray)
    {
        for (FSVector<FSLineStyle*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            lineStyles.push_back(*i);
    }

    int FSShapeStyle::lengthInStream(FSOutputStream* aStream)
    {
        bool _containsStyles = containsStyles();
        bool _containsLineStyle = containsLineStyle();
        bool _containsAltFillStyle = containsAltFillStyle();
        bool _containsFillStyle = containsFillStyle();
        bool _containsMove = containsMove();
    
        int numberOfFillBits = aStream->getContext(FSStream::FillBits);
        int numberOfLineBits = aStream->getContext(FSStream::LineBits);
        int countExtended = aStream->getContext(FSStream::ArrayCountExtended);
        
        int numberOfBits = 0;
    
        numberOfBits += 6;

        if (_containsMove)
        {
            int _moveFieldSize = fieldSize();
            
            numberOfBits += 5 + _moveFieldSize*2;
        }
    
        numberOfBits += (_containsFillStyle) ? numberOfFillBits : 0;
        numberOfBits += (_containsAltFillStyle) ? numberOfFillBits : 0;
        numberOfBits += (_containsLineStyle) ? numberOfLineBits : 0;
        
        aStream->setCursor(aStream->getCursor()+numberOfBits);

        if (_containsStyles)
        {
            int numberOfStyleBits = 0;
            int flushBits = aStream->getCursor();
            
            numberOfStyleBits += (flushBits % 8 > 0) ? 8 - (flushBits % 8) : 0;
            numberOfStyleBits += (countExtended && (fillStyles.size() >= 255)) ? 24 : 8;

            for (FSVector<FSFillStyle*>::const_iterator i = fillStyles.begin(); i != fillStyles.end(); ++i)
                numberOfStyleBits += (*i)->lengthInStream(aStream) * 8;

            numberOfStyleBits += (countExtended && (lineStyles.size() >= 255)) ? 24 : 8;

            for (FSVector<FSLineStyle*>::const_iterator i = lineStyles.begin(); i != lineStyles.end(); ++i)
                numberOfStyleBits += (*i)->lengthInStream(aStream) * 8;

            numberOfStyleBits += 8;
    
            numberOfFillBits = (int)(fillStyles.size()) > 0 ? FSStream::FieldSize((int)(fillStyles.size())): 0;
            numberOfLineBits = (int)(lineStyles.size()) > 0 ? FSStream::FieldSize((int)(lineStyles.size())): 0;

            // Update the stream with the new numbers of line and fill bits
            aStream->setContext(FSStream::FillBits, numberOfFillBits);
            aStream->setContext(FSStream::LineBits, numberOfLineBits);

            // Update the stream with the new numbers of line and fill styles
            aStream->setContext(FSStream::FillStyles, (int)(fillStyles.size()));
            aStream->setContext(FSStream::LineStyles, (int)(lineStyles.size()));

            numberOfBits += numberOfStyleBits;
            aStream->setCursor(aStream->getCursor()+numberOfStyleBits);            
        }
        return numberOfBits;
    }
    
    void FSShapeStyle::encodeToStream(FSOutputStream* aStream)
    {
        bool _containsStyles = containsStyles();
        bool _containsLineStyle = containsLineStyle();
        bool _containsAltFillStyle = containsAltFillStyle();
        bool _containsFillStyle = containsFillStyle();
        bool _containsMove = containsMove();
    
        int numberOfFillBits = aStream->getContext(FSStream::FillBits);
        int numberOfLineBits = aStream->getContext(FSStream::LineBits);
        int countExtended = aStream->getContext(FSStream::ArrayCountExtended);
            
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */

        aStream->write(0, FSStream::UnsignedBit, 1);
        aStream->write(_containsStyles ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(_containsLineStyle ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(_containsAltFillStyle ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(_containsFillStyle ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(_containsMove ? 1 : 0, FSStream::UnsignedBit, 1);

        if (_containsMove)
        {
            int _moveFieldSize = fieldSize();
            
            aStream->write(_moveFieldSize, FSStream::UnsignedBit, 5);
            aStream->write(moveX, FSStream::SignedBit, _moveFieldSize);
            aStream->write(moveY, FSStream::SignedBit, _moveFieldSize);
        }
    
        if (_containsFillStyle)
            aStream->write(fillStyle, FSStream::UnsignedBit, numberOfFillBits);
    
        if (_containsAltFillStyle)
            aStream->write(altFillStyle, FSStream::UnsignedBit, numberOfFillBits);
    
        if (_containsLineStyle)
            aStream->write(lineStyle, FSStream::UnsignedBit, numberOfLineBits);
    
        if (_containsStyles)
        {
            aStream->flush();
        
            if (countExtended && (fillStyles.size() >= 255))
            {
                aStream->write(0xFF, FSStream::UnsignedBit, 8);
                aStream->write((int)(fillStyles.size()), FSStream::UnsignedBit, 16);
            }
            else
            {
                aStream->write((int)(fillStyles.size()), FSStream::UnsignedBit, 8);
            }
    
#ifdef _DEBUG
            aStream->startEncoding("array");
#endif
            for (FSVector<FSFillStyle*>::iterator i = fillStyles.begin(); i != fillStyles.end(); ++i)
                (*i)->encodeToStream(aStream);

#ifdef _DEBUG
            aStream->endEncoding("array");
#endif
            if (countExtended && (lineStyles.size() >= 255))
            {
                aStream->write(0xFF, FSStream::UnsignedBit, 8);
                aStream->write((int)(lineStyles.size()), FSStream::UnsignedBit, 16);
            }
            else
            {
                aStream->write((int)(lineStyles.size()), FSStream::UnsignedBit, 8);
            }

#ifdef _DEBUG
            aStream->startEncoding("array");
#endif
            for (FSVector<FSLineStyle*>::iterator i = lineStyles.begin(); i != lineStyles.end(); ++i)
                (*i)->encodeToStream(aStream);

#ifdef _DEBUG
            aStream->endEncoding("array");
#endif
    
            numberOfFillBits = fillStyles.size() > 0 ? FSStream::FieldSize((int)(fillStyles.size())): 0;
            numberOfLineBits = lineStyles.size() > 0 ? FSStream::FieldSize((int)(lineStyles.size())): 0;
        
            aStream->write(numberOfFillBits, FSStream::UnsignedBit, 4);
            aStream->write(numberOfLineBits, FSStream::UnsignedBit, 4);

            // Update the stream with the new numbers of line and fill bits
            aStream->setContext(FSStream::FillBits, numberOfFillBits);
            aStream->setContext(FSStream::LineBits, numberOfLineBits);

            // Update the stream with the new numbers of line and fill styles
            aStream->setContext(FSStream::FillStyles, (int)(fillStyles.size()));
            aStream->setContext(FSStream::LineStyles, (int)(lineStyles.size()));
        }
#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSShapeStyle::decodeFromStream(FSInputStream* aStream)
    {
        bool _containsStyles = false;
        bool _containsLineStyle = false;
        bool _containsAltFillStyle = false;
        bool _containsFillStyle = false;
        bool _containsMove = false;
        
        int numberOfFillBits = aStream->getContext(FSStream::FillBits);
        int numberOfLineBits = aStream->getContext(FSStream::LineBits);
        int shapeType = 0;
        int fillStyleCount = 0;
        int lineStyleCount = 0;
        int moveFieldSize = 0;

#ifdef _DEBUG
        aStream->startDecoding(className());
#endif

        shapeType = aStream->read(FSStream::UnsignedBit, 1);
        _containsStyles = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        _containsLineStyle = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        _containsAltFillStyle = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        _containsFillStyle = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        _containsMove = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        
        if (_containsMove)
        {
            moveFieldSize = aStream->read(FSStream::UnsignedBit, 5);
            moveX = aStream->read(FSStream::SignedBit, moveFieldSize);
            moveY = aStream->read(FSStream::SignedBit, moveFieldSize);
        }
        else
        {
            aStream->read(FSStream::UnsignedBit, 0);
            aStream->read(FSStream::SignedBit, 0);
            aStream->read(FSStream::SignedBit, 0);
        }

        if (_containsFillStyle)
            fillStyle = aStream->read(FSStream::UnsignedBit, numberOfFillBits);
        else
            aStream->read(FSStream::UnsignedBit, 0);

        if (_containsAltFillStyle)
            altFillStyle = aStream->read(FSStream::UnsignedBit, numberOfFillBits);
        else
            aStream->read(FSStream::UnsignedBit, 0);

        if (_containsLineStyle)
            lineStyle = aStream->read(FSStream::UnsignedBit, numberOfLineBits);
        else
            aStream->read(FSStream::UnsignedBit, 0);

        if (_containsStyles)
        {
            aStream->flush();
            
            fillStyleCount = aStream->read(FSStream::UnsignedWord, 8);

            if (aStream->getContext(FSStream::ArrayCountExtended) && fillStyleCount == 0xFF)
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

            if (aStream->getContext(FSStream::ArrayCountExtended) && lineStyleCount == 0xFF)
                lineStyleCount = aStream->read(FSStream::UnsignedWord, 16);
            else
                aStream->read(FSStream::UnsignedWord, 0);

#ifdef _DEBUG
            aStream->startDecoding("array");
#endif
            for (int i=0; i<lineStyleCount; i++)
                lineStyles.push_back(new FSSolidLine(aStream));

#ifdef _DEBUG
            aStream->endDecoding("array");
#endif    
            numberOfFillBits = aStream->read(FSStream::UnsignedBit, 4);
            numberOfLineBits = aStream->read(FSStream::UnsignedBit, 4);
    
            aStream->setContext(FSStream::FillBits, numberOfFillBits);
            aStream->setContext(FSStream::LineBits, numberOfLineBits);
        }
#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }

    bool FSShapeStyle::containsStyles() const
    {
        return (lineStyles.size() > 0) || (fillStyles.size() > 0);
    }

    bool FSShapeStyle::containsLineStyle() const
    {
        return lineStyle != Transform::VALUE_NOT_SET;
    }

    bool FSShapeStyle::containsAltFillStyle() const
    {
        return altFillStyle != Transform::VALUE_NOT_SET;
    }

    bool FSShapeStyle::containsFillStyle() const
    {
        return fillStyle != Transform::VALUE_NOT_SET;
    }

    bool FSShapeStyle::containsMove() const
    {
        return moveX != Transform::VALUE_NOT_SET && moveY != Transform::VALUE_NOT_SET;
    }

    int FSShapeStyle::fieldSize() const
    {
        int values[2] = { moveX, moveY };
        int size = FSStream::FieldSize(values, 2, true);

        return (size == 0) ? 1 : size;
    }
}
