/* 
 * FSCodec.cpp
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

#include "FSCodec.h"

#include <math.h>
#include <stdio.h>
#include <string.h>

using namespace transform;

namespace transform {

class FSCodecImpl : public FSCodec
{
public:
    FSCodecImpl(ByteOrder order) 
        : ordering(order)
        , data(0)
        , ptr(0)
        , dataSize(0)
    {
    }
    FSCodecImpl(ByteOrder order, size_t size) 
        : ordering(order)
        , data(0)
        , ptr(0)
        , dataSize(size)
    {
        data = new unsigned char[dataSize];

        memset(data, 0, dataSize*sizeof(unsigned char));
    }
    ~FSCodecImpl()
    {
        delete [] data;
    }
    void operator delete(void* p)
    {
        ::operator delete(p);
    }
    void CALL destroy()
    {
        delete this;
    }
    ByteOrder CALL getByteOrder() 
    { 
        return ordering; 
    }
    void CALL setByteOrder(ByteOrder order)
    {
        ordering = order;
    }
    size_t CALL getDataSize()
    {
        return dataSize;
    }
    size_t CALL getData(unsigned char* bytes)
    {
        memcpy(bytes, data, dataSize*sizeof(unsigned char));

        return dataSize;
    }
    int CALL setDataFromFile(const char* filename)
    {
        int status = TransformUtil::OK;

        FILE* input = 0;
        long length = 0;

        if ((input = fopen(filename, "rb")))
        {
            if (fseek(input, 0, SEEK_END) == 0)
            {
                if ((length = ftell(input)) != -1L)
                {
                    rewind(input);

                    data = new unsigned char[length];
                    dataSize = length;

                    if (fread(data, sizeof(unsigned char), length, input) != length)
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
        return status;
    }
    void CALL setData(const unsigned char* bytes, size_t size)
    {
        dataSize = size;

        delete [] data;
        ptr = 0;

        data = new unsigned char[dataSize];
        memcpy(data, bytes, dataSize*sizeof(unsigned char));
    }
    unsigned int CALL getPointer()
    {
        return (unsigned int)ptr;
    }
    void CALL setPointer(unsigned int offset)
    {
        size_t end = dataSize << 3;

        ptr = offset;

        if (ptr >= end)
            ptr = end;
    }
    void CALL adjustPointer(int offset)
    {
        size_t end = dataSize << 3;

        ptr += offset;
        
        if (ptr >= end)
            ptr = end;
    }
    void CALL alignToByte() 
    { 
        ptr = (ptr+7) & ~7; 
    }
    bool CALL eof() 
    { 
        return ptr >= (dataSize<<3); 
    }
    bool CALL findBits(int value, unsigned int numberOfBits, int step)
    {
        bool found = false;

        size_t start = ptr;
        size_t end = dataSize << 3;

        for (; ptr < end; ptr += step)
        {
            if (readBits(numberOfBits) == value)
            {
                ptr -= numberOfBits;
                found = true; 
                break;
            }
            ptr -= numberOfBits;
        }
        
        if (found == false)
            ptr = start;
            
        return found;
    }
    bool CALL findWord(int value, unsigned int numberOfBytes, int step)
    {
        bool found = false;

        size_t start = ptr;
        size_t end = dataSize << 3;

        if (numberOfBytes < 1 || numberOfBytes > 4)
            return found;
        
        ptr = (ptr+7) & ~7;

        for (; ptr < end; ptr += step*8)
        {
            if (readWord(numberOfBytes) == value)
            {
                ptr -= (numberOfBytes*8);
                found = true;
                break;
            }
            ptr -= (numberOfBytes*8);
        }
        
        if (found == false)
            ptr = start;
            
        return found;
    }
    unsigned int CALL readBits(unsigned int numberOfBits)
    {
        unsigned int value = 0;

        if (numberOfBits == 0)
            return value;
        
        if (numberOfBits < 1 || numberOfBits > 32)
            return 0;
        
        size_t index = ptr >> 3;
        size_t end = dataSize << 3;

        unsigned int bitsLeft = (unsigned int)(end - ptr);
        unsigned int base = (bitsLeft >= 32) ? 0 : 32-bitsLeft;
        
        for (unsigned int i=32; i>base; i-=8, index++)
            value |= (data[index] & 0x000000FF) << (i-8);

        value <<= ptr % 8;
        value >>= 32 - numberOfBits;

        ptr += numberOfBits;

        if (ptr > end)
            ptr = end;

        return value;
    }
    int CALL readSignedBits(unsigned int numberOfBits)
    {
        unsigned int value = 0;

        if (numberOfBits < 1 || numberOfBits > 32)
            return 0;
        
        size_t index = ptr >> 3;
        size_t end = dataSize << 3;

        unsigned int bitsLeft = (unsigned int)(end - ptr);
        unsigned int base = (bitsLeft > 32) ? 0 : 32-bitsLeft;
        
        for (unsigned int i=32; i>base; i-=8, index++)
            value |= (data[index] & 0x000000FF) << (i-8);

        value <<= ptr % 8;
        value >>= 32 - numberOfBits;

        if (value >> (numberOfBits-1))
            value |= ~0 << numberOfBits;

        ptr += numberOfBits;

        if (ptr > end)
            ptr = end;

        return value;
    }
    unsigned int CALL readWord(unsigned int numberOfBytes)
    {
        unsigned int value = 0;

        if (numberOfBytes < 1 || numberOfBytes > 4)
            return 0;
        
        size_t index = ptr >> 3;
        size_t end = dataSize << 3;
        
        if (index + numberOfBytes > dataSize)
            numberOfBytes = (unsigned int)(dataSize - index);
        
        unsigned int numberOfBits = numberOfBytes*8;

        if (ordering == LittleEndian)
        {
            for (unsigned int i=0; i<numberOfBits; i+=8, ptr+=8, index++)
                value += (data[index] & 0x000000FF) << i;
        }
        else
        {
            for (unsigned int i=0; i<numberOfBits; i+=8, ptr+=8, index++)
            {
                value = value << 8;
                value += data[index] & 0x000000FF;
            }
        }
        
        if (ptr > end)
            ptr = end;

        return value;
    }
    int CALL readSignedWord(unsigned int numberOfBytes)
    {
        unsigned int value = 0;

        if (numberOfBytes < 1 || numberOfBytes > 4)
            return 0;
        
        size_t index = ptr >> 3;
        size_t end = dataSize << 3;
        
        if (index + numberOfBytes > dataSize)
            numberOfBytes = (unsigned int)(dataSize - index);
        
        unsigned int numberOfBits = numberOfBytes*8;

        if (ordering == LittleEndian)
        {
            for (unsigned int i=0; i<numberOfBits; i+=8, ptr+=8, index++)
                value += (data[index] & 0x000000FF) << i;
        }
        else
        {
            for (unsigned int i=0; i<numberOfBits; i+=8, ptr+=8, index++)
            {
                value = value << 8;
                value += data[index] & 0x000000FF;
            }
        }
        
        if (value >> (numberOfBits-1))
            value |= ~0 << numberOfBits;

        if (ptr > end)
            ptr = end;

        return value;
    }
    void CALL writeBits(int value, unsigned int numberOfBits)
    {
        size_t end = dataSize << 3;

        if (ptr+numberOfBits > end)
        {
            unsigned char* bytes = new unsigned char[dataSize*2];
            
            memcpy(bytes, data, dataSize*sizeof(unsigned char));
            delete [] data;
            data = bytes;
            dataSize *= 2;
        }
        
        size_t index = ptr >> 3;
        unsigned int val = value << (32 - numberOfBits);

        val = val >> (ptr % 8);
        val = val | (data[index] << 24);

        for (int i=24; i>=0; i-=8, index++)
            data[index] = val >> i;
        
        ptr += numberOfBits;
    }
    void CALL writeWord(int value, unsigned int numberOfBytes)
    {
        if (numberOfBytes < 1 || numberOfBytes > 4)
            numberOfBytes = 0;
            
        unsigned int numberOfBits = numberOfBytes*8;
        size_t end = dataSize << 3;
        
        if (ptr+numberOfBits > end)
        {
            unsigned char* bytes = new unsigned char[dataSize*2];
            
            memcpy(bytes, data, dataSize*sizeof(unsigned char));
            delete [] data;
            data = bytes;
            dataSize *= 2;
        }
        
        if (ordering == LittleEndian)
        {
            size_t index = ptr >> 3;
            
            for (unsigned int i=0; i<numberOfBits; i+=8, ptr+=8, value >>= 8, index++)
                data[index] = value;
        }
        else
        {
            size_t index = (ptr + numberOfBits - 8) >> 3;
            
            for (unsigned int i=0; i<numberOfBits; i+=8, ptr+=8, value >>= 8, index--)
                data[index] = value;
        }
    }
    int CALL readBytes(unsigned char* bytes, size_t size)
    {
        int bytesRead = 0;

        if (bytes == 0 || size == 0)
            return bytesRead;

        size_t index = ptr >> 3;

        if (index+size > dataSize)
            size = dataSize - index;

        for (unsigned int i=0; i<size; i++, ptr+=8, index++, bytesRead++)
            bytes[i] = data[index];

        return bytesRead;
    }
    int CALL writeBytes(const unsigned char* bytes, size_t size)
    {
        int bytesWritten = 0;

        if (bytes == 0 || size == 0)
            return bytesWritten;

        size_t index = ptr >> 3;

        if (index+size > dataSize)
        {
            unsigned char* buffer = new unsigned char[dataSize*2];
            
            memcpy(buffer, data, dataSize*sizeof(unsigned char));
            delete [] data;
            data = buffer;
            dataSize *= 2;
        }
        
        for (unsigned int i=0; i<dataSize; i++, ptr+=8, index++, bytesWritten++)
            data[index] = bytes[i];
        
        return bytesWritten;
    }
    float CALL readFixedBits(unsigned int numberOfBits, unsigned int fractionSize)
    {
        float value = 0;
        float divisor = (float)(1 << fractionSize);

        value = ((float)readSignedBits(numberOfBits)) / divisor;
        
        return value;
    }
    void CALL writeFixedBits(float value, unsigned int numberOfBits, unsigned int fractionSize)
    {
        float floatValue = value * (float)pow(2.0, (double)fractionSize);

        writeBits((int)floatValue, numberOfBits);
    }
    unsigned char CALL readByte()
    {
        unsigned char value = data[ptr>>3];

        ptr += 8;
        
        return value;
    }
    unsigned short CALL readShort()
    {
        unsigned int value = 0;
        size_t index = ptr >> 3;
        
        if (ordering == LittleEndian)
        {
            value = (data[index++] & 0xFF);    
            value += (data[index] & 0xFF) << 8;
        }
        else
        {
            value = (data[index++] & 0xFF) << 8;
            value += (data[index] & 0xFF);    
        }

        ptr += 16;
        
        return value;
    }
    short CALL readSignedShort()
    {
        unsigned int value = 0;
        size_t index = ptr >> 3;
        
        if (ordering == LittleEndian)
        {
            value = (data[index++] & 0xFF);    
            value += (data[index] & 0xFF) << 8;
        }
        else
        {
            value = (data[index++] & 0xFF) << 8;
            value += (data[index] & 0xFF);    
        }

        if (value >> 15)
            value |= ~0 << 16;

        ptr += 16;
        
        return value;
    }
    unsigned int CALL readInt()
    {
        unsigned int value = 0;
        size_t index = ptr >> 3;
        
        if (ordering == LittleEndian)
        {
            value = (data[index++] & 0xFF);    
            value += (data[index++] & 0xFF) << 8;
            value += (data[index++] & 0xFF) << 16;
            value += (data[index] & 0xFF) << 24;
        }
        else
        {
            value = (data[index++] & 0xFF) << 24;
            value += (data[index++] & 0xFF) << 16;
            value += (data[index++] & 0xFF) << 8;
            value += (data[index] & 0xFF);    
        }
        ptr += 32;
        
        return value;
    }
private:
    ByteOrder ordering;
    size_t ptr;

    unsigned char* data;
    size_t dataSize;
};

extern "C" FSCodec* CALL Codec(FSCodec::ByteOrder order)
{
    return new FSCodecImpl(order);
}

extern "C" FSCodec* CALL CodecWithSize(FSCodec::ByteOrder order, size_t size)
{
    return new FSCodecImpl(order, size);
}

}
