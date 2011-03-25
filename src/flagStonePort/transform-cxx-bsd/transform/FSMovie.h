/*
 *  FSMovie.h
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

#pragma warning( disable : 4290 )

#ifndef __FSMovie_h__
#define __FSMovie_h__ 1

#include <string.h>

#include "FSMovieObject.h"
#include "FSVector.h"
#include "FSBounds.h"
#include "FSShape.h"
#include "FSException.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSMovieObject*>;
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSShape>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
    class FSActionObject;
    class FSFillStyle;
    class FSMovieListener;
/**
 * %FSMovie is a container class for the objects that represents the data structures in a Flash file. 
 * 
<p>FSMovie is the core class of the Transform package. It is used to parse and generate Flash files, translating the binary format of the Flash file into an array objects that can be inspected and updated.</p>

<p>An FSMovie object also contains the attributes that make up the header information of the Flash file, identifying the version support, size of the Flash Player screen, etc.:</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSMovie_0">signature</a></td>
<td>The signature is a three character code that identifies that the file contains Flash encoded data. For Flash versions 1 to 5 this was 'F', 'W', 'S' ("SWF" reversed). In Flash 6, zlib compressed files were introduced to reduce file sizes. Compressed files are identified by the signature,  'C', 'W', 'S'.</td>
</tr>

<tr><td><a name="FSMovie_1">version</a></td>
<td>The version of Flash that is contained in the file.</td>
</tr>

<tr><td><a name="FSMovie_2">frameSize</a></td>
<td>An FSBounds object that define the size of the Flash Player's screen when playing the movie.</td>
</tr>

<tr><td><a name="FSMovie_3">frameRate</a></td>
<td>The number of frames per second that the movie will be played at.</td>
</tr>

<tr><td><a name="FSMovie_4">objects</a></td>
<td>An array of FSMovieObjects that define the shapes, buttons, images etc to be displayed along with the commands that control how the movie is animated.</td>
</tr>

</table>

<p>The header information defined in the Macromedia Flash (SWF) File Format Specification also identifies the length of the (uncompressed) movie and the number of frames. These attributes are derived when the FSMovie object is encoded to a file.</p>

<h1 class="datasheet">Generating a Flash File</h1>

<p>Flash files can be built from scratch by simply constructing instances of objects that represent 
the respective Flash data structure and adding them to an FSMovie object in the order they will 
be executed by the Flash player.</p>

<pre>
FSMovie movie;

// Define a shape to be displayed

FSDefineShape* rectangle = new FSDefineShape(movie.newIdentifier(), ....);

// Set the size of the Flash Player screen 400x400 and the number of
// frames displayed per second.

movie.setFrameSize(FSBounds(0, 0, 400, 400));
movie.setFrameRate(1.0);

// Set the background colour for the movie

movie.add(new FSSetBackgroundColor(FSColor(0xAD, 0x12, 0x83)));

// Add the shape to the movie. All objects must be defined before
// they can be used.

movie.add(rectangle);

// Place the shape in the center of the screen (200,200) on the first layer
// in the Flash Player's display list.

movie.add(new FSPlaceObject2(FSPlaceObject2::New, rectangle->getIdentifier(), 1, 200, 200));

// Display the frame

movie.add(new FSShowFrame());

</pre>

<p>Note that when the shape was defined a call was made to the newIdentifier() method on the movie. Each object that defines either a shape, button, sound etc., is assigned a unique identifier to allow the object to be referenced in objects such as FSPlaceObject which places the shape on the Flash Player's display list. The identifier is unique only within a movie so the FSMovie class maintains a counter that is used to generate values for the identifiers that are assigned to objects derived from the FSDefineObject class.</p>

To generate a Flash file use the <code>encodeToFile(char* fileName)</code> method:

<pre>
try {
    aMovie.encodeToFile(filename);
}
catch (FSFileOpenException e) {
    ... Process Exception ...
}
catch (FSAccessException e) {
    ... Process Exception ...
}
catch (FSFormatException e) {
    ... Process Exception ...
}
</pre>
<h1 class="datasheet">Parsing a Flash File</h1>

<p>To parse a Flash file simply create an instance using the <code>FSMovie(char* fileName)</code> constructor:</P>

<pre>
FSMovie* aMovie = null;
char* filename = "aFlashFile.swf";

try {
    aMovie = new FSMovie(filename);
}
catch (FSFileOpenException e) {
    ... Process Exception ...
}
catch (FSAccessException e) {
    ... Process Exception ...
}
catch (FSFormatException e) {
    ... Process Exception ...
}
</pre>
<p>The objects array of the movie will contain an instance of the respective package class for 
each data structure  decoded from the file. The objects may be inspected and their attributes 
changed accordingly.</p>

<p>The FSMovie object keeps track of the identifiers assigned to objects that define the shapes, 
buttons, sounds etc. that make up a Flash file. If a new object is added to the movie then 
the call to newIdentifier() is guaranteed to return a value that is unique within the movie.</p>

<p><b>Object Ownership</b><br>Each data structures that defined in the Flash File Format 
specification are represented by a different class from the Transform library. The Transform 
SWF library provides abstract classes (FSTransformObject, FSMovieObject and FSActionObject) 
that define the basic behaviour of each class, specifically how they encode and decode 
themselves from the binary data that represents a Flash file. Consequently objects are added 
to movies and manipulated through pointers. Since a movie is in effect a large data structure 
providing an object-oriented view of a Flash file, <b>ALL</b> objects added to a movie are 
owned by the movie. Similarly throughout the Transform library if a pointer is added to an 
object the object now owns the object referenced. As a result no explicit memory management 
is required for objects dynamically allocated. The movie object will free all memory allocated 
when it is deleted.</p>

 */
    class DLL_DECL FSMovie
    {
public:
        /** Constructs an FSMovie object with no objects.
            */
        FSMovie();

        /** Constructs an FSMovie object with the specified bounding rectangle, frame rate and no objects. The Flash version defaults to the package constant Transform::VERSION.

            @param aBounds the bounding rectangle that defines the size of each frame in the movie.
            @param framesPerSecond the number of frames per second that the Player plays the movie at.
            */
        FSMovie(const FSBounds& aBounds, float framesPerSecond);

        /** Constructs an FSMovie object with the specified bounding rectangle, frame rate and array of objects. Once added, the objects in the array are owned by the movie object. They will be deleted when the movie is deleted.
   
            @param aBounds the bounding rectangle that defines the size of each frame in the movie.
            @param framesPerSecond the number of frames per second that the Player plays the movie at.
            @param anArray the array of objects that define the movie.
            */
        FSMovie(const FSBounds& aBounds, float framesPerSecond, const FSVector<FSMovieObject*>& anArray);

        /** Constructs an FSMovie object and decodes the contents of the specified file to generate an array of objects representing the Flash file.
    
            @param fileName the path to the Flash file that will be parsed.
            @throws FSFileOpenException - if the file does not exist, is a directory rather than a regular file, or for some other reason cannot be opened for reading.
            @throws FSAccessException - if an I/O error occurs.
            @throws FSFormatException - if the Flash file does not start with a valid signature.
            */
        FSMovie(const char* fileName) throw (FSFileOpenException, FSAccessException, FSFormatException);
        
        /** 
         * Constructs an FSMovie object with the specified signature, version, bounding rectangle, 
         * frame rate and array of objects.
         *
         * The signature controls whether the file will be compressed when encoded. If the 
         * signature is "FWS" the file will not be compressed. If the signature is "CWS" then 
         * the file will be compressed using the zlib algorithm after encoding. Note that 
         * compressed Flash files are only readable by a Flash Player that supports Flash from 
         * version 6 onwards.
         *
            @param aSignature a string indicating that the file contains Flash data, 
            either "FWS" for uncompressed files or "CWS" for compressed files.
            @param aVersion the version number of Flash implemented in this coder.
            @param aBounds the bounding rectangle that defines the size of each frame in the coder.
            @param framesPerSecond the number of frames per second that the Player plays the movie at.
            @param anArray the array of objects that define the coder.
            */
        FSMovie(char* aSignature, int aVersion, const FSBounds& aBounds, float framesPerSecond, const FSVector<FSMovieObject*>& anArray);
    
        /** Constructs an FSMovie object and decodes the binary data presented in the byte array to generate an array of objects representing the Flash data. The byte array is added to the movie and the movie assumes ownership. It will be deleted when the movie is deleted.
    
            @param data an array of bytes that contain the encoded Flash objects.
            @param numberOfBytes the length of the array of bytes.
            @throws FSFormatException if the Flash file does not start with a valid signature.
            */
        FSMovie(const byte* data, size_t numberOfBytes) throw (FSFormatException);

        FSMovie(const FSMovie& rhs);

        ~FSMovie();

        FSMovie& operator= (const FSMovie& rhs);

        /** Creates a deep copy of the movie. The object is dynamically allocated and ownership of the object is assumed by the code requesting the clone. The registered listeners are assigned to the movie rather than copied.

            @return a pointer to the cloned movie.
            */
        FSMovie* clone() const;

        /** Returns a unique identifier for an object derived from the FSDefineObject class. In order to reference objects that define items such as shapes, sounds, etc. each must be assigned an identifier that is unique for a given Movie.
    
            When binary data is decoded into a sequence of objects, the Movie class tracks each Define tag decoded, recording the highest value. If a new Define tag is added to the array of decoded objects the identifier assigned to the new tag will be guaranteed to be unique.
    
            @return an unique identifier for objects that define shapes, sounds, etc. in a Flash file.
            */
        int newIdentifier();
    
        /** Gets the current value for the unique identifer that will be assigned to definition objects (classes derived from the FSDefineObject class). The value returned is the last value requested using the newIdentifier() method.
    
            @return current value for the unique identifer.
            */
        int getIdentifier() const;

        /** 
         * Gets the signature identifying that the movie contains Flash. Up to version 5 the string
         * "FWS" identifies that data is encoded using the Flash file format. From Flash version 6 
         * onwards Flash data could also be compressed using the zlib algorithm to reduce the file 
         * size. A signature of "CWS" is used to denote that a file contain compressed Flash data.
         * The original signature "FWS" is still used to denote that a file contains uncompressed 
         * data.
         *
         * When encoding a FSMovie object the signature also determines whether the data generated
         * will be compressed.
         *
         * @return the string identifying the format for the encoded Flash data. 
         */
        char* getSignature() { return signature; }
    
        /** Gets the number representing the version of Flash that the movie represents.

            @return an integer defining the Flash version number for the movie.
            */
        int getVersion();

        /** Gets the bounding rectangle that defines the size of the player screen.  

            @return the FSBounds object that defines the bounding rectangle that describes the size of each frame in the movie.
            */
        FSBounds& getFrameSize();

        /** Gets the number of frames played per second that the movie will be displayed at.

            @return the speed the movie will be played at.
            */
        float getFrameRate();

        /** Sets the initial value for the unique identifer assigned to definition objects. When a new identifier is requested the identifier is incremented before being returned. For most situations the method argument will be zero. This method should be used with caution as generating definition object with duplicate identifiers will most probably crash the program displaying the Flash file generated.
    
            @param aValue the initial value for the unique identifer.
            */
        void setIdentifier(int aValue);
    
        /** 
         * Sets the signature for the Flash data when it is encoded. The signature is used to control 
         * whether the encoded data will be compressed. If the signature is "CWS" then the movie 
         * data will be compressed. If the signature is "FWS" then the data will not be compressed.
         *
         * @param aString the signature used for the encoded Flash file.
         */
        void setSignature(char* aString) { strncpy(signature, aString, 3); }

        /** Sets the Flash version supported in this Movie. Note that there are no restrictions on the objects that can be used in a movie. Using objects that are not supported by an earlier version of the Flash file format may cause the Player to not display the movie correctly or even crash the Player.

            @param aNumber the version of the Flash file format that this movie utilises.
            */
        void setVersion(int aNumber);

        /** Sets the bounding rectangle that defines the size of the player screen. The coordinates of the bounding rectangle are also used to define the coordinate range. For example if a 400 x 400 pixel  rectangle is defined, specifying the values for the x and y coordinates the range -200 to 200 sets the centre of the screen at (0,0), if the x and y coordinates are specified in the range 0 to 400 then the centre of the screen will be at (200, 200).

            @param aBounds the FSBounds object that defines the frame size.
            */
        void setFrameSize(const FSBounds& aBounds);

        /** Sets the number of frames played per second that the Player will display the movie.

            @param aNumber the number of frames per second that the movie is played.
            */
        void setFrameRate(float aNumber);

        /** Gets the array of objects contained in the Movie.
    
            @return the array of objects that describe a movie.
            */
        FSVector<FSMovieObject*>& getObjects();
    
        /** Adds the object to the Movie.
    
            @param anObject the object to be added to the movie.
            */
        void add(FSMovieObject* anObject);

        /** Adds the array of objects to the Movie, appending the objects at the end of the array. The objects added are owned by the movie.
    
            @param anArray the array of objects to be added to the movie.
            */
        void add(const FSVector<FSMovieObject*>& anArray);
    
        /** Sets the array of objects contained in the Movie. Any existing objects in the movie are deleted. The objects added are owned by the movie.
    
            @param anArray the array of objects that describe a movie.
            */
        void setObjects(const FSVector<FSMovieObject*>& anArray);
    
        /** Gets the total number of frames in the movie.
    
            @return the number of frames.
            */
        int getFrameCount() const;
    
        /** Decodes the contents of the specified file. An object for each tag decoded from the file is placed in the  Movie's object array in the order they were decoded from the file. 
    
            If an error occurs while the file is being read, the file will be closed and the array of objects in the Movie will contain the last tag successfully decoded.
    
            @param fileName the path to the Flash file that will be parsed.
            @throws FSFileOpenException - if the file does not exist, is a directory rather than a regular file, or for some other reason cannot be opened for reading.
            @throws FSAccessException - if an I/O error occurs.
            @throws FSFormatException if the Flash file does not start with a valid signature.
            */
        void decodeFromFile(const char* fileName) throw (FSFileOpenException, FSAccessException, FSFormatException);
    
        void decodeFromFile(const char* fileName, FSMovieListener* listener);
    
        /** Decodes the binary Flash data stored in the byte array, creating an object for each type of data structure decoded.
    
            If an error occurs while the data is being decoded the array of objects in the Movie will contain the last tag successfully decoded.

            A copy of the binary data is made before it is decoded so it should be explicitly deleted once the decoding process has been completed.

            @param bytes an array of bytes that contain the encoded Flash objects.
            @param numberOfBytes the length of the array of bytes.
            @throws FSFormatException if the Flash file does not start with a valid signature.
            */
        void decodeFromData(const byte* bytes, size_t numberOfBytes) throw (FSFormatException);
    
        void decodeFromData(const byte* bytes, size_t numberOfBytes, FSMovieListener* listener);

        /** Encodes the array of objects and writes the data to the specified file.
    
            If an error occurs during the encoding process, the file will be closed and the exception that reported the error is passed to the code calling the method.
    
            @param fileName the path to the Flash file that the movie will be encoded to.
            @throws FSFileOpenException - if the file does not exist, is a directory rather than a regular file, or for some other reason cannot be opened for reading.
            @throws FSAccessException - if an I/O error occurs.
            */
        void encodeToFile(const char* fileName) throw (FSFileOpenException, FSAccessException, FSValidationException);
    
        void encodeToFile(const char* fileName, FSMovieListener* listener);
    
        /** Returns the encoded representation of the array of objects that this Movie contains. The movie object does not own the binary data so it should be explicitly deleted.
    
            @param length a pointer which will contains the length of the encoded data.
            @return the array of bytes representing the encoded objects.
            */
        byte* encode(size_t& length) throw (FSValidationException);

        byte* encode(FSMovieListener* listener);

        static void encodeToStream(FSMovieObject* anObject, FSOutputStream* aStream);
        static void encodeToStream(FSActionObject* anObject, FSOutputStream* aStream);
        static void encodeToStream(FSVector<FSShape>& anArray, int indexWordSize, bool indexEnd, FSOutputStream* aStream);

        static FSMovieObject* objectFromStream(FSInputStream* aStream);
        static FSActionObject* actionFromStream(FSInputStream* aStream);
        static FSFillStyle* fillStyleFromStream(FSInputStream* aStream);

    private:
        byte* _encode(size_t& length, FSMovieListener* listener=NULL);
        void  _decode(const byte* bytes, size_t numberOfBytes, FSMovieListener* listener=NULL);

        int identifier;

        char signature[3];
        int version;
        FSBounds frameSize;
        float frameRate;

        FSVector<FSMovieObject*> objects;
    };
}

#endif
