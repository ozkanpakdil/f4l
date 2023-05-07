/*
 *  FSMovie.cpp
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

#include "FSMovie.h"

#include <stdlib.h>
#include <stdio.h>
#include <zlib.h>

#include "FSMovieObject.h"
#include "FSDefineObject.h"
#include "FSActionObject.h"
#include "FSInputStream.h"
#include "FSOutputStream.h"
#include "FSMovieEvent.h"
#include "FSMovieListener.h"

#include "FSUnknownAction.h"
#include "FSUnknownObject.h"

#include "FSAction.h"
#include "FSGetUrl.h"
#include "FSGotoFrame.h"

#include "FSSetBackgroundColor.h"
#include "FSRemoveObject.h"
#include "FSPlaceObject.h"
#include "FSDoAction.h"
#include "FSShowFrame.h"

#include "FSShape.h"

#include "FSFillStyle.h"
#include "FSSolidFill.h"
#include "FSBitmapFill.h"
#include "FSGradientFill.h"

#include "FSDefineShape.h"

#include "FSJPEGEncodingTable.h"
#include "FSDefineJPEGImage.h"

#include "FSDefineButton.h"

#include "FSStartSound.h"
#include "FSDefineSound.h"
#include "FSSoundStreamBlock.h"
#include "FSSoundStreamHead.h"

#include "FSDefineFont.h"
#include "FSFontInfo.h"

#include "FSDefineText.h"

// SWF5
#include "FSPush.h"
#include "FSGetUrl2.h"
#include "FSGotoFrame2.h"
#include "FSIf.h"
#include "FSJump.h"
#include "FSWith.h"
#include "FSCall.h"
#include "FSTable.h"
#include "FSWaitForFrame.h"
#include "FSWaitForFrame2.h"
#include "FSRegisterCopy.h"
#include "FSNewFunction.h"
#include "FSGotoLabel.h"
#include "FSSetTarget.h"

#include "FSPlaceObject2.h"
#include "FSRemoveObject2.h"
#include "FSFrameLabel.h"
#include "FSDefineMovieClip.h"
#include "FSFree.h"
#include "FSPathsArePostscript.h"
#include "FSSerialNumber.h"
#include "FSPointer.h"
#include "FSImport.h"
#include "FSExport.h"
#include "FSProtect.h"
#include "FSEnableDebugger.h"
#include "FSQuicktimeMovie.h"

#include "FSMorphSolidFill.h"
#include "FSMorphBitmapFill.h"
#include "FSMorphGradientFill.h"
#include "FSMorphGradient.h"

#include "FSDefineShape2.h"
#include "FSDefineShape3.h"
#include "FSDefineMorphShape.h"

#include "FSButtonColorTransform.h"
#include "FSButtonSound.h"
#include "FSDefineButton2.h"

#include "FSDefineJPEGImage2.h"
#include "FSDefineJPEGImage3.h"
#include "FSDefineImage.h"
#include "FSDefineImage2.h"

#include "FSDefineFont2.h"

#include "FSDefineText2.h"
#include "FSDefineTextField.h"

#include "FSSoundStreamHead2.h"

// SWF6
#include "FSInitialize.h"
#include "FSDefineVideo.h"
#include "FSVideoFrame.h"
#include "FSFontInfo2.h"
#include "FSEnableDebugger2.h"

// SWF7
#include "FSLimitScript.h"
#include "FSTabOrder.h"
#include "FSNewFunction2.h"
#include "FSExceptionHandler.h"

using namespace transform;

namespace transform
{
    FSMovie::FSMovie() :
        identifier(0),
        version(Transform::VERSION),
        frameSize(),
        frameRate(0),
        objects()
    {
        signature[0] = (version > 5) ? 'C' : 'F';
        signature[1] = 'W';
        signature[2] = 'S';
    }

    FSMovie::FSMovie(const FSBounds& aBounds, float framesPerSecond) :
        identifier(0),
        version(Transform::VERSION),
        frameSize(aBounds),
        frameRate(framesPerSecond),
        objects()
    {
        signature[0] = (version > 5) ? 'C' : 'F';
        signature[1] = 'W';
        signature[2] = 'S';
    }
    
    FSMovie::FSMovie(const FSBounds& aBounds, float framesPerSecond, const FSVector<FSMovieObject*>& anArray) :
        identifier(0),
        version(Transform::VERSION),
        frameSize(aBounds),
        frameRate(framesPerSecond),
        objects(anArray)
    {
        signature[0] = (version > 5) ? 'C' : 'F';
        signature[1] = 'W';
        signature[2] = 'S';
    }

    FSMovie::FSMovie(char* aSignature, int aVersion, const FSBounds& aBounds, float framesPerSecond, const FSVector<FSMovieObject*>& anArray) :
        identifier(0),
        signature(),
        version(aVersion),
        frameSize(aBounds),
        frameRate(framesPerSecond),
        objects(anArray)
    {
        strncpy(signature, aSignature, 3);
    }

    FSMovie::FSMovie(const char* fileName): 
        identifier(0),
        version(Transform::VERSION),
        frameSize(),
        frameRate(0.0),
        objects()
    {
        decodeFromFile(fileName);
    }
    
    FSMovie::FSMovie(const byte* data, size_t numberOfBytes):
        identifier(0),
        version(Transform::VERSION),
        frameSize(),
        frameRate(0.0),
        objects()
    {
        decodeFromData(data, numberOfBytes);
    }

    FSMovie::FSMovie(const FSMovie& rhs) :
        identifier(rhs.identifier),
        version(rhs.version),
        frameSize(rhs.frameSize),
        frameRate(rhs.frameRate),
        objects(rhs.objects.size())
    {
        for (FSVector<FSMovieObject*>::iterator i = objects.begin(); i != objects.end(); ++i)
        {
            delete *i;
            *i = 0;
        }

        int index = 0;

        for (FSVector<FSMovieObject*>::const_iterator i = rhs.objects.begin(); i != rhs.objects.end(); i++, index++)
            objects[index] = (*i)->clone();
    }
    
    FSMovie::~FSMovie()
    {
        for (FSVector<FSMovieObject*>::iterator i = objects.begin(); i != objects.end(); ++i)
        {
            delete *i;
            *i = 0;
        }
    }

    FSMovie& FSMovie::operator= (const FSMovie& rhs)
    {
        if (this != &rhs)
        {
            identifier = rhs.identifier;
            
            strncpy(signature, rhs.signature, 3);
            
            version = rhs.version;
            frameSize = rhs.frameSize;
            frameRate = rhs.frameRate;

            for (FSVector<FSMovieObject*>::iterator i = objects.begin(); i != objects.end(); ++i)
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

    FSMovie* FSMovie::clone() const
    {
        return new FSMovie(*this);
    }

    int FSMovie::newIdentifier() 
    { 
        return ++identifier; 
    }
    
    int FSMovie::getIdentifier() const
    {
        return identifier;
    }

    int FSMovie::getVersion()
    {
        return version;
    }
    
    FSBounds& FSMovie::getFrameSize()
    {
        return frameSize;
    }
    
    float FSMovie::getFrameRate()
    {
        return frameRate;
    }
    
    void FSMovie::setIdentifier(int aValue)
    {
        identifier = aValue;
    }

    void FSMovie::setVersion (int aNumber)
    {
        version = aNumber;
    }
    
    void FSMovie::setFrameSize (const FSBounds& aBounds)
    {
        frameSize = aBounds;
    }
    
    void FSMovie::setFrameRate (float aNumber)
    {
        frameRate = aNumber;
    }
    
    FSVector<FSMovieObject*>& FSMovie::getObjects()
    {
        return objects;
    }
    
    void FSMovie::add(FSMovieObject* anObject) 
    {
        objects.push_back(anObject);
    }
    
    void FSMovie::add(const FSVector<FSMovieObject*>& anArray) 
    {
        for (FSVector<FSMovieObject*>::const_iterator i = anArray.begin(); i != anArray.end(); ++i)
            objects.push_back(*i);
    }
    
    void FSMovie::setObjects(const FSVector<FSMovieObject*>& anArray)
    {
        objects = anArray;
    }
    
    int FSMovie::getFrameCount() const
    {
        int numberOfFrames = 0;

        for (FSVector<FSMovieObject*>::const_iterator i = objects.begin(); i != objects.end(); ++i)
        {
            if ((*i)->getType() == FSMovieObject::ShowFrame)
                numberOfFrames += 1;
        }
        return numberOfFrames;
    }

    void FSMovie::decodeFromFile(const char* fileName)
    {
        size_t size = 0;
        byte* bytes = dataFromFile(fileName, size);

        _decode(bytes, size);
    }
    
    void FSMovie::decodeFromFile(const char* fileName, FSMovieListener* listener)
    {
        size_t size = 0;
        byte* bytes = NULL;
            
        try 
        {
            bytes = dataFromFile(fileName, size);
            _decode(bytes, size, listener);
        }
        catch (FSFileOpenException)
        {
            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Decode, FSMovieEvent::Error, 0, 0, "", "Cannot open file"));
        }
        catch (FSAccessException)
        {
            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Decode, FSMovieEvent::Error, 0, 0, "", "Cannot read file"));
        }
    }
    
    void FSMovie::decodeFromData(const byte* bytes, size_t numberOfBytes)
    {
        if ((bytes[0] == 'F' || bytes[0] == 'C') && bytes[1] == 'W' && bytes[2] == 'S' != true)
            throw FSFormatException("Not Flash format");

        _decode(bytes, numberOfBytes);
    }

    void FSMovie::decodeFromData(const byte* bytes, size_t numberOfBytes, FSMovieListener* listener)
    {
        if ((bytes[0] == 'F' || bytes[0] == 'C') && bytes[1] == 'W' && bytes[2] == 'S' != true)
        {
            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Decode, FSMovieEvent::Error, 0, 0, "", "Not Flash format"));
            return;
        }

        _decode(bytes, numberOfBytes, listener);
    }

    void FSMovie::encodeToFile(const char* fileName)
    {
        FILE* output = 0;
        byte* buffer = 0;
        size_t length = 0;

        if ((output = fopen(fileName, "wb")) == 0)
            throw FSFileOpenException("Cannot open file");

        buffer = _encode(length);

        if (fwrite(buffer, 1, length, output) != length)
            throw FSAccessException("Cannot write to file");

        if (fclose(output) != 0)
            throw FSAccessException("Cannot write to file");

        delete [] buffer;
    }
    
    void FSMovie::encodeToFile(const char* fileName, FSMovieListener* listener)
    {
        FILE* output = 0;
        byte* buffer = 0;
        size_t length = 0;

        if ((output = fopen(fileName, "wb")) == 0)
        {
            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Decode, FSMovieEvent::Error, 0, 0, "", "Cannot open file"));
            return;
        }

        buffer = _encode(length, listener);

        if (fwrite(buffer, 1, length, output) != length)
        {
            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Decode, FSMovieEvent::Error, 0, 0, "", "Cannot write to file"));
        }

        if (fclose(output) != 0)
        {
            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Decode, FSMovieEvent::Error, 0, 0, "", "Cannot write to file"));
        }
        delete [] buffer;
    }
    
    byte* FSMovie::encode(size_t& length)
    {
        return _encode(length);
    }

    void FSMovie::encodeToStream(FSMovieObject* anObject, FSOutputStream* aStream)
    {
        int length = anObject->getLength();
        int start = aStream->getCursor() + ((anObject->getExtendLength() || length >= 63) ? 48 : 16);
        int next = start + (length << 3);

        anObject->encodeToStream(aStream);

        int delta = (next - aStream->getCursor()) >> 3;

        if (delta != 0)
        {
            FSMovieListener* listener = aStream->getListener();

            char str[64];
            
            if (delta > 0)
                sprintf(str, "%s underflowed by %d bytes.", anObject->className(), delta);
            else
                sprintf(str, "%s overflowed by %d bytes.", anObject->className(), -delta);
            
            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Encode, FSMovieEvent::Error, 0, 0, "", str));
            else
                throw FSFormatException(str);
        }
        aStream->setCursor(next);
    }

    void FSMovie::encodeToStream(FSActionObject* anObject, FSOutputStream* aStream)
    {
        int length = anObject->getLength();
        int start = aStream->getCursor() + ((anObject->getType() > 128) ? 24 : 8);
        int next = start + (length << 3);

        anObject->encodeToStream(aStream);

        int delta = (next - aStream->getCursor()) >> 3;

        if (delta != 0)
        {
            FSMovieListener* listener = aStream->getListener();

            char str[64];
            
            if (delta > 0)
                sprintf(str, "%s underflowed by %d bytes.", anObject->className(), delta);
            else
                sprintf(str, "%s overflowed by %d bytes.", anObject->className(), -delta);
            
            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Encode, FSMovieEvent::Error, 0, 0, "", str));
            else
                throw FSFormatException(str);
        }
        aStream->setCursor(next);
    }

    FSMovieObject* FSMovie::objectFromStream(FSInputStream* aStream)
    {
        FSMovieObject* currentTag = 0;

        int start = aStream->getCursor();
        int word = aStream->scan(FSStream::UnsignedWord, 16);
        int type = word >> 6;
        int length = word & 0x3F;
        int next = aStream->getCursor() + (length << 3);

        if (type == 0) // End
            return currentTag;

        if (length == 0x3F)
        {
            length = aStream->scan(FSStream::UnsignedWord, 32);
            next = aStream->getCursor() + (length << 3);
        }
        
        aStream->setCursor(start);

        switch (type)
        {
            case FSMovieObject::ShowFrame:
                currentTag = new FSShowFrame(aStream);
                break;
            case FSMovieObject::DefineShape:
                currentTag = new FSDefineShape(aStream);
                break;
            case FSMovieObject::PlaceObject:
                currentTag = new FSPlaceObject(aStream);
                break;
           case FSMovieObject::RemoveObject:
                currentTag = new FSRemoveObject(aStream);
                break;
            case FSMovieObject::DefineJPEGImage:
                currentTag = new FSDefineJPEGImage(aStream);
                break;
            case FSMovieObject::DefineButton:
                currentTag = new FSDefineButton(aStream);
                break;
            case FSMovieObject::JPEGEncodingTable:
                currentTag = new FSJPEGEncodingTable(aStream);
                break;
            case FSMovieObject::SetBackgroundColor:
                currentTag = new FSSetBackgroundColor(aStream);
                break;
            case FSMovieObject::DefineFont:
                currentTag = new FSDefineFont(aStream);
                break;
            case FSMovieObject::DefineText:
                currentTag = new FSDefineText(aStream);
                break;
            case FSMovieObject::DoAction:
                currentTag = new FSDoAction(aStream);
                break;
            case FSMovieObject::FontInfo:
                currentTag = new FSFontInfo(aStream);
                break;
            case FSMovieObject::DefineSound:
                currentTag = new FSDefineSound(aStream);
                break;
            case FSMovieObject::StartSound:
                currentTag = new FSStartSound(aStream);
                break;
            case FSMovieObject::SoundStreamHead:
                currentTag = new FSSoundStreamHead(aStream);
                break;
            case FSMovieObject::SoundStreamBlock:
                currentTag = new FSSoundStreamBlock(aStream);
                break;
// Flash 2
            case FSMovieObject::DefineButtonSound:
                currentTag = new FSButtonSound(aStream);
                break;
            case FSMovieObject::DefineImage:
                currentTag = new FSDefineImage(aStream);
                break;
            case FSMovieObject::DefineJPEGImage2:
                currentTag = new FSDefineJPEGImage2(aStream);
                break;
            case FSMovieObject::DefineShape2:
                currentTag = new FSDefineShape2(aStream);
                break;
            case FSMovieObject::ButtonColorTransform:
                currentTag = new FSButtonColorTransform(aStream);
                break;
            case FSMovieObject::Protect:
                currentTag = new FSProtect(aStream);
                break;
// Flash 3
            case FSMovieObject::Free:
                currentTag = new FSFree(aStream);
                break;
            case FSMovieObject::PlaceObject2:
                currentTag = new FSPlaceObject2(aStream);
                break;
            case FSMovieObject::RemoveObject2:
                currentTag = new FSRemoveObject2(aStream);
                break;
            case FSMovieObject::DefineShape3:
                currentTag = new FSDefineShape3(aStream);
                break;
            case FSMovieObject::DefineText2:
                currentTag = new FSDefineText2(aStream);
                break;
            case FSMovieObject::DefineButton2:
                currentTag = new FSDefineButton2(aStream);
                break;
            case FSMovieObject::DefineJPEGImage3:
                currentTag = new FSDefineJPEGImage3(aStream);
                break;
            case FSMovieObject::DefineImage2:
                currentTag = new FSDefineImage2(aStream);
                break;
            case FSMovieObject::DefineMovieClip:
                currentTag = new FSDefineMovieClip(aStream);
                break;
            case FSMovieObject::FrameLabel:
                currentTag = new FSFrameLabel(aStream);
                break;
            case FSMovieObject::SoundStreamHead2:
                currentTag = new FSSoundStreamHead2(aStream);
                break;
            case FSMovieObject::DefineMorphShape:
                currentTag = new FSDefineMorphShape(aStream);
                break;
            case FSMovieObject::DefineFont2:
                currentTag = new FSDefineFont2(aStream);
                break;
// Flash 4                
            case FSMovieObject::PathsArePostscript:
                currentTag = new FSPathsArePostscript(aStream);
                break;
            case FSMovieObject::DefineTextField:
                currentTag = new FSDefineTextField(aStream);
                break;
            case FSMovieObject::QuicktimeMovie:
                currentTag = new FSQuicktimeMovie(aStream);
                break;
            case FSMovieObject::SerialNumber:
                currentTag = new FSSerialNumber(aStream);
                break;
            case FSMovieObject::Pointer:
                currentTag = new FSPointer(aStream);
                break;
            case FSMovieObject::EnableDebugger:
                currentTag = new FSEnableDebugger(aStream);
                break;
            case FSMovieObject::Export:
                currentTag = new FSExport(aStream);
                break;
            case FSMovieObject::Import:
                currentTag = new FSImport(aStream);
                break;
// Flash 6
            case FSMovieObject::Initialize:
                currentTag = new FSInitialize(aStream);
                break;
            case FSMovieObject::DefineVideo:
                currentTag = new FSDefineVideo(aStream);
                break;
            case FSMovieObject::VideoFrame:
                currentTag = new FSVideoFrame(aStream);
                break;
            case FSMovieObject::FontInfo2:
                currentTag = new FSFontInfo2(aStream);
                break;
            case FSMovieObject::EnableDebugger2:
                currentTag = new FSEnableDebugger2(aStream);
                break;
// Flash 7
            case FSMovieObject::LimitScript:
                currentTag = new FSLimitScript(aStream);
                break;
            case FSMovieObject::TabOrder:
                currentTag = new FSTabOrder(aStream);
                break;
            default:
                /*
                 * Decode the object but set the type to signal to the 
                 * calling methods to drop it from the movie.
                 */
                currentTag = new FSUnknownObject(aStream);
                break;
        }

        if (currentTag == 0)
            throw FSAllocationException("Cannot allocate memory for movie object.");

        int delta = (next - aStream->getCursor()) >> 3;

        if (delta != 0)
        {
            FSMovieListener* listener = aStream->getListener();

            char str[64];
            
            if (delta > 0)
                sprintf(str, "%s underflowed by %d bytes.", currentTag->className(), delta);
            else
                sprintf(str, "%s overflowed by %d bytes.", currentTag->className(), -delta);
            
            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Decode, FSMovieEvent::Error, 0, 0, "", str));
            else
                throw FSFormatException(str);
        }
        aStream->setCursor(next);

        return currentTag;
    }

    FSActionObject* FSMovie::actionFromStream(FSInputStream* aStream)
    {
        FSActionObject* anAction = 0;

        int actionStart = aStream->getCursor();
        int actionType = aStream->scan(FSStream::UnsignedWord, 8);
        int length = 0;
        int tagStart = aStream->getCursor();
        int next = tagStart;
    
        if (actionType == 0)
        {
            /*
             * Skip over the End object so it does not generate an event.
             */ 
            aStream->setCursor(next);
            return anAction;
        }
        
        if (actionType > 128)
        {
            length = aStream->scan(FSStream::UnsignedWord, 16);
            tagStart = aStream->getCursor();
            next = tagStart + (length << 3);
        }

        aStream->setCursor(actionStart);

        switch (actionType)
        {
            case FSAction::NextFrame:
            case FSAction::PrevFrame:
            case FSAction::Play:
            case FSAction::Stop:
            case FSAction::ToggleQuality:
            case FSAction::StopSounds:
                anAction = new FSAction(aStream);
                break;
            case FSActionObject::GetUrl:
                anAction = new FSGetUrl(aStream);
                break;
// Flash 3
            case FSActionObject::GotoFrame:
                anAction = new FSGotoFrame(aStream);
                break;
// Flash 4
            case FSAction::IntegerAdd:
            case FSAction::Subtract:
            case FSAction::IntegerEquals:
            case FSAction::IntegerLess:
            case FSAction::Multiply:
            case FSAction::Divide:
            case FSAction::And:
            case FSAction::Or:
            case FSAction::Not:
            case FSAction::StringEquals:
            case FSAction::StringLength:
            case FSAction::StringExtract:
            case FSAction::Pop:
            case FSAction::ToInteger:
            case FSAction::GetVariable:
            case FSAction::SetVariable:
            case FSAction::SetTarget2:
            case FSAction::StringAdd:
            case FSAction::GetProperty:
            case FSAction::SetProperty:
            case FSAction::CloneSprite:
            case FSAction::RemoveSprite:
            case FSAction::Trace:
            case FSAction::StartDrag:
            case FSAction::EndDrag:
            case FSAction::StringLess:
            case FSAction::RandomNumber:
            case FSAction::MBStringLength:
            case FSAction::CharToAscii:
            case FSAction::AsciiToChar:
            case FSAction::GetTime:
            case FSAction::MBStringExtract:
            case FSAction::MBCharToAscii:
            case FSAction::MBAsciiToChar:
                anAction = new FSAction(aStream);
                break;
            case FSActionObject::GotoLabel:
                anAction = new FSGotoLabel(aStream);
                break;
            case FSActionObject::SetTarget:
                anAction = new FSSetTarget(aStream);
                break;
            case FSActionObject::WaitForFrame:
                anAction = new FSWaitForFrame(aStream);
                break;
            case FSActionObject::Call:
                anAction = new FSCall(aStream);
                break;
            case FSActionObject::Push:
                anAction = new FSPush(aStream);
                break;
            case FSActionObject::WaitForFrame2:
                anAction = new FSWaitForFrame2(aStream);
                break;
            case FSActionObject::Jump:
                anAction = new FSJump(aStream);
                break;
            case FSActionObject::If:
                anAction = new FSIf(aStream);
                break;
            case FSActionObject::GetUrl2:
                anAction = new FSGetUrl2(aStream);
                break;
            case FSActionObject::GotoFrame2:
                anAction = new FSGotoFrame2(aStream);
                break;
// Flash 5
            case FSAction::Add:
            case FSAction::Equals:
            case FSAction::Less:
            case FSAction::Modulo:
            case FSAction::Enumerate:
            case FSAction::Duplicate:
            case FSAction::Swap:
            case FSAction::ExecuteMethod:
            case FSAction::NewMethod:
            case FSAction::ExecuteFunction:
            case FSAction::GetAttribute:
            case FSAction::SetAttribute:
            case FSAction::Increment:
            case FSAction::Decrement:
            case FSAction::LogicalShiftLeft:
            case FSAction::LogicalShiftRight:
            case FSAction::ArithmeticShiftRight:
            case FSAction::BitwiseAnd:
            case FSAction::BitwiseOr:
            case FSAction::BitwiseXOr:
            case FSAction::NamedObject:
            case FSAction::NewArray:
            case FSAction::NewObject:
            case FSAction::DeleteVariable:
            case FSAction::Delete:
            case FSAction::Return:
            case FSAction::ToNumber:
            case FSAction::ToString:
            case FSAction::GetType:
            case FSAction::GetTarget:
            case FSAction::NewVariable:
            case FSAction::InitVariable:
                anAction = new FSAction(aStream);
                break;
            case FSActionObject::Table:
                anAction = new FSTable(aStream);
                length = anAction->getLength();
                next = tagStart + (length << 3);
                break;
            case FSActionObject::RegisterCopy:
                anAction = new FSRegisterCopy(aStream);
                break;
            case FSActionObject::NewFunction:
                anAction = new FSNewFunction(aStream);
                length = anAction->getLength();
                next = tagStart + (length << 3);
                break;
            case FSActionObject::With:
                anAction = new FSWith(aStream);
                length = anAction->getLength();
                next = tagStart + (length << 3);
                break;
// Flash 6
            case FSAction::InstanceOf:
            case FSAction::EnumerateObject:
            case FSAction::Greater:
            case FSAction::StringGreater:
            case FSAction::StrictEquals:
                anAction = new FSAction(aStream);
                break;
// Flash 7
            case FSAction::Cast:
            case FSAction::Extends:
            case FSAction::Implements:
            case FSAction::Throw:
                anAction = new FSAction(aStream);
                break;
            case FSActionObject::ExceptionHandler:
                anAction = new FSExceptionHandler(aStream);
            case FSActionObject::NewFunction2:
                anAction = new FSNewFunction2(aStream);
                length = anAction->getLength();
                next = tagStart + (length << 3);
                break;
            default:
                anAction = new FSUnknownAction(aStream);
                break;
        }

        if (anAction == 0)
            throw FSAllocationException("Cannot allocate memory for action object.");

#ifdef _DEBUG
        int bytesRead = (aStream->getCursor() - tagStart) >> 3;
        FSMovieListener* listener = aStream->getListener();

        if (bytesRead < length)
        {
            char str[64];

            sprintf(str, "%s underflowed by %d bytes.", anAction->className(), length - bytesRead);

            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Decode, FSMovieEvent::Error, 0, 0, "", str));
            else
                throw FSFormatException(str);
        }
        else if (bytesRead > length)
        {
            char str[64];

            sprintf(str, "%s overflowed by %d bytes.", anAction->className(), bytesRead - length);

            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Decode, FSMovieEvent::Error, 0, 0, "", str));
            else
                throw FSFormatException(str);
        }
