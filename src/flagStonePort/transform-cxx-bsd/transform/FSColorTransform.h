/*
 *  FSColorTransform.h
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

#ifndef __FSColorTransform_h__
#define __FSColorTransform_h__ 1

#include "FSTransformObject.h"

namespace transform
{
    class FSStream;
    
    /**
     * The %FSColorTransform is used to change the colour of a shape or button without changing 
     * the values in the original definition of the object.
     * 
<p>Two types of transformation are supported: <b>Add</b> and <b>Multiply</b></p>

<p>In Add transformations a value is added to each colour channel:</p>

<pre>
newRed = red + addRedTerm
newGreen = green + addGreenTerm
newBlue = blue + addBlueTerm
newAlpha = alpha + addAlphaTerm
</pre>

<p>In Multiply transformations each colour channel is multiplied by a given value:</p>

<pre>
newRed = red * multiplyRedTerm
newGreen = green * multiplyGreenTerm
newBlue = blue * multiplyBlueTerm
newAlpha = alpha * multiplyAlphaTerm
</pre>

<p>Add and Multiply transforms may be combined in which case the multiply terms are
applied to the colour channel before the add terms.</p>

<pre>
newRed = (red * multiplyRedTerm) + addRedTerm
newGreen = (green * multiplyGreenTerm) + addGreenTerm
newBlue = (blue * multiplyBlueTerm) + addBlueTerm
newAlpha = (alpha * multiplyAlphaTerm) + addAlphaTerm
</pre>

<p>For each type of transform the result of the calculation is limited to the range 0..255. If the result is less than 0 or greater than 255 then it is clamped at 0 and 255 respectively.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSColorTransform_0">multiplyRed</a></td>
<td>The multiply term for the red colour channel.</td>
</tr>

<tr>
<td><a name="FSColorTransform_1">multiplyGreen</a></td>
<td>The multiply term for the green colour channel.</td>
</tr>

<tr>
<td><a name="FSColorTransform_2">multiplyBlue</a></td>
<td>The multiply term for the blue colour channel.</td>
</tr>

<tr>
<td><a name="FSColorTransform_3">multiplyAlpha</a></td>
<td>The optional multiply term for the alpha colour channel.</td>
</tr>

<tr>
<td><a name="FSColorTransform_4">addRed</a></td>
<td>The add term for the red colour channel.</td>
</tr>

<tr>
<td><a name="FSColorTransform_5">addGreen</a></td>
<td>The add term for the green colour channel.</td>
</tr>

<tr>
<td><a name="FSColorTransform_6">addBlue</a></td>
<td>The add term for the blue colour channel.</td>
</tr>

<tr>
<td><a name="FSColorTransform_7">addAlpha</a></td>
<td>The optional add term for the alpha colour channel.</td>
</tr>

</table>

<p>Not all objects containing a colour transform use the add or multiply terms defined for the alpha channel. The colour objects defined in an FSDefineButton, FSButtonColorTransform or FSPlaceObject object do not use the alpha channel. Transparent colours was introduced in Flash 3. The "parent" object that contains the colour transform controls whether the alpha channel information is encoded or not. Simplifying the alpha channel is not sufficient.</p>

<h1 class="datasheet">Examples</h1>

<p>The class provides a range of constructors to support the different colour transformations. To create a colour transform object specify the values for colour channels in the following order: red, green, blue and optionally alpha:</p>

<pre>
float multRed = 1.5f;
float multGreen = 1.5f;
float multBlue = 1.5f;
float multAlpha = 1.5f;

FSColorTransform multiply(multRed, multGreen, multBlue);

FSColorTransform multiplyWithAlpha(multRed, multGreen, multBlue, multAlpha);
</pre>

<pre>
int addRed = 128;
int addGreen = 128;
int addBlue = 128;
int addAlpha = 128;

FSColorTransform add(addRed, addGreen, addBlue);

FSColorTransform addWithAlpha(addRed, addGreen, addBlue, addAlpha);
</pre>


<p>For transforms combining both multiply and add terms:</p>

<pre>
int addRed = 128;
int addGreen = 128;
int addBlue = 128;
int addAlpha = 128;

float multRed = 1.5f;
float multGreen = 1.5f;
float multBlue = 1.5f;
float multAlpha = 1.5f;

FSColorTransform combined(multRed, multGreen, multBlue, addRed, addGreen, addBlue);

FSColorTransform combinedWithAlpha(multRed, multGreen, multBlue, multAlpha, 
    addRed, addGreen, addBlue, addAlpha); 
</pre>


<h1 class="datasheet">History</h1>

<p>The FSCoordTransform class represents the CXForm and CXFormWithAlpha data structures from the Macromedia Flash (SWF) File Format Specification. They were introduced in Flash 1 and Flash 3 respectively.</P>

     */
    class DLL_DECL FSColorTransform : public FSTransformObject
    {
public:
        FSColorTransform(FSInputStream* aStream);

        /** Constructs an FSColorTransform object defining a unity transform. If the transform is applied to a shape its colour will not change.
            */
        FSColorTransform() : multiplyRed(1.0f), multiplyGreen(1.0f), multiplyBlue(1.0f), multiplyAlpha(1.0f), addRed(0), addGreen(0), addBlue(0), addAlpha(0) {}
        
        /** Constructs an FSColorTransform object with the specified add terms, including the alpha channel.

            Each colour channel is transformed by the following calculation:
        
            \verbatim
            newRed = red + addRedTerm
            newGreen = green + addGreenTerm
            newBlue = blue + addBlueTerm
            newAlpha = alpha + addAlphaTerm
            \endverbatim
            
            In the Flash Player the value assigned to the respective colour channel is clamped to the range 0..255.
            
            @param redTerm value to add to the red colour channel.
            @param greenTerm value to add to the green colour channel.
            @param blueTerm value to add to the blue colour channel.
            @param alphaTerm value to add to the alpha colour channel.
            */
        FSColorTransform(int redTerm, int greenTerm, int blueTerm, int alphaTerm = 0) : multiplyRed(1.0f), multiplyGreen(1.0f), multiplyBlue(1.0f), multiplyAlpha(1.0f), addRed(redTerm), addGreen(greenTerm), addBlue(blueTerm), addAlpha(alphaTerm) {}
        
        /** Constructs a FSColorTransform object initialised with the specified multiply terms, including the alpha channel.
    
            Each colour channel is transformed by the following calculation:
            
            \verbatim
            newRed = red * multiplyRedTerm
            newGreen = green * multiplyGreenTerm
            newBlue = blue * multiplyBlueTerm
            newAlpha = alpha * multiplyAlphaTerm
            \endverbatim
            
            In the Flash Player the value assigned to the respective colour channel is clamped to the range 0..255.
            
            @param redTerm value to multiply the red colour channel by.
            @param greenTerm value to multiply the green colour channel by.
            @param blueTerm value to multiply the blue colour channel by.
            @param alphaTerm value to multiply the alpha colour channel by.
            */
        FSColorTransform(float redTerm, float greenTerm, float blueTerm, float alphaTerm = 1.0f)  :
            multiplyRed(redTerm), multiplyGreen(greenTerm), multiplyBlue(blueTerm), multiplyAlpha(alphaTerm), addRed(0), addGreen(0), addBlue(0), addAlpha(0) {}

        /** Constructs a FSColorTransform object initialised with the specified addition and multiplication terms. 
    
            Each colour channel is transformed by the following calculation:
            
            \verbatim
            newRed = (red * multiplyRedTerm) + addRedTerm
            newGreen = (green * multiplyGreenTerm) + addGreenTerm
            newBlue = (blue * multiplyBlueTerm) + addBlueTerm
            \endverbatim
            
            The multiply and add terms for the alpha channel default to 1.0 and 0 respectively so for objects that use the alpha channel information then the alpha channel will remain unchanged.
            
            In the Flash Player the value assigned to the respective colour channel is clamped to the range 0..255.
            
            @param multRedTerm value to multiply the red colour channel by.
            @param multGreenTerm value to multiply the green colour channel by.
            @param multBlueTerm value to multiply the blue colour channel by.
            @param addRedTerm value to add to the red colour channel.
            @param addGreenTerm value to add to the green colour channel.
            @param addBlueTerm value to add to the blue colour channel.
            */
        FSColorTransform(float multRedTerm, float multGreenTerm, float multBlueTerm, int addRedTerm, int addGreenTerm, int addBlueTerm) : multiplyRed(multRedTerm), multiplyGreen(multGreenTerm), multiplyBlue(multBlueTerm), multiplyAlpha(1.0f), addRed(addRedTerm), addGreen(addGreenTerm), addBlue(addBlueTerm), addAlpha(0) {}

        /** Constructs a FSColorTransform object initialised with the specified addition and multiplication terms, including alpha channel values. 
    
            Each colour channel is transformed by the following calculation:
            
            \verbatim
            newRed = (red * multiplyRedTerm) + addRedTerm
            newGreen = (green * multiplyGreenTerm) + addGreenTerm
            newBlue = (blue * multiplyBlueTerm) + addBlueTerm
            newAlpha = (alpha * multiplyAlphaTerm) + addAlphaTerm
            \endverbatim

            In the Flash Player the value assigned to the respective colour channel is clamped to the range 0..255.
            
            @param multRedTerm value to multiply the red colour channel by.
            @param multGreenTerm value to multiply the green colour channel by.
            @param multBlueTerm value to multiply the blue colour channel by.
            @param multAlphaTerm value to multiply the alpha colour channel by.
            @param addRedTerm value to add to the red colour channel.
            @param addGreenTerm value to add to the green colour channel.
            @param addBlueTerm value to add to the blue colour channel.
            @param addAlphaTerm value to add to the alpha colour channel.
            */
        FSColorTransform(float multRedTerm, float multGreenTerm, float multBlueTerm, float multAlphaTerm, int addRedTerm, int addGreenTerm, int addBlueTerm, int addAlphaTerm) : multiplyRed(multRedTerm), multiplyGreen(multGreenTerm), multiplyBlue(multBlueTerm), multiplyAlpha(multAlphaTerm), addRed(addRedTerm), addGreen(addGreenTerm), addBlue(addBlueTerm), addAlpha(addAlphaTerm) {}

        FSColorTransform* clone() const { return new FSColorTransform(*this); }

        const char* className() const;

        /** Gets the value of the multiply term for the red channel. 

            @return the value that will be multiplied with the red colour channel's value.
            */
        float getMultiplyRed() const { return multiplyRed; }

        /** Gets the value of the multiply term for the green channel. 

            @return the value that will be multiplied with the green colour channel's value.
            */
        float getMultiplyGreen() const { return multiplyGreen; }

        /** Gets the value of the multiply term for the blue channel. 

            @return the value that will be multiplied with the blue colour channel's value.
            */
        float getMultiplyBlue() const { return multiplyBlue; }

        /** Gets the value of the multiply term for the alpha channel. 

            @return the value that will be multiplied with the alpha colour channel's value.
            */
        float getMultiplyAlpha() const { return multiplyAlpha; }

        /** Gets the value of the add term for the red channel. 

            @return the value that will be added to the red colour channel's value.
            */
        int getAddRed() const { return addRed; }

        /** Gets the value of the add term for the green channel. 

            @return the value that will be added to the green colour channel's value.
            */
        int getAddGreen() const { return addGreen; }

        /** Gets the value of the add term for the blue channel. 

            @return the value that will be added to the blue colour channel's value.
            */
        int getAddBlue() const { return addBlue; }

        /** Gets the value of the add term for the alpha channel. 

            @return the value that will be added to the alpha colour channel's value.
            */
        int getAddAlpha() const { return addAlpha; }

        /** Sets the value for the multiplyTerm which will be applied to the red colour channel.

            @param aNumber the value to be multiplied with the red colour channel's value.
            */
        void setMultiplyRed(float aNumber) { multiplyRed = aNumber; }

        /** Sets the value for the multiplyTerm which will be applied to the green colour channel.

            @param aNumber the value to be multiplied with the green colour channel's value.
            */
        void setMultiplyGreen(float aNumber) { multiplyGreen = aNumber; }

        /** Sets the value for the multiplyTerm which will be applied to the blue colour channel.

            @param aNumber the value to be multiplied with the blue colour channel's value.
            */
        void setMultiplyBlue(float aNumber) { multiplyBlue = aNumber; }

        /** Sets the value for the multiplyTerm which will be applied to the alpha colour channel.

            @param aNumber the value to be multiplied with the alpha colour channel's value.
            */
        void setMultiplyAlpha(float aNumber) { multiplyAlpha = aNumber; }

        /** Sets the values for the multiply terms for each of the colour channels
    
            @param redTerm value to multiply the red colour channel by.
            @param greenTerm value to multiply the green colour channel by.  
            @param blueTerm value to multiply the blue colour channel by.
            @param alphaTerm value to multiply the alpha colour channel by. 
            */
        void setMultiplyTerms(float redTerm, float greenTerm, float blueTerm, float alphaTerm = 1.0f)
        {
            multiplyRed = redTerm;
            multiplyGreen = greenTerm;
            multiplyBlue = blueTerm;
            multiplyAlpha = alphaTerm;
        }
        
        /** Sets the value for the addTerm which will be applied to the red colour channel.

            @param aNumber the value to be added to the red colour channel's value.
            */
        void setAddRed(int aNumber) { addRed = aNumber; }

        /** Sets the value for the addTerm which will be applied to the green colour channel.

            @param aNumber the value to be added to the green colour channel's value.
            */
        void setAddGreen(int aNumber) { addGreen = aNumber; }

        /** Sets the value for the addTerm which will be applied to the blue colour channel.

            @param aNumber the value to be added to the blue colour channel's value.
            */
        void setAddBlue(int aNumber) { addBlue = aNumber; }

        /** Sets the value for the addTerm which will be applied to the alpha colour channel.

            @param aNumber the value to be added to the alpha colour channel's value.
            */
        void setAddAlpha(int aNumber) { addAlpha = aNumber; }

        /** Sets the values for the add terms for each of the colour channels.
    
        @param redTerm value to add to the red colour channel.
        @param greenTerm value to add to the green colour channel.  
        @param blueTerm value to add to the blue colour channel.
        @param alphaTerm value to add to the alpha colour channel. 
        */
        void setAddTerms(int redTerm, int greenTerm, int blueTerm, int alphaTerm = 0)
        {
            addRed = redTerm;
            addGreen = greenTerm;
            addBlue = blueTerm;
            addAlpha = alphaTerm;
        }
        
        /** Returns true if the values for the add and multiply terms represent a unity transform - one which will not change the color of a shape. Whether the alpha channel is included is determined by the context associated with the FSStream object.

            @param aStream the FSOutputStream used to encoded the transform.
            @return true if the object represents a unity transform, false otherwise.
            */
        bool isUnityTransform(FSStream* aStream) const;

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int addFieldSize(FSOutputStream* aStream) const;
        int multiplyFieldSize(FSOutputStream* aStream) const;
        int fieldSize(FSOutputStream* aStream) const;
        
        bool containsAddTerms(FSStream* aStream) const;
        bool containsMultiplyTerms(FSStream* aStream) const;

        float multiplyRed;
        float multiplyGreen;
        float multiplyBlue;
        float multiplyAlpha;
        
        int addRed;
        int addGreen;
        int addBlue;
        int addAlpha;
    };
} 

#endif
