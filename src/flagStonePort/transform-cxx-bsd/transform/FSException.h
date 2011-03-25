/*
 *  FSAssertion.h
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

#ifndef __FSException_h__
#define __FSException_h__ 1

#include <string.h>

#include "FSTransform.h"

namespace transform
{
    /** FSException is the base class for the exceptions used in the library. Classes derived from this base class are used to create different categories of exceptions. Each exception contains a message describing the circumstances which caused the exception to be thrown.

    @author  Stuart MacKay
    */
    class DLL_DECL FSException
    {
public:
        /** Constructor for an exception. The string argument is used to provide information about the exception - in addition to the type of exception thrown.

            @param msg a string describing the exception.
        */
        FSException(const char* msg)
        {
            message = new char[strlen(msg)+1];
            strcpy(message, msg);
        }

       /** Copy constructor for an exception.

            @param rhs an exception object.
        */
        FSException(const FSException& rhs)
        {
            message = new char[strlen(rhs.message)+1];
            strcpy(message, rhs.message);
        }

        ~FSException()
        {
            delete [] message;
        }

        /** Returns the message describing the exception.

            @return a string describing the exception.
        */
        const char* what() const 
        { 
            return message; 
        }

private:
        char* message;
    };

    /** FSNullPointerException is used to report errors when encountering a null pointer.

        @author  Stuart MacKay
        */
    class DLL_DECL FSNullPointerException : public FSException
    {
public:
        /** Constructs an exception with the message describing the circumstances in which the exception was thrown.

            @param msg a string describing why the exception was thrown.
            */
        FSNullPointerException(const char* msg) : FSException(msg) {}
    };

    /** FSAllocationException is used to report errors when dynamically allocating memory.

        @author  Stuart MacKay
        */
    class DLL_DECL FSAllocationException : public FSException
    {
public:
        /** Constructs an exception with the message describing the circumstances in which the exception was thrown.

            @param msg a string describing why the exception was thrown.
            */
        FSAllocationException(const char* msg) : FSException(msg) {}

        /** Constructs an exception with a default message defined.

            */
        FSAllocationException() : FSException("Cannot allocate memory") {}
    };

    /** FSIllegalArgumentException is used to report errors in arguments supplied in a member function.

        @author  Stuart MacKay
        */
    class DLL_DECL FSIllegalArgumentException : public FSException
    {
public:
        /** Constructs an exception with the message describing the circumstances in which the exception was thrown.

        @param msg a string describing why the exception was thrown.
        */
        FSIllegalArgumentException(const char* msg) : FSException(msg) {}
    };

    /** FSFileOpenException is used to report errors when opening a file for reading or writing.

        @author  Stuart MacKay
        */
    class DLL_DECL FSFileOpenException : public FSException
    {
public:
        /** Constructs an exception with the message describing the circumstances in which the exception was thrown.

        @param msg a string describing why the exception was thrown.
        */
        FSFileOpenException(const char* msg) : FSException(msg) {}
    };

    /** FSAccessException is used to report errors when reading or writing data from a file.

        @author Stuart MacKay
        */
    class DLL_DECL FSAccessException : public FSException
    {
public:
        /** Constructs an exception with the message describing the circumstances in which the exception was thrown.

        @param msg a string describing why the exception was thrown.
        */
        FSAccessException(const char* msg) : FSException(msg) {}
    };

    /** FSFormatException is used to report an error when the contents of a file is not in the expected format.

        @author Stuart MacKay
        */
    class DLL_DECL FSFormatException : public FSException
    {
public:
        /** Constructs an exception with the message describing the circumstances in which the exception was thrown.

        @param msg a string describing why the exception was thrown.
        */
        FSFormatException(const char* msg) : FSException(msg) {}
    };

    /** FSValidationException is used to report an error when validating an object.

        @author Stuart MacKay
        */
    class DLL_DECL FSValidationException : public FSException
    {
public:
        /** Constructs an exception with the message describing the circumstances in which the exception was thrown.

        @param msg a string describing why the exception was thrown.
        */
        FSValidationException(const char* msg) : FSException(msg) {}
    };

    /** FSIndexOutOfBoundsException is used to errors when accessing elements in an indexed data structure.

        @author Stuart MacKay
        */
    class DLL_DECL FSIndexOutOfBoundsException : public FSException
    {
public:
        /** Constructs an exception with the message describing the circumstances in which the exception was thrown along with the index of the element and the size of the structure being accessed.

            @param msg a string describing why the exception was thrown.
            @param anIndex the index of the element being accessed.
            @param aSize the number of the elements in the structure.
            */
        FSIndexOutOfBoundsException(const char* msg, int anIndex, int aSize) : FSException(msg), index(anIndex), size(aSize) {}

        /** Accessor method returns the index of the element being accessed when the exception was thrown.

            @return the index of the element being accessed.
            */
        int getIndex() const { return index; }

        /** Accessor method returns the size of the structure being accessed when the exception was thrown.

            @return the size of the structure being accessed.
        */
        int getSize() const  { return size; }

private:
        int index;
        int size;
    };

    /** FSArrayIndexOutOfBoundsException is used to errors when accessing elements in an array.

        @author Stuart MacKay
        */
    class DLL_DECL FSArrayIndexOutOfBoundsException : public FSIndexOutOfBoundsException
    {
public:
        /** Constructs an exception reporting the index of the element and the size of the array being accessed.

            @param anIndex the index of the element being accessed.
            @param aSize the number of the elements in the structure.
            */
        FSArrayIndexOutOfBoundsException(int anIndex, int aSize) : FSIndexOutOfBoundsException("Array index out of bounds", anIndex, aSize) {}
    };

    /** FSStringIndexOutOfBoundsException is used to errors when accessing elements in a string.

        @author Stuart MacKay
        */
    class DLL_DECL FSStringIndexOutOfBoundsException : public FSIndexOutOfBoundsException
    {
public:
        /** Constructs an exception reporting the index of the character and the size of the string being accessed.

        @param anIndex the index of the character being accessed.
        @param aSize the length of the string.
        */
        FSStringIndexOutOfBoundsException(int anIndex, int aSize) : FSIndexOutOfBoundsException("String index out of bounds", anIndex, aSize) {}
    };
}

#endif // __FSException_h__
