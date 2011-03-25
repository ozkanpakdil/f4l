/*
 *  FSColor.cpp
 *  Transform SWF
 *
 *  Created by smackay on Tue Feb 18 2003.
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

#include "FSColor.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSColor::FSColor(FSInputStream* aStream) :
        red(Transform::VALUE_NOT_SET),
        green(Transform::VALUE_NOT_SET),
        blue(Transform::VALUE_NOT_SET),
        alpha(Transform::VALUE_NOT_SET)
    {
        decodeFromStream(aStream);
    }    

    FSColor::FSColor() :
        red(Transform::VALUE_NOT_SET),
        green(Transform::VALUE_NOT_SET),
        blue(Transform::VALUE_NOT_SET),
        alpha(Transform::VALUE_NOT_SET)
    {
    }
    
    FSColor* FSColor::clone() const
    {
        return new FSColor(*this);
    }
    
    const char* FSColor::className() const
    {
        const static char _name[] = "FSColor";

        return _name;
    }

    bool FSColor::containsColor() const
    {
        bool containsRed = red != Transform::VALUE_NOT_SET;
        bool containsGreen = green != Transform::VALUE_NOT_SET;
        bool containsBlue = blue != Transform::VALUE_NOT_SET;
        bool containsAlpha = alpha != Transform::VALUE_NOT_SET;

        return containsRed || containsGreen || containsBlue || containsAlpha;
    }
    
    int FSColor::lengthInStream(FSOutputStream* aStream)
    {
        return aStream->getContext(FSStream::ColorContainsAlpha) ? 4 : 3;
    }
    
    void FSColor::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */
            
        aStream->write(red, FSStream::UnsignedWord, 8);
        aStream->write(green, FSStream::UnsignedWord, 8);
        aStream->write(blue, FSStream::UnsignedWord, 8);
    
        if (aStream->getContext(FSStream::ColorContainsAlpha))
            aStream->write(alpha, FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSColor::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        red = aStream->read(FSStream::UnsignedWord, 8);
        green = aStream->read(FSStream::UnsignedWord, 8);
        blue = aStream->read(FSStream::UnsignedWord, 8);
        
        if (aStream->getContext(FSStream::ColorContainsAlpha))
            alpha = aStream->read(FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}