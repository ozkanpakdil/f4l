/*
 *  FSDefineText.cpp
 *  Transform SWF
 *
 *  Created by smackay on Tue Feb 25 2003.
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

#include "FSDefineText.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSDefineText::FSDefineText(FSInputStream* aStream) :
        FSDefineObject(DefineText, 0),
        bounds(),
        transform(),
        textRecords()
    {
        decodeFromStream(aStream);
    }
    
    const char* FSDefineText::className() const
    {
        const static char _name[] = "FSDefineText";

        return _name;
    }

    void FSDefineText::add(const FSVector<FSText>& anArray)
    {
        for (FSVector<FSText>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            textRecords.push_back(*i);
    }
    
    int FSDefineText::lengthInStream(FSOutputStream* aStream)
    {
        FSDefineObject::lengthInStream(aStream);

        aStream->setContext(FSStream::GlyphBits, glyphBits());
        aStream->setContext(FSStream::AdvanceBits, advanceBits());

        length += bounds.lengthInStream(aStream);
        length += transform.lengthInStream(aStream);
        length += 2;

        for (FSVector<FSText>::iterator i = textRecords.begin(); i != textRecords.end(); ++i)
            length += (*i).lengthInStream(aStream);
    
        length += 1;

        aStream->setContext(FSStream::GlyphBits, 0);
        aStream->setContext(FSStream::AdvanceBits, 0);

        return length;
    }
    
    void FSDefineText::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);

        aStream->setContext(FSStream::GlyphBits, glyphBits());
        aStream->setContext(FSStream::AdvanceBits, advanceBits());

        bounds.encodeToStream(aStream);
        transform.encodeToStream(aStream);
    
        aStream->write(aStream->getContext(FSStream::GlyphBits), FSStream::UnsignedWord, 8);
        aStream->write(aStream->getContext(FSStream::AdvanceBits), FSStream::UnsignedWord, 8);
    
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSText>::iterator i = textRecords.begin(); i != textRecords.end(); ++i)
            (*i).encodeToStream(aStream);

        aStream->write(0, FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
        aStream->setContext(FSStream::GlyphBits, 0);
        aStream->setContext(FSStream::AdvanceBits, 0);

        aStream->endEncoding(className());
    }
    
    void FSDefineText::decodeFromStream(FSInputStream* aStream)
    {
        int glyphBits = 0;
        int advanceBits = 0;
        int location = 0;
        
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);

        // Mark the start of the tag body
        
        location = aStream->getCursor();

        bounds.decodeFromStream(aStream);

        // This code is used to get round a bug in Flash - sometimes 16, 
        // 8-bit zeroes are written out before the transform. The root 
        // cause in Flash is unknown but seems to be related to the 
        // bounds not being set - all values are zero.

        bool bytesAreZero = true;
        int start = aStream->getCursor();
        
        for (int i=0; i<16; i++)
        {
            if (aStream->scan(FSStream::UnsignedWord, 8) != 0)
                bytesAreZero = false;
        }
        
        aStream->setCursor(start);
        
        if (bytesAreZero)
            for (int i=0; i<16; i++)
                aStream->scan(FSStream::UnsignedWord, 8);

        // Back to reading the rest of the tag

        transform.decodeFromStream(aStream);

        glyphBits = aStream->read(FSStream::UnsignedWord, 8);
        advanceBits = aStream->read(FSStream::UnsignedWord, 8);

        aStream->setContext(FSStream::GlyphBits, glyphBits);
        aStream->setContext(FSStream::AdvanceBits, advanceBits);
        
#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        /*
         * Set the instance variable directly since Flash files can contain
         * FSDefineText objects with no text records - this appears to be a 
         * bug in the Flash file.
         */

        while (aStream->scan(FSStream::UnsignedBit, 8))
        {
            aStream->setCursor(aStream->getCursor()-8);
            textRecords.push_back(FSText(aStream));
        }

#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        aStream->setContext(FSStream::GlyphBits, 0);
        aStream->setContext(FSStream::AdvanceBits, 0);

        aStream->endDecoding(className());
    }

    int FSDefineText::glyphBits() const
    {
        int numberOfBits = 0;
    
        for (FSVector<FSText>::const_iterator i = textRecords.begin(); i != textRecords.end(); ++i)
        {
            int size = (*i).glyphBits();
    
            numberOfBits = (numberOfBits > size) ? numberOfBits : size;
        }
        return numberOfBits;
    }
    
    int FSDefineText::advanceBits() const
    {
        int numberOfBits = 0;
    
        for (FSVector<FSText>::const_iterator i = textRecords.begin(); i != textRecords.end(); ++i)
        {
            int size = (*i).advanceBits();
    
            numberOfBits = (numberOfBits > size) ? numberOfBits : size;
        }
        return numberOfBits;
    }
}
