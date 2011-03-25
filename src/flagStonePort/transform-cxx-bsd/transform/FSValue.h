/*
 *  FSValue.h
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

#ifndef __FSValue_h__
#define __FSValue_h__ 1

#include "FSTransformObject.h"

namespace transform
{
    /** FSValue is the base class for a series of classes that will used to wrap basic data types so they can be pushed onto the Flash Player's stack using the FSPush class.

    This class is primarily used internally in the library however the getType() method is invaluable when manipulating decoded Flash files. Rather than use dynamic casting provided by the C++ environment the method can be used to identify the class, derived from FSValue, that represents each data type.

    @see FSPush
    */
    class DLL_DECL FSValue : public FSTransformObject
    {
public:
        /** valueType defines the different data types that can be used with the FSPush class. The values are used by the derived wrapper classes to identify the different data types when the respective class is encoded.
        */
        enum valueType { String = 0, Property = 1, Null = 2, Void = 3, RegisterIndex = 4, Boolean = 5, Double = 6, Integer = 7, TableIndex = 8 };

        FSValue(FSInputStream* aStream);

        FSValue(int aType) : type(aType) {}

        virtual FSValue* clone() const = 0;

        FSValue& operator= (const FSValue& rhs);
        
        virtual int length() const = 0;

        /** Returns the valueType that identifies the data type when the object is encoded.

            @return a value form the valueType enumeration.
            */
        int getType() const { return type; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

protected:
        int type;
    };
} 

#endif
