/*
 *  FSClipEvent.cpp
 *  Transform SWF
 *
 *  Created by smackay on Web Feb 19 2003.
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

#include "FSClipEvent.h"

#include "FSMovie.h"
#include "FSActionObject.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSClipEvent::FSClipEvent(FSInputStream* aStream) :
        event(0),
        keyCode(0),
        actions()
    {
        decodeFromStream(aStream);
    }

    FSClipEvent::FSClipEvent(const FSClipEvent& rhs) :
        event(rhs.event),
        keyCode(rhs.keyCode),
        actions(rhs.actions.size())
    {
        int index = 0;
            
        for (FSVector<FSActionObject*>::const_iterator i = rhs.actions.begin(); i != rhs.actions.end(); i++, index++)
            actions[index] = (*i)->clone();
    }

    FSClipEvent::~FSClipEvent()
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
    
    const char* FSClipEvent::className() const
    {
        const static char _name[] = "FSClipEvent";

        return _name;
    }

    FSClipEvent& FSClipEvent::operator= (const FSClipEvent& rhs)
    {
        if (this != &rhs)
        {
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

    void FSClipEvent::add(const FSVector<FSActionObject*>& anArray)
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

    void FSClipEvent::setActions(const FSVector<FSActionObject*>& anArray)
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

    void FSClipEvent::setEncodedActions(byte* bytes, size_t size)
    {
        delete [] encodedActions;
        encodedActions = bytes;
        encodedLength = size;
    }

    int FSClipEvent::lengthInStream(FSOutputStream* aStream)
    {
        int length = 4 + ((aStream->getContext(FSStream::Version) > 5) ? 4 : 2);
    
        if (aStream->getContext(FSStream::Version) > 5)
            length += ((event & KeyPress) != 0) ? 1 : 0;

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
    
    void FSClipEvent::encodeToStream(FSOutputStream* aStream)
    {
        int eventSize = (aStream->getContext(FSStream::Version) > 5) ? 32 : 16;
        
        int actionsLength = 1;

        if (encodedLength > 0)
        {
            actionsLength += encodedLength;
        }
        else
        {
            for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); ++i)
            {
                actionsLength += (*i)->lengthInStream(aStream);
                actionsLength += ((*i)->getType() > 128) ? 3 : 1;
            }
        }

        if (aStream->getContext(FSStream::Version) > 5)
            actionsLength += ((event & KeyPress) != 0) ? 1 : 0;
            
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif

        aStream->write(event, FSStream::UnsignedWord, eventSize);
        aStream->write(actionsLength, FSStream::UnsignedWord, 32);
            
        if ((aStream->getContext(FSStream::Version) > 5) && ((event & KeyPress) != 0))
            aStream->write(keyCode, FSStream::UnsignedWord, 8);            

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
#ifdef _DEBUG
                FSMovie::encodeToStream(*i, aStream);
#else
                (*i)->encodeToStream(aStream);
#endif
            aStream->write(0, FSStream::UnsignedWord, 8);
        
#ifdef _DEBUG
            aStream->endEncoding("array");
            aStream->endEncoding(className());
#endif
        }
    }
    
    void FSClipEvent::decodeFromStream(FSInputStream* aStream)
    {
        int eventSize = (aStream->getContext(FSStream::Version) > 5) ? 32 : 16;

#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        event = aStream->read(FSStream::UnsignedWord, eventSize);
        aStream->read(FSStream::UnsignedWord, 32);

        if ((aStream->getContext(FSStream::Version) > 5) && ((event & KeyPress) != 0))
            keyCode = aStream->read(FSStream::UnsignedWord, 8);
        else
            aStream->read(FSStream::UnsignedWord, 0);

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
