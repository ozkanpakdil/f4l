/*
 *  transform.h
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

#ifndef __transform_h__
#define __transform_h__ 1

/** \mainpage Transform SWF

Flash is designed to display vector graphics across the Internet and displayed on host devices using the 
Macromedia Flash Player. Flash is designed to be compact, extensible and platform independent. Animations 
delivered using Flash will be displayed consistently and accurately across a wide range of devices.

A Flash file (movie) contain a sequence of tagged data blocks.

\image html taggedData.gif " "

\n Each movie starts with header information followed by a sequence of tags that describe how the movie 
is displayed. All movies end with an End tag which marks the end of the file.

The header identifies the type and version of Flash contained in the file; the size of screen displayed 
by the Flash Player; the length of file; the rate at which frames are displayed and the number of frames 
in the movie.

Two categories of tag are provided: <i>definition</i> tags which are used to describe shapes, images, 
buttons, sounds, etc., and <i>control</i> tags that create instances of the shapes, etc. and display 
them on the Flash Player screen to create animations.

Flash also supports actions which control the behaviour of objects in response to events such as a button 
being clicked or when a particular frame is displayed. Actions are represented by byte-codes and the Flash 
Player supports a stack-based programming model which provides a rich programming environment that supports 
complex behaviours. This allows Flash movies to provide all the flexibility and sophistication of user 
interfaces found in desktop computers and personal devices.

The Transform SWF library is a collection of classes for each of the tags and data structures that make up 
the Flash File Format. The FSMovie class is the principal class in the library. FSMovie objects are used to 
represent a complete Flash movie, containing instances of the classes that represent each type of tag.

FSMovie is designed to simplify the creation and manipulation of Flash files. Creating an instance of the class:

\verbatim
    FSMovie aMovie(filename);
\endverbatim

parses the Flash file, <em>filename</em> and creates objects for each different tags and data structure decoded 
from the file. The objects may be inspected and their attributes changed accordingly. Once the objects have been updated:

\verbatim
    aMovie.writeToFile(filename);
\endverbatim

encodes each object and generates the file according to the Flash specification.

<H4>1.1. Flash Programming Model</H4>

Flash is, in effect, a programming language for the Flash Player. A movie contains definitions of objects 
which are created, displayed and updated to create an animation. In order to understand how the classes 
provided in Transform are used to create Flash movies it is essential to understand the programming model 
provided by the Flash Player.

\image html player.gif " "

\n The <b>Dictionary</b> is a table that contains the definitions of the objects (buttons, images, sounds) 
that will be displayed in the movie. Each definition tag (represented in Transform by classes derived from 
FSDefineObject) contains a unique identifier which allows the definition to be referenced when creating 
instances of a particular shape, button, etc., to display on the screen. Entries are added to the dictionary 
whenever a definition tag is decoded from the Flash movie. Dictionary entries may be deleted using the 
FSFree class once a definition is no longer needed.

The <b>Display List</b> controls the order in which objects are displayed on the screen. The display list 
is divided into layers. To display an object on the screen it is placed on a display list layer (using the 
FSPlaceObject or FSPlaceObject2 classes). The layer number controls the stacking order of object when the 
movie is displayed. Objects placed on a higher layer are displayed in front on an object on a lower layer. 
Only one object can be placed on a given layer at a time so like the unique identifier used to create the 
object from its definition in the Dictionary the layer number can be used to refer to an object once it is 
on the display list. When placed on the Display List an object is always visible (unless hidden by another 
or moved off the visible area of the screen) until it is explicitly removed (using FSRemoveObject or 
FSRemoveObject2). Once an object is removed it is "destroyed" so another instance must be re-created from 
its definition if the object must be displayed again.

The <b>Movie List</b> is used to manage the movie and any movie clips (also known as sprites). The Movie 
List contains a number of virtual levels, analogous to the layers in the Display List, which are used to 
keep track of which movie clips are currently loaded. The main movie is placed automatically on _level0. 
Movie clips that are displayed within the main movie may be loaded to _level1, _level2, etc. Note that 
movie clips must still be placed on the Display List for them to become visible on the Screen. Loading a 
movie clip (using the FSGetUrl2 class) to a level replaces any clip already loaded at that level. Movies 
loaded to _level0 replace the main movie. This allows several movies sequences to be chained together 
into a single movie.

The <b>Screen</b> is a bit-mapped display where the Flash Player renders the graphics objects to create 
the animation. Each time a ShowFrame tag is decoded the objects added to the Display List are rendered 
on the Screen. All graphics and fonts are anti-aliased. The size of the Screen is defined by the frameSize 
attribute of the FSMovie object. Coordinates in Flash are specified in <b>twips</b> where 1 twip equals 
1/1440th of an inch or 1/20th of a point. For most practical purposes this can be simplified to 1 twip = 
1/20th of a pixel.

It is important to note that in Flash the positive x and y axes extend from the top left corner of the 
screen (not from the lower left as in the Cartesian coordinate system). The coordinate range may also be 
specified in the attributes of a Flash movie so that the top left corner is set to an arbitrary pair of 
coordinates. For example specifying the corners at the points (-100,-100) and (100,100) defines a screen 
200 twips by 200 twips with the point (0,0) located in the centre. Specifying the points (0,0) and (200,200) 
defines a screen with the same size however the center is now located at (100,100).

The Flash Player supports three other physical devices (through the host operating system) to allow a 
user to interact with the animation being played. Users can enter data and keystrokes representing 
commands through a keyboard. A mouse or other pointing device is supported to allow users to click buttons 
and generate events for movie clips. Finally the Flash Player supports CD-quality sound in mono or stereo 
with between three and eight sound channels playing simultaneously, depending on the capabilities of the 
host platform. Sounds can be played in response to specific events, such as a mouse being clicked or 
streamed with the movie to provide as soundtrack as it is displayed. With the introduction of Flash 5, 
access to the keyboard and mouse are provided through the Key and Mouse objects and the methods they 
support, see Object-Oriented Programming below.

Actions executed by the Flash Player are loaded into the <b>Instruction Buffer</b>. Actions may be 
specified as part of a button definition to be executed when the button is clicked. Flash also allows 
actions to be executed whenever each frame is displayed (using the FSDoAction class). Flash does not 
support the concept of a program as such. Rather the complete movie can be regarded as the program 
executed by the Flash Player. Sequences of actions defined in FSDefineButton, FSDoAction objects are 
best viewed as procedures or sub-routines that are executed whenever a particular event occurs. A given 
set of actions are executed each and every time the corresponding event occurs. The Instruction Buffer 
is byte-addressable. Control flow within the Instruction Buffer is controlled by the <b>Instruction 
Pointer</b> which contains the address of the next instruction to be executed. Conditional and unconditional 
jumps are supported through the FSIf and FSJump classes respectively. Each action contains a 16-bit offset 
which is added to the address in the Instruction Pointer to obtain the address of the next instruction in 
the Instruction Buffer.

Calculations are performed using the <b>Stack</b>. The FSPush class is used to push values onto the stack. 
When actions are executed any required arguments are popped from the Stack and any results are pushed back 
on the stack then the action finishes executing. Values pushed onto the Stack are primarily integers or 
strings. When values are used repeatedly in a calculation the Flash Player provides the <b>String Table</b> 
and a set of 4 internal <b>Registers</b> to improve efficiency. Rather than repeatedly push a string value 
onto the Stack the FSTable class allows an array of up to 256 strings to be defined in a look-up table, 
using the FSTable class. A string is referenced from the table by pushing an FSTableIndex value onto 
the Stack. A table index only occupies 1 byte in the Instruction Buffer so the space required by a sequence 
of actions can be reduced considerably using indices rather than explicitly pushing strings onto the stack. 
The Flash Player also has four internal registers for temporarily storing values. Values are copied (not popped) 
from the top of the Stack using the FSRegisterCopy action. The contents of the register is referenced by 
pushing an FSRegisterIndex onto the Stack. This simplifies use of the Stack is complex calculations and 
again reduced the space required to represent a given set of actions in the Instruction Buffer.

Although calculations are performed using the Stack, Flash also supports the concept of named variables. 
Variables are stored in <b>Memory</b> which is a scratchpad memory accessible only by the Flash Player. 
It cannot be accessed using any of the actions provided by Flash. Variables are fetched and set from Memory 
using the GetVariable and SetVariable actions (byte-code actions are supported using the FSAction class). 
The name of the variable is pushed onto the Stack and a GetVariable action is executed. The value of the 
variable is fetched form Memory and pushed onto the Stack by the Flash Player. Similarly to set a variable 
the value followed by the variable name are pushed onto the Stack and a SetVariable action is executed to 
update the variable in Memory.

<H4>1.2. A Quick Tour of Flash</H4>

Flash provides a rich environment for drawing object and creating animations. This is a brief description 
of the main aspects of Flash and is intended to introduce the main classes available in the Transform SWF 
library. Examples showing how to use the individual classes to create Flash movies are presented on 
Flagstone's web site.

<b>Drawing Shapes</b>\n
Shapes are drawn using a combination FSLine and FSCurve which specify the line or curve to draw relative 
to the current drawing point. The line style is defined using FSSolidLine class - only solid lines are 
supported. Shapes can be filled with solid colour (FSSolidFill), an image (FSBitmapFill) or a colour gradient 
(FSGradientFill). The FSShapeStyle class is used to select a particular line and fill style while drawing 
a shape. It can also change the current drawing point and the set of line and fill styles used for a particular 
shape. Shapes are defined using FSDefineShape, FSDefineShape2 or FSDefineShape3. FSDefineShape is the most 
commonly used class. FSDefineShape2 extends FSDefineShape to support a large number (greater than 65535) 
of line and fill styles while FSDefineShape3 supports transparent shapes.

Flash supports shape morphing using the FSDefineMorphShape class which defines the appearance of the start 
and end shapes. The interpolation between the start and end shapes is performed by the Flash Player. Displaying 
a morphing shape is controlled by the FSPlaceObject2 class which identifies the point in the morphing process 
and updates the display list with the morphed shape.

<b>Buttons</b>\n
Buttons are created by defining a shape for when button is up, the mouse is over the button or the button 
is clicked.FSDefineButton displays a button that executes a set of actions when it is clicked. FSDefineButton2 
provides are more flexible class allowing actions to be executed for any of the states a button can occupy. 
Sounds can also be played, using the FSButtonSound class, when an event occurs, such as the button being clicked.

<b>Images</b>\n
Flash supports JPEG and lossless image formats such as GIF. Several classes are provided which display 
"regular" and transparent images. Images cannot be displayed directly. They can only be displayed inside a 
shape that contains a bitmap fill style. Creating such "image shapes" is simple however. 

<b>Fonts and Text</b>\n
Flash ensures consistency and quality when display text by defining the glyphs that represent each of the 
text characters displayed in a movie. Fonts are defined using FSDefineFont and FSDefineFont2 - the latter 
combines the FSDefineFont and FSFontInfo classes into a more convenient and flexible class. A string is 
defined, using FSDefineText and FSText, by specifying the index of the glyph, from the font definition, that 
represents a given character. Using the index of a glyph allows only the glyphs actually displayed to be 
used, greatly reducing the size of a Flash file. The relative placement of glyphs is also specified in the 
text string giving a high degree of control over how a piece of text is rendered.

Creating fonts and text directly using the Transform classes can be very cumbersome. Flagstone provides 
the <b>Transform Utilities</b> library that allows fonts and text to be created from existing Flash or 
Java font definitions greatly simplifying the process.

Text fields can be created using the FSDefineTextField class. This class is very flexible and can be used 
to create editable text fields that allow users to submit information to a server in the same way as HTML forms.

<b>Sound</b>\n
Flash can supports sounds that are played when an event occurs such as a button being clicked (FSDefineSound) 
or streaming sound that allows a soundtrack to be played while displaying a movie (FSSoundStreamHead, 
FSSoundStreamBlock). Flash can play sounds that are compressed using ADPCM or MP3. A high degree of control 
over the sound is available - an envelope can be created that controls how a sound fades in and fades out (FSSound).

<b>Movie Clips</b>\n
Movie Clips (sprites) contain "pre-packaged" animation sequences that liven up a movie. Movie clip are 
defined using the FSDefineMovie class. A Flash file can contain all the required movie clips or they can 
be loaded on demand using the FSGetUrl and FSGetUrl2 classes.

<b>Display List</b>\n
Shapes, buttons, images and text are placed on the display list using the FSPlaceObject and FSPlaceObject2 
classes. Objects can be removed from the display list using FSRemoveObject and FSRemoveObject2.

<b>Timelines</b>\n
A Flash file is composed of a series of frames. Each frame contains definitions of objects to be displayed 
and the sequence of commands used to update the display list. Frames in a movie are displayed using the 
FSShowFrame class. This instructs the Flash Player to display all the objects currently in the display list. 
Successive frames in a movie or movie clip are delimited by successive FSShowFrame objects. The timeline is 
controlled by FSGotoFrame, FSGotoFrame2 and FSGotoLabel actions which instruct the Flash Player to play 
the movie or clip starting at a particular frame.

<b>Actions</b>\n
Actions are executed when a frame is displayed, a button is clicked or an event occurs in a movie clip. 
The FSDoAction class is used to define the list of actions for a given frame. The FSButtonEvent class 
defines actions for a button and the FSClipEvent class in conjunction with the FSPlaceObject2 class is 
used to define the events for a movie clip.

FSPush is used to push integers, strings, double precision floating point numbers onto the Stack. The 
byte-codes that represent stack-based actions are supported using the FSAction class. The type assigned 
to instances of this class identify the type of action to be executed.

Control flow is performed using FSIf and FSJump.

FSGetUrl and FSGetUrl2 are used to load web pages, movies and movie clips. FSGetUrl2 also allows variables 
to be loaded and submitted to and from a remote server. XML formatted data can also be exchanged using 
the XMLSocket class allowing direct communication with a server process.

<H4>1.3. Object-Oriented Programming</H4>

With the introduction of Flash 5 the concept of classes and objects (in the programming sense) was introduced 
to Flash. The Flash Player supports several pre-defined classes for different data types such as Strings, 
Integers and XML formatted data structures. Classes are also used access to system resources such as the 
mouse or other pointing device supported by the host device. The Flash Player also supports <b>Socket</b> 
objects which allow XML formatted data to be exchanged between the Flash Player and a remote server.

Objects are instantiated and assigned to variables in Memory. Instances of pre-defined classes (String, 
Integer, etc.) are created by pushing any arguments followed by the name of the class onto the Stack then 
executing a NamedObject action. Methods are executed by pushing the arguments, if any, followed by a 
reference to the object (usually through a variable) and a string containing the name of a method. The 
ExecuteMethod pops the items from the stack and executes the function associated with the method definition, 
returning any results to the stack.

User defined classes and objects can also be defined and created. User-defined classes are created by 
pushing pairs of strings and default values onto the Stack for each member variable then executing the 
NewObject action. A reference to the object in memory is pushed on the Stack. Assigning this reference 
to a variable allows the object to be referenced in future calculations. Methods can be defined by using 
the FSNewFunction class to define a function and then assigning it to a member variable of the class using 
the SetAttribute action. Methods can be executed using the ExecuteMethod action using the same sequence of 
operations described previously.

The introduction of classes and objects is significant. Future releases of Flash and the Flash Player can 
have new functionality added using the general purpose mechanism describe above for creating objects and 
executing methods without adding new tags to the file format specification.

<H4>1.4. ActionScript</H4>

ActionScript is a high-level language provided by Macromedia to control and manipulate objects using the 
Flash authoring program. ActionScript is compiled into the byte-codes and actions supported by Transform 
when a movie is encoded to the Flash file format. Programming directly using the actions defined in 
Transform is analogous to assembly-language programming for microprocessors. Creating programs at this low 
level is relatively cumbersome, prone to error and difficult to debug. To address this, Flagstone developed 
<b>Translate</b>, a Java based program that compiles ActionScript into the objects supported in the Transform 
SWF Library. This greatly simplifies the creation of programs that can be used in Flash files. Although 
Translate is current only available for Java, compiled scripts can easily be added to programs developed 
in C++ by compiling the ActionScript and encoding the objects to a Flash file. The file can then be parsed 
using the FSMovie class and the compiled actions extracted and added to the relevant objects in the current 
movie.

<H3>2. Object Ownership</H3>

Three root classes are provided to create objects representing the different types of tag and action supported 
in a Flash movie. The FSDefineObject class is the parent for classes that define the different types of object 
displayed in a movie. FSMovieObject class is the parent for classes that create and manipulate objects to 
animate a movie. FSActionObject is the parent for the different types of action that is executed by the Flash 
Player. As the FSMovie class contains classes derived from FSMovieObject and FSDefineObject, objects are added 
and manipulated using pointers. Similarly the objects that contain objects from the different action classes 
derived from FSActionObject also manage the objects using pointers. In Transform any object which manages 
pointers also assumes ownership of the object that the pointer references. Ownership is assumed as soon as 
a pointer is added to an object. When an object is deleted all the objects referenced through pointers will 
also be deleted. Consequently while objects are dynamically created the responsibility for managing and 
releasing the memory allocated rests with the respective Transform class.

<H3>Additional Information</H3>

More information on Flash and the binary encoding of the tags can be found in the 
<a href=http://www.macromedia.com/software/flash/open/licensing/fileformat/>Flash File Format Specification</a> 
from Macromedia.

*/

