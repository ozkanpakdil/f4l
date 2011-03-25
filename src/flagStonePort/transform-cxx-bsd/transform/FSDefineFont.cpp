/*
 *  FSDefineFont.cpp
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

#include "FSDefineFont.h"

#include <string.h>

#include "FSMovie.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSDefineFont::FSDefineFont(FSInputStream* aStream) :
        FSDefineObject(DefineFont, 0),
        shapes()
    {
        decodeFromStream(aStream);
    }

    const char* FSDefineFont::className() const
    {
        const static char _name[] = "FSDefineFont";

        return _name;
    }

    void FSDefineFont::add(const FSVector<FSShape>& anArray)
    {
        for (FSVector<FSShape>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            shapes.push_back(*i);
    }

    int FSDefineFont::lengthInStream(FSOutputStream* aStream)
    {
        FSDefineObject::lengthInStream(aStream);
        
        aStream->setContext(FSStream::FillBits, 1);
        aStream->setContext(FSStream::LineBits, 0);
        
        length += (int)(shapes.size())*2;
    
        for (FSVector<FSShape>::iterator i = shapes.begin(); i != shapes.end(); ++i)
            length += (*i).lengthInStream(aStream);

        aStream->setContext(FSStream::FillBits, 0);
        aStream->setContext(FSStream::LineBits, 0);
    
        return length;
    }
    
    void FSDefineFont::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);

        aStream->setContext(FSStream::FillBits, 1);
        aStream->setContext(FSStream::LineBits, 0);
        
        aStream->setContext(FSStream::FillStyles, 1);
        aStream->setContext(FSStream::LineStyles, 0);

        FSMovie::encodeToStream(shapes, 16, false, aStream);
    
        aStream->setContext(FSStream::FillBits, 0);
        aStream->setContext(FSStream::LineBits, 0);
        
        aStream->setContext(FSStream::FillStyles, 0);
        aStream->setContext(FSStream::LineStyles, 0);

        aStream->endEncoding(className());
    }
    
    void FSDefineFont::decodeFromStream(FSInputStream* aStream)
    {
        int glyphCount = 0;
        
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);

        glyphCount = aStream->scan(FSStream::UnsignedWord, 16) / 2;
        aStream->setCursor(aStream->getCursor()-16);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=0; i<glyphCount; i++)
            aStream->read(FSStream::UnsignedWord, 16);

#ifdef _DEBUG
        aStream->endDecoding("array");
        aStream->startDecoding("array");
#endif
        for (int i=0; i<glyphCount; i++)
            shapes.push_back(FSShape(aStream));

#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        aStream->endDecoding(className());
    }
}
