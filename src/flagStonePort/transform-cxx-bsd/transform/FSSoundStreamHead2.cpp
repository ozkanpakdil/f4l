/*
 *  FSSoundStreamHead2.cpp
 *  Transform SWF
 *
 *  Created by smackay on Sat Mar 29 2003.
 *  Copyright (c) 2001-2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file is part of the Transform SWF library. You may not use this file except in
 *  compliance with the terms of the license (the 'License') that accompanied this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an 
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone 
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY 
 *  RIGHTS. Please see the License for the specific language governing rights and limitations 
 *  under the License.
 */

#include "FSSoundStreamHead2.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSSound.h"

using namespace transform;

namespace transform
{
    FSSoundStreamHead2::FSSoundStreamHead2(FSInputStream* aStream) :
        FSMovieObject(SoundStreamHead),
        format(FSSound::NATIVE_PCM),
        playbackRate(0),
        playbackChannels(0),
        playbackSampleSize(0),
        streamRate(0),
        streamChannels(0),
        streamSampleSize(0),
        streamSampleCount(0),
        latency(0)
    {
            decodeFromStream(aStream);
    }
    
    const char* FSSoundStreamHead2::className() const
    {
        const static char _name[] = "FSSoundStreamHead2";
    
        return _name;
    }
    
    int FSSoundStreamHead2::lengthInStream(FSOutputStream* aStream)
    {
        FSMovieObject::lengthInStream(aStream);
    
        length += 4;

        if (format == FSSound::MP3)
            length += 2;
            
        return length;
    }
    
    void FSSoundStreamHead2::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSMovieObject::encodeToStream(aStream);

        aStream->write(0, FSStream::UnsignedBit, 4);

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
        aStream->write(playbackSampleSize+1, FSStream::UnsignedBit, 1);
        aStream->write(playbackChannels+1, FSStream::UnsignedBit, 1);

        aStream->write(format, FSStream::UnsignedBit, 4);

        switch (streamRate)
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
        aStream->write(streamSampleSize+1, FSStream::UnsignedBit, 1);
        aStream->write(streamChannels+1, FSStream::UnsignedBit, 1);
        aStream->write(streamSampleCount, FSStream::UnsignedWord, 16);
        
        if (format == FSSound::MP3)
            aStream->write(latency, FSStream::UnsignedWord, 16);

        aStream->endEncoding(className());
    }
    
    void FSSoundStreamHead2::decodeFromStream(FSInputStream* aStream)
    {
        aStream->startDecoding(className());
        FSMovieObject::decodeFromStream(aStream);

        aStream->read(FSStream::UnsignedBit, 4);

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
        playbackSampleSize = aStream->read(FSStream::UnsignedBit, 1)+1;
        playbackChannels = aStream->read(FSStream::UnsignedBit, 1)+1;

        format = aStream->read(FSStream::UnsignedBit, 4);

        switch (aStream->read(FSStream::UnsignedBit, 2))
        {
            case 0:
                streamRate = 5512;
                break;
            case 1:
                streamRate = 11025;
                break;
            case 2:
                streamRate = 22050;
                break;
            case 3:
                streamRate = 44100;
                break;
        }
        streamSampleSize = aStream->read(FSStream::UnsignedBit, 1)+1;
        streamChannels = aStream->read(FSStream::UnsignedBit, 1)+1;
        streamSampleCount = aStream->read(FSStream::UnsignedWord, 16);
        
        if (format == FSSound::MP3)
            latency = aStream->read(FSStream::UnsignedWord, 16);

        aStream->endDecoding(className());
    }
}
