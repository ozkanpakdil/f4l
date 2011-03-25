/*
 *  FSProtect.h
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

#ifndef __FSProtect_h__
#define __FSProtect_h__ 1

#include "FSMovieObject.h"

#include "FSString.h"

namespace transform
{
/**
 * %FSProtect marks a file as not-readable, preventing the file from being loaded into an editor.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSProtect_0">type</a></td>
<td>Identifies the action when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSProtect_1">password</a></td>
<td>An MD-5 encrypted password.</td>
</tr>

</table>

<p>In order to use the debugger a password must be supplied. When encrypted using the MD5 algorithm it must match the value stored in the password attribute.</p>

<p>IMPORTANT: this form of protection only works with Macromedia's Flash Authoring tool. Any application that parses Flash files can choose to ignore or delete this data structure therefore it is not safe to use this to protect the contents of a Flash file.</p>

<p>Transform will parse all Flash files containing the Protect data structure. Since the encoded data is can be removed by trivial scripts the level of copy-protection offered is minimal. Indeed the use of the Protect mechanism in Flash movies may lead to a false sense of security, putting proprietary information at risk. Sensitive information should not be included in Flash movies.</p>

<h1 class="datasheet">History</h1>

<p>The FSProtect class represents the Protect tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 2. The password attribute was added in Flash 5.</p>

 */
    class DLL_DECL FSProtect : public FSMovieObject
    {
public:
        FSProtect(FSInputStream* aStream);

        /** Constructs an FSProtect object. */
        FSProtect() : FSMovieObject(Protect), password() {}

        /** Constructs an FSProtect object with the MD5 encrypted password required to load the file. 

            @param aString an MD5 encrypted password.
            */
        FSProtect(const char* aString) : FSMovieObject(EnableDebugger), password(aString) {}

        FSProtect* clone() const { return new FSProtect(*this); }

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
