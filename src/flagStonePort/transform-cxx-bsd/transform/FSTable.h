/*
 *  FSTable.h
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

#ifndef __FSTable_h__
#define __FSTable_h__

#include "FSActionObject.h"

#include "FSVector.h"
#include "FSString.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSString>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSTable is used to create a table of string literals that can be referenced by an index 
 * rather than using the literal value when executing a sequence of actions.
 * 
<p>Variables and built-in functions are specified by their name and the FSTable 
class contains a table of the respective strings. References to a variable or 
function can then use its index in the table rather than the name resulting in 
a more compact representation when the actions are encoded into binary form.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSTable_0">type</a></td>
<td>Identifies the action when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSTable_1">values</a></td>
<td>An array of up to 65536 strings.</td>
</tr>
</table>

<p>The use of the FSTable class is illustrated in the following simple expression:</p>

<pre>
var1 = (var1 + var2) / (var1 - var3);
</pre>

<p>This can be translated into the following sequence of actions:</p>

<pre>
FSTable values = new FSTable();

values.add("var1");
values.add("var2");
values.add("var3");

actions.add(values);

actions.add(new FSPush(FSTableIndex(0)));            // var1
actions.add(FSAction.GetVariable());
actions.add(new FSPush(FSTableIndex(0)));            // var1
actions.add(FSAction.GetVariable());
actions.add(new FSPush(FSTableIndex(1)));            // var2
actions.add(FSAction.GetVariable());
actions.add(new FSAction(FSAction.Add));
actions.add(new FSPush(FSTableIndex(0)));            // var1
actions.add(FSAction.GetVariable());
actions.add(new FSPush(FSTableIndex(2)));            // var3
actions.add(FSAction.Subtract());
actions.add(FSAction.Divide());
actions.add(FSAction.SetVariable());
</pre>

<p>The table in the FSTable class can support up to 65536 different variables. As 
a result using the FSVariable class to reference the variables in the example 
above uses one byte rather than the five required to represent the name directly 
(including the null character terminating the string).</p>

<p>The FSTable stores the strings in an array. No checking for duplicate values is performed.</p>

<h1 class="datasheet">History</h1>

<p>The FSTable class represents the ActionConstantPool in the Macromedia Flash (SWF)
File Format Specification. It was introduced in Flash 5. It was extended in Flash 
6 to support tables of up to 65536 strings.</p>

 */  
    class DLL_DECL FSTable : public FSActionObject
    {
public:
        FSTable(FSInputStream* aStream);

        /** Constructs a table with no entries. */
        FSTable() : FSActionObject(Table), values() {}

        /** Constructs an FSTable object using the array of C strings.

            @param anArray of strings that will be added to the table.
            @param size the number of strings in the array.
            */
        FSTable(const char* anArray[], int size) : FSActionObject(Table), values(size)
        {
            for (int i=0; i<size; i++)
                values[i] = FSString(anArray[i]);
        }
        
        /** Constructs an FSTable object using the array of FSString objects.

            @param anArray of FSString objects that will be added to the table.
            */
        FSTable(const FSVector<FSString>& anArray) : FSActionObject(Table), values(anArray) {}

        FSTable* clone() const { return new FSTable(*this); }

        const char* className() const;

        /** Adds a C string to the end of the table.

            @param aString a C string.
            */
        void add(const char* aString) { values.push_back(FSString(aString)); }

        /** Adds an FSString to the end of the table.

            @param aString an FSString object.
            */
        void add(const FSString& aString) { values.push_back(aString); }

        /** Append all the strings in the array to the table.

            @param anArray of strings that will be add at the end of the table.
            @param size the number of strings in the array.
            */
        void add(const char* anArray[], int size)
        {
            for (int i=0; i<size; i++)
                values.push_back(FSString(anArray[i]));
        }

        /** Append all the FSStrings in the array to the table.

            @param anArray of FSString objects.
            */
        void add(const FSVector<FSString>& anArray);

        /** Gets the array of strings stored in the table.

            @return an array of FSString objects.
            */
        FSVector<FSString>& getValues() { return values; }

        /** Sets the array of strings stored in the table.

            @param anArray of C strings.
            @param size the number of strings in the array.
            */
        void setValues(const char* anArray[], int size);

        /** Sets the array of FSStrings stored in the table.

            @param anArray of FSString objects.
            */
        void setValues(const FSVector<FSString>& anArray) { values = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSVector<FSString>values;
    };
}

#endif
