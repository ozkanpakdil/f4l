/* 
 * FSCodec.h
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

#ifndef __FSCodec_h__
#define __FSCodec_h__ 1

#include "FSTransformUtil.h"

namespace transform
{
/**
 * FSCodec is similar to stream classes, allowing words and bit fields to be read and 
 * written from an internal array of bytes. FSCodec supports both little-endian and
 * big-endian byte ordering. The primary use of the class is to support post-processing
 * of sound files loaded using the FSSoundConstructor class where the encoded sound samples
 * contain bits fields. For example compressing 16-bit, byte-aligned sound samples to the 
 * ADPCM format. However the class may be used in any situation where data must be encoded
 * or decoded to an array of bytes.
 * 
 * The FSCodec class maintains an internal pointer which points to the next bit in the internal
 * array where data will be read or written. When calculating an offset in bytes to jump to
 * simply multiply the offset by 8 for the correct bit position. The class provides accessor
 * methods, getPointer() and setPointer() to change the location of the internal pointer.
 * 
 * When writing to an array the size of the array is changed dynamically should a write 
 * operation cause a buffer overflow. For reads if an overflow results then the bits/bytes
 * that overflowed will be set to zero, rather than throwing an exception. The eof() method 
 * can be used to determine whether the end of the buffer has been reached.
 */
class FSCodec
{
public:
    /** Byte ordering supported when reading and writing multibyte words. */
    enum ByteOrder {
        /**
         * Multibyte words are stored in little-endian format with the least significant 
         * byte in a word stored first.
         */
        LittleEndian = 0,
        /** 
         * Multibyte words are stored in big-endian format with the most significant
         * byte in a word stored first.
         */
        BigEndian = 1
    };
    /**
     * Returns the byte-ordering used to encode or decode multi-byte words.
     *
     * @return the order of multi-byte words, either FSCodec::LittleEndian or 
     * FSCodec::BigEndian.
     */
    virtual ByteOrder CALL getByteOrder() = 0;
    /**
     * Sets the byte-ordering used to encode or decode multi-byte words.
     *
     * @param order the order of multi-byte words, either FSCodec::LittleEndian or 
     * FSCodec::BigEndian.
     */
    virtual void CALL setByteOrder(ByteOrder order) = 0;
    /**
     * Returns the number of bytes in the internal buffer.
     * 
     * @return the size of the internal buffer.
     */
    virtual size_t CALL getDataSize() = 0;
    /**
     * Returns a copy of the internal buffer.
     *
     * @param bytes a buffer where the data will be copied to.
     * @return the actual number of bytes copied.
     */
    virtual size_t CALL getData(unsigned char* bytes) = 0;
    /**
     * Initializes the internal buffer with the contents of the file.
     *
     * The method returns a status code indicating whether the FSCodec was initialized 
     * correctly, either TransformUtil::OK, TransformUtil::FileNotFound or 
     * TransformUtil::ReadError.
     * 
     * @param filename the name of the file which will be loaded into the internal buffer.
     * @return a status code indicating whether the buffer was initialized successfully.
     */
    virtual int CALL setDataFromFile(const char* filename) = 0;
    /**
     * Initializes the internal buffer with an array of bytes for decoding.
     * 
     * @param bytes a byte array that will be copied to the internal buffer.
     * @param size the number of bytes in the array.
     */
    virtual void CALL setData(const unsigned char* bytes, size_t size) = 0;
    /**
     * Returns the offset, in bits, from the start of the buffer where the next value will be 
     * read or written.
     * 
     * @return the offset in bits where the next value will be read or written. 
     */
    virtual unsigned int CALL getPointer() = 0;
    /**
     * Sets the offset, in bits, from the start of the buffer where the next value will be 
     * read or written. If the offset falls outside of the bits range supported by the buffer 
     * then the pointer is clamped to either the start or end of the buffer.
     *  
     * @param offset the offset in bits from the start of the array of bytes.
     */
    virtual void CALL setPointer(unsigned int offset) = 0;
    /**
     * Adds an offset to the internal pointer. If the offset falls outside of the bits range 
     * supported by the buffer then the pointer is clamped to either the start or end of the 
     * buffer.
     *  
     * @param offset the value to add to the internal pointer.
     */
    virtual void CALL adjustPointer(int offset) = 0;

