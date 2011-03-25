/*
 *  FSTableIndex.h
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

#ifndef __FSTableIndex_h__
#define __FSTableIndex_h__ 1

#include "FSValue.h"

namespace transform
{
/**
 * %FSTableIndex is used with an %FSPush action to push a reference to an entry in a table 
 * of literals onto the stack. 
 * 
<p>The value is can then be retrieved from the table and used in a subsequent calculation. The data type was extended in Flash 6 to support tables of up to 65535 strings.</p>

<p>In the Macromedia Flash (SWF) File Format Specification all literals used in calculations are stored as strings. When performing a series of actions each time a literal value is used in a calculation it must be pushed onto the stack. Rather than repeatedly pushing the value explicitly using an FSPush action, all the literals are added to a table in the Flash Player's memory using the FSTable action. To retrieve a literal from the table a reference to an entry in the table is pushed onto the stack using an FSTableIndex. The reduces the number of bytes required to perform a given calculation when the values are used repeatedly.</p>

<p>As an example consider the code required to concatenate two strings:</p>

<pre>
ArrayList actions = new ArrayList();
...
// Create the table of literals
FSTable literals = new FSTable();
literals.add("abc");
literals.add("def");
actions.add(literals);
...
// Create references to the string literals
FSPush push = new FSPush();
push.add(new FSTableIndex(0));
push.add(new FSTableIndex(1));
actions.add(push);
...
// concatenate the strings
actions.add(new FSAction(FSAction.Add));
</pre>

<p>An FSTable can store up to 65536 string literals. Using a table index rather 
than specifying the string literal explicitly reduces considerably the number of 
bytes required to represent a sequence of actions.</p>

<h1 class="datasheet">History</h1>

<p>The string literal table was introduced in Flash 5. It was extended in Flash 
6 to support tables of up to 65536 strings.</p>

 */  
    class DLL_DECL FSTableIndex : public FSValue
    {
public:
        FSTableIndex(FSInputStream* aStream);

        /** Constructs an FSTableIndex object referencing the value stored in the literal table.

        @param anIndex the index into the literal table.
        */
        FSTableIndex(int anIndex) : FSValue(FSValue::TableIndex), index(anIndex) {}

        FSTableIndex* clone() const { return new FSTableIndex(*this); }

        const char* className() const;

        int length() const;

        /** Gets the index in the table of string literals.

            @return the index into the literal table.
            */
        int getIndex() const { return index; }

        /** Sets the index in the table of string literals.

            @param anIndex the index into the literal table.
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
