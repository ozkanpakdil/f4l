/*
 *  FSPlaceObject2.cpp
 *  Transform SWF
 *
 *  Created by smackay on Wed Feb 19 2003.
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

#include "FSPlaceObject2.h"

#include <string.h>

#include "FSInputStream.h"
#include "FSOutputStream.h"

#include "FSColorTransform.h"
#include "FSClipEvent.h"

using namespace transform;

namespace transform
{
    FSPlaceObject2::FSPlaceObject2(FSInputStream* aStream) :
        FSMovieObject(PlaceObject2),
        place(New),
        layer(0),
        identifier(0),
        transform(),
        colorTransform(),
        ratio(-1.0f),
        depth(0),
        name(""),
        events(),
        encodedEvents(0),
        encodedLength(0)
    {
        decodeFromStream(aStream);
    }

    const char* FSPlaceObject2::className() const
    {
        const static char _name[] = "FSPlaceObject2";

        return _name;
    }

    void FSPlaceObject2::add(const FSVector<FSClipEvent>& anArray)
    {
        if (encodedLength > 0)
        {
            delete [] encodedEvents;
            encodedEvents = 0;
            encodedLength = 0;
        }
        for (FSVector<FSClipEvent>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            events.push_back(FSClipEvent(*i));
    }

    void FSPlaceObject2::setEncodedEvents(byte* bytes, size_t size)
    {
        encodedEvents = bytes;
        encodedLength = size;
           
        events.resize(0);
    }

    int FSPlaceObject2::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);

        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        length += 3;
        length += (place == New || place == Replace) ? 2 : 0;
        length += (containsTransform()) ? transform.lengthInStream(aStream) : 0;
        length += (containsColorTransform(aStream)) ? colorTransform.lengthInStream(aStream) : 0;
        length += (containsRatio()) ? 2 : 0;
        length += (containsName()) ? name.length()+1 : 0;
        length += (containsClippingDepth()) ? 2 : 0;
       
        if (containsClipEvents())
        {
            if (encodedLength > 0)
            {
                length += encodedLength;
            }
            else
            {
                int eventSize = aStream->getContext(FSStream::Version) > 5 ? 4 : 2;
                
                length += 2 + eventSize;

                for (FSVector<FSClipEvent>::iterator i = events.begin(); i != events.end(); ++i)
                    length += (*i).lengthInStream(aStream);
                    
                length += eventSize;
            }
        }
        aStream->setContext(FSStream::ColorContainsAlpha, 0);
        
        return length;
    }
    
    void FSPlaceObject2::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);
        
        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        aStream->write(containsClipEvents() ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(containsClippingDepth() ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(containsName() ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(containsRatio() ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(containsColorTransform(aStream) ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(containsTransform() ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(place, FSStream::UnsignedBit, 2);
        aStream->write(layer, FSStream::UnsignedWord, 16);
        
        if (place == New || place == Replace)
            aStream->write(identifier, FSStream::UnsignedWord, 16);
        if (containsTransform())
            transform.encodeToStream(aStream);
        if (containsColorTransform(aStream))
            colorTransform.encodeToStream(aStream);
        if (containsRatio())
            aStream->write((int)(ratio*65535.0f), FSStream::UnsignedWord, 16);
        if (containsName())
        {
            aStream->write((byte*)name.c_str(), name.length());
            aStream->write(0, FSStream::UnsignedWord, 8);
        }
        if (containsClippingDepth())
            aStream->write(depth+1, FSStream::UnsignedWord, 16);

        if (containsClipEvents())
        {
            if (encodedLength > 0)
            {
                aStream->write(encodedEvents, encodedLength);
            }
            else
            {
                int eventSize = aStream->getContext(FSStream::Version) > 5 ? 32 : 16;
                int eventMask = 0;
                
                aStream->write(0, FSStream::UnsignedWord, 16);

                for (FSVector<FSClipEvent>::iterator i = events.begin(); i != events.end(); ++i)
                    eventMask += (*i).getEvent();
               
                aStream->write(eventMask, FSStream::UnsignedWord, eventSize);

#ifdef _DEBUG
                aStream->startEncoding("array");
#endif
                for (FSVector<FSClipEvent>::iterator i = events.begin(); i != events.end(); ++i)
                    (*i).encodeToStream(aStream);

                aStream->write(0, FSStream::UnsignedWord, eventSize);
     
#ifdef _DEBUG
                aStream->endEncoding("array");
#endif
            }
        }
        aStream->setContext(FSStream::ColorContainsAlpha, 0);
        
        aStream->endEncoding(className());
    }
    
    void FSPlaceObject2::decodeFromStream(FSInputStream* aStream)
    {
        bool containsClipEvents = false;
        bool containsClippingDepth = false;
        bool containsName = false;
        bool containsRatio = false;
        bool containsColorTransform = false;
        bool containsTransform = false;
       
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        containsClipEvents = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        containsClippingDepth = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        containsName = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        containsRatio = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        containsColorTransform = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        containsTransform = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        place = aStream->read(FSStream::UnsignedBit, 2);
        layer = aStream->read(FSStream::UnsignedWord, 16);
        
        if (place == New || place == Replace)
            identifier = aStream->read(FSStream::UnsignedWord, 16);
        else
            aStream->read(FSStream::UnsignedWord, 0);
            
        if (containsTransform)
            transform.decodeFromStream(aStream);
        else
            aStream->read(FSStream::UnsignedWord, 0);

        if (containsColorTransform)
            colorTransform.decodeFromStream(aStream);
        else
            aStream->read(FSStream::UnsignedWord, 0);

        if (containsRatio)
            ratio = aStream->read(FSStream::UnsignedWord, 16) / 65535.0f;
        else
            aStream->read(FSStream::UnsignedWord, 0);

        if (containsName)
        {
            const char* str = aStream->readString();
            name = str;
            delete [] str;
        }
        else
        {
            aStream->read(0);
        }

        if (containsClippingDepth)
            depth = aStream->read(FSStream::UnsignedWord, 16) - 1;
        else
            aStream->read(FSStream::UnsignedWord, 0);

        if (containsClipEvents)
        {
            int eventSize = aStream->getContext(FSStream::Version) > 5 ? 32 : 16;

            aStream->read(FSStream::UnsignedWord, 16);
            aStream->read(FSStream::UnsignedWord, eventSize);

#ifdef _DEBUG
            aStream->startDecoding("array");
#endif
            while (aStream->scan(FSStream::UnsignedWord, eventSize))
            {
                aStream->setCursor(aStream->getCursor()-eventSize);
                events.push_back(FSClipEvent(aStream));
            }
#ifdef _DEBUG
            aStream->endDecoding("array");
#endif
        }
        aStream->setContext(FSStream::ColorContainsAlpha, 0);
        
        aStream->endDecoding(className());
    }

    bool FSPlaceObject2::containsTransform() const
    {
        return transform.isUnityTransform() == false;
    }

    bool FSPlaceObject2::containsColorTransform(FSOutputStream* aStream) const
    {
        return colorTransform.isUnityTransform(aStream) == false;
    }

    bool FSPlaceObject2::containsClipEvents() const
    {
        return events.size() > 0 || encodedLength > 0;
    }

    bool FSPlaceObject2::containsClippingDepth() const
    {
        return depth > 0;
    }

    bool FSPlaceObject2::containsName() const
    {
        return name.length() > 0;
    }

    bool FSPlaceObject2::containsRatio() const
    {
        return ratio >= 0.0;
    }
}