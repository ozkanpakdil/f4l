/*
 *  FSDefineFont2.cpp
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

#include "FSDefineFont2.h"

#include <string.h>

#include "FSMovie.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSDefineFont2::FSDefineFont2(FSInputStream* aStream) :
        FSDefineObject(DefineFont2, 0),
        wideOffsets(false),
        encoding(FSText::Unicode),
        small(false),
        italic(false),
        bold(false),
        language(0),
        name(""),
        shapes(),
        codes(),
        ascent(0),
        descent(0),
        leading(0),
        advances(),
        bounds(),
        kernings()
    {
        decodeFromStream(aStream);
    }

    const char* FSDefineFont2::className() const
    {
        const static char _name[] = "FSDefineFont2";

        return _name;
    }

    void FSDefineFont2::add(const FSVector<FSShape>& anArray)
    {
        for (FSVector<FSShape>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            shapes.push_back(*i);
    }

    void FSDefineFont2::addCode(const FSVector<int>& anArray)
    {
        for (FSVector<int>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            codes.push_back(*i);
    }

    void FSDefineFont2::addAdvance(const FSVector<int>& anArray)
    {
        for (FSVector<int>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            advances.push_back(*i);
    }

    void FSDefineFont2::add(const FSVector<FSBounds>& anArray)
    {
        for (FSVector<FSBounds>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            bounds.push_back(*i);
    }

    void FSDefineFont2::add(const FSVector<FSKerning>& anArray)
    {
        for (FSVector<FSKerning>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            kernings.push_back(*i);
    }

    int FSDefineFont2::lengthInStream(FSOutputStream* aStream)
    {
        int glyphLength = 0;
        int wideCodes = 0;
        
        if (aStream->getContext(FSStream::Version) > 5)
            wideCodes = 1;
        else
            wideCodes = (encoding != FSText::ANSI) ? 1 : 0;

        FSDefineObject::lengthInStream(aStream);
        
        aStream->setContext(FSStream::FillBits, 1);
        aStream->setContext(FSStream::LineBits, 0);
        aStream->setContext(FSStream::WideCodes, wideCodes);
        
        for (FSVector<FSShape>::iterator i = shapes.begin(); i != shapes.end(); i++)
            glyphLength += (*i).lengthInStream(aStream);

        wideOffsets = (shapes.size()*2 + glyphLength) > 65535;

        length += 3;
        length += name.length();
        length += 2;
        length += (int)(shapes.size())*(wideOffsets ? 4 : 2);
        length += wideOffsets ? 4 : 2;
        length += glyphLength;
        length += (int)(shapes.size())*(wideCodes ? 2 : 1);

        if (containsLayoutInfo())
        {
            length += 6;
            length += (int)(shapes.size())*2;

            for (FSVector<FSBounds>::iterator i = bounds.begin(); i != bounds.end(); ++i)
                length += (*i).lengthInStream(aStream);
        
            length += 2;
            length += (int)(kernings.size())*(wideCodes ? 6 : 4);
        }

        aStream->setContext(FSStream::FillBits, 0);
        aStream->setContext(FSStream::LineBits, 0);
        aStream->setContext(FSStream::WideCodes, 0);

        return length;
    }
    
    void FSDefineFont2::encodeToStream(FSOutputStream* aStream)
    {
        int wideCodes = 0;
        int format = 0;
        
        if (aStream->getContext(FSStream::Version) > 5)
            wideCodes = 1;
        else
            wideCodes = (encoding != FSText::ANSI) ? 1 : 0;

        if (encoding == FSText::ANSI)
            format = 1;
        else if (small)
           format = 2;
        else if (encoding == FSText::SJIS)
            format = 4;
        
        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);

        aStream->setContext(FSStream::FillBits, 1);
        aStream->setContext(FSStream::LineBits, 0);
        aStream->setContext(FSStream::WideCodes, wideCodes);
        
        aStream->setContext(FSStream::FillStyles, 1);
        aStream->setContext(FSStream::LineStyles, 0);

        aStream->write(containsLayoutInfo() ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(format, FSStream::UnsignedBit, 3);
        aStream->write(wideOffsets ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(wideCodes ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(italic ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(bold ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(language, FSStream::UnsignedBit, 8);
        aStream->write(name.length(), FSStream::UnsignedWord, 8);
        aStream->write((byte*)name.c_str(), name.length());
            
        aStream->write((int)(shapes.size()), FSStream::UnsignedWord, 16);

        FSMovie::encodeToStream(shapes, wideOffsets ? 32 : 16, true, aStream);
    
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<int>::iterator i = codes.begin(); i != codes.end(); i++)
            aStream->write((*i), FSStream::UnsignedWord, wideCodes ? 16 : 8);
    
#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
        if (containsLayoutInfo())
        {
            aStream->write(ascent, FSStream::SignedWord, 16);
            aStream->write(descent, FSStream::SignedWord, 16);
            aStream->write(leading, FSStream::SignedWord, 16);

#ifdef _DEBUG
            aStream->startEncoding("array");
#endif
            for (FSVector<int>::iterator i = advances.begin(); i != advances.end(); i++)
                aStream->write((*i), FSStream::SignedWord, 16);

#ifdef _DEBUG
            aStream->endEncoding("array");
            aStream->startEncoding("array");
#endif
            for (FSVector<FSBounds>::iterator i = bounds.begin(); i != bounds.end(); i++)
                (*i).encodeToStream(aStream);

#ifdef _DEBUG
            aStream->endEncoding("array");
#endif
            aStream->write((int)(kernings.size()), FSStream::UnsignedWord, 16);

#ifdef _DEBUG
            aStream->startEncoding("array");
#endif
            for (FSVector<FSKerning>::iterator i = kernings.begin(); i != kernings.end(); i++)
                (*i).encodeToStream(aStream);

#ifdef _DEBUG
            aStream->endEncoding("array");
#endif
        }

        aStream->setContext(FSStream::FillBits, 0);
        aStream->setContext(FSStream::LineBits, 0);
        aStream->setContext(FSStream::WideCodes, 0);
        
        aStream->setContext(FSStream::FillStyles, 0);
        aStream->setContext(FSStream::LineStyles, 0);

        aStream->endEncoding(className());
    }
    
    void FSDefineFont2::decodeFromStream(FSInputStream* aStream)
    {
        bool containsWideOffsets = false;
        bool containsWideCodes = false;
        bool containsLayout = false;
        
        int glyphCount = 0;
        int kerningCount = 0;
        int nameLength = 0;
        int codeOffset = 0;
        
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);
        
        containsLayout = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        int format = aStream->read(FSStream::UnsignedBit, 3);

        if (format == 1)
            encoding = FSText::ANSI;
        else if (format == 2)
            small = true;
        else if (format == 4)
            encoding = FSText::SJIS;
        
        containsWideOffsets = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        containsWideCodes = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;

        aStream->setContext(FSStream::WideCodes, containsWideCodes);

        italic = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        bold = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        language = aStream->read(FSStream::UnsignedBit, 8);
        nameLength = aStream->read(FSStream::UnsignedWord, 8);

        char* dst = new char[nameLength+1];
        char* src = (char*)aStream->read(nameLength);

        if (dst == 0)
            throw FSAllocationException("Cannot allocate memory for font name.");

        strncpy(dst, src, nameLength);
        dst[nameLength] = '\0';

        name = dst;

        delete [] src;
        delete [] dst;
        
        glyphCount = aStream->read(FSStream::UnsignedWord, 16);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=0; i<glyphCount; i++)
            aStream->read(FSStream::UnsignedWord, (containsWideOffsets) ? 32 : 16);

#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        codeOffset = aStream->read(FSStream::UnsignedWord, (containsWideOffsets) ? 32 : 16);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=0; i<glyphCount; i++)
            shapes.push_back(FSShape(aStream));
            
#ifdef _DEBUG
        aStream->endDecoding("array");
        aStream->startDecoding("array");
#endif
        for (int i=0; i<glyphCount; i++)
            codes.push_back(aStream->read(FSStream::UnsignedWord, (containsWideCodes) ? 16 : 8));

#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        if (containsLayout)
        {
            ascent = aStream->read(FSStream::SignedWord, 16);
            descent = aStream->read(FSStream::SignedWord, 16);
            leading = aStream->read(FSStream::SignedWord, 16);
            
#ifdef _DEBUG
            aStream->startDecoding("array");
#endif
            for (int i=0; i<glyphCount; i++)
                advances.push_back(aStream->read(FSStream::SignedWord, 16));

#ifdef _DEBUG
            aStream->endDecoding("array");
            aStream->startDecoding("array");
#endif
            for (int i=0; i<glyphCount; i++)
                bounds.push_back(FSBounds(aStream));

#ifdef _DEBUG
            aStream->endDecoding("array");
#endif
            kerningCount = aStream->read(FSStream::UnsignedWord, 16);

#ifdef _DEBUG
            aStream->startDecoding("array");
#endif
            for (int i=0; i<kerningCount; i++)
                kernings.push_back(FSKerning(aStream));

#ifdef _DEBUG
            aStream->endDecoding("array");
#endif
        }

        aStream->setContext(FSStream::WideCodes, 0);

        aStream->endDecoding(className());
    }

    bool FSDefineFont2::containsLayoutInfo() const
    {
        bool layout = false;
        
        layout = layout || ascent != 0;
        layout = layout || descent != 0;
        layout = layout || leading != 0;
        layout = layout || advances.size() > 0;
        layout = layout || bounds.size() > 0;
        layout = layout || kernings.size() > 0;
        
        return layout;
    }
}
