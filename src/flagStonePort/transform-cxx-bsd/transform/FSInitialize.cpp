/*
 *  FSInitialize.cpp
 *  Transform SWF
 *
 *  Created by smackay on Fri Apr 30 2004.
 *  Copyright (c) 2001-2004 Flagstone Software Ltd. All rights reserved.
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

#include "FSInitialize.h"

#include "FSMovie.h"
#include "FSActionObject.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSInitialize::FSInitialize(FSInputStream* aStream) :
        FSMovieObject(Initialize),
		identifier(0),
        actions()
	{
		decodeFromStream(aStream);
	}
	
    FSInitialize::FSInitialize(const FSInitialize& rhs) :
        FSMovieObject(rhs),
		identifier(rhs.identifier),
        actions(rhs.actions.size())
    {
        int index = 0;
            
        for (FSVector<FSActionObject*>::const_iterator i = rhs.actions.begin(); i != rhs.actions.end(); i++, index++)
            actions[index] = (*i)->clone();
    }

    FSInitialize::~FSInitialize()
    {
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }
    }

    const char* FSInitialize::className() const
    {
        const static char _name[] = "FSInitialize";
        
        return _name;
    }

    FSInitialize* FSInitialize::clone() const
    {
        return new FSInitialize(*this);
    }

    FSInitialize& FSInitialize::operator= (const FSInitialize& rhs)
    {
        if (this != &rhs)
        {
            this->FSMovieObject::operator=(rhs);

			identifier = rhs.identifier;

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

    void FSInitialize::add(const FSVector<FSActionObject*>& anArray)
    {
        for (FSVector<FSActionObject*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            actions.push_back(*i);
    }

    void FSInitialize::setActions(const FSVector<FSActionObject*>& anArray)
	{
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }

        actions = anArray;
	}

	int FSInitialize::lengthInStream(FSOutputStream* aStream)
	{
		FSMovieObject::lengthInStream(aStream);

		length += 2;

        for (FSVector<FSActionObject*>::const_iterator i = actions.begin(); i != actions.end(); ++i)
		{
            length += (*i)->lengthInStream(aStream);
            length += ((*i)->getType() > 128) ? 3 : 1;
		}

        length += 1;

		return length;
	}
	
	void FSInitialize::encodeToStream(FSOutputStream* aStream)
	{
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

		aStream->write(identifier, FSStream::UnsignedWord, 16);

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
        aStream->endEncoding(className());
	}
	
	void FSInitialize::decodeFromStream(FSInputStream* aStream)
	{
        aStream->startDecoding(className());
		FSMovieObject::decodeFromStream(aStream);

		identifier = aStream->read(FSStream::UnsignedWord, 16);

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
