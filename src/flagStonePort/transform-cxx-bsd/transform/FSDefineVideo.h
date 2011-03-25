/*
 *  FSDefineVideo.h
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

#ifndef __FSDefineVideo_h__
#define __FSDefineVideo_h__ 1

#include "FSDefineObject.h"

#include "FSException.h"

namespace transform
{
	/**
	 * The %FSDefineVideo class is used to display video within a Flash file. 
	 * 
<p>Video objects contain a unique identifier and are treated in the same way as shapes, buttons, images, etc. The video data displayed is define using the FSVideoFrame class. Each frame of video is displayed whenever display list is updated using the FSShowFrame object - any timing information stored within the video data is ignored.</p>

<p>An FSDefineVideo is defined with the following information:</p>
 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSDefineVideo_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSDefineVideo_1">identifier</a></td>
<td>A unique identifier, in the range 1..65535, that is used to reference the video 
from other objects, e.g. when adding or removing from the display list.</td>
</tr>

<tr>
<td><a name="FSDefineVideo_2">frameCount</a></td>
<td>The number of frames that will be displayed.</td>
</tr>

<tr>
<td><a name="FSDefineVideo_3">width</a></td>
<td>Width of each frame in pixels</td>
</tr>

<tr>
<td><a name="FSDefineVideo_4">height</a></td>
<td>Height of each frame in pixels.</td>
</tr>

<tr>
<td><a name="FSDefineVideo_5">deblocking</a></td>
<td>Whether a filter is used when assembling the blocks of video data into a frame. 
This may be set to Off to turn off the deblock filter in the Flash Player; On to 
turn on the Flash Player's filter or UseVideo to allow the video data to specify 
whether the deblocking filter is used.</td>
</tr>

<tr>
<td><a name="FSDefineVideo_6">smoothing</a></td>
<td>Controls whether the Plash Player performs smoothing to increase the quality 
of the image displayed albeit at the price of performance.</td>
</tr>

<tr
><td><a name="FSDefineVideo_7">codec</a></td>
<td>Identifies the format of the video data either FSDefineVideo.H263 for data encoded 
using the Sorenson modified H263 format or FSDefineVideo.ScreenVideo for data 
encoded using Macromedia's Screen Video format.</td>
</tr>
</table>

<p>The ScreenVideo format was introduced in Flash 7, only the H263 format was supported in Flash 6.</p>

<h1 class="datasheet">History</h1>

<p>The FSDefineVideo class represents the DefineVideo of the Macromedia Flash (SWF) 
File Format Specification. It was introduced in Flash 6. The ScreenVideo format 
was introduced in Flash 7.</p>

	 */  
    class DLL_DECL FSDefineVideo : public FSDefineObject
    {
public:
		enum videoType {
			H263 = 2,  // Video data was encoded using the Sorenson modified H263 format.
			ScreenVideo = 3 // Video data was encoded using Macromedia's ScreenVideo format.
		};

		enum deblockingType {
			UseVideo = 0, // Instruct the Flash Player to use the deblocking value specified in the video data.
			Off = 1, // Instruct the Flash Player to turn the deblocking filter off.
			On = 2 // Instruct the Flash Player to turn the deblocking filter on. 
		};
		
		FSDefineVideo(FSInputStream* aStream);

		/**
		 * Constructs an FSDefineVideo object with the specified parameters.
		 *
		 * @param anIdentifier	the unique identifier for this object
		 * @param frameCount the number of video frames.
		 * @param frameWidth the width of each frame in pixels.
		 * @param frameHeight the height of each frame in pixels.
		 * @param deblock controls whether the Flash Player's deblocking filter is used, either Off, On or UseVideo to allow the video data to specify whether the deblocking filter is used. 
		 * @param smooth turns smoothing on or off to improve the quality of the displayed image.
		 * @param videoCodec the format of the video data. Flash 6 supports FSDefineVideo::H263. Support for Macromedia's 
		 * ScreenVideo format was added in Flash 7.
		 */
		FSDefineVideo(int anIdentifier, int frameCount, int frameWidth, int frameHeight, int deblock, bool smooth, int videoCodec) : 
			FSDefineObject(DefineVideo, anIdentifier),
			count(frameCount),
			width(frameWidth),
			height(frameHeight),
			deblocking(deblock),
			smoothing(smooth),
			codec(videoCodec)
			{}

		FSDefineVideo* clone() const { return new FSDefineVideo(*this); }

        const char* className() const;

		/**
		 * Gets the number of frames in the video.
		 * 
		 * @return the number of video frames.
		 */ 
		int getFrameCount() { return count; }

		/**
		 * Sets the number of frames in the video.
		 * 
		 * @param frameCount the number of video frames.
		 */ 
		void setFrameCount(int frameCount) { count = frameCount; }
	    
		/**
	 	 * Gets the width of each frame in pixels.
		 * 
		 * @return the width of the frame.
		 */ 
		int getWidth() { return width; }

		/**
		 * Sets the width of each frame in pixels.
		 * 
		 * @param frameWidth the width of the frame.
		 */ 
		void setWidth(int frameWidth) { width = frameWidth; }
	    
		/**
		 * Gets the height of each frame in pixels.
		 * 
		 * @return the height of the frame.
		 */ 
		int getHeight() { return height; }

		/**
		 * Sets the height of each frame in pixels.
		 * 
		 * @param frameHeight the height of the frame.
		 */ 
		void setHeight(int frameHeight) { height = frameHeight; }
	    
		/**
		 * Gets the method used to control the Flash Player's deblocking filter.
		 * 
		 * @return the deblocking filter control, either FSDefineVideo::Off, FSDefineVideo::On or
		 * FSDefineVideo::UseVideo to allow the video data to specify wherther the deblocking 
		 * filter is used.
		 */ 
		int getDeblocking() { return deblocking; }

		/**
		 * Sets the method used to control the Flash Player's deblocking filter.
		 * 
		 * @param deblock the deblocking filter control, either FSDefineVideo::Off, FSDefineVideo::On
		 * or FSDefineVideo::UseVideo to allow the video data to specify wherther the deblocking filter 
		 * is used.
		 */ 
		void setDeblocking(int deblock) { deblocking = deblock; }

		/**
		 * Gets the method used to control Flash Player's smoothing filter.
		 * 
		 * @return true if smoothing is turned on, false if it is turned off.
		 */
		bool getSmoothing() { return smoothing; }

		/**
		 * Sets the method used to control Flash Player's smoothing filter.
		 * 
		 * @param smooth true if smoothing is turned on, false if it is turned off.
		 */
		void setSmoothing(bool smooth) { smoothing = smooth; }

		/**
		 * Get the format used to encode the video data, either FSDefineVideo::H263 for data 
		 * encoded using the Sorenson modified H263 format or FSDefineVideo::ScreenVideo (Flash 7 only) 
		 * for data encoded using Macromedia's Screen Video format.
		 *
		 * @return the codec used to encode the video, either FSDefineVideo::H263 or FSDefineVideo::ScreenVideo.
		 */
		int getCodec() { return codec; }

		/**
		 * Set the format used to encode the video data, either FSDefineVideo::H263 for data encoded 
		 * using the Sorenson modified H263 format or FSDefineVideo::ScreenVideo (Flash 7 only) for 
		 * data encoded using Macromedia's Screen Video format.
		 *
		 * @param videoCodec the format used encode the video, either FSDefineVideo::H263 or FSDefineVideo::ScreenVideo.
		 */
		void setCodec(int videoCodec) { codec = videoCodec; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
		int count;
		int width;
		int height;
		int deblocking;
		bool smoothing;
		int codec;
    };
}

#endif
