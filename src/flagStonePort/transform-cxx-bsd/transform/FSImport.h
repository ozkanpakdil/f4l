/*
 *  FSImport.h
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

#ifndef __FSImport_h__
#define __FSImport_h__ 1

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
 * %FSImport is used to import shapes and other objects from another Flash file. 
 * 
<p>Since the identifier for an object is only unique within a given Flash file, imported objects are referenced by a name assigned when the object is exported.</p>

<table class="datasheet">

<tr>
<th align="left">Attribute</th>
<th align="left">Description</th>
</tr>

<tr>
<td><a name="FSImport_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSImport_1">url</a></td>
<td>The URL of the file containing the object to be imported. The URL must be in the same sub-domain and relative to the URL of the Flash file containing the file importing the object.</td>
</tr>

<tr>
<td><a name="FSImport_2">objects</a></td>
<td>A HashTable containing key-value pairs where the key is the identifier of the object being imported and the value is name assigned to the object when it was exported into a Flash file.</td>
</tr>

</table>

<p>To provide a degree of security the Flash Player will only import files that originate from the same domain as the file that it is currently playing. For example if the Flash file being shown was loaded from www.mydomain.com/flash.swf then the file contains the exported objects must reside somewhere at www.mydomain.com. This prevents a malicious Flash file from loading files from an unknown third party.</p>

<h1 class="datasheet">Examples</h1>

<p>To export an object from a Flash file:</p>

<pre>
FSDefineShape shape = new FSDefineShape(...);

movie.add(shape);
movie.add(new FSExport(shape.getIdentifier(), "Shape"));
</pre>

<p>The object can then be imported:</p>

<pre>
movie.add(new FSImport("exportFile.swf", movie.newIdentifier(), "Shape"));
</pre>

<h1 class="datasheet">History</h1>

<p>The FSImport class represents the ImportAssets data structure in the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 5.</p>

 */  
    class DLL_DECL FSImport : public FSMovieObject
    {
public:
        FSImport(FSInputStream* aStream);

        FSImport() : FSMovieObject(Import), url(), objects() {}

        /** Constructs an FSImport object that imports an object from the specified file. The exported object is referenced by a name assigned to it when it was exported. The newly imported object must be assigned an identifier that is unique within the movie the object is imported into. Limited security is provided by requiring that the URL must be in the same domain or sub-domain as the URL of the movie which contains this object.

            @param aUrl the URL referencing the file to be imported.
            @param anIdentifier the identifier of the object to be exported.
            @param aString the name of the exported object to allow it to be referenced.
            */
        FSImport(const char* aUrl, int anIdentifier, const char* aString) : FSMovieObject(Import), url(aUrl), objects()
        {
            objects.push_back(FSObjectName(anIdentifier, aString));
        }

        /** Constructs an FSImport object that imports an array of objects. Each FSObjectName object contains the object's identifier and a name that allows the object to be referenced from the file where it was exported.

            @param anArray an array of FSObjectName objects.
            */
        FSImport(const FSVector<FSObjectName>& anArray);

        FSImport* clone() const { return new FSImport(*this); }

        const char* className() const;

        /** Adds the identifier and name to the list of objects being imported.

            @param anIdentifier the identifier of the object to be imported.
            @param aString the name assigned to the exported object.
            */
        void add(int anIdentifier, const char* aString)
        {
            objects.push_back(FSObjectName(anIdentifier, aString));
        }

        /** Adds the array of objects to list of objects being imported.

            @param anArray an array of FSObjectName objects.
            */
        void add(const FSVector<FSObjectName>& anArray);

        /** Gets the URL of the file containing the object to be imported. Limited security is provided by requiring that the URL must be in the same domain or sub-domain as the URL of the movie which contains this object.

            @return the URL of the file containing the object to be imported.
            */
        const char* getUrl() { return url.c_str(); }

        /** Gets the objects to be imported.

            @return the an array of FSObjectName objects.
            */
        FSVector<FSObjectName>& getObjects() { return objects; }

        /**  Sets the URL of the file containing the imported objects. The URL must be in the same sub-domain and relative to the URL of the file containing the FSImport object.

            @param aString a URL relative to the URL of the file containing the FSImport object.
            */
        void setUrl(const char* aString) { url = aString; }

        /** Sets the array of objects to be imported.

            @param anArray the array of FSObjectName objects.
            */
        void setObjects(const FSVector<FSObjectName>& anArray) { objects = anArray; }
        
        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSString url;
        FSVector<FSObjectName>objects;
    };
}

#endif
