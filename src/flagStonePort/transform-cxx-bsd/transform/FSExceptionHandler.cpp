/*
 *  FSExceptionHandler.cpp
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

#include "FSExceptionHandler.h"

#include "FSMovie.h"
#include "FSActionObject.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSExceptionHandler::FSExceptionHandler(FSInputStream* aStream) :
        FSActionObject(ExceptionHandler),
		registerNumber(0),
		variable(),
 		tryLength(0),
		catchLength(0),
		finalLength(0),
        tryActions(),
		catchActions(),
		finalActions()
	{
		decodeFromStream(aStream);
	}
	
    FSExceptionHandler::FSExceptionHandler(const FSExceptionHandler& rhs) :
        FSActionObject(rhs),
		registerNumber(rhs.registerNumber),
		variable(rhs.variable),
		tryLength(rhs.tryLength),
		catchLength(rhs.catchLength),
		finalLength(rhs.finalLength),
        tryActions(rhs.tryActions.size()),
		catchActions(rhs.tryActions.size()),
		finalActions(rhs.tryActions.size())
    {
        int index = 0;
            
        for (FSVector<FSActionObject*>::const_iterator i = rhs.tryActions.begin(); i != rhs.tryActions.end(); i++, index++)
            tryActions[index] = (*i)->clone();

		index = 0;

	    for (FSVector<FSActionObject*>::const_iterator i = rhs.catchActions.begin(); i != rhs.catchActions.end(); i++, index++)
            catchActions[index] = (*i)->clone();

		index = 0;

		for (FSVector<FSActionObject*>::const_iterator i = rhs.finalActions.begin(); i != rhs.finalActions.end(); i++, index++)
            finalActions[index] = (*i)->clone();

	}

    FSExceptionHandler::~FSExceptionHandler()
    {
        for (FSVector<FSActionObject*>::iterator i = tryActions.begin(); i != tryActions.end(); i++)
        {
            delete *i;
            *i = 0;
        }

	    for (FSVector<FSActionObject*>::iterator i = catchActions.begin(); i != catchActions.end(); i++)
        {
            delete *i;
            *i = 0;
        }

	    for (FSVector<FSActionObject*>::iterator i = finalActions.begin(); i != finalActions.end(); i++)
        {
            delete *i;
            *i = 0;
        }
}

    const char* FSExceptionHandler::className() const
    {
        const static char _name[] = "FSExceptionHandler";
        
        return _name;
    }

    FSExceptionHandler* FSExceptionHandler::clone() const
    {
        return new FSExceptionHandler(*this);
    }

    FSExceptionHandler& FSExceptionHandler::operator= (const FSExceptionHandler& rhs)
    {
        if (this != &rhs)
        {
            int index = 0;

			this->FSActionObject::operator=(rhs);

			registerNumber = rhs.registerNumber;
			variable = rhs.variable;

            for (FSVector<FSActionObject*>::iterator i = tryActions.begin(); i != tryActions.end(); i++)
            {
                delete *i;
                *i = 0;
            }

            tryActions = FSVector<FSActionObject*>(rhs.tryActions.size());

            index = 0;
            
            for (FSVector<FSActionObject*>::const_iterator i = rhs.tryActions.begin(); i != rhs.tryActions.end(); i++, index++)
                tryActions[index] = (*i)->clone();

			// Actions for the catch block
		    for (FSVector<FSActionObject*>::iterator i = catchActions.begin(); i != catchActions.end(); i++)
            {
                delete *i;
                *i = 0;
            }

            catchActions = FSVector<FSActionObject*>(rhs.catchActions.size());

            index = 0;
            
            for (FSVector<FSActionObject*>::const_iterator i = rhs.catchActions.begin(); i != rhs.catchActions.end(); i++, index++)
                catchActions[index] = (*i)->clone();

			// Actions for the final block
		    for (FSVector<FSActionObject*>::iterator i = finalActions.begin(); i != finalActions.end(); i++)
            {
                delete *i;
                *i = 0;
            }

            finalActions = FSVector<FSActionObject*>(rhs.finalActions.size());

            index = 0;
            
            for (FSVector<FSActionObject*>::const_iterator i = rhs.finalActions.begin(); i != rhs.finalActions.end(); i++, index++)
                finalActions[index] = (*i)->clone();
		
		}
        return *this;
    }

    void FSExceptionHandler::addToTry(const FSVector<FSActionObject*>& anArray)
    {
        for (FSVector<FSActionObject*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            tryActions.push_back(*i);
    }

    void FSExceptionHandler::addToCatch(const FSVector<FSActionObject*>& anArray)
    {
        for (FSVector<FSActionObject*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            catchActions.push_back(*i);
    }

    void FSExceptionHandler::addToFinal(const FSVector<FSActionObject*>& anArray)
    {
        for (FSVector<FSActionObject*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            finalActions.push_back(*i);
    }

    void FSExceptionHandler::setTryActions(const FSVector<FSActionObject*>& anArray)
	{
        for (FSVector<FSActionObject*>::iterator i = tryActions.begin(); i != tryActions.end(); i++)
        {
            delete *i;
            *i = 0;
        }

        tryActions = anArray;
	}

    void FSExceptionHandler::setCatchActions(const FSVector<FSActionObject*>& anArray)
	{
        for (FSVector<FSActionObject*>::iterator i = catchActions.begin(); i != catchActions.end(); i++)
        {
            delete *i;
            *i = 0;
        }

        catchActions = anArray;
	}

    void FSExceptionHandler::setFinalActions(const FSVector<FSActionObject*>& anArray)
	{
        for (FSVector<FSActionObject*>::iterator i = finalActions.begin(); i != finalActions.end(); i++)
        {
            delete *i;
            *i = 0;
        }

        finalActions = anArray;
	}

	int FSExceptionHandler::lengthInStream(FSOutputStream* aStream)
	{
		FSActionObject::lengthInStream(aStream);

        length += 7;
        length += variable.length() + 1;

		tryLength = 0;

		for (FSVector<FSActionObject*>::const_iterator i = tryActions.begin(); i != tryActions.end(); ++i)
		{
            tryLength += (*i)->lengthInStream(aStream);
            tryLength += ((*i)->getType() > 128) ? 3 : 1;
		}

		length += tryLength;

		catchLength = 0;

		for (FSVector<FSActionObject*>::const_iterator i = catchActions.begin(); i != catchActions.end(); ++i)
		{
            catchLength += (*i)->lengthInStream(aStream);
            catchLength += ((*i)->getType() > 128) ? 3 : 1;
		}

		length += catchLength;

		finalLength = 0;

		for (FSVector<FSActionObject*>::const_iterator i = finalActions.begin(); i != finalActions.end(); ++i)
		{
            finalLength += (*i)->lengthInStream(aStream);
            finalLength += ((*i)->getType() > 128) ? 3 : 1;
		}

		length += finalLength;
		
		return length;
	}
	
	void FSExceptionHandler::encodeToStream(FSOutputStream* aStream)
	{
        aStream->startEncoding(className());
        FSActionObject::encodeToStream(aStream);

		aStream->write(0, FSStream::UnsignedBit, 5);
		aStream->write(variable.length() == 0 ? 1:0, FSStream::UnsignedBit, 1);
		aStream->write(catchActions.size() > 0 ? 1:0, FSStream::UnsignedBit, 1);
		aStream->write(finalActions.size() > 0 ? 1:0, FSStream::UnsignedBit, 1);

		aStream->write(tryLength, FSStream::UnsignedWord, 16);
		aStream->write(catchLength, FSStream::UnsignedWord, 16);
		aStream->write(finalLength, FSStream::UnsignedWord, 16);

        if (variable.length() > 0)
		{
			aStream->write((byte*)variable.c_str(), variable.length());
			aStream->write(0, FSStream::UnsignedWord, 8);
		}
        else
		{
			aStream->write(registerNumber, FSStream::UnsignedWord, 8);
		}

#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSActionObject*>::iterator i = tryActions.begin(); i != tryActions.end(); ++i)
#ifdef _DEBUG
            FSMovie::encodeToStream(*i, aStream);
#else
            (*i)->encodeToStream(aStream);
#endif

#ifdef _DEBUG
        aStream->endEncoding("array");
#endif

		// Catch Actions
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSActionObject*>::iterator i = catchActions.begin(); i != catchActions.end(); ++i)
#ifdef _DEBUG
            FSMovie::encodeToStream(*i, aStream);
#else
            (*i)->encodeToStream(aStream);
#endif

#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
		
		// Final actions
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSActionObject*>::iterator i = finalActions.begin(); i != finalActions.end(); ++i)
#ifdef _DEBUG
            FSMovie::encodeToStream(*i, aStream);
#else
            (*i)->encodeToStream(aStream);
#endif

#ifdef _DEBUG
        aStream->endEncoding("array");
#endif

		aStream->endEncoding(className());
	}
	
	void FSExceptionHandler::decodeFromStream(FSInputStream* aStream)
	{
        aStream->startDecoding(className());
		FSActionObject::decodeFromStream(aStream);

		aStream->read(FSStream::UnsignedBit, 5);
		int containsVariable = aStream->read(FSStream::UnsignedBit, 1);
		int containsCatch = aStream->read(FSStream::UnsignedBit, 1);
		int containsFinal = aStream->read(FSStream::UnsignedBit, 1);

		int tryLength = aStream->read(FSStream::UnsignedWord, 16);
		int catchLength = aStream->read(FSStream::UnsignedWord, 16);
		int finalLength = aStream->read(FSStream::UnsignedWord, 16);

        if (containsVariable != 0)
        {
			const char* str = aStream->readString();
			variable = str;
			delete [] str;
        }
        else
        {
            registerNumber = aStream->read(FSStream::UnsignedWord, 8);
        }

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
		while (tryLength > 0)
        {
            FSActionObject* anAction = FSMovie::actionFromStream(aStream);
            
            if (anAction != 0)
            {
                tryLength -= anAction->getLength() + ((anAction->getType() >= 128) ? 3 : 1);
                tryActions.push_back(anAction);
            }
        }
#ifdef _DEBUG
        aStream->endDecoding("array");
#endif

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
		while (catchLength > 0)
        {
            FSActionObject* anAction = FSMovie::actionFromStream(aStream);
            
            if (anAction != 0)
            {
                catchLength -= anAction->getLength() + ((anAction->getType() >= 128) ? 3 : 1);
                catchActions.push_back(anAction);
            }
        }
#ifdef _DEBUG
        aStream->endDecoding("array");
#endif

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
		while (finalLength > 0)
        {
            FSActionObject* anAction = FSMovie::actionFromStream(aStream);
            
            if (anAction != 0)
            {
                finalLength -= anAction->getLength() + ((anAction->getType() >= 128) ? 3 : 1);
                finalActions.push_back(anAction);
            }
        }
#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
		aStream->endDecoding(className());
	}
}
