/*
 * FSSoundConstructor.h
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

#ifndef __FSSoundConstructor_h__
#define __FSSoundConstructor_h__ 1

#include "FSTransformUtil.h"

using namespace transform;

namespace transform
{
    class FSDefineSound;
    class FSSoundStreamHead2;
    class FSSoundStreamBlock;
/** 
 * The FSSoundConstructor class is used to generate the objects used to define and 
 * control the sounds that are played in a Flash movie. The FSSoundConstructor can 
 * be used to generate definitions for:
 *
 * <ul>
 * <li>Event sounds that are played in response to a particular event such as a button 
 * being clicked.</li>
 * <li>Streaming sound that is played as movie is being displayed.</li>
 * </ul>
 *
 * The FSSoundConstructor contains constructors and methods that allow sound data to 
 * be loaded from an external file simplifying the process of adding sound to a movie. 
 * The FSSoundConstructor currently supports uncompressed PCM format (with either 
 * big-endian or little-endian byte ordering) and MP3 format files.
 *
 * Once loaded, the PCM sound data should be compressed to ADPCM format as the relatively 
 * large sizes make PCM coded sounds generally unsuitable for inclusion in a Flash movie. 
 * ADPCM is a compressed format and Flash supports a modified ADPCM algorithm with 
 * compressed samples taking 2, 3, 4 or 5 bits. This results in much smaller file sizes 
 * when a movie is encoded. Code, developed at Centre for Mathematics and Computer Science,
 * Amsterdam, The Netherlands, is available on Flagstone's web site to perform the 
 * ADPCM compression.
 * 
 * For sounds containing more than one channel, the sound levels for each channel are 
 * interleaved for each sample. For example a stereo sound the order of the samples and 
 * channels levels are:
 *
 *\verbatim
 * Sample       0          1          2
 *          +---+---+  +---+---+  +---+---+
 *          | 1 | 2 |  | 1 | 2 |  | 1 | 2 | ....
 *          +---+---+  +---+---+  +---+---+
 *\endverbatim
 *
 * NOTE: The byte order for the PCM data in WAVE sound files may vary according to the 
 * platform on which the sound file was created. The FSSoundConstructor currently only
 * supports WAVE files with little-endian byte order.
 *
 * <b>Examples</b>
 *
 * The following code samples illustrate how to use the FSSoundConstructor class to add 
 * sounds to a Flash file.
 *
 * 1. Playing an uncompressed WAVE file.\n
 *
 *\verbatim
 * int soundId = movie.newIdentifier();
 *
 * // Generate an FSDefineSound object using the attributes defined in the wave file.
 * // An FSSound object is used to instruct the Flash Player to start playing a sound.
 *
 * FSSoundConstructor* soundGenerator = SoundConstructor();
 * 
 * int status = soundGenerator->setSoundFromFile("sound.wav");
 *
 * if (status == TransformUtil::OK)
 * {
 *     movie.add(soundGenerator->defineSound(soundId));
 *     movie.add(new FSSound(soundId, FSSound::Start));
 * }
 * else
 * {
 *     ... Handle Error ...
 * }
 *\endverbatim
 *
 * 2. Streaming Sounds.\n
 *
 * Larger sound files may be streamed to the Flash Player - splitting the sound data into a 
 * sequence of blocks which is synchronized with the frames as they are displayed. Typically 
 * block of sound data is generated for each frame displayed.
 *
 *\verbatim
 * int framesPerSecond = 12;
 *
 * FSSoundConstructor* soundGenerator = SoundConstructor();
 * 
 * int status = soundGenerator->setSoundFromFile("soundTrack.mp3");
 *   
 * if (status == TransformUtil::OK)
 * {
 *     // Calculate the number of decoded sound samples played for each frame
 *     int samplesPerBlock = soundGenerator->getSampleRate() / framesPerSecond;
 *     int numberOfBlocks = soundGenerator->getSamplesPerChannel() / samplesPerBlock;
 *
 *     // An FSSoundStreamHeader2 object defines the attributes of the streaming sound.
 * 
 *     movie.add(soundGenerator->streamHeader(samplesPerBlock));
 *
 *     // Add a streaming block for each frame so the sound is played as each frame is displayed.
 *
 *     for (int i=0; i&lt;numberOfBlocks; i++)
 *     {
 *         movie.add(soundGenerator->streamBlock(i, samplesPerBlock));
 *         movie.add(new FSShowFrame());
 *     }
 * }
 * \endverbatim
 *
 */
