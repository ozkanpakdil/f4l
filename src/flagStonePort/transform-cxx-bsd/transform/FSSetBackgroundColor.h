/*
 *  FSSetBackgroundColor.h
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

#ifndef __FSSetBackgroundColor_h__
#define __FSSetBackgroundColor_h__ 1

#include "FSMovieObject.h"

#include "FSColor.h"

namespace transform
{
/**
 * %FSSetBackgroundColor sets the background colour displayed in every frame in the movie.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSSetBackgroundColor_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr><td><a name="FSSetBackgroundColor_1">color</a></td>
<td>An FSColor object that defines the background colour.</td>
</tr>

</table>

<p>Although the colour is specified using an FSColor object the colour displayed is completely opaque - the alpha channel information in the object is ignored.</p>

<p>The background colour must be set before the first frame is displayed otherwise the background colour defaults to white. This is typically the first object in a coder. If more than one FSSetBackgroundColor object is added to a movie then only first one sets the background colour. Subsequent objects are ignored.</p>

<pre>
FSMovie movie;

movie.setFrameSize(FSBounds(0, 0, 8000, 8000)); // twips = 400 x 400 pixels
movie.setFrameRate(1.0f); 1 frame per second.

movie.add(new FSSetBackgroundColor(FSColor(0xAD, 0xD8, 0xE6))); // light blue
</pre>

<h1 class="datasheet">History</h1>

<p>The FSSetBackgroundColor class represents the SetBackgroundColor tag from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSSetBackgroundColor : public FSMovieObject
    {
public:
        FSSetBackgroundColor(FSInputStream* aStream);

        /** Constructs an FSSetBackgroundColor object with the specified colour. Although the FSColor class supports an alpha channel allowing transparent colours this is ignored by the Flash Player.

            @param aColor the background colour for the movie.
            */
        FSSetBackgroundColor(const FSColor& aColor) : FSMovieObject(SetBackgroundColor), color(aColor) {}

        FSSetBackgroundColor* clone() const { return new FSSetBackgroundColor(*this); }

        const char* className() const;

        /** Gets the object defining the movie's background colour for the movie background.

            @return the FSColor object defining the background colour for the movie.
            */
        FSColor& getColor() { return color; }

        /** Sets the colour for the movie background. The alpha channel in the FSColor object is ignored and may be left at its default value.

            @param aColor the background colour for the movie.
            */
        void setColor(const FSColor& aColor) { color = aColor; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSColor color;
    };
} 

#endif
