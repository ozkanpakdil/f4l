/*
 *  FSStartSound.h
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

#ifndef __FSStartSound_h__
#define __FSStartSound_h__ 1

#include "FSMovieObject.h"

#include "FSSound.h"

namespace transform
{
/**
 * %FSStartSound instructs the player to start or stop playing a sound defined using the 
 * %FSDefineSound class.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSStartSound_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr><td><a name="FSStartSound_1">sound</a></td>
<td>An FSSound object that identifies the sound and controls how it is played - how the sound fades in or out, whether it is repeated along with an envelope that controls the sound levels as it is played.</td>
</tr>

</table>

<h1 class="datasheet">History</h1>

<p>The FSStartSound class represents the StartSound tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1. In the Macromedia Flash (SWF) File Format Specification the StartSound tag contains an identifier and an FSSoundInfo structure. The Transform FSSound object simply combines both to simplify the design of other sound classes. The information encoded is identical.</p>

 */
    class DLL_DECL FSStartSound : public FSMovieObject
    {
public:
        FSStartSound(FSInputStream* aStream);

        /** Constructs an FSStartSound object with an FSSound object that identifies the sound and controls how it is played.

            @param aSound the FSSound object.
        */
        FSStartSound(const FSSound& aSound) : FSMovieObject(StartSound), sound(aSound) {}

        FSStartSound* clone() const { return new FSStartSound(*this); }

        const char* className() const;

        /**  Gets the FSSound object describing how the sound will be played.

            @return the FSSound object.
            */
        FSSound& getSound() { return sound; }

        /**  Sets the FSSound object that describes how the sound will be played.

            @param aSound the FSSound object that controls how the sound is played.
            */
        void setSound(const FSSound& aSound) { sound = aSound; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSSound sound;
    };
}

#endif
