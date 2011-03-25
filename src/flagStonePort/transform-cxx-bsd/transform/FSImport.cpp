/*
 *  FSImport.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 10 2003.
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

#include "FSImport.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSImport::FSImport(FSInputStream* aStream) :
        FSMovieObject(Import),
        url(),
        objects()
    {
        decodeFromStream(aStream);
    }

    FSImport::FSImport(const FSVector<FSObjectName>& anArray) :
        FSMovieObject(Import),
        objects(anArray.size())
    {
        int index = 0;

        for (FSVector<FSObjectName>::const_iterator i = anArray.begin(); i != anArray.end(); i++, index++)
            objects[index] = *i;
    }
    
    const char* FSImport::className() const
    {
        const static char _name[] = "FSImport";

        return _name;
    }

    void FSImport::add(const FSVector<FSObjectName>& anArray)
    {
        for (FSVector<FSObjectName>::const_iterator i = anArray.begin(); i != anArray.end(); i++)
            objects.push_back(*i);
    }

    int FSImport::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);

        length += url.length() + 1;
        length += 2;

        for (FSVector<FSObjectName>::const_iterator i = objects.begin(); i != objects.end(); i++)
        {
            length += 2;
            length += (*i).name.length() + 1;
        }            
        return length;
    }
    
    void FSImport::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        aStream->write((byte*)url.c_str(), url.length());
        aStream->write(0, FSStream::UnsignedWord, 8);

        aStream->write(objects.size(), FSStream::UnsignedWord, 16);

        for (FSVector<FSObjectName>::iterator i = objects.begin(); i != objects.end(); i++)
        {
            aStream->write((*i).identifier, FSStream::UnsignedWord, 16);
            aStream->write((byte*)(*i).name.c_str(), (*i).name.length());
            aStream->write(0, FSStream::UnsignedWord, 8);
        }
        aStream->endEncoding(className());
    }
    
    void FSImport::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

        char* str = aStream->readString();

        url = str;
        delete [] str;

        int count = aStream->read(FSStream::UnsignedWord, 16);

        for (int i=0; i<count; i++)
        {
            int identifier = aStream->read(FSStream::UnsignedWord, 16);
            char* str = aStream->readString();

            objects.push_back(FSObjectName(identifier, str));

            delete [] str;
        }
        aStream->endDecoding(className());
    }
}
