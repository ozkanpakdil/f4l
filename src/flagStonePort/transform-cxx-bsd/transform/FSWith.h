/*
 *  FSWith.java
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

#ifndef __FSWith_h__
#define __FSWith_h__

#include "FSActionObject.h"
#include "FSVector.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSActionObject*>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSWith is a stack-based action and supports the with statement from the ActionScript language.
 * 
<pre>
with(_root.movieClip)
{
    gotoAndPlay("frame");
}
</pre>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSWith_0">type</a></td>
<td>A code identifying the action when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSWith_1">actions</a></td>
<td>An array of actions that will be executed for the specified movie clip.</td>
</tr>
</table>

<p>The FSWith action temporarily selects the movie clip allowing the following stream of actions to control the movie clip's time-line.</p>

<p>The ActionScript shown above is represented (compiled) into the following actions:</p>

<pre>
clipActions.add(new FSPush("frame"));
clipActions.add(new FSPush(1));
clipActions.add(new FSPush("gotoAndPlay"));
clipActions.add(FSAction.ExecuteFunction());

// Get the movie clip 

actions.add(new FSPush("_root"));
actions.add(FSAction.GetVariable());
actions.add(new FSPush("movieClip"));
actions.add(FSAction.GetAttribute());

actions.add(new FSWith(clipActions));

</pre>

<h1 class="datasheet">History</h1>

<p>The FSWith class represents the ActionWith action in the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 5. FSWith supersedes the FSSetTarget action.</p>

 */  
    class DLL_DECL FSWith : public FSActionObject
    {
public:
        FSWith(FSInputStream* aStream);

        /**  Constructs an FSWith object with an array actions. The FSWith object assumes ownership of all the action objects in the array.

            @param anArray the array of action objects.
            */
        FSWith(const FSVector<FSActionObject*>& anArray) : FSActionObject(With), actionsLength(0), actions(anArray) {}

        FSWith(const FSWith& rhs);

        ~FSWith();

        FSWith& operator= (const FSWith& rhs);

        FSWith* clone() const;

        const char* className() const;

        /** Adds an action to the array of actions. The FSWith object assumes ownership of the action object.

            @param anAction a pointer to an action object.
            */
        void add(FSActionObject* anAction) { actions.push_back(anAction); }

        /** Adds all the actions in an array to the array of actions. The FSWith object assumes ownership of all the action objects in the array.

            @param anArray an array of pointers to action objects.
            */
        void add(const FSVector<FSActionObject*>& anArray);

        /** Get the array of actions that are executed when the frame is displayed.

            @return the array of action objects.
            */
        FSVector<FSActionObject*>& getActions() { return actions; }

        /** Set the array of actions that will be executed. The FSWith object assumes ownership of all the action objects in the array.

            @param anArray the array of action objects.
            */
        void setActions(const FSVector<FSActionObject*>& anArray);

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int actionsLength;
        FSVector<FSActionObject*> actions;
    };
}

#endif
