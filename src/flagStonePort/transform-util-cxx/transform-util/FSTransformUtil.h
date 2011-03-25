/*
 * FSTransformUtil.h
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

#ifndef __FSTransformUtil_h__
#define __FSTransformUtil_h__ 1

#ifdef WIN32
#  define CALL __stdcall
#else
#  define CALL
#endif

#include <stdlib.h>

namespace transform
{
/** 
 * The TransformUtil class defines constants that are used throughout the package.
 */
class TransformUtil
{
public:
    /**
     * The Status enumeration is used to define the status codes returned by the 
     * methods used to initialize objects with contents of files, etc. The codes 
     * are used to handle error conditions without resorting to throwing exceptions.
     */
    enum Status {
        /**
         * The operation was completed successfully.
         */
        OK,
        /**
         * A file not found error is reported when the specified file cannot be opened.
         */
        FileNotFound,
        /**
         * A read error is reported when an error occurs while reading a file.
         */
        ReadError,
        /**
         * A format error is reported when attempting to process data in a format not 
         * supported.
         */
        FormatError
    };

		/** 
		 * MAJOR is used to identify the current version of the framework
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
};

} 

#endif