#include "FSTransform.h"

#include "FSMovie.h"
#include "FSMovieListener.h"
#include "FSMovieEvent.h"

#include "FSException.h"

#include "FSTransformObject.h"
#include "FSMovieObject.h"
#include "FSDefineObject.h"
#include "FSActionObject.h"

#include "FSBounds.h"
#include "FSColor.h"
#include "FSColorTable.h"
#include "FSCoordTransform.h"
#include "FSColorTransform.h"
#include "FSVector.h"
#include "FSString.h"

#include "FSUnknownAction.h"
#include "FSUnknownObject.h"

#include "FSAction.h"
#include "FSGetUrl.h"
#include "FSGotoFrame.h"

#include "FSSetBackgroundColor.h"
#include "FSRemoveObject.h"
#include "FSPlaceObject.h"
#include "FSDoAction.h"
#include "FSShowFrame.h"

#include "FSShape.h"
#include "FSShapeObject.h"
#include "FSShapeStyle.h"
#include "FSLine.h"
#include "FSCurve.h"

#include "FSLineStyle.h"
#include "FSSolidLine.h"

#include "FSFillStyle.h"
#include "FSSolidFill.h"
#include "FSBitmapFill.h"
#include "FSGradientFill.h"
#include "FSGradient.h"

#include "FSDefineShape.h"

