/*
 *  FSDefineTextField.cpp
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

#include "FSDefineTextField.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSDefineTextField::FSDefineTextField(FSInputStream* aStream) : FSDefineObject(DefineTextField, 0),
        bounds(0, 0, 0, 0),
        wordWrapped(false),
        multiline(false),
        password(false),
        readOnly(false),
        selectable(false),
        bordered(false),
        html(false),
        outlined(false),
        fontId(0),
        fontHeight(0),
        color(0, 0, 0, 0),
        maxLength(0),
        alignment(0),
        leftMargin(0),
        rightMargin(0),
        indent(0),
        leading(0),
        variableName(""),
        initialText("")
    {
        decodeFromStream(aStream);
    }
    
    FSDefineTextField::FSDefineTextField(int anIdentifier, const FSBounds& aBounds) : FSDefineObject(DefineTextField, anIdentifier),
        bounds(aBounds),
        wordWrapped(false),
        multiline(false),
        password(false),
        readOnly(false),
        selectable(false),
        bordered(false),
        html(false),
        outlined(false),
        fontId(0),
        fontHeight(0),
        color(0, 0, 0, 0),
        maxLength(0),
        alignment(0),
        leftMargin(0),
        rightMargin(0),
        indent(0),
        leading(0),
        variableName(""),
        initialText("")
    {
    }
    
    FSDefineTextField* FSDefineTextField::clone() const
    {
        return new FSDefineTextField(*this);
    }
    
    const char* FSDefineTextField::className() const
    {
        const static char _name[] = "FSDefineTextField";

        return _name;
    }

    int FSDefineTextField::lengthInStream(FSOutputStream* aStream)
    {
        bool _containsFont = containsFont();
        bool _containsColor = color.containsColor();
        bool _containsMaxLength = containsMaxLength();
        bool _containsText = containsText();
        
        FSDefineObject::lengthInStream(aStream);
    
        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        length += bounds.lengthInStream(aStream);
        length += 2;
        length += (_containsFont) ? 4 : 0;
        length += (_containsColor) ? color.lengthInStream(aStream) : 0;
        length += (_containsMaxLength) ? 2 : 0;
        length += (containsLayoutInfo()) ? 9 : 0;
        length += variableName.length()+1;
        length += (_containsText) ? initialText.length()+1 : 0;
    
        aStream->setContext(FSStream::ColorContainsAlpha, 0);
        
        return length;
    }
    
    void FSDefineTextField::encodeToStream(FSOutputStream* aStream)
    {
        bool _containsFont = containsFont();
        bool _containsColor = color.containsColor();
        bool _containsMaxLength = containsMaxLength();
        bool _containsText = containsText();
        
        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);
        
        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        bounds.encodeToStream(aStream);
        aStream->write(_containsText ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(wordWrapped ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(multiline ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(password ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(readOnly ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(_containsColor ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(_containsMaxLength ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(_containsFont ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(0, FSStream::UnsignedBit, 2);
        aStream->write(containsLayoutInfo() ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(selectable ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(bordered ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(0, FSStream::UnsignedBit, 1);
        aStream->write(html ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(outlined ? 1 : 0, FSStream::UnsignedBit, 1);
    
        if (_containsFont)
        {
            aStream->write(fontId, FSStream::UnsignedWord, 16);
            aStream->write(fontHeight, FSStream::UnsignedWord, 16);
        }
    
        if (_containsColor)
            color.encodeToStream(aStream);
    
        if (_containsMaxLength)
            aStream->write(maxLength, FSStream::UnsignedWord, 16);
    
        if (containsLayoutInfo())
        {
            aStream->write(alignment, FSStream::UnsignedWord, 8);
            aStream->write(leftMargin, FSStream::UnsignedWord, 16);
            aStream->write(rightMargin, FSStream::UnsignedWord, 16);
            aStream->write(indent, FSStream::UnsignedWord, 16);
            aStream->write(leading, FSStream::UnsignedWord, 16);
        }

        aStream->write((byte*)variableName.c_str(), variableName.length());
        aStream->write(0, FSStream::UnsignedWord, 8);
    
        if (_containsText)
        {
            aStream->write((byte*)initialText.c_str(), initialText.length());
            aStream->write(0, FSStream::UnsignedWord, 8);
        }
        aStream->setContext(FSStream::ColorContainsAlpha, 0);
        
        aStream->endEncoding(className());
    }
    
    void FSDefineTextField::decodeFromStream(FSInputStream* aStream)
    {
        bool _containsFont = false;
        bool _containsColor = false;
        bool _containsMaxLength = false;
        bool _containsText = false;
        bool _containsLayout = false;

        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);

        aStream->setContext(FSStream::ColorContainsAlpha, 1);

        bounds.decodeFromStream(aStream);

        _containsText = aStream->read(FSStream::UnsignedBit, 1) == 1;
        wordWrapped = aStream->read(FSStream::UnsignedBit, 1) == 1;
        multiline = aStream->read(FSStream::UnsignedBit, 1) == 1;
        password = aStream->read(FSStream::UnsignedBit, 1) == 1;
        readOnly = aStream->read(FSStream::UnsignedBit, 1) == 1;
        _containsColor = aStream->read(FSStream::UnsignedBit, 1) == 1;
        _containsMaxLength = aStream->read(FSStream::UnsignedBit, 1) == 1;
        _containsFont = aStream->read(FSStream::UnsignedBit, 1) == 1;
        aStream->read(FSStream::UnsignedBit, 2); // reserved1
        _containsLayout = aStream->read(FSStream::UnsignedBit, 1) == 1;
        selectable = aStream->read(FSStream::UnsignedBit, 1) == 1;
        bordered = aStream->read(FSStream::UnsignedBit, 1) == 1;
        aStream->read(FSStream::UnsignedBit, 1); // reserved2
        html = aStream->read(FSStream::UnsignedBit, 1) == 1;
        outlined = aStream->read(FSStream::UnsignedBit, 1) == 1;
        
        if (_containsFont)
        {
             fontId = aStream->read(FSStream::UnsignedWord, 16);
             fontHeight = aStream->read(FSStream::UnsignedWord, 16);
        }
        else
        {
             aStream->read(FSStream::UnsignedWord, 0);
             aStream->read(FSStream::UnsignedWord, 0);
        }

        if (_containsColor)
            color.decodeFromStream(aStream);
        else
             aStream->read(FSStream::UnsignedWord, 0);

        if (_containsMaxLength)
            maxLength = aStream->read(FSStream::UnsignedWord, 16);
        else
             aStream->read(FSStream::UnsignedWord, 0);

        if (_containsLayout)
        {
            alignment = aStream->read(FSStream::UnsignedWord, 8);
            leftMargin = aStream->read(FSStream::UnsignedWord, 16);
            rightMargin = aStream->read(FSStream::UnsignedWord, 16);
            indent = aStream->read(FSStream::UnsignedWord, 16);
            leading = aStream->read(FSStream::UnsignedWord, 16);
        }
        else
        {
            aStream->read(FSStream::UnsignedWord, 0);
            aStream->read(FSStream::UnsignedWord, 0);
            aStream->read(FSStream::UnsignedWord, 0);
            aStream->read(FSStream::UnsignedWord, 0);
            aStream->read(FSStream::UnsignedWord, 0);
        }

        const char* vstr = aStream->readString();
        
        variableName = vstr;
        delete [] vstr;

        if (_containsText)
        {
            const char* istr = aStream->readString();
            
            initialText = istr;
            delete [] istr;
        }

        aStream->setContext(FSStream::ColorContainsAlpha, 0);
        
        aStream->endDecoding(className());
    }
    
    bool FSDefineTextField::containsFont() const
    {
        return fontId != 0 && fontHeight != 0;
    }
    
    bool FSDefineTextField::containsMaxLength() const
    {
        return maxLength > 0;
    }
    
    bool FSDefineTextField::containsLayoutInfo() const
    {
        bool layout = false;
        
        layout = alignment != LeftAlign;
        layout = layout || leftMargin != 0;
        layout = layout || rightMargin != 0;
        layout = layout || indent != 0;
        layout = layout || leading != 0;
        
        return layout;
    }

    bool FSDefineTextField::containsText() const
    {
        return initialText.length() > 0;
    }
}
