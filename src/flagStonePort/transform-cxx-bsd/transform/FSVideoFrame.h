/*
 *  FSVideoFrame.h
 *  Transform SWF
 * 
 * Copyright (c) 2001-2004 Flagstone Software Ltd.. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *  * Neither the name of Flagstone Software Ltd. nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#pragma warning( disable : 4290 )

#ifndef __FSVideoFrame_h__
#define __FSVideoFrame_h__ 1

#include "FSMovieObject.h"

#include "FSException.h"

namespace transform
{
	/**
	 * %FSVideoFrame contains the video data displayed in a single frame of a Flash movie.
	 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSVideoFrame_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSVideoFrame_1">identifier</a></td>
<td>The identifier of the FSDefineVideo object that defines the size of the images displayed.</td>
</tr>

<tr>
<td><a name="FSVideoFrame_1">frameNumber</a></td>
<td>The number of the frame that the data is for.</td>
</tr>

<tr>
<td><a name="FSVideoFrame_1">data</a></td>
<td>The encoded video data. Encoded using either the modified Sorenson H263 or Macromedia's Screen Video formats.</td>
</tr>

</table>

<p>Each frame of video is displayed whenever display list is updated using the FSShowFrame object - any timing information stored within the video data is ignored. Since the video is updated at the same time as the display list the frame rate of the video may be the same or less than the frame rate of the Flash movie but not higher.</p>

<h1 class="datasheet">History</h1>

<p>The FSVideoFrame class represents the VideoFrame data structure in the Macromedia Flash (SWF) File Format Specification. It was added in Flash 6 with support for the Sorenson modified H263 format. Support for Macromedia's Screen Video format was added in Flash 7.</p>

	 */  
    class DLL_DECL FSVideoFrame : public FSMovieObject
    {
public:
        FSVideoFrame(FSInputStream* aStream);

		/**
		 * Constructs a new FSVideoFrame object which will display the specified frame of video data
		 * in the FSDefineVideo object that matches the identifier. 
		 *
		 * @param anIdentifier the unique identifier of the FSDefineVideo object.
		 * @param frameNumber the number of the frame.
		 * @param bytes the encoded video data. For Flash 6 this is encoded in the H263 format. In Flash 7
		 * H263 and ScreenVideo is supported.
		 * @param size the number of bytes in the encoded video data.
		 */
        FSVideoFrame(int anIdentifier, int frameNumber, byte* bytes, size_t size) : 
			FSMovieObject(VideoFrame), 
			identifier(anIdentifier), 
			frame(frameNumber), 
			video(bytes),
			videoSize(size)
        {
        }

        FSVideoFrame(const FSVideoFrame& rhs);

        ~FSVideoFrame();

        FSVideoFrame& operator= (const FSVideoFrame& rhs);

        FSVideoFrame* clone() const { return new FSVideoFrame(*this); }

        const char* className() const;

		/**
		 * Get the identifier of the FSDefineVideo object where the frame will be displayed.
		 *
		 * @return the unique identifier of the FSDefineVideo object.
		 */
		int getIdentifier() { return identifier; }

		/**
		 * Sets the identifier of the FSDefineVideo object where the frame will be displayed.
		 *
		 * @param anIdentifier the unique identifier of the FSDefineVideo object.
		 */
		void setIdentifier(int anIdentifier) { identifier = anIdentifier; }
	    
		/**
		 * Gets the number of the frame.
		 *
		 * @return the frame number.
		 */
		int getFrameNumber() { return frame; }

		/**
		 * Sets the number of the frame.
		 *
		 * @param frameNumber the frame number.
		 */
		void setFrameNumber(int frameNumber) { frame = frameNumber; }
	    
		/**
		 * Gets the encoded video data. In Flash 6 modified H263 encoded video is supported. Flash 7 supports 
		 * both modified H263 and ScreenVideo.
		 *
		 * @return the encoded video data.
		 */
        byte* getVideo() { return video; }

		/**
		 * Gets the number of bytes in the encoded video data.
		 *
		 * @return the size of the encoded video in bytes.
		 */
        size_t getVideoSize() { return videoSize; }

        /**
		 * Sets the encoded video data. In Flash 6 modified H263 encoded video is supported. Flash 7 supports 
		 * both modified H263 and ScreenVideo

            @param bytes byte array containing zlib compressed colour table and image.
            @param size the number of bytes in the zlib compressed colour table and image.
            */
        void setVideo(byte* bytes, size_t size)
        {
            delete [] video;
            
            video = bytes;
            videoSize = size;
        }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int identifier;
        int frame;

        byte* video;
        size_t videoSize;
    };
}

#endif
