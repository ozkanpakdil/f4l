/*
 *  FSDefineMovieClip.cpp
 *  Transform SWF
 *
 *  Created by smackay on Fri Mar 28 2003.
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

#include "FSDefineMovieClip.h"

#include "FSMovie.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"

namespace transform
{
    FSDefineMovieClip::FSDefineMovieClip(FSInputStream* aStream) :
        FSDefineObject(DefineMovieClip, 0),
        objects()
    {
        decodeFromStream(aStream);
    }

    FSDefineMovieClip::FSDefineMovieClip(const FSDefineMovieClip& rhs) :
        FSDefineObject(rhs),
        objects(rhs.objects.size())
    {
        int index = 0;

        for (FSVector<FSMovieObject*>::const_iterator i = rhs.objects.begin(); i != rhs.objects.end(); i++, index++)
            objects[index] = (*i)->clone();
    }
    
    FSDefineMovieClip::~FSDefineMovieClip()
    {
        for (FSVector<FSMovieObject*>::iterator i = objects.begin(); i != objects.end(); i++)
        {
            delete *i;
            *i = 0;
        }
    }
    
    const char* FSDefineMovieClip::className() const
    {
        const static char _name[] = "FSDefineMovieClip";
    
        return _name;
    }
    
    FSDefineMovieClip& FSDefineMovieClip::operator= (const FSDefineMovieClip& rhs)
    {
        if (this != &rhs)
        {
            this->FSDefineObject::operator=(rhs);
    
            for (FSVector<FSMovieObject*>::iterator i = objects.begin(); i != objects.end(); i++)
            {
                delete *i;
                *i = 0;
            }
    
            objects = FSVector<FSMovieObject*>(rhs.objects.size());
    
            int index = 0;
    
            for (FSVector<FSMovieObject*>::const_iterator i = rhs.objects.begin(); i != rhs.objects.end(); i++, index++)
                objects[index] = (*i)->clone();
        }
        return *this;
    }

    void FSDefineMovieClip::add(const FSVector<FSMovieObject*>& anArray)
    {
        for (FSVector<FSMovieObject*>::const_iterator i = anArray.begin(); i != anArray.end(); i++)
            objects.push_back(*i);
    }

    int FSDefineMovieClip::getFrameCount()
    {
        int numberOfFrames = 0;

        for (FSVector<FSMovieObject*>::const_iterator i = objects.begin(); i != objects.end(); i++)
        {
            if ((*i)->getType() == ShowFrame)
                numberOfFrames++;
        }
        return numberOfFrames;
    }

    int FSDefineMovieClip::lengthInStream(FSOutputStream* aStream)
    {
        FSDefineObject::lengthInStream(aStream);
            
        length += 4; // Includes End;

        for (FSVector<FSMovieObject*>::const_iterator i = objects.begin(); i != objects.end(); i++)
        {
            int objectLength = (*i)->lengthInStream(aStream);
            
            length += ((*i)->getExtendLength() || objectLength >= 63) ? objectLength+6 : objectLength+2;
        }
        return length;
    }
    
    void FSDefineMovieClip::encodeToStream(FSOutputStream* aStream)
    {
        aStream->startEncoding(className());
        FSDefineObject::encodeToStream(aStream);
        
        aStream->write(getFrameCount(), FSStream::UnsignedWord, 16);
    
#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSMovieObject*>::const_iterator i = objects.begin(); i != objects.end(); i++)
            (*i)->encodeToStream(aStream);

        aStream->write(0, FSStream::UnsignedWord, 16); // End

#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
        aStream->endEncoding(className());
    }
    
    void FSDefineMovieClip::decodeFromStream(FSInputStream* aStream)
    {
        FSMovieObject* currentObject = 0;

        aStream->startDecoding(className());
        FSDefineObject::decodeFromStream(aStream);

        aStream->read(FSStream::UnsignedWord, 16); // frame count
    
#ifdef _DEBUG
        aStream->startDecoding("array");
#endif
        while ((currentObject = FSMovie::objectFromStream(aStream)) != 0)
            objects.push_back(currentObject);

#ifdef _DEBUG
        aStream->endDecoding("array");
#endif
        aStream->endDecoding(className());

    }
    
}
