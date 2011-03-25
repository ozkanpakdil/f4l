/*
 *  FSSoundStreamHead2.h
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

#ifndef __FSSoundStreamHead2_h__
#define __FSSoundStreamHead2_h__

#include "FSMovieObject.h"
#include "FSSound.h"

namespace transform
{
/**
 * %FSSoundStreamHead2 defines a sound, compressed using different compression formats, 
 * that is streamed in tight synchronisation with the movie being played.
 * 
<p>The FSSoundStreamHead2 class defines how the streaming sound is played. Objects 
of the FSSoundStreamBlock class contains the sound data.</P>

<p>When a stream sound is played if the Flash Player cannot render the frames fast 
enough to maintain synchronisation with the sound being played then frames will 
be skipped. Normally the player will reduce the frame rate so every frame of a 
movie is played.</p>

<p>To define the stream sound the parameters for and sampled sound and how it will 
be played back must be specified:</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSSoundStreamHead_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSSoundStreamHead_1">format</a></td>
<td>The format of the encoded sound data - FSSound.PCM (Little-Endian byte order), 
FSSound.ADPCM, FSSound.NATIVE_PCM (Big-Endian or Little-Endian byte order 
depending on the platform where the sound was created), FSSound.MP3 or 
FSSound.NELLYMOSER</td>
</tr>

<tr>
<td><a name="FSSoundStreamHead_2">playbackRate</a></td>
<td>The recommended playback rate in Hertz - 5512, 11025, 22050 or 44100.</td>
</tr>

<tr>
<td><a name="FSSoundStreamHead_3">playbackSampleSize</a></td>
<td>The number of bytes in an uncompressed sample when the sound is played, either 1 or 2.</td>
</tr>

<tr>
<td><a name="FSSoundStreamHead_4">playbackChannels</a></td>
<td>The recommended number of playback channels: 1 = mono or 2 = stereo.</td>
</tr>

<tr>
<td><a name="FSSoundStreamHead_5">streamRate</a></td>
<td>The stream sampling rate - 5512, 11025, 22050 or 44100 Hz</td>
</tr>

<tr>
<td><a name="FSSoundStreamHead_6">streamSampleSize</a></td>
<td>The size of an uncompressed sample in the streaming sound in bytes, either 1 or 2.</td>
</tr>

<tr>
<td><a name="FSSoundStreamHead_7">streamChannels</a></td>
<td>The number of channels: 1 = mono or 2 = stereo in the streaming sound</td>
</tr>

<tr>
<td><a name="FSSoundStreamHead_8">streamSampleCount</a></td>
<td>The average number of samples in each sound stream block.</td>
</tr>

<tr>
<td><a name="">latency</a></td>
<td>Latency defines the number of samples to skip only when playing sounds encoded 
with the MP3 format.</td>
</tr>

</table>

<p>FSSoundStreamHead2 allows way the sound is played to differ from the way it is 
encoded and streamed to the player. This allows the Player more control over how 
the animation is rendered. Reducing the resolution or playback rate can improve 
synchronisation with the frames displayed.</p>

<b>History</b>

<p>The FSSoundStreamHead2 class represents the SoundStreamHead structure from the 
Flash specification. It was introduced in Flash 3. Support for the Nellymoser Asao
format was added in Flash 6.</p>

 */
    class DLL_DECL FSSoundStreamHead2 : public FSMovieObject
    {
    public:
        FSSoundStreamHead2(FSInputStream* aStream);
    
        /** Constructs an FSSoundStreamHead2 object specifying all the parameters required to define the sound.
    
        @param encoding the compression format for the sound data, either FSSound::NATIVE_PCM, FSSound::ADPCM, FSSound::MP3 or FSSound::PCM.
        @param playRate the recommended rate for playing the sound, either 5512, 11025, 22050 or 44100 Hz.
        @param playChannels The recommended number of playback channels: 1 = mono or 2 = stereo.
        @param playSize the recommended uncompressed sample size for playing the sound, either 1 or 2 bytes.
        @param streamingRate the rate at which the sound was sampled, either 5512, 11025, 22050 or 44100 Hz.
        @param streamingSize the sample size for the sound, either 1 or 2 bytes.
        @param streamingChannels the number of channels: 1 = mono or 2 = stereo.
        @param streamingCount the number of samples in each subsequent FSSoundStreamBlock object.
        @param skip defines the number of samples to skip only when playing sounds encoded with the MP3 format.
        */
        FSSoundStreamHead2(int encoding, int playRate, int playChannels, int playSize, int streamingRate, int streamingChannels, int streamingSize, int streamingCount, int skip) : FSMovieObject(SoundStreamHead2), format(encoding), playbackRate(playRate), playbackChannels(playChannels), playbackSampleSize(playSize), streamRate(streamingRate), streamChannels(streamingChannels), streamSampleSize(streamingSize), streamSampleCount(streamingCount), latency(skip) {}
    
        FSSoundStreamHead2* clone() const { return new FSSoundStreamHead2(*this); }
    
        const char* className() const;
    
        /** Gets the streaming sound format. For the FSSoundStreamHead2 class supports NATIVE_PCM, ADPCM,  MP3 and PCM.
    
            @return the format used to play the sound
            */
        int getFormat() { return format; }
    
        /** Gets the recommended playback rate: 5512, 11025, 22050 or 44100 Hz.
    
            @return the rate at which the sound will be played back.
            */
        int getPlaybackRate() { return playbackRate; }
    
        /** Gets the recommended number of playback channels = 1 = mono 2 = stereo.
    
            @return the number of channels for the sound playback.
            */
        int getPlaybackChannels() { return playbackChannels; }
    
        /** Gets the recommended playback sample range in bits: 8 or 16.
    
            @return the sample size used to play back the sound.
            */
        int getPlaybackSampleSize() { return playbackSampleSize; }
    
        /** Gets the sample rate: 5512, 11025, 22050 or 44100 Hz in the streaming sound.
    
            @return the rate at which the sound was sampled.
            */
        int getStreamRate() { return streamRate; }
    
        /** Gets the number of channels, 1 = mono 2 = stereo, in the streaming sound.
    
            @return the number of channels in the sound.
            */
        int getStreamChannels() { return streamChannels; }
    
        /** Gets the sample size in bytes: 1 or 2 in the streaming sound.
    
            @return the sample size.
            */
        int getStreamSampleSize() { return streamSampleSize; }
    
        /** Gets the average number of samples in each stream block following.
    
            @return the number of sound samples in each following FSSoundStreamBlock object.
            */
        int getStreamSampleCount() { return streamSampleCount; }
    
        /**
         * For MP3 encoded sounds, returns the number of samples to skip when starting to play a sound.
         *
         * @return the number of samples skipped in an MP3 encoded sound Returns 0 for other sound formats.
         */
        int getLatency() { return latency; }

        /** Sets the format for the streaming sound.
    
            @param encoding the compression format for the sound data, either FSSound::NATIVE_PCM, FSSound::ADPCM, FSSound::MP3 or FSSound::PCM.
            */
        void setFormat(int encoding) { format = encoding; }
    
        /** Sets the recommended playback rate in Hz. Must be either: 5512, 11025, 22050 or 44100.
    
            @param playRate the recommended rate for playing the sound.
            */
        void setPlaybackRate(int playRate) { playbackRate = playRate; }
    
        /** Sets the recommended number of playback channels = 1 = mono 2 = stereo.
    
            @param channels the recommended number of playback channels.
            */
        void setPlaybackChannels(int channels) { playbackChannels = channels; }
    
        /** Sets the recommended playback sample size in bytes. Must be wither 1 or 2.
    
            @param playSize the recommended sample size for playing the sound.
            */
        void setPlaybackSampleSize(int playSize) { playbackSampleSize = playSize; }
    
        /** Sets the sample rate in Hz for the streaming sound. Must be either: 5512, 11025, 22050 or 44100.
    
            @param streamingRate the rate at which the streaming sound was sampled.
            */
        void setStreamRate(int streamingRate) { streamRate = streamingRate; }
    
        /** Sets the number of channels in the streaming sound: 1 = mono 2 = stereo.
    
            @param streamingChannels the number of channels in the streaming sound.
            */
        void setStreamChannels(int streamingChannels) { streamChannels = streamingChannels; }
    
        /** Sets the sample size in bytes for the streaming sound. Must be 1 or 2.
    
            @param streamingSampleSize the sample size for the sound.
            */
        void setStreamSampleSize(int streamingSampleSize) { streamSampleSize = streamingSampleSize; }
    
        /** Sets the number of samples in each stream block.
    
            @param streamingCount the number of samples in each subsequent FSSoundStreamBlock object.
            */
        void setStreamSampleCount(int streamingCount) { streamSampleCount = streamingCount; }
    
        /**
         * Set the number of samples to skip when starting to play an MP3 encoded sound.
         *
         * @param skip the number of samples to be skipped in an MP3 encoded sound should be 0 for other sound formats.
         */
        void setLatency(int skip) { latency = skip; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
    
    private:
        int format;
        
        int playbackRate;
        int playbackChannels;
        int playbackSampleSize;
    
        int streamRate;
        int streamChannels;
        int streamSampleSize;
        int streamSampleCount;
        int latency;
    };
}

#endif
