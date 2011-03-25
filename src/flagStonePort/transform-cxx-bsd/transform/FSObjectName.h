/*
 *  FSObjectName.h
 *  Transform SWF
 *
 *  Created by Stuart MacKay on Thu Mar 13 2003.
 *  Copyright (c) 2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file is part of the Transform SWF library. You may not use this file except in
 *  compliance with the terms of the license (the 'License')that accompanied this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY
 *  RIGHTS. Please see the License for the specific language governing rights and limitations
 *  under the License.
 */

#ifndef __FSOBJECTNAME_H__
#define __FSOBJECTNAME_H__ 1

#include "FSString.h"

namespace transform
{
    /** The FSObjectName class is a simple data structure that is used to associated the unique identifier for an object with a name. It is used in the FSImport and FSExport classes.

        @see FSImport
        @see FSExport
        */
    class DLL_DECL FSObjectName
    {
    public:
        FSObjectName() : identifier(0), name("") {}

        /** Constructs and FSObjectName object associating the object with the identifier with a name.

            @param anIdentifier the identifier of the object to be exported.
            @param aString the name assigned to the exported object.
            */
        FSObjectName(int anIdentifier, const char* aString) : identifier(anIdentifier), name(aString) {}
    
        int identifier;
        FSString name;
    };
}

#endif
