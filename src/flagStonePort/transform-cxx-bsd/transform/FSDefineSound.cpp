/*
 *  FSDefineSound.cpp
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

#include "FSDefineSound.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSSound.h"

using namespace transform;

namespace transform
{
    FSDefineSound::FSDefineSound(FSInputStream* aStream) :
        FSDefineObject(DefineSound, 0),
        format(0),
        playbackRate(0),
        playbackChannels(0),
        playbackSampleSize(0),
        sampleCount(0),
        soundLength(0),
        sound(0)
    {
        decodeFromStream(aStream);
    }

    FSDefineSound::FSDefineSound(int anIdentifier, int encoding, int rate, int channels, int sampleSize, int count, byte* bytes, size_t length) : 
        FSDefineObject(DefineSound, anIdentifier), 
        format(encoding), 
        playbackRate(rate), 
        playbackChannels(channels), 
        playbackSampleSize(sampleSize), 
        sampleCount(count), 
        soundLength(length), 
        sound(bytes) 
    {}

    FSDefineSound::FSDefineSound(const FSDefineSound& rhs) :
        FSDefineObject(rhs),
        format(rhs.format),
        playbackRate(rhs.playbackRate),
        playbackChannels(rhs.playbackChannels),
        playbackSampleSize(rhs.playbackSampleSize),
        sampleCount(rhs.sampleCount),
        soundLength(rhs.soundLength),
        sound(0)
    {
        sound = new byte[soundLength];

        if (soundLength > 0 && sound == 0)
            throw FSAllocationException("Could not allocate memory to copy sound data.");
        
        memcpy(sound, rhs.sound, soundLength*sizeof(byte));
    }
    
    FSDefineSound::~FSDefineSound()
    {
        delete [] sound;
        sound = 0;
    }

    FSDefineSound* FSDefineSound::clone() const
    {
        return new FSDefineSound(*this);
    }
    
    const char* FSDefineSound::className() const
    {
        const static char _name[] = "FSDefineSound";

        return _name;
    }

    FSDefineSound& FSDefineSound::operator= (const FSDefineSound& rhs)
    {
        if (this != &rhs)
        {
            this->FSDefineObject::operator=(rhs);

            format = rhs.format;

            playbackRate = rhs.playbackRate;
            playbackChannels = rhs.playbackChannels;
            playbackSampleSize = rhs.playbackSampleSize;

            sampleCount = rhs.sampleCount;
            soundLength = rhs.soundLength;

            delete [] sound;

            sound = new byte[soundLength];

            if (soundLength > 0 && sound == 0)
                throw FSAllocationException("Could not allocate memory to copy sound data.");

            memcpy(sound, rhs.sound, soundLength*sizeof(byte));
        }
        return *this;
    }

    int FSDefineSound::lengthInStream(FSOutputStream* aStream)
    {
        FSDefineObject::lengthInStream(aStream);
    
        length += 5;
        length += soundLength;
        
        return length;
    }
    
    void FSDefineSound::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);
        
        aStream->write(format, FSStream::UnsignedBit, 4);

        switch (playbackRate)
        {
            case 5512:
                aStream->write(0, FSStream::UnsignedBit, 2);
                break;
            case 11025:
                aStream->write(1, FSStream::UnsignedBit, 2);
                break;
            case 22050:
                aStream->write(2, FSStream::UnsignedBit, 2);
                break;
            case 44100:
                aStream->write(3, FSStream::UnsignedBit, 2);
                break;
        }
        aStream->write(playbackSampleSize-1, FSStream::UnsignedBit, 1);
        aStream->write(playbackChannels-1, FSStream::UnsignedBit, 1);
        aStream->write(sampleCount, FSStream::UnsignedWord, 32);
        aStream->write(sound, soundLength);

        aStream->endEncoding(className());
    }
    
    void FSDefineSound::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);
        
        format = aStream->read(FSStream::UnsignedBit, 4);

        switch (aStream->read(FSStream::UnsignedBit, 2))
        {
            case 0:
                playbackRate = 5512;
                break;
            case 1:
                playbackRate = 11025;
                break;
            case 2:
                playbackRate = 22050;
                break;
            case 3:
                playbackRate = 44100;
                break;
        }
        
        playbackSampleSize = aStream->read(FSStream::UnsignedBit, 1) + 1;
        playbackChannels = aStream->read(FSStream::UnsignedBit, 1) + 1;
        sampleCount = aStream->read(FSStream::UnsignedWord, 32);

        soundLength = getLength()-7;
        sound = aStream->read(soundLength);

        aStream->endDecoding(className());
    }
}
