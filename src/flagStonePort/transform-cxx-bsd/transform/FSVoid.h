/*
 *  FSVoid.h
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

#ifndef __FSVoid_h__
#define __FSVoid_h__ 1

#include "FSValue.h"

namespace transform
{
/**
 * %FSVoid is a lightweight object that is used solely to allow void values to be pushed 
 * onto the Flash Player stack by the %FSPush class.
 * 
<h1 class="datasheet">History</h1>

<p>The FSVoid class represents the Void data type from the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 5.</p>


 */  
    class DLL_DECL FSVoid : public FSValue
    {
public:
        FSVoid(FSInputStream* aStream);
        
        /** Constructs an FSVoid object.
            */
        FSVoid() : FSValue(FSValue::Void) {}

        FSVoid* clone() const { return new FSVoid(*this); }

        const char* className() const;

        int length() const { return 2; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
    };
} 

#endif
