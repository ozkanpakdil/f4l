/*
 *  FSPathsArePostscript.h
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

#ifndef __FSPathsArePostscript_h__
#define __FSPathsArePostscript_h__ 1

#include "FSMovieObject.h"

namespace transform
{
/**
 * The %FSPathsArePostscript class is used to notify the Flash Player that the glyphs encoded
 * in a font definition were derived from a PostScript-based font definition.
 * 
<p>The PathsArePostscript is not documented in the current Macromedia Flash (SWF) 
File Format Specification. IT was referenced in earlier editions but its exact
function was not known. It is thought that is used to signal to the Flash 
Player that the paths describing the outlines of the glyphs in a font were 
derived from a font defined using Postscript. The information can be used to 
provide better rendering of the glyphs.</P>

<p>It does not affect the paths defined in FSCurve objects which describe 
quadratic Bezier curves. It is included in the package for completeness.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSPathsArePostscript_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

</table>

<h1 class="datasheet">History</h1>

<p>The FSPathsArePostscript class represents the PathsArePostscript tag from the 
Macromedia Flash (SWF) File Format Specification. It is not documented in later 
editions of the specification. It is not known when this tag was added.</p>

 */  
    class DLL_DECL FSPathsArePostscript : public FSMovieObject
    {
public:
        FSPathsArePostscript(FSInputStream* aStream);

        /** Constructs an FSPathsArePostscript object. */
        FSPathsArePostscript() : FSMovieObject(PathsArePostscript) {}

        FSPathsArePostscript* clone() const { return new FSPathsArePostscript(*this); }

        const char* className() const;

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
    };
} 

#endif
