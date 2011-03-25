/*
 *  FSShape.cpp
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

#include "FSShape.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSMovieListener.h"

#include "FSShapeStyle.h"
#include "FSLine.h"
#include "FSCurve.h"

#include "FSShapeObject.h"

using namespace transform;

namespace transform
{
    FSShape::FSShape(FSInputStream* aStream) : objects()
    {
        decodeFromStream(aStream);
    }

    FSShape::FSShape(const FSShape& rhs) : objects(rhs.objects.size())
    {
        int index=0;
        
        for (FSVector<FSShapeObject*>::const_iterator i = rhs.objects.begin(); i != rhs.objects.end(); i++, index++)
            objects[index] = (*i)->clone();
    }

    FSShape::~FSShape()
    {
        for (FSVector<FSShapeObject*>::iterator i = objects.begin(); i != objects.end(); i++)
        {
            delete *i;
            *i = 0;
        }
    }
    
    const char* FSShape::className() const
    {
        const static char _name[] = "FSShape";

        return _name;
    }

    FSShape& FSShape::operator= (const FSShape& rhs)
    {
        if (this != &rhs)
        {
            for (FSVector<FSShapeObject*>::iterator i = objects.begin(); i != objects.end(); i++)
            {
                delete *i;
                *i = 0;
            }

            objects = FSVector<FSShapeObject*>(rhs.objects.size());

            int index = 0;

            for (FSVector<FSShapeObject*>::const_iterator i = rhs.objects.begin(); i != rhs.objects.end(); i++, index++)
                objects[index] = (*i)->clone();
        }
        return *this;
    }

    void FSShape::add(const FSVector<FSShapeObject*>& anArray)
    {
        for (FSVector<FSShapeObject*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            objects.push_back(*i);
    }

    int FSShape::lengthInStream(FSOutputStream* aStream)
    {
        int numberOfBits = 8; // 4-bits each for number of line and fill bits.
        int currentLocation = aStream->getCursor();
        
        aStream->setCursor(currentLocation+numberOfBits);

        for (FSVector<FSShapeObject*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
            numberOfBits += (*i)->lengthInStream(aStream);
    
        numberOfBits += 6;
        numberOfBits += (numberOfBits % 8 > 0) ? 8-(numberOfBits % 8) : 0;
    
        aStream->setCursor(currentLocation);

        return numberOfBits>>3;
    }

    void FSShape::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        // Number of line and fill bits is set by parent.
        aStream->write(aStream->getContext(FSStream::FillBits), FSStream::UnsignedBit, 4);
        aStream->write(aStream->getContext(FSStream::LineBits), FSStream::UnsignedBit, 4);

#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSShapeObject*>::iterator i = objects.begin(); i != objects.end(); ++i)
            (*i)->encodeToStream(aStream);

        aStream->write(0, FSStream::UnsignedBit, 6);

        aStream->flush();

#ifdef _DEBUG
        aStream->endEncoding("array");
        aStream->endEncoding(className());
#endif
    }
    
    void FSShape::decodeFromStream(FSInputStream* aStream)
    {
        int fillBits = 0;
        int lineBits = 0;

        FSShapeObject* aShapeRecord = 0;
        
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        fillBits = aStream->read(FSStream::UnsignedBit, 4);
        lineBits = aStream->read(FSStream::UnsignedBit, 4);

        aStream->setContext(FSStream::FillBits, fillBits);
        aStream->setContext(FSStream::LineBits, lineBits);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        while ((aShapeRecord = shapeRecordFromStream(aStream)) != 0)
            objects.push_back(aShapeRecord);

        aStream->flush();

#ifdef _DEBUG
        aStream->endDecoding("array");
        aStream->endDecoding(className());
#endif
    }
    
    FSShapeObject* FSShape::shapeRecordFromStream(FSInputStream* aStream)
    {
        FSShapeObject* anObject = 0;
        int shapeType = aStream->scan(FSStream::UnsignedBit, 6);
        FSMovieListener* listener = aStream->getListener();

        aStream->setCursor(aStream->getCursor()-6);

        if ((shapeType & 0x20) > 0)
        {
            if ((shapeType & 0x10) > 0)
                anObject = new FSLine(aStream);
            else
                anObject = new FSCurve(aStream);
        }
        else
        {
            if (shapeType != 0)
                anObject = new FSShapeStyle(aStream);
            else
                aStream->read(FSStream::UnsignedBit, 6);
        } 
        if (shapeType != 0 && anObject == 0)
        {
            const char* message = "Cannot allocate memory to decode a shape object.";

            if (listener != 0)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Decode, FSMovieEvent::Error, 0, 0, "", message));            
            else
                throw FSAllocationException(message);
        }
        return anObject;
    }    
}
