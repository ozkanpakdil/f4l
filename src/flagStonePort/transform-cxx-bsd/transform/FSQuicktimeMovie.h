/*
 *  FSQuicktimeMovie.h
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

#ifndef __FSQuicktimeMovie_h__
#define __FSQuicktimeMovie_h__

#include "FSMovieObject.h"

#include "FSString.h"

namespace transform
{
/**
 * The %FSQuicktimeMovie defines the name of an external Quicktime movie to be played. 
 *  
<p>The name of the movie can be a reference to a file or to a URL.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSQuicktimeMovie_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSQuicktimeMovie_0">name</a></td>
<td>The name of a file or a URL referencing the file to be displayed by the Flash Player.</td>
</tr>

</table>

<h1 class="datasheet">History</h1>

<p>The FSQuicktimeMovie class represents the QuicktimeMovie structure from the Macromedia Flash (SWF) File Format Specification. This structure is undocumented in later versions of the specification. It is not known when it was introduced.</p>

 */  
    class DLL_DECL FSQuicktimeMovie : public FSMovieObject
    {
public:
        FSQuicktimeMovie(FSInputStream* aStream);

        FSQuicktimeMovie() : FSMovieObject(FrameLabel), name() {}

        /** Constructs an FSQuicktimeMovie object referencing the specified file.

            @param aString the file or URL where the file is located.
            */
        FSQuicktimeMovie(const char* aString) : FSMovieObject(QuicktimeMovie), name(aString) {}

        FSQuicktimeMovie* clone() const { return new FSQuicktimeMovie(*this); }

        const char* className() const;

       /** Gets the reference to the file containing the movie.

            @return the location of the file or URL.
            */
        const char* getName() const { return name.c_str(); }

        /** Sets the reference to the file containing the movie.

            @param aString the file or URL where the file is located.
            */
        void setName(const char* aString) { name = aString; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSString name;
    };
}

#endif
