/*
 *  FSDefineTextField.h
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

#ifndef __FSDefineTextField_h__
#define __FSDefineTextField_h__ 1

#include "FSDefineObject.h"
#include "FSString.h"
#include "FSBounds.h"
#include "FSColor.h"

namespace transform
{
/**
 * %FSDefineTextField defines an editable text field. 
 * 
<p>The value entered into the text field is assigned to a specified variable allowing the creation of forms to accept values entered by a person viewing the Flash file.</p>

<p>The class contains a complex set of attributes which allows a high degree of control over how a text field is displayed:</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSDefineTextField_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr><td><a name="FSDefineTextField_1">identifier</a></td><td>An unique identifier for this object in the range 1..65535.</td></tr>
<tr><td><a name="FSDefineTextField_2">bounds</a></td><td>The bounding rectangle for the text field.</td></tr>
<tr><td><a name="FSDefineTextField_3">wordWrap</a></td><td>Indicates whether the text should be wrapped.</td></tr>
<tr><td><a name="FSDefineTextField_4">multiline</a></td><td>Indicates whether the text field contains multiple lines.</td></tr>
<tr><td><a name="FSDefineTextField_5">password</a></td><td>Indicates whether the text field will be used to display a password.</td></tr>
<tr><td><a name="FSDefineTextField_6">readOnly</a></td><td>Indicates whether the text field is read only.</td></tr>
<tr><td><a name="FSDefineTextField_7">selectable</a></td><td>Indicates whether the text field is selectable.</td></tr>
<tr><td><a name="FSDefineTextField_8">bordered</a></td><td>Indicates whether the text field is bordered.</td></tr>
<tr><td><a name="FSDefineTextField_9">HTML</a></td><td>Indicates whether the text field contains HTML.</td></tr>
<tr><td><a name="FSDefineTextField_10">fontIdentifier</a></td><td>The identifier of the font displayed in the text field.</td></tr>
<tr><td><a name="FSDefineTextField_11">height</a></td><td>The height of the characters in twips.</td></tr>
<tr><td><a name="FSDefineTextField_12">useFontGlyphs</a></td><td>Use either the glyphs defined in the movie to display the text or load the specified from the platform on which the Flash Player is hosted.</td></tr>
<tr><td><a name="FSDefineTextField_13">autosize</a></td><td>Indicates whether the text field will resize automatically to fit the text entered.</td></tr>
<tr><td><a name="FSDefineTextField_14">colour</a></td><td>The colour of the text. If set to null then the text color defaults to black.</td></tr>
<tr><td><a name="FSDefineTextField_15">maxLength</a></td><td>The maximum length of the text field. May be set to zero is not maximum length is defined.</td></tr>
<tr><td><a name="FSDefineTextField_16">variableName</a></td><td>The name of the variable the text will be assigned to.</td></tr>
<tr><td><a name="FSDefineTextField_17">initialText</a></td><td>The default text displayed in the text field.</td></tr>
</table>

<p>Additional layout information for the spacing of the text relative to the text field borders can also be specified through the following set of attributes:</p>

<table class="datasheet">

<tr><td><a name="FSDefineTextField_17">alignment</a></td><td>Whether the text in the field is left-aligned, right-aligned, centred.</td></tr>
<tr><td><a name="FSDefineTextField_18">leftMargin</a></td><td>Left margin in twips.</td></tr>
<tr><td><a name="FSDefineTextField_19">rightMargin</a></td><td>Right margin in twips.</td></tr>
<tr><td><a name="FSDefineTextField_20">indent</a></td><td>Text indentation in twips.</td></tr>
<tr><td><a name="FSDefineTextField_21">leading</a></td><td>Leading in twips.</td></tr>
</table>

<p>The default values for the alignment is AlignLeft while the leftMargin, rightMargin indent and leading attributes are set to zero. If the attributes all set to their default values then the layout information will not be encoded. If any of the values are set to a value other than the default then the values for all of the attributes will be encoded.</p>

<p><b>HTML Support</b><br/>
Setting the HTML flag to true allows text marked up with a limited set of HTML tags to be displayed in the text field. The following tags are supported:</p>

<table class="datasheet">
<tr>
<td>&lt;p&gt;&lt;/p&gt;</td>
<td>Delimits a paragraph. Only the align attribute is supported:<br><p [align = left | right | center ]></p></td>
</tr>
<tr>
<td>&lt;br&gt;</td>
<td>Inserts a line break.></p></td>
</tr>
<tr>
<td>&lt;a&gt;&lt;/a&gt;</td>
<td>Define a hyperlink. Two attributes are supported:
<ul>
<li>href - the URL of the link.</li>
<li>target - name of a window or frame. (optional)</li>
</ul>
</td>
</tr>
<tr>
<td>&lt;font&gt;&lt;/font&gt;</td>
<td>Format enclosed text using the font. Three attributes are supported:
<ul>
<li>name - must match the name of a font defined using the FSDefineFont2 class.</li>
<li>size - the height of the font in twips.</li>
<li>color - the colour of the text in the hexadecimal format #RRGGBB.</li>
</ul>
</td>
</tr>
<tr>
<td>&lt;b&gt;&lt;/b&gt;</td>
<td>Delimits text that should be displayed in bold.</td>
</tr>
<tr>
<td>&lt;b&gt;&lt;/b&gt;</td>
<td>Delimits text that should be displayed in italics.</td>
</tr>
<tr>
<td>&lt;b&gt;&lt;/b&gt;</td>
<td>Delimits text that should be displayed underlined.</td>
</tr>
<tr>
<td>&lt;li&gt;&lt;/li&gt;</td>
<td>Display bulleted paragraph. Strictly speaking this is not an HTML list. The &lt;ul&gt; tag is not required and no other list format is supported.</td>
</tr>
</table>

<h1 class="datasheet">History</h1>

<p>FSDefineTextField class represents the DefineTextField from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 4.</p>

 */  
    class DLL_DECL FSDefineTextField : public FSDefineObject
    {
public:
        /** Definition of the different ways text can be aligned in a text field. */
        enum alignment { LeftAlign = 0, RightAlign = 1, CenterAlign = 2, JustifyAlign = 3 };

        FSDefineTextField(FSInputStream* aStream);

        /** Constructs an FSDefineTextField object with the specified identifier and with the size defined by the bounding rectangle. All other attributes are set to their default values which will result in a blank, single-line, editable text field. Any values entered will not be assigned to a variable. Since no font is specified the text will be displayed in a non-spaced font 20 twips in height.

            @param anIdentifier the unique identifier for this object.
            @param aBounds the bounding rectangle for the field which defines its size.
            */
        FSDefineTextField(int anIdentifier, const FSBounds& aBounds);

        FSDefineTextField* clone() const;

        const char* className() const;

        /** Gets the bounding rectangle that completely encloses the text field.

            @return the bounding rectangle for the text field.
            */
        FSBounds& getBounds() { return bounds; }

        /** Does the text field support word wrapping.

            @return a flag indicating whether the text in the field will be wrapped.
            */
        bool isWordWrapped() const { return wordWrapped; }

        /** Does the text field support multiple lines of text.

            @return a flag indicating whether the text in the field will contain multiple lines.
            */
        bool  isMultiline() const { return multiline; }

        /** Does the text field protect passwords being entered.

            @return a flag indicating whether the text in the field represents a password.
            */
        bool isPassword() const { return password; }

        /** Is the text field read-only.

            @return a flag indicating whether the text in the field is read-only.
            */
        bool isReadOnly() const { return readOnly; }

        /** Is the text field selectable.

            @return a flag indicating whether the text in the field is selectable.
            */
        bool isSelectable() const { return selectable; }

        /** Is the text field bordered.

            @return a flag indicating whether the text in the field is bordered.
            */
        bool isBordered() const { return bordered; }

        /** Does the text field contain HTML.

            @return a flag indicating whether the text in the field contains HTML.
            */
        bool isHTML() const { return html; }

        /** Is the text displayed using a font defined on the host device rather than using the font defined in an FSDefineFont2 object.

            @return a flag indicating whether the text in the field is uses a host font.
            */
        bool isOutlined() const { return outlined; }

        /** Gets the identifier of the font used to display the characters.

            @return the font identifier.
            */
        int getFontId() const { return fontId; }

        /** Gets the height of the characters.

            @return the height of the font.
            */
        int getFontHeight() const { return fontHeight; }

        /** Gets the text color.

            @return the color of the text.
            */
        FSColor& getColor() { return color; }

        /** Gets the maximum length of the text displayed.

            @return the maximum number of characters displayed.
            */
        int getMaxLength() const { return maxLength; }

        /** Gets the alignment of the text, either AlignLeft, AlignRight, AlignCenter or AlignJustify.

            @return the alignment code.
            */
        int getAlignment() const { return alignment; }

        /** Gets the left margin in twips.

            @return the left margin.
            */
        int getLeftMargin() const { return leftMargin; }

        /** Gets the right margin in twips.

            @return the right margin.
            */
        int getRightMargin() const { return rightMargin; }

        /** Gets the indentation of the first line of text in twips.

            @return the indentation of the first line.
            */
        int getIndent() const { return indent; }

        /** Gets the leading in twips.

            @return the leading.
            */
        int getLeading() const { return leading; }

        /** Gets the name of the variable the value in the text field will be assigned to.

            @return the name of the variable.
            */
        const char* getVariableName() { return variableName.c_str(); }

        /** Gets the default text displayed in the field.

            @return the default value displayed in the field.
            */
        const char* getInitialText() { return initialText.c_str(); }

        /** Sets the bounding rectangle of the text field.

            @param aBounds the bounding rectangle enclosing the text field.
            */
        void setBounds(const FSBounds& aBounds) { bounds = aBounds; }

        /** Set whether the text field supports word wrapping.

            @param aFlag set whether the text field is word wrapped.
            */
        void setWordWrapped(bool aFlag) { wordWrapped = aFlag; }

        /** Set whether the text field contains multiple lines of text.

            @param aFlag set whether the text field is multiline.
            */
        void setMultiline(bool aFlag) { multiline = aFlag; }

        /** Set whether the text field should protect passwords entered.

            @param aFlag set whether the text field is password protected.
            */
        void setPassword(bool aFlag) { password = aFlag; }

        /** Set whether the text field is read-only.

            @param aFlag set whether the text field is read-only.
            */
        void setReadOnly(bool aFlag) { readOnly = aFlag; }

        /** Set whether the text field is selectable.

            @param aFlag set whether the text field is selectable.
            */
        void setSelectable(bool aFlag) { selectable = aFlag; }

        /** Set whether the text field is bordered.

            @param aFlag set whether the text field is bordered.
            */
        void setBordered(bool aFlag) { bordered = aFlag; }

        /** Set whether the text field contains HTML.

            @param aFlag set whether the text field contains HTML.
            */
        void setHTML(bool aFlag) { html = aFlag; }

        /** Set whether the text uses a font defined on the host device rather than using the font defined in an FSDefineFont2 object.

            @param aFlag set whether the text uses a host font.
            */
        void setOutlined(bool aFlag) { outlined = aFlag; }

        /** Sets the identifier of the font used to display the characters.

            @param anIdentifier the identifier for the font that the text will be rendered in.
            */
        void setFontId(int anIdentifier) { fontId = anIdentifier; }

        /** Sets the height of the characters. 

            @param aNumber the identifier for the font that the text will be rendered in.
            */
        void setFontHeight(int aNumber) { fontHeight = aNumber; }

        /** Sets the text color. If set to NULL then the text color defaults to black.

            @param aColor the colour object that defines the text colour.
            */
        void setColor(const FSColor& aColor) { color = aColor; }

        /** Sets the maximum length of the text displayed. May be set to zero if no maximum length is defined.

            @param aNumber the maximum number of characters displayed in the field.
            */
        void setMaxLength(int aNumber) { maxLength = aNumber; }

        /** Sets the alignment of the text, either AlignLeft, AlignRight, AlignCenter or AlignJustify.

            @param aType the type of alignment.
            */
        void setAlignment(int aType) { alignment = aType; }

        /** Sets the left margin in twips.

            @param aNumber the width of the left margin.
            */
        void setLeftMargin(int aNumber) { leftMargin = aNumber; }

        /** Sets the right margin in twips.

            @param aNumber the width of the right margin.
            */
        void setRightMargin(int aNumber) { rightMargin = aNumber; }

        /** Gets the indentation of the first line of text in twips.

            @param aNumber the identation for the first line.
            */
        void setIndent(int aNumber) { indent = aNumber; }

        /** Sets the leading in twips.

            @param aNumber the value for the leading.
            */
        void setLeading(int aNumber) { leading = aNumber; }

        /** Sets the name of the variable the value in the text field will be assigned to.

            @param aString the name of the variable.
            */
        void setVariableName(const char* aString) { variableName = aString; }

        /** Sets the value that will initially be displayed in the text field.

            @param aString the initial text displayed.
            */
        void setInitialText(const char* aString) { initialText = aString; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        bool containsFont() const;
        bool containsMaxLength() const;
        bool containsLayoutInfo() const;
        bool containsText() const;

        FSBounds bounds;
        
        bool wordWrapped;
        bool multiline;
        bool password;
        bool readOnly;
        bool selectable;
        bool bordered;
        bool html;
        bool outlined;
        
        int fontId;
        int fontHeight;
        
        FSColor color;

        int maxLength;
        int alignment;
        int leftMargin;
        int rightMargin;
        int indent;
        int leading;
        
        FSString variableName;
        FSString initialText;        
    };
}

#endif

