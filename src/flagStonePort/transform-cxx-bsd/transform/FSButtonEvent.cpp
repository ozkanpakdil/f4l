/*
 *  FSButtonEvent.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 24 2003.
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

#include "FSButtonEvent.h"

#include "FSMovie.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

#include "FSActionObject.h"

using namespace transform;

namespace transform
{
    int FSButtonEvent::codeForKey(char c)
    {
        return c << 9;
    }
    
    FSButtonEvent::FSButtonEvent(FSInputStream* aStream) 
        : event(0)
        , actions()
        , encodedActions(0)
        , encodedLength(0)
    {
        decodeFromStream(aStream);
    }
    
    FSButtonEvent::FSButtonEvent(const FSButtonEvent& rhs) 
        : event(rhs.event)
        , actions(rhs.actions.size())
        , encodedActions(0)
        , encodedLength(0)
    {
        int index = 0;
        
        for (FSVector<FSActionObject*>::const_iterator i = rhs.actions.begin(); i != rhs.actions.end(); i++, index++)
            actions[index] = (*i)->clone();
    }

    FSButtonEvent::~FSButtonEvent()
    {
        if (encodedLength > 0)
        {
            delete [] encodedActions;
            encodedActions = 0;
            encodedLength = 0;
        }

        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }
    }
    
    const char* FSButtonEvent::className() const
    {
        const static char _name[] = "FSButtonEvent";

        return _name;
    }

    FSButtonEvent& FSButtonEvent::operator= (const FSButtonEvent& rhs)
    {
        if (this != &rhs)
        {
            event = rhs.event;
            
            if (encodedLength > 0)
            {
                delete [] encodedActions;
                encodedLength = rhs.encodedLength;
                encodedActions = new byte[encodedLength];
                memcpy(encodedActions, rhs.encodedActions, encodedLength*sizeof(byte));
            }
            else
            {
                for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
                {
                    delete *i;
                    *i = 0;
                }

                actions = FSVector<FSActionObject*>(rhs.actions.size());

                int index = 0;
                
                for (FSVector<FSActionObject*>::const_iterator i = rhs.actions.begin(); i != rhs.actions.end(); i++, index++)
                    actions[index] = (*i)->clone();
            }
        }
        return *this;
    }

    void FSButtonEvent::add(const FSVector<FSActionObject*>& anArray)
    {
        if (encodedLength > 0)
        {
            delete [] encodedActions;
            encodedActions = NULL;
            encodedLength = 0;
        }

        for (FSVector<FSActionObject*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            actions.push_back(*i);
    }

    void FSButtonEvent::setActions(const FSVector<FSActionObject*>& anArray)
    {
        if (encodedLength > 0)
        {
            delete [] encodedActions;
            encodedActions = NULL;
            encodedLength = 0;
        }

        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }

        actions = anArray;
    }

    void FSButtonEvent::setEncodedActions(byte* bytes, size_t size)
    {
        delete [] encodedActions;
        encodedActions = bytes;
        encodedLength = size;
    }

    int FSButtonEvent::lengthInStream(FSOutputStream* aStream)
    {
        int length = 2;

        if (encodedLength > 0)
        {
            length += encodedLength;
        }
        else
        {
            for (FSVector<FSActionObject*>::const_iterator i = actions.begin(); i != actions.end(); ++i)
            {
                length += (*i)->lengthInStream(aStream);
                length += ((*i)->getType() > 128) ? 3 : 1;
            }
        }
        length += 1;
        
        return length;
    }
    
    void FSButtonEvent::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        aStream->write(event, FSStream::UnsignedWord, 16);

        if (encodedLength > 0)
        {
            aStream->write(encodedActions, encodedLength);
        }
        else
        {
#ifdef _DEBUG
            aStream->startEncoding("array");
#endif
            for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); ++i)
                (*i)->encodeToStream(aStream);

            aStream->write(0, FSStream::UnsignedWord, 8);

#ifdef _DEBUG
            aStream->endEncoding("array");
#endif
        }
#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSButtonEvent::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        event = aStream->read(FSStream::UnsignedWord, 16);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        while (FSActionObject* anAction = FSMovie::actionFromStream(aStream))
            actions.push_back(anAction);

#ifdef _DEBUG
        aStream->endDecoding("array");
        aStream->endDecoding(className());
#endif
    }
}
