/*
 *  FSNewFunction.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 10 2003.
 *  Copyright (c) 2001-2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file is part of the Transform SWF library. You may not use this file except in
 *  compliance with the terms of the license (the 'License') that accompanied this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an 
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone 
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY 
 *  RIGHTS. Please see the License for the specific language governing rights and limitations 
 *  under the License.
 */

#include "FSNewFunction.h"

#include "FSMovie.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSNewFunction::FSNewFunction(FSInputStream* aStream) :
        FSActionObject(NewFunction),
        name(),
        arguments(),
        actions()
    {
        decodeFromStream(aStream);
    }

   FSNewFunction:: FSNewFunction(const FSNewFunction& rhs) :
        FSActionObject(rhs),
        name(rhs.name),
        arguments(rhs.arguments),
        actions(rhs.actions.size())
    {
        int index = 0;

        for (FSVector<FSActionObject*>::const_iterator i = rhs.actions.begin(); i != rhs.actions.end(); i++, index++)
            actions[index] = (*i)->clone();
    }

    FSNewFunction::~FSNewFunction()
    {
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }
    }

    const char* FSNewFunction::className() const
    {
        const static char _name[] = "FSNewFunction";

        return _name;
    }

    FSNewFunction& FSNewFunction::operator= (const FSNewFunction& rhs)
    {
        if (this != &rhs)
        {
            this->FSActionObject::operator=(rhs);

            name = rhs.name;
            arguments = rhs.arguments;

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

    void FSNewFunction::add(const FSVector<FSActionObject*>& anArray)
    {
        for (FSVector<FSActionObject*>::const_iterator i = anArray.begin(); i != anArray.end(); i++)
            actions.push_back(*i);
    }

    void FSNewFunction::setActions(const FSVector<FSActionObject*>& anArray) 
    {
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }
        actions = anArray;
    }
    
    int FSNewFunction::lengthInStream(FSOutputStream* aStream)
    { 
        FSActionObject::lengthInStream(aStream);
        
        length += name.length() + 1;
        length += 2;
        
        if (arguments.size() > 0)
        {
            for (FSVector<FSString>::const_iterator i = arguments.begin(); i != arguments.end(); i++)
                length += (*i).length() + 1;
        }
        
        length += 2;

        for (FSVector<FSActionObject*>::const_iterator i = actions.begin(); i != actions.end(); i++)
        {
            length += (*i)->lengthInStream(aStream);
            length += ((*i)->getType() > 128) ? 3 : 1;
        }
        
        return length;
    }
        
    void FSNewFunction::encodeToStream(FSOutputStream* aStream) 
    {
        int actionsLength = 0;

        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
            actionsLength += (*i)->lengthInStream(aStream);

#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * Write the type and length attributes manually since the object contains the 
         * actions array - in reality the it is separate from the object. Consequently
         * the length must be adjusted accordingly.
         */
        aStream->write(getType(), FSStream::UnsignedWord, 8);

        if (type >= 128)
            aStream->write(lengthInStream(aStream)-3-actionsLength, FSStream::UnsignedWord, 16);

        aStream->write((byte*)name.c_str(), name.length());
        aStream->write(0, FSStream::UnsignedWord, 8);

        aStream->write(arguments.size(), FSStream::UnsignedWord, 16);

#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSString>::iterator i = arguments.begin(); i != arguments.end(); i++)
        {
            aStream->write((byte*)(*i).c_str(), (*i).length());
            aStream->write(0, FSStream::UnsignedWord, 8);
        }
#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
        
        aStream->write(actionsLength, FSStream::UnsignedWord, 16);

#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
            (*i)->encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding("array");
        aStream->endEncoding(className());
#endif
    }
    
    void FSNewFunction::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);

        name = aStream->readString();
        
        int argumentCount = aStream->read(FSStream::UnsignedWord, 16);
        
#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=argumentCount; i>0; i--)
            arguments.push_back(aStream->readString());

#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
            
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
