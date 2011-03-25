/*
 *  FSFontInfo.cpp
 *  Transform SWF
 *
 *  Created by smackay on Thu Mar 20 2003.
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

#include "FSFontInfo.h"

#include <string.h>

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSFontInfo::FSFontInfo(FSInputStream* aStream) :
        FSMovieObject(FontInfo),
        identifier(0),
        name(""),
        encoding(FSText::Unicode),
        small(false),
        italic(false),
        bold(false),
        codes()
    {
        decodeFromStream(aStream);
    }

    const char* FSFontInfo::className() const
    {
        const static char _name[] = "FSFontInfo";

        return _name;
    }

    int FSFontInfo::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);
        
        length += 3;
        length += name.length();
        length += 1;
        length += (int)(codes.size())*((encoding != FSText::ANSI) ? 2 : 1);

        return length;
    }
    
    void FSFontInfo::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        aStream->write(identifier, FSStream::UnsignedWord, 16);
        aStream->write(name.length(), FSStream::UnsignedWord, 8);
        aStream->write((byte*)name.c_str(), name.length());

        aStream->write(0, FSStream::UnsignedBit, 2);
        aStream->write(small ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(encoding, FSStream::UnsignedBit, 2);
        aStream->write(italic ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(bold ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write((encoding != FSText::ANSI) ? 1 : 0, FSStream::UnsignedBit, 1);
        
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<int>::iterator i = codes.begin(); i != codes.end(); i++)
            aStream->write((*i), FSStream::UnsignedWord, (encoding != FSText::ANSI) ? 16 : 8);
    
#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
        aStream->endEncoding(className());
    }
    
    void FSFontInfo::decodeFromStream(FSInputStream* aStream)
    {
        bool containsWideCodes = false;
        int nameLength = 0;
        int reserved = 0;
        
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

        identifier = aStream->read(FSStream::UnsignedWord, 16);
        nameLength = aStream->read(FSStream::UnsignedWord, 8);

        char* dst = new char[nameLength+1];
        char* src = (char*)aStream->read(nameLength);

        if (dst == 0)
            throw FSAllocationException("Could not allocate memory for the name of a font.");

        strncpy(dst, src, nameLength);
        dst[nameLength] = '\0';

        name = dst;

        delete [] src;
        delete [] dst;
        
        reserved = aStream->read(FSStream::UnsignedBit, 2);
        small = aStream->read(FSStream::UnsignedBit, 1) ? true : false;
        encoding = aStream->read(FSStream::UnsignedBit, 2);
        italic = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        bold = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        containsWideCodes = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;

        int bytesRead = 3 + nameLength + 1;

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        while (bytesRead < getLength())
        {
            codes.push_back(aStream->read(FSStream::UnsignedWord, (containsWideCodes) ? 16 : 8));
            bytesRead += (containsWideCodes) ? 2 : 1;
        }

#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
       aStream->endDecoding(className());
    }
}
