/*
 *  FSTransform.h
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

#ifndef __FSTransform_h__
#define __FSTransform_h__ 1

#ifdef WIN32
#  ifdef TRANSFORM_DLL
#      ifdef TRANSFORM_EXPORT
#          define DLL_DECL __declspec(dllexport)
#          define DLL_TEMPLATE
#      else
#          define DLL_DECL __declspec(dllimport)
#          define DLL_TEMPLATE extern
#      endif
#  else
#      define DLL_DECL
#      define DLL_TEMPLATE
#  endif
#else
#  define DLL_DECL
#  define DLL_TEMPLATE
#endif

#include <stdlib.h>

typedef unsigned char byte;

namespace transform
{
    /** 
       The Transform class defines constants and utility methods that are used throughout 
       the Transform package.

    @author  Stuart MacKay
    */
    class DLL_DECL Transform
    {
public:
        /** VERSION is used to identify the version of Flash that the package supports. */
        static const int VERSION = 7;
		/** 
		 * MAJOR is used to identify the current version of the framework. This
		 * is incremented for each new version of Flash supported.
		 */
		static const int MAJOR = 2;
		/** 
		 * MINOR is used to identify the current minor version of the framework. This
	 	 * is incremented when new functionality is added or API changes are made.
		 */
		static const int MINOR = 0;
		/** 
		 * The RELEASE number is used to differentiate between different releases. 
		 * This number is incremented when an enhancement or bug fix has been made 
		 * and the API is unchanged.
		*/
		static const int RELEASE = 3;

        /** VALUE_NOT_SET is used to signify that a field has not yet assigned a value. Some Flash tags contain optional fields to reduce the size of the binary data when a tag is encoded. These fields are only encoded if they have been assigned a valid value. The range of valid values will depend on the number of bits used to encode the field and whether it is a signed or unsigned value. VALUE_NOT_SET was chosen to be the largest negative integer - since the largest optional field is 16-bits in length and thus no confusion will result.
            */
        static const int VALUE_NOT_SET = -2147483647;
    };

    byte* dataFromFile(const char* filename, size_t& size);
    byte* zip(const byte* bytes, size_t size, size_t offset, size_t& compressedSize);
    byte* unzip(const byte* bytes, size_t size, size_t& uncompressedSize);
} 

#endif