#endif
        aStream->setCursor(next);

        return anAction;
    }

    void FSMovie::encodeToStream(FSVector<FSShape>& anArray, int indexWordSize, bool indexEnd, FSOutputStream* aStream)
    {
        int tableStart = aStream->getCursor(); // start of the offset table
        int tableEntry = aStream->getCursor(); // index into offset table

        // Write blank offset table

        int count = (int)anArray.size();

#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (int i=0; i<count; i++)
            aStream->write(0, FSStream::UnsignedWord, indexWordSize);

        // Write the offset to end of the shapes

        if (indexEnd)
            aStream->write(0, FSStream::UnsignedWord, indexWordSize);

#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
        // now write the shape table, updating the offset table for each entry.
        // Offset is calculated from the start of the table.

#ifdef _DEBUG
        aStream->startEncoding("array");
#endif
        for (FSVector<FSShape>::iterator i = anArray.begin(); i != anArray.end(); i++)
        {
            int currentCursor = aStream->getCursor();
            int byteOffset = (currentCursor - tableStart) >> 3;

            aStream->setCursor(tableEntry);
            aStream->write(byteOffset, FSStream::UnsignedWord, indexWordSize);
            aStream->setCursor(currentCursor);

            (*i).encodeToStream(aStream);

            tableEntry += indexWordSize;
        }

        // Write offset to end of shapes, offset includes 2 bytes forming offset.

        if (indexEnd)
        {
            int currentCursor = aStream->getCursor();
            int offset = (currentCursor - tableStart) >> 3;

            aStream->setCursor(tableEntry);
            aStream->write(offset, FSStream::UnsignedWord, indexWordSize);
            aStream->setCursor(currentCursor);
        }
#ifdef _DEBUG
        aStream->endEncoding("array");
#endif
    }

    FSFillStyle* FSMovie::fillStyleFromStream(FSInputStream* aStream)
    {
        int location = aStream->getCursor();
        int fillType = aStream->scan(FSStream::UnsignedWord, 8);
        FSFillStyle* aFillStyle = 0;
        FSMovieListener* listener = aStream->getListener();

        aStream->setCursor(location);

        if (aStream->getContext(FSStream::Type) == FSMovieObject::DefineMorphShape)
        {
            switch (fillType)
            {
                case FSFillStyle::Solid:
                    aFillStyle = new FSMorphSolidFill(aStream);
                    break;
                case FSFillStyle::LinearGradient:
                    aFillStyle = new FSMorphGradientFill(aStream);
                    break;
                case FSFillStyle::RadialGradient:
                    aFillStyle = new FSMorphGradientFill(aStream);
                    break;
                case FSFillStyle::TiledBitmap:
                    aFillStyle = new FSMorphBitmapFill(aStream);
                    break;
                case FSFillStyle::ClippedBitmap:
                    aFillStyle = new FSMorphBitmapFill(aStream);
                    break;
            }
        }
        else
        {
            switch (fillType)
            {
                case FSFillStyle::Solid:
                    aFillStyle = new FSSolidFill(aStream);
                    break;
                case FSFillStyle::LinearGradient:
                    aFillStyle = new FSGradientFill(aStream);
                    break;
                case FSFillStyle::RadialGradient:
                    aFillStyle = new FSGradientFill(aStream);
                    break;
                case FSFillStyle::TiledBitmap:
                    aFillStyle = new FSBitmapFill(aStream);
                    break;
                case FSFillStyle::ClippedBitmap:
                    aFillStyle = new FSBitmapFill(aStream);
                    break;
            }
        }
        if (aFillStyle == 0)
        {
            const char* message = "Cannot allocate memory for fill style.";

            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Decode, FSMovieEvent::Error, 0, 0, "", message));            
            else
                throw FSAllocationException(message);
        }
        return aFillStyle;
    }

    byte* FSMovie::_encode(size_t& length, FSMovieListener* listener)
    {
        FSOutputStream* swfOut = new FSOutputStream();

        if (swfOut == 0)
        {
            const char* message = "Could not allocate memory for an FSOutputStream object.";

            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Encode, FSMovieEvent::Error, 0, 0, "", message));            
            else
                throw FSAllocationException(message);
        }

        swfOut->setContext(FSStream::Version, version);
        swfOut->setListener(listener);

        int numberOfBytes = 14 + frameSize.lengthInStream(swfOut);\
        int objectLength = 0;
        
        for (FSVector<FSMovieObject*>::iterator i = objects.begin(); i != objects.end(); ++i)
        {
            objectLength = (*i)->lengthInStream(swfOut);
            numberOfBytes += ((*i)->getExtendLength() || objectLength >= 63) ? objectLength+6 : objectLength+2;
        }

        byte* bytes = new byte[numberOfBytes];
        memset(bytes, 0, numberOfBytes);

        if (bytes == 0)
        {
            const char* message = "Could not allocate memory to encode a movie.";

            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Encode, FSMovieEvent::Error, 0, 0, "", message));            
            else
                throw FSAllocationException(message);
        }

        swfOut->setData(bytes, numberOfBytes);
        delete [] bytes;

        swfOut->startEncoding("FSMovie");
    
        // Now encode the movie - first the header

        int frameRateFraction = (int)(frameRate - (int)frameRate) * 256;

        swfOut->write((byte*)signature, 3);
        swfOut->write(version, FSStream::UnsignedWord, 8);
        swfOut->write(numberOfBytes, FSStream::UnsignedWord, 32);

        frameSize.encodeToStream(swfOut);

        swfOut->write(frameRateFraction, FSStream::UnsignedWord, 8);
        swfOut->write((int)frameRate, FSStream::UnsignedWord, 8);
        swfOut->write(getFrameCount(), FSStream::UnsignedWord, 16);

        for (FSVector<FSMovieObject*>::iterator i = objects.begin(); i != objects.end(); ++i)
            encodeToStream(*i, swfOut);
        
        swfOut->write(0, FSStream::UnsignedWord, 16); // End

        swfOut->endEncoding("FSMovie");
        
        byte* data = NULL;
        
        if (signature[0] == 'C')
        {
            byte* bytes = (byte*)swfOut->getData();

            data = zip(bytes, numberOfBytes, 8, length);

            delete [] bytes;
        }
        else
        {
            data = (byte*)swfOut->getData();
            length = numberOfBytes;

            if (numberOfBytes > 0 && data == 0)
            {
                const char* message = "Could not allocate memory to encode a movie.";

                if (listener != NULL)
                    listener->logEvent(FSMovieEvent(FSMovieEvent::Encode, FSMovieEvent::Error, 0, 0, "", message));            
                else
                    throw FSAllocationException(message);
            }
        }
        delete swfOut;
    
        return data;
    }
    
    void FSMovie::_decode(const byte* bytes, size_t numberOfBytes, FSMovieListener* listener)
    {
        FSInputStream* swfIn = 0;
        float frameRateFraction = 0.0f;
        int movieLength = 0;
        int frameCount = 0;
        int id = 0;

        size_t uncompressedSize = 0; 
        unsigned int i = 0;

        for (i=0; i<4; i++)
            uncompressedSize += (bytes[i+4] & 0x000000FF) << (i*8);
            
        if (bytes[0] == 0x43)
        {
            byte* uncompressedBytes = unzip(bytes+8, numberOfBytes-8, uncompressedSize);
            byte* movieData = new byte[uncompressedSize+8];

            memcpy(movieData, bytes, 8);
            memcpy(movieData+8, uncompressedBytes, uncompressedSize);

            swfIn = new FSInputStream(movieData, uncompressedSize+8);

            delete [] uncompressedBytes;
            delete [] movieData;
        }
        else
        {
            swfIn = new FSInputStream(bytes, numberOfBytes);
        }
        
        if (swfIn == 0)
        {
            const char* message = "Could not allocate memory to uncompress a movie.";

            if (listener != NULL)
                listener->logEvent(FSMovieEvent(FSMovieEvent::Encode, FSMovieEvent::Error, 0, 0, "", message));            
            else
                throw FSAllocationException(message);
        }

        swfIn->setListener(listener);
        swfIn->startDecoding("FSMovie");

        signature[0] = swfIn->read(FSStream::UnsignedWord, 8);
        signature[1] = swfIn->read(FSStream::UnsignedWord, 8);
        signature[2] = swfIn->read(FSStream::UnsignedWord, 8);
        
        version = swfIn->read(FSStream::UnsignedWord, 8);
        movieLength = swfIn->read(FSStream::UnsignedWord, 32);

        swfIn->setContext(FSStream::Version, version);

        frameSize.decodeFromStream(swfIn);

        frameRateFraction = (float)swfIn->read(FSStream::UnsignedWord, 8);
        frameRate = (float)swfIn->read(FSStream::UnsignedWord, 8) + (frameRateFraction / 256);

        frameCount = swfIn->read(FSStream::UnsignedWord, 16);

        FSMovieObject* currentObject;
    
        swfIn->startDecoding("array");

        while ((currentObject = objectFromStream(swfIn)) != 0)
        {
            switch (currentObject->getType())
            {
                case FSMovieObject::DefineShape:
                case FSMovieObject::DefineJPEGImage:
                case FSMovieObject::DefineButton:
                case FSMovieObject::DefineFont:
                case FSMovieObject::DefineText:
                case FSMovieObject::DefineSound:
// Flash 5
                case FSMovieObject::DefineButtonSound:
                case FSMovieObject::DefineImage:
                case FSMovieObject::DefineJPEGImage2:
                case FSMovieObject::DefineShape2:
                case FSMovieObject::ButtonColorTransform:
                case FSMovieObject::DefineShape3:
                case FSMovieObject::DefineText2:
                case FSMovieObject::DefineButton2:
                case FSMovieObject::DefineJPEGImage3:
                case FSMovieObject::DefineImage2:
                case FSMovieObject::DefineTextField:
                case FSMovieObject::DefineMovieClip:
                case FSMovieObject::DefineMorphShape:
                case FSMovieObject::DefineFont2:
// Flash 6
                case FSMovieObject::DefineVideo:
                    id = ((FSDefineObject*)currentObject)->getIdentifier();
                    identifier = (identifier > id) ? identifier : id;
                    break;
                default:
                    break;
            }
            objects.push_back(currentObject);
        }
    
        swfIn->endDecoding("array");
        swfIn->endDecoding("FSMovie");

        delete swfIn;
    }
} 
