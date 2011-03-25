/*
 *  FSNewFunction2.cpp
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

#include "FSNewFunction2.h"

#include "FSMovie.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSNewFunction2::FSNewFunction2(FSInputStream* aStream) :
        FSActionObject(NewFunction2),
		name(), 
		registerCount(0), 
		optimizations(0), 
		arguments(), 
		actions(),
		actionsLength(0)
	{
        decodeFromStream(aStream);
	}

   FSNewFunction2:: FSNewFunction2(const FSNewFunction2& rhs) :
        FSActionObject(rhs),
        name(rhs.name),
		registerCount(rhs.registerCount), 
		optimizations(rhs.optimizations),
        arguments(rhs.arguments),
        actions(rhs.actions.size()),
		actionsLength(rhs.actionsLength)
    {
        int index = 0;

        for (FSVector<FSActionObject*>::const_iterator i = rhs.actions.begin(); i != rhs.actions.end(); i++, index++)
            actions[index] = (*i)->clone();
    }

    FSNewFunction2::~FSNewFunction2()
    {
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }
    }

    const char* FSNewFunction2::className() const
    {
        const static char _name[] = "FSNewFunction2";

        return _name;
    }

    FSNewFunction2& FSNewFunction2::operator= (const FSNewFunction2& rhs)
    {
        if (this != &rhs)
        {
            this->FSActionObject::operator=(rhs);

            name = rhs.name;
			registerCount = rhs.registerCount;
			optimizations = rhs.optimizations;
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

			actionsLength = rhs.actionsLength;
        }
        return *this;
    }

    void FSNewFunction2::add(const FSVector<FSRegisterVariable>& anArray)
    {
        for (FSVector<FSRegisterVariable>::const_iterator i = anArray.begin(); i != anArray.end(); i++)
            arguments.push_back(*i);
    }

    void FSNewFunction2::add(const FSVector<FSActionObject*>& anArray)
    {
        for (FSVector<FSActionObject*>::const_iterator i = anArray.begin(); i != anArray.end(); i++)
            actions.push_back(*i);
    }

    void FSNewFunction2::setActions(const FSVector<FSActionObject*>& anArray) 
	{
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }
        actions = anArray;
    }
	
	int FSNewFunction2::lengthInStream(FSOutputStream* aStream)
    { 
        FSActionObject::lengthInStream(aStream);
        
        length += name.length() + 1;
        length += 5;
        
        if (arguments.size() > 0)
        {
            for (FSVector<FSRegisterVariable>::iterator i = arguments.begin(); i != arguments.end(); i++)
                length += (*i).lengthInStream(aStream);
        }
        
        length += 2;

        actionsLength = 0;

        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
		{
            actionsLength += (*i)->lengthInStream(aStream);
            actionsLength += ((*i)->getType() > 128) ? 3 : 1;
		}
		length += actionsLength;
        
        return length;
    }
    	
	void FSNewFunction2::encodeToStream(FSOutputStream* aStream) 
    {
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
            aStream->write(length-actionsLength, FSStream::UnsignedWord, 16);

        aStream->write((byte*)name.c_str(), name.length());
        aStream->write(0, FSStream::UnsignedWord, 8);

        aStream->write(arguments.size(), FSStream::UnsignedWord, 16);
        aStream->write(registerCount, FSStream::UnsignedWord, 8);
        aStream->write(optimizations, FSStream::UnsignedBit, 16);

#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSRegisterVariable>::iterator i = arguments.begin(); i != arguments.end(); i++)
			(*i).encodeToStream(aStream);
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
    
	void FSNewFunction2::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);

        name = aStream->readString();
        
        int argumentCount = aStream->read(FSStream::UnsignedWord, 16);
        registerCount = aStream->read(FSStream::UnsignedWord, 8);
        optimizations = aStream->read(FSStream::UnsignedBit, 16);
        
#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=argumentCount; i>0; i--)
            arguments.push_back(FSRegisterVariable(aStream));

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
