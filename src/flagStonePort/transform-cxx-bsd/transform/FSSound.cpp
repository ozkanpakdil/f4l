/*
 *  FSSound.cpp
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

#include "FSSound.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSSound::FSSound(FSInputStream* aStream) :
        identifier(0),
        mode(Stop),
        inPoint(0),
        outPoint(0),
        loopCount(0),
        envelopes()
    {
        decodeFromStream(aStream);
    }

    const char* FSSound::className() const
    {
        const static char _name[] = "FSSound";

        return _name;
    }

    void FSSound::add(const FSVector<FSEnvelope>& anArray)
    {
        for (FSVector<FSEnvelope>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            envelopes.push_back(*i);
    }
    
    int FSSound::lengthInStream(FSOutputStream* aStream)
    {
        bool _containsInPoint = containsInPoint();
        bool _containsOutPoint = containsOutPoint();
        bool _containsLoopCount = containsLoopCount();
        bool _containsEnvelopes = containsEnvelopes();
        
        int tagLength = 3;

        tagLength += (_containsInPoint) ? 4 : 0;
        tagLength += (_containsOutPoint) ? 4 : 0;
        tagLength += (_containsLoopCount) ? 2 : 0;
        tagLength += (_containsEnvelopes) ? 1 : 0;
        tagLength += (_containsEnvelopes) ? ((int)(envelopes.size()))*8 : 0;
    
        return tagLength;
    }
    
    void FSSound::encodeToStream(FSOutputStream* aStream)
    {
        bool _containsInPoint = containsInPoint();
        bool _containsOutPoint = containsOutPoint();
        bool _containsLoopCount = containsLoopCount();
        bool _containsEnvelopes = containsEnvelopes();
        
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        /*
         * The parent object decides whether to perform validation.
         */

        aStream->write(identifier, FSStream::UnsignedWord, 16);
        aStream->write(mode, FSStream::UnsignedBit, 4);
        aStream->write(_containsEnvelopes ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(_containsLoopCount ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(_containsOutPoint ? 1 : 0, FSStream::UnsignedBit, 1);
        aStream->write(_containsInPoint ? 1 : 0, FSStream::UnsignedBit, 1);
    
        if (_containsInPoint)
            aStream->write(inPoint, FSStream::UnsignedWord, 32);
        if (_containsOutPoint)
            aStream->write(outPoint, FSStream::UnsignedWord, 32);
        if (_containsLoopCount)
            aStream->write(loopCount, FSStream::UnsignedWord, 16);
        if (_containsEnvelopes)
        {
            aStream->write((int)(envelopes.size()), FSStream::UnsignedWord, 8);

#ifdef _DEBUG
            aStream->startEncoding("array");
#endif
            for (FSVector<FSEnvelope>::iterator i = envelopes.begin(); i != envelopes.end(); ++i)
                (*i).encodeToStream(aStream);
#ifdef _DEBUG
            aStream->endEncoding("array");
#endif
        }
#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSSound::decodeFromStream(FSInputStream* aStream)
    {
        bool _containsInPoint = false;
        bool _containsOutPoint = false;
        bool _containsLoopCount = false;
        bool _containsEnvelopes = false;
        
        int envelopeCount = 0;

#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        identifier = aStream->read(FSStream::UnsignedWord, 16);
        mode = aStream->read(FSStream::UnsignedBit, 4);
        _containsEnvelopes = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        _containsLoopCount = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        _containsOutPoint = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        _containsInPoint = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
    
        if (_containsInPoint)
            inPoint = aStream->read(FSStream::UnsignedWord, 32);
        else
            aStream->read(FSStream::UnsignedWord, 0);
            
        if (_containsOutPoint)
            outPoint = aStream->read(FSStream::UnsignedWord, 32);
        else
            aStream->read(FSStream::UnsignedWord, 0);
            
        if (_containsLoopCount)
            loopCount = aStream->read(FSStream::UnsignedWord, 16);
        else
            aStream->read(FSStream::UnsignedWord, 0);
            
        if (_containsEnvelopes)
        {
            envelopeCount = aStream->read(FSStream::UnsignedWord, 8);

#ifdef _DEBUG
            aStream->startDecoding("array");
#endif
            for (int i=0; i<envelopeCount; i++)
                envelopes.push_back(FSEnvelope(aStream));

#ifdef _DEBUG
            aStream->endDecoding("array");
#endif
        }
#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }

    bool FSSound::containsInPoint() const
    {
        return inPoint != 0;
    }

    bool FSSound::containsOutPoint() const
    {
        return outPoint != 0;
    }
    
    bool FSSound::containsLoopCount() const
    {
        return loopCount != 0;
    }

    bool FSSound::containsEnvelopes() const
    {
        return envelopes.size() > 0;
    }
}
