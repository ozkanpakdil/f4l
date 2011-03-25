/*
 * FSImageConstructor.h
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

#ifndef __FSImageConstructor_h__
#define __FSImageConstructor_h__ 1

#include "FSTransformUtil.h"

using namespace transform;

namespace transform
{
    class FSColor;
    class FSDefineObject;
    class FSDefineShape3;
/**
 * The FSImageConstructor class is used to generate an image definition object from an image stored
 * in a file. Currently PNG, BMP and JPEG encoded images are supported. FSImageConstructor objects 
 * are generated using the global function ImageConstructor():</p>
 *
 * <pre>
 *     FSImageConstructor* imageConstructor = ImageConstructor();
 * </pre>
 *
 * A single FSImageConstructor object can also be used to load a series of images:
 *
 * <pre>
 *     status = imageConstructor->setImageFromFile(imageFile);
 * </pre>
 *
 * The method returns a status code indicating whether the object was initialized cirrectly,
 * either TransformUtil::OK, TransformUtil::FileNotFound, TransformUtil::ReadError or
 * TransformUtil::FormatError.
 *
 * \verbatim
 * if ((status = imageGenerator->setImageFromFile(image.c_str())) != TransformUtil::OK)
 * {
 *     switch (status)
 *     {
 *         case TransformUtil::FileNotFound:
 *             cerr << "Could not find sound file" << endl; break;
 *         case TransformUtil::ReadError:
 *             cerr << "Could not read sound file" << endl; break;
 *         case TransformUtil::FormatError:
 *             cerr << "Could not read sound file" << endl; break;
 *     }
 * }
 * \endverbatim
 *
 * <P>When an image is loaded the getFormat() method identifies the way the image is encoded:</P>
 *
 * <table>
 * <tr><th>Format</th><th>Description</th></tr>
 *
 * <tr>
 * <td>JPEG</td>
 * <td>A JPEG encoded image.</td>
 * </tr>
 *
 * <tr>
 * <td>IDX8</td>
 * <td>An indexed image where each pixel specifies an index into a colour table containing up to 
 * 256, 24-bit colours. Transparent colours are not supported.</td>
 * </tr>
 *
 * <tr>
 * <td>IDXA</td>
 * <td>An indexed image where each pixel specifies an index into a colour table containing up to 
 * 256, 32-bit colours - 8-bits for each colour channel and 8-bits for transparency.</td>
 * </tr>
 *
 * <tr>
 * <td>RGB5</td>
 * <td>An true colour image where each pixel specifies a 16-bit colour, with 5-bits per colour
 * channel. Transparent colours are not supported.</td>
 * </tr>
 *
 * <tr>
 * <td>RGB8</td>
 * <td>An true colour image where each pixel specifies a 24-bit colour, with 8-bits per colour
 * channel. Each pixel occupies 32-bits. Transparent colours are not supported so the byte 
 * containing the alpha channel is set to 255 by default.</td>
 * </tr>
 *
 * <tr>
 * <td>RGBA</td>
 * <td>An true colour image where each pixel specifies a 32-bit colour, with 8-bits per colour
 * channel and 8-bits for transparency. The 32-bit word contains colour information for the 
 * red, green, blue and alpha channels respectively.</td>
 * </tr>
 *
 * </table>
 *
 * <P>Once an image is loaded the definition required to add the image to a Flash file is 
 * generated using the defineImage() method:</p>
 *
 * <pre>
 *     movie.add(imageConstructor->defineImage(movie.newIdentifier()));
 * </pre>
 *
 * <P>The defineImage() method returns an FSDefineObject (the abstract base class for all objects used 
 * to define shapes etc. in a Flash file. The exact class of the object generated depends of the format 
 * of the image loaded.</P>
 *
 * <table>
 * <tr><th>Class</th><th>Generated when...</th></tr>
 *
 * <tr>
 * <td>FSDefineJPEGImage2</td>
 * <td>the image contains JPEG encoded data.</td>
 * </tr>
 *
 * <tr>
 * <td>FSDefineImage</td>
 * <td>an indexed BMP or PNG image contains a colour table without transparent colours or 
 * when a true colour image contains 16-bit or 24-bit colours is loaded. The getFormat() method returns 
 * the class constants IDX8, RGB5 or RGB8.</td>
 * </tr>
 *
 * <tr>
 * <td>FSDefineImage2</td>
 * <td>A BMP or PNG indexed image contains a colour table with transparent colours is loaded or 
 * when a true colour image contains 32-bit bit colours. The getFormat() method returns the class 
 * constants IDXA or RGBA.</td>
 * </tr>
 *
 * </table>
 * 
 * <P>Images are displayed in Flash by filling a shape with the image bitmap. The defineShape()
 * method generates a rectangular shape object which wraps the image:
 *
 * <pre>
 *     int imageId = movie.newIdentifier();
 *     int shapeId = movie.newIdentifier();
 * 
 *     int xOrigin = imageConstructor->getWidth()/2;
 *     int yOrigin = imageConstructor->getHeight()/2;
 * 
 *     int width = 20;
 *     FSColor color = FSColorTable::black();
 * 
 *     movie.add(imageConstructor->defineImage(imageId));
 *     movie.add(imageConstructor->defineShape(shapeId, imageId, xOrigin, yOrigin, width, &color));
 * </pre>
 * 
 * <P>Here the origin, used when placing the shape on the screen, is defined as the centre of the shape.
 * Other points may be defined to suit the alignment of the shape when it is placed on the display list.</P>
 * 
 * <h2>Post Processing</h2>
 * 
 * <P>Once an image has been loaded, FSImageConstructor supports a range of methods to access the colour table 
 * or image data - depending on the image format. This allows the image data to be processed before the objects
 * used to add the image to a Flash file are defined.
 * 
 * <pre>
 *     size_t size = imageConstructor->getColorTableSize();
 *     unsigned char* buffer = new unsigned char[size];
 *     bytesCopied = imageConstructor->getColorTable(buffer);
 *
 *     size_t size = imageConstructor->getIndexedImageSize();
 *     unsigned char* buffer = new unsigned char[size];
 *     bytesCopied = imageConstructor->getIndexedImage(buffer);
 *
 *     size_t size = imageConstructor->getColorImageSize();
 *     unsigned char* buffer = new unsigned char[size];
 *     bytesCopied = imageConstructor->getColorImage(buffer);
 *
 *     size_t size = imageConstructor->getJPEGImageSize();
 *     unsigned char* buffer = new unsigned char[size];
 *     bytesCopied = imageConstructor->getJPEGImage(buffer);
 * </pre>
 * 
 * <P>The information returned will depend on the image format. If an indexed image is loaded then the 
 * getColourTableSize() and getIndexedImageSize() will return the number of bytes for the colour table
 * and image respectively. If getColorImage() or getJPEGImage() are used on an indexed image then they 
 * will return zero. Similarly if the accessor methods getColorTable() is used on a true-colour or JPEG
 * encoded image then no bytes copied to the buffer.</P>
 * 
 * <P>Once the image data has been processed separate set methods are available depending on the type of 
 * image:</P>
 *
 * <pre>
 *     imageConstructor->setIndexedImage(format, imageWidth, imageHeight, colourTable, tableSize, image);
 *     imageConstructor->setColorImage(format, imageWidth, imageHeight, image);
 *     imageConstructor->setJPEGImage(imageWidth, imageHeight, image, imageSize);
 * </pre>
 */
