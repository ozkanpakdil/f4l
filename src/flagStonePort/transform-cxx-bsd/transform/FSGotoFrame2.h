/*
 *  FSGotoFrame2.h
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

#ifndef __FSGotoFrame2_h__
#define __FSGotoFrame2_h__

#include "FSActionObject.h"

namespace transform
{
/**
 * The %FSGotoFrame2 action instructs the player to go to the named or numbered frame in the 
 * current movie's main time-line.
 * 
<p>The FSGotoFrame2 action instructs the player to go to the named or numbered frame in the current 
movie's main time-line. It extends the functionality provided by the FSGotoFrame action by allowing 
the name of a frame, previously assigned using the FSFrameLabel object, to be specified.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSGotoFrame2_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSGotoFrame2_1">play</a></td>
<td>A boolean flag indicating whether the Flash Player should start playing the frame as soon as it 
is loaded.</td>
</tr>

<tr>
<td><a name="FSGotoFrame2_2">frameOffset</a></td>
<td>An offset added to the frame number of the stack to generate the final frame number that the 
timeline should move to.</td>
</tr>

</table>

<p>Up to Flash Version 4, movies contained a single sequence of 65536 frames. In Flash 5 the 
concept of Scenes was added which allowed movies to contain 'pages' of frames. FSGotoFrame2 
contains a frameOffset attribute which allows the frames in each scene to be referenced by 
its 'logical' number. The frameOffset for a given scene is added to the frame number to 
generate the 'physical' page number.</p>

<p>FSGotoFrame2 is a stack-based action. The name or number of the frame is pushed onto the 
stack before the FSGotoFrame2 action is executed. If a frameOffset is specified it is added 
to the number of the frame identified by the stack arguments to give the final frame number. 
Whether the movie starts playing the frame is controlled by the boolean attribute, <i>play</i>. 
When set to true the movie starts playing the frame as soon as it has been loaded by the Flash 
Player.</p>

<h1 class="datasheet">Examples</h1>

<p>Start playing a movie at the specified frame number:</p>

<pre>
FSDoAction actions = new FSDoAction();

actions.add(new FSPush(12));
actions.add(new FSGotoFrame2(true));
</pre>

<p>Move to the named frame but do not start playing immediately:</p>

<pre>
FSMovie movie = new FSMovie();
FSDoAction actions = new FSDoAction();

movie.add(new FSFrameLabel("FirstFrame"));

actions.add(new FSPush("FirstFrame"));
actions.add(new FSGotoFrame2(false));
</pre>

<p>To use the concept of scenes in a movie, divide the physical frames into a sequence of logical pages:</p>

<pre>

int sceneSize = 1024;
int scene = 5;
boolean play = true;

// Goto the first frame in scene 5.

frameAction.add(new FSPush(1));
frameAction.add(new FSGotoFrame2(scene*sceneSize, play);

</pre>

<p>FSGotoFrame2 is only used to control the main time-line of a movie. Controlling how an individual 
movie clip is played is handled by a different mechanism. From Flash 5 onward movie clips are defined 
as objects. The ExecuteMethod action is used to execute the gotoAndPlay() or gotoAndStop() methods 
that control a movie clip's time-line:</p>

<pre>
// Push the arguments followed by the number of arguments onto the stack

frameAction.add(new FSPush("frameName"));
frameAction.add(new FSPush(1));

// Get a reference to the object.

frameAction.add(new FSPush("_root"));
frameAction.add(new FSPush("movieClip"));
frameAction.add(FSAction.GetAttribute());

// Place the name of the method on the stack then execute it.

frameAction.add(new FSPush("gotoAndPlay"));
frameAction.add(FSAction.ExecuteMethod());
</pre>

<h1 class="datasheet">History</h1>

<p>The FSGotoFrame2 is a class for representing the ActionGotoFrame2 action of the Macromedia 
Flash (SWF) File Format Specification. It  was introduced in Flash 4 and supersedes the FSGotoFrame 
action. In Flash 5 the frameOffset attribute was added which allows movies to be divided into a 
series of 'pages'.</p>

 */  
    class DLL_DECL FSGotoFrame2 : public FSActionObject
    {
public:
        FSGotoFrame2(FSInputStream* aStream);

        /** Constructs an FSGotoFrame2 object with the specified play flag setting. 

        @param aBool true if the player should being playing the movie at the specified frame, false if the player should not start playing the movie.
        */
        FSGotoFrame2(bool aBool) : FSActionObject(GotoFrame2), playFrame(aBool), frameOffset(0) {}

        /** Constructs an FSGotoFrame2 object with the specified play flag setting 
         * and frame offset for a given scene. 

            @param aBool true if the player should being playing the movie at the specified frame, 
            false if the player should stop playing the movie.
            @param offset a number which will be added to the number of the frame popped from the 
            stack to give the final frame number.
            */
        FSGotoFrame2(bool aBool, int offset) : FSActionObject(GotoFrame2), playFrame(aBool), frameOffset(offset) {}

        FSGotoFrame2* clone() const { return new FSGotoFrame2(*this); }

        const char* className() const;

        /** Gets the play flag. 

            @return true if the player will being playing the movie at the specified frame, false otherwise.
            */
        bool getPlayFrame() const { return playFrame; }

        /**
         * Gets the offset that will be added to the 'logical' frame number obtained from the stack to 
         * generate the 'physical' frame number.
         *
         * @return an offset that will be added to the frame number obtained form the stack.
         */
        int getFrameOffset() { return frameOffset; }

        /** Sets the play flag. 

            @param aBool true if the player should being playing the movie at the specified frame, false if the player should not start playing the movie.
            */
        void setPlayFrame(bool aBool) { playFrame = aBool; }

        /**
         * Sets the offset that will be added to the 'logical' frame number obtained from the stack to 
         * generate the 'physical' frame number.
         *
         * @param offset a number that will be added to the frame number obtained form the stack.
         */
        void setFrameOffset(int offset) { frameOffset = offset; } 

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        bool playFrame;
        int frameOffset;
    };
} 

#endif