#include "FSJPEGEncodingTable.h"
#include "FSDefineJPEGImage.h"

#include "FSButton.h"
#include "FSDefineButton.h"

#include "FSEnvelope.h"
#include "FSSound.h"
#include "FSStartSound.h"
#include "FSDefineSound.h"
#include "FSSoundStreamBlock.h"
#include "FSSoundStreamHead.h"

#include "FSDefineFont.h"
#include "FSFontInfo.h"

#include "FSCharacter.h"
#include "FSText.h"
#include "FSDefineText.h"

// Flash 5
#include "FSBoolean.h"
#include "FSInteger.h"
#include "FSDouble.h"
#include "FSNull.h"
#include "FSVoid.h"
#include "FSRegisterIndex.h"
#include "FSTableIndex.h"
#include "FSObjectName.h"

#include "FSClipEvent.h"
#include "FSButtonEvent.h"

#include "FSPush.h"
#include "FSGetUrl2.h"
#include "FSGotoFrame2.h"
#include "FSIf.h"
#include "FSJump.h"
#include "FSWith.h"
#include "FSCall.h"
#include "FSTable.h"
#include "FSWaitForFrame.h"
#include "FSWaitForFrame2.h"
#include "FSRegisterCopy.h"
#include "FSNewFunction.h"
#include "FSGotoLabel.h"
#include "FSSetTarget.h"

