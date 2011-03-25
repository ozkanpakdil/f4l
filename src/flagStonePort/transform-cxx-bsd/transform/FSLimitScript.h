/*
 *  FSLimitScript.h
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

#ifndef __FSLimitScript_h__
#define __FSLimitScript_h__ 1

#include "FSMovieObject.h"

namespace transform
{
	/**
	 * The %FSLimitScript is used to define the execution environment of the Flash Player, 
	 * limiting the resources available when executing actions.
	 * 
<p>FSLimitScript can be used to limit the maximum recursion depth and limit the time a sequence of actions can execute for. This provides a rudimentary mechanism for people viewing a movie to regain control of the Flash Player should a script fail.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSLimitScript_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSLimitScript_1">depth</a></td>
<td>The maximum depth, in the range 1..65535, that a sequence of actions can recurse to.</td>
</tr>

<tr>
<td><a name="FSLimitScript_1">timeout</a></td>
<td>The maximum time, in seconds, that a sequence of actions will execute before the Flash Player present a dialog box asking whether the script should be terminated.</td>
</tr>

</table>

<h1 class="datasheet">History</h1>

<p>The FSLimitScript represents the ScriptLimits tag in the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 7.</p>

	 */  
    class DLL_DECL FSLimitScript : public FSMovieObject
    {
public:
        FSLimitScript(FSInputStream* aStream);

		/**
		 * Constructs an FSLimitScript object that limits the recursion depth to <em>depth</em> levels
		 * and specifies that any sequence of actions will timeout after <em>timeout</em> seconds.
		 *
		 * @param stackDepth the maximum depth a sequence of actions can recurse to.
		 * @param timeLimit the time in seconds that a sequence of actions is allowed to execute before the Flash Player displays a dialog box asking whether the script should be terminated.
		 */
        FSLimitScript(int stackDepth, int timeLimit) : FSMovieObject(LimitScript), depth(stackDepth), timeout(timeLimit) {}

        FSLimitScript* clone() const { return new FSLimitScript(*this); }

        const char* className() const;

		/**
		 * Gets the maximum recursion level.
		 *
		 * @return the maximum depth a sequence of actions can recurse to.
		 */
        int getDepth() const { return depth; }

		/**
		 * Gets the maximum time a sequence of actions will execute before the Flash Player present a dialog box asking whether the script should be terminated.
		 *
		 * @return the time in seconds that a sequence of actions is allowed to execute.
		 */
        int getTimeout() const { return timeout; }

		/**
		 * Sets the maximum recursion level.
		 *
		 * @param stackDepth the maximum depth a sequence of actions can recurse to.
		 */
		void setDepth(int stackDepth) { depth = stackDepth; }

		/**
		 * Sets the maximum time a sequence of actions will execute before the Flash Player present a dialog box asking whether the script should be terminated.
		 *
		 * @param timeLimit the time in seconds that a sequence of actions is allowed to execute.
		 */
        void setTimeout(int timeLimit) { timeout = timeLimit; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
        
private:
	    int depth;
        int timeout;
    };
} 

#endif
