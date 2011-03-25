/*
 *  FSShape.h
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

#ifndef __FSShape_h__
#define __FSShape_h__ 1

#include "FSVector.h"

#include "FSTransformObject.h"
#include "FSShapeObject.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSShapeObject*>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSShape is a container for the shape objects (%FSLine, %FSCurve and %FSShapeStyle objects) 
 * that describe how a particular shape is drawn.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSShape_0">objects</a></td>
<td>An array of shape (FSLine, FSCurve and FSShapeStyle) objects which are used to draw the outline of the shape.</td>
</tr>

</table>
</p>

<p>FSShapes are used in shape and font definitions. The FSShape class is used to simplify the design of these classes and provides no added functionality other than acting as a container class.</p>

<h1 class="datasheet">History</h1>

<p>The FSShape class represents the Shape record from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 1.</p>

 */
    class DLL_DECL FSShape : public FSTransformObject
    {
public:
        FSShape(FSInputStream* aStream);

        /** Constructs an FSShape object with no shape objects. */
        FSShape() : objects() {}

        /** Constructs an FSShape object, specifying the ShapeRecords that describe how the shape is drawn.

            @param anArray the array of shape records.
            */
        FSShape(const FSVector<FSShapeObject*>& anArray) : objects(anArray) {}

        FSShape(const FSShape& rhs);

        ~FSShape();

        FSShape& operator= (const FSShape& rhs);

        FSShape* clone() const { return new FSShape(*this); }

        const char* className() const;

        /** Add a shape object to the array of shape objects.

            @param anObject a shape object.
            */
        void add(FSShapeObject* anObject) { objects.push_back(anObject); }

        /** Add all the shape object in the array to the end of the shape objects array.

            @param anArray an array of shape objects.
            */
        void add(const FSVector<FSShapeObject*>& anArray);

        /** Gets the array of shape objects that define the shape.

            @return the array of shape objects.
            */
        FSVector<FSShapeObject*>& getObjects() { return objects; }

        /** Sets the array of shape objects.

            @param anArray the array of shape objects.
            */
        void setObjects(const FSVector<FSShapeObject*>& anArray) { objects = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSShapeObject* shapeRecordFromStream(FSInputStream* aStream);

        FSVector<FSShapeObject*> objects;
    };
} 
    
#endif
