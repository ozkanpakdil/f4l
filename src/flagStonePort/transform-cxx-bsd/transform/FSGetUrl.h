/*
 *  FSGetUrl.h
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

#ifndef __FSGetUrl_h__
#define __FSGetUrl_h__

#include "FSActionObject.h"

#include "FSString.h"

namespace transform
{
/**
 * %FSGetUrl is used to display a web page or load a movie clip into the Flash Player.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr><td><a name="FSGetUrl_0">type</a></td>
<td>Identifies the action when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSGetUrl_1">url</a></td>
<td>The fully qualified uniform resource location where the movie clip or web page will be retrieved from.</td>
</tr>

<tr>
<td><a name="FSGetUrl_2">target</a></td>
<td>A level in the Flash Player where the movie clip will be loaded or frame or window in the browser where the web page will be displayed.</td>
</tr>
</table>

<p>To display a web page or new Flash movie the target can either be the name of the web browser frame or one of the following reserved words:</p>

<table class="datasheet">

<tr>
<td><code>"name"</code></td>
<td>opens the new page in the frame with the name defined in an HTML &lt;frame&gt; tag.</td>
</tr>

<tr>
<td><code>_blank</code></td>
<td>opens the new page in a new window.</td>
</tr>

<tr>
<td><code>_self</code></td>
<td>opens the new page in the current window.</td>
</tr>

<tr>
<td><code>_top</code></td>
<td>opens the new page in the top level frame of the current window.</td>
</tr>

<tr>
<td><code>_parent</code></td>
<td>opens the new page in the parent frame of the frame where the Flash Player id displayed.</td>
</tr>

<tr>
<td><code>""</code></td>
<td>(blank string) opens the new page in the current frame or window.</td>
</tr>

</table>

<p>To load a movie clip into the currently playing movie then the target is a string literal of the form "_level<i>n</i>". The Flash Player supports the concept of virtual layers (analogous to the layers in the Display List). Higher levels are displayed in front of lower levels. The background of each level is transparent allowing movie clips on lower levels to be visible in areas not filled by the movie clip on a given level. The main movie is loaded into _level0. Movie clips are loaded into any level above this (1, 2, 124, etc.). If a movie clip is loaded into a level that already contains a movie clip then the existing clip is replaced by the new one.</p>

<h1 class="datasheet">Examples</h1>

<p>To create an action that will load a web page into the named frame:</p>

<pre>
FSGetUrl anAction = new FSGetUrl("http://www.myserver.com/page.html", "myFrame");
</pre>

<p>To create an action that will load a web page in a new window:</p>

<pre>
FSGetUrl anAction(\"http://www.myserver.com/page.html\", \"_blank\");
</pre>

<p>To create an action that will load a web page into the current window or frame:</p>

<pre>
FSGetUrl anAction(\"http://www.myserver.com/page.html", \"\");

<p>or</p>

<pre>
FSGetUrl anAction(\"http://www.myserver.com/page.html\");
</pre>

<p>To create an action that will load a movie clip into the currently playing movie:</p>

<pre>
FSGetUrl anAction(\"http://www.myserver.com/movieClip.swf\", \"_level1\");
</pre>

<h1 class="datasheet">History</h1>

<p>The FSGetUrl is a class for representing the ActionGetUrl action of the Macromedia Flash (SWF) File Format Specification. It was introduced in  Flash 1.</p>

 */
    class DLL_DECL FSGetUrl : public FSActionObject
    {
public:
        FSGetUrl(FSInputStream* aStream);

        /** Constructs an FSGetUrl with the specified url and target frame.

             @param urlString a fully qualified URL.
             @param targetString the location (in the Flash Player or web browser) where the contents of file retrieved via the url will be displayed.
             */
        FSGetUrl(const char* urlString, const char* targetString) : FSActionObject(GetUrl), url(urlString), target(targetString) {}

        /** Constructs an FSGetUrl with the specified url. The target defaults to the current window.

            @param aString a fully qualified URL.
            */
        FSGetUrl(const char* aString) : FSActionObject(GetUrl), url(aString), target() {}

        FSGetUrl* clone() const { return new FSGetUrl(*this); }

        const char* className() const;

        /** Gets the URL.

            @return the URL that web page or movie clip will be loaded from.
            */
        const char* getUrl() { return url.c_str(); }

        /** Gets the name of the target frame.

            @return the name of the location (in the Flash Player or web browser) where the web page or movie clip will be displayed.
            */
        const char* getTarget() { return target.c_str(); }

        /**  Sets the URL of the file to be retrieved.

            @param aString a fully qualified URL.
            */
        void setUrl(const char* aString) { url = aString; }

        /** Sets the name of the Target where the URL will be displayed. The target may be a frame or window in a web browser when displaying a web page or a level in the current movie when loading a movie clip.

            @param aString the name of the location (in the Flash Player or web browser) where contents of file retrieved via the url will be displayed.
            */
        void setTarget(const char* aString) { target = aString; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSString url;
        FSString target;
    };
}

#endif