class FSImageConstructor
{
public:
    /** 
     * Define the different formats supported by the FSImageConstructor. 
     */
    enum ImageFormat {
        NONE = -1, /**< The object does not contain an image. */ 
        JPEG = 0, /**< JPEG encoded images */
        IDX8 = 1, /**< Indexed images containing a colour table with 24-bit colours. */
        IDXA = 2, /**< Indexed images containing a colour table with 32-bit colours. */
        RGB5 = 3, /**< True colour images containing 16-bit colours, 5-bits for each colour channel. */
        RGB8 = 4, /**< True colour images containing 24-bit colours, 8-bits for each colour channel. */
        RGBA = 5  /**< True colour images containing 32-bit colours, 8-bits for each colour channel plus transparency. */
    };
    /**
     * Initializes the FSImageConstructor object with the image in the specified file. 
     * This method can be used to generate the image definition objects for a Flash movie 
     * using the same FSImageConstructor object.
     *
     * The method returns a status code indicating whether the object was initialized 
     * correctly, either TransformUtil::OK, TransformUtil::FileNotFound, TransformUtil::ReadError
     * or TransformUtil::FormatError.
     *
     * @param filename the name of the file containing the image.
     * @return a status code indicating whether the image was loaded successfully.
     */
    virtual int CALL setImageFromFile(const char* filename) = 0;
    /**
     * Initializes the FSImageConstructor object with the image data.
     *
     * The method returns a status code indicating whether the object was initialized 
     * correctly, either TransformUtil::OK or TransformUtil::FormatError.
     *
     * @param bytes an array of bytes containing the encoded image.
     * @param size the number of bytes in the array containing the encoded image.
     */
    virtual int CALL setImage(const unsigned char* bytes, size_t size) = 0;
    /**
     * Returns a constant identifying the format for the way the pixels are encoded. The 
     * value returned will be one of the supported image formats: NONE, JPEG, IDX8, IDXA,
     * RGB5, RGB8 or RGBA.
     *
     * @return the image format.
     */
    virtual int CALL getFormat() = 0;
    /**
     * Returns the width of the image in pixels.
     * 
     * @return the image width in pixels.
     */
    virtual unsigned int CALL getWidth() = 0;
    /**
     * Returns the height of the image in pixels.
     * 
     * @return the image height in pixels.
     */
    virtual unsigned int CALL getHeight() = 0;
    /**
     * Returns the number of bytes in the colour table of an indexed image. Each 
     * entry in the colour table contains 4 bytes.
     *
     * If the image format is JPEG or one of the true colour formats (RGB5, RGB8, RGBA)
     * then the number returned is 0.
     *
     * @return the number of bytes in the colour table.
     */
    virtual size_t CALL getColorTableSize() = 0;
    /**
     * Copies the colour table used in an indexed image to the specified buffer. 
     * Each entry in the colour table contains four bytes specifying the values 
     * for the red, green, blue and alpha channels respectively.
     *
     * For images in IDX8 format the alpha channel defaults to 255 (completely opaque).
     * 
     * If the image format is JPEG or one of the true colour formats (RGB5, RGB8, RGBA)
     * then the number returned, indicating the number of bytes copied, is 0.
     *
     * @param buffer an array of bytes large enough to hold the number of bytes in the 
     * colour table.
     *
     * @return the number of bytes copied to the buffer.
     */
    virtual size_t CALL getColorTable(unsigned char* buffer) = 0;
    /**
     * Returns a copy of the image data decoded from an indexed image. The array is 
     * ordered by rows, with each byte specifying an index into the colour table.
     * The buffer should be large enough to hold the entire indexed image: 
     * getWidth() x getHeight() bytes.
     * 
     * The number of bytes copied to the buffer is returned. If the image format is 
     * JPEG or one of the true colour formats (RGB5, RGB8, RGBA) then the number of
     * bytes copied is 0.
     *
     * @param buffer an array large enough to hold the colour table.
     *
     * @return the number of bytes copied to the buffer. If the image format is not
     * an indexed image (either JPEG, RGB5, RGB8, RGBA) then 0 is returned.
     */
    virtual size_t CALL getIndexedImage(unsigned char* buffer) = 0;
    /**
     * Returns a copy of the data decoded from a true colour image. The data
     * returned contains the image, ordered by rows. Each entry for a pixel in a 
     * given row contains 4 bytes - one byte for the red, green, blue and
     * alpha channels, respectively.
     * 
     * The number of bytes copied to the buffer is returned. If the image format is 
     * JPEG or one of the indexed image formats (IDX8, IDXA) then the number of
     * bytes copied is 0.
     *
     * @param buffer an array large enough to hold the image.
     *
     * @return the number of bytes copied to the buffer. If the image format is not
     * a true colour image (either JPEG, IDX8, IDX) then 0 is returned.
     */
    virtual size_t CALL getColorImage(unsigned char* buffer) = 0;
    /**
     * Returns the number of bytes in a JPEG encoded image.
     *
     * If the image format is not in the JPEG format (IDX8, IDXA, RGB5, RGB8, RGBA)
     * then the number returned is 0.
     *
     * @return the number of bytes in the JPEG table.
     */
    virtual size_t CALL getJPEGImageSize() = 0;
    /**
     * Returns a copy of the encoded data decoded from a JPEG image file. The 
     * method returns the number of bytes copied to the buffer.
     *
     * If the image format is an indexed or true colour image (IDX8, IDXA, RGB5, 
     * RGB8, RGBA) then the number of bytes copied is zero.
     *
     * @param buffer an array large enough to hold the image.
     *
     * @return the number of bytes copied to the buffer. If the image format is not
     * a JPEG image (either RGB5, RGB8, RGBA, IDX8, IDXA) then 0 is returned.
     */
    virtual size_t CALL getJPEGImage(unsigned char* buffer) = 0;
    /**
     * Sets the image data for an indexed image.
     * 
     * @param encoding the format for the encoded image, either IDX8, or IDXA.
     * @param imageWidth the width of the image in pixels.
     * @param imageHeight the height of the image in pixels.
     * @param table a pointer to an array containing four bytes for each colour,
     * with bytes for the red, green, blue and alpha channels respectively.
     * @param tableSize the total number of bytes in the colour table.
     * @param image a pointer to an array of bytes, (imageHeight x imageWidth bytes) containing
     * the index into the colour table for each pixel in the image. The array is ordered
     * by rows.
     */
    virtual void CALL setIndexedImage(int encoding, unsigned int imageWidth, unsigned int imageHeight, const unsigned char* table, size_t tableSize, const unsigned char* image) = 0;
    /**
     * Sets the image data for a true colour image.
     * 
     * @param encoding the format for the encoded image, either RGB5, RGB8 or RGBA.
     * @param imageWidth the width of the image in pixels.
     * @param imageHeight the height of the image in pixels.
     * @param image a pointer to an array of bytes, (imageHeight X imageWidth x 4 bytes) containing
     * the colours for each pixel in the image. The image data is ordered by row and each pxiel
     * has 4 bytes for the colour information, ordered by red, green, blue and alpha respectively.
     */
    virtual void CALL setColorImage(int encoding, unsigned int imageWidth, unsigned int imageHeight, const unsigned char* image) = 0;
    /**
     * Sets the image data for a JPEG encoded image.
     * 
     * @param imageWidth the width of the image in pixels.
     * @param imageHeight the height of the image in pixels.
     * @param image a pointer to an array of bytes containing the JPEG encoded image.   
     * @param size the total number of bytes in the image.
     */
    virtual void CALL setJPEGImage(unsigned int imageWidth, unsigned int imageHeight, const unsigned char* image, size_t size) = 0;
    /**
     * Generates an object used to define an image in a Flash file. The class of the object returned is 
     * determined by the format of the image data:
     *
     * <table>
     * <tr><th>Class</th><th>Generated when...</th></tr>
     *
     * <tr>
     * <td>FSDefineJPEGImage2</td>
     * <td>The image format is JPEG and the level of transparency is not defined.</td>
     * </tr>
     *
     * <tr>
     * <td>FSDefineImage</td>
     * <td>The image format is IDX8, RGB5 or RGB8.</td>
     * </tr>
     *
     * <tr>
     * <td>FSDefineImage2</td>
     * <td>The image format is IDXA, RGBA.</td>
     * </tr>
     *
     * </table>
     *
     * @param identifier an unique identifier that is used to reference the image definition in a Flash movie.
     */
    virtual FSDefineObject* CALL defineImage(int identifier) = 0;
    /**
     * Generates the shape definition object that is required to display an image in a Flash movie.
     * The shape is generated with a single fill style (FSBitmapFill object). The origin of the shape
     * is specified relative to the top left corner of the image.
     *
     * The borderStyle argument specifies a border that will be drawn around the image. The line 
     * thickness for the style may be set to zero if no border is drawn.
     * 
     * @param shapeIdentifier an unique identifier that is used to reference the shape definition in a  
     * Flash movie.
     *
     * @param imageIdentifier the unique identifier of the image generated using the defineImage() method.
     * 
     * @param xOrigin the offset in pixels along the x-axis, relative to the top left corner of 
     * the image, where the origin (0,0) of the shape will be located.
     * 
     * @param yOrigin the offset in pixels along the y-axis, relative to the top left corner of 
     * the image, where the origin (0,0) of the shape will be located.
     *
     * @param borderWidth the of the line drawn around the border of the image. May be set to zero
     * if no border is drawn.
     *
     * @param borderColor a pointer to an FSColor object used to render the border surrounding the image.
     */
    virtual FSDefineShape3* CALL defineShape(int shapeIdentifier, int imageIdentifier, int xOrigin, int yOrigin, int borderWidth, const FSColor* borderColor) = 0;
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
            FSImageConstructor* constructor = static_cast<FSImageConstructor*>(p);
            constructor->destroy();
        }
    }
};

/**
 * Factory function for creating an FSImageConstructor object with no image.
 */
extern "C" FSImageConstructor* ImageConstructor();
}

#endif // __FSImageConstructor_h__
