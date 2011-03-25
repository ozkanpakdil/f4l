/*
 *  FSUnknownAction.h
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

#ifndef __FSUnknownAction_h__
#define __FSUnknownAction_h__ 1

#include "FSActionObject.h"

namespace transform
{
/**
 * %FSUnknownAction class is used to represent any action decoded from a Flash file that 
 * is currently not supported by the framework. 
 * 
<p>This allows Flash files to be parsed, processed and encoded without affecting any of the actions not directly supported.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSUnknownAction_0">type</a></td>
<td>The value used to identify the type of action. Read-only.</td>
</tr>

<tr>
<td><a name="FSUnknownAction_1">data</a></td>
<td>The encoded bytes that make up the body of the action's data structure.</td>
</tr>
</table>

<p>The object provides direct access to the encoded data of the action offering the possibility to encode and decode actions that are not directly supported in the current release of the framework. However a detailed knowledge of how the action is encoded and decoded is required.</p>

 */
    class DLL_DECL FSUnknownAction : public FSActionObject
    {
public:
        FSUnknownAction(FSInputStream* aStream);

        /** Constructs an FSUnknownAction object of the specified type with the encoded Flash data. The object assumes ownership of the data which will be deleted when the object is deleted.

            @param aType the code identifying the action type.
            @param bytes the encoded data for the action.
            @param numberOfBytes the number of bytes in the encoded data.
            */
        FSUnknownAction(int aType, byte* bytes, size_t numberOfBytes);

        FSUnknownAction(const FSUnknownAction& rhs);

        ~FSUnknownAction();

        FSUnknownAction& operator= (const FSUnknownAction& rhs);
        
        FSUnknownAction* clone() const;

        const char* className() const;

        /** Gets the encoded data for the action. Ownership is retained by the FSUnknownObject object.

            @return a pointer to the encoded binary data owned by the object.
            */
        const byte* getData() const;

        /** Sets the encoded data for the action. The object assumes ownership of the data, deleting it when the object is deleted. Any existing data is deleted.

            @param bytes the encoded data for the action.
            @param numberOfBytes the number of bytes in the encoded data.
            */
        void setData(byte* bytes, size_t numberOfBytes);

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        byte* data;
    };
} 

#endif
