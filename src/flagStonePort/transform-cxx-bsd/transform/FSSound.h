/*
 *  FSSound.h
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

#ifndef __FSSound_h__
#define __FSSound_h__ 1

#include "FSTransformObject.h"

#include "FSVector.h"
#include "FSEnvelope.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSEnvelope>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * The %FSSound class identifies a sound (previously defined using the %FSDefineSound class) 
 * and controls how it is played.
 *
<p>FSSound defines how the sound fades in and out, whether it is repeated as well as specifying an envelope that provides a finer degree of control over the levels at which the sound is played.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSSound_0">identifier</a></td>
<td>The identifier, in the range 1..65535, of the FSDefineSound object that contains the sound data.</td>
</tr>

<tr>
<td><a name="FSSound_1">mode</a></td>
<td>Controls how the sound is played, either: Start - start playing the sound, Continue - start playing the sound if it is not already playing and Stop - stop playing the sound.</td>
</tr>

<tr>
<td><a name="FSSound_2">inPoint</a></td>
<td>The sample number that the sound increases in volume to until full volume is reached. Optional. Set to 0 if the sound does not fade in.</td>
</tr>

<tr>
<td><a name="FSSound_3">outPoint</a></td>
<td>The sample number at which the that the sound starts to fades until the sound has finished playing. Optional. Set to 0 if the sound does not fade out.</td>
</tr>

<tr>
<td><a name="FSSound_4">loopCount</a></td>
<td>The number of times the sound is repeated. Optional. Must be at least 1 if a sound is being played. Set to 0 if a sound is being stopped.</td>
</tr>

<tr>
<td><a name="FSSound_5">envelopes</a></td>
<td>An array of FSEnvelope objects that control how the sound is played. Optional. May be set to null or an empty array if no envelope is defined.</td>
</tr>

</table>

<p>Not all the attributes are required to play a sound. Only the identifier and the mode is required. The other attributes are optional and may be added as a greater degree of control is required. The inPoint and outPoint attributes may be set to zero if the sound does not fade in or out respectively. The loopCount may be set to zero if a sound is being stopped. The envelopes array may be left empty if no envelope is defined for the sound. The class provides different constructors to specify different sets of attributes.</p>

<p>The in and out point specify the sample number which marks the point in time at which the sound stops increasing or starts decreasing in volume respectively. Sounds are played by the Flash player at 44.1KHz so the sample number also indicates the time when the total number of samples in the sound is taken into account.</p>

<h1 class="datasheet">History</h1>

<p>The FSSound class is based on the SoundInfo data structure from the Macromedia Flash (SWF) File Format Specification. However it also contains the identifier for the sound which is a separate attribute in the data structures defined in the specification that contain SoundInfo data.</p>

 */
    class DLL_DECL FSSound : public FSTransformObject
    {
public:
        /** Definition of the different sound encoding formats.

            NATIVE_PCM - PCM with platform specific byte order
            ADPCM - compressed adaptive PCM
            MP3 - compressed MPEG Layer 3
            PCM - PCM with little-endian byte order
            */
        enum format { NATIVE_PCM, ADPCM, MP3, PCM };

        /** Definition of the different modes for playing a sound. */
        enum soundType { Start = 0, Continue = 1, Stop = 2 };

        FSSound(FSInputStream* aStream);

        FSSound() : identifier(0), mode(Start), inPoint(0), outPoint(0), loopCount(0), envelopes() {}
        
        /** Constructs an FSSound object specifying how the sound is played.

            @param anIdentifier the unique identifier of the object that contains the sound data.
            @param aMode how the sound is synchronised when the frames are displayed: Start - start playing the sound, Continue - do not play the sound if it is already playing and Stop - stop playing the sound.
            */
        FSSound(int anIdentifier, int aMode) : identifier(anIdentifier), mode(aMode), inPoint(0), outPoint(0), loopCount(0), envelopes() {}

        /** Constructs and FSSound object specifying how the sound is played and the number of times the sound is repeated.

            @param anIdentifier the unique identifier of the object that contains the sound data.
            @param aMode how the sound is synchronised when the frames are displayed: Play - do not play the sound if it is already playing and Stop - stop playing the sound.
            @param aCount the number of times the sound is repeated. May be set to zero if the sound will not be repeated.
            */
        FSSound(int anIdentifier, int aMode, int aCount) : identifier(anIdentifier), mode(aMode), inPoint(0), outPoint(0), loopCount(aCount), envelopes() {}

        /** Constructs and FSSound object specifying how the sound is played and the points at which the sound fades in and out.

            @param anIdentifier the unique identifier of the object that contains the sound data.
            @param aMode how the sound is synchronised when the frames are displayed: Play - do not play the sound if it is already playing and Stop - stop playing the sound.
            @param anInPoint the sample number which the sound fades in to. May be set to zero if the sound does not fade in.
            @param anOutPoint the sample number at which the sound starts to fade. May be set to zero if the sound does not fade out.
            */
            FSSound(int anIdentifier, int aMode, int anInPoint, int anOutPoint) : identifier(anIdentifier), mode(aMode), inPoint(anInPoint), outPoint(anOutPoint), loopCount(0), envelopes() {}

        /** Constructs and FSSound object specifying how the sound is played, the point at which the sound fades in and out and the number of times the sound is repeated.

            @param anIdentifier the unique identifier of the object that contains the sound data.
            @param aMode how the sound is synchronised when the frames are displayed: Play - do not play the sound if it is already playing and Stop - stop playing the sound.
            @param anInPoint the sample number which the sound fades in to. May be set to zero if the sound does not fade in.
            @param anOutPoint the sample number at which the sound starts to fade. May be set to zero if the sound does not fade out.
            @param aCount the number of times the sound is repeated. May be set to zero if the sound will not be repeated.
            */
        FSSound(int anIdentifier, int aMode, int anInPoint, int anOutPoint, int aCount) : identifier(anIdentifier), mode(aMode), inPoint(anInPoint), outPoint(anOutPoint), loopCount(aCount), envelopes() {}
    
        /** Constructs and FSSound object specifying how the sound is played, the point at which the sound fades in and out, the number of times the sound is repeated and the envelopes used to control how the sound is played.

            @param anIdentifier the unique identifier of the object that contains the sound data.
            @param aMode how the sound is synchronised when the frames are displayed: Play - do not play the sound if it is already playing and Stop - stop playing the sound.
            @param anInPoint the sample number which the sound fades in to. May be set to zero if the sound does not fade in.
            @param anOutPoint the sample number at which the sound starts to fade. May be set to zero if the sound does not fade out.
            @param aCount the number of times the sound is repeated. May be set to zero if the sound will not be repeated.
            @param anArray an array of FSEnvelope objects that define the levels at which a sound is played over the duration of the sound. May be set to NULL if no envelope is defined.
            */
        FSSound(int anIdentifier, int aMode, int anInPoint, int anOutPoint, int aCount, const FSVector<FSEnvelope>& anArray) : identifier(anIdentifier), mode(aMode), inPoint(anInPoint), outPoint(anOutPoint), loopCount(aCount), envelopes(anArray) {}

        FSSound* clone() const { return new FSSound(*this); }

        const char* className() const;

        /** Adds an FSEnvelope object to the end of the array of envelopes.

            @param anEnvelope an FSEnvelope object.
            */
        void add(const FSEnvelope& anEnvelope) { envelopes.push_back(anEnvelope); }

        /** Adds all the FSEnvelope objects in the array to the end of the array of envelopes.

            @param anArray an array of FSEnvelope objects.
            */
        void add(const FSVector<FSEnvelope>& anArray);

        /** Gets the identifier of the sound to the played.

            @return the sound identifier.
            */
        int getIdentifier() const { return identifier; }

        /** Gets how the sound is played: Start - start playing the sound, Continue - do not play the sound if it is already playing and Stop - stop playing the sound.

            @return the synchronisation mode of the sound.
            */
        int getMode() const { return mode; }

        /** Gets the sample number at which the sound reaches full volume when fading in.

            @return the in point
            */
        int getInPoint() const { return inPoint; }

        /** Gets the sample number at which the sound starts to fade.

            @return the out point
            */
        int getOutPoint() const { return outPoint; }
        
        /** Gets the number of times the sound will be repeated.

            @return the Loop Count.
            */
        int getLoopCount() const { return loopCount; }

        /** Gets the array of FSEnvelope objects that control the levels the sound is played.

            @return an array of FSEnvelope objects.
            */
        FSVector<FSEnvelope>& getEnvelopes() { return envelopes; }

        /** Sets the identifier of the sound to the played.

            @param anIdentifier the identifier for the sound to be played.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Sets how the sound is synchronised when the frames are displayed: Start - start playing the sound, Continue - do not play the sound if it is already playing and Stop - stop playing the sound.

            @param aMode how the sound is played.
            */
        void setMode(int aMode) { mode = aMode; }

        /** Sets the sample number at which the sound reaches full volume when fading in. May be set to zero if the sound does not fade in.

            @param aNumber the sample number which the sound fades in to.
            */
        void setInPoint(int aNumber) { inPoint = aNumber; }

        /** Sets the sample number at which the sound starts to fade. May be set to zero if the sound does not fade out.

            @param aNumber the sample number at which the sound starts to fade.
            */
        void setOutPoint(int aNumber) { outPoint = aNumber; }

        /** Sets the number of times the sound is repeated. May be set to zero if the sound will not be repeated.

            @param aNumber the number of times the sound is repeated.
            */
        void setLoopCount(int aNumber) { loopCount = aNumber; }

        /** Sets the array of FSEnvelope objects that define the levels at which a sound is played over the duration of the sound. May be set to NULL if no envelope is defined.

            @param anArray an array of FSEnvelope objects.
            */
        void setEnvelopes(const FSVector<FSEnvelope>& anArray) { envelopes = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        bool containsInPoint() const;
        bool containsOutPoint() const;
        bool containsLoopCount() const;
        bool containsEnvelopes() const;

        int identifier;
        int mode;
        int inPoint;
        int outPoint;
        int loopCount;
        
        FSVector<FSEnvelope> envelopes;
    };
} 

#endif

