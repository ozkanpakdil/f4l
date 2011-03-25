/*
 *  FSButton.h
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

#ifndef __FSButton_h__
#define __FSButton_h__ 1

#include "FSTransformObject.h"

#include "FSCoordTransform.h"
#include "FSColorTransform.h"

namespace transform
{
/**
 * %FSButton identifies the shape that is drawn when a button is in a particular state. 
 * 
<p>Shapes can be drawn for each of three button states, Over, Up and Down. Creating a button with more than one FSButton object each referencing a different shape allows the button to be animated as it is clicked.</p>

<p>A shape is also used to define active area of the button. When defining the active area the outline of the shape defines the boundary of the area. The shape is not drawn when the button is displayed. The button will only respond to mouse events when the cursor is placed inside the active area.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSButton_0">state</a></td>
<td>the state(s) the button is in when the shape will be drawn, either Up, Over or Down. Active is used to denote when a shape defined the active area of a button.</td>
</tr>

<tr>
<td><a name="FSButton_1">identifier<a/></td>
<td>The identifier, in the range 1..65535, of the object that contains the definition of the shape that is drawn.</td>
</tr>

<tr>
<td><a name="FSButton_2">layer</a></td>
<td>The layer number defines the order in which shapes are displayed. Shapes with a higher layer number are displayed in front of those on a lower layer. Complex buttons can be created by displaying more than one shape for a given button state. The layer number may be in the range 1..65535 - the range is determined by the size of the field when the value is encoded to a Flash file - however the vast majority of buttons will typically only use layer numbers less than 10.</td>
</tr>

<tr>
<td><a name="FSButton_3">transform</a></td>
<td>an FSCoordTransform object that defines a coordinate transform that will be applied to the shape when it is displayed. The transform is most commonly used to offset shapes to create a 3-D appearance. The size may also be changed allowing a single shape definition to be used to display buttons in a range of sizes while still maintaining the same look and feel.</td>
</tr>

</table>

<p>An FSButton can define the appearance of the button for more than one state. Multiple states can be defined by bitwise Or-ing individual state codes together:</p>

<pre>
int buttonState = FSButton::Up | FSButton::Over;
</pre>

<p>The purpose of the layer attribute is to define the order in which shapes are displayed for a given button state. This is analogous to the layer number in the Flash Player's display list - specified using objects such as FSPlaceObject. When a button is displayed it is placed on a single layer in the display list and the layer numbers assigned to shapes in a FSButton object do not interfere with shapes assigned to the same layer in the display list.</p>

<p>The coordinate transform is used to change the appearance of the button without changing the original shape definitions. If it is omitted then a unity transform will be encoded which does not change the way the shape is drawn.</p>

<h1 class="datasheet">History</h1>

<p>The FSButton class represents the ButtonRecord structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */  
    class DLL_DECL FSButton : public FSTransformObject
    {
public:
        /** Definition of the different states a button can occupy. */
        enum buttonState { Up = 1, Over = 2, Down = 4, Active = 8 };

        FSButton(FSInputStream* aStream);

        FSButton() : state(0), identifier(0), layer(0), transform(), colorTransform() {}

        /**  Constructs an FSButton object without a coordinate or colour transform that will be applied to the shape drawn for the button states. The transforms default to unity transforms which do not change the location of colour of the shape for the button.

            @param aState the state of the button when the shape is drawn.
            @param anIdentifier the identifier of an FSDefineShape, FSDefineShape2 or FSDefineShape3 object.
            @param aLayer the layer in the display list on which the shape is drawn.
            */
        FSButton(int aState, int anIdentifier, int aLayer) : state(aState), identifier(anIdentifier), layer(aLayer), transform(), colorTransform() {}

        /**  Constructs an FSButton object with a coordinate and colour transform that will be applied to the shape drawn for the button states.

            @param aState the state of the button when the shape is drawn.
            @param anIdentifier the identifier of an FSDefineShape, FSDefineShape2 or FSDefineShape3 object.
            @param aLayer the layer in the display list on which the shape is drawn.
            @param aTransform an FSCoordTransform object that changes the appearance of the shape when it is drawn.
            @param aColorTransform an optional FSColorTransform object that changes the colour of the shape when it is drawn. This attribute is ignored when used with FSDefineButton.
            */
        FSButton(int aState, int anIdentifier, int aLayer, const FSCoordTransform& aTransform, const FSColorTransform& aColorTransform = FSColorTransform()) : state(aState), identifier(anIdentifier), layer(aLayer), transform(aTransform), colorTransform(aColorTransform) {}

        FSButton* clone() const { return new FSButton(*this); }

        const char* className() const;

        /** Get the state(s) of the button when the shape is drawn.
            
            @return the state of the button when the shape is drawn.
            */
        int getState() const { return state; }

        /** Does the Button Record defines a shape for the button's active area.

            @return a bool flag indicating whether the button record defines the button's active area.
            */
        bool isActive() const { return ((state & Active) != 0) ? true : false; }

        /** Does the Button Record define a shape for the button's 'down' state.

            @return a bool flag indicating whether the button record defines the shape for the button's 'down' state.
            */
        bool isDown() const { return ((state & Down) != 0) ? true : false; }

        /** Does the Button Record define a shape for the button's 'over' state.

            @return a bool flag indicating whether the button record defines the shape for the button's 'over' state.
            */
        bool isOver() const { return ((state & Over) != 0) ? true : false; }

        /** Does the Button Record define a shape for the button's 'up' state.

            @return a bool flag indicating whether the button record defines the shape for the     button's 'up' state.
            */
        bool isUp() const { return ((state & Up) != 0) ? true : false; }

        /** Gets the identifier of the shape that this FSButton applies to. 

            @return the identifier of the shape.
            */
        int getIdentifier() const { return identifier; }

        /** Gets the layer that the button will be displayed on.

            @return the layer on which the shape is displayed.
            */
        int getLayer() const { return layer; }

        /** Gets the coordinate transform that will be applied to the button.

            @return the coordinate transform that is applied to the shape.
            */
        FSCoordTransform& getTransform() { return transform; }

        /** Gets the colour transform that will be applied to the button.

            @return the colour transform that is applied to the shape.
            */
        FSColorTransform& getColorTransform() { return colorTransform; }

        /** Set the state(s) of the button when the shape is drawn. The shape may be drawn for more than one state. Multiple states can be defined by bitwise-OR'ing individual states together, e.g.  Up | Over.

            @return the state of the button when the shape is drawn.
            */
        void setState(int aNumber) { state = aNumber; }

        /** Sets the identifier of the  FSDefineShape, FSDefineShape2 or FSDefineShape3 object that defines the appearance of the button when it is in the specified state(s). 

            @param anIdentifier the identifier of the shape object that defines the shape's appearance.
            */
        void setIdentifier(int anIdentifier) { identifier = anIdentifier; }

        /** Sets the layer in the display list that the shape will be displayed on.

            @param aNumber the number of the layer in the display list where the shape is drawn.
            */
        void setLayer(int aNumber) { layer = aNumber; }

        /** Sets the coordinate transform that will be applied to the shape to change it's appearance.

            @param aTransform an FSCoordTransform object that will be applied to the shape.
            */
        void setTransform(const FSCoordTransform& aTransform) { transform = aTransform; }

        /** Sets the colour transform that will be applied to the shape to change it's colour. This transform is ignored when used with an FSDefineButton object.

            @param aTransform an FSColorTransform object that will be applied to the shape.
            */
        void setColorTransform(const FSColorTransform& aTransform) { colorTransform = aTransform; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int state;
        int identifier;
        int layer;
        
        FSCoordTransform transform;
        FSColorTransform colorTransform;
    };
}

#endif
