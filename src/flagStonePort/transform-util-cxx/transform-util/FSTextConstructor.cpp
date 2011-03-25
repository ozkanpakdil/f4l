/*
 * FSTextConstructor.cpp
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
 
#include "FSTextConstructor.h"

#include "FSShapeConstructor.h"
#include "FSCodec.h"

#include <stdlib.h>
#include <stdio.h>
#include <transform/transform.h>

#define OS_2 0x4F532F32
#define HEAD 0x68656164
#define HHEA 0x68686561
#define MAXP 0x6D617870
#define LOCA 0x6C6F6361
#define CMAP 0x636D6170
#define HMTX 0x686D7478
#define NAME 0x6E616D65
#define GLYF 0x676C7966

#define ITLF_SHORT 0
#define ITLF_LONG  1

#define FONT_WEIGHT_THIN       100
#define FONT_WEIGHT_EXTRALIGHT 200
#define FONT_WEIGHT_LIGHT      300
#define FONT_WEIGHT_NORMAL     400
#define FONT_WEIGHT_MEDIUM     500
#define FONT_WEIGHT_SEMIBOLD   600
#define FONT_WEIGHT_BOLD       700
#define FONT_WEIGHT_EXTRABOLD  800
#define FONT_WEIGHT_BLACK      900

#define ON_CURVE    0x01
#define X_SHORT     0x02
#define Y_SHORT     0x04
#define REPEAT_FLAG 0x08
#define X_SAME      0x10
#define Y_SAME      0x20
#define X_POSITIVE  0x10
#define Y_POSITIVE  0x20

#define ARG_1_AND_2_ARE_WORDS    0x01
#define ARGS_ARE_XY_VALUES       0x02
#define WE_HAVE_A_SCALE          0x08
#define WE_HAVE_AN_X_AND_Y_SCALE 0x40
#define WE_HAVE_A_TWO_BY_TWO     0x80
#define MORE_COMPONENTS          0x10

#define NUMBER_OF_METRICS 0
#define SCALE 1
#define GLYPH_OFFSET_SIZE 2

#ifndef WIN32
size_t wcslen(const wchar_t* wstr)
{
    size_t count = 0;
    size_t index = 0;
    
    if (wstr != NULL)
    {
        while (*(wstr+index) != 0)
        {
           count += 1;
           index += 1;
        }
    }
    return count;
}
#endif
    
using namespace transform;

namespace transform {

class FSGlyph
{
public:
    FSGlyph() : 
        shape(), 
        bounds(), 
        advance(0), 
        xCoordinates(NULL), 
        yCoordinates(NULL), 
        onCurve(NULL), 
        endPoints(NULL),
        numberOfPoints(0),
        numberOfEndPoints(0)
    {}
    FSGlyph(const FSShape& aShape, const FSBounds& aBounds) : 
        shape(aShape), 
        bounds(aBounds), 
        advance(0), 
        xCoordinates(NULL), 
        yCoordinates(NULL), 
        onCurve(NULL), 
        endPoints(NULL),
        numberOfPoints(0),
        numberOfEndPoints(0) 
    {}
    ~FSGlyph()
    {
        delete [] xCoordinates;
        delete [] yCoordinates;
        delete [] onCurve;
        delete [] endPoints;
    }
    FSGlyph& operator= (const FSGlyph& rhs)
    {
        if (this != &rhs)
        {
            shape = rhs.shape;
            bounds = rhs.bounds;
            advance = rhs.advance;

            delete [] xCoordinates;
            delete [] yCoordinates;
            delete [] onCurve;

            xCoordinates = new int[rhs.numberOfPoints];
            yCoordinates = new int[rhs.numberOfPoints];
            onCurve = new bool[rhs.numberOfPoints];

            for (int i=0; i<numberOfPoints; i++)
            {
                xCoordinates[i] = rhs.xCoordinates[i];
                yCoordinates[i] = rhs.yCoordinates[i];
                onCurve[i] = rhs.onCurve[i];
            }

            delete [] endPoints;

            endPoints = new int[rhs.numberOfEndPoints];

            for (int i=0; i<numberOfEndPoints; i++)
            {
                endPoints[i] = rhs.endPoints[i];
            }
        }
        return *this;
    }
    FSShape shape;
    FSBounds bounds;
    int advance;

    int* xCoordinates;
    int* yCoordinates;
    bool* onCurve;
    int* endPoints;

    int numberOfPoints;
    int numberOfEndPoints;
};

class FSTextConstructorImpl : public FSTextConstructor
{
public:
    FSTextConstructorImpl()
    {
        identifier = 0;
        size = 0;
        color = FSColorTable::black();

        name = NULL;
        encoding = 0;
        isBold = false;
        isItalic = false;

        baseline = 0;
        ascent = 0;
        descent = 0;
        leading = 0;
            
        for (unsigned int i=0; i<65536; i++)
        {
            characterTable[i] = 0;
            orderTable[i] = -1;
        }

        glyphTable = NULL;
            
        numberOfGlyphs = 0;
        missingGlyph = 0;

        for (int i=0; i<8; i++)
            attributes[i] = 0;
    }
    ~FSTextConstructorImpl() 
    { 
        delete [] name;
        delete [] glyphTable;
    }
    void operator delete(void* p)
    {
        ::operator delete(p);
    }
    void CALL destroy()
    {
        delete this;
    }
    int CALL setFontFromFile(const char* filename)
    {
        int status = TransformUtil::OK;

        FILE* input = 0;
        unsigned char* buffer = NULL;
        long length = 0;

        if ((input = fopen(filename, "rb")) != 0)
        {
            if (fseek(input, 0, SEEK_END) == 0)
            {
                if ((length = ftell(input)) != -1L)
                {
                    rewind(input);

                    buffer = new unsigned char[length];

                    if (fread(buffer, sizeof(unsigned char), length, input) != length)
                        status = TransformUtil::ReadError;

                    if (fclose(input) != 0)
                        status = TransformUtil::ReadError;
                }
                else
                {
                    status = TransformUtil::ReadError;
                }
            }
            else
            {
                status = TransformUtil::ReadError;
            }
        }
        else
        {
            status = TransformUtil::FileNotFound;
        }

        if (status == TransformUtil::OK)
            status = setFont(buffer, (size_t)length);

        delete [] buffer;

        return status;
    }
    int CALL setFont(const unsigned char* bytes, size_t numberOfBytes)
    {
        int status = TransformUtil::OK;

        identifier = 0;
        size = 0;
        color = FSColorTable::black();

        if (name != NULL)
        {
            delete [] name;
            name = NULL;
        }

        encoding = 0;
        isBold = false;
        isItalic = false;

        baseline = 0;
        ascent = 0;
        descent = 0;
        leading = 0;
            
        numberOfGlyphs = 0;
        missingGlyph = 0;

        for (int i=0; i<65536; i++)
        {
            characterTable[i] = 0;
            orderTable[i] = -1;
        }

        if (glyphTable != NULL)
        {
            delete [] glyphTable;
            glyphTable = NULL;
        }

        kernings.resize(0);
            
        for (int i=0; i<8; i++)
            attributes[i] = 0;

        int signature = ((bytes[0] & 0xFF) << 16) | ((bytes[1] & 0xFF) << 8) | (bytes[2] & 0xFF);

        switch (signature)
        {
            case 0x465743: status = decodeSWFFont(bytes, numberOfBytes); break;
            case 0x465753: status = decodeSWFFont(bytes, numberOfBytes); break;
            default: status = decodeOpenTypeFont(bytes, numberOfBytes); break;
        }
        return status;
    }
    void CALL setIdentifier(int anIdentifier) 
    { 
        identifier = anIdentifier; 
    }
    void CALL setSize(unsigned int fontSize) 
    { 
        size = fontSize; 
    }
    void CALL setColor(const FSColor* fontColor) 
    { 
        color = FSColor(*fontColor); 
    }
    int CALL canDisplayCharacters(const char* aString)
    {
        int firstMissingChar = -1;
        size_t len = strlen(aString);

        for (unsigned int i=0; i<len; i++)
        {
            unsigned short index = (unsigned short)aString[i];

            if (index > 65536 || characterTable[index] == 0)
            {
                firstMissingChar = i;
                break;
            }
        }
        return firstMissingChar;
    }  
    int CALL canDisplayWideCharacters(const wchar_t* aString)
    {
        int firstMissingChar = -1;
        int len = 0;

        while (aString[len++] != 0);

        for (int i=0; i <len; i++)
        {
            unsigned short index = (unsigned short)aString[i];

            if (index > 65536 || characterTable[index] == 0)
            {
                firstMissingChar = i;
                break;
            }
        }
        return firstMissingChar;
    }
    FSDefineFont2* CALL defineFont()
    {
        FSDefineFont2* font = NULL;
        int count = 0;
        
        for (count=0; orderTable[count] != -1 && count<65536; count++);

        FSVector<FSShape> glyphsArray(count);
        FSVector<int> codesArray(count);
        FSVector<int> advancesArray(count);
        FSVector<FSBounds> boundsArray(count);

        for (int i=0; i<count; i++)
        {
            unsigned short glyphIndex = (unsigned short)orderTable[i];
            unsigned short character = 0;
            
            while (characterTable[character] != glyphIndex) character++;
 
            glyphsArray[i] = glyphTable[glyphIndex].shape;
            codesArray[i] = character;
            advancesArray[i] = glyphTable[glyphIndex].advance;
            boundsArray[i] = glyphTable[glyphIndex].bounds;
        }

        font = new FSDefineFont2(identifier, name);
                
        font->setEncoding(encoding);
        font->setItalic(isItalic);
        font->setBold(isBold);
        font->setAscent((int)ascent);
        font->setDescent((int)descent);
        font->setLeading((int)leading);
        font->setShapes(glyphsArray);
        font->setCodes(codesArray);
        font->setAdvances(advancesArray);
        font->setBounds(boundsArray);
        font->setKernings(kernings);
        
        return font;
    }
    FSDefineText2* CALL defineText(int anIdentifier, const char* text)
    {
        FSDefineText2* textDefinition = NULL;

        FSCoordTransform coordTransform(0, 0);

        float scaleFactor = ((float)size) / 1024.0f;
        int* glyphCodes = new int[strlen(text)];
        int* glyphAdvances = new int[strlen(text)];

        int yOffset = 0;

        yOffset = (int)(baseline*scaleFactor);
        yOffset += (20 - (yOffset % 20));

        glyphIndicesAndAdvancesForString(glyphCodes, glyphAdvances, text);
        
        FSVector<FSCharacter> characters((int)strlen(text));

        for (unsigned int i=0; i <strlen(text); i++)
            characters[i] = FSCharacter(glyphCodes[i], glyphAdvances[i]);

        FSText textRecord(identifier, color, 0, yOffset, size, characters);

        FSVector<FSText> textRecords;

        textRecords.push_back(textRecord);

        textDefinition = new FSDefineText2(anIdentifier,
            boundsForText(glyphCodes, glyphAdvances, strlen(text)), coordTransform, textRecords);

        delete [] glyphCodes;
        delete [] glyphAdvances;

        return textDefinition;
    }
    FSDefineText2* CALL defineWideText(int anIdentifier, const wchar_t* text)
    {
        FSDefineText2* textDefinition = NULL;

        FSCoordTransform coordTransform(0, 0);

        float scaleFactor = ((float)size) / 1024.0f;
        int* glyphCodes = new int[wcslen(text)];
        int* glyphAdvances = new int[wcslen(text)];

        int yOffset = 0;

        yOffset = (int)(baseline*scaleFactor);
        yOffset += (20 - (yOffset % 20));

        glyphIndicesAndAdvancesForWideString(glyphCodes, glyphAdvances, text);
        
        FSVector<FSCharacter> characters((int)wcslen(text));

        for (unsigned int i=0; i <wcslen(text); i++)
            characters.push_back(FSCharacter(glyphCodes[i], glyphAdvances[i]));

        FSText textRecord(identifier, color, 0, yOffset, size, characters);

        FSVector<FSText> textRecords;

        textRecords.push_back(textRecord);

        textDefinition = new FSDefineText2(anIdentifier,
            boundsForText(glyphCodes, glyphAdvances, wcslen(text)), coordTransform, textRecords);

        delete [] glyphCodes;
        delete [] glyphAdvances;

        return textDefinition;
    }
    FSDefineText2* CALL defineTextBlock(int anIdentifier, const char* lines[], size_t count, int lineSpacing)
    {
        FSCoordTransform coordTransform(0, 0);

        float scaleFactor = ((float)size) / 1024.0f;
        
        int xMin = 0;
        int yMin = 0;
        int xMax = 0;
        int yMax = 0;
        
        int xOffset = 0;
        int yOffset = 0;
        
        yOffset = (int)(baseline*scaleFactor);
        yOffset += (20 - (yOffset % 20));

        FSVector<FSText> textRecords;
        
        int n = 0;

        for (unsigned int i=0; i<count; i++, yOffset += lineSpacing, n++)
        {
            const char* text = lines[i];

            int* glyphCodes = new int[strlen(text)];
            int* glyphAdvances = new int[strlen(text)];

            glyphIndicesAndAdvancesForString(glyphCodes, glyphAdvances, text);
            
            FSBounds bounds = boundsForText(glyphCodes, glyphAdvances, strlen(text));
            
            if (n==0)
            {
                yMin = yMax = bounds.getMinY();
            }
            
            xMin = (xMin < bounds.getMinX()) ? xMin : bounds.getMinX();
            xMax = (xMax > bounds.getMaxX()) ? xMax : bounds.getMaxX();
            yMax += bounds.getHeight();
        
            FSVector<FSCharacter> characters((int)strlen(text));

            for (unsigned int j=0; j<strlen(text); j++)
                characters[j] = FSCharacter(glyphCodes[j], glyphAdvances[j]);

            FSText textRecord(identifier, color, xOffset, yOffset, size, characters);

            textRecords.push_back(textRecord);

            delete [] glyphCodes;
            delete [] glyphAdvances;
        }

        return new FSDefineText2(anIdentifier, FSBounds(xMin, yMin, xMax, yMax), coordTransform, textRecords);
    }
    FSDefineText2* CALL defineWideTextBlock(int anIdentifier, const wchar_t* lines[], size_t count, int lineSpacing)
    {
        FSCoordTransform coordTransform(0, 0);

        float scaleFactor = ((float)size) / 1024.0f;
        
        int xMin = 0;
        int yMin = 0;
        int xMax = 0;
        int yMax = 0;
        
        int xOffset = 0;
        int yOffset = 0;
        
        yOffset = (int)(baseline*scaleFactor);
        yOffset += (20 - (yOffset % 20));

        FSVector<FSText> textRecords;
        
        int n = 0;

        for (unsigned int i=0; i<count; i++, yOffset += lineSpacing, n++)
        {
            const wchar_t* text = lines[i];

            int* glyphCodes = new int[wcslen(text)];
            int* glyphAdvances = new int[wcslen(text)];

            glyphIndicesAndAdvancesForWideString(glyphCodes, glyphAdvances, text);
            
            FSBounds bounds = boundsForText(glyphCodes, glyphAdvances, wcslen(text));
            
            if (n==0)
            {
                yMin = yMax = bounds.getMinY();
            }
            
            xMin = (xMin < bounds.getMinX()) ? xMin : bounds.getMinX();
            xMax = (xMax > bounds.getMaxX()) ? xMax : bounds.getMaxX();
            yMax += bounds.getHeight();
        
            FSVector<FSCharacter> characters((int)wcslen(text));

            for (unsigned int j=0; j<wcslen(text); j++)
                characters[j] = FSCharacter(glyphCodes[j], glyphAdvances[j]);

            FSText textRecord(identifier, color, xOffset, yOffset, size, characters);

            textRecords.push_back(textRecord);

            delete [] glyphCodes;
            delete [] glyphAdvances;
        }

        return new FSDefineText2(anIdentifier, FSBounds(xMin, yMin, xMax, yMax), coordTransform,
            textRecords);
    }
    FSBounds* CALL boundsForText(const char* text)
    {
        FSBounds* bounds = NULL;

        int* glyphCodes = new int[strlen(text)];
        int* glyphAdvances = new int[strlen(text)];

        glyphIndicesAndAdvancesForString(glyphCodes, glyphAdvances, text);

        bounds = new FSBounds(boundsForText(glyphCodes, glyphAdvances, strlen(text)));

        delete [] glyphCodes;
        delete [] glyphAdvances;

        return bounds;
    }
    FSBounds* CALL boundsForWideText(const wchar_t* text)
    {
        FSBounds* bounds = NULL;

        int* glyphCodes = new int[wcslen(text)];
        int* glyphAdvances = new int[wcslen(text)];

        glyphIndicesAndAdvancesForWideString(glyphCodes, glyphAdvances, text);

        bounds = new FSBounds(boundsForText(glyphCodes, glyphAdvances, wcslen(text)));

        delete [] glyphCodes;
        delete [] glyphAdvances;

        return bounds;
    }
    FSDefineShape3* CALL defineShape(int anIdentifier, const char* text)
    {
        FSShapeConstructor* path = ShapeConstructor();
        FSSolidFill* fillStyle = new FSSolidFill(color);
        
        path->addFillStyle(fillStyle);
        path->selectFillStyle(0);

        delete fillStyle;
        
        float scaleFactor = ((float)size) / 1024.0f;
        
        int* glyphCodes = new int[strlen(text)];
        int* glyphAdvances = new int[strlen(text)];

        glyphIndicesAndAdvancesForString(glyphCodes, glyphAdvances, text);
        
        int xOffset = 0;
        
        for (unsigned int i=0; i<strlen(text); i++)
        {
            FSVector<FSShapeObject*> array = glyphTable[orderTable[glyphCodes[i]]].shape.getObjects();
    
            for (FSVector<FSShapeObject*>::iterator j=array.begin(); j != array.end(); j++)
            {
                FSShapeObject* currentObject = (*j);

                if (currentObject->getType() == FSShapeObject::Style)
                {
                    FSShapeStyle* style = (FSShapeStyle*) currentObject;
                    int moveX = (int)(style->getMoveX()*scaleFactor + ((style->getMoveX() < 0) ? (-0.5) : 0.5));
                    int moveY = (int)(style->getMoveY()*scaleFactor + ((style->getMoveY() < 0) ? (-0.5) : 0.5));
                    
                    path->closePath();
                    path->move(moveX + xOffset, moveY);
                }
                else if (currentObject->getType() == FSShapeObject::Line)
                {
                    FSLine* line = (FSLine*) currentObject;
                    int x = (int)(line->getX()*scaleFactor + ((line->getX() < 0) ? (-0.5) : 0.5));
                    int y = (int)(line->getY()*scaleFactor + ((line->getY() < 0) ? (-0.5) : 0.5));

                    path->rline(x, y);
                }
                else if (currentObject->getType() == FSShapeObject::Curve)
                {
                    FSCurve* curve = (FSCurve*) currentObject;
                    int cx = (int)(curve->getControlX()*scaleFactor + ((curve->getControlX() < 0) ? (-0.5) : 0.5));
                    int cy = (int)(curve->getControlY()*scaleFactor + ((curve->getControlY() < 0) ? (-0.5) : 0.5));
                    int ax = (int)(curve->getAnchorX()*scaleFactor + ((curve->getAnchorX() < 0) ? (-0.5) : 0.5));
                    int ay = (int)(curve->getAnchorY()*scaleFactor + ((curve->getAnchorY() < 0) ? (-0.5) : 0.5));

                    path->rcurve(cx, cy, ax, ay);
                }
            }
            path->closePath();
            xOffset += glyphAdvances[i];
        }

        FSDefineShape3* shapeDef = path->defineShape(anIdentifier);

        delete path;

        return shapeDef;
    }
    FSDefineShape3* CALL defineWideShape(int anIdentifier, const wchar_t* text)
    {
        FSShapeConstructor* path = ShapeConstructor();
        FSSolidFill* fillStyle = new FSSolidFill(color);
        
        path->addFillStyle(fillStyle);
        path->selectFillStyle(0);

        delete fillStyle;
        
        float scaleFactor = ((float)size) / 1024.0f;
        
        int* glyphCodes = new int[wcslen(text)];
        int* glyphAdvances = new int[wcslen(text)];

        glyphIndicesAndAdvancesForWideString(glyphCodes, glyphAdvances, text);
        
        int xOffset = 0;
        
        for (unsigned int i=0; i<wcslen(text); i++)
        {
            FSVector<FSShapeObject*> array = glyphTable[orderTable[glyphCodes[i]]].shape.getObjects();
    
            for (FSVector<FSShapeObject*>::iterator j=array.begin(); j != array.end(); j++)
            {
                FSShapeObject* currentObject = (*j);

                if (currentObject->getType() == FSShapeObject::Style)
                {
                    FSShapeStyle* style = (FSShapeStyle*) currentObject;
                    int moveX = (int)(style->getMoveX()*scaleFactor + ((style->getMoveX() < 0) ? (-0.5) : 0.5));
                    int moveY = (int)(style->getMoveY()*scaleFactor + ((style->getMoveY() < 0) ? (-0.5) : 0.5));
                    
                    path->closePath();
                    path->move(moveX + xOffset, moveY);
                }
                else if (currentObject->getType() == FSShapeObject::Line)
                {
                    FSLine* line = (FSLine*) currentObject;
                    int x = (int)(line->getX()*scaleFactor + ((line->getX() < 0) ? (-0.5) : 0.5));
                    int y = (int)(line->getY()*scaleFactor + ((line->getY() < 0) ? (-0.5) : 0.5));

                    path->rline(x, y);
                }
                else if (currentObject->getType() == FSShapeObject::Curve)
                {
                    FSCurve* curve = (FSCurve*) currentObject;
                    int cx = (int)(curve->getControlX()*scaleFactor + ((curve->getControlX() < 0) ? (-0.5) : 0.5));
                    int cy = (int)(curve->getControlY()*scaleFactor + ((curve->getControlY() < 0) ? (-0.5) : 0.5));
                    int ax = (int)(curve->getAnchorX()*scaleFactor + ((curve->getAnchorX() < 0) ? (-0.5) : 0.5));
                    int ay = (int)(curve->getAnchorY()*scaleFactor + ((curve->getAnchorY() < 0) ? (-0.5) : 0.5));

                    path->rcurve(cx, cy, ax, ay);
                }
            }
            path->closePath();
            xOffset += glyphAdvances[i];
        }

        FSDefineShape3* shapeDef = path->defineShape(anIdentifier);

        delete path;

        return shapeDef;
    }
private:
    int decodeSWFFont(const unsigned char* bytes, size_t numberOfBytes)
    {
        FSMovie fontMovie(bytes, numberOfBytes);
        int status = TransformUtil::OK;

        FSDefineFont* font = 0;
        FSFontInfo* fontInfo = 0;
        FSDefineText* text = 0;

        FSText textRecord;

        for (FSVector<FSMovieObject*>::iterator i=fontMovie.getObjects().begin(); i != fontMovie.getObjects().end(); i++)
        {
            FSMovieObject* currentObject = (FSMovieObject*)(*i);

            if (currentObject->getType() == FSMovieObject::DefineFont)
                font = (FSDefineFont*) currentObject;
            else if (currentObject->getType() == FSMovieObject::FontInfo)
                fontInfo = (FSFontInfo*) currentObject;
            else if (currentObject->getType() == FSMovieObject::DefineText)
                text = (FSDefineText*) currentObject;
        }

        textRecord = text->getTextRecords()[0];

        const char* fontName = fontInfo->getName();
        name = new char[strlen(fontName)+1];
        strcpy(name, fontName);

        encoding = fontInfo->getEncoding();
        float fontSize = (float) (textRecord.getHeight());
        isBold = fontInfo->isBold();
        isItalic = fontInfo->isItalic();
        
        /*
         * Change the encoding for ASCII to Unicode since ASCII is compatible
         * with UTF8.
         */
        if (encoding == FSText::ANSI)
            encoding = FSText::Unicode;

        glyphTable = new FSGlyph[font->getShapes().size()];
        
        int glyphIndex = 0;

        for (FSVector<FSShape>::iterator j=font->getShapes().begin(); j != font->getShapes().end(); j++, glyphIndex++)
            glyphTable[glyphIndex] = FSGlyph(*j, FSBounds(0, 0, 0, 0));

        glyphIndex = 0;

        for (FSVector<int>::iterator k=fontInfo->getCodes().begin(); k != fontInfo->getCodes().end(); k++, glyphIndex++)
            characterTable[(*k)] = (unsigned short) glyphIndex;

        for (FSVector<FSCharacter>::iterator l=text->getTextRecords()[0].getCharacters().begin(); l != text->getTextRecords()[0].getCharacters().end(); l++)
            glyphTable[(*l).getGlyphIndex()].advance = (int) ((*l).getAdvance() * (1024.0 / fontSize));

        orderTable[0] = 0;

        return status;
    }
    int decodeOpenTypeFont(const unsigned char* bytes, size_t numberOfBytes)
    {
        FSCodec* coder = Codec(FSCodec::BigEndian);
        coder->setData(bytes, numberOfBytes);

        int status = TransformUtil::OK;
        
        float version = coder->readFixedBits(32, 16);

        int tableCount = coder->readShort();
        int searchRange = coder->readShort();
        int entrySelector = coder->readShort();
        int rangeShift = coder->readShort();
        
        int os_2Offset = 0;
        int headOffset = 0;
        int hheaOffset = 0;
        int maxpOffset = 0;
        int locaOffset = 0;
        int cmapOffset = 0;
        int glyfOffset = 0;
        int hmtxOffset = 0;
        int nameOffset = 0;
        
        int os_2Length = 0;
        int headLength = 0;
        int hheaLength = 0;
        int maxpLength = 0;
        int locaLength = 0;
        int cmapLength = 0;
        int hmtxLength = 0;
        int nameLength = 0;
        int glyfLength = 0;

        int chunkType = 0;
        int checksum = 0;
        int offset = 0;
        int length = 0;
        
        for (int i=0; i<tableCount; i++) 
        {
            chunkType = coder->readInt();
            checksum = coder->readInt();
            offset = coder->readInt() << 3;
            length = coder->readInt();
            
            /* 
             * Chunks are encoded in ascending alphabetical order so
             * the location of the tables is mapped before they are 
             * decoded since the glyphs come before the loca or maxp
             * table which identify how many glyphs are encoded.
             */
            switch (chunkType)
            {
                case OS_2: os_2Offset = offset; os_2Length = length; break;
                case CMAP: cmapOffset = offset; cmapLength = length; break;
                case GLYF: glyfOffset = offset; glyfLength = length; break;
                case HEAD: headOffset = offset; headLength = length; break;
                case HHEA: hheaOffset = offset; hheaLength = length; break;
                case HMTX: hmtxOffset = offset; hmtxLength = length; break;
                case LOCA: locaOffset = offset; locaLength = length; break;
                case MAXP: maxpOffset = offset; maxpLength = length; break;
                case NAME: nameOffset = offset; nameLength = length; break;
                default: break;
            }
        }
        
        int bytesRead = 0;

        if (maxpOffset != 0) { coder->setPointer(maxpOffset); decodeMAXP(coder); bytesRead = (coder->getPointer() - maxpOffset) >> 3; }
        if (os_2Offset != 0) { coder->setPointer(os_2Offset); decodeOS_2(coder); bytesRead = (coder->getPointer() - os_2Offset) >> 3; }
        if (headOffset != 0) { coder->setPointer(headOffset); decodeHEAD(coder); bytesRead = (coder->getPointer() - headOffset) >> 3; }
        if (hheaOffset != 0) { coder->setPointer(hheaOffset); decodeHHEA(coder); bytesRead = (coder->getPointer() - hheaOffset) >> 3; }
        if (nameOffset != 0) { coder->setPointer(nameOffset); decodeNAME(coder); bytesRead = (coder->getPointer() - nameOffset) >> 3; }
        
        glyphTable = new FSGlyph[numberOfGlyphs];
        
        // Decode glyphs first so objects will be created.
        if (locaOffset != 0) { coder->setPointer(locaOffset); decodeGlyphs(coder, glyfOffset); bytesRead = (coder->getPointer() - locaOffset) >> 3; }
        if (hmtxOffset != 0) { coder->setPointer(hmtxOffset); decodeHMTX(coder); bytesRead = (coder->getPointer() - hmtxOffset) >> 3; }
        if (cmapOffset != 0) { coder->setPointer(cmapOffset); status = decodeCMAP(coder); bytesRead = (coder->getPointer() - cmapOffset) >> 3; }

        orderTable[0] = (unsigned short)missingGlyph;
        
        for (int i=0; i<65536; i++)
        {
            if (characterTable[i] >= numberOfGlyphs)
                characterTable[i] = (unsigned short)missingGlyph;
        }
        delete coder;

        return status;
    }

    void decodeHEAD(FSCodec* coder)
    {
        byte date[8];
    
        coder->readFixedBits(32, 16); // table version 
        coder->readFixedBits(32, 16); // font version 
        coder->readInt(); // checksum adjustment
        coder->readInt(); // magic number
        coder->readBits(1); // baseline at y=0
        coder->readBits(1); // side bearing at x=0;
        coder->readBits(1); // instructions depend on point size
        coder->readBits(1); // force ppem to integer values
        coder->readBits(1); // instructions may alter advance
        coder->readBits(11);
        attributes[SCALE] = coder->readShort() / 1024;  // units per em

        if (attributes[SCALE] == 0) 
            attributes[SCALE] = 1;

        coder->readBytes(date, 8); // number of seconds since midnight, Jan 01 1904
        coder->readBytes(date, 8); // number of seconds since midnight, Jan 01 1904
    
        coder->readSignedShort(); // xMin for all glyph bounding boxes
        coder->readSignedShort(); // yMin for all glyph bounding boxes
        coder->readSignedShort(); // xMax for all glyph bounding boxes
        coder->readSignedShort(); // yMax for all glyph bounding boxes
    
        /*
         * Next two byte define font appearance on Macs, values are 
         * specified in the OS/2 table 
         */ 
        isBold = coder->readBits(1) != 0;
        isItalic = coder->readBits(1) != 0;
        coder->readBits(14); // 

        coder->readShort();// smallest readable size in pixels
        coder->readSignedShort(); // font direction hint
        attributes[GLYPH_OFFSET_SIZE] = coder->readSignedShort(); 
        coder->readSignedShort(); // glyph data format
    }
    void decodeHHEA(FSCodec* coder)
    {
        coder->readFixedBits(32, 16); // table version
    
        ascent = (float)coder->readSignedShort();
        descent = (float)coder->readSignedShort();
        leading = (float)coder->readSignedShort();
        
        coder->readShort(); // maximum advance in the htmx table
        coder->readSignedShort(); // minimum left side bearing in the htmx table
        coder->readSignedShort(); // minimum right side bearing in the htmx table
        coder->readSignedShort(); // maximum extent
        coder->readSignedShort(); // caret slope rise 
        coder->readSignedShort(); // caret slope run
        coder->readSignedShort(); // caret offset
    
        coder->readShort(); // reserved
        coder->readShort(); // reserved
        coder->readShort(); // reserved
        coder->readShort(); // reserved
    
        coder->readSignedShort(); // metric data format 
        
        attributes[NUMBER_OF_METRICS] = coder->readShort();    
    }
    void decodeOS_2(FSCodec* coder)
    {
        byte panose[10];
        int unicodeRange[4];
        byte vendor[4];

        int version = coder->readShort(); // version
        coder->readSignedShort(); // average character width
        
        switch (coder->readShort()) // weight class
        {
            case FONT_WEIGHT_BOLD: isBold = true; break;
            default: break;
        }

        coder->readShort(); // width class
        coder->readShort(); // embedding licence
        
        coder->readSignedShort(); // subscript x size
        coder->readSignedShort(); // subscript y size
        coder->readSignedShort(); // subscript x offset
        coder->readSignedShort(); // subscript y offset
        coder->readSignedShort(); // superscript x size
        coder->readSignedShort(); // superscript y size
        coder->readSignedShort(); // superscript x offset
        coder->readSignedShort(); // superscript y offset
        coder->readSignedShort(); // width of strikeout stroke
        coder->readSignedShort(); // strikeout stroke position
        coder->readSignedShort(); // font family class
    
        coder->readBytes(panose, 4);
        
        for (int i=0; i<4; i++)
            unicodeRange[i] = coder->readInt();
            
        coder->readBytes(vendor, 4); // font vendor identification
        
        isItalic = coder->readBits(1) != 0;
        coder->readBits(4);
        isBold = coder->readBits(1) != 0;
        coder->readBits(10);
        
        coder->readShort(); // first unicode character code
        coder->readShort(); // last unicode character code
        
        ascent = (float)coder->readShort();
        descent = (float)coder->readShort();
        leading = (float)coder->readShort();
    
        coder->readShort(); // ascent in Windows
        coder->readShort(); // descent in Windows
        
        if (version > 0)
        {
            coder->readInt(); // code page range 
            coder->readInt(); // code page range

            if (version > 1)
            {
                coder->readSignedShort(); // height
                coder->readSignedShort(); // Capitals height
                missingGlyph = coder->readShort();
                coder->readShort(); // break character
                coder->readShort(); // maximum context
            }
        }
    }
    void decodeNAME(FSCodec* coder)
    {
        int format = coder->readShort();
        int numberOfNameRecords = coder->readShort();
        int stringTable = coder->readShort();
        
        for (int i=0; i<numberOfNameRecords; i++) 
        {
            int platformId = coder->readShort();
            int encodingId = coder->readShort();
            int languageId = coder->readShort();
            int nameId = coder->readShort();
            
            int stringLength = coder->readShort();
            int stringOffset = coder->readShort();
            
            int current = coder->getPointer();
            
            coder->setPointer((stringTable+stringOffset) << 3);
            name = new char[stringLength];
            coder->readBytes((unsigned char*)name, stringLength);
            
            FSString nameEncoding = "UTF-8";
            
            if (platformId == 0) // Unicode
            {
                nameEncoding = "UTF-16";
            }
            else if (platformId == 1) // Macintosh
            {
                if (encodingId == 0 && languageId == 0)
                    nameEncoding = "ISO8859-1";
            }
            else if (platformId == 3) // Microsoft
            {
                switch (encodingId)
                {
                    case 1: nameEncoding = "UTF-16"; break;
                    case 2: nameEncoding = "SJIS"; break;
                    case 4: nameEncoding = "Big5"; break;
                }
            }
            
            // Porting Issue: The name might use different character encoding
            // name is set directly - see above

            //name = new char[strlen(b)+1];
            //strcpy(name, b);
            //delete [] b;

            coder->setPointer(current);
        }
    }
    void decodeMAXP(FSCodec* coder)
    {
        float version = coder->readFixedBits(32, 16);
        numberOfGlyphs = coder->readShort();
        
        if (version == 1.0)
        {
            coder->readShort(); // maximum number of points in a simple glyph
            coder->readShort(); // maximum number of contours in a simple glyph
            coder->readShort(); // maximum number of points in a composite glyph
            coder->readShort(); // maximum number of contours in a composite glyph
            coder->readShort(); // maximum number of zones
            coder->readShort(); // maximum number of point in Z0
            coder->readShort(); // number of storage area locations
            coder->readShort(); // maximum number of FDEFs
            coder->readShort(); // maximum number of IDEFs
            coder->readShort(); // maximum stack depth
            coder->readShort(); // maximum byte count for glyph instructions
            coder->readShort(); // maximum number of components for composite glyphs
            coder->readShort(); // maximum level of recursion
        }
    }
    void decodeHMTX(FSCodec* coder)
    {
        unsigned int i = 0;
        
        for (i=0; i<(unsigned int)attributes[NUMBER_OF_METRICS]; i++) 
        {
            glyphTable[i].advance = (coder->readShort() / attributes[SCALE]);
            coder->readSignedShort(); // left side bearing
        }
        
        int advance = glyphTable[i-1].advance;

        for (; i<numberOfGlyphs; i++)
            glyphTable[i].advance = advance;

        for (; i<numberOfGlyphs; i++)
            coder->readSignedShort();
    }
    int decodeCMAP(FSCodec* coder)
    {
        int tableStart = coder->getPointer();
        int status = TransformUtil::OK;
        
        int version = coder->readShort();
        int numberOfTables = coder->readShort();
        
        int platformId = 0;
        int encodingId = 0;
        int offset = 0;
        int current = 0;
        
        int format = 0;
        int length = 0;
        int language = 0;
        
        int segmentCount = 0;
        int* startCount = 0;
        int* endCount = 0;
        int* delta = 0;
        int* range = 0;
        int* rangeAdr = 0;
        
        int i = 0;
        int n = 0;

        for (i=0; i<numberOfTables; i++)
        {
            platformId = coder->readShort();
            encodingId = coder->readShort();
            offset = coder->readInt() << 3;
            current = coder->getPointer();
            
            if (platformId == 0) // Unicode
            {
                encoding = FSText::Unicode;
            }
            else if (platformId == 1) // Macintosh
            {
                switch (encodingId)
                {
                    case 1: encoding = FSText::SJIS; break;
                    default: encoding = FSText::ANSI; break;
                }
                    
            }
            else if (platformId == 3) // Microsoft
            {
                switch (encodingId)
                {
                    case 1: encoding = FSText::Unicode; break;
                    case 2: encoding = FSText::SJIS; break;
                    default: encoding = FSText::ANSI; break;
                }
            }

            coder->setPointer(tableStart+offset);
            
            format = coder->readShort();
            length = coder->readShort();
            language = coder->readShort();
            
            int glyphIndex = 0;
            int location = 0;
                            
            switch (format) 
            {
                case 0: 
                    for (n=0; n<256; n++)
                        characterTable[n] = (short)coder->readByte();
                    break;
                case 4:
                    segmentCount = coder->readShort() / 2;
    
                    coder->readShort(); // search range
                    coder->readShort(); // entry selector
                    coder->readShort(); // range shift

                    startCount = new int[segmentCount];
                    endCount = new int[segmentCount];
                    delta = new int[segmentCount];
                    range = new int[segmentCount];
                    rangeAdr = new int[segmentCount];
                    
                    for (n=0; n<segmentCount; n++)
                        endCount[n] = coder->readShort();

                    coder->readShort(); // reserved padding
                
                    for (n=0; n<segmentCount; n++)
                        startCount[n] = coder->readShort();
                
                    for (n=0; n<segmentCount; n++)
                        delta[n] = coder->readSignedShort();
                
                    for (n=0; n<segmentCount; n++)
                    {
                        rangeAdr[n] = coder->getPointer() >> 3;
                        range[n] = coder->readSignedShort();
                    }

                    glyphIndex = 0;
                    location = 0;
                            
                    for (n=0; n<segmentCount; n++)
                    {
                        for (int code=startCount[n]; code<=endCount[n]; code++)
                        {
                            if (range[n] != 0)
                            {
                                location = rangeAdr[n] + range[n] + ((code - startCount[n]) << 1);
                                coder->setPointer(location << 3);
                                glyphIndex = coder->readShort();
                                
                                if (glyphIndex != 0)
                                    glyphIndex = (glyphIndex + delta[n]) % 65536;
                            }
                            else
                                glyphIndex = (delta[n] + code) % 65536;

                            characterTable[code] = (unsigned short)glyphIndex;
                        }
                    }
                    break;
                case 2:
                case 6:
                    // Unimplemented encoding table format.
                    status = TransformUtil::FormatError;
                    break;
                default: 
                    // Illegal value for encoding table format.
                    status = TransformUtil::FormatError;
                    break;
            }
            coder->setPointer(current);
        }
        encoding = FSText::SJIS;

        delete [] startCount;
        delete [] endCount;
        delete [] delta;
        delete [] range;
        delete [] rangeAdr;

        return status;
    }
    void decodeGlyphs(FSCodec* coder, int glyfOffset)
    {
        unsigned int* offsets = new unsigned int[numberOfGlyphs];
        int numberOfContours = 0;

        int endOfTable = 0;
        
        if (attributes[GLYPH_OFFSET_SIZE] == ITLF_SHORT)
            offsets[0] = glyfOffset + (coder->readShort()*2 << 3);
        else
            offsets[0] = glyfOffset + (coder->readInt() << 3);

        for (unsigned int i=1; i<numberOfGlyphs; i++)
        {
            if (attributes[GLYPH_OFFSET_SIZE] == ITLF_SHORT)
                offsets[i] = glyfOffset + (coder->readShort()*2 << 3);
            else
                offsets[i] = glyfOffset + (coder->readInt() << 3);

            if (offsets[i-1] == offsets[i])
                offsets[i-1] = 0;
        }

        endOfTable = coder->getPointer();
            
        for (unsigned int i=0; i<numberOfGlyphs; i++)
        {
            if (offsets[i] == 0)
            {
                glyphTable[i] = FSGlyph(FSShape(), FSBounds(0, 0, 0, 0));
            }
            else
            {
                coder->setPointer(offsets[i]);

                numberOfContours = coder->readSignedShort();
            
                if (numberOfContours >= 0)
                    decodeSimpleGlyph(coder, i, numberOfContours);
            }
        }
        
        for (unsigned int i=0; i<numberOfGlyphs; i++)
        {
            if (offsets[i] != 0)
            {
                coder->setPointer(offsets[i]);
            
                if (coder->readSignedShort() == -1)
                    decodeCompositeGlyph(coder, i);
            }
        }
        coder->setPointer(endOfTable);

        delete [] offsets;
    }
    void decodeSimpleGlyph(FSCodec* coder, int glyphIndex, int numberOfContours)
    {
        int xMin = coder->readSignedShort() / attributes[SCALE];
        int yMin = coder->readSignedShort() / attributes[SCALE];
        int xMax = coder->readSignedShort() / attributes[SCALE];
        int yMax = coder->readSignedShort() / attributes[SCALE];
        
        int* endPtsOfContours = new int[numberOfContours];

        for (int i=0; i<numberOfContours; i++)
            endPtsOfContours[i] = coder->readShort();

        int instructionCount = coder->readShort();   
        int* instructions = new int[instructionCount];
            
        for (int i=0; i<instructionCount; i++)
            instructions[i] = coder->readByte();
                
        int numberOfPoints = (numberOfContours == 0) ? 0 : endPtsOfContours[numberOfContours-1]+1;
        
        int* flags = new int[numberOfPoints];
        int* xCoordinates = new int[numberOfPoints];
        int* yCoordinates = new int[numberOfPoints];
        bool* onCurve = new bool[numberOfPoints];
        
        int repeatCount = 0;
        int repeatFlag  = 0;
            
        for (int i=0; i<numberOfPoints; i++) 
        {
            if (repeatCount > 0) 
            {
                flags[i] = repeatFlag;
                repeatCount--;
            } 
            else 
            {
                flags[i] = coder->readByte();
                    
                if ((flags[i] & REPEAT_FLAG) > 0) 
                {
                    repeatCount = coder->readByte();
                    repeatFlag = flags[i];
                }
            }
            onCurve[i] = (flags[i] & ON_CURVE) > 0;
        }

        int last = 0;

        for (int i=0; i<numberOfPoints; i++) 
        {        
            if ((flags[i] & X_SHORT) > 0) 
            {
                if ((flags[i] & X_POSITIVE) > 0)
                    last = xCoordinates[i] = last + coder->readByte();
                else 
                    last = xCoordinates[i] = last - coder->readByte();
            } 
            else 
            {
                if ((flags[i] & X_SAME) > 0)
                    last = xCoordinates[i] = last;
                else
                    last = xCoordinates[i] = last + coder->readSignedShort();
            }
        }

        last = 0;

        for (int i = 0; i < numberOfPoints; i++) 
        {
            if ((flags[i] & Y_SHORT) > 0)
            {
                if ((flags[i] & Y_POSITIVE) > 0)
                    last = yCoordinates[i] = last + coder->readByte();
                else 
                    last = yCoordinates[i] = last - coder->readByte();
            } 
            else 
            {
                if ((flags[i] & Y_SAME) > 0)
                    last = yCoordinates[i] = last;
                else 
                    last = yCoordinates[i] = last + coder->readSignedShort();
            }
        }

        delete [] instructions;
        delete [] flags;
            
        /*
         * Convert the coordinates into a shape
         */
        FSShapeConstructor* path = ShapeConstructor();
        
        bool contourStart = true;
        bool offPoint = false;
        
        int contour = 0;
        
        int x = 0;
        int y = 0;
        
        int prevX = 0;
        int prevY = 0;
        
        int initX = 0;
        int initY = 0;
        
        for (int i=0; i<numberOfPoints; i++)
        {
            x = xCoordinates[i] / attributes[SCALE];
            y = yCoordinates[i] / attributes[SCALE];
            
            if (onCurve[i])
            {
                if (contourStart)
                {
                    path->moveForFont(x, -y);
                    contourStart = false;
                    initX = x;
                    initY = y;
                }
                else if (offPoint)
                {
                    path->curve(prevX, -prevY, x, -y);
                    offPoint = false;
                }
                else
                {
                    path->line(x, -y);
                }
            }
            else
            {
                if (offPoint == true)
                    path->curve(prevX, -prevY, (x+prevX)/2, -(y+prevY)/2);

                prevX = x;
                prevY = y;
                offPoint = true;
            }
            
            if (i == endPtsOfContours[contour])
            {
                if (offPoint)
                {
                    path->curve(x, -y, initX, -initY);
                }
                else
                {
                    path->closePath();
                } 
                contourStart = true;
                offPoint = false;
                prevX = 0;
                prevY = 0;
                contour++;
            }
        }
        
        FSDefineShape3* shape = path->defineShape(0);

        glyphTable[glyphIndex] = FSGlyph(shape->getShape(), FSBounds(xMin, -yMax, xMax, -yMin));

        delete shape;
        delete path;

        glyphTable[glyphIndex].xCoordinates = xCoordinates;
        glyphTable[glyphIndex].yCoordinates = yCoordinates;
        glyphTable[glyphIndex].onCurve = onCurve;
        glyphTable[glyphIndex].endPoints = endPtsOfContours;
    }      
    void decodeCompositeGlyph(FSCodec* coder, int glyphIndex)
    {
        FSShape shape;
        FSCoordTransform transform;
                        
        int xMin = coder->readSignedShort();
        int yMin = coder->readSignedShort();
        int xMax = coder->readSignedShort();
        int yMax = coder->readSignedShort();
        
        FSGlyph points;
        
        int numberOfPoints = 0;
        
        int* endPtsOfContours = 0;
        int* xCoordinates = 0;
        int* yCoordinates = 0;
        bool* onCurve = 0;
        
        int flags = 0;
        unsigned int sourceGlyph = 0;
        
        int xOffset = 0;
        int yOffset = 0;
        
        int sourceIndex = 0;
        int destIndex = 0;

        do {
            transform = FSCoordTransform();
            
            flags = coder->readShort();
            sourceGlyph = coder->readShort();
            
            if (sourceGlyph >= numberOfGlyphs)
            {
                glyphTable[glyphIndex] = FSGlyph();            
                glyphTable[glyphIndex].bounds = FSBounds(xMin, yMin, xMax, yMax);
                return;
            }
            
            points = glyphTable[sourceGlyph];
            numberOfPoints = points.numberOfPoints;
            
            endPtsOfContours = new int[points.numberOfEndPoints];
            
            for (int i=0; i<points.numberOfEndPoints; i++)
                endPtsOfContours[i] = points.endPoints[i];
                
            xCoordinates = new int[numberOfPoints];
            
            for (int i=0; i<numberOfPoints; i++)
                xCoordinates[i] = points.xCoordinates[i];
                
            yCoordinates = new int[numberOfPoints];
            
            for (int i=0; i<numberOfPoints; i++)
                yCoordinates[i] = points.yCoordinates[i];
                
            onCurve = new bool[numberOfPoints];
            
            for (int i=0; i<numberOfPoints; i++)
                onCurve[i] = points.onCurve[i];
            
            if ((flags & ARG_1_AND_2_ARE_WORDS) == 0 && (flags & ARGS_ARE_XY_VALUES) == 0)
            {
                destIndex = coder->readByte();
                sourceIndex = coder->readByte();
                
                //xCoordinates[destIndex] = glyphTable[sourceGlyph].xCoordinates[sourceIndex];
                //yCoordinates[destIndex] = glyphTable[sourceGlyph].yCoordinates[sourceIndex];
                transform.translate(0, 0);
            }
            else if ((flags & ARG_1_AND_2_ARE_WORDS) == 0 && (flags & ARGS_ARE_XY_VALUES) > 0)
            {
                xOffset = (coder->readByte() << 24) >> 24;
                yOffset = (coder->readByte() << 24) >> 24;
                transform.translate(xOffset, yOffset);
            }
            else if ((flags & ARG_1_AND_2_ARE_WORDS) > 0 && (flags & ARGS_ARE_XY_VALUES) == 0)
            {
                destIndex = coder->readShort();
                sourceIndex = coder->readShort();
                
                //xCoordinates[destIndex] = glyphTable[sourceGlyph].xCoordinates[sourceIndex];
                //yCoordinates[destIndex] = glyphTable[sourceGlyph].yCoordinates[sourceIndex];
                transform.translate(0, 0);
            }
            else
            {
                xOffset = coder->readSignedShort();
                yOffset = coder->readSignedShort();
                transform.translate(xOffset, yOffset);
            }
            
            
            if ((flags & WE_HAVE_A_SCALE) > 0) 
            {
                float scaleXY = coder->readFixedBits(16, 14);
                transform.scale(scaleXY, scaleXY);
            }
            else if ((flags & WE_HAVE_AN_X_AND_Y_SCALE) > 0)
            {
                float scaleX = coder->readFixedBits(16, 14);
                float scaleY = coder->readFixedBits(16, 14);
                transform.scale(scaleX, scaleY);
            }
            else if ((flags & WE_HAVE_A_TWO_BY_TWO) > 0) 
            {
                float scaleX = coder->readFixedBits(16, 14);
                float scale01 = coder->readFixedBits(16, 14);
                float scale10 = coder->readFixedBits(16, 14);
                float scaleY = coder->readFixedBits(16, 14);
                
                float matrix[3][3];

                matrix[0][0] = scaleX;
                matrix[0][1] = scale01;
                matrix[0][2] = 0.0f;
                matrix[1][0] = scale10;
                matrix[1][1] = scaleY;
                matrix[1][2] = 0.0f;
                matrix[2][0] = 0.0f;
                matrix[2][1] = 0.0f;
                matrix[2][2] = 1.0f;

                transform.composite(FSCoordTransform(matrix));
            }
            
            for (int i=0; i<numberOfPoints; i++)
                transform.transformPoint(xCoordinates[i], yCoordinates[i]);

            FSShapeConstructor* path = ShapeConstructor();
        
            bool contourStart = true;
            bool offPoint = false;
        
            int contour = 0;
        
            int x = 0;
            int y = 0;
        
            int prevX = 0;
            int prevY = 0;
        
            int initX = 0;
            int initY = 0;
        
            for (int i=0; i<numberOfPoints; i++)
            {
                x = xCoordinates[i] / attributes[SCALE];
                y = yCoordinates[i] / attributes[SCALE];
            
                if (onCurve[i])
                {
                    if (contourStart)
                    {
                        path->moveForFont(x, -y);
                        contourStart = false;
                        initX = x;
                        initY = y;
                    }
                    else if (offPoint)
                    {
                        path->curve(prevX, -prevY, x, -y);
                        offPoint = false;
                    }
                    else
                    {
                        path->line(x, -y);
                    }
                }
                else
                {
                    if (offPoint == true)
                        path->curve(prevX, -prevY, (x+prevX)/2, -(y+prevY)/2);

                    prevX = x;
                    prevY = y;
                    offPoint = true;
                }
            
                if (i == endPtsOfContours[contour])
                {
                    if (offPoint)
                    {
                        path->curve(x, -y, initX, -initY);
                    }
                    else
                    {
                        path->closePath();
                    } 
                    contourStart = true;
                    offPoint = false;
                    prevX = 0;
                    prevY = 0;
                    contour++;
                }
            }

            FSDefineShape3* shapeDef = path->defineShape(0);
            FSVector<FSShapeObject*>& shapeObjects = shapeDef->getShape().getObjects();

            for (FSVector<FSShapeObject*>::iterator j = shapeObjects.begin(); j != shapeObjects.end(); j++)
                shape.getObjects().push_back((*j)->clone());

            delete shapeDef;
            delete path;

        } while ((flags & MORE_COMPONENTS) > 0);

        glyphTable[glyphIndex] = FSGlyph(shape, FSBounds(xMin, yMin, xMax, yMax));

        glyphTable[glyphIndex].xCoordinates = xCoordinates;
        glyphTable[glyphIndex].yCoordinates = yCoordinates;
        glyphTable[glyphIndex].onCurve = onCurve;
        glyphTable[glyphIndex].endPoints = endPtsOfContours;
    }

    void glyphIndicesAndAdvancesForString(int* glyphCodes, int* glyphAdvances, const char* aString)
    {
        unsigned int length = (unsigned int)strlen(aString);
        float scale = ((float)size) / 1024.0f;

        for (unsigned int i=0; i<length; i++)
        {
            int glyphIndex = characterTable[(unsigned short)aString[i]];
            int index = 0;

            for (index=0; index<65536; index++)
            {
                if (orderTable[index] == glyphIndex)
                {
                    break;
                }
                else if (orderTable[index] == -1)
                {
                    orderTable[index] = glyphIndex;
                    break;
                }
            }
            glyphCodes[i] = index;
            glyphAdvances[i] = (int) (glyphTable[(unsigned int)orderTable[index]].advance * scale);
        }
    }
    void glyphIndicesAndAdvancesForWideString(int* glyphCodes, int* glyphAdvances, const wchar_t* aString)
    {
        unsigned int length = (unsigned int)wcslen(aString);
        float scale = ((float)size) / 1024.0f;

        for (unsigned int i=0; i<length; i++)
        {
            int glyphIndex = characterTable[(unsigned short)aString[i]];
            int index = 0;
            
            for (index=0; index<65536; index++)
            {
                if (orderTable[index] == glyphIndex)
                {
                    break;
                }
                else if (orderTable[index] == -1)
                {
                    orderTable[index] = glyphIndex;
                    break;
                }
            }
            glyphCodes[i] = index;
            glyphAdvances[i] = (int) (glyphTable[(unsigned int)orderTable[index]].advance * scale);
        }
    }
    
    FSBounds boundsForText(int* glyphIndices, int* advances, size_t count)
    {
        float scaleEMSquare = ((float)size) / 1024.0f;

        int advance = 0;

        int minX = 0;
        int maxX = (int)(advances[count - 1] / scaleEMSquare);

        int ascent = 0;
        int descent = 0;

        for (unsigned int i=0; i<count; i++)
        {
            FSVector<FSShapeObject*> array = glyphTable[glyphIndices[i]].shape.getObjects();

            int x = 0;
            int y = 0;

            for (FSVector<FSShapeObject*>::iterator j=array.begin(); j != array.end(); j++)
            {
                FSShapeObject* currentObject = *j;

                if (currentObject->getType() == FSShapeObject::Style)
                {
                    FSShapeStyle* style = (FSShapeStyle*) currentObject;

                    x = style->getMoveX();
                    y = style->getMoveY();
                }
                else if (currentObject->getType() == FSShapeObject::Line)
                {
                    FSLine* line = (FSLine*) currentObject;

                    x += line->getX();
                    y += line->getY();
                }
                else if (currentObject->getType() == FSShapeObject::Curve)
                {
                    FSCurve* curve = (FSCurve*) currentObject;

                    x += (curve->getControlX() + curve->getAnchorX());
                    y += (curve->getControlY() + curve->getAnchorY());
                }
                
                minX = ((i == 0) && (x < minX)) ? x : minX;
                maxX = ((i == (count - 1)) && (x > maxX)) ? x : maxX;

                ascent = (y < ascent) ? y : ascent;
                descent = (y > descent) ? y : descent;
            }
            advance += advances[i];
        }

        minX = (int) (minX * scaleEMSquare);
        ascent = (int) (ascent * scaleEMSquare);
        descent = (int) (descent * scaleEMSquare);

        return FSBounds(minX, ascent, advance, descent);
    }

    int identifier;
    int size;
    FSColor color;

    char* name;

    int encoding;
    bool isBold;
    bool isItalic;

    int baseline;
    float ascent;
    float descent;
    float leading;
    
    unsigned short characterTable[65536];
    int orderTable[65536];

    FSGlyph* glyphTable;
    
    unsigned int numberOfGlyphs;
    unsigned int missingGlyph;
    
    FSVector<FSKerning> kernings;
    int attributes[8];
};

extern "C" FSTextConstructor* TextConstructor()
{
    return new FSTextConstructorImpl();
}
    
}
