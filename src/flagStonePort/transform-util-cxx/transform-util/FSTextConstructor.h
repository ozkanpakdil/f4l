/*
 * FSTextConstructor.h
 * Transform Utilities
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
 
#ifndef __FSTextConstructor_h__
#define __FSTextConstructor_h__ 1

#include "FSTransformUtil.h"

#include <stdlib.h>

using namespace transform;

namespace transform
{
    class FSBounds;
    class FSColor;
    class FSDefineFont2;
    class FSDefineText2;
    class FSDefineShape3;
/**
 * The FSTextConstructor class greatly simplifies the use of fonts and text when creating
 * Flash files. Font definitions can be created using:
 * 
 * <ol>
 * <li>TrueType or OpenType font definition stored in a file.</li>
 * <li>a font definition stored in an existing Flash file.</li>
 * </ol>
 * 
 * <P>The name of the file containing the font definition can be specified using the 
 * setFontFromFile() method:</p>
 * 
 * <pre>
 *     FSTextConstructor* textGenerator = TextConstructor();
 *
 *     textGenerator->setFontFromFile("Arial.otf");
 *     textGenerator->setFontFromFile("TimesNewRoman.swf");
 * </pre>
 * 
 * <P>The OpenType or TrueType file is parsed to construct the font definition. File with the
 * extensions ".otf" or ".ttf" may be used. Files containing collections of fonts ".otc" are 
 * not currently supported. For Flash files the first font definition encountered is used and 
 * all the text definition objects associated with the font are used to obtain the advance 
 * information for each character. An example Flash file can be found in the resources directory 
 * included in this release.</p>
 *
 * The setFont() and setFontFromFile() methods return status codes to indicate whether the
 * font was decoded successfully:
 *
 * \verbatim
 *     FSTextConstructor* textGenerator = TextConstructor();
 *
 *     int status = textGenerator->setFontFromFile("Arial.otf");
 *
 *     if (status != TransformUtil::OK)
 *     {
 *         switch (status)
 *         {
 *             case TransformUtil::FileNotFound: ...
 *             case TransformUtil::ReadError: ...
 *             case TransformUtil::FormatError: ...
 *         }
 *     }
 * \endverbatim
 * 
 * <P>Once a font has been loaded, text strings can be generated:</p>
 * 
 * <pre>
 *    int fontId = movie.newIdentifier();
 *    int fontSize = 280;
 *    FSColor black = FSColorTable::black();
 *
 *    font->setIdentifier(fontId);
 *    font->setSize(fontSize);
 *    font->setColor(&black);
 *
 *    FSDefineText2* str = font->defineText(movie.newIdentifier(), "This is a string");
 * </pre>
 * 
 * <P>The defineText method returns FSDefineText2 objects since they support transparent
 * colours, while FSDefineText only supports opaque colours. A unique identifier should be 
 * set for the font definition before any text objects are generated since this is used to 
 * tie the text objects to a particular font definition. The size, in points, and the colour
 * should also be set before the text objects are generated. Font definitions in Flash are size 
 * independent, the text definition objects specify the size of the glyphs that will be drawn.</P>
 *
 * <P>Once all the strings to be displayed have been generated the font definition object 
 * containing the glyphs can be generated.</p>
 * 
 * <pre>
 *    FSDefineFont2* defineFont = font->defineFont();
 * </pre>
 * 
 * <P>Remember however that objects in a Flash file must be defined before they are used so
 * the font object must be added to the file before the first FSDefineText object that
 * references the glyphs in the font.</p>
 * 
 * <P>To reduce the size of the Flash file only the glyphs actually displayed can be included
 * in a font definition object. When a FSDefineText object is created the glyphs used are 
 * tracked. This is why the text definition objects are generated before the font definition.</P>
 *
 * <P>Glyphs are included in the font in the order they are used with each FSDefineText2 object 
 * referencing a glyph by its position in the array of glyphs contained in a font definition.
 * Any unused glyphs can then easily be omitted.</P>
 * 
 * <P>When the font definition is created only the glyphs used (up to that point) are included. 
 * If subsequent FSDefineText objects are generated that include glyphs not previously used then 
 * the text will not be displayed correctly.</p>
 *
 * <b>Text Fields</b><br/>
 *
 * <P>When creating text fields using the FSDefineTextField class, there are two options when 
 * specifying the font used to display the characters entered into the field:
 *
 * <ol>
 * <li>The glyphs for the font may be loaded from the host platform.</li>
 * <li>The glyphs for the font are taken from a font definition object.</li>
 * </ol>
 *
 * <P>Using the glyphs loaded from the host platform is by far the easiest way of using text fields.
 * First a font definition is created that specifies only the name of the font which will be loaded
 * from the host platform. When creating the text fields set the useFontGlyphs attribute to false.</P>
 *
 * <pre>
 *    FSDefineFont2* fontDefinition = new FSDefineFont2(movie.newIdentifier(), "Arial");
 *
 *    FSDefineTextField* textField = new FSDefineTextField(movie.newIdentifier(), bounds);
 *
 *    textField->setUseFontGlyphs(false);
 * </pre>
 *
 * <P>This approach only works if the font is defined on the host platform otherwise the Flash Player
 * will substitute a default font.</P>
 *
 * <P>When using a font definition from a file, obviously the glyphs for all possible characters that
 * may be displayed in the text field must be included in the font definition otherwise the character 
 * will not be displayed correctly. There are two ways to do this, either generate FSDefineText objects 
 * which contain all possible characters (the object need not be added to the Flash file)</P>
 *
 * <pre>
 *    string lowerCaseLetters = "abcdefghijklmnopqrstuvwxyz";
 *    string upperCaseLetters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
 *    string numbers = "1234567890";
 *    string everythingElse = "`!@#$%^&*()-=[]\\:\"<>?~_+{}|;',./";
 *
 *    FSColor fontColor = FSColorTable::black();
 *
 *    font->setIdentifier(movie.newIdentifier());
 *    font->setSize(280);
 *    font->setColor(&fontColor);
 *
 *    font->defineText(movie.newIdentifier(), lowerCaseLetters.c_str());
 *    font->defineText(movie.newIdentifier(), upperCaseLetters.c_str());
 *    font->defineText(movie.newIdentifier(), numbers.c_str());
 *    font->defineText(movie.newIdentifier(), everythingElse.c_str());
 *
 *    FSDefineFont2* defineFont = font->defineFont();
 * </pre>
 *
 * <p>or alternatively define a range of characters to be included:</p>
 *
 * <pre>
 *    wchar_t first = L'A';
 *    wchar_t last = L'z';
 *    wchar_t str[2];
 *     
 *    str[1] = L'\\0';
 *
 *    FSColor fontColor = FSColorTable::black();
 *
 *    font->setIdentifier(movie.newIdentifier());
 *    font->setSize(280);
 *    font->setColor(&fontColor);
 *
 *    for (int i=first; i&lt;=last; i++)
 *    {
 *        str[0] = (wchar_t)i;
 *           font->defineText(movie.newIdentifier(), str);
 *    }
 * </pre>
 *
 * <P>This will include all the glyphs representing the range of characters in the 
 * font definition.</P>
 *
 * <b>Missing Characters</b><br/>
 *
 * <P>Characters that cannot be displayed using the font are handled by a displaying a 
 * default glyph which typically represents a space or an empty box. True/Open Type 
 * definitions explicitly define the missing glyph. For fonts parsed from Flash files 
 * the missing glyph is assumed (by default) to be the first glyph in the font definition.</p>
 * 
 * <P>When a font is loaded the missing glyph is added automatically to the font 
 * definition so there is no need to explicitly include it by creating a text object
 * to force it to be included. The missing glyph will always be the first glyph in the
 * font definition generated by the FSTextConstructor object so it may be substituted
 * by another suitable shape if required.</P>
 * 
 * <P>Whether a string can be displayed using a font can be determined by the 
 * <em>canDisplay()</em> method which returns the index of the first character that 
 * cannot be displayed (the missing glyph will be displayed instead) or -1 if all the 
 * characters are represented in the font.</P>
 */
