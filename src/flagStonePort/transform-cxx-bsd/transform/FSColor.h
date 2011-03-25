/*
 *  FSColor.h
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

#ifndef __FSColor_h__
#define __FSColor_h__ 1

#include "FSTransformObject.h"

namespace transform {
    
/**
 * %FSColor is used to represent colours. 
 * 
<p>The FSColor class supports the RGB colour space with an optional alpha channel which is used to specify the transparency of an object. An FSColor object supports 32-bit colours with 8 bits per colour channel.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSColor_0">red</a></td>
<td>The red channel of the colour, with values in the range 0..255.</td>
</tr>

<tr>
<td><a name="FSColor_1">green</a></td>
<td>The green channel of the colour, with values in the range 0..255.</td>
</tr>

<tr>
<td><a name="FSColor_2">blue</a></td>
<td>The blue channel of the colour, with values in the range 0..255.</td>
</tr>

<tr>
<td><a name="FSColor_3">alpha</a></td>
<td>The alpha channel of the colour, with values in the range 0..255.</td>
</tr>

</table>

<p>Whether a colour contains transparency information is determined by the context created by the object that contains the colour. For example colours within the FSDefineShape and FSDefineShape2 objects do not contain alpha channel information while those in an FSDefineShape3 object do. To simplify the use of the colours only a single class is provided. The alpha channel can be ignored if not required within the object the colour is defined for. When a FSColor object is encoded or decoded the object notifies the colour objects it contains whether the alpha channel information should also be encoded or decoded. As of Version 5 of the Macromedia Flash (SWF) File Format Specification only the FSPlaceObject2, FSDefineText2 and FSDefineShape3 classes use colours containing an alpha channel.</p>

<p>The class provides a range of constructors to instantiate objects using colour information presented in a variety of formats. To create a colour, specifying values for colour channels in the following order: red, green, blue and optionally alpha:</p>

<pre>
FSColor red(255, 0, 0);
FSColor green(0, 255, 0);
FSColor blue(0, 0, 255);
</pre>

<p>When the alpha channel is not specified it defaults to a value of 255 which defines the colour to be completely opaque. For transparent colours the alpha channel determines how opaque the colour is. 0 represents a fully transparent colour and 255 is fully opaque.</p>

<pre>
FSColor transparentRed(255, 0, 0, 128);
FSColor transparentGreen(0, 255, 0, 128);
FSColor transparentBlue(0, 0, 255, 128);
</pre>

<p>When the alpha channel is not specified it defaults to a value of 255 which defines the colour to be completely opaque. The classes that contain colour objects control whether the value for the alpha channel is encoded. For example FSDefineShape and FSDefineShape2 support opaque colours while FSDefineShape3 supports transparent colours. If only opaque colours are supported then the alpha channel can be ignored when creating and manipulating FSColor objects.</p>

<h1 class="datasheet">History</h1>

<p>FSColor class represents the colour data types, RGB and RGBA in the Macromedia Flash (SWF) File Format Specification. The colour data structure was available was introduced in Flash 1 and transparent colours were introduced in Flash 3.</p>

 */
    class DLL_DECL FSColor : public FSTransformObject
    {
public:
        FSColor(FSInputStream* aStream);

        /** Default constructor for an FSColor object. All the colour channels are set to the constant Transform::VALUE_NOT_SET. The principal use of this constructor is to create a colour object that may omitted from the encoding process if no colour information is specified resulting in a smaller binary representation. This constructor is for internal use and should not be used directly.
            */
        FSColor();

        /** Constructs an FSColor object containing red, green, blue and alpha channels. The value for the alpha channel may be omitted to specifying an opaque color. If omitted then the alpha channel defaults to a value of 255.
            
            @param r value for the red channel, in the range 0..255.
            @param g value for the green channel, in the range 0..255.
            @param b value for the blue channel, in the range 0..255.
            @param a value for the alpha channel, in the range 0..255.
            */
        FSColor(int r, int g, int b, int a = 255) : red(r), green(g), blue(b), alpha(a) {}
        
        /** Constructs an FSColor object with the values for the red, green, blue and alpha channels specified in an array of integers. The value for the red channel is at index 0, blue at index 1, green at index 2 and alpha at 3. This constructor is primarily intended to be used with the colour value constants defined in supporting classes the describe specific colour spaces, such as HTML colours. The FSColorTable class defines an array of colour values for each color defined the Netscape Color Table.

            @param values array of int containing values for red, green, blue and alpha channels.
            */

        FSColor(int values[4]) : red(values[0]), green(values[1]), blue(values[2]), alpha(values[3]) {}

        FSColor* clone() const;

        const char* className() const;

        /** Gets the value for the red colour channel. 

            @return the value for the red channel in the range 0..255.
            */
        int getRed() const { return red; }

        /** Gets the value for the green colour channel. 

            @return the value for the green channel in the range 0..255.
            */
        int getGreen() const { return green; }

        /** Gets the value for the blue colour channel. 

            @return the value for the blue channel in the range 0..255.
            */
        int getBlue() const { return blue; }

        /** Gets the value for the alpha colour channel. 

            @return the value for the alpha channel in the range 0..255.
            */
        int getAlpha() const { return alpha; }

        /** Set the value for the red colour channel. 

            @param aNumber value for the red channel, in the range 0..255.
            */
        void setRed(int aNumber) { red = aNumber; }

        /** Set the value for the green colour channel.

            @param aNumber value for the green channel, in the range 0..255.
            */
        void setGreen(int aNumber) { green = aNumber; }

        /** Set the value for the blue colour channel.

            @param aNumber value for the blue channel, in the range 0..255.
            */
        void setBlue(int aNumber) { blue = aNumber; }

        /** Set the value for the alpha channel.

            @param aNumber value for the alpha channel, in the range 0..255.
            */
        void setAlpha(int aNumber) { alpha = aNumber; }

        /** Set the values for the red, green and blue colour channels. If omitted then the alpha channel defaults to a value of 255.

            @param r value for the red channel, in the range 0..255.
            @param g value for the green channel, in the range 0..255.
            @param b value for the blue channel, in the range 0..255.
            @param a value for the alpha channel, in the range 0..255.
            */
        void setChannels(int r, int g, int b, int a = 255)
        {
            red = r;
            green = g;
            blue = b;
            alpha = a;
        }
        
        /** Set the values for each channel using an array of integers. The value for the red channel is at index 0, blue at index 1, green at index 2 and alpha at index 3.

            @param channels int array containing values for red, green, blue and alpha channels.
            */
        void setChannels(int channels[4])
        {
            red = channels[0];
            green = channels[1];
            blue = channels[2];
            alpha = channels[3];
        }        

        /** containsColor is used internally to identify colour objects that are optional in a given class e.g. FSText. Returns true if any of the color channels is set to a value, returns false if all the colour channels are set to Transform::VALUE_NOT_SET.
            
            @return true if the red, green, blue or alpha channels is set, false is all values are Transform::VALUE_NOT_SET.
            */
        bool containsColor() const;

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int red;
        int green;
        int blue;
        int alpha;
    };
} 

#endif
