/*
 *  FSRegisterIndex.h
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

#ifndef __FSRegisterIndex_h__
#define __FSRegisterIndex_h__ 1

#include "FSValue.h"

namespace transform
{
/**
 * %FSRegisterIndex is used with an %FSPush action to refer to one of the Flash Player's 
 * internal registers that contains a value to be used in a calculation.
 * 
<p>The number of registers in the Flash Player was increased in Flash 7 to 256.</p>

<p>The Flash Player uses a stack to store values when executing the actions associated with a button being  pushed, frame being played, etc. If a value is used repeatedly in a calculation, it must be pushed onto the stack each time using an FSPush action. To speed up the execution of the calculation and reduce the amount of code required the value can be saved to one of the internal registers of the Flash Player using the FSRegisterCopy action (which copies the value currently at the top of the stack into the specified register). An FSRegisterIndex creates a reference to the register so the Flash Player uses the value directly rather than popping it from the stack.</p>

<p>To copy a value from the top of the stack to one of the Flash Player's internal registers specify the register number in the constructor for the FSRegisterCopy class:</p>

<pre>
ArrayList actions = new ArrayList();
...
actions.add(new FSRegisterCopy(0));
...
</pre>

<p>References to one of the Flash Player's internal registers are created using the FSRegisterIndex class and pushing it onto the stack using the FSPush class. When the value is used in a calculation then the value will be retrieved from the specified register.</p>

<pre>
FSPush push = new FSPush();
push.add(new FSRegisterIndex(0));
...
actions.add(push);
...
</pre>

<h1 class="datasheet">History</h1>

<p>The RegisterCopy action and access to the Flash Player's internal registers was introduced in Flash 5. The number of registers supported was expanded in Flash 7 to 256.</p>

 */  
    class DLL_DECL FSRegisterIndex : public FSValue
    {
public:
        FSRegisterIndex(FSInputStream* aStream);

        /** Constructs an FSRegisterIndex object referencing the value stored in one of the Flash Player's internal registers. 

        @param anIndex the register number, in the range 0..3.
        */
        FSRegisterIndex(int anIndex) : FSValue(FSValue::RegisterIndex), index(anIndex) {}

        FSRegisterIndex* clone() const { return new FSRegisterIndex(*this); }

        const char* className() const;

        int length() const { return 2; }

        /** Gets the number of the Flash Player's internal register. 

            @return the register number.
            */
        int getIndex() const { return index; }

        /** Sets the number of the Flash Player's internal register.

            @param anIndex the register number, in the range 0..3.
            */
        void setIndex(int anIndex) { index = anIndex; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
        
private:
        int index;
    };
} 

#endif
