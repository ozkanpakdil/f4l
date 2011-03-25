/*
 *  FSButtonColorTransform.h
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

#ifndef __FSButtonColorTransform_h__
#define __FSButtonColorTransform_h__ 1

#include "FSMovieObject.h"
#include "FSColorTransform.h"

namespace transform
{
/**
 * %FSButtonColorTransform defines the colour transform that is applied to each shape 
 * that is used to draw a button.
 * 
<p>This class is only used in conjunction with FSDefineButton. FSDefineButton2 allows colour transforms to be specified in the FSButtonRecord object that identifies each shape that is displayed for a given button state.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSButtonColorTransform_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSButtonColorTransform_1">identifier</a></td>
<td>the identifier for the FSDefineButton or FSDefineButton2 object that defines the appearance and behaviour of a button.</td>
</tr>

<tr>
<td><a name="FSButtonColorTransform_2">colorTransform</a></td>
<td>An FSColorTransform object that describes how the colours are changed.</td>
</tr>

</table>

<h1 class="datasheet">History</h1>

<p>The FSButtonColorTransform class represents the DefineButtonCXForm structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 2.</p>

 */
    class DLL_DECL FSButtonColorTransform : public FSMovieObject
    {
public:
        FSButtonColorTransform(FSInputStream* aStream);

        /** Constructs an FSButtonColorTransform object with a colour transform for the specified button.

            @param anIdentifier    the identifier of a button that this FSButtonColorTransform applies to.
            @param aColorTransform an FSColorTransform object that will be applied to the button.
            */
        FSButtonColorTransform(int anIdentifier, const FSColorTransform& aColorTransform) :
            FSMovieObject(ButtonColorTransform), identifier(anIdentifier), colorTransform(aColorTransform) {}

        FSButtonColorTransform* clone() const { return new FSButtonColorTransform(*this); }

        const char* className() const;

        /** Gets the identifier of the button that this FSButtonColorTransform object applies to. 

            @return the identifier of the button that the transform will be applied to.
            */
        int getIdentifier() const { return identifier; }

        /** Gets the colour transform that will be applied to the FSDefineButton object.

            @return the colour transform that will be applied to the button.
            */
        FSColorTransform& getColorTransform() { return colorTransform; }

        /** Sets the identifier of the button that the transform applies to.

            @param anIdentifier the identifier of the FSDefineButton object that the transform will be applied to.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Sets the colour transform.

            @param aTransform the colour transform object that will be applied to the button.
            */
        void setColorTransform(const FSColorTransform& aTransform) { colorTransform = aTransform; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int identifier;
        FSColorTransform colorTransform;
    };
}

#endif
