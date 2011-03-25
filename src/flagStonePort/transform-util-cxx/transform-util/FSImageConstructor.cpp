/*
 * FSImageConstructor.cpp
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

#include "FSImageConstructor.h"

#include <stdio.h>
#include <transform/transform.h>
#include "FSCodec.h"

// BMP formats

#define BI_RGB 0
#define BI_RLE8 1
#define BI_RLE4 2
#define BI_BITFIELDS 3

// PNG Chunk types

#define CRITICAL_CHUNK 0x20000000
#define IHDR 0x49484452
#define PLTE 0x504c5445
#define IDAT 0x49444154
#define IEND 0x49454e44
#define tRNS 0x74524e53
#define bKGD 0x624b4744
#define cHRM 0x6348524d
#define fRAc 0x66524163
#define gAMA 0x67414d41
#define gIFg 0x67494667
#define gIFt 0x67494674
#define gIFx 0x67494678
#define hIST 0x68495354
#define iCCP 0x69434350
#define iTXt 0x69545874
#define oFFs 0x6f464673
#define pCAL 0x7043414c
#define pHYs 0x70485973
#define sBIT 0x73424954
#define sCAL 0x7343414c
#define sPLT 0x73504c54
#define sRGB 0x73524742
#define tEXt 0x74455874
#define tIME 0x74494d45
#define zTXt 0x7a545874

// PNG image types

#define GREYSCALE 0
#define TRUE_COLOUR 2
#define INDEXED_COLOUR 3
#define ALPHA_GREYSCALE 4
#define ALPHA_TRUECOLOUR 6

// PNG filter types

#define NO_FILTER 0
#define SUB_FILTER 1
#define UP_FILTER 2
#define AVG_FILTER 3
#define PAETH_FILTER 4

// PNG image attributes

#define BIT_DEPTH 0
#define COLOUR_COMPONENTS 1
#define COMPRESSION_METHOD 2

// BMP attributes

#define RED_MASK 4
#define GREEN_MASK 5
#define BLUE_MASK 6

// PNG attributes

#define COLOUR_TYPE 4
#define FILTER_METHOD 5
#define INTERLACE_METHOD 6
#define TRANSPARENT_GREY 7
#define TRANSPARENT_RED 8
#define TRANSPARENT_GREEN 9
#define TRANSPARENT_BLUE 10
        
using namespace transform;

namespace transform {

class FSImageConstructorImpl : public FSImageConstructor
{
public:
    FSImageConstructorImpl() 
        : format(NONE)
        , width(0)
        , height(0)
        , colourTable(NULL)
        , colourTableSize(0)
        , indexedImage(NULL)
        , colorImage(NULL)
        , jpegImage(NULL)
        , jpegImageSize(0)
        , chunkData(NULL)
        , chunkDataSize(0)
    {
        for (unsigned int i=0; i<16; i++) 
            attributes[i] = 0;
    }
    void operator delete(void* p)
    {
        ::operator delete(p);
    }
    void CALL destroy()
    {
        delete this;
    }
    int CALL setImageFromFile(const char* filename)
    {
        int status = TransformUtil::OK;

        FILE* input = 0;
        unsigned char* buffer = NULL;
        long length = 0;

        if ((input = fopen(filename, "rb")))
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
            status = setImage(buffer, (size_t)length);

        delete [] buffer;

        return status;
    }  
    int CALL setImage(const unsigned char* bytes, size_t size)
    {
        format = 0;
        width = 0;
        height = 0;
    
        attributes[BIT_DEPTH] = 0;
        attributes[COLOUR_COMPONENTS] = 0;
        attributes[COLOUR_TYPE] = 0;
        attributes[COMPRESSION_METHOD] = 0;
        attributes[FILTER_METHOD] = 0;
        attributes[INTERLACE_METHOD] = 0;

        attributes[TRANSPARENT_GREY] = -1;    
        attributes[TRANSPARENT_RED] = -1;
        attributes[TRANSPARENT_GREEN] = -1;
        attributes[TRANSPARENT_BLUE] = -1;

        attributes[RED_MASK] = 0;
        attributes[GREEN_MASK] = 0;
        attributes[BLUE_MASK] = 0;

        if (colourTable != NULL)
        {
            delete [] colourTable;
            colourTable = NULL;
        }
        colourTableSize = 0;

        if (indexedImage != NULL)
        {
            delete [] indexedImage;
            indexedImage = NULL;
        }

        if (colorImage != NULL)
        {
            delete [] colorImage;
            colorImage = NULL;
        }

        if (jpegImage != NULL)
        {
            delete [] jpegImage;
            jpegImage = NULL;
        }
        jpegImageSize = 0;
        
        if (chunkData != NULL)
        {
            delete [] chunkData;
            chunkData = new unsigned char[0];
        }
        chunkDataSize = 0;

        int status = TransformUtil::OK;
        int signature = ((bytes[0] & 0xFF) << 8) | (bytes[1] & 0xFF);

        switch (signature)
        {
            case 0xffd8: status = decodeJPEG(bytes, size); break;
            case 0x424d: status = decodeBMP(bytes, size); break;
            case 0x8950: status = decodePNG(bytes, size); break;
            default: 
                status = TransformUtil::FormatError;  
        }
        return status;
    }
    int CALL getFormat()
    {
        return format;
    }

    unsigned int CALL getWidth()
    {
        return width;
    }

    unsigned int CALL getHeight()
    {
        return height;
    }
    size_t CALL getColorTableSize()
    {
        return colourTableSize;
    }
    size_t CALL getColorTable(unsigned char* buffer)
    {
        size_t size = 0;
        
        if (colourTable != NULL)
        {
            memcpy(buffer, colourTable, colourTableSize*sizeof(unsigned char));
            size = colourTableSize;
        }
        return size;
    }
    size_t CALL getIndexedImage(unsigned char* buffer)
    {
        size_t numberOfBytes = 0;
        
        if (indexedImage != NULL)
        {
            numberOfBytes = height*width;
            memcpy(buffer, indexedImage, numberOfBytes*sizeof(unsigned char));
        }
        return numberOfBytes;
    }
    size_t CALL getColorImage(unsigned char* buffer)
    {
        size_t numberOfBytes = 0;
        
        if (colorImage != NULL)
        {
            numberOfBytes = height*width*4;
            memcpy(buffer, colorImage, numberOfBytes*sizeof(unsigned char));
        }
        return numberOfBytes;
    }
    size_t CALL getJPEGImageSize()
    {
        return jpegImageSize;
    }
    size_t CALL getJPEGImage(unsigned char* buffer)
    {
        size_t numberOfBytes = 0;
        
        if (jpegImage != NULL)
        {
            numberOfBytes = jpegImageSize;
            memcpy(buffer, jpegImage, jpegImageSize*sizeof(unsigned char));
        }
        return numberOfBytes;
    }
    void CALL setIndexedImage(int encoding, unsigned int imageWidth, unsigned int imageHeight, const unsigned char* table, size_t tableSize, const unsigned char* image)
    {
        format = encoding;
        width = imageWidth;
        height = imageHeight;
        
        delete [] colourTable;
        colourTableSize = tableSize;
        colourTable = new unsigned char[colourTableSize];
        memcpy(colourTable, table, tableSize*sizeof(unsigned char));

        delete [] indexedImage;
        indexedImage = new unsigned char[height*width];
        memcpy(indexedImage, image, sizeof(unsigned char)*height*width);
    }

    void CALL setColorImage(int encoding, unsigned int imageWidth, unsigned int imageHeight, const unsigned char* image)
    {
        format = encoding;
        width = imageWidth;
        height = imageHeight;
        
        delete [] colorImage;
        colorImage = new unsigned char[height*width*4];
        memcpy(colorImage, image, height*width*4*sizeof(unsigned char));
    }

    void CALL setJPEGImage(unsigned int imageWidth, unsigned int imageHeight, const unsigned char* image, size_t size)
    {
        format = JPEG;
        width = imageWidth;
        height = imageHeight;
        
        delete [] jpegImage;
        jpegImageSize = size;
        jpegImage = new unsigned char[jpegImageSize];
        memcpy(jpegImage, image, jpegImageSize*sizeof(unsigned char));
    }
    FSDefineObject* CALL defineImage(int identifier)
    {
        FSDefineObject* object = NULL;
        unsigned char* table = NULL;

        unsigned char* image = NULL;
        size_t imageSize = NULL;
 
        unsigned char* compressedImage = NULL;
        size_t compressedImageSize = 0;
        
        switch (format)
        {
            case JPEG:
                image = new unsigned char[jpegImageSize];
                memcpy(image, jpegImage, jpegImageSize*sizeof(unsigned char));
                object = new FSDefineJPEGImage2(identifier, image, jpegImageSize); 
                break;
            case IDX8:
                image = getImage(imageSize);
                compressedImage = zip(image, imageSize, 0, compressedImageSize);
                object = new FSDefineImage(identifier, width, height, (int)colourTableSize/4, compressedImage, compressedImageSize); 
                delete [] image;
                break;
            case IDXA: 
                image = getImage(imageSize);
                compressedImage = zip(image, imageSize, 0, compressedImageSize);
                object = new FSDefineImage2(identifier, width, height, (int)colourTableSize/4, compressedImage, compressedImageSize); 
                delete [] image;
                break;
            case RGB5:
                image = getImage(imageSize);
                compressedImage = zip(image, imageSize, 0, compressedImageSize);
                object = new FSDefineImage(identifier, width, height, compressedImage, compressedImageSize, 16);
                delete [] image;
                break;
            case RGB8: 
                image = getImage(imageSize);
                compressedImage = zip(image, imageSize, 0, compressedImageSize);
                object = new FSDefineImage(identifier, width, height, compressedImage, compressedImageSize, 24); 
                delete [] image;
                break;
            case RGBA: 
                image = getImage(imageSize);
                compressedImage = zip(image, imageSize, 0, compressedImageSize);
                object = new FSDefineImage2(identifier, width, height, compressedImage, compressedImageSize); 
                delete [] image;
                break;
        }
        return object;
    }
    FSDefineShape3* CALL defineShape(int shapeIdentifier, int imageIdentifier, int xOrigin, int yOrigin, int borderWidth, const FSColor* borderColor)
    {
        FSVector<FSLineStyle*> lineStyles;
        FSVector<FSFillStyle*> fillStyles;

        int lineWidth = borderWidth / 2;
        
        if (lineWidth != 0)
            lineStyles.push_back(new FSSolidLine(borderWidth, FSColor(*borderColor)));
        
        FSBounds bounds(-(xOrigin*20)-lineWidth, -(yOrigin*20)-lineWidth, (width-xOrigin)*20+lineWidth, (height-yOrigin)*20+lineWidth);

        fillStyles.push_back(new FSBitmapFill(FSFillStyle::ClippedBitmap, imageIdentifier, FSCoordTransform(-xOrigin*20, -yOrigin*20, 20.0, 20.0)));

        FSShape shape;

        int rectWidth = width*20;
        int rectHeight = height*20;
    
        shape.add(new FSShapeStyle((lineStyles.size() > 0) ? 1 : 0, 1, 0, -xOrigin*20, -yOrigin*20));
        shape.add(new FSLine(rectWidth, 0));
        shape.add(new FSLine(0, rectHeight));
        shape.add(new FSLine(-rectWidth, 0));
        shape.add(new FSLine(0, -rectHeight));
        shape.add(new FSLine(rectWidth, 0));
        
        return new FSDefineShape3(shapeIdentifier, bounds, fillStyles, lineStyles, shape);
    }

private:    
    int Paeth(int L, int u, int nw)
    {
        int a = 0xFF & L;
        int b = 0xFF & u; 
        int c = 0xFF & nw; 
        int p = a + b - c;
        int pa = p - a; if (pa < 0) pa = -pa;
        int pb = p - b; if (pb < 0) pb = -pb; 
        int pc = p - c; if (pc < 0) pc = -pc; 
        if (pa <= pb && pa <= pc) return a;
        if (pb <= pc) return b;
        return c;
    }

    int CALL decodeJPEG(const unsigned char* bytes, size_t size)
    {
        int status = TransformUtil::OK;

        format = JPEG;

        jpegImageSize = size;
        jpegImage = new unsigned char[jpegImageSize];
        memcpy(jpegImage, bytes, size*sizeof(unsigned char));

        FSCodec* coder = Codec(FSCodec::BigEndian);
        coder->setData(jpegImage, jpegImageSize);
                 
        if (coder->readShort() != 0xffd8)
            return TransformUtil::FormatError;

        while (true) 
        {
            int marker = coder->readShort();
            int size = coder->readShort();
            
            if ((marker & 0xff00) != 0xff00)
            {
                status = TransformUtil::FormatError;
                break;
            }
            
            if (marker >= 0xffc0 && marker <= 0xffcf && marker != 0xffc4 && marker != 0xffc8) 
            {
                coder->readByte();
                height = coder->readShort();
                width = coder->readShort();
                break;
            } 
            else 
            {
                coder->adjustPointer((size - 2) << 3);
            }
        }
        delete coder;

        return status;
    }
    int CALL decodeBMP(const unsigned char* bytes, size_t size)
    {
        FSCodec* coder = Codec(FSCodec::LittleEndian);
        coder->setData(bytes, size);
        
        if (coder->readByte() != bmpSignature[0] || coder->readByte() != bmpSignature[1])
            return TransformUtil::FormatError;

        int fileSize = coder->readInt();
        int reserved = coder->readInt();
        int offset = coder->readInt();
        int headerSize = coder->readInt();
        
        int bitPlanes = 0;
        int bitsPerPixel = 0;
        int imageSize = 0;
        int horizontalResolution = 0;
        int verticalResolution = 0;
        int coloursUsed = 0;
        int importantColours = 0;

        switch (headerSize)
        {
            case 12:
                width = coder->readShort();
                height = coder->readShort();
                bitPlanes = coder->readShort();
                bitsPerPixel = coder->readShort();
                break;
            case 40:
                width = coder->readInt();
                height = coder->readInt();
                bitPlanes = coder->readShort();
                bitsPerPixel = coder->readShort();
                attributes[COMPRESSION_METHOD] = coder->readInt();
                imageSize = coder->readInt();
                horizontalResolution = coder->readInt();
                verticalResolution = coder->readInt();
                coloursUsed = coder->readInt();
                importantColours = coder->readInt();
                break;
            default:
                break;
        }
        
        if (attributes[COMPRESSION_METHOD] == BI_BITFIELDS)
        {
            attributes[RED_MASK] = coder->readInt();
            attributes[GREEN_MASK] = coder->readInt();
            attributes[BLUE_MASK] = coder->readInt();
        }
        
        switch (bitsPerPixel)
        {
            case 1: format = IDX8; attributes[BIT_DEPTH] = 1; attributes[COLOUR_COMPONENTS] = 1; break;
            case 2: format = IDX8; attributes[BIT_DEPTH] = 2; attributes[COLOUR_COMPONENTS] = 1; break;
            case 4: format = IDX8; attributes[BIT_DEPTH] = 4; attributes[COLOUR_COMPONENTS] = 1; break;
            case 8: format = IDX8; attributes[BIT_DEPTH] = 8; attributes[COLOUR_COMPONENTS] = 1; break;
            case 16: format = RGB5; attributes[BIT_DEPTH] = 5; attributes[COLOUR_COMPONENTS] = 3; break;
            case 24: format = RGB8; attributes[BIT_DEPTH] = 8; attributes[COLOUR_COMPONENTS] = 3; break;
            case 32: format = RGBA; attributes[BIT_DEPTH] = 8; attributes[COLOUR_COMPONENTS] = 4; break;
        }
        
        if (format == IDX8) 
        {
            int tableIndex = 0;

            coloursUsed = 1 << bitsPerPixel;
            colourTableSize = coloursUsed*4;
            colourTable = new unsigned char[colourTableSize];
            indexedImage = new unsigned char[height*width];

            if (headerSize == 12)
            {
                for (int i=0; i<coloursUsed; i++) 
                {
                    tableIndex = i*4;

                    colourTable[tableIndex+3] = (byte)0xFF;
                    colourTable[tableIndex] = coder->readByte();
                    colourTable[tableIndex+1] = coder->readByte();
                    colourTable[tableIndex+2] = coder->readByte();
                }
            }
            else
            {
                for (int i=0; i<coloursUsed; i++)
                {
                    tableIndex = i*4;

                    colourTable[tableIndex+2] = coder->readByte();
                    colourTable[tableIndex+1] = coder->readByte();
                    colourTable[tableIndex+0] = coder->readByte();
                    colourTable[tableIndex+3] = (byte) (coder->readByte() | 0xFF);
                }
            }
                
            coder->setPointer(offset<<3);

            switch (attributes[COMPRESSION_METHOD])
            {
                case BI_RGB:  decodeIDX8(coder); break;
                case BI_RLE8: decodeRLE8(coder); break;
                case BI_RLE4: decodeRLE4(coder); break;
            }
        }
        else
        {
            colorImage = new unsigned char[height*width*4];

            coder->setPointer(offset<<3);

            switch (format)
            {
                case RGB5: decodeRGB5(coder); break;
                case RGB8: decodeRGB8(coder); break;
                case RGBA: decodeRGBA(coder); break;
            }
        }
        return TransformUtil::OK;
    }
    int CALL decodePNG(const unsigned char* bytes, size_t size)
    {
        FSCodec* coder = Codec(FSCodec::BigEndian);
        coder->setData(bytes, size);

        int status = TransformUtil::OK;

        int length = 0;
        int chunkType = 0;
        bool moreChunks = true;

        for (int i=0; i<8; i++)
        {
            if (coder->readByte() != pngSignature[i])
                status = TransformUtil::FormatError;
        }

        if (status != TransformUtil::OK)
            return status;
        
        while (moreChunks)
        {
            length = coder->readInt();
            chunkType = coder->readInt();
            
            int current = coder->getPointer();
            int next = current + ((length+4) << 3);
            
            switch (chunkType)
            {
                case IHDR: decodeIHDR(coder, length); break;
                case PLTE: decodePLTE(coder, length); break;
                case tRNS: decodeTRNS(coder, length); break;
                case IDAT: decodeIDAT(coder, length); break;
                case IEND: moreChunks = false; coder->adjustPointer(32); break;
                default:
                    coder->adjustPointer((length+4) << 3);
                    break;
            }         
            length += 4; // include CRC at end of chunk

#ifdef _DEBUG
            int bytesRead = (coder->getPointer() - current) >> 3;
                
            char chars[4];
            
            chars[3] = chunkType;
            chars[2] = chunkType >> 8;
            chars[1] = chunkType >> 16;
            chars[0] = chunkType >> 24;
            
            if (bytesRead < length)
                printf("%s chunk underflowed by %d bytes.", chars, length - bytesRead);
            else if (bytesRead > length)
                printf("%s chunk overflowed by %d bytes.", chars, bytesRead - length);
#endif // _DEBUG
            coder->setPointer(next);
            
            if (coder->eof())
                moreChunks = false;
        } 

        // Decode Image 

        switch (attributes[COLOUR_TYPE])
        {
            case GREYSCALE: format = (attributes[TRANSPARENT_GREY] != -1) ? RGBA : RGB8; attributes[COLOUR_COMPONENTS] = 1; break;
            case TRUE_COLOUR: format = (attributes[TRANSPARENT_RED] != -1) ? RGBA : RGB8; attributes[COLOUR_COMPONENTS] = 3; break;
            case INDEXED_COLOUR: format = IDX8; attributes[COLOUR_COMPONENTS] = 1; break;
            case ALPHA_GREYSCALE: format = RGBA; attributes[COLOUR_COMPONENTS] = 2; break;
            case ALPHA_TRUECOLOUR: format = RGBA; attributes[COLOUR_COMPONENTS] = 4; break;
        }
        
        if (format == RGB8 && attributes[BIT_DEPTH] <= 5)
            format = RGB5;

        if (format == RGB5 || format == RGB8 || format == RGBA)
            colorImage = new unsigned char[height*width*4];
            
        if (format == IDX8 || format == IDXA)
            indexedImage = new unsigned char[height*width];

        size_t encodedImageSize = width*height*32;

        unsigned char* encodedImage = unzip(chunkData, chunkDataSize, encodedImageSize);
            
        unsigned int bitsPerPixel = attributes[BIT_DEPTH]*attributes[COLOUR_COMPONENTS];
        int bitsPerRow = width * bitsPerPixel;
        int rowWidth = (bitsPerRow % 8 > 0) ? (bitsPerRow/8)+1 : (bitsPerRow/8);
        unsigned int bytesPerPixel = (bitsPerPixel<8) ? 1 : bitsPerPixel/8;
        
        unsigned char* current = new unsigned char[rowWidth];
        unsigned char* previous = new unsigned char[rowWidth];
        
        for (int i=0; i<rowWidth; i++)
            previous[i] = 0;
            
        int rowStart = 0;
        int rowInc = 0;
        int colStart = 0;
        int colInc = 0;
        
        unsigned int imageIndex = 0;
        int pixelCount = 0;
        
        unsigned int row = 0;
        unsigned int col = 0;
        int filter = 0;
        
        int scanBits = 0;
        unsigned int scanLength = 0;
        
        int numberOfPasses = (attributes[INTERLACE_METHOD] == 1) ? 7 : 1;

        unsigned int xc = 0;
        unsigned int xp = 0;

        for (int pass=0; pass<numberOfPasses; pass++)
        {
            rowStart = (attributes[INTERLACE_METHOD] == 1) ? startRow[pass] : 0;
            rowInc = (attributes[INTERLACE_METHOD] == 1) ? rowIncrement[pass] : 1;
            
            colStart = (attributes[INTERLACE_METHOD] == 1) ? startColumn[pass] : 0;
            colInc = (attributes[INTERLACE_METHOD] == 1) ? columnIncrement[pass] : 1;
            
            for (row=rowStart; row<height && imageIndex<encodedImageSize; row+=rowInc)
            {
                for (col=colStart, pixelCount=0, scanBits=0; col<width; pixelCount++, col += colInc, scanBits+=bitsPerPixel);

                scanLength = (scanBits%8 > 0) ? (scanBits/8)+1 : (scanBits/8);

                filter = encodedImage[imageIndex++];
                              
                for (unsigned int i=0; i<scanLength; i++, imageIndex++)
                    current[i] = (imageIndex < encodedImageSize) ? encodedImage[imageIndex] : previous[i];

                switch (filter) 
                {
                    case NO_FILTER:
                        break;
                    case SUB_FILTER:
                        for (xc = bytesPerPixel, xp = 0; xc < scanLength; xc++, xp++)
                            current[xc] = (byte)(current[xc] + current[xp]);
                        break;
                    case UP_FILTER:
                        for (xc = 0; xc < scanLength; xc++)
                            current[xc] = (byte)(current[xc] + previous[xc]);
                        break;
                    case AVG_FILTER:
                        for (xc = 0; xc < bytesPerPixel; xc++)
                            current[xc] = (byte)(current[xc] + (0 + (0xFF & previous[xc])) / 2);
                        
                        for (xc = bytesPerPixel, xp = 0; xc < scanLength; xc++, xp++)
                            current[xc] = (byte)(current[xc] + ((0xFF & current[xp]) + (0xFF & previous[xc])) / 2);
                        break;
                    case PAETH_FILTER:
                        for (xc = 0; xc < bytesPerPixel; xc++)
                            current[xc] = (byte)(current[xc] + Paeth((byte)0, previous[xc], (byte)0));
                        
                        for (xc = bytesPerPixel, xp = 0; xc < scanLength; xc++, xp++)
                            current[xc] = (byte)(current[xc] + Paeth(current[xp], previous[xc], previous[xp]));
                        break;
                }
        
                memcpy(previous, current, scanLength);
                        
                FSCodec* coder = Codec(FSCodec::BigEndian);
                coder->setData(current, scanLength);
                
                for (col=colStart; col<width; col+=colInc)
                {
                    switch (attributes[COLOUR_TYPE])
                    {
                        case GREYSCALE: decodeGreyscale(coder, row, col); break;
                        case TRUE_COLOUR: decodeTrueColour(coder, row, col); break;
                        case INDEXED_COLOUR: decodeIndexedColour(coder, row, col); break;
                        case ALPHA_GREYSCALE: decodeAlphaGreyscale(coder, row, col); break;
                        case ALPHA_TRUECOLOUR: decodeAlphaTrueColour(coder, row, col); break;
                    }        
                }

                delete coder;
            }
        }
        delete [] encodedImage;
        delete [] current;
        delete [] previous;
        delete coder;

        return status;
    }

    void CALL decodeIDX8(FSCodec* coder)
    {
        unsigned int h = 0;
        unsigned int w = 0;
        int bitsRead = 0;
        int offset = 0;
        
        for (h=height-1; h>0; h--)
        {
            offset = h*width;

            for (w=0, bitsRead=0; w<width; w++)
            {
                indexedImage[offset++] = (byte)coder->readBits(attributes[BIT_DEPTH]);
                bitsRead += attributes[BIT_DEPTH];
            }
            if (bitsRead % 32 > 0)
                coder->adjustPointer(32 - (bitsRead % 32));
        }
    }
    void CALL decodeRLE4(FSCodec* coder)
    {
        unsigned int row = height-1;
        unsigned int col = 0;
        
        bool containsMorePixels = true;

        while (containsMorePixels) 
        {       
            unsigned int count = coder->readByte();
        
            if (count == 0)
            {
                int code = coder->readByte();
                
                switch (code)
                {
                    case 0: 
                        col = 0; 
                        row--; 
                        break;
                    case 1: 
                        containsMorePixels = false; 
                        break;
                    case 2: 
                        col += coder->readShort();
                        row -= coder->readShort();
                    default:
                        for (int i=0; i<code; i+=2)
                        {
                            indexedImage[row*width+col++] = (byte) coder->readBits(4);
                            indexedImage[row*width+col++] = (byte) coder->readBits(4);
                        }
                        
                        if ((code & 2) == 2) coder->readByte();
                        break;
                }
            }
            else
            {
                char indexA = (byte)coder->readBits(4);
                char indexB = (byte)coder->readBits(4);
                
                for (unsigned int i=0; i<count && col < width; i++) 
                    indexedImage[row*width+col++] = (i % 2 > 0) ? indexB : indexA;
            }
        }
    }    
    void CALL decodeRLE8(FSCodec* coder)
    {
        int row = height-1;
        int col = 0;
        
        bool containsMorePixels = true;

        while (containsMorePixels) 
        {       
            int count = coder->readByte();
        
            if (count == 0)
            {
                int code = coder->readByte();
                
                switch (code)
                {
                    case 0: 
                        col = 0; 
                        row--; 
                        break;
                    case 1: 
                        containsMorePixels = false; 
                        break;
                    case 2: 
                        col += coder->readShort();
                        row -= coder->readShort();
                    default:
                        for (int i=0; i<code; i++)
                            indexedImage[row*width+col++] = coder->readByte();
                        
                        if ((code & 1) == 1) coder->readByte();
                        break;
                }
            }
            else
            {
                char index = (byte)coder->readByte();
                
                for (int i=0; i<count; i++) 
                    indexedImage[row*width+col++] = index;
            }
        }
    }
    void CALL decodeRGB5(FSCodec* coder)
    {
        unsigned int h = 0;
        unsigned int w = 0;
        int bitsRead = 0;
        
        if (attributes[COMPRESSION_METHOD] == BI_RGB)
        {
            for (h=height-1; h>0; h--)
            {
                for (w=0, bitsRead=0; w<width; w++)
                {                
                    int colour = coder->readShort() & 0xFFFF;
                    
                    colorImage[h*width*4+w*4+0] = (byte)((colour & 0x7C00) >> 7);
                    colorImage[h*width*4+w*4+1] = (byte)((colour & 0x03E0) >> 2);
                    colorImage[h*width*4+w*4+2] = (byte)((colour & 0x001F) << 3);
                    colorImage[h*width*4+w*4+3] = (byte)0xFF;

                    bitsRead += 16;
                }
                if (bitsRead % 32 > 0)
                    coder->adjustPointer(32 - (bitsRead % 32));
            }
        }
        else
        {
            for (h=height-1; h>0; h--)
            {
                for (w=0, bitsRead=0; w<width; w++)
                {
                    int colour = coder->readShort() & 0xFFFF;
                    
                    if (attributes[RED_MASK] == 0x7C00 && attributes[GREEN_MASK] == 0x03E0 && attributes[BLUE_MASK] == 0x001F)
                    {
                        colorImage[h*width*4+w*4+0] = (byte)((colour & 0x7C00) >> 7);
                        colorImage[h*width*4+w*4+1] = (byte)((colour & 0x03E0) >> 2);
                        colorImage[h*width*4+w*4+2] = (byte)((colour & 0x001F) << 3);
                        colorImage[h*width*4+w*4+3] = (byte)0xFF;
                    }
                    else if (attributes[RED_MASK] == 0xF800 && attributes[GREEN_MASK] == 0x07E0 && attributes[BLUE_MASK] == 0x001F)
                    {
                        colorImage[h*width*4+w*4+0] = (byte)((colour & 0xF800) >> 8);
                        colorImage[h*width*4+w*4+1] = (byte)((colour & 0x07E0) >> 3);
                        colorImage[h*width*4+w*4+2] = (byte)((colour & 0x001F) << 3);
                        colorImage[h*width*4+w*4+3] = (byte)0xFF;
                    }
                    bitsRead += 16;
                }
                if (bitsRead % 32 > 0)
                    coder->adjustPointer(32 - (bitsRead % 32));
            }
        }
        
    }
    void CALL decodeRGB8(FSCodec* coder)
    {
        unsigned int h = 0;
        unsigned int w = 0;
        int bitsRead = 0;
        
        for (h=height-1; h>0; h--)
        {
            for (w=0, bitsRead=0; w<width; w++)
            {
                colorImage[h*width*4+w*4+0] = (byte)coder->readBits(attributes[BIT_DEPTH]);
                colorImage[h*width*4+w*4+1] = (byte)coder->readBits(attributes[BIT_DEPTH]);
                colorImage[h*width*4+w*4+2] = (byte)coder->readBits(attributes[BIT_DEPTH]);
                colorImage[h*width*4+w*4+3] = (byte)0xFF;
                
                bitsRead += 24;
            }
            if (bitsRead % 32 > 0)
                coder->adjustPointer(32 - (bitsRead % 32));
        }
    }
    void CALL decodeRGBA(FSCodec* coder)
    {
        unsigned int h = 0;
        unsigned int w = 0;
        
        for (h=height-1; h>0; h--)
        {
            for (w=0; w<width; w++)
            {
                colorImage[h*width*4+w*4+2] = (byte)coder->readByte();
                colorImage[h*width*4+w*4+1] = (byte)coder->readByte();
                colorImage[h*width*4+w*4+0] = (byte)coder->readByte();
                colorImage[h*width*4+w*4+3] = (byte)coder->readByte();
                colorImage[h*width*4+w*4+3] = (byte)0xFF;
            }
        }
    }

    void CALL decodeIHDR(FSCodec* coder, int length)
    {
        width = coder->readInt();
        height = coder->readInt();
        attributes[BIT_DEPTH] = coder->readByte();
        attributes[COLOUR_TYPE] = coder->readByte();
        attributes[COMPRESSION_METHOD] = coder->readByte();
        attributes[FILTER_METHOD] = coder->readByte();
        attributes[INTERLACE_METHOD] = coder->readByte();
        
        coder->readInt(); // crc
    }
    void CALL decodePLTE(FSCodec* coder, int length)
    {
        if (attributes[COLOUR_TYPE] == 3)
        {
            int paletteSize = length / 3;
            
            colourTable = new unsigned char[paletteSize*4];
            colourTableSize = paletteSize*4;
            
            for (int i=0; i<paletteSize; i++)
            {
                colourTable[i*4+3] = (byte)0xFF;
                colourTable[i*4+2] = (byte)coder->readByte();
                colourTable[i*4+1] = (byte)coder->readByte();
                colourTable[i*4+0] = (byte)coder->readByte();
            }
        }
        else
        {
            coder->adjustPointer(length << 3);
        }        
        coder->readInt(); // crc
    }
    void CALL decodeTRNS(FSCodec* coder, int length)
    {
        switch(attributes[COLOUR_TYPE])
        {
            case GREYSCALE:
                attributes[TRANSPARENT_GREY] = coder->readShort();
                break;
            case TRUE_COLOUR:
                attributes[TRANSPARENT_RED] = coder->readShort();
                attributes[TRANSPARENT_GREEN] = coder->readShort();
                attributes[TRANSPARENT_BLUE] = coder->readShort();
                break;
            case INDEXED_COLOUR:
                for (int i=0; i<length; i+=4)
                    colourTable[i+3] = (byte)coder->readByte();
                break;
            default:
                break;
        }
        coder->readInt(); // crc
    }
    void CALL decodeIDAT(FSCodec* coder, int length)
    {
        size_t currentLength = chunkDataSize;
        size_t newLength = currentLength + length;
        
        unsigned char* data = new unsigned char[newLength];
        memcpy(data, chunkData, currentLength*sizeof(unsigned char));

        for (size_t i=currentLength; i<newLength; i++)
            data[i] = coder->readByte();
            
        chunkData = data;
        chunkDataSize = newLength;
        
        coder->readInt(); // crc
    }

    void decodeGreyscale(FSCodec* coder, int row, int col)
    {
        int pixel = 0;
        byte colour = 0;
        
        switch (attributes[BIT_DEPTH])
        {
            case 1:  pixel = coder->readBits(1); colour = (byte) monochrome[pixel]; break;
            case 2:  pixel = coder->readBits(2); colour = (byte) greyscale2[pixel]; break;
            case 4:  pixel = coder->readBits(4); colour = (byte) greyscale4[pixel]; break;
            case 8:  pixel = coder->readByte(); colour = (byte) pixel; break;
            case 16: pixel = coder->readShort(); colour = (byte) (pixel >> 8); break;
        }                    

        colorImage[row*width*4+col*4+0] = colour;
        colorImage[row*width*4+col*4+1] = colour;
        colorImage[row*width*4+col*4+2] = colour;
        colorImage[row*width*4+col*4+3] = (byte)attributes[TRANSPARENT_GREY];
    }   
    void decodeTrueColour(FSCodec* coder, int row, int col)
    {
        int pixel = 0;
        byte colour = 0;
        
        for (int i=0; i<attributes[COLOUR_COMPONENTS]; i++)
        {
            switch (attributes[BIT_DEPTH])
            {
                case 8:  pixel = coder->readByte(); colour = (byte) pixel; break;
                case 16: pixel = coder->readShort(); colour = (byte) (pixel >> 8); break;
            }                    
            colorImage[row*width*4+col*4+i] = colour;
        }
        colorImage[row*width*4+col*4+3] = (byte)attributes[TRANSPARENT_RED];
    }   
    void decodeIndexedColour(FSCodec* coder, int row, int col)
    {
        int index = 0;
        
        switch (attributes[BIT_DEPTH])
        {
            case 1:  index = coder->readBits(1); break;
            case 2:  index = coder->readBits(2); break;
            case 4:  index = coder->readBits(4); break;
            case 8:  index = coder->readByte(); break;
            case 16: index = coder->readShort(); break;
        }                    
        indexedImage[row*width+col] = (byte)index;
    }   
    void decodeAlphaGreyscale(FSCodec* coder, int row, int col)
    {
        int pixel = 0;
        byte colour = 0;
        int alpha = 0;
        
        switch (attributes[BIT_DEPTH])
        {
            case 1:  pixel = coder->readBits(1); colour = (byte) monochrome[pixel]; alpha = coder->readBits(1); break;
            case 2:  pixel = coder->readBits(2); colour = (byte) greyscale2[pixel]; alpha = coder->readBits(2); break;
            case 4:  pixel = coder->readBits(4); colour = (byte) greyscale4[pixel]; alpha = coder->readBits(4); break;
            case 8:  pixel = coder->readByte(); colour = (byte) pixel; alpha = coder->readByte(); break;
            case 16: pixel = coder->readShort(); colour = (byte) (pixel >> 8); alpha = coder->readShort() >> 8; break;
        }                    

        colorImage[row*width*4+col*4+0] = colour;
        colorImage[row*width*4+col*4+1] = colour;
        colorImage[row*width*4+col*4+2] = colour;
        colorImage[row*width*4+col*4+3] = (byte) alpha;
    }  
    void CALL decodeAlphaTrueColour(FSCodec* coder, int row, int col)
    {
        int pixel = 0;
        byte colour = 0;
        
        for (int i=0; i<attributes[COLOUR_COMPONENTS]; i++)
        {
            switch (attributes[BIT_DEPTH])
            {
                case 8:  pixel = coder->readByte(); colour = (byte) pixel; break;
                case 16: pixel = coder->readShort(); colour = (byte) (pixel >> 8); break;
            }                    
            colorImage[row*width*4+col*4+i] = colour;
        }
    }

    unsigned char* CALL getImage(size_t& size)
    {
        unsigned int row = 0;
        unsigned int col = 0;
        unsigned int index = 0;
        unsigned int scanLength = 0;
        unsigned int bytesPerColor = 0;

        unsigned char* formattedImage = NULL;
        unsigned char* src = NULL;
        unsigned char* dst = NULL;

        switch (format)
        {
            case IDX8:
            case IDXA: 
                bytesPerColor = (format == IDXA) ? 4 : 3;
                
                scanLength = (width + 3) & ~3;
                size = (colourTableSize/4)*bytesPerColor + scanLength*height;
                formattedImage = new unsigned char[size];

                src = indexedImage;
                dst = formattedImage;

                for (unsigned int i=0; i<colourTableSize; i+=4)
                {
                    *dst++ = colourTable[i]; // R
                    *dst++ = colourTable[i+1]; // G
                    *dst++ = colourTable[i+2]; // B
                    
                    if (format == IDXA)
                        *dst++ = colourTable[i+3]; // A
                }

                for (row=0; row<height; row++)
                {
                    memcpy(dst, src, width);
                    memset(dst+width, 0, scanLength-width);

                    dst += scanLength;
                    src += width;
                }
                break;
            case RGB5: 
                scanLength = width + (width & 1);
                size = scanLength*height*2;
                formattedImage = new unsigned char[size];

                src = colorImage;
                dst = formattedImage;

                for (row=0; row<height; row++)
                {
                    for (col=0; col<width; col++, src+=4)
                    {
                        unsigned int red = (*src & 0xF8) << 7;
                        unsigned int green = (*(src+1) & 0xF8) << 2;
                        unsigned int blue = (*(src+2) & 0xF8) >> 3;
                        unsigned int colour = (red | green | blue) & 0x7FFF;
                        
                        *dst++ = (colour >> 8);
                        *dst++ = colour;
                    }

                    memset(dst, 0, (scanLength-width)*2);
                    dst += (scanLength-width)*2;
                }
                break;
            case RGB8: 
                size = width*height*4;
                formattedImage = new unsigned char[size];

                src = colorImage;
                dst = formattedImage;

                for (row=0; row<height; row++)
                {
                    for (col=0; col<width; col++, src+=4)
                    {
                        *dst++ = (byte)0xFF;
                        *dst++ = *src;
                        *dst++ = *(src+1);
                        *dst++ = *(src+2);
                    }
                }
                break;
            case RGBA: 
                size = width*height*4;
                formattedImage = new unsigned char[size];

                src = colorImage;
                dst = formattedImage;

                for (row=0; row<height; row++)
                {
                    for (col=0; col<width; col++, src+=4)
                    {
                        *dst++ = *(src+3);
                        *dst++ = *(src+0);
                        *dst++ = *(src+1);
                        *dst++ = *(src+2);
                    }
                }
                break;
        }
        return formattedImage;
    }   


    static const int monochrome[2];
    static const int greyscale2[4];
    static const int greyscale4[16];
    
    static const int bmpSignature[2];
    static const int pngSignature[8];
    
    static const int startRow[7];
    static const int startColumn[7];
    static const int rowIncrement[7];
    static const int columnIncrement[7];
        
    int format;

    unsigned int width;
    unsigned int height;

    unsigned char* colourTable;
    size_t colourTableSize;

    unsigned char* indexedImage;
    unsigned char* colorImage;

    unsigned char* jpegImage;
    size_t jpegImageSize;
    
    unsigned char* chunkData;
    size_t chunkDataSize;

    int attributes[16];
};
    
const int FSImageConstructorImpl::monochrome[2] = { 0, 255 };
const int FSImageConstructorImpl::greyscale2[4] = { 0, 85, 170, 255 };
const int FSImageConstructorImpl::greyscale4[16] = { 0, 17, 34, 51, 68, 85, 102, 119, 136, 153, 170, 187, 204, 221, 238, 255 };

const int FSImageConstructorImpl::bmpSignature[2] = { 66, 77 };

const int FSImageConstructorImpl::pngSignature[8] = { 137, 80, 78, 71, 13, 10, 26, 10 };

const int FSImageConstructorImpl::startRow[7] =        { 0, 0, 4, 0, 2, 0, 1 };
const int FSImageConstructorImpl::startColumn[7] =     { 0, 4, 0, 2, 0, 1, 0 };
const int FSImageConstructorImpl::rowIncrement[7] =    { 8, 8, 8, 4, 4, 2, 2 };
const int FSImageConstructorImpl::columnIncrement[7] = { 8, 8, 4, 4, 2, 2, 1 };

extern "C" FSImageConstructor* ImageConstructor()
{
    return new FSImageConstructorImpl();
}
}
