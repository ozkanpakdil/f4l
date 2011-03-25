/*
 *  FSMovieEvent.h
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

#ifndef __FSMovieEvent_h__
#define __FSMovieEvent_h__ 1

#include "FSTransform.h"

namespace transform
{
/**
 * The %FSMovieEvent class is a container class for the information generated for events 
 * while a movie is being encoded or decoded.
 */
    class DLL_DECL FSMovieEvent
    {
    public:
        /** Actions indicating whether an object is being encoded or decoded. */
        enum eventAction { Encode, Decode };

        /** The different types of event that will be generated.

        <ul>
        <li>Begin events are generated when an object begins the encoding or decoding process.</li>
        <li>End events are generated when an object finishes the encoding or decoding process.</li>
        <li>Value events are generated when a value (a number or string) is encoded or decoded.</li>
        <li>Error events occur when an object an error occurs.
        </ul>

        */
        enum eventType { Begin, End, Value, Error};

        /** Constructs an FSMovieEvent.
            
            @param anAction whether the event reports an encoding or decoding event.
            @param anEvent the type of event that occurs: BeginObject, EndObject or Field.
            @param aLocation the bit location where the event occurs in the binary Flash data.
            @param aLength the number of bits encoded or decoded.
            @param aType the type of the object that was encoded or decoded.
            @param aValue depends on the type of event generated. For Begin and End events, aValue is a String containing the name of the object being encoded or decoded. For Value events, aValue is an object wrapping the value being decoded. For Error events, aValue is an error message describing the error that occurred.
         */
        FSMovieEvent(int anAction, int anEvent, int aLocation, int aLength, const char* aType, const char* aValue);

        /** Gets the action that generated the event: FSMovieEvent::Encode or FSMovieEvent::Decode.

            @return either FSMovieEvent::Encode or FSMovieEvent::Decode.
            */
        int getAction() const;
    
        /** Gets the type of event that occurred: FSMovieEvent::Begin, FSMovieEvent::End, FSMovieEvent::Value, FSMovieEvent::Error.

            @return the type of event that occurred.
            */
        int getEvent() const;
    
        /** Gets the offset, in number of bits, from the start of the binary data where the current event occurs.

            @return the location in the data stream where the event occurred.
            */
        int getLocation() const;
        
        /** Gets the number of bits involved when encoding or decoding a value to or from the binary data. This is only defined for Value events, it is set to zero for all other types of event.

            @return the number of bits for the value when encoded or decoded as binary data.
            */
        int getLength() const;

        /** Gets the type of the object. For Value events this will be either "int", "float", "double" or "string". For BeginObject or EndObject events this will be wither "array" or the name of the class being encoded or decoded, e.g. "FSBounds".

            @return the type of the object involved in the encoding or decoding process.
            */
        const char* getType() const;
        
        /** Gets the "value" associated with an event.

            <ul>
            <li>For Value events this is a string representation of the data encoded or decoded and the type attribute may be used to convert it to a C++ data type.</li>
            <li>For Error events the "value" is a message that describe the error that occurred.</li>
            <li>For Begin and End events the value is an empty string.</li>
            </ul>

            @return the value of the object involved in the encoding or decoding process.
            */
        const char* getValue() const;

        /** Sets the action that generated the event: FSMovieEvent::Encode or FSMovieEvent::Decode.

            @param anAction either FSMovieEvent::Encode or FSMovieEvent::Decode.
            */
        void setAction(int anAction);
    
        /** Sets the type of event that is occurring: FSMovieEvent::Begin, FSMovieEvent::End, FSMovieEvent::Value, FSMovieEvent::Error.

            @param anEvent the type of event.
            */
        void setEvent(int anEvent);

        /** Sets the offset, in number of bits, from the start of the binary data where the event occurred.

            @param aLocation the bit location in the binary data stream.
            */
        void setLocation(int aLocation);

        /** Sets the number of bits involved when encoding or decoding a value to or from the binary data.

            @param aLength the number of bits encoded or decoded for a value.
            */
        void setLength(int aLength);

        /** Sets the type of the object. For Value events this will be either "int", "float", "double" or "string". For BeginObject or EndObject events this will be wither "array" or the name of the class being encoded or decoded, e.g. "FSBounds".

            @param aType the type of the object that was encoded or decoded.
            */
        void setType(const char* aType);

        /** Sets the value of the object involved in the event or a message if an error event occurred.

            @param aValue a string representation of the value that triggered the event or a message describing an error.
            @see #getValue()
            */
        void setValue(const char* aValue);

    private:
        enum messageSizes { typeSize = 32, valueSize = 256  };
        
        int action;
        int event;

        int location;
        int length;

        char type[typeSize];
        char value[valueSize];
    };
} 

#endif
