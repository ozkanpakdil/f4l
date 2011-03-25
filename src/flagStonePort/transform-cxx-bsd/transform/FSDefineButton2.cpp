/*
 *  FSDefineButton2.cpp
 *  Transform SWF
 *
 *  Created by smackay on Tue Feb 25 2003.
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

#include "FSDefineButton2.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSDefineButton2::FSDefineButton2(FSInputStream* aStream) 
        : FSDefineObject(DefineButton2, 0)
        , buttonType(Push)
        , buttonRecords()
        , buttonEvents()
        , encodedEvents(0)
        , encodedLength(0)
    {
        decodeFromStream(aStream);
    }

    const char* FSDefineButton2::className() const
    {
        const static char _name[] = "FSDefineButton2";

        return _name;
    }

    void FSDefineButton2::add(const FSVector<FSButton>& anArray)
    {
        for (FSVector<FSButton>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            buttonRecords.push_back(*i);
    }

    void FSDefineButton2::add(const FSButtonEvent& aButtonEvent) 
    { 
        if (encodedLength > 0)
        {
            delete [] encodedEvents;
            encodedEvents = 0;
            encodedLength = 0;
        }
        buttonEvents.push_back(aButtonEvent); 
    }

    void FSDefineButton2::add(const FSVector<FSButtonEvent>& anArray)
    {
        if (encodedLength > 0)
        {
            delete [] encodedEvents;
            encodedEvents = 0;
            encodedLength = 0;
        }
        for (FSVector<FSButtonEvent>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            buttonEvents.push_back(*i);
    }

    void FSDefineButton2::setEncodedEvents(byte* bytes, size_t size)
    {
        encodedEvents = bytes;
        encodedLength = size;
           
        buttonEvents.resize(0);
    }

    int FSDefineButton2::lengthInStream(FSOutputStream* aStream)
    {    
        FSDefineObject::lengthInStream(aStream);
    
        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        length += 3;

        for (FSVector<FSButton>::iterator i = buttonRecords.begin(); i != buttonRecords.end(); ++i)
            length += (*i).lengthInStream(aStream);

        length += 1;

        if (encodedLength > 0)
        {
            length += encodedLength;
        }
        else
        {
            for (FSVector<FSButtonEvent>::iterator i = buttonEvents.begin(); i != buttonEvents.end(); ++i)
            {
                length += 2;
                length += (*i).lengthInStream(aStream);
            }
        }
        aStream->setContext(FSStream::ColorContainsAlpha, 0);
        
        return length;
    }
    
    void FSDefineButton2::encodeToStream(FSOutputStream* aStream)
    {
        int offsetStart = 0;
        int offsetEnd = 0;
        int currentCursor = 0;
        
        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);
        
        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        aStream->write(buttonType, FSStream::UnsignedWord, 8);
        
        offsetStart = aStream->getCursor();
        aStream->write(0, FSStream::UnsignedWord, 16);
    
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSButton>::iterator i = buttonRecords.begin(); i != buttonRecords.end(); ++i)
            (*i).encodeToStream(aStream);
    
        aStream->write(0, FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
        // Write actions offset
        
        currentCursor = aStream->getCursor();
        offsetEnd = (currentCursor - offsetStart) >> 3;
        aStream->setCursor(offsetStart);
        aStream->write(offsetEnd, FSStream::UnsignedWord, 16);
        aStream->setCursor(currentCursor);
    
        if (encodedLength > 0)
        {
            aStream->write(encodedEvents, encodedLength);
        }
        else
        {
#ifdef _DEBUG
            aStream->startEncoding("array");
#endif
            for (FSVector<FSButtonEvent>::iterator i = buttonEvents.begin(); i != buttonEvents.end(); ++i)
            {
                FSButtonEvent& anEvent = *i;

                offsetStart = aStream->getCursor();
                aStream->write(anEvent.lengthInStream(aStream) + 2, FSStream::UnsignedWord, 16);
                anEvent.encodeToStream(aStream);
            }
#ifdef _DEBUG
            aStream->endEncoding("array");
#endif
        }
        // Write offset of zero for last Action Condition
        
        currentCursor = aStream->getCursor();
        aStream->setCursor(offsetStart);
        aStream->write(0, FSStream::UnsignedWord, 16);
        aStream->setCursor(currentCursor);

        aStream->setContext(FSStream::ColorContainsAlpha, 0);
        
        aStream->endEncoding(className());
    }
    
    void FSDefineButton2::decodeFromStream(FSInputStream* aStream)
    {
        int actionsOffset = 0;
        
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);

        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        buttonType = aStream->read(FSStream::UnsignedWord, 8);
        actionsOffset = aStream->read(FSStream::UnsignedWord, 16);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        while (aStream->scan(FSStream::UnsignedWord, 8) != 0)
        {
            aStream->setCursor(aStream->getCursor()-8);
            buttonRecords.push_back(FSButton(aStream));
        }
        
#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        if (actionsOffset != 0)
        {
#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
            do {
                actionsOffset = aStream->read(FSStream::UnsignedWord, 16);
                buttonEvents.push_back(FSButtonEvent(aStream));
            } while (actionsOffset != 0);

#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        }
        aStream->setContext(FSStream::ColorContainsAlpha, 0);
        
        aStream->endDecoding(className());
    }
}
