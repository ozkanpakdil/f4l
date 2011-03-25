/*
 *  FSButtonSound.cpp
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

#include "FSButtonSound.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

#include "FSButtonEvent.h"

using namespace transform;

namespace transform
{
    FSButtonSound::FSButtonSound(FSInputStream* aStream) :
        FSMovieObject(DefineButtonSound), identifier(0)
    {
        decodeFromStream(aStream);
    }

    FSButtonSound::FSButtonSound(int anIdentifier, int eventCode, const FSSound& aSound) :
        FSMovieObject(DefineButtonSound), identifier(anIdentifier)
    {
        setSoundForEvent(eventCode, aSound);
    }

    const char* FSButtonSound::className() const
    {
        const static char _name[] = "FSButtonSound";

        return _name;
    }

    FSSound& FSButtonSound::getSoundForEvent(int eventCode)
    {
        if (eventCode == FSButtonEvent::RollOver)
            return sound[0];
        else if (eventCode == FSButtonEvent::RollOut)
            return sound[1];
        else if (eventCode == FSButtonEvent::Press)
            return sound[2];
            
        return sound[3];
    }
    
    void FSButtonSound::setSoundForEvent(int eventCode, const FSSound& aSound)
    {
        if (eventCode == FSButtonEvent::RollOver)
            sound[0] = aSound;
        else if (eventCode == FSButtonEvent::RollOut)
            sound[1] = aSound;
        else if (eventCode == FSButtonEvent::Press)
            sound[2] = aSound;
        else
            sound[3] = aSound;
    }

    int FSButtonSound::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);
    
        length += 2;

        for (int i=0; i<4; i++)
        {
            if (sound[i].getIdentifier() != 0)
                length += sound[i].lengthInStream(aStream);
            else
                length += 2;
        }
        return length;
    }

    void FSButtonSound::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
        FSMovieObject::encodeToStream(aStream);
        
        aStream->write(identifier, FSStream::UnsignedWord, 16);

        for (int i=0; i<4; i++)
        {
            if (sound[i].getIdentifier() != 0)
                sound[i].encodeToStream(aStream);
            else
                aStream->write(0, FSStream::UnsignedWord, 16);
        }
#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSButtonSound::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSMovieObject::decodeFromStream(aStream);

        identifier = aStream->read(FSStream::UnsignedWord, 16);

        for (int i=0; i<4; i++)
        {
            if (aStream->scan(FSStream::UnsignedWord, 16))
            {
                aStream->setCursor(aStream->getCursor()-16);

                sound[i].decodeFromStream(aStream);
            }
        }
#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
