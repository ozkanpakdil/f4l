/*
 *  FSEnableDebugger.h
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

#ifndef __FSEnableDebugger_h__
#define __FSEnableDebugger_h__ 1

#include "FSMovieObject.h"

#include "FSString.h"

namespace transform
{
/**
 * Enables a movie to be debugged when played using the Flash authoring tool, allowing the 
 * variables defined in the arrays of actions specified in object to be inspected.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSEnableDebugger_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSEnableDebugger_1">password</a></td>
<td>An MD-5 encrypted password.</td>
</tr>

</table>

<p>In order to use the debugger a password must be supplied. When encrypted using the MD5 algorithm it must match the value stored in the password attribute.</p>

<h1 class="datasheet">History</h1>

<p>The FSEnableDebugger class represents the EnableDebugger data structure of the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 5.</p>

 */  
    class DLL_DECL FSEnableDebugger : public FSMovieObject
    {
public:
        FSEnableDebugger(FSInputStream* aStream);

        FSEnableDebugger() : FSMovieObject(EnableDebugger), password() {}

        /** Constructs an FSEnableDebugger object with the MD5 encrypted password required to start debugging. 

            @param aString an MD5 encrypted password.
            */
        FSEnableDebugger(const char* aString) : FSMovieObject(EnableDebugger), password(aString) {}

        FSEnableDebugger* clone() const { return new FSEnableDebugger(*this); }

        const char* className() const;

        /** Gets the MD-5 encrypted password.

            @return the string defining the password.
            */
        const char* getPassword() const { return password.c_str(); }

       /** Sets the MD-5 encrypted password.

            @param aString the string defining the password.
            */
        void setPassword(const char* aString) { password = aString; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSString password;
    };
}

#endif
