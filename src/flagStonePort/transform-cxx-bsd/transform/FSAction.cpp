/*
 *  Transform.cpp
 *  Transform SWF
 *
 *  Created by smackay on Wed Feb 19 2003.
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

#include "FSAction.h"

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSAction::FSAction(FSInputStream* aStream) : FSActionObject(0)
    {
        decodeFromStream(aStream);
    }

    const char* FSAction::className() const
    {
        static char* _name;
        
        switch (type)
        {
            case NextFrame:
                _name = "NextFrame";
                break;
            case PrevFrame:
                _name = "PrevFrame";
                break;
            case Play:
                _name = "Play";
                break;
            case Stop:
                _name = "Stop";
                break;
            case ToggleQuality:
                _name = "ToggleQuality";
                break;
            case StopSounds:
                _name = "StopSounds";
                break;
            case IntegerAdd:
                _name = "IntegerAdd";
                break;
            case Subtract:
                _name = "Subtract";
                break;
            case Multiply:
                _name = "Multiply";
                break;
            case Divide:
                _name = "Divide";
                break;
            case IntegerEquals:
                _name = "IntegerEquals";
                break;
            case IntegerLess:
                _name = "IntegerLess";
                break;
            case Less:
                _name = "Less";
                break;
            case And:
                _name = "And";
                break;
            case Or:
                _name = "Or";
                break;
            case Not:
                _name = "Not";
                break;
            case StringEquals:
                _name = "StringEquals";
                break;
            case StringLength:
                _name = "StringLength";
                break;
            case StringExtract:
                _name = "StringExtract";
                break;
            case Pop:
                _name = "Pop";
                break;
            case ToInteger:
                _name = "ToInteger";
                break;
            case GetVariable:
                _name = "GetVariable";
                break;
            case SetVariable:
                _name = "SetVariable";
                break;
            case SetTarget2:
                _name = "SetTarget2";
                break;
            case StringAdd:
                _name = "StringAdd";
                break;
            case GetProperty:
                _name = "GetProperty";
                break;
            case SetProperty:
                _name = "SetProperty";
                break;
            case CloneSprite:
                _name = "CloneSprite";
                break;
            case RemoveSprite:
                _name = "RemoveSprite";
                break;
            case Trace:
                _name = "Trace";break;
            case StartDrag:
                _name = "StartDrag";
                break;
            case EndDrag:
                _name = "EndDrag";
                break;
            case StringLess:
                _name = "StringLess";
                break;
            case RandomNumber:
                _name = "RandomNumber";
                break;
            case MBStringLength:
                _name = "MBStringLength";
                break;
            case CharToAscii:
                _name = "CharToAscii";
                break;
            case AsciiToChar:
                _name = "AsciiToChar";
                break;
            case GetTime:
                _name = "GetTime";
                break;
            case MBStringExtract:
                _name = "MBStringExtract";
                break;
            case MBCharToAscii:
                _name = "MBCharToAscii";
                break;
            case MBAsciiToChar:
                _name = "MBAsciiToChar";
                break;
            case DeleteVariable:
                _name = "DeleteVariable";
                break;
            case Delete:
                _name = "Delete";
                break;
            case InitVariable:
                _name = "InitVariable";
                break;
            case ExecuteFunction:
                _name = "ExecuteFunction";
                break;
            case Return:
                _name = "Return";
                break;
            case Modulo:
                _name = "Modulo";
                break;
            case NamedObject:
                _name = "NamedObject";
                break;
            case NewVariable:
                _name = "NewVariable";
                break;
            case NewArray:
                _name = "NewArray";
                break;
            case NewObject:
                _name = "NewObject";
                break;
            case GetType:
                _name = "GetType";
                break;
            case GetTarget:
                _name = "GetTarget";
                break;
            case Enumerate:
                _name = "Enumerate";
                break;
            case Add:
                _name = "Add";
                break;
            case Equals:
                _name = "Equals";
                break;
            case ToNumber:
                _name = "ToNumber";
                break;
            case ToString:
                _name = "ToString";
                break;
            case Duplicate:
                _name = "Duplicate";
                break;
            case Swap:
                _name = "Swap";
                break;
            case GetAttribute:
                _name = "GetAttribute";
                break;
            case SetAttribute:
                _name = "SetAttribute";
                break;
            case Increment:
                _name = "Increment";
                break;
            case Decrement:
                _name = "Decrement";
                break;
            case ExecuteMethod:
                _name = "ExecuteMethod";
                break;
            case NewMethod:
                _name = "NewMethod";
                break;
            case BitwiseAnd:
                _name = "BitwiseAnd";
                break;
            case BitwiseOr:
                _name = "BitwiseOr";
                break;
            case BitwiseXOr:
                _name = "BitwiseXOr";
                break;
            case LogicalShiftLeft:
                _name = "LogicalShiftLeft";
                break;
            case LogicalShiftRight:
                _name = "LogicalShiftRight";
                break;
            case ArithmeticShiftRight:
                _name = "ArithmeticShiftRight";
                break;
            default:
                _name = "Action";
                break;
        }
        return _name;
    }

    int FSAction::lengthInStream(FSOutputStream* aStream)
    {
        return FSActionObject::lengthInStream(aStream);
    }

void FSAction::encodeToStream(FSOutputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif
         FSActionObject::encodeToStream(aStream);

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSAction::decodeFromStream(FSInputStream* aStream)
    {
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        FSActionObject::decodeFromStream(aStream);

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }
}
