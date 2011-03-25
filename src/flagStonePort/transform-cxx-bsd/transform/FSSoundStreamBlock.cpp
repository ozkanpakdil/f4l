/*
 *  FSSoundStreamBlock.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 10 2003.
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

#include "FSSoundStreamBlock.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSException.h"

using namespace transform;

namespace transform
{
    FSSoundStreamBlock::FSSoundStreamBlock(FSInputStream* aStream) :
        FSMovieObject(SoundStreamBlock),
        soundData(0)
    {
        decodeFromStream(aStream);
    }

    FSSoundStreamBlock::FSSoundStreamBlock(const FSSoundStreamBlock& rhs) :
        FSMovieObject(rhs),
        soundData(0)
    {
        if (rhs.soundData)
        {
            soundData = new byte[length];

            if (length > 0 && soundData == 0)
                throw FSAllocationException("Cannot allocate memory to copy an FSSoundStreamBlock.");

            for (int i=0; i<length; i++)
                soundData[i] = rhs.soundData[i];
        }
    }

     FSSoundStreamBlock::~FSSoundStreamBlock()
    {
        delete [] soundData;
        soundData = 0;
    }

    const char* FSSoundStreamBlock::className() const
    {
        const static char _name[] = "FSSoundStreamBlock";

        return _name;
    }

    FSSoundStreamBlock& FSSoundStreamBlock::operator= (const FSSoundStreamBlock& rhs)
    {
        if (this != &rhs)
        {
            this->FSMovieObject::operator=(rhs);
            
            delete [] soundData;
            
            soundData = new byte[length];

            if (length > 0 && soundData == 0)
                throw FSAllocationException("Cannot allocate memory to copy an FSSoundStreamBlock.");

            for (int i=0; i<length; i++)
                soundData[i] = rhs.soundData[i];
        }
        return *this;
    }
    
    int FSSoundStreamBlock::lengthInStream(FSOutputStream* aStream)
    {
        return length;
    }
    
    void FSSoundStreamBlock::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        aStream->write(soundData, length);

        aStream->endEncoding(className());
    }
    
    void FSSoundStreamBlock::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

        soundData = aStream->read(length);

        aStream->endDecoding(className());
    }
}