#include "FSPlaceObject2.h"
#include "FSRemoveObject2.h"
#include "FSFrameLabel.h"
#include "FSDefineMovieClip.h"
#include "FSFree.h"
#include "FSPathsArePostscript.h"
#include "FSSerialNumber.h"
#include "FSPointer.h"
#include "FSImport.h"
#include "FSExport.h"
#include "FSProtect.h"
#include "FSEnableDebugger.h"
#include "FSQuicktimeMovie.h"

#include "FSMorphSolidFill.h"
#include "FSMorphBitmapFill.h"
#include "FSMorphGradientFill.h"
#include "FSMorphGradient.h"

#include "FSMorphSolidLine.h"

#include "FSDefineShape2.h"
#include "FSDefineShape3.h"
#include "FSDefineMorphShape.h"

#include "FSButtonColorTransform.h"
#include "FSButtonSound.h"
#include "FSDefineButton2.h"

#include "FSDefineJPEGImage2.h"
#include "FSDefineJPEGImage3.h"
#include "FSDefineImage.h"
#include "FSDefineImage2.h"

#include "FSKerning.h"
#include "FSDefineFont2.h"

#include "FSDefineText2.h"
#include "FSDefineTextField.h"

#include "FSSoundStreamHead2.h"


// Flash 6
#include "FSInitialize.h"
#include "FSDefineVideo.h"
#include "FSVideoFrame.h"
#include "FSFontInfo2.h"
#include "FSEnableDebugger2.h"

// Flash 7
#include "FSLimitScript.h"
#include "FSTabOrder.h"
#include "FSNewFunction2.h"
#include "FSExceptionHandler.h"

#endif /* __transform_h__ */
