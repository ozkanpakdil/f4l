/*
 *  FSMovieObject.h
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

#ifndef __FSMovieObject_h__
#define __FSMovieObject_h__ 1

#include "FSTransformObject.h"

namespace transform
{
/** 
 * The %FSMovieObject is the root class for objects that represent each of the 
 * tagged data structures that make up the Flash file format specification.
 *
 * Each of the major data structures defined in the Flash file format specification 
 * start with a header that contains the type identifying the data structure followed 
 * by the number of bytes that the body of the encoded data structure occupies in 
 * the file. The FSMovieObject manages the encoding and decoding of this information.
 *
 * This class is primarily used internally in the library however the getType()
 * method is useful when manipulating decoded Flash files. Rather than using the 
 * runtime type checking provided in the programming environment the method can be used 
 * to identify the class, derived from %FSMovieObject, that represents each data 
 * structure, improving performance.
 */

    class DLL_DECL FSMovieObject : public FSTransformObject
    {
public:
        /** Definition of the different types of object (derived classes of FSMovieObject) that can be added to a FSMovie object to create a Flash file. The type attribute of the FSMovieObject class is used to store the value and allows derived classes to be identified without using dynamic casting operations.
        */
        enum objectType { 
            End = 0, 
            ShowFrame = 1, 
            DefineShape = 2, 
            Free = 3, 
            PlaceObject = 4, 
            RemoveObject = 5, 
            DefineJPEGImage = 6, 
            DefineButton = 7, 
            JPEGEncodingTable = 8, 
            SetBackgroundColor = 9, 
            DefineFont = 10, 
            DefineText = 11, 
            DoAction = 12, 
            FontInfo = 13, 
            DefineSound = 14, 
            StartSound = 15, 
            DefineButtonSound = 17, 
            SoundStreamHead = 18, 
            SoundStreamBlock = 19, 
            DefineImage = 20, 
            DefineJPEGImage2 = 21, 
            DefineShape2 = 22, 
            ButtonColorTransform = 23, 
            Protect = 24, 
            PathsArePostscript = 25, 
            PlaceObject2 = 26, 
            RemoveObject2 = 28, 
            DefineShape3 = 32, 
            DefineText2 = 33, 
            DefineButton2 = 34, 
            DefineJPEGImage3 = 35, 
            DefineImage2 = 36, 
            DefineTextField = 37, 
            QuicktimeMovie = 38,
            DefineMovie = 38, 
            DefineMovieClip = 39, 
            SerialNumber = 41, 
            FrameLabel = 43, 
            SoundStreamHead2 = 45, 
            DefineMorphShape = 46, 
            DefineFont2 = 48, 
            Export = 56, 
            Import = 57, 
            EnableDebugger = 58, 
// Flash 6
            Initialize = 59,
            DefineVideo = 60,
            VideoFrame = 61,
            FontInfo2 = 62,
            EnableDebugger2 = 64,
// Flash 7
            LimitScript = 65,
            TabOrder = 66,
// End Flash 7
            QuickTime = 170, 
            Pointer = 1023
        };

        FSMovieObject(int aType) : type(aType), length(0), extendLength(false) {}
        
        FSMovieObject(const FSMovieObject& rhs);

        virtual FSMovieObject* clone() const = 0;

        FSMovieObject& operator= (const FSMovieObject& rhs);

        /** Gets the code identifying the type of Flash data structure that a derived class represents. This method can be used to identify derived classes rather than using  dynamic casting.

            @return the code used to denote the type of the object.
            */
        int getType() const { return type; }

        /** Returns the number of bytes in the body of a data structure when an object is decoded from its binary representation. The value returned is valid when an object is decoded from a Flash file and no changes have been made. 

            @return the number of bytes decoded from the binary data.
            */
        int getLength() const { return length; }

        bool getExtendLength() const { return extendLength; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

protected:
        int type;
        int length;
        bool extendLength;
    };
} 

#endif
