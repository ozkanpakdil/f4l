/*
 *  FSMovieListener.h
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

#ifndef __FSMovieListener_h__
#define __FSMovieListener_h__ 1

#include "FSMovieEvent.h"

namespace transform
{
/**
 * The %FSMovieListener interface defines the methods required to register an object to 
 * receive event information from an %FSMovie object as it encodes and decodes Flash 
 * movies.
 */
    class DLL_DECL FSMovieListener
    {
public:
        virtual ~FSMovieListener() {};
        
        /** logEvent is used report the FSMovieEvents that are generated when Flash data is encoded or decoded.

        @param anEvent the movie event generated by an FSMovie object.
        */
        virtual void logEvent(FSMovieEvent anEvent) = 0;
    };
} 
#endif
