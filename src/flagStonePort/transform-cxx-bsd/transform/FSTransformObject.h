/*
 *  FSTransformObject.h
 *  Transform SWF
 *
 *  Created by smackay on Mon Feb 10 2003.
 *  Copyright (c) 2001-2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file is part of the Transform SWF library. You may not use this file except in
 *  compliance with the terms of the license (the 'License') that accompanied this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY
 *  RIGHTS. Please see the License for the specific language governing rights and limitations
 *  under the License.
 */

#ifndef __FSTransformObject_h__
#define __FSTransformObject_h__ 1

#include "FSTransform.h"

namespace transform
{
    class FSInputStream;
    class FSOutputStream;
    
/** 
 * The %FSTransformObject object defines the basic set of method that an object must implement 
 * if it can used to represent the data structures that make up the Flash File Format
 * specification.
 * 
 * Sub-classes can be used to represent either one of the tagged data structures 
 * such as PlaceObject and added directly to an FSMovie or one of the data-types
 * that the objects contain e.g. a colour.
 *
 * In addition to the methods directly relating to the coding of the object to and from the 
 * binary data representation that comprises the Flash File Format specification the class
 * also includes a common set of methods used when validating or reporting the state of 
 * individual objects.
 */
    class DLL_DECL FSTransformObject
    {
public:
        virtual ~FSTransformObject() {};

        /** Returns the name of the class. This method is used to report the class involved when a movie event is generated.

            @return a C string containing the name of the class.
            */
        virtual const char* className() const = 0;

        /** Creates a deep copy of this object. The object is dynamically allocated and ownership of the object is assumed by the code requesting the clone.

            @return a pointer to the cloned object.
            */
        virtual FSTransformObject* clone() const = 0;

        virtual int  lengthInStream(FSOutputStream* aStream) = 0;
        virtual void encodeToStream(FSOutputStream* aStream) = 0;
        virtual void decodeFromStream(FSInputStream* aStream) = 0;
    };
} 

#endif
