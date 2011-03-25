/*
 *  FSVideoFrame.cpp
 *  Transform SWF
 *
 *  Created by smackay on Fri Apr 30 2004.
 *  Copyright (c) 2001-2004 Flagstone Software Ltd. All rights reserved.
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

#include "FSVideoFrame.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
	FSVideoFrame::FSVideoFrame(FSInputStream* aStream) :
        FSMovieObject(VideoFrame),
        identifier(0),
        frame(0),
        video(0),
        videoSize(0)
	{
		decodeFromStream(aStream);
	}

    FSVideoFrame::FSVideoFrame(const FSVideoFrame& rhs) :
        FSMovieObject(rhs),
        identifier(rhs.identifier),
        frame(rhs.frame),
        video(0),
        videoSize(rhs.videoSize)
    {
        video = new byte[videoSize];

        if (videoSize > 0 && video == 0)
            throw FSAllocationException();

        for (unsigned int i=0; i<videoSize; i++)
           video[i] = rhs.video[i];
    }

    FSVideoFrame::~FSVideoFrame()
    {
        delete [] video;
        video = 0;
    }

    const char* FSVideoFrame::className() const
    {
        const static char _name[] = "FSVideoFrame";

        return _name;
    }

    FSVideoFrame& FSVideoFrame::operator= (const FSVideoFrame& rhs)
    {
        if (this != &rhs)
        {
            this->FSMovieObject::operator=(rhs);
            
            identifier = rhs.identifier;
            frame = rhs.frame;

			videoSize = rhs.videoSize;

            delete [] video;

            video = new byte[videoSize];

            if (videoSize > 0 && video == 0)
                throw FSAllocationException();

            for (unsigned int i=0; i<videoSize; i++)
                video[i] = rhs.video[i];
        }
        return *this;
    }

	int FSVideoFrame::lengthInStream(FSOutputStream* aStream)
	{
		FSMovieObject::lengthInStream(aStream);

		length += 4 + videoSize;

		return length;
	}
	
	void FSVideoFrame::encodeToStream(FSOutputStream* aStream)
	{
        aStream->startEncoding(className());
		FSMovieObject::encodeToStream(aStream);
	
		aStream->write(identifier, FSStream::UnsignedWord, 16);
		aStream->write(frame, FSStream::UnsignedWord, 16);

		aStream->write(video, videoSize);

		aStream->endEncoding(className());
	}
	
	void FSVideoFrame::decodeFromStream(FSInputStream* aStream)
	{
        aStream->startDecoding(className());
		FSMovieObject::decodeFromStream(aStream);
		
		identifier = aStream->read(FSStream::UnsignedWord, 16);
		frame = aStream->read(FSStream::UnsignedWord, 16);

        videoSize = getLength() - 4;
        video = aStream->read(videoSize);

        aStream->endDecoding(className());
	}
}
