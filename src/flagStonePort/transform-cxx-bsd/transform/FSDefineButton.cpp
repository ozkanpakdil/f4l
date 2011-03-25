/*
 *  FSDefineButton.cpp
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

#include "FSDefineButton.h"

#include "FSMovie.h"
#include "FSActionObject.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSDefineButton::FSDefineButton(FSInputStream* aStream) :
        FSDefineObject(DefineButton, 0),
        buttonRecords(),
        actions()
    {
        decodeFromStream(aStream);
    }

    FSDefineButton::FSDefineButton(const FSDefineButton& rhs) :
        FSDefineObject(rhs),
        buttonRecords(rhs.buttonRecords),
        actions(rhs.actions.size())
    {
        int index = 0;

        for (FSVector<FSActionObject*>::const_iterator i = rhs.actions.begin(); i != rhs.actions.end(); i++, index++)
            actions[index] = (*i)->clone();
    }
    
    FSDefineButton::~FSDefineButton()
    {
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }
    }
    
    const char* FSDefineButton::className() const
    {
        const static char _name[] = "FSDefineButton";
    
        return _name;
    }
    
    FSDefineButton& FSDefineButton::operator= (const FSDefineButton& rhs)
    {
        if (this != &rhs)
        {
            this->FSDefineObject::operator=(rhs);

            buttonRecords = rhs.buttonRecords;
    
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
    
    void FSDefineButton::add(const FSVector<FSButton>& anArray)
    {
        for (FSVector<FSButton>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            buttonRecords.push_back(*i);
    }
 
    void FSDefineButton::add(const FSVector<FSActionObject*>& anArray)
    {
        for (FSVector<FSActionObject*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            actions.push_back(*i);
    }

    void FSDefineButton::setActions(const FSVector<FSActionObject*>& anArray)
    {
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); i++)
        {
            delete *i;
            *i = 0;
        }
        actions = anArray;
    }

    int FSDefineButton::lengthInStream(FSOutputStream* aStream)
    {
        FSDefineObject::lengthInStream(aStream);

        for (FSVector<FSButton>::iterator i = buttonRecords.begin(); i != buttonRecords.end(); ++i)
            length += (*i).lengthInStream(aStream);

        length += 1;

        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); ++i)
        {
            length += (*i)->lengthInStream(aStream);
            length += ((*i)->getType() > 128) ? 3 : 1;
        }

        length += 1;
        
        return length;
    }
    
    void FSDefineButton::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);
        
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSButton>::iterator i = buttonRecords.begin(); i != buttonRecords.end(); ++i)
            (*i).encodeToStream(aStream);

        aStream->write(0, FSStream::UnsignedWord, 8);
    
#ifdef _DEBUG
        aStream->endEncoding("array");
        aStream->startEncoding("array");
#endif
        for (FSVector<FSActionObject*>::iterator i = actions.begin(); i != actions.end(); ++i)
            (*i)->encodeToStream(aStream);

        aStream->write(0, FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
        aStream->endEncoding(className());
    }
    
    void FSDefineButton::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);
        
#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        while (aStream->scan(FSStream::UnsignedWord, 8) != 0)
        {
            aStream->setCursor(aStream->getCursor()-8);
            buttonRecords.push_back(FSButton(aStream));
        }
        
#ifdef _DEBUG
        aStream->endDecoding("array");
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
