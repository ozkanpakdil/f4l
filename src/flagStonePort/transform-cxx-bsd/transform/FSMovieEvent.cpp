/*
 *  FSMovieEvent.cpp
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 10 2003.
 *  Copyright (c) 2001-2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file contains Original Code and/or Modifications of Original Code as defined in
 *  and that are subject to the Flagstone Software Source License Version 1.0 (the
 *  'License'). You may not use this file except in compliance with the License. Please
 *  obtain a copy of the License at http://www.flagstonesoftware.com/licenses/source.html
 *  and read it before using this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an 
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone 
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY 
 *  RIGHTS. Please see the License for the specific language governing rights and limitations 
 *  under the License.
 */

#include "FSMovieEvent.h"

#include <string.h>

using namespace transform;

namespace transform
{
    FSMovieEvent::FSMovieEvent(int anAction, int anEvent, int aLocation, int aLength, const char* aType, const char* aValue) :
        action(anAction),
        event(anEvent),
        location(aLocation),
        length(aLength),
        type(),
        value()
    {
        setType(aType);
        setValue(aValue);
    }

    int FSMovieEvent::getAction() const { return action; }
    int FSMovieEvent::getEvent() const { return event; }

    int FSMovieEvent::getLocation() const { return location; }
    int FSMovieEvent::getLength() const { return length; }

    const char* FSMovieEvent::getType() const { return type; }
    const char* FSMovieEvent::getValue() const { return value; }
        
    void FSMovieEvent::setAction(int anAction)
    {
       action = anAction;
    }
    
    void FSMovieEvent::setEvent(int anEvent)
    {
        event = anEvent;
    }
    
    void FSMovieEvent::setLocation(int aLocation)
    {
        location = aLocation;
    }
    
    void FSMovieEvent::setLength(int aLength)
    {
        length = aLength;
    }
    
    void FSMovieEvent::setType(const char* aType)
    {
        if (aType == 0)
            aType = "";

        strncpy(type, aType, typeSize);
        type[typeSize-1] = '\0';
    }
    
    void FSMovieEvent::setValue(const char* aValue)
    {
        if (aValue == 0)
            aValue = "";

        strncpy(value, aValue, valueSize);
        value[valueSize-1] = '\0';
    }
} 