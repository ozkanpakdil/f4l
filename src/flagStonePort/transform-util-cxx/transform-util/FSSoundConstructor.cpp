/*
 * FSSoundConstructor.cpp
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

#include "FSSoundConstructor.h"

#include <stdlib.h>
#include <stdio.h>
#include <transform/transform.h>
#include "FSCodec.h"

#define FMT   0x20746d66
#define DATA  0x61746164
#define MPEG1 3

using namespace transform;

namespace transform {

class FSSoundConstructorImpl : public FSSoundConstructor
{
public:
    FSSoundConstructorImpl() 
        : format(0)
        , numberOfChannels(0)
        , samplesPerChannel(0)
        , sampleRate(0)
        , sampleSize(0)
        , sound(NULL)
        , soundSize(0)
        , frameTable(NULL)
        , samplesPerFrame(0)
    {
    }
    ~FSSoundConstructorImpl()
    {
        delete [] sound;
        delete [] frameTable;
    }
    void operator delete(void* p)
    {
        ::operator delete(p);
    }
    void CALL destroy()
    {
        delete this;
    }
    int CALL getFormat()
    {
        return format;
    }
    unsigned int CALL getNumberOfChannels()
    {
        return numberOfChannels;
    }
    unsigned int CALL getSamplesPerChannel()
    {
        return samplesPerChannel;
    }
    unsigned int CALL getSampleRate()
    {
        return sampleRate;
    }
    unsigned int CALL getSampleSize()
    {
        return sampleSize;
    }
    size_t CALL getSoundSize()
    {
        return soundSize;
    }
    size_t CALL getSound(unsigned char* buffer)
    {
        memcpy(buffer, sound, soundSize*sizeof(unsigned char));
        return soundSize;
    }

    int CALL setSoundFromFile(const char* filename)
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
            status = setSound(buffer, (size_t)length);

        delete [] buffer;

        return status;
    } 
    int CALL setSound(const unsigned char* bytes, size_t size)
    {
        int status = TransformUtil::OK;
        int signature = ((bytes[0] & 0xFF) << 8) | (bytes[1] & 0xFF);

        switch (signature)
        {
            case 0x5249: status = decodeWAV(bytes, size); break;
            case 0x4944: status = decodeMP3(bytes, size); break;
            default: status = decodeMP3(bytes, size); break;
        }
        return status;
    }
    void CALL setSound(int encoding, unsigned int channelCount, unsigned int sampleCount, unsigned int samplingRate, unsigned int samplingSize, const unsigned char* bytes, size_t size)
    {
        format = encoding;
        numberOfChannels = channelCount;
        samplesPerChannel = sampleCount;
        sampleRate = samplingRate;
        sampleSize = samplingSize;

        sound = new unsigned char[size];
        soundSize = size;

        memcpy(sound, bytes, size*sizeof(unsigned char));
        
        if (format == FSSound::MP3)
        {
            FSCodec* coder = Codec(FSCodec::LittleEndian);
            coder->setData(bytes, size);

            coder->findBits(0x7FF, 11, 8);
            
            int frameStart = coder->getPointer();
            int dataLength = (unsigned int)size - (coder->getPointer() >> 3);
            int numberOfFrames = 0;
            
            while (coder->findBits(0x7FF, 11, 8))
            {
                coder->adjustPointer(MP3FrameSize(coder) << 3);
                numberOfFrames++;
            }
            
            delete [] frameTable;
            frameTable = new int[numberOfFrames*2];
            
            coder->setPointer(frameStart);
            
            int frameNumber = 0;
            
            while (coder->findBits(0x7FF, 11, 8))
            {
                frameTable[frameNumber+0] = (coder->getPointer()- frameStart + 16) >> 3;
                
                coder->adjustPointer(11); // skip start of frame marker

                int version = coder->readBits(2);
                
                coder->adjustPointer(3);
                
                int bitRate = bitRates[version][coder->readBits(4)];
                int sampleRate = samplingRates[version][coder->readBits(2)];
                int padding = coder->readBits(1);

                frameTable[frameNumber++ + 1] = 4 + (((version == MPEG1) ? 144 : 72) * bitRate*1000 / sampleRate + padding) - 4;
        
                coder->adjustPointer((MP3FrameSize(coder) << 3)-23);
            }
        }
    }

    FSDefineSound* CALL defineSound(int anIdentifier)
    {
        byte* bytes = 0;
        size_t size = 0;
        
        switch (format)
        {
            case FSSound::PCM:
            case FSSound::ADPCM:
                size = soundSize;
                bytes = new byte[size];
                memcpy(bytes, sound, size);
                break;
            case FSSound::MP3:
                size = 2 + soundSize;
                bytes = new byte[size];
                bytes[0] = 0;
                bytes[1] = 0;
                memcpy(bytes+2, sound, soundSize);
                break;
        }
        return new FSDefineSound(anIdentifier, format, sampleRate, numberOfChannels, sampleSize, samplesPerChannel, bytes, size);
    }
    FSSoundStreamHead2* CALL streamHeader(unsigned int samplesPerBlock)
    {
       return new FSSoundStreamHead2(format, sampleRate, numberOfChannels, sampleSize, sampleRate, numberOfChannels, sampleSize, samplesPerBlock, 0);
    }
    FSSoundStreamBlock* CALL streamBlock(unsigned int blockNumber, unsigned int samplesPerBlock)
    {
        int firstSample = 0;
        int firstSampleOffset = 0;
        int bytesPerBlock = 0;
        int bytesRemaining = 0;
        int numberOfBytes = 0;
        
        int framesToSend = 0;
        int framesSent = 0;
        int frameCount = 0;
        int sampleCount = 0;
        int seek = 0;
        
        byte* bytes = 0;
        size_t size = 0;

        switch (format)
        {
            case FSSound::PCM:
                firstSample = blockNumber * samplesPerBlock;
                firstSampleOffset = firstSample * sampleSize * numberOfChannels;
                bytesPerBlock = samplesPerBlock * sampleSize * numberOfChannels;
                bytesRemaining = (int)soundSize - firstSampleOffset;
                
                numberOfBytes = (bytesRemaining < bytesPerBlock) ? bytesRemaining : bytesPerBlock;
            
                bytes = new byte[numberOfBytes];
                memcpy(bytes, sound+firstSampleOffset, numberOfBytes);
                break;
            case FSSound::ADPCM:
                break;
            case FSSound::MP3:
                framesToSend = ((blockNumber+1) * samplesPerBlock) / samplesPerFrame;
                framesSent = (blockNumber * samplesPerBlock) / samplesPerFrame;
                frameCount = framesToSend - framesSent;
                sampleCount = frameCount * samplesPerFrame;
                seek = (blockNumber * samplesPerBlock) - (framesSent * samplesPerFrame);
            
                numberOfBytes = 4;
                
                for (int i=0, j=framesSent; i<frameCount; i++, j++)
                     numberOfBytes += frameTable[j*2+1];
                
                bytes = new byte[numberOfBytes];
            
                bytes[0] = sampleCount;
                bytes[1] = sampleCount >> 8;
                bytes[2] = seek;
                bytes[3] = seek >> 8;
                
                int offset = 4; 
                
                for (int i=0, j=framesSent; i<frameCount; i++, j++)
                {
                    memcpy(bytes+offset, sound+frameTable[j*2], frameTable[j*2+1]);
                    offset += frameTable[j*2+1];
                }
                break;
        }
        
        if (bytes != 0)
            return new FSSoundStreamBlock(bytes, numberOfBytes);
        else
            return NULL;
    }

private:
    int MP3FrameSize(FSCodec* coder)
    {
        int frameSize = 4;
        
        coder->adjustPointer(11);

        int version = coder->readBits(2);
            
        coder->adjustPointer(3);
            
        int bitRate = bitRates[version][coder->readBits(4)];
        int sampleRate = samplingRates[version][coder->readBits(2)];
           int padding = coder->readBits(1);

        coder->adjustPointer(-23);
            
        frameSize += (((version == MPEG1) ? 144 : 72) * bitRate*1000 / sampleRate + padding) - 4;
        
        return frameSize;
    }
    int decodeWAV(const byte* bytes, size_t size)
    {
        FSCodec* coder = Codec(FSCodec::LittleEndian);
        coder->setData(bytes, size);

        int status = TransformUtil::OK;

        const int riffSignature[4] = { 82, 73, 70, 70 };
        const int wavSignature[4] = { 87, 65, 86, 69 };

        int length = 0;
        int chunkType = 0;
        bool moreChunks = true;

        for (int i=0; i<4; i++)
        {
            if (coder->readByte() != riffSignature[i])
                status = TransformUtil::FormatError;
        }
        
        coder->readInt();
        
        for (int i=0; i<4; i++)
        {
            if (coder->readByte() != wavSignature[i])
                status = TransformUtil::FormatError;
        }

        if (status != TransformUtil::OK)
            return status;
       
        while (moreChunks)
        {
            chunkType = coder->readInt();
            length = coder->readInt();
            
            int blockStart = coder->getPointer();
            
            switch (chunkType)
            {
                case FMT: status = decodeFMT(coder, length); break;
                case DATA: decodeDATA(coder, length); length += (length % 2); break;
                default: coder->adjustPointer(length << 3); break;
            }

            int nextBlock = blockStart + (length << 3);

#ifdef _DEBUG              
            int bytesRead = (coder->getPointer() - blockStart) >> 3;
                
            if (bytesRead < length)
                printf("%d chunk underflowed by %d bytes.", chunkType, length - bytesRead);
            else if (bytesRead > length)
                printf("%d chunk overflowed by %d bytes.", chunkType, bytesRead - length);
#endif // _DEBUG
            coder->setPointer(nextBlock);
            moreChunks = coder->eof() == false;

        }
        return status;
    }
    int decodeFMT(FSCodec* coder, size_t length)
    {
        format = FSSound::PCM;
        int status = TransformUtil::OK;
        
        if (coder->readShort() != 1)
            return TransformUtil::FormatError;
        
        numberOfChannels = coder->readShort();
        sampleRate = coder->readInt();
        coder->readInt(); // total data length
        coder->readShort(); // total bytes per sample
        sampleSize = coder->readShort() / 8;

        return status;
    }    
    void decodeDATA(FSCodec* coder, size_t length)
    {
        samplesPerChannel = (int)length / (sampleSize*numberOfChannels);

        sound = new byte[length];
        soundSize = length;
        coder->readBytes(sound, length);
        
        coder->adjustPointer(((int)length % 2)*8);
    }
    int decodeMP3(const byte* bytes, size_t size)
    {
        FSCodec* coder = Codec(FSCodec::LittleEndian);
        coder->setData(bytes, size);

        int status = TransformUtil::OK;

        const int frameSizeMP3[4] = { 576, 576, 576, 1152 };
        const int channelCount[4] = { 2, 2, 2, 1 };

        format = FSSound::MP3;
        sampleSize = 2;
        
        coder->findBits(0x7FF, 11, 8);
        
        int frameStart = coder->getPointer();
        int dataLength = (int)size - (coder->getPointer() >> 3);
        
        sound = new byte[dataLength];
        soundSize = dataLength;

        coder->readBytes(sound, dataLength);
        coder->adjustPointer(-(dataLength << 3));
        
        int numberOfFrames = 0;
        
        while (coder->findBits(0x7FF, 11, 8))
        {
            coder->adjustPointer(MP3FrameSize(coder) << 3);
            numberOfFrames++;
        }
        
        delete [] frameTable;
        frameTable = new int[numberOfFrames*2];
        
        for (int i=0; i<numberOfFrames; i++)
        {
            frameTable[i*2] = -1;
            frameTable[i*2+1] = 0;
        }
            
        coder->setPointer(frameStart);
        
        int index = 0;
        
        while (coder->findBits(0x7FF, 11, 8))
        {
            frameTable[index] = (coder->getPointer()- frameStart + 16) >> 3;
            
            coder->adjustPointer(11); // skip start of frame marker

            int version = coder->readBits(2);
            
            samplesPerFrame = frameSizeMP3[version];
            
            if (coder->readBits(2) != 1)
                status = TransformUtil::FormatError;
                
            coder->readBits(1); // crc follows header
            
            int bitRate = bitRates[version][coder->readBits(4)];
            
            if (bitRate == -1)
                status = TransformUtil::FormatError;
            
            sampleRate = samplingRates[version][coder->readBits(2)];
            
            if (sampleRate == -1)
                status = TransformUtil::FormatError;
            
            int padding = coder->readBits(1);
            int reserved = coder->readBits(1);

            numberOfChannels = channelCount[coder->readBits(2)];

            coder->adjustPointer(6); // skip modeExtension, copyright, original and emphasis
            
            samplesPerChannel += samplesPerFrame;
            
            int frameSize = (((version == MPEG1) ? 144 : 72) * bitRate*1000 / sampleRate + padding) - 4;
            
            frameTable[index+1] = 4 + frameSize;
    
            coder->adjustPointer(frameSize << 3);
            index += 2;
        }
        return status;
    }
    
    static const int bitRates[4][16];
    static const int samplingRates[4][4];
    
    int format;

    int numberOfChannels;
    int samplesPerChannel;
    int sampleRate;
    int sampleSize;

    unsigned char* sound;
    size_t soundSize;
    
    int* frameTable;
    unsigned int samplesPerFrame;
};

const int FSSoundConstructorImpl::bitRates[4][16] =
{
    { -1,  8, 16, 24, 32, 40, 48, 56,  64,  80,  96, 112, 128, 144, 160, -1 }, // MPEG 2.5
    { -1, -1, -1, -1, -1, -1, -1, -1,  -1,  -1,  -1,  -1,  -1,  -1,  -1, -1 }, // Reserved
    { -1,  8, 16, 24, 32, 40, 48, 56,  64,  80,  96, 112, 128, 144, 160, -1 }, // MPEG 2.0
    { -1, 32, 40, 48, 56, 64, 80, 96, 112, 128, 160, 192, 224, 256, 320, -1 } // MPEG 1.0
};

const int FSSoundConstructorImpl::samplingRates[4][4] =
{
    { 11025, -1, -1, -1 },
    {    -1, -1, -1, -1 },
    { 22050, -1, -1, -1 },
    { 44100, -1, -1, -1 }
};

extern "C" FSSoundConstructor* SoundConstructor()
{
    return new FSSoundConstructorImpl();
}

}
