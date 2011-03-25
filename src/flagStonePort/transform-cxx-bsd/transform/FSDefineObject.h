/*
 *  FSDefineObject.h
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

#ifndef __FSDefineObject_h__
#define __FSDefineObject_h__ 1

#include "FSMovieObject.h"

namespace transform
{
/**
The %FSDefineObject is an base class for the classes that define the different 
types of object used to create images, buttons, shapes etc. in a Flash file. 
Each such object contains a unique identifier that is used to reference the 
object when performing operations such as placing it in the display list using 
the FSPlaceObject class, etc. The %FSDefineObject manages the encoding and 
decoding of this identifier.

Identifiers are unique within a given movie. The FSMovie class is maintains an 
internal counter which is used to generate the identifiers that are assigned 
to classes derived from FSDefineObject.

Two accessor methods, getIdentifier() and setIdentifier() are used to retrieve 
and update the unique identifier assigned to an object.
*/
    class DLL_DECL FSDefineObject : public FSMovieObject
    {
public:
        FSDefineObject(int aType, int anIdentifier) : FSMovieObject(aType), identifier(anIdentifier) {}

        FSDefineObject(const FSDefineObject& rhs);

        FSDefineObject& operator= (const FSDefineObject& rhs);

        /** Returns the unique identifier assigned to this definition object. 

            @return the unique identifier for the object.
            */
        int getIdentifier() const { return identifier; }

        /** Sets the identifier used to uniquely identify the object within a given FSMovie.

            @param anIdentifier a unique identifier for the object. The value must be in the range 1..65535.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int identifier;
    };
} 

#endif
