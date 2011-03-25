/*
 *  FSSoundStreamBlock.h
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

#ifndef __FSSoundStreamBlock_h__
#define __FSSoundStreamBlock_h__ 1

#include "FSMovieObject.h"

namespace transform
{
/**
 * %FSSoundStreamBlock contains the sound data being streamed to the Flash Player. 
 * 
<p>Streaming sounds are played in tight synchronisation with one FSSoundStreamBlock 
object defining the sound for each frame displayed in a movie.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSSoundStreamBlock_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr><td><a name="FSSoundStreamBlock_1">soundData</a></td>
<td>The encoded sound data for a single frame in a movie. The format for the sound 
is defined by an FSSoundStreamHead object. Sounds may be encoded using the uncompressed 
PCM (big or little endian byte order), compressed ADPCM, compressed MP3 or NELLYMOSER
formats.</td>
</tr>

</table>

<p>When a streaming sound is played if the Flash Player cannot render the frames fast 
enough to maintain synchronisation with the sound being played then frames will be 
skipped. Normally the player will reduce the frame rate so every frame of a movie 
is played.</p>

<h1 class="datasheet">History</h1>

<p>The FSSoundStreamBlock class represents the SoundStreamBlock tag from the Macromedia 
Flash (SWF) File Format Specification. It was introduced in Flash 1 with support for 
Uncompressed PCM encoded sounds (both Little-Endian and Big-Endian formats) and the 
compressed ADPCM format. Support for MP3 was added in Flash 3. The Nellymoser Asao
format was added in Flash 6.</p>

 */
    class DLL_DECL FSSoundStreamBlock : public FSMovieObject
    {
public:
        FSSoundStreamBlock(FSInputStream* aStream);

        /** Constructs an FSSoundStreamBlock specifying the sound data in the format defined by a preceding FSSoundStreamHead or FSSoundStreamHead2 object.

            @param bytes an array of bytes containing the sound data.
            @param size the number of bytes in the sound data.
            */
        FSSoundStreamBlock(byte* bytes, size_t size) : FSMovieObject(SoundStreamBlock), soundData(0)
        {
            setSoundData(bytes, size);
        }

        FSSoundStreamBlock(const FSSoundStreamBlock& rhs);

        ~FSSoundStreamBlock();

        FSSoundStreamBlock& operator= (const FSSoundStreamBlock& rhs);

        FSSoundStreamBlock* clone() const { return new FSSoundStreamBlock(*this); }

        const char* className() const;

        /** Gets the sound data in the format defined by a preceding FSSoundStreamHead or FSSoundStreamHead2 object.

            @return the sound data.
            */
        const byte* getSoundData() const { return soundData; }

        /** Sets the sound data. The object assumes ownership of the data. Any existing sound data is deleted.

            @param bytes the sound data.
            @param numberOfBytes in the sound data.
            */
        void setSoundData(byte* bytes, size_t numberOfBytes)
        {
            delete [] soundData;

            soundData = bytes;
            length = (int)numberOfBytes;
        }

        int  lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        byte* soundData;
    };
} 

#endif
