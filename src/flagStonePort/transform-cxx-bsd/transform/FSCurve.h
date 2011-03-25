/*
 *  FSCurve.h
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

#ifndef __FSCurve_h__
#define __FSCurve_h__ 1

#include "FSShapeObject.h"

namespace transform
{    
    /**
     * %FSCurve is used to define a curve. Curved lines are constructed using a Quadratic 
     * Bezier curve.
     * 
<p>The curve is specified using two points relative to the current drawing position, an off-curve control point and an on-curve anchor point which defines the end-point of the curve.</p>

<img src="quadratic.gif">

<p>To define a curve the points are defined as pairs of relative coordinates. The control point is specified relative to the current drawing point and the anchor point is specified relative to the control point. Once the line is drawn, the anchor point becomes the current drawing point.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSCurve_0">controlX</a></td>
<td>The x-coordinate of the control point relative to the current drawing point.</td>
</tr>

<tr>
<td><a name="FSCurve_1">controlY</a></td>
<td>The y-coordinate of the control point relative to the current drawing point.</td>
</tr>

<tr>
<td><a name="FSCurve_2">anchorX</a></td>
<td>The x-coordinate of the anchor point relative to the control point.</td>
</tr>

<tr>
<td><a name="FSCurve_3">anchorY</a></td>
<td>The y-coordinate of the anchor point relative to the control point.</td>
</tr>

</table>

<p>The relative coordinates are specified in twips (where 20 twips = 1 pixel) and must be in the range -65536..65535.</p>

<p>Flash does not directly support Cubic Bezier curves. Converting a Cubic Bezier curve to a Quadratic curve is a non trivial process, however the FSShapeConstructor class in the Transform Utilities framework contains an algorithm to perform the conversion simplifying the create of Shape outlines in Flash from other graphics formats.</p>

<h1 class="datasheet">History</h1>

<p>The FSCurve class represents the CurvedEdge record from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

     */
    class DLL_DECL FSCurve : public FSShapeObject
    {
public:
        FSCurve(FSInputStream* aStream);
        
        /** Constructs an FSCurve object specifying the anchor and control point coordinates. 
        
            @param cx the x-coordinate of the control point, specified relative to the current drawing point.
            @param cy the y-coordinate of the control point, specified relative to the current drawing point.
            @param ax the x-coordinate of the anchor point, specified relative to the control point.
            @param ay the y-coordinate of the anchor point, specified relative to the control point.
            */
        FSCurve(int cx, int cy, int ax, int ay) : FSShapeObject(Curve), controlX(0), controlY(0), anchorX(0), anchorY(0)
        {
            setControlX(cx);
            setControlY(cy);
            setAnchorX(ax);
            setAnchorY(ay);
        }

        FSCurve* clone() const { return new FSCurve(*this); }

        const char* className() const;

        /** Gets the x-coordinate of the control point.

            @return the x-coordinate of the control point.
            */
        int getControlX() const
        {
            return controlX;
        }

        /** Gets the y-coordinate of the control point. 

            @return the y-coordinate of the control point.
            */
        int getControlY() const
        {
            return controlY;
        }

        /** Gets the x-coordinate of the anchor point. 

            @return the x-coordinate of the anchor point.
            */
        int getAnchorX() const
        {
            return anchorX;
        }

        /** Gets the y-coordinate of the anchor point.

            @return the y-coordinate of the anchor point.
            */
        int getAnchorY() const
        {
            return anchorY;
        }
    
        /** Sets the x-coordinate of the control point.
            
            @param cx the x-coordinate of the control point.
            */
        void setControlX(int cx)
        {
            controlX = cx;
        }
    
        /** Sets the y-coordinate of the control point.

            @param cy the y-coordinate of the control point.
            */
        void setControlY(int cy)
        {
            controlY = cy;
        }

        /** Sets the x-coordinate of the anchor point.

            @param ax the x-coordinate of the anchor point.
            */
        void setAnchorX(int ax)
        {
            anchorX = ax;
        }

        /** Sets the y-coordinate of the anchor point.
            
            @param ay the y-coordinate of the anchor point.
            */
        void setAnchorY(int ay)
        {
            anchorY = ay;
        }

        /** Sets the x and y coordinates of control point.

            @param cx the x-coordinate of the control point.
            @param cy the y-coordinate of the control point.
            */
        void setControl(int cx, int cy)
        {
            controlX = cx;
            controlY = cy;
        }

        /** Sets the x and y coordinates of anchor point. 

            @param ax the x-coordinate of the anchor point.
            @param ay the y-coordinate of the anchor point.
            */
        void setAnchor(int ax, int ay)
        {
            anchorX = ax;
            anchorY = ay;
        }

        /** Sets the x and y coordinates of the control and anchor points.

            @param cx the x-coordinate of the control point.
            @param cy the y-coordinate of the control point.
            @param ax the x-coordinate of the anchor point.
            @param ay the y-coordinate of the anchor point.
            */
        void setPoints(int cx, int cy, int ax, int ay)
        {
            controlX = cx;
            controlY = cy;
            anchorX = ax;
            anchorY = ay;
        }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        int fieldSize() const;

        int controlX;
        int controlY;
        int anchorX;
        int anchorY;
    };
} 

#endif