    /**
     * Moves the internal pointer forward so it is aligned on a byte boundary. All word
     * values read and written to the internal buffer must be byte-aligned.
     */
    virtual void CALL alignToByte() = 0;
    /**
     * Returns true of the internal pointer is at the end of the buffer.
     * 
     * @return true if the pointer is at the end of the buffer, false otherwise.
     */
    virtual bool CALL eof() = 0;
    /**
     * Searches the internal buffer for a bit pattern and advances the pointer to
     * the start of the bit field, returning true to signal a successful search.
     * If the bit pattern cannot be found then the method returns false and the 
     * position of the internal pointer is not changed.
     * 
     * The step, in bits, added to the pointer can be specified, allowing the
     * number of bits being searched to be independent of the location in the 
     * internal buffer. This is useful for example when searching for a bit 
     * field that begins on a byte or word boundary.
     *  
     * @param value an integer containing the bit pattern to search for.
     * @param numberOfBits least significant n bits in the value to search for.
     * @param step the increment in bits to add to the internal pointer as the buffer
     * is searched.
     * @return true if the pattern was found, false otherwise.
     */
    virtual bool CALL findBits(int value, unsigned int numberOfBits, int step) = 0;
    /**
     * Searches the internal buffer for a word and advances the pointer to the location
     * where the word was found, returning true to signal a successful search. The 
     * search will begin on the next byte boundary. If word cannot be found then the 
     * method returns false and the position of the internal pointer is not changed.
     * 
     * Specifying the number of bytes in the search value allows word of either 8, 16,
     * 24 or 32 bits to be searched for. Searches for words are performed faster than 
     * using the findBits() method.
     * 
     * @param value an integer containing the word to search for.
     * @param numberOfBytes least significant n bytes in the value to search for.
     * @param step the increment in bytes to add to the internal pointer as the buffer
     * is searched.
     * @return true if the pattern was found, false otherwise.
     */
    virtual bool CALL findWord(int value, unsigned int numberOfBytes, int step) = 0;
    /**
     * Read an unsigned bit field from the internal buffer.
     * 
     * If a buffer overflow occurs then the number of bits which cause the overflow will 
     * be set to zero.
     * 
     * @param numberOfBits the number of bits to read.
     * @return the value read.
     */
    virtual unsigned int CALL readBits(unsigned int numberOfBits) = 0;
    /**
     * Read a signed bit field from the internal buffer.
     * 
     * If a buffer overflow occurs then the number of bits which cause the overflow will 
     * be set to zero.
     * 
     * @param numberOfBits the number of bits to read.
     * @return the value read.
     */
    virtual int CALL readSignedBits(unsigned int numberOfBits) = 0;
    /**
     * Read an unsigned word from the internal buffer.
     * 
     * If a buffer overflow occurs then the number of bytes which cause the overflow will 
     * be set to zero.
     * 
     * @param numberOfBytes the number of bytes read in the range 1..4.
     * @return the value read.
     */
    virtual unsigned int CALL readWord(unsigned int numberOfBytes) = 0;
    /**
     * Read a signed word from the internal buffer.
     * 
     * If a buffer overflow occurs then the number of bytes which cause the overflow will 
     * be set to zero.
     * 
     * @param numberOfBytes the number of bytes read in the range 1..4.
     * @return the value read.
     */
    virtual int CALL readSignedWord(unsigned int numberOfBytes) = 0;
    /**
     * Write a bit value to the internal buffer. The buffer will resize automatically
     * if required.
     * 
     * @param value an integer containing the value to be written.
     * @param numberOfBits the least significant n bits from the value that will be 
     * written to the buffer.
     */
    virtual void CALL writeBits(int value, unsigned int numberOfBits) = 0;
    /**
     * Write a word to the internal buffer. The buffer will resize automatically
     * if required.
     * 
     * @param value an integer containing the value to be written.
     * @param numberOfBytes the least significant n bytes from the value that will be 
     * written to the buffer.
     */
    virtual void CALL writeWord(int value, unsigned int numberOfBytes) = 0;
    /**
     * Reads an array of bytes from the internal buffer. If a read overflow occurs
     * while reading the internal buffer then the remaining bytes in the array will
     * not be filled. The method returns the number of bytes read.
     * 
     * @param bytes the array that will be initialized with the bytes read.
     * @param size the number of bytes of data.
     * @return the number of bytes read from the buffer.
     */
    virtual int CALL readBytes(unsigned char* bytes, size_t size) = 0;
    /**
     * Writes an array of bytes to the internal buffer. The internal buffer will
     * be resized automatically if required.
     * 
     * @param bytes the array containing the data to be written.
     * @param size the number of bytes of data.
     * @return the number of bytes written to the buffer.
     */
    virtual int CALL writeBytes(const unsigned char* bytes, size_t size) = 0;
    /**
     * Reads a bit field representing a fixed-point number from the internal buffer.
     * The value is returned as a floating point value.
     *
     * This method can only be used to read fixed-point numbers that are stored 
     * as bit fields where the most significant bit is read first from the buffer.
     * This will also work for word-oriented values stored in BigEndian format.
     *
     * @param numberOfBits the total number of bits used to represent the value.
     * @param fractionSize the number of bits in the word used to store the 
     * fractional value.
     *
     */
    virtual float CALL readFixedBits(unsigned int numberOfBits, unsigned int fractionSize) = 0;
    /**
     * Writes floating point number as a fixed-point bit field to the internal buffer.
     *
     * This method can only be used to write fixed-point numbers that are stored 
     * as bit fields where the most significant bit is written first to the buffer.
     * This will also work for word-oriented values stored in BigEndian format.
     *
     * @param value the number to be written to the buffer.
     * @param numberOfBits the total number of bits used to represent the value.
     * @param fractionSize the number of bits in the word used to store the 
     * fractional value.
     *
     */
    virtual void CALL writeFixedBits(float value, unsigned int numberOfBits, unsigned int fractionSize) = 0;
    /**
     * readByte is a convenience method to read an 8-bit value from the internal
     * buffer.
     *
     * @return a byte containing an 8-bit word from the internal buffer.
     */ 
    virtual unsigned char CALL readByte() = 0;
    /**
     * readShort is a convenience method to read an unsigned 16-bit value from the 
     * internal buffer. No checking is performed to avoid overflowing the internal
     * buffer.
     *
     * @return a value containing an unsigned 16-bit word from the internal buffer.
     */ 
    virtual unsigned short CALL readShort() = 0;
    /**
     * readSignedShort is a convenience method to read a signed 16-bit value from the 
     * internal buffer. No checking is performed to avoid overflowing the internal
     * buffer.
     *
     * @return a value containing a signed 16-bit word from the internal buffer.
     */ 
    virtual short CALL readSignedShort() = 0;
    /**
     * readInt is a convenience method to read an unsigned 32-bit value from the 
     * internal buffer. No checking is performed to avoid overflowing the internal
     * buffer.
     *
     * @return a value containing an unsigned 32-bit word from the internal buffer.
     */ 
    virtual unsigned int CALL readInt() = 0;
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
            FSCodec* codec = static_cast<FSCodec*>(p);
            codec->destroy();
        }
    }
};

/**
 * Factory function creating an FSCodec object using the specified byte ordering.
 * 
 * @param order the byte-order for encoding or decoding multi-byte words, either 
 * FSCodec::LittleEndian or FSCodec::BigEndian.
 */
extern "C" FSCodec* CALL Codec(FSCodec::ByteOrder order);
/**
 * Factory function creating an FSCodec object with the specified byte ordering
 * and an internal buffer initialized to hold size bytes.
 * 
 * @param order the byte-order for encoding or decoding multi-byte words, either 
 * FSCodec::LittleEndian or FSCodec::BigEndian.
 */
extern "C" FSCodec* CALL CodecWithSize(FSCodec::ByteOrder order, size_t size);

}
#endif // __FSCodec_h__
