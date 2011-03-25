/*
 *  FSText.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 24 2003.
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

#include "FSText.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSText::FSText(FSInputStream* aStream) :
        identifier(0),
        color(),
        xOffset(Transform::VALUE_NOT_SET),
        yOffset(Transform::VALUE_NOT_SET),
        height(0),
        characters()
    {
        decodeFromStream(aStream);
    }

    const char* FSText::className() const
    {
        const static char _name[] = "FSText";

        return _name;
    }

    void FSText::add(const FSVector<FSCharacter>& anArray)
    {
        for (FSVector<FSCharacter>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            characters.push_back(*i);
    }

    int FSText::glyphBits() const
    {
        int numberOfBits = 0;

        for (FSVector<FSCharacter>::const_iterator i = characters.begin(); i != characters.end(); ++i)
        {
            int size = FSStream::FieldSize((*i).getGlyphIndex());

            numberOfBits = (numberOfBits > size) ? numberOfBits : size;
        }

        return numberOfBits;
    }

    int FSText::advanceBits() const
    {
        int numberOfBits = 0;
    
        for (FSVector<FSCharacter>::const_iterator i = characters.begin(); i != characters.end(); ++i)
        {
            int size = FSStream::FieldSize((*i).getAdvance(), true);
    
            numberOfBits = (numberOfBits > size) ? numberOfBits : size;
        }
    
        return numberOfBits;
    }
    
    int FSText::lengthInStream(FSOutputStream* aStream)
    {
        bool _containsStyle = containsStyle();
        bool _containsFont = containsFont();
        bool _containsColor = color.containsColor();
        bool _containsYOffset = containsYOffset();
        bool _containsXOffset = containsXOffset();

        int tagLength = 0;

        if (_containsStyle)
        {
            tagLength += 1;
            tagLength += (_containsFont) ? 2 : 0;
            tagLength += (_containsColor) ? color.lengthInStream(aStream) : 0;
            tagLength += (_containsYOffset) ? 2 : 0;
            tagLength += (_containsXOffset) ? 2 : 0;
            tagLength += (_containsFont) ? 2 : 0;
        }

        if (characters.size() > 0)
        {
            int numberOfBits = 0;
            int numberOfGlyphBits = aStream->getContext(FSStream::GlyphBits);
            int numberOfAdvanceBits = aStream->getContext(FSStream::AdvanceBits);

            numberOfBits = 8 + (numberOfGlyphBits + numberOfAdvanceBits)*(int)(characters.size());
            numberOfBits += (numberOfBits % 8 > 0) ? 8 - (numberOfBits % 8) : 0;

            tagLength += numberOfBits >> 3;
        }
    
        return tagLength;
    }
    
    void FSText::encodeToStream(FSOutputStream* aStream)
    {
        bool _containsStyle = containsStyle();
        bool _containsFont = containsFont();
        bool _containsColor = color.containsColor();
        bool _containsYOffset = containsYOffset();
        bool _containsXOffset = containsXOffset();

#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */

        if (_containsStyle)
        {
            aStream->write(1, FSStream::UnsignedBit, 1);
            aStream->write(0, FSStream::UnsignedBit, 3);
            aStream->write(_containsFont ? 1 : 0, FSStream::UnsignedBit, 1);
            aStream->write(_containsColor ? 1 : 0, FSStream::UnsignedBit, 1);
            aStream->write(_containsYOffset ? 1 : 0, FSStream::UnsignedBit, 1);
            aStream->write(_containsXOffset ? 1 : 0, FSStream::UnsignedBit, 1);

            if (_containsFont)
                aStream->write(identifier, FSStream::UnsignedWord, 16);

            if (_containsColor)
                color.encodeToStream(aStream);

            if (_containsXOffset)
                aStream->write(xOffset, FSStream::SignedWord, 16);

            if (_containsYOffset)
                aStream->write(yOffset, FSStream::SignedWord, 16);

            if (_containsFont)
                aStream->write(height, FSStream::UnsignedWord, 16);
        }

        if (characters.size() > 0)
        {
            aStream->write((int)(characters.size()), FSStream::UnsignedBit, 8);

#ifdef _DEBUG
            aStream->startEncoding("array");
#endif
            for (FSVector<FSCharacter>::iterator i = characters.begin(); i != characters.end(); ++i)
                (*i).encodeToStream(aStream);

            aStream->flush();

#ifdef _DEBUG
            aStream->endEncoding("array");
#endif
        }

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSText::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        
        aStream->read(FSStream::UnsignedBit, 1);
        aStream->read(FSStream::UnsignedBit, 3); // reserved

        bool _containsFont = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        bool _containsColor = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        bool _containsYOffset = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        bool _containsXOffset = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;

        if (_containsFont)
            identifier = aStream->read(FSStream::UnsignedWord, 16);
        else
            aStream->read(FSStream::UnsignedWord, 0);

        if (_containsColor)
            color.decodeFromStream(aStream);
        else
            aStream->read(FSStream::UnsignedWord, 0);

        if (_containsXOffset)
            xOffset = aStream->read(FSStream::SignedWord, 16);
        else
            aStream->read(FSStream::SignedWord, 0);

        if (_containsYOffset)
            yOffset = aStream->read(FSStream::SignedWord, 16);
        else
            aStream->read(FSStream::SignedWord, 0);

        if (_containsFont)
            height = aStream->read(FSStream::UnsignedWord, 16);
        else
            aStream->read(FSStream::UnsignedWord, 0);

        int charCount = aStream->read(FSStream::UnsignedBit, 8);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=0; i<charCount; i++)
            characters.push_back(FSCharacter(aStream));

        aStream->flush();

#ifdef _DEBUG
        aStream->endDecoding("array");
        aStream->endDecoding(className());
#endif
    }

    bool FSText::containsStyle() const
    {
        return containsFont() || color.containsColor() || containsXOffset() || containsYOffset();
    }
    
    bool FSText::containsFont() const
    {
        return identifier != 0 && height != 0;
    }

    bool FSText::containsXOffset() const
    {
        return xOffset != Transform::VALUE_NOT_SET;
    }

    bool FSText::containsYOffset() const
    {
        return yOffset != Transform::VALUE_NOT_SET;
    }
}
