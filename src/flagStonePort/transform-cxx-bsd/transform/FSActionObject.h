/*
 *  FSActionObject.h
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

#ifndef __FSActionObject_h__
#define __FSActionObject_h__ 1

#include "FSTransformObject.h"

namespace transform
{
/** The %FSActionObject is a base class for the classes that represent the different types 
 * of actions defined in the Flash file format specification. The function of the class 
 * is the same as the FSMovieObject class however the format of the encoded binary data 
 * is different.
 * 
 * This class is primarily used internally in the library however the getType() method is 
 * useful when manipulating decoded Flash files. Rather than use run-time type inspection 
 * provided by the programming environment the method can be used to identify the action that a 
 * given object represents. The getType() method is essential when examining FSAction objects
 * which represent a large number byte-codes which perform stack-based operations such as 
 * add, subtract, etc.
 */
    class DLL_DECL FSActionObject : public FSTransformObject
    {
public:
        /** Definition of the different types of action that contain the arguments they required for execution by the Flash Player. Types of stack based actions are defined in the FSAction class.
        */
        enum actionType { 
            GotoFrame = 129, 
            GetUrl = 131, 
            RegisterCopy = 135, 
            Table = 136, 
            WaitForFrame = 138, 
            SetTarget = 139, 
            GotoLabel = 140, 
            WaitForFrame2 = 141, 
// Flash 7
            NewFunction2 = 142,
            ExceptionHandler = 143,
// End Flash 7
            With = 148, 
            Push = 150, 
            Jump = 153, 
            GetUrl2 = 154, 
            NewFunction = 155, 
            If = 157, 
            Call = 158, 
            GotoFrame2 = 159
        };

        FSActionObject(int aType) : type(aType), length(0) {}

        FSActionObject(const FSActionObject& rhs);

        virtual FSActionObject* clone() const = 0;

        FSActionObject& operator= (const FSActionObject& rhs);

        /** Gets the code used that identifies the type of the action when it is encoded. 

            @return the code used to denote the type of action performed.
            */
        int getType() const { return type; }

        /** Returns the number of bytes that was decoded from the binary data. Once the attributes of an action have changed the value returned by this method will not be accurate.

            @return the length of the decoded action.
            */
        int getLength() const { return length; }
        
        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

protected:
        int type;
        int length;
    };
} 

#endif
