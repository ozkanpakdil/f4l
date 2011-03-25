/*
 *  FSExport.h
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

#ifndef __FSExport_h__
#define __FSExport_h__ 1

#include "FSMovieObject.h"

#include "FSVector.h"
#include "FSObjectName.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSObjectName>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * %FSExport is used to export shapes and other objects so they can be used in another Flash file. 
 * 
<p>Since the identifier for an object is only unique within a given Flash file, each object exported must be given a name so it can referenced when it is imported.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSExport_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSExport_1">objects</a></td>
<td>A HashTable containing key-value pairs where the key is the identifier of the object being exported and the value is name assigned to the object so it can be referenced when it is imported into a Flash file.</td>
</tr>

</table>

<h1 class="datasheet">Examples</h1>

<P>To export an object from a Flash file:</P>

<pre>
FSDefineShape shape = new FSDefineShape(...);

movie.add(shape);
movie.add(new FSExport(shape.getIdentifier(), "Shape"));
</pre>

The object can then be imported into another file:

<pre>
movie.add(new FSImport("exportFile.swf", movie.newIdentifier(), "Shape"));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSExport class represents the ExportAssets tag in the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 5.</p>

 */  
    class DLL_DECL FSExport : public FSMovieObject
    {
public:
        FSExport(FSInputStream* aStream);

        FSExport() : FSMovieObject(Export), objects() {}

        /** Constructs an FSExport object that exports the object with the specified identifier. The exported object is assigned the specified name to allow it to be referenced in files importing the object. 
    
            @param anIdentifier the identifier of the object to be exported.
            @param aString the name assigned to the exported object.
            */
        FSExport(int anIdentifier, const char* aString) : FSMovieObject(Export), objects()
        {
            objects.push_back(FSObjectName(anIdentifier, aString));
        }

        /** Constructs an FSExport object that exports an array of objects. Each FSObjectName object contains the object's identifier and a name that allows the object to be referenced in the file where it is imported.

            @param anArray an array of FSObjectName objects.
            */
        FSExport(const FSVector<FSObjectName>& anArray);

        FSExport* clone() const { return new FSExport(*this); }

        const char* className() const;

        /** Adds the identifier and name to the list of objects being exported.

            @param anIdentifier the identifier of the object to be exported.
            @param aString the name assigned to the exported object.
            */
        void add(int anIdentifier, const char* aString)
        {
            objects.push_back(FSObjectName(anIdentifier, aString));
        }

        /** Adds the array of objects to list of objects being exported.

            @param anArray an array of FSObjectName objects.
            */
        void add(const FSVector<FSObjectName>& anArray);

        /** Gets the objects to be exported. 

            @return the an array of FSObjectName objects.
            */
        FSVector<FSObjectName>& getObjects() { return objects; }

        /** Sets the array of objects to be exported.

            @param anArray the array of FSObjectName objects.
            */
        void setObjects(const FSVector<FSObjectName>& anArray) { objects = anArray; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSVector<FSObjectName>objects;
    };
}

#endif
