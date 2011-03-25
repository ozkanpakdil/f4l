/*
 *  FSGradientFill.cpp
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

#include "FSGradientFill.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSGradientFill::FSGradientFill(FSInputStream* aStream) :
        FSFillStyle(LinearGradient),
        transform(),
        gradients()
    {
        decodeFromStream(aStream);
    }
    
    const char* FSGradientFill::className() const
    {
        const static char _name[] = "FSGradientFill";

        return _name;
    }

    void FSGradientFill::add(const FSVector<FSGradient>& anArray)
    {
        for (FSVector<FSGradient>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            gradients.push_back(*i);
    }

    int FSGradientFill::lengthInStream(FSOutputStream* aStream)
    {
        int tagLength = FSFillStyle::lengthInStream(aStream);
    
        tagLength += transform.lengthInStream(aStream);
        tagLength += 1;

        for (FSVector<FSGradient>::iterator i = gradients.begin(); i != gradients.end(); ++i)
            tagLength += (*i).lengthInStream(aStream);

         return tagLength;
    }
    
    void FSGradientFill::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */
        FSFillStyle::encodeToStream(aStream);
        
        transform.encodeToStream(aStream);
        aStream->write((int)(gradients.size()), FSStream::UnsignedWord, 8);
    
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSGradient>::iterator i = gradients.begin(); i != gradients.end(); ++i)
            (*i).encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding("array");
        aStream->endEncoding(className());
#endif
    }
    
    void FSGradientFill::decodeFromStream(FSInputStream* aStream)
    {
        int count = 0;
        
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSFillStyle::decodeFromStream(aStream);
        
        transform.decodeFromStream(aStream);
        count = aStream->read(FSStream::UnsignedWord, 8);

#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        for (int i=0; i<count; i++)
            gradients.push_back(FSGradient(aStream));

#ifdef _DEBUG
        aStream->endDecoding("array");
        aStream->endDecoding(className());
#endif
    }
}
