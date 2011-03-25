/*
 *  FSDefineShape.cpp
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

#include "FSDefineShape.h"

#include "FSMovie.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

#include "FSLineStyle.h"
#include "FSFillStyle.h"
#include "FSSolidLine.h"
#include "FSShape.h"

using namespace transform;

namespace transform
{
    FSDefineShape::FSDefineShape(FSInputStream* aStream) :
        FSDefineObject(DefineShape, 0),
        bounds(),
        fillStyles(),
        lineStyles(),
        shape(FSShape())
    {
        decodeFromStream(aStream);
    }
    
    FSDefineShape::FSDefineShape(const FSDefineShape& rhs) :
        FSDefineObject(rhs),
        bounds(rhs.bounds),
        fillStyles(rhs.fillStyles.size()),
        lineStyles(rhs.lineStyles.size()),
        shape(rhs.shape)
    {
        int index = 0;
            
        for (FSVector<FSFillStyle*>::const_iterator i = rhs.fillStyles.begin(); i != rhs.fillStyles.end(); i++, index++)
            fillStyles[index] = (*i)->clone();

        index = 0;
        
        for (FSVector<FSLineStyle*>::const_iterator i = rhs.lineStyles.begin(); i != rhs.lineStyles.end(); i++, index++)
            lineStyles[index] = (*i)->clone();
    }

    FSDefineShape::~FSDefineShape()
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
    
    const char* FSDefineShape::className() const
    {
        const static char _name[] = "FSDefineShape";

        return _name;
    }

    FSDefineShape& FSDefineShape::operator= (const FSDefineShape& rhs)
    {
        if (this != &rhs)
        {
            this->FSDefineObject::operator=(rhs);

            bounds = rhs.bounds;

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

            shape = rhs.shape;
        }
        return *this;
    }

    void FSDefineShape::add(const FSVector<FSFillStyle*>& anArray)
    {
        for (FSVector<FSFillStyle*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            fillStyles.push_back(*i);
    }

    void FSDefineShape::add(const FSVector<FSLineStyle*>& anArray)
    {
        for (FSVector<FSLineStyle*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            lineStyles.push_back(*i);
    }
    
    int FSDefineShape::lengthInStream(FSOutputStream* aStream)
    {
        int numberOfFillBits = fillStyles.size() > 0 ? FSStream::FieldSize((int)(fillStyles.size())): 0;
        int numberOfLineBits = lineStyles.size() > 0 ? FSStream::FieldSize((int)(lineStyles.size())): 0;
        
        FSDefineObject::lengthInStream(aStream);
    
        length += bounds.lengthInStream(aStream);
        length += 1;

        for (FSVector<FSFillStyle*>::const_iterator i = fillStyles.begin(); i != fillStyles.end(); ++i)
            length += (*i)->lengthInStream(aStream);
    
        length += 1;

        for (FSVector<FSLineStyle*>::const_iterator i = lineStyles.begin(); i != lineStyles.end(); ++i)
            length += (*i)->lengthInStream(aStream);
    
        aStream->setContext(FSStream::FillBits, numberOfFillBits);
        aStream->setContext(FSStream::LineBits, numberOfLineBits);
    
        length += shape.lengthInStream(aStream);
    
        aStream->setContext(FSStream::FillBits, 0);
        aStream->setContext(FSStream::LineBits, 0);

        return length;
    }
    
    void FSDefineShape::encodeToStream(FSOutputStream* aStream)
    {
        int numberOfFillBits = fillStyles.size() > 0 ? FSStream::FieldSize((int)(fillStyles.size())): 0;
        int numberOfLineBits = lineStyles.size() > 0 ? FSStream::FieldSize((int)(lineStyles.size())): 0;

        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);

        bounds.encodeToStream(aStream);
    
        aStream->write((int)(fillStyles.size()), FSStream::UnsignedWord, 8);
    
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSFillStyle*>::iterator i = fillStyles.begin(); i != fillStyles.end(); ++i)
            (*i)->encodeToStream(aStream);
    
#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
        aStream->write((int)(lineStyles.size()), FSStream::UnsignedWord, 8);
                
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

        aStream->setContext(FSStream::FillStyles, (int)(fillStyles.size()));
        aStream->setContext(FSStream::LineStyles, (int)(lineStyles.size()));

        shape.encodeToStream(aStream);

        aStream->setContext(FSStream::FillBits, 0);
        aStream->setContext(FSStream::LineBits, 0);

        aStream->setContext(FSStream::FillStyles, 0);
        aStream->setContext(FSStream::LineStyles, 0);

        aStream->endEncoding(className());
    }
    
    void FSDefineShape::decodeFromStream(FSInputStream* aStream)
    {
        int fillStyleCount = 0;
        int lineStyleCount = 0;
        
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);

        bounds.decodeFromStream(aStream);
        fillStyleCount = aStream->read(FSStream::UnsignedWord, 8);
            
#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=0; i<fillStyleCount; i++)
            fillStyles.push_back(FSMovie::fillStyleFromStream(aStream));
        
#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        lineStyleCount = aStream->read(FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=0; i<lineStyleCount; i++)
            lineStyles.push_back(new FSSolidLine(aStream));

#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        shape.decodeFromStream(aStream);

        aStream->endDecoding(className());
    }
}