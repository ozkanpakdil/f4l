/*
 *  FSEnvelope.h
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

#ifndef __FSEnvelope_h__
#define __FSEnvelope_h__ 1

#include "FSTransformObject.h"

namespace transform
{
/**
 * %FSEnvelope is used to define an envelope which controls how a particular sound is 
 * played over time. 
 * 
<p>Each FSEnvelope object defines a point in the envelope. The FSSound object contains an array of FSEnvelope objects which define the complete envelope.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSEnvelope_0">mark</a></td>
<td>The location in the playback sound data stream where the following level information applies.</td>
</tr>

<tr>
<td><a name="FSEnvelope_1">left</a></td>
<td>The sound level for the left channel, in the range 0..65535.</td>
</tr>

<tr>
<td><a name="FSEnvelope_2">right</a></td>
<td>The sound level for the right channel, in the range 0..65535..</td>
</tr>
</table>

<p>The Flash Player plays sounds at a fixed rate of 44.1KHz, therefore sounds sampled at a lower frequency are interpolated with each sample repeated to generated the 44.1Khz playback rate. For example each sample in a sound sampled at 22KHz is played twice to generated the 44.1Khz playback rate.</p>

<p>The envelope defines the sample number (and hence the time) in the playback data stream where the level information applies and <b>not</b> the sample number in the original sound data. For example to set the level 0.1 seconds into a sound that plays for 1 second the value for the mark attribute in the envelope object would be 44100 * 0.1/1.0 = 4410.</p>

<h1 class="datasheet">History</h1>

<p>The FSEnvelope class represents the SoundEnvelope structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSEnvelope : public FSTransformObject
    {
public:
        FSEnvelope(FSInputStream* aStream);

        FSEnvelope() : mark(0), left(0), right(0) {}

        /** Constructs an envelope specifying the mark, left and right values.

            @param markValue the sample number in the 44.1KHz playback data stream where the levels for the channels is applied.
            @param leftValue the level for the left sound channel.
            @param rightValue the level for the right sound channel.
            */
        FSEnvelope(int markValue, int leftValue, int rightValue) : mark(markValue), left(leftValue), right(rightValue) {}

        FSEnvelope* clone() const { return new FSEnvelope(*this); }

        const char* className() const;

        /** Gets the sample number in the 44.1KHz playback data stream where the level information is applied.

            @return the mark value.
            */
        int getMark() const { return mark; }

        /** Gets the level of the sound played in the left channel.

            @return the left value.
            */
        int getLeft() const { return left; }

        /** Gets the level of the sound played in the right channel.

            @return the right value.
            */
        int getRight() const { return right; }

        /** Sets the sample number in the 44.1KHz playback data stream where the levels for the channels is applied.

            @param aNumber the mark value.
            */
        void setMark(int aNumber) { mark = aNumber; }

        /** Sets the level for the left sound channel.

            @param aNumber the level for the left sound channel.
            */
        void setLeft(int aNumber) { left = aNumber; }

        /** Sets the level for the right sound channel.

            @param aNumber the level for the right sound channel.
            */
        void setRight(int aNumber) { right = aNumber; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
    
    private:
        int mark;
        int left;
        int right;
    };
} 

#endif

