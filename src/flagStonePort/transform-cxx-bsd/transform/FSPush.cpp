/*
 *  FSPush.cpp
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

#include "FSPush.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

#include "FSValue.h"
#include "FSBoolean.h"
#include "FSInteger.h"
#include "FSDouble.h"
#include "FSString.h"
#include "FSNull.h"
#include "FSVoid.h"
#include "FSTableIndex.h"
#include "FSRegisterIndex.h"

using namespace transform;

namespace transform
{
    FSPush::FSPush(FSInputStream* aStream) :
        FSActionObject(Push),
        values()
    {
        decodeFromStream(aStream);
    }

    FSPush::FSPush(const FSVector<FSValue*>& anArray) :
        FSActionObject(Push),
        values(anArray)
    {
    }

    FSPush::FSPush(const FSPush& rhs) :
        FSActionObject(rhs),
        values(rhs.values.size())
    {
        int index = 0;
            
        for (FSVector<FSValue*>::const_iterator i = rhs.values.begin(); i != rhs.values.end(); i++, index++)
            values[index] = (*i)->clone();
    }

    FSPush::~FSPush()
    {
        for (FSVector<FSValue*>::iterator i = values.begin(); i != values.end(); i++)
        {
            delete *i;
            *i = 0;
        }
    }
    
    FSPush* FSPush::clone() const
    {
        return new FSPush(*this);
    }
    
    const char* FSPush::className() const
    {
        const static char _name[] = "FSPush";

        return _name;
    }

    FSPush& FSPush::operator= (const FSPush& rhs)
    {
        if (this != &rhs)
        {
            this->FSActionObject::operator=(rhs);

            for (FSVector<FSValue*>::iterator i = values.begin(); i != values.end(); i++)
            {
                delete *i;
                *i = 0;
            }

            values = FSVector<FSValue*>(rhs.values.size());

            int index = 0;
            
            for (FSVector<FSValue*>::const_iterator i = rhs.values.begin(); i != rhs.values.end(); i++, index++)
                values[index] = (*i)->clone();
        }
        return *this;
    }
    
    void FSPush::add(const FSVector<FSValue*>& anArray)
    {
        for (FSVector<FSValue*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            values.push_back(*i);
    } 
    
    int FSPush::lengthInStream(FSOutputStream* aStream)
    {
        FSActionObject::lengthInStream(aStream);

        for (FSVector<FSValue*>::const_iterator i = values.begin(); i != values.end(); ++i)
            length += (*i)->lengthInStream(aStream);

        return length;
    }
    
    void FSPush::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSActionObject::encodeToStream(aStream);

#ifdef _DEBUG
        aStream->startEncoding("array");
#endif

        for (FSVector<FSValue*>::iterator i = values.begin(); i != values.end(); ++i)
            (*i)->encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding("array");
        aStream->endEncoding(className());
#endif
    }
    
    void FSPush::decodeFromStream(FSInputStream* aStream)
    {
        int valuesLength = 0;
        
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);
        
        valuesLength = getLength();

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        while (valuesLength > 0)
        {
            FSValue* currentValue;
            
            int valueType = aStream->scan(FSStream::UnsignedWord, 8);

            aStream->setCursor(aStream->getCursor()-8);
            
            switch (valueType)
            {
                case 0:
                    currentValue = new FSString(aStream);
                    break;
                case 1: // Pre version 5 property
                    currentValue = new FSInteger(aStream);
                    break;
                case 2:
                    currentValue = new FSNull(aStream);
                    break;
                case 3:
                    currentValue = new FSVoid(aStream);
                    break;
                case 4:
                    currentValue = new FSRegisterIndex(aStream);
                    break;
                case 5:
                    currentValue = new FSBoolean(aStream);
                    break;
                case 6:
                    currentValue = new FSDouble(aStream);
                    break;
                case 7:
                    currentValue = new FSInteger(aStream);
                    break;
                case 8:
                case 9:
                    currentValue = new FSTableIndex(aStream);
                    break;
            }

            if (currentValue == 0)
                throw FSAllocationException("Cannot allocate new data type for FSPush object.");

            switch (valueType)
            {
                case 0: valuesLength -= currentValue->length()+2; break;
                case 1: valuesLength -= 5; break;
                case 2: valuesLength -= 1; break;
                case 3: valuesLength -= 1; break;
                case 4: valuesLength -= 2; break;
                case 5: valuesLength -= 2; break;
                case 6: valuesLength -= 9; break;
                case 7: valuesLength -= 5; break;
                case 8: valuesLength -= 2; break;
                case 9: valuesLength -= 3; break;
            }
            values.push_back(currentValue);
        }
        
#ifdef _DEBUG
        aStream->endDecoding("array");
        aStream->endDecoding(className());
#endif
    }
}