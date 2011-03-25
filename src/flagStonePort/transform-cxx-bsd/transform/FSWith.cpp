/*
 *  FSWith.java
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

#include "FSWith.h"

#include "FSMovie.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSWith::FSWith(FSInputStream* aStream) :
        FSActionObject(With),
        actionsLength(0),
        actions()
    {
        decodeFromStream(aStream);
    }

    FSWith::FSWith(const FSWith& rhs) :
        FSActionObject(rhs),
        actionsLength(0),
        actions(rhs.actions.size())
    {
        int index = 0;
            
        for (FSVector<FSActionObject*>::const_iterator i = rhs.actions.begin(); i != rhs.actions.end(); i++, index++)
            actions[index] = (*i)->clone();
    }

    FSWith::~FSWith()
    {
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }
    }

    const char* FSWith::className() const
    {
        const static char _name[] = "FSWith";
    
        return _name;
    }
    
    FSWith* FSWith::clone() const
    {
        return new FSWith(*this);
    }

    FSWith& FSWith::operator= (const FSWith& rhs)
    {
        if (this != &rhs)
        {
            this->FSActionObject::operator=(rhs);

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
        return *this;
    }

    void FSWith::add(const FSVector<FSActionObject*>& anArray)
    {
        for (FSVector<FSActionObject*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            actions.push_back(*i);
    }

    void FSWith::setActions(const FSVector<FSActionObject*>& anArray)
    {
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }

        actions = anArray;
    }

    int FSWith::lengthInStream(FSOutputStream* aStream)
    { 
        FSActionObject::lengthInStream(aStream);
        
        length += 2;

        actionsLength = 0;
        
        for (FSVector<FSActionObject*>::const_iterator i = actions.begin(); i != actions.end(); ++i)
        {
            actionsLength += (*i)->lengthInStream(aStream);
            actionsLength += ((*i)->getType() > 128) ? 3 : 1;
        }
        length += actionsLength;
        
        return length;
    }
        
    void FSWith::encodeToStream(FSOutputStream* aStream) 
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * Write the type and length attributes manually since the object contains the 
         * actions array - in reality the it is separate from the object.
         */
        aStream->write(getType(), FSStream::UnsignedWord, 8);

        if (type >= 128)
            aStream->write(2, FSStream::UnsignedWord, 16);

        aStream->write(actionsLength, FSStream::UnsignedWord, 16);
            
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); ++i)
#ifdef _DEBUG
            FSMovie::encodeToStream(*i, aStream);
#else
            (*i)->encodeToStream(aStream);
#endif

#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSWith::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);

        int actionsLength = aStream->read(FSStream::UnsignedWord, 16);
        
        /*
         * Update the decoded length of the tag since we are adding the array 
         * of actions to the object and it is separate in the Flash specification.
         */
        
        length += actionsLength;
        
#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        while (actionsLength > 0)
        {
            FSActionObject* anAction = FSMovie::actionFromStream(aStream);
            
            if (anAction != 0)
            {
                actionsLength -= anAction->getLength() + ((anAction->getType() >= 128) ? 3 : 1);
                actions.push_back(anAction);
            }
        }
        
#ifdef _DEBUG
        aStream->endDecoding("array");
        aStream->endDecoding(className());
#endif
    }
}