class FSTextConstructor
{
public:
    /**
     * Initializes the FSFontConstructor object with the font in the specified file.
     *
     * The method returns a status code indicating whether the object was initialized 
     * correctly, either TransformUtil::OK, TransformUtil::FileNotFound, TransformUtil::ReadError
     * or TransformUtil::FormatError.
     *
     * @param filename either the name of a Flash, TrueType or OpenType file containing an 
     * existing font definition.
     * @return a status code indicating whether the image was loaded successfully.
     */
    virtual int CALL setFontFromFile(const char* filename) = 0;
    /**
     * Initializes the FSFontConstructor object with the encoded font data.
     *
     * The method returns a status code indicating whether the object was initialized 
     * correctly, either TransformUtil::OK or TransformUtil::FormatError.
     *
     * @param bytes an array of bytes containing the encoded font.
     * @param numberOfBytes the number of bytes in the array containing the encoded font.
     *
     * @throws FSFormatException if the encoded font cannot be identified as either a Flash file
     * a TrueType font or an OpenType font, or if an error occurs while decoding the font 
     * information.
     */
    virtual int CALL setFont(const unsigned char* bytes, size_t numberOfBytes) = 0;
    /**
     * Sets the unique identifier used to identify the font definition in a file. The identifier
     * is also used when defining text objects to reference the font definition.
     *
     * @param anIdentifier the identifier for the font.
     */
    virtual void CALL setIdentifier(int anIdentifier) = 0;
    /**
     * Set the size of the font, in twips, that will be used as the default value when 
     * generating text objects. 20 twips is equivalent to 1 point.
     *
     * @param fontSize the height of the font in twips.
     */
    virtual void CALL setSize(unsigned int fontSize) = 0;
    /**
     * Sets the colour used to fill the glyphs representing the text.
     *
     * @param fontColor a pointer to an FSColor object.
     */
    virtual void CALL setColor(const FSColor* fontColor) = 0;
    /**
     * Indicates whether or not the font can be used to display a string. This method returns 
     * the index of the first character that cannot be displayed. If the Font can display all 
     * characters, -1 is returned.
     *
     * @param aString the String to be displayed.
     *
     * @return the index of the first character that cannot be displayed, -1 otherwise.
     */
    virtual int CALL canDisplayCharacters(const char* aString) = 0;
    /**
     * Indicates whether or not the font can be used to display a string containing wide
     * characters. This method returns the index of the first character that cannot be displayed. 
     * If the Font can display all characters, -1 is returned.
     *
     * @param aString a string containing the characters to be displayed.
     *
     * @return the index of the first character that cannot be displayed, -1 otherwise.
     */
    virtual int CALL canDisplayWideCharacters(const wchar_t* aString) = 0;
    /**
     * Generates a FSDefineFont2 object containing a complete definition of the font.
     *
     * <P>NOTE: Only the glyphs referenced in the FSDefineText2 objects created using the 
     * defineText method will be included in the font definition. If FSDefineText2 objects 
     * are created after the font is generated and the text references a glyph not 
     * previously used then the text string will not be displayed correctly.</P>
     *
     * @return a FSDefineFont2 object generated from the font definition.
     */
    virtual FSDefineFont2* CALL defineFont() = 0;
    /**
     * Generates an FSDefineText2 object for a string of characters. The text will be 
     * rendered using the size and colour specified using the setSize() setColor()
     * methods.
     * 
     * <P>If any of the characters in the String cannot be displayed using this font
     * then the missing glyph is substituted.</p>
     * 
     * <P>All the FSDefineText2 objects should be created before the font definition. Only 
     * the glyphs referenced up to that point will be included in the font. If text objects
     * are created after the font definition has been generated and a glyph is referenced 
     * that is not in the font then the text will not be displayed correctly and may even
     * crash the Flash Player.
     *
     * @param anIdentifier a unique identifier for the object.
     * @param text the String to be displayed.
     *
     * @return an FSDefineText object representing the text.
     */
    virtual FSDefineText2* CALL defineText(int anIdentifier, const char* text) = 0;
    /**
     * Generates an FSDefineText2 object for a block of text.
     * 
     * <P>If any of the characters in the String cannot be displayed using this font
     * then the missing glyph is substituted.</p>
     * 
     * <P>All the FSDefineText2 objects should be created before the font definition. Only 
     * the glyphs referenced up to that point will be included in the font. If text objects
     * are created after the font definition has been generated and a glyph is referenced 
     * that is not in the font then the text will not be displayed correctly and may even
     * crash the Flash Player.
     *
     * @param anIdentifier a unique identifier for the object.
     * @param lines an array containing the strings to be displayed.
     * @param count the number of lines in the array.
     * @param lineSpacing the distance, in twips, between successive lines.
     *
     * @return an FSDefineText object representing the text.
     */
    virtual FSDefineText2* CALL defineTextBlock(int anIdentifier, const char* lines[], size_t count, int lineSpacing) = 0;
    /**
     * Generates an FSDefineText2 object for a string containing wide characters.
     * 
     * <P>If any of the characters in the String cannot be displayed using this font
     * then the missing glyph is substituted.</p>
     * 
     * <P>All the FSDefineText2 objects should be created before the font definition. Only 
     * the glyphs referenced up to that point will be included in the font. If text objects
     * are created after the font definition has been generated and a glyph is referenced 
     * that is not in the font then the text will not be displayed correctly and may even
     * crash the Flash Player.
     *
     * @param anIdentifier a unique identifier for the object.
     * @param text a string containing the wide characters to be displayed.
     *
     * @return an FSDefineText object representing the text.
     */
    virtual FSDefineText2* CALL defineWideText(int anIdentifier, const wchar_t* text) = 0;
    /**
     * Generates an FSDefineText2 object for a block of text containing strings of wide
     * characters.
     * 
     * <P>If any of the characters in the String cannot be displayed using this font
     * then the missing glyph is substituted.</p>
     * 
     * <P>All the FSDefineText2 objects should be created before the font definition. Only 
     * the glyphs referenced up to that point will be included in the font. If text objects
     * are created after the font definition has been generated and a glyph is referenced 
     * that is not in the font then the text will not be displayed correctly and may even
     * crash the Flash Player.
     *
     * @param anIdentifier a unique identifier for the object.
     * @param lines an array containing the lines of text to be displayed.
     * @param count the number of lines in the array.
     * @param lineSpacing the distance, in twips, between successive lines.
     *
     * @return an FSDefineText object representing the text.
     */
    virtual FSDefineText2* CALL defineWideTextBlock(int anIdentifier, const wchar_t* lines[], size_t count, int lineSpacing) = 0;
    /**
     * Generates an FSBounds object that defines the bounding box that encloses the text,
     * rendered in the specified font size.
     *
     * @param text the String to be displayed.
     *
     * @return a pointer to an FSBounds object defining the bounding box enclosing the text.
     */
    virtual FSBounds* CALL boundsForText(const char* text) = 0;
    /**
     * Generates an FSBounds object that defines the bounding box that encloses the text,
     * rendered in the specified font size.
     *
     * @param text the string of wide characters to be displayed.
     *
     * @return a pointer to an FSBounds object defining the bounding box enclosing the text.
     */
    virtual FSBounds* CALL boundsForWideText(const wchar_t* text) = 0;
    /**
     * defineShape converts a string into an equivalent shape representation. The
     * shape is constructed from glyphs used to represent each character in the 
     * string.
     * 
     * @param anIdentifier an unique identifier for the shape.
     * @param text the string to convert into a shape.
     *
     * @return an FSDefineShape3 object4 which contains a shape that represents 
     * the characters contained in the string argument.
     */
    virtual FSDefineShape3* CALL defineShape(int anIdentifier, const char* text) = 0;
    /**
     * defineShape converts a string containing wide characters into an equivalent 
     * shape representation.
     * 
     * @param anIdentifier an unique identifier for the shape.
     * @param text the string containing wide characters to convert into a shape.
     *
     * @return an FSDefineShape3 object4 which contains a shape that represents 
     * the characters contained in the string argument.
     */
    virtual FSDefineShape3* CALL defineWideShape(int anIdentifier, const wchar_t* text) = 0;
    /**
     * Deletes this object.
     */
	virtual void CALL destroy() = 0;
    /**
     * Deletes this object.
     *
     * @param p a pointer to a parser object.
     */
    void operator delete(void* p) 
    {
        if (p) 
        {
            FSTextConstructor* constructor = static_cast<FSTextConstructor*>(p);
            constructor->destroy();
        }
    }
};

/**
 * Factory function for creating an FSTextConstructor object.
 */
extern "C" FSTextConstructor* TextConstructor();

}

#endif // __FSTextConstructor_h__
