/*
 *  FSDefineSound.h
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

#ifndef __FSDefineSound_h__
#define __FSDefineSound_h__ 1

#include "FSDefineObject.h"
#include "FSSound.h"

namespace transform
{
/**
 * %FSDefineSound is used to define a sound that will be played when a given event occurs. 
 * 
<p>Three different types of object are used to play an event sound:</p>

<ul>
<li>The FSDefineSound object that contains the sampled sound.</li>
<li>A FSSound object that defines how the sound fades in and out, whether it repeats and also defines an envelope for more sophisticated control over how the sound is played.</li>
<li>A FSStartSound object that signals the Flash Player to begin playing the sound.</li>
</ul>

<p>An FSDefineSound object contains the following attributes:</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>


<tr><td><a name="FSDefineSound_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSDefineSound_1">identifier</a></td><td>An unique identifier for this object in the range 1..65535.</td></tr>

<tr>
<td>
<a name="FSDefineSound_2">format</a></td>
<td>The format of the sound data - FSSound.NATIVE_PCM, FSSound.ADPCM, FSSound.MP3, FSSound.PCM or FSSound.NELLYMOSER</td></tr>

<tr>
<td><a name="FSDefineSound_3">playbackRate</a></td>
<td>The rate the sound will be played in Hertz: 5512, 11025, 22050 or 44100</td>
</tr>

<tr>
<td><a name="FSDefineSound_4">playbackChannels</a></td>
<td>The number of channels in the sound, typically 1 (mono) or 2 (stereo).</td>
</tr>

<tr>
<td><a name="FSDefineSound_5">playbackSampleSize</a></td>
<td>The number of bytes in a sample: 1 or 2.</td>
</tr>

<tr>
<td><a name="FSDefineSound_6">sampleCount</a></td>
<td>The number of samples in the sound.</td>
</tr>

<tr>
<td><a name="FSDefineSound_7">soundLength</a></td>
<td>The number of bytes in the sound data.</td>
</tr>

<tr>
<td><a name="FSDefineSound_8">sound</a></td>
<td>The encoded sound data.</td>
</tr>

</table>

<p>Five encoded formats for the sound data are supported:</p>

<ul>
<li>NATIVE_PCM - uncompressed Pulse Code Modulated: samples are either 1 or 2 bytes. For two-byte samples the byte order is dependent on the platform on which the Flash Player is hosted. Sounds created on a platform which supports big-endian byte order will not be played correctly when listened to on a platform which supports little-endian byte order.</li>
<li>PCM - uncompressed Pulse Code Modulated: samples are either 1 or 2 bytes with 
the latter presented in Little-Endian byte order. This ensures that sounds can be played across different platforms.</li>
<li>ADPCM - compressed ADaptive Pulse Code Modulated: samples are encoded and compressed
by comparing the difference between successive sound sample which dramatically reduces
the size of the encoded sound when compared to the uncompressed PCM formats. Use this 
format whenever possible.</li>
<li>MP3 - compressed MPEG Audio Layer-3.</li>
<li>NELLYMOSER - compressed Nellymoser Asao format supporting low bit-rate sound for improving synchronisation between the sound and frame rate of movies.</li>
</ul>

<p>Constants representing the different formats are defined in the FSSound class.</p>

<h1 class="datasheet">History</h1>

<p>The FSDefineSound class represents the DefineSound structure from the Macromedia 
Flash (SWF) File Format Specification. It was introduced in Flash 1. Flash 3 added 
support for MP3 and the Nellymoser Asao format was added in Flash 6.</p>

 */  
    class DLL_DECL FSDefineSound : public FSDefineObject
    {
public:
        FSDefineSound(FSInputStream* aStream);

        /** Constructs an FSDefineSound object specifying the unique identifier and all the parameters required to describe the sound.
    
            @param anIdentifier the unique identifier for this sound.
            @param encoding the encoding format for the sound, either FSSound::NATIVE_PCM, FSSound::ADPCM, FSSound::MP3 or FSSound::PCM.
            @param rate the number of samples per second that the sound is played at , either 5512, 11025, 22050 or 44100.
            @param channels the number of channels in the sound, either 1 (Mono) or 2 (Stereo).
            @param sampleSize the size of an uncompressed sound sample in bits, either 8 or 16.
            @param count the number of samples in the sound data.
            @param bytes the sound data.
            @param length the number of bytes in the sound data.
            */
        FSDefineSound(int anIdentifier, int encoding, int rate, int channels, int sampleSize, int count, byte* bytes, size_t length);

        FSDefineSound(const FSDefineSound& rhs);

        ~FSDefineSound();

        FSDefineSound& operator= (const FSDefineSound& rhs);

        FSDefineSound* clone() const;

        const char* className() const;

        /** Gets the format used, either FSSound::NATIVE_PCM, FSSound::ADPCM, FSSound::MP3 or FSSound::PCM.

            @return the encoding format.
            */
        int getFormat() const { return format; }

        /** Gets the rate at which the sound will be played, in Hz: 5512, 11025, 22050 or 44100.

            @return the rate at which the sound will be played.
            */
        int getPlaybackRate() const { return playbackRate; }

        /** Gets the number of sound channels, 1 (Mono) or 2 (Stereo).

            @return the number of channels.
            */
        int getPlaybackChannels() const { return playbackChannels; }

        /** Gets the size of an uncompressed sample.

            @return the number of bytes per sample when the sound is uncompressed.
            */
        int getPlaybackSampleSize() const { return playbackSampleSize; }

        /** Gets the number of samples in the sound data.

            @return the number of samples.
            */
        int getSampleCount() { return sampleCount; }

        /** Gets the number of bytes in the sound data.

            @return the number of bytes in the sound data.
            */
        size_t getSoundLength() { return soundLength; }

        /** Gets the sound data.

            @return an array of bytes containing the sampled sound.
            */
        byte* getSound() const { return sound; }

        /** Sets the encoding format used, either FSSound::NATIVE_PCM, FSSound::ADPCM, FSSound::MP3 or FSSound::PCM.

            @param encoding the format for the sound.
            */
        void setFormat(int encoding) { format = encoding; }

        /** Sets the sampling rate in Hertz. Must be one of: 5512, 11025, 22050 or 44100.

            @param rate the rate at which the sounds is played in Hz.
            */
        void setPlaybackRate(int rate) { playbackRate = rate; }

        /** Sets the number of channels defined in the sound.

            @param channels the number of channels in the sound, either 1 (Mono) or 2 (Stereo).
            */
        void setPlaybackChannels(int channels) { playbackChannels = channels; }

        /** Sets the sample size in bytes. Must be either 1 or 2.

            @param sampleSize the size of sound samples in bytes.
            */
        void setPlaybackSampleSize(int sampleSize) { playbackSampleSize = sampleSize; }

        /** Sets the number of samples in the sound data.

            @param count the number of samples for the sound.
            */
        void setSampleCount(int count) { sampleCount = count; }

        /** Sets the sound data. The object assumes ownership of the data added. Any existing data is deleted.

            @param bytes the sound data.
            @param length the number of bytes in the sound data.
            */
        void setSound(byte* bytes, size_t length)
        {
            delete [] sound;

            soundLength = length;
            sound = bytes;
        }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int format;
        
        int playbackRate;
        int playbackChannels;
        int playbackSampleSize;
        int sampleCount;

        byte* sound;
        size_t soundLength;
    };
}  
#endif
