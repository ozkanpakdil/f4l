/*
 *  FSTable.cpp
 *  Transform SWF
 *
 *  Created by smackay on Fri Mar 28 2003.
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

#include "FSTable.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSTable::FSTable(FSInputStream* aStream) :
        FSActionObject(Table),
        values()
    {
        decodeFromStream(aStream);
    }

    const char* FSTable::className() const
    {
        const static char _name[] = "FSTable";

        return _name;
    }

    void FSTable::add(const FSVector<FSString>& anArray)
    {
        for (FSVector<FSString>::const_iterator i = anArray.begin(); i != anArray.end(); i++)
            values.push_back(*i);
    }

    void FSTable::setValues(const char* anArray[], int size)
    {
        values.resize(size);

        for (int i=0; i<size; i++)
            values[i] = FSString(anArray[i]);
    }

    int FSTable::lengthInStream(FSOutputStream* aStream)
    {
        FSActionObject::lengthInStream(aStream);
        
        length += 2;

        for (FSVector<FSString>::const_iterator i = values.begin(); i != values.end(); i++)
            length += (*i).length()+1;
                    
        return length;
    }
    
    void FSTable::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSActionObject::encodeToStream(aStream);

        aStream->write(values.size(), FSStream::UnsignedWord, 16);
        
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSString>::const_iterator i = values.begin(); i != values.end(); i++)
        {
            aStream->write((byte*)(*i).c_str(), (*i).length());
            aStream->write(0, FSStream::UnsignedWord, 8);
        }
#ifdef _DEBUG
        aStream->endEncoding("array");
        aStream->endEncoding(className());
#endif
    }
    
    void FSTable::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);

        int attributeCount = aStream->read(FSStream::UnsignedWord, 16);
            
        if (attributeCount > 0)
        {
#ifdef _DEBUG
            aStream->startDecoding("array");
#endif
            for (int i=0; i<attributeCount; i++)
            {
                char* str = aStream->readString();

                values.push_back(FSString(str));

                delete [] str;
            }
#ifdef _DEBUG
            aStream->endDecoding("array");
#endif
        }
        else
        {
            /*
             * Reset the length as Macromedia is using the length of a 
             * table to hide coded following an empty table.
             */
            length = 2;
        }
#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
