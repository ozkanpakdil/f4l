/*
 *  FSMorphGradientFill.cpp
 *  Transform SWF
 *
 *  Created by smackay on Thu Feb 20 2003.
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

#include "FSMorphGradientFill.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSMorphGradientFill::FSMorphGradientFill(FSInputStream* aStream) :
        FSFillStyle(LinearGradient),
        startTransform(),
        endTransform(),
        gradients()
    {
        decodeFromStream(aStream);
    }
    
    const char* FSMorphGradientFill::className() const
    {
        const static char _name[] = "FSMorphGradientFill";

        return _name;
    }

    void FSMorphGradientFill::add(const FSVector<FSMorphGradient>& anArray)
    {
        for (FSVector<FSMorphGradient>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            gradients.push_back(*i);
    }
    
    int FSMorphGradientFill::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = FSFillStyle::lengthInStream(aStream);
    
        tagLength += startTransform.lengthInStream(aStream);
        tagLength += endTransform.lengthInStream(aStream);
        tagLength += 1;

        for (FSVector<FSMorphGradient>::iterator i = gradients.begin(); i != gradients.end(); ++i)
            tagLength += (*i).lengthInStream(aStream);

         return tagLength;
    }
    
    void FSMorphGradientFill::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */
        FSFillStyle::encodeToStream(aStream);
        
        startTransform.encodeToStream(aStream);
        endTransform.encodeToStream(aStream);
        
        aStream->write((int)(gradients.size()), FSStream::UnsignedWord, 8);
    
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSMorphGradient>::iterator i = gradients.begin(); i != gradients.end(); ++i)
            (*i).encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding("array");
        aStream->endEncoding(className());
#endif
    }
    
    void FSMorphGradientFill::decodeFromStream(FSInputStream* aStream)
    {
        int count = 0;
        
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSFillStyle::decodeFromStream(aStream);
        
        startTransform.decodeFromStream(aStream);
        endTransform.decodeFromStream(aStream);

        count = aStream->read(FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=0; i<count; i++)
            gradients.push_back(FSMorphGradient(aStream));

#ifdef _DEBUG
        aStream->endDecoding("array");
        aStream->endDecoding(className());
#endif
    }
}
