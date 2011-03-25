/*
 *  transformutil.h
 *  Transform Utilities
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

#ifndef __transformutil_h__
#define __transformutil_h__ 1

/** \mainpage Transform Utilities
 
The Transform Utilities framework is designed to extend the functionality provided 
by the Transform SWF framework and support a higher level interface to reduce the 
level of effort required to implement applications that use the Transform SWF framework.

Transform Utilities contains the following classes:
 
\htmlonly
<table cellspacing="0" cellpadding="4" border="0" class="datasheet">
<tr><th align="left">Class</th><th align="left">Description</th></tr>
<tr><td>FSImageConstructor</td><td>Loads JPEG, PNG and BMP format images from files and 
generates the objects required to display them in a movie. The class provides accessor 
methods to the image data allowing further processing before generating the Transform 
object that contain the image data.</td></tr>
<tr class="shaded"><td>FSShapeConstructor</td><td>Draws arbitrary complex paths for 
drawing shapes. The class also supports a number of predefined paths for drawing geometric 
shapes and polygons. Support for drawing cubic Bezier curves is provided so the class 
provides a comprehensive API for integration into any 2-D graphics application.</td></tr>

<tr><td>FSSoundConstructor</td><td>Generates the Transform SWF objects required to play 
sounds played in response to events and to stream sounds so soundtracks can be added to 
movies. Sound files containing WAVE and MP3 are supported. As with the FSImageConstructor 
class accessor methods are provided to allow the sound samples to be processed before the 
Transform SWF objects are generated. See also 
<a href="http://www.flagstonesoftware.com/usefulcode.html">Useful Code</a>
for code to compress PCM encoded sounds to the ADPCM format.</td></tr>

<tr class="shaded"><td>FSTextConstructor</td><td>Used to generate font definitions and 
create strings that are displayed in Flash files. Font definitions may be created from 
an existing Flash file or an OpenType/TrueType font file. The Java version of the framework 
also allows fonts to be created from AWT font classes. Text objects used to define single 
strings or blocks of text can be generated from the font definition. The FSTextConstructor 
tracks the string generated so, if required, the font definition object generated only 
contains the glyphs used, greatly reducing the size of the Flash file generated.</td></tr>

<tr><td>FSCodec</td><td>Supports reading and writing of data from an array of bytes. Similar 
to stream classes the FSCodec also supports reading and writing of bit fields at any bit 
position with in the data. The FSCodec class can be used to process data loaded from files 
from either the FSImageConstructor or FSSoundConstructor classes.</td></tr>

</table>
<p></P>
\endhtmlonly
 */

#include "FSTransformUtil.h"

#include "FSCodec.h"

#include "FSImageConstructor.h"
#include "FSShapeConstructor.h"
#include "FSSoundConstructor.h"
#include "FSTextConstructor.h"

#endif /* __transformutil_h__ */