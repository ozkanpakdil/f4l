/*
 *  FSInitialize.h
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

#ifndef __FSInitialize_h__
#define __FSInitialize_h__ 1

#include "FSMovieObject.h"

#include "FSVector.h"
#include "FSActionObject.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSActionObject*>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSInitialize is used to specify a sequence of actions that are executed to initialise 
 * a movie clip before it is displayed.
 * 
<p>It implements the #initclip pragma in the ActionScript language.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSInitialize_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSInitialize_1">identifier</a></td>
<td>The identifier of the FSDefineMovieClip object that defines the movie clip.</td>
</tr>

<tr>
<td><a name="FSInitialize_2">actions</a></td>
<td>An array of actions that will be executed to initialize the movie clips.</td>
</tr>

</table>

<p>Unlike the FSDoAction class which specifies the actions that are executed when a particular frame is displayed the actions contained in an FSInitialize object are executed only once, regardless of where the object is included in a movie. If a frame containing the FSInitialize object is played again the actions are skipped. Also there can only be one FSInitialize object for each movie clip defined in the movie.</p>

<h1 class="datasheet">Examples</h1>

<pre>
ArrayList actions = new ArrayList();

actions.add(new FSPush("_root"));
actions.add(FSAction.GetVariable());

int clipId = movie.newIdentifier();

movie.add(new FSDefineMovieClip(clipId, clipObjects));
...

movie.add(new FSInitialize(clipId, actions));
...
movie.add(new FSShowFrame()); 
</pre>

<h1 class="datasheet">History</h1>

<p>The FSInitialize class represents the DoInitAction tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 6.</p>

@see FSDoAction

 */  
    class DLL_DECL FSInitialize : public FSMovieObject
    {
public:
        FSInitialize(FSInputStream* aStream);

		/**  
		 * Constructs an FSInitialize object that will initialize the movie clip 
		 * with the specified identifier with the actions in the array.
		 *
		 * @param anIdentifier the identifier of the movie clip to initialize
	 	 * @param anArray the array of action objects.
		 */
        FSInitialize(int anIdentifier, const FSVector<FSActionObject*>& anArray) : FSMovieObject(Initialize), identifier(anIdentifier), actions(anArray) {}

        FSInitialize(const FSInitialize& rhs);

        ~FSInitialize();

        FSInitialize& operator= (const FSInitialize& rhs);
        
        FSInitialize* clone() const;

        const char* className() const;

		/** Returns the identifier of the movie clip that will be initialized. 

			@return the identifier of the movie clip.
			*/	 
		int getIdentifier() { return identifier; }

		/** Sets the identifier of the movie clip that will be initialized.

			@param anIdentifier the identifier of the movie clip. The value must be in the 
			range 1..65535.
			*/	 
		void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Adds an action to the array of actions. The FSInitialize object assumes ownership of the action object.

            @param anAction a pointer to an action object.
            */
        void add(FSActionObject* anAction) { actions.push_back(anAction); }

        /** Adds all the actions in an array to the array of actions. The FSInitialize object assumes ownership of all the action objects in the array.

            @param anArray an array of pointers to action objects.
            */
        void add(const FSVector<FSActionObject*>& anArray);

		/** Get the array of actions that are used to initialize the movie clip.

			@return the array of action objects.
			*/
        FSVector<FSActionObject*>& getActions() { return actions; }

		/** Set the array of actions of the movie clip that will be initialized

			@param anArray the array of action objects.
			*/
        void setActions(const FSVector<FSActionObject*>& anArray);

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
		int identifier;
        FSVector<FSActionObject*> actions;
    };
}

#endif
