/*
 *  FSCoordTransform.h
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

#ifndef __FSCoordTransform_h__
#define __FSCoordTransform_h__ 1

#include "FSTransformObject.h"

namespace transform {
    
    /**
     * %FSCoordTransform is used to specify two-dimensional coordinate transforms, allowing an 
     * object to be scaled, rotated or moved without changing the original definition of how 
     * the object is drawn.
     * 
<p>A two-dimensional transform is defined using a 3x3 matrix and the new values for a pair of coordinates (x,y) are calculated using the following matrix multiplication:</p>

<img src="transform.gif">

<p>Different transformations such as scaling, rotation, shearing and translation can be performed using the above matrix multiplication. More complex transformations can be defined by performing successive matrix multiplications in a process known as compositing. This allows a complex transformations to performed on an object.</p>

<p>The FSCoordTransform contains a 3x3 array for defining the transformations. However when it is encoded the matrix is reduced to the following set attributes:</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSCoordTransform_0">scaleX</a></td>
<td>The value to scale the shape in the x direction combined with the cosine 
component of any rotation.</td>
</tr>

<tr>
<td><a name="FSCoordTransform_1">scaleY</a></td>
<td>The value to scale the shape in the x direction combined with the cosine 
component of any rotation.</td>
</tr>

<tr>
<td><a name="FSCoordTransform_2">rotate0</a></td>
<td>The sine component of any rotation applied to the shape.</td>
</tr>

<tr>
<td><a name="FSCoordTransform_3">rotate1</a></td>
<td>The negative sine component of any rotation applied to the shape.</td>
</tr>

<tr>
<td><a name="FSCoordTransform_4">translateX</a></td>
<td>The x-coordinate of any translation applied to the shape.</td>
</tr>

<tr>
<td><a name="FSCoordTransform_5">translateY</a></td>
<td>The y-coordinate of any translation applied to the shape.</td>
</tr>

</table>

<h2 class="datasheet">Examples</h1>

<p>The FSCoordTransform provides a set of methods for generating the matrices that will perform specific transformations. Methods are provided that represent matrices for performing translation, scaling, rotation and shearing transformations.</p>

<pre>
FSCoordTransform transform;

transform.scale(2.0, 2.0); // scale(x,y)
transform.rotate(30.0);  // rotate(degrees)
transform.shear(1.2, 0.9);  // shear(x, y)
</pre>


<p>The composite method can be used to multiply two matrices together to create complex transformations though successive compositing steps. For example to place a new object on the screen first rotating it by 30 degrees and scaling it to twice its original size the required transform can be constructed using the following steps:</p>

<pre>
FSCoordTransform transform();

transform.scale(2.0, 2.0);
transform.rotate(30.0);

int layer = 1;
int identifier = movie.newIdentifier();

FSDefineShape* shape = new FSDefineShape(identifier, ...);

FSPlaceObject2* placeShape = new FSPlaceObject2(identifier, layer, transform);
</pre>


<p>Compositing transforms are not commutative, the order in which transformations are applied will affect the final result. For example consider the following pair if transforms:</p>

<pre>
FSCoordTransform transform();

transform.translate(100, 100);
transform.scale(2.0, 2.0);
</pre>     

<p>The composite transform places an object at the coordinates (100,100) then scales it to twice its original size. If the transform was composited in the opposite order:</p>

<pre>
FSCoordTransform transform();

transform.scale(2.0, 2.0);
transform.translate(100, 100);
</pre>     


<p>Then the coordinates for the object's location would also be scaled, placing the object at (200,200).</p>

<p>Arbitrary coordinate transforms are created by specifying the 3 by 3 array of floating-point values in the constructor:</p>

<pre>
float[][] matrix = new float[][] {
    {0.923f, 0.321f, 1000.0f}, 
    {0.868f, 0.235f, 1000.0f}, 
    {0.000f, 0.000f, 1.0000f}
};

FSCoordTransform transform = new FSCoordTransform(matrix);
</pre>

<p>A constructor is also provided to handle the most common composite transform - scaling and translating an object at the same time:</p>

<pre>
FSCoordTransform composite(100, 150, 2.0, 2.0);
</pre>

<p>Will place the object at the twip coordinates (100, 150) and scale the object to twice its original size.</P>

<h1 class="datasheet">History</h1>

<p>The FSCoordTransform class represents the Matrix data structure from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

     */
    class DLL_DECL FSCoordTransform : public FSTransformObject
    {
public:
        FSCoordTransform(FSInputStream* aStream);

        /** Constructs an FSCoordTransform object defining a unity transform. If the transform is applied to a shape its location or appearance will not change.
            */
        FSCoordTransform();

        /** Constructs an FSCoordTransform object defining a translation transform that will change an objects location to the specified coordinates. 
        
            @param x the x-coordinate where the object will be displayed.
            @param y the y-coordinate where the object will be displayed.
            */
        FSCoordTransform(int x, int y);

        /** 
        * Constructs an FSCoordTransform object defining translation and scaling transforms
        * that will change an object's location and size.
        
            @param x the x-coordinate where the object will be displayed.
            @param y the y-coordinate where the object will be displayed.
            @param scaleX value to scale the object in the x direction.
            @param scaleY value to scale the object in the y direction.
            */
        FSCoordTransform(int x, int y, double scaleX, double scaleY);

        /** Constructs an FSCoordTransform object with the specified transformation matrix. Note the matrix must contain translation values (m[0][2] and m[1][2]) expressed in twips.
        
            @param aMatrix a 3x3 array of floats containing the values defining the transform.
            */
        FSCoordTransform(const float aMatrix[][3]);

        FSCoordTransform* clone() const;

        const char* className() const;

        /** Sets the translation points of the transform.
        * 
        * @param x the x-coordinate where the object will be displayed.
        * @param y the y-coordinate where the object will be displayed.
        */
        void translate(int x, int y);

        /** Sets the scaling factor for the transform.
        * 
        * @param x value to scale the object in the x direction.
        * @param y value to scale the object in the y direction.
        */
        void scale(double x, double y);

        /** Sets the angle which the transform will rotate an object.
        * 
        * @param angle value, in degrees, to rotate the object clockwise.
        */
        void rotate(double angle);

        /** Sets the shearing factor for the transform.
        * 
        * @param x value to shear the object in the x direction.
        * @param y value to shear the object in the y direction.
        */
        void shear(double x, double y);

        /**
        * Applies the transformation to the coordinates of a point.
        * 
        * @param x a reference to the x-coordinate of a point.
        * @param y a reference to the y-coordinate of a point.
        * @return an array containing the transformed point.
        */
        void transformPoint(int& x, int& y);

        /** Gets the 3 X 3 array that is used to store the transformation values. Note the matrix will contain translation values (aMatrix[0][2] and aMatrix[1][2]) expressed in twips.

            @return an array, float[3][3], containing the values for the transformation matrix.
            */
        void getMatrix(float aMatrix[3][3]) const;

        /** Sets the values in the 3 X 3 array that is used to store the transformation values. Note the matrix must contain translation values (m[0][2] and m[1][2]) expressed in twips.

            @param aMatrix a 3x3 array of floats containing the values defining the transform.
            */
        void setMatrix(const float aMatrix[][3]);

        /** Composite the 3 X 3 matrix with the FSCoordTransform argument. This method is used to create multiple transformation effects that can be applied to an object in a single step. Using the instance method fixes the order in which the transforms are composited. Since matrix multiplication is not commutative this limits the number of complex transforms that can be generated when compared to the class method.

            @param transform an FSCoordTransform object to composite with this instance.
            */
        void composite(const FSCoordTransform& transform);

        /** Returns true if the values in the transformation matrix represent a unity transform - one which will not change the physical appearance or location of a shape.

            @return true if the object represents a unity transform, false otherwise.
            */
        bool isUnityTransform() const;

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        bool containsScaling() const;
        bool containsRotation() const;
        bool containsTranslation() const;
        int scaleFieldSize() const;
        int rotateFieldSize() const;
        int translateFieldSize() const;
        void composite(float m[3][3]);

        float matrix[3][3];
    };
} 

#endif