class FSSoundConstructor
{
public:
    /** 
     * Accessor method returning the format for the encoded sound data.
     *
     * @return the format of the encoded sound, either FSSound::NATIVE_PCM (platform
     * dependent byte-order), FSSound::PCM (PCM little-endian byte-order) or
     * FSSound::MP3.
     */
    virtual int CALL getFormat() = 0;
    /** 
     * Accessor method returning the number of channels in the sound.
     * 
     * @return the number of sound channels, typically this will be 1 (mono) or 2 (stereo).
     */
    virtual unsigned int CALL getNumberOfChannels() = 0;
    /** 
     * Accessor method returning the number of samples in each channel.
     *
     * @return the number of samples in each channel.
     */
    virtual unsigned int CALL getSamplesPerChannel() = 0;
    /** 
     * Accessor method returning the rate at which the sound will be played. The playback 
     * rate should be a value supported by the Flash Player 5512, 11025, 22050 or 44100 
     * Hertz. 
     *
     * MP3 formatted sounds have playback rates of 11025, 22050 or 44100.
     *
     * @return the playback rate for the sound, either 5512, 11025, 22050 or 44100 Hertz.
     */
    virtual unsigned int CALL getSampleRate() = 0;
    /** 
     * Accessor method returning the number of bytes for each decoded sound sample.
     * 
     * @return the number of bytes in each sample.
     */
    virtual unsigned int CALL getSampleSize() = 0;
    /** 
     * Returns the size of the encoded sound data in bytes.
     * 
     * @return the length of the encoded sound data in bytes.
     */
    virtual size_t CALL getSoundSize() = 0;
    /** 
     * Accessor method returning a copy of the encoded sound data. The buffer 
     * should be large enough to hold the sound and the method returns the 
     * number of bytes written to the buffer.
     * 
     * @param buffer an array where the sound data is copied to.
     * @return the number of bytes copied to the buffer.
     */
    virtual size_t CALL getSound(unsigned char* buffer) = 0;
    /** 
     * Initialises the FSSoundConstructor with the contents of the specified file.
     *
     * The method returns a status code indicating whether the object was initialized 
     * correctly, either TransformUtil::OK, TransformUtil::FileNotFound, TransformUtil::ReadError
     * or TransformUtil::FormatError.
     *
     * @param filename the name of the file containing the image.
     * @return a status code indicating whether the image was loaded successfully.
     */
    virtual int CALL setSoundFromFile(const char* filename) = 0;
    /** 
     * Initialises the FSSoundConstructor with the encoded sound data.
     *
     * The method returns a status code indicating whether the object was initialized 
     * correctly, either TransformUtil::OK or TransformUtil::FormatError.
     *
     * @param bytes an array of bytes containing the encoded image.
     * @param size the number of bytes in the array containing the encoded image.
     */
    virtual int CALL setSound(const unsigned char* bytes, size_t size) = 0;
    /** 
     * Initialises the FSSoundConstructor with the sound data and set of parameters. This method
     * can be used to update the sound following processing for example to convert a stereo sound
     * to mono to reduce the size of the encoded data.
     * 
     * @param encoding the format of the encoded sound either FSSound::PCM, FSSound::ADPCM or FSSound::MP3.
     * @param channelCount the number of sound channels, 1 = mono, 2 = stereo.
     * @param sampleCount the number of samples in each channel.
     * @param samplingRate the rate at which the sound is played in kilohertz. Flash supports 5512, 11025, 22050 or 44100.
     * @param samplingSize the number of bytes for each uncompressed sound sample, either 1 or 2.
     * @param bytes an array of sound samples encoding in the specified format.
     * @param size the number of bytes in the sound samples.
     */
    virtual void CALL setSound(int encoding, unsigned int channelCount, unsigned int sampleCount, unsigned int samplingRate, unsigned int samplingSize, const unsigned char* bytes, size_t size) = 0;
    /** 
     * Generates an FSDefineSound object from the sound data. The FSDefineSound object is 
     * created using the encoded sound data so if the sound was decoded in order to change 
     * the number of channels, sample rate or sample size it must be re-encoded.
     * 
     * @param anIdentifier a unique identifier for the FSDefineSound object.
     * 
     * @return an FSDefineSound object initialised with the encoded sound data.
     */
    virtual FSDefineSound* CALL defineSound(int anIdentifier) = 0;
    /** 
     * Generates an FSSoundStreamHead2 object to stream the sound data to the Flash Player.
     * 
     * @param samplesPerBlock the number of samples in each subsequent FSSoundStreamBlock 
     * object.
     * 
     * @return an FSDefineSound object initialised with the encoded sound data.
     */
    virtual FSSoundStreamHead2* CALL streamHeader(unsigned int samplesPerBlock) = 0;
    /** 
     * Generates an FSSoundStreamBlock object containing a block sound data. This method is 
     * used to divide the encoded sound into a sequence of blocks to allow a sound to be 
     * streamed to the Flash Player.
     *
     * If the number of samples in the last block to stream is less than the samplesPerBlock,
     * the size of the FSSoundStreamBlock object is reduced accordingly. It is not padded 
     * to maintain the specified length.
     * 
     * @param blockNumber the nth block of samples.
     * 
     * @param samplesPerBlock the number of samples to stream.
     * 
     * @return an FSSoundStreamBlock object containing a block of bytes from the encoded 
     * sound.
     */
    virtual FSSoundStreamBlock* CALL streamBlock(unsigned int blockNumber, unsigned int samplesPerBlock) = 0;
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
            FSSoundConstructor* constructor = static_cast<FSSoundConstructor*>(p);
            constructor->destroy();
        }
    }
};
/**
 * Factory function for creating an FSSoundConstructor object.
 */
extern "C" FSSoundConstructor* SoundConstructor();
}
#endif // __FSSoundConstructor_h__
