/*
 *  FSDoAction.cpp
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

#include "FSDoAction.h"

#include "FSMovie.h"
#include "FSActionObject.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSDoAction::FSDoAction(FSInputStream* aStream) :
        FSMovieObject(DoAction),
        actions(),
        encodedActions(0),
        encodedLength(0)
    {
        decodeFromStream(aStream);
    }
    
    FSDoAction::FSDoAction(byte* bytes, size_t size) :
        FSMovieObject(DoAction),
        actions(),
        encodedActions(0),
        encodedLength(0)
    {
        setEncodedActions(bytes, size);
    }
    
    FSDoAction::FSDoAction(const FSDoAction& rhs) :
        FSMovieObject(rhs),
        actions(rhs.actions.size()),
        encodedActions(0),
        encodedLength(0)
    {
        if (rhs.encodedLength > 0)
        {
            delete [] encodedActions;
            encodedLength = rhs.encodedLength;
            encodedActions = new byte[encodedLength];
            memcpy(encodedActions, rhs.encodedActions, encodedLength*sizeof(byte));
        }
        else
        {
            int index = 0;
                
            for (FSVector<FSActionObject*>::const_iterator i = rhs.actions.begin(); i != rhs.actions.end(); i++, index++)
                actions[index] = (*i)->clone();
        }
    }

    FSDoAction::~FSDoAction()
    {
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }

        if (encodedLength > 0)
        {
            delete [] encodedActions;
            encodedLength = 0;
        }
    }

    const char* FSDoAction::className() const
    {
        const static char _name[] = "FSDoAction";
        
        return _name;
    }

    FSDoAction* FSDoAction::clone() const
    {
        return new FSDoAction(*this);
    }

    FSDoAction& FSDoAction::operator= (const FSDoAction& rhs)
    {
        if (this != &rhs)
        {
            this->FSMovieObject::operator=(rhs);

            if (encodedLength > 0)
            {
                delete [] encodedActions;

                encodedActions = new byte[encodedLength];

                if (encodedLength > 0 && encodedActions == 0)
                    throw FSAllocationException("Cannot allocate memory to copy FSUnknownObject.");

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

    void FSDoAction::add(const FSVector<FSActionObject*>& anArray)
    {
        if (encodedLength > 0)
        {
            delete [] encodedActions;
            encodedLength = 0;
        }

        for (FSVector<FSActionObject*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            actions.push_back(*i);
    }

    void FSDoAction::setActions(const FSVector<FSActionObject*>& anArray)
    {
        if (encodedLength > 0)
        {
            delete [] encodedActions;
            encodedLength = 0;
        }

        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }

        actions = anArray;
    }

    void FSDoAction::setEncodedActions(byte* bytes, size_t size)
    {
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }

        actions.resize(0);

        delete [] encodedActions;

        encodedActions = bytes;
        encodedLength = size;
    }

    int FSDoAction::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);

        if (encodedLength > 0)
        {
            length = encodedLength;
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
    
    void FSDoAction::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        if (encodedLength > 0)
        {
            aStream->write(encodedActions, encodedLength);
            aStream->write(0, FSStream::UnsignedWord, 8);
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
#endif
        }
        aStream->endEncoding(className());
    }
    
    void FSDoAction::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        while (FSActionObject* anAction = FSMovie::actionFromStream(aStream))
            actions.push_back(anAction);

#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        aStream->endDecoding(className());
    }
}
