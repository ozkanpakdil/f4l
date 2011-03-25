/*
 *  ASParser.cpp
 *  Translate AS1
 *
 *  Created by smackay on Tue Jun 15 2004.
 *  Copyright (c) 2004 Flagstone Software Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 2 of the License, or (at your option) any later 
 * version.
 * 
 * This program is distributed in the hope that it will be useful, but WITHOUT
 * ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
 * FOR A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along with
 * this program; if not, write to the Free Software Foundation, Inc., 59 Temple
 * Place, Suite 330, Boston, MA 02111-1307 USA
 * 
 * For more information please contact:
 * 
 * Stuart MacKay
 * Flagstone Software Ltd
 * 92 High Street
 * Wick, Caithness KW1 4LY
 * Scotland
 * 
 * www.flagstonesoftware.com
 */
#include "ASParser.h"
#include "ASNode.h"
#include "Preprocessor.hpp"
#include "ActionScriptLexer.hpp"
#include "ActionScriptParser.hpp"
#include <antlr/CharStreamException.hpp>
#include <antlr/TokenStreamException.hpp>
#include <antlr/RecognitionException.hpp>
#include <antlr/Token.hpp>

#include <float.h>
#include <string>
#include <list>
#include <vector>
#include <set>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;
using namespace translate;
using namespace antlr;

namespace translate 
{
/*
 * Coder class for turning Actions and Events into bytes.
 */
class Coder
{
public:
	Coder(int swfVersion, unsigned char* bytes)
	{
        version = swfVersion;
		data = bytes;
        ptr = data;
	}
	Coder()
	{
        version = 5;
        data = 0;
        ptr = 0;
	}
    ~Coder()
    {
        data = 0;
        ptr = 0;
    }
    void writeByte(int value)
    {
        *ptr++ = (unsigned char)value;
    }
    void writeShort(int value)
    {
        *ptr++ = (unsigned char)value;
        *ptr++ = (unsigned char)(value >> 8);
    }
	void writeWord(int value)
	{
        *ptr++ = (unsigned char)value;
        *ptr++ = (unsigned char)(value >> 8);
        *ptr++ = (unsigned char)(value >> 16);
        *ptr++ = (unsigned char)(value >> 24);
	}

    void writeDouble(double value)
    {
        union convert {
            char bytes[8];
            double dval;
        };

        convert cnv;

        cnv.dval = value;
        
#ifdef WIN32
        for (int i=4; i<8; i++, ptr++)
            *ptr = cnv.bytes[i];

        for (int i=0; i<4; i++, ptr++)
            *ptr = cnv.bytes[i];
#else
        for (int i=3; i>-1; i--, ptr++)
            *ptr = cnv.bytes[i];

        for (int i=7; i>3; i--, ptr++)
            *ptr = cnv.bytes[i];
#endif
    }
	void writeString(string& str)
	{
        unsigned int len = str.length();
        const char* s = str.c_str();

	    for (unsigned int i=0; i<len; i++, ptr++)
			*ptr = s[i];
			
		*ptr++ = 0;
	}

    int version;    
	unsigned char* data;
	unsigned char* ptr;
};
/*
 * Values added to Push actions.
 */ 
class Value : public DLLInterface
{
public:
    enum valueType { 
        _String = 0, 
        _Property = 1, 
        _Null = 2, 
        _Void = 3, 
        _RegisterIndex = 4, 
        _Boolean = 5, 
        _Double = 6, 
        _Integer = 7, 
        _TableIndex = 8 
    };
//    Value(int aType) : type(aType) {}
    int getType() const { return type; }

    virtual Value* clone() const = 0;
    virtual int getLength(int version) = 0;
    virtual void encode(Coder* coder) = 0;
protected:
    int type;
};

class Boolean : public DLLImpl<Value>
{
public:
    Boolean(bool aValue)
    {
        type = _Boolean; 
        value = aValue; 
    }
    ~Boolean() {}
    bool boolValue() { return value; }
    Boolean* clone() const { return new Boolean(value); }
    int getLength(int version) { return 2; }
    void encode(Coder* coder)
    {
        coder->writeByte(5);
        coder->writeByte(value ? 1 : 0);
    }
private:
    bool value;
};
class Integer : public DLLImpl<Value>
{
public:
    static int hxtoi(const char* value)
    {
        struct HexMap
        {
            char chr;
            int value;
        };

        const int HexMapL = 22;

        HexMap HexMap[HexMapL] =
        {
            {'0', 0}, {'1', 1},
            {'2', 2}, {'3', 3},
            {'4', 4}, {'5', 5},
            {'6', 6}, {'7', 7},
            {'8', 8}, {'9', 9},
            {'A', 10}, {'a', 10},
            {'B', 11}, {'b', 11},
            {'C', 12}, {'c', 12},
            {'D', 13}, {'d', 13},
            {'E', 14}, {'e', 14},
            {'F', 15}, {'f', 15}
        };
        int result = 0;
        int base = 10;

        if (*value == '0' && (*(value+1) == 'X' || *(value+1) == 'x')) 
        {
            value += 2;
            base = 16;
        }

        bool firsttime = true;

        while (*value != '\0')
        {
            bool found = false;

            for (int i = 0; i<HexMapL; i++)
            {
                if (*value == HexMap[i].chr)
                {
                    if (!firsttime) result *= base;
                    result += HexMap[i].value;
                    found = true;
                    break;
                }
            }
            if (!found) break;
            value++;
            firsttime = false;
        }
        return result;
    }

    Integer(int aValue) { type = _Integer; value = aValue; }
    Integer(string aValue) { type = _Integer; value = hxtoi(aValue.c_str()); }
    ~Integer() {}
    Integer* clone() const { return new Integer(value); }
    int intValue() { return value; }
    int getLength(int version) { return 5; }
    void encode(Coder* coder)
    {
        coder->writeByte(7);
        coder->writeWord(value);
    }
private:
    int value;
};
class Double : public DLLImpl<Value>
{
public:
    Double(double aValue) { type = _Double; value = aValue; }
    Double(string aValue) { type = _Double; value = atof(aValue.c_str()); }
    ~Double() {}
    Double* clone() const { return new Double(value); }
    double doubleValue() { return value; }
    int getLength(int version) { return 9; }
    void encode(Coder* coder)
    {
        coder->writeByte(6);
        coder->writeDouble(value);
    }
private:
    double value;
};
class Null : public DLLImpl<Value>
{ 
public:
    Null() { type = _Null; } 
    ~Null() {}
    Null* clone() const { return new Null(); }
    int getLength(int version) { return 1; }
    void encode(Coder* coder)
    {
        coder->writeByte(2);
    }
};
class Void : public DLLImpl<Value>
{ 
public:
    Void() { type = _Void; } 
    ~Void () {}
    Void* clone() const { return new Void(); }
    int getLength(int version) { return 1; }
    void encode(Coder* coder)
    {
         coder->writeByte(3);
    }
};
class TableIndex : public DLLImpl<Value>
{
public:
    TableIndex(int aValue) { type = _TableIndex; value = aValue; }
    ~TableIndex() {}
    TableIndex* clone() const { return new TableIndex(value); }
    int indexValue() { return value; }
    int getLength(int version) { return (value < 256) ? 2 : 3; }
    void encode(Coder* coder)
    {
		if (value < 256)
		{
			coder->writeByte(8);
            coder->writeByte(value);
		}
		else
		{
			coder->writeByte(9);
            coder->writeShort(value);
		}
    }
private:
    int value;
};
class RegisterIndex : public DLLImpl<Value>
{
public:
    RegisterIndex(int aValue) { type = _RegisterIndex; value = aValue; }
    ~RegisterIndex() {}
    RegisterIndex* clone() const { return new RegisterIndex(value); }
    int indexValue() { return value; }
    int getLength(int version) { return 2; }
    void encode(Coder* coder)
    {
        coder->writeByte(4);
        coder->writeByte(value);
    }
private:
    int value;
};
class String : public DLLImpl<Value>
{
public:
    String(string aValue) { type = _String; value = aValue; }
    ~String() {}
    String* clone() const { return new String(value); }
    string& stringValue() { return value; }
    int getLength(int version) { return value.length()+2; }
    void encode(Coder* coder)
    {
        coder->writeByte(0);
        coder->writeString(value);
    }
private:
    string value;
};
/*
 * Action objects
 */
class Coding : public DLLInterface
{
public:
    enum CodingType {
        None                 = 0,
        Array                = 1,
        Button               = 2,
        MovieClip            = 3,

		NextFrame            = 4,
		PrevFrame            = 5,
		Play                 = 6,
		Stop                 = 7,
		ToggleQuality        = 8,
		StopSounds           = 9,
		IntegerAdd           = 10,
		Subtract             = 11,
		Multiply             = 12,
		Divide               = 13,
		IntegerEquals        = 14,
		IntegerLess          = 15,
		And                  = 16,
		Or                   = 17,
		Not                  = 18,
		StringEquals         = 19,
		StringLength         = 20,
		StringExtract        = 21,
		Pop                  = 23,
		ToInteger            = 24,
		GetVariable          = 28,
		SetVariable          = 29,
		SetTarget2           = 32,
		StringAdd            = 33,
		GetProperty          = 34,
		SetProperty          = 35,
		CloneSprite          = 36,
		RemoveSprite         = 37,
		Trace                = 38,
		StartDrag            = 39,
		EndDrag              = 40,
		StringLess           = 41,
		RandomNumber         = 48,
		MBStringLength       = 49,
		CharToAscii          = 50,
		AsciiToChar          = 51,
		GetTime              = 52,
		MBStringExtract      = 53,
		MBCharToAscii        = 54,
		MBAsciiToChar        = 55,
		DeleteVariable       = 58,
		Delete		         = 59,
		InitVariable         = 60,
		ExecuteFunction      = 61,
		Return               = 62,
		Modulo	             = 63,
		NamedObject          = 64,
		NewVariable          = 65,
		NewArray             = 66,
		NewObject            = 67,
		GetType              = 68,
		GetTarget            = 69,
		Enumerate            = 70,
		Add                  = 71,
		Less                 = 72,
		Equals               = 73,
		ToNumber             = 74,
		ToString             = 75,
		Duplicate            = 76,
		Swap                 = 77,
		GetAttribute         = 78,
		SetAttribute         = 79,
		Increment            = 80,
		Decrement            = 81,
		ExecuteMethod        = 82,
		NewMethod            = 83,
        InstanceOf           = 84,
		BitwiseAnd           = 96,
		BitwiseOr            = 97,
		BitwiseXOr           = 98,
		LogicalShiftLeft     = 99,
		ArithmeticShiftRight = 100,
		LogicalShiftRight    = 101,
		GotoFrame            = 129,
		GetUrl               = 131,
		RegisterCopy         = 135,
		Table                = 136,
		WaitForFrame         = 138,
		SetTarget            = 139,
		GotoLabel            = 140,
		WaitForFrame2        = 141,
		With                 = 148,
		Push                 = 150,
		Jump                 = 153,
		GetUrl2              = 154,
		NewFunction          = 155,
		If                   = 157,
		Call                 = 158,
		GotoFrame2           = 159
    };

    enum RequestType {
        MovieToLevel              = 0,
		MovieToLevelWithGet       = 1,
		MovieToLevelWithPost      = 2,
		MovieToTarget             = 64,
		MovieToTargetWithGet      = 65,
		MovieToTargetWithPost     = 66,
		VariablesToLevel          = 128,
		VariablesToLevelWithGet   = 129,
		VariablesToLevelWithPost  = 130,
		VariablesToTarget         = 192,
		VariablesToTargetWithGet  = 193,
		VariablesToTargetWithPost = 194
    };

    int getType() { return type; }
    void setType(int aType) { type = aType; }
    virtual int getLength(int version) = 0;
    virtual void encode(Coder* coder) = 0;

protected:
    int type;
    int length;
};
class Action : public DLLImpl<Coding>
{
public:
    Action(int aType)
    {
        type = aType;
        length = 1;

		if (type == Call) length += 2;
    }
    ~Action() {}
    int getLength(int version) 
    { 
        return length;
    }
	void encode(Coder* coder)
	{
	    coder->writeByte(type);

		if (type == Call) coder->writeShort(0);
	}
};
class ValueAction : public DLLImpl<Coding>
{
public:
    ValueAction(int aType, int aValue)
	{
        type = aType;

		switch (type)
		{
			case GetUrl2:
			case GotoFrame2:
			case RegisterCopy:
				length = 4;
				break;
			default:
				length = 5;
				break;
		}
		value = aValue;	
	}
    ~ValueAction() {}
    void setValue(int aValue)
    {
        value = aValue;
    }
    int getLength(int version) 
    { 
        return length;
    }
	void encode(Coder* coder)
	{
		coder->writeByte(type);
		coder->writeShort(length-3);

		switch (type)
		{
			case GotoFrame2:
			case GetUrl2:
			case RegisterCopy:
				coder->writeByte(value);
				break;
			default:
				coder->writeShort(value);
				break;
		}
	}
protected:
    int value;
};
class StringAction : public DLLImpl<Coding>
{
public:
	StringAction(int aType, string nodeValue)
	{
        type = aType;
        count = 1;
		length = 4 + nodeValue.length();
		strA = nodeValue;
	}

	StringAction(int aType, string a, string b)
	{
        type = aType;
        count = 2;
		length = 5 + a.length() + b.length();
		strA = a;
		strB = b; 
	}
    ~StringAction()
    {
    }
    int getLength(int version) 
    { 
        return length;
    }
	void encode(Coder* coder)
	{
		coder->writeByte(type);
		coder->writeShort(length-3);
        coder->writeString(strA);
		
		if (count == 2)
            coder->writeString(strB);
	}
private:
    int count;
	string strA;
	string strB;
};
class TableAction : public DLLImpl<Coding>
{
public:
    TableAction(list<string>& array)
	{
        type = Table;
        length = 5;

        for (list<string>::iterator i=array.begin(); i != array.end(); i++)
        {
			length += (*i).length()+1;
            values.push_back(*i);
        }
	}
    ~TableAction()
    {
    }
    int getLength(int version) 
    { 
        return length;
    }
	void encode(Coder* coder)
	{
		coder->writeByte(type);
		coder->writeShort(length-3);
		coder->writeShort(values.size());
	    
        for (list<string>::iterator i=values.begin(); i != values.end(); i++)
			coder->writeString(*i);
	}
private:
    list<string>values;
};
class PushAction : public DLLImpl<Coding>
{
public:
    PushAction(Value* value)
	{
        type = Push;
		values.push_back(value);
    }
    ~PushAction()
    {
		for (list<Value*>::iterator i = values.begin(); i != values.end(); i++)
			delete *i;

        values.erase(values.begin(), values.end());
    }
	void add(Value* value)
	{
		values.push_back(value);
	}
	Value* back()
	{
		return values.back();
	}
	void replace_back(Value* value)
	{
        Value* last = values.back();

        values.pop_back();
        values.push_back(value);

		delete last;
	}
	int getLength(int version)
	{
		length = 3;
    
		for (list<Value*>::iterator i = values.begin(); i != values.end(); i++)
            length += (*i)->getLength(version);

        return length;
	}
	void encode(Coder* coder)
	{
		coder->writeByte(type);
		coder->writeShort(length-3);

		for (list<Value*>::iterator i = values.begin(); i != values.end(); i++)
            (*i)->encode(coder);
	}
private:
    list<Value*>values;
};
class NewFunctionAction : public DLLImpl<Coding>
{
public:
    NewFunctionAction(string str, list<string>args, list<Coding*>actionArray)
	{
        type = NewFunction;
		name = str;
		arguments = args;
		actions = actionArray;
		
        actionsLength = 0;
	}
    ~NewFunctionAction()
    {
		for (list<Coding*>::iterator i = actions.begin(); i != actions.end(); i++)
			delete *i;
    }
	int getLength(int version)
	{
		length = 8 + name.length();

        for (list<string>::iterator i = arguments.begin(); i != arguments.end(); i++)
            length += (*i).length()+1;

		actionsLength = 0;

		for (list<Coding*>::iterator i = actions.begin(); i != actions.end(); i++) 
			actionsLength += (*i)->getLength(version);

        return length + actionsLength;
	}

	void encode(Coder* coder)
	{
		coder->writeByte(type);
		coder->writeShort(length-3);
		coder->writeString(name);
		coder->writeShort(arguments.size());
		
        for (list<string>::iterator i = arguments.begin(); i != arguments.end(); i++)
            coder->writeString(*i);

		coder->writeShort(actionsLength);
		
		for (list<Coding*>::iterator i = actions.begin(); i != actions.end(); i++)
			(*i)->encode(coder);
	}
private:
    int actionsLength;
	
	string name;
	list<string>arguments;
	list<Coding*>actions;
};
/*
 * Event objects
 */
class ASEvent : public DLLImpl<Coding>
{
public:
    ASEvent(int eventType, int eventCode, list<Coding*>array)
	{
        type = eventType;
		event = eventCode;
        code = 0;
		
        for (list<Coding*>::iterator i = array.begin(); i != array.end(); i++)
            actions.push_back(*i);
	}
	ASEvent(int eventType, int eventCode, int keyCode, list<Coding*>array)
	{
        type = eventType;
		event = eventCode;
		code = keyCode;
		
        for (list<Coding*>::iterator i = array.begin(); i != array.end(); i++)
            actions.push_back(*i);
	}
    ~ASEvent()
    {
		for (list<Coding*>::iterator i = actions.begin(); i != actions.end(); i++)
			delete *i;
    }
    int getEvent()
    {
        return event;
    }
	int getLength(int version)
	{
        switch (type)
        {
            case ASNode::OnClipEvent:
                length = 5 + ((version > 5) ? 4 : 2);
                
                if (version > 5 && (event & 131072) != 0)
                    length += 1;
                
                for (list<Coding*>::iterator i = actions.begin(); i != actions.end(); i++)
                    length += (*i)->getLength(version);
                break;
            case ASNode::On:
                length = 3;
                
                for (list<Coding*>::iterator i = actions.begin(); i != actions.end(); i++)
                    length += (*i)->getLength(version);
                break;
        }
		return length;
	}
	void encode(Coder* coder)
	{
        int eventSize = (coder->version > 5) ? 4 : 2;
        
        switch (type)
        {
            case ASNode::OnClipEvent:
                if (coder->version > 5)
                    coder->writeWord(event);
                else
                    coder->writeShort(event);

                coder->writeWord(length-(4+eventSize));
            
                if (coder->version > 5 && (event & 131072) != 0)
                    coder->writeByte(code);
                
                for (list<Coding*>::iterator i = actions.begin(); i != actions.end(); i++) 
                    (*i)->encode(coder);
                    
                coder->writeByte(0);
                break;
            case ASNode::On:
                coder->writeShort(event);
            
                for (list<Coding*>::iterator i = actions.begin(); i != actions.end(); i++) 
                    (*i)->encode(coder);

                coder->writeByte(0);
                break;
        }
	}
private:
	int event;
	int code;
    
	list<Coding*>actions;
};
class ASArray : public DLLImpl<Coding>
{
public:
    ASArray(int arrayType, list<Coding*>array)
	{
        type = arrayType;
		objects = array;
	}
    ~ASArray()
    {
		for (list<Coding*>::iterator i = objects.begin(); i != objects.end(); i++)
			delete *i;
    }
	void add(Coding* object)
	{
		objects.push_back(object);		
	}	
	int getLength(int version)
	{
        length = 0;

		switch (type)
		{
            case Array:
				for (list<Coding*>::iterator i = objects.begin(); i != objects.end(); i++)
					length += (*i)->getLength(version);
				break;
			case Button:
				for (list<Coding*>::iterator i = objects.begin(); i != objects.end(); i++)
					length += 2 + (*i)->getLength(version);
				break;
            case MovieClip:
				length += version > 5 ? 10 : 6;
				for (list<Coding*>::iterator i = objects.begin(); i != objects.end(); i++)
					length += (*i)->getLength(version);
				break;
		}		
		return length;
	}
	void encode(Coder* coder)
	{
        int count = objects.size()-1; 

		switch (type)
		{
			case Array:
				for (list<Coding*>::iterator i = objects.begin(); i != objects.end(); i++)
					(*i)->encode(coder);
				break;
			case Button:
				for (list<Coding*>::iterator i = objects.begin(); i != objects.end(); i++, count--)
				{
					coder->writeShort(count ? (*i)->getLength(coder->version) + 2 : 0);
					(*i)->encode(coder);
				}
				break;
			case MovieClip:
				int allEvents = 0;

                for (list<Coding*>::iterator i = objects.begin(); i != objects.end(); i++)
					allEvents |= ((ASEvent*)(*i))->getEvent();
				
				coder->writeShort(0);

                if (coder->version > 5)
                    coder->writeWord(allEvents);
                else
				    coder->writeShort(allEvents);

				for (list<Coding*>::iterator i = objects.begin(); i != objects.end(); i++)
					(*i)->encode(coder);

                if (coder->version > 5)
                    coder->writeWord(0);
                else
				    coder->writeShort(0);

				break;
		}
    }
private:       
	list<Coding*>objects;
};

/*
 * Context and Coder classes for turning Actions into bytes.
 */
class ASInfo
{
public:
	int version;

    list<ASNode*>nodes;
    list<int>insertionPoints;

    list<string>context;

    bool useStrings;
    list<string>strings;

    ASInfo()
    {
        version = 5;
        useStrings = false;

    }
    ASInfo(int swfVersion)
	{
        version = swfVersion;
        useStrings = false;
	}
    ~ASInfo()
    {
        nodes.clear();
        insertionPoints.clear();
        context.clear();
        strings.clear();
    }
	void addString(string str)
	{
        unsigned int maxSize = (version < 6) ? 256 : 65536;

        for (list<string>::iterator i = strings.begin(); i != strings.end(); i++)
        {
            if (*i == str) { 
                useStrings = true; 
                return; 
            }
        }
        if (strings.size() < maxSize)
            strings.push_back(str);
	}

    int indexOf(string str)
    {
        int index = -1;
        int count = 0;

        list<string>::iterator i = strings.begin();

        while (i != strings.end())
        {
            if (*i == str)
            {
                index = count;
                break;
            }
            count++;
            i++;
        }
        return index;
    }

    bool inContext(string str)
    {
        bool found = false;

        for (list<string>::iterator i = context.begin(); !found && i != context.end(); i++)
        {
            if (*i == str) found = true;
        }
        return found;
    }
};
/*
 * Parser
 */
class ASParserImpl : public DLLImpl<ASParser>
{
public:
    ASParserImpl()
    {
        message = "";
        filename = "";
        line = "";
        lineNumber = 0;
        columnNumber = 0;
        error = OK;

        data = 0;
        length = 0;

        pathNames.push_back(".");
        if (buttonEvents.empty())
        {
	        buttonEvents.insert(make_pair("rollOver", 1));
	        buttonEvents.insert(make_pair("rollOut", 2));
	        buttonEvents.insert(make_pair("press", 4));
	        buttonEvents.insert(make_pair("release", 8));
	        buttonEvents.insert(make_pair("releaseOutside", 16));
	        buttonEvents.insert(make_pair("dragOver", 160)); // dragOver | menuDragOver
	        buttonEvents.insert(make_pair("releaseOut", 64));
	        buttonEvents.insert(make_pair("menuDragOver", 128));
	        buttonEvents.insert(make_pair("menuDragOut", 256));
	        buttonEvents.insert(make_pair("<left>", 512));
	        buttonEvents.insert(make_pair("<right>", 1024));
	        buttonEvents.insert(make_pair("<home>", 1536));
	        buttonEvents.insert(make_pair("<end>", 2048));
	        buttonEvents.insert(make_pair("<insert>", 2560));
	        buttonEvents.insert(make_pair("<delete>", 3072));
	        buttonEvents.insert(make_pair("<backspace>", 4096));
	        buttonEvents.insert(make_pair("<enter>", 6656));
	        buttonEvents.insert(make_pair("<up>", 7168));
	        buttonEvents.insert(make_pair("<down>", 7680));
	        buttonEvents.insert(make_pair("<pageUp>", 8192));
	        buttonEvents.insert(make_pair("<pageDown>", 8704));
	        buttonEvents.insert(make_pair("<tab>", 9216));
	        buttonEvents.insert(make_pair("<escape>", 9728));
	        buttonEvents.insert(make_pair("<space>", 16384));
        }
        if (clipEvents.empty())
        {
	        clipEvents.insert(make_pair("load", 1));
	        clipEvents.insert(make_pair("enterFrame", 2));
	        clipEvents.insert(make_pair("unload", 4));
	        clipEvents.insert(make_pair("mouseMove", 8));
	        clipEvents.insert(make_pair("mouseDown", 16));
	        clipEvents.insert(make_pair("mouseUp", 32));
	        clipEvents.insert(make_pair("keyDown", 64));
	        clipEvents.insert(make_pair("keyUp", 128));
	        clipEvents.insert(make_pair("data", 256));
        }
        if (constants.empty())
        {
	        constants.insert(make_pair("Key.BACKSPACE", new Integer(8)));
	        constants.insert(make_pair("Key.CAPSLOCK", new Integer(20)));
	        constants.insert(make_pair("Key.CONTROL", new Integer(17)));
	        constants.insert(make_pair("Key.DELETEKEY", new Integer(46)));
	        constants.insert(make_pair("Key.DOWN", new Integer(40)));
	        constants.insert(make_pair("Key.END", new Integer(35)));
	        constants.insert(make_pair("Key.ENTER", new Integer(13)));
	        constants.insert(make_pair("Key.ESCAPE", new Integer(27)));
	        constants.insert(make_pair("Key.HOME", new Integer(36)));
	        constants.insert(make_pair("Key.INSERT", new Integer(45)));
	        constants.insert(make_pair("Key.LEFT", new Integer(37)));
	        constants.insert(make_pair("Key.PGDN", new Integer(34)));
	        constants.insert(make_pair("Key.PGUP", new Integer(33)));
	        constants.insert(make_pair("Key.RIGHT", new Integer(39)));
	        constants.insert(make_pair("Key.SHIFT", new Integer(16)));
	        constants.insert(make_pair("Key.SPACE", new Integer(32)));
	        constants.insert(make_pair("Key.TAB", new Integer(9)));
	        constants.insert(make_pair("Key.UP", new Integer(38)));

            constants.insert(make_pair("Math.E", new Double(2.7182818284590452354)));
	        constants.insert(make_pair("Math.LN2", new Double(0.69314718055994530942)));
	        constants.insert(make_pair("Math.LOG2E", new Double(1.4426950408889634074)));
	        constants.insert(make_pair("Math.LN10", new Double(2.30258509299404568402)));
	        constants.insert(make_pair("Math.LOG10E", new Double(0.43429448190325182765)));
	        constants.insert(make_pair("Math.PI", new Double(3.14159265358979323846)));
	        constants.insert(make_pair("Math.SQRT1_2", new Double(0.70710678118654752440)));
	        constants.insert(make_pair("Math.SQRT2", new Double(1.41421356237309504880)));

#ifdef WIN32
            unsigned long val[2];
            
            val[0] = 0xffffffff;
            val[1] = 0x7fffffff;

	        constants.insert(make_pair("Number.NaN", new Double(*(double*)val)));

            val[0] = 0x00000000;
            val[1] = 0x7ff00000;

	        constants.insert(make_pair("Number.POSITIVE_INFINITY", new Double(*(double*)val)));

            val[0] = 0x00000000;
            val[1] = 0xfff00000;

	        constants.insert(make_pair("Number.NEGATIVE_INFINITY", new Double(*(double*)val)));
#endif

#ifndef WIN32
#ifdef NAN
            constants.insert(make_pair("Number.NaN", new Double(NAN)));
	        constants.insert(make_pair("Number.NEGATIVE_INFINITY", new Double(-INFINITY)));
	        constants.insert(make_pair("Number.POSITIVE_INFINITY", new Double(INFINITY)));
#endif
#endif
	        constants.insert(make_pair("Number.MAX_VALUE", new Double(DBL_MAX)));
            // Flash generates a number different than DBL_MIN so the value is
            // used directly for compatibility.
	        constants.insert(make_pair("Number.MIN_VALUE", new Double(4.9e-324)));
        } 
        if (properties.empty())
        {
	        properties.insert(make_pair("_x", 0));
	        properties.insert(make_pair("_y", 1));
	        properties.insert(make_pair("_xscale", 2));
	        properties.insert(make_pair("_yscale", 3));
	        properties.insert(make_pair("_currentframe", 4));
	        properties.insert(make_pair("_totalframes", 5));
	        properties.insert(make_pair("_alpha", 6));
	        properties.insert(make_pair("_visible", 7));
	        properties.insert(make_pair("_width", 8));
	        properties.insert(make_pair("_height", 9));
	        properties.insert(make_pair("_rotation", 10));
	        properties.insert(make_pair("_target", 11));
	        properties.insert(make_pair("_framesloaded", 12));
	        properties.insert(make_pair("_name", 13));
	        properties.insert(make_pair("_droptarget", 14));
	        properties.insert(make_pair("_url", 15));
	        properties.insert(make_pair("_highquality", 16));
	        properties.insert(make_pair("_focusrect", 17));
	        properties.insert(make_pair("_soundbuftime", 18));
	        properties.insert(make_pair("_quality", 19));
	        properties.insert(make_pair("_xmouse", 20));
	        properties.insert(make_pair("_ymouse", 21));
        }
        if (functions.empty())
        {
            functions.insert("delete");
	        functions.insert("duplicateMovieClip");
	        functions.insert("eval");
	        functions.insert("fscommand");
	        functions.insert("getProperty");
	        functions.insert("getURL");
	        functions.insert("getVersion");
	        functions.insert("gotoAndPlay");
	        functions.insert("gotoAndStop");
	        functions.insert("hitTest");
	        functions.insert("loadMovie");
	        functions.insert("loadVariables");
	        functions.insert("nextFrame");
	        functions.insert("nextScene");
	        functions.insert("Number");
	        functions.insert("play");
	        functions.insert("prevFrame");
	        functions.insert("prevScene");
	        functions.insert("print");
	        functions.insert("printAsBitmap");
	        functions.insert("removeMovieClip");
	        functions.insert("set");
	        functions.insert("setProperty");
	        functions.insert("startDrag");
	        functions.insert("stop");
	        functions.insert("stopAllSounds");
	        functions.insert("stopDrag");
	        functions.insert("String");
	        functions.insert("targetPath");
	        functions.insert("toggleHighQuality");
	        functions.insert("trace");
	        functions.insert("typeof");
	        functions.insert("unloadMovie");
	        functions.insert("void");
        }
        if (valueFunctions.empty())
        {
 	        valueFunctions.insert("attachMovie");
	        valueFunctions.insert("delete");
	        valueFunctions.insert("escape");
	        valueFunctions.insert("eval");
	        valueFunctions.insert("getBounds");
	        valueFunctions.insert("getBytesLoaded");
	        valueFunctions.insert("getBytesTotal");
	        valueFunctions.insert("getProperty");
	        valueFunctions.insert("getVersion");
	        valueFunctions.insert("globalToLocal");
	        valueFunctions.insert("hitTest");
	        valueFunctions.insert("isFinite");
	        valueFunctions.insert("isNaN");
	        valueFunctions.insert("localToGlobal");
	        valueFunctions.insert("parseFloat");
	        valueFunctions.insert("parseInt");
	        valueFunctions.insert("swapDepths");
	        valueFunctions.insert("targetPath");
	        valueFunctions.insert("typeof");
	        valueFunctions.insert("unescape");
	        valueFunctions.insert("updateAfterEvent");
	        valueFunctions.insert("void");
        }
    }

    ~ASParserImpl()
    {
        if (data) 
        {
            delete [] data;
            data = 0;
        }
    }

    void CALL addPath(const char* path)
    {
        pathNames.push_back(path);
    }

    const char* CALL getMessage()
    {
        return message.c_str();
    }

    const char* CALL getFilename()
    {
        return filename.c_str();
    }

    int CALL getLineNumber()
    {
        return lineNumber;
    }

    int CALL getColumnNumber()
    {
        return columnNumber;
    }

    const char* CALL getLine()
    {
        return line.c_str();
    }

    int CALL getError()
    {
        return error;
    }

    ASNode* CALL parse(const char* scriptIn)
    {
        ASNode* root = NULL;

        files.clear();
        lines.clear();
        codes.clear();

        try
        {
            if (scriptIn != 0 && strlen(scriptIn))
            {
                stringstream ss(scriptIn, stringstream::in);

                processDirectives(ss, "Main");

		        ActionScriptLexer* lexer = new ActionScriptLexer(script);
		        ActionScriptParser* parser = new ActionScriptParser(*lexer);

                root = parser->script();

                delete parser;
                delete lexer;
            }
        }
        catch (CharStreamException& e)
        {
            error = READ_ERROR;

            if (e.getMessage().length() > 0)
                message = e.getMessage();
            else
                message = "An error occurred while reading the script.";

            filename = "Main";
            lineNumber = 0;
            columnNumber = 0;
            line = "No Line";

            delete root;
            root = 0;
        }
        catch (TokenStreamException& e)
        {
            error = READ_ERROR;

            if (e.getMessage().length() > 0)
                message = e.getMessage();
            else
                message = "An error occurred while reading the script.";

            filename = "Main";
            lineNumber = 0;
            columnNumber = 0;
            line = "No Line";

            delete root;
            root = 0;
        }
        catch (RecognitionException& e)
        {
            unsigned int errorLine = e.getLine() - 1;

            error = PARSE_ERROR;
            message = e.toString();
            filename = (files.size() > errorLine) ? files[errorLine] : "Main";
            lineNumber = (lines.size() > errorLine) ? lines[errorLine] : 0;
            columnNumber = e.getColumn();
            line = (codes.size() > errorLine) ? codes[errorLine] : "No Line";

            delete root;
            root = 0;
        }
        return root;
    }
    size_t CALL compile(ASNode* root, int version)
    {
	    length = 0;

        if (version < 5) return length;
           
	    ASInfo* info = new ASInfo(version);
	    list<Coding*>array;
           
        reorder(root, info);
        findStrings(root, info);
        generate(root, info, array);
        
	    for (list<Coding*>::iterator i = array.begin(); i != array.end(); i++)
            length += (*i)->getLength(version);

        if (data)
        {
            delete [] data;
            data = 0;
        }

        data = new unsigned char[length];

	    Coder* coder = new Coder(version, data);

	    for (list<Coding*>::iterator i = array.begin(); i != array.end(); i++)
        {
		    (*i)->encode(coder);
            delete *i;
        }
        data = coder->data;

        return length;
    }
    size_t CALL getCode(unsigned char* buf)
    {
        memcpy(buf, data, length*sizeof(unsigned char));
        return length;
    }
private:
    enum NodeStatus {
        DISCARD = 1};

    void processDirectives(istream& cin, const char* filename)
    {
        Preprocessor processor(cin);

		string definition = "";
        string code = "";

        bool define = false;
        bool include = false;
		bool ifdef = false;
		bool ifndef = false;
		bool append = true;

        int lineNumber = 0;

        while (true) 
        {
            RefToken token = processor.nextToken();

            if (token->getType() == Token::EOF_TYPE)
            {
                if (code.length() > 0)
                {
                    files.push_back(filename);
                    lines.push_back(++lineNumber);
                    codes.push_back(code);

                    script << code << endl;
                }
                break;
            }
            else if (token->getType() == PreprocessorTokenTypes::SL_COMMENT)
            {
                lineNumber = token->getLine();

                files.push_back(filename);
                lines.push_back(lineNumber);
                codes.push_back("");

                script << endl;
            }
            else if (token->getType() == PreprocessorTokenTypes::ML_COMMENT)
            {
                int lastLine = token->getLine();

                while (lineNumber++ < lastLine)
                {
                    files.push_back(filename);
                    lines.push_back(lineNumber);
                    codes.push_back("");

                    script << endl;
                }
            }
            else if (token->getType() == PreprocessorTokenTypes::LINE_END)
            {
				if (define)
				{
					definitions.insert(make_pair(definition, ""));
					definition = "";
					define = false;
				}
                lineNumber = token->getLine();

                files.push_back(filename);
                lines.push_back(lineNumber);
                codes.push_back(code);

                script << code << endl;
                code = "";
            }
            else if (token->getType() == PreprocessorTokenTypes::INCLUDE)
            {
                include = true;
            }
            else if (token->getType() == PreprocessorTokenTypes::DEFINE)
            {
				define = true;
            }
            else if (token->getType() == PreprocessorTokenTypes::IFDEF)
            {
				ifdef = true;
            }
            else if (token->getType() == PreprocessorTokenTypes::IFNDEF)
            {
				ifndef = true;
            }
            else if (token->getType() == PreprocessorTokenTypes::ELSE)
            {
				append = !append;
			}
            else if (token->getType() == PreprocessorTokenTypes::ENDIF)
            {
				append = true;
			}
            else if (token->getType() == PreprocessorTokenTypes::STRING_LITERAL && include)
            {
                include = false;

                string pathname = pathToFile(token->getText());

                if (pathname.length() > 0)
                {
                    ifstream input(pathname.c_str());
                    processDirectives(input, pathname.c_str());
                    input.close();
                }
                else
                {
                    string message = "Could not find file: " + token->getText();
                    throw RecognitionException(message, filename, token->getLine(), token->getColumn());
                }
            }
            else if (token->getType() == PreprocessorTokenTypes::LITERAL && define)
            {
				definition = token->getText();
			}
            else if (token->getType() == PreprocessorTokenTypes::LITERAL && ifdef)
            {
				append = isDefinition(token->getText());
				ifdef = false;
			}
            else if (token->getType() == PreprocessorTokenTypes::LITERAL && ifndef)
            {
				append = !isDefinition(token->getText());
				ifndef = false;
			}
            else if (token->getType() == PreprocessorTokenTypes::NUMERIC_LITERAL && define)
            {
				if (definition.length() > 0)
				{
					definitions.insert(make_pair(definition, token->getText()));
					definition = "";
					define = false;
				}
				else
				{
					string message = "Unsupported value for #define: " + token->getText();
                    throw RecognitionException(message, filename, token->getLine(), token->getColumn());
				}
			}
            else if (append == true && (include == false || define == false))
            {
                code.append(token->getText());
            }
        }
    }

    bool isConstant(string name)
    {
        return constants.find(name) != constants.end();
    }
    bool isProperty(string name)
    {
        return properties.find(name) != properties.end();
    }
    bool isFunction(string name)
    {
        return functions.find(name) != functions.end();
    }
    bool isValueFunction(string name)
    {
        return valueFunctions.find(name) != valueFunctions.end();
    }
    bool isDefinition(string name)
    {
        return definitions.find(name) != definitions.end();
    }
    int getButtonEvent(string name)
    {
        int val = 0;

        if (buttonEvents.find(name) != buttonEvents.end())
            val = buttonEvents.find(name)->second;

        return val;
    }
    int getClipEvent(string name)
    {
        int val = 0;

        if (clipEvents.find(name) != clipEvents.end())
            val = clipEvents.find(name)->second;

        return val;
    }
    Value* getConstant(string name)
    {
        Value* val = NULL;

        if (constants.find(name) != constants.end())
            val = constants.find(name)->second;

        return val->clone();
    }
    int getProperty(string name)
    {
        int val = 0;

        if (properties.find(name) != properties.end())
            val = properties.find(name)->second;

        return val;
    }
    string getDefinition(string name)
    {
        string val = 0;

        if (definitions.find(name) != definitions.end())
            val = definitions.find(name)->second;

        return val;
    }
    void reorder(ASNode* node, ASInfo* info)
    {
        int type = node->getType();

        if (type == ASNode::Array || type == ASNode::Button || type == ASNode::MovieClip || type == ASNode::List)
        {
            info->nodes.push_back(node);
            info->insertionPoints.push_back(0);
        }

        for (unsigned int i=0; i<node->count(); i++)
		    reorder(node->get(i), info);
    		
        /*
         * See if the value is actually a pre-defined constant.
         */
        if (type == ASNode::Value && node->get(0)->getType() == ASNode::Identifier)
        {
            if (node->get(1)->getType() == ASNode::Attribute)
            {
                string name = node->get(0)->getValue();
                name += ".";
                name += node->get(1)->getValue();
                
                if (isConstant(name))
                {
                    node->setType(ASNode::Constant);
                    node->setValue(name.c_str());

                    node->get(0)->setType(ASNode::NoOp);
                    node->get(1)->setType(ASNode::NoOp);
                }
            }
        }
        /*
         * See if the value is actually a floating point number.
         */
        if (type == ASNode::Value && node->get(0)->getType() == ASNode::Number)
        {
            if (node->get(1)->getType() == ASNode::Attribute)
            {
                string name = node->get(0)->getValue();
                name += ".";
                name += node->get(1)->getValue();
                
                if (isConstant(name))
                {
                    node->setType(ASNode::Number);
                    node->setValue(name.c_str());

                    node->get(0)->setType(ASNode::NoOp);
                    node->get(1)->setType(ASNode::NoOp);
                }
            }
        }
        else if (type == ASNode::DefineFunction)
        {
            ASNode* parent = node->getParent();
            ASNode* top = info->nodes.empty() ? NULL : info->nodes.back();
            /*
             * If this is a function definition insert near the front of the enclosing 
             * ActionScript block structure and remove it from its current position in
             * the node tree.
             */
            if (parent != NULL && top != NULL)
            {
                int& point = info->insertionPoints.back();
                int index = parent->indexOf(node);

                parent->set(index, NewASNode(ASNode::NoOp));
                top->insert(point++, node);
            }
        }
        else if (type == ASNode::Function)
        {
            string functionName = node->getValue();
            string value;

            ASNode* child = NULL;

            if (functionName == "fscommand")
            {
                child = node->get(0);

                if (child->getType() == ASNode::String)
                {
                    value = "FSCommand:";
                    value += child->getValue();
                    child->setValue(value.c_str());
                }
            }
            else if (functionName == "print")
            {
                child = node->get(1);
                value = child->getValue();

                if (value == "bmovie")
                    child->setValue("print:");
                else
                {
                    value = "print:#" + value;
                    child->setValue(value.c_str());
                }
            }
            else if (functionName == "printAsBitmap")
            {
                child = node->get(1);
                value = child->getValue();

                if (value == "bmovie")
                    child->setValue("printasbitmap:");
                else
                {
                    value = "printasbitmap:#" + value;
                    child->setValue(value.c_str());
                }
            }
        }

        if (type == ASNode::Array || type == ASNode::Button || type == ASNode::MovieClip || type == ASNode::List)
        {
            info->nodes.pop_back();
            info->insertionPoints.pop_back();
        }
    }

    void findStrings(ASNode* node, ASInfo* info)
    {
        int type = node->getType();
        string value = node->getValue();
        ASNode** children = node->getChildren();

        int size = node->count();
        int i=0;

        bool addedToContext = false;
        
        if (type == ASNode::With || (type == ASNode::Function && value == "getProperty"))
        {
            info->context.push_back(value);
            addedToContext = true;
        }

        switch (type)
        {
		    case ASNode::Value:
                i = size;
			    while (--i >= 0)
                {
                    if (children[i]->getType() == ASNode::Function)
				        findStrings(children[i], info);
                }
			    for (i=0; i<size; i++)
                {
                    if (children[i]->getType() != ASNode::Function)
				        findStrings(children[i], info);
                }
			    break;
            case ASNode::String:
            case ASNode::DefineVariable:
				info->addString(value);
			    break;
		    case ASNode::Identifier:
                if (node->getParent()->getType() == ASNode::OnClipEvent && getClipEvent(value) != 0)
                {
                    break;
                }
                if (node->getParent()->getType() == ASNode::On && getButtonEvent(value) != 0)
                {
                    break;
                }
			    else if (isProperty(value))
			    {
                    bool isProperty = false;
                    bool isWith = false;

                    for (list<string>::iterator iter = info->context.begin(); iter != info->context.end(); iter++)
                    {
                        if (*iter == "With") isWith = true;
                        if (*iter == "getProperty") isProperty = true;
                    }

                    if (node->getParent()->getType() != ASNode::Value) isProperty = true;

                    if (isProperty == false)
                    {
				        if (isWith)
                            info->addString("");

                        info->addString(value);
                    }
                }
                else
                {
                    if (value != "true" && value != "false" && value != "null")
			            info->addString(value);
                }
			    break;
		    case ASNode::Attribute:
 		    case ASNode::Method:
		    case ASNode::NewObject:
                i = size;
                while (--i >= 0)
				    findStrings(children[i], info);
			    info->addString(value);
			    break;
    	    case ASNode::Function:
 			    if (isFunction(value) == false)
 			    {
                    for (i=0; i<size; i++)
                        findStrings(children[i], info);

                    if (value.length() > 0)
                        info->addString(value);
 			    }
 			    else
 			    {
 				    if (value == "fscommand")
 				    {
					    info->addString("FSCommand:");

                        for (int i=0; i<size; i++)
                            findStrings(children[i], info);
 				    }
 				    else if (value == "getURL" || value == "loadMovie" || value == "loadVariables")
 				    {
 					    if (size > 0)
 						    findStrings(*children, info);

					    if (size > 1)
						    findStrings(children[1], info);
    						
					    if (size == 1)
						    info->addString("");
    						
  					    break;
				    }
 				    else if (value == "gotoAndPlay" || value == "gotoAndStop")
 				    {
                        findStrings(children[1], info);
  					    break;
				    }
 				    else if (value == "print" || value == "printAsBitmap")
 				    {
                        int index = node->count() - 1;

                        while (index >= 0) 
                            findStrings(children[index--], info);
  					    break;
				    }
                    else
                    {
                        for (i=0; i<size; i++, children++)
                            findStrings(*children, info);
                    }
 			    }
    		    break;
		    case ASNode::DefineFunction:
			    findStrings(*(children+size-1), info);
			    break;
		    case ASNode::DefineArray:
                i = size;
			    while (--i >= 0)
				    findStrings(children[i], info);
			    break;
            case ASNode::NoOp:
                break;
   		    default:
			    for (i=0; i<size; i++, children++)
				    findStrings(*children, info);
			    break;
        }
        if (addedToContext)
            info->context.pop_back();
    }
    void generate(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
	    switch (node->getType())
        {
            case ASNode::Array:
                generateScript(node, info, actions); 
                break;
		    case ASNode::Button:
                generateScript(node, info, actions); 
                break;
		    case ASNode::MovieClip: 
                generateScript(node, info, actions); 
                break;
		    case ASNode::List: 
                generateList(node, info, actions); 
                break;
		    case ASNode::ExpressionList: 
                generateExpressionList(node, info, actions); 
                break;
		    case ASNode::If: 
                generateIf(node, info, actions); 
                break;
		    case ASNode::Do: 
                generateDo(node, info, actions); 
                break;
		    case ASNode::While: 
                generateWhile(node, info, actions); 
                break;
		    case ASNode::For: 
                generateFor(node, info, actions); 
                break;
		    case ASNode::ForIn: 
                generateForIn(node, info, actions); 
                break;
		    case ASNode::With: 
                generateWith(node, info, actions); 
                break;
		    case ASNode::On:
                generateOn(node, info, actions); 
                break;
		    case ASNode::OnClipEvent: 
                generateOn(node, info, actions); 
                break;
		    case ASNode::Break: 
                actions.push_back(new ValueAction(256, 0)); 
                break;
		    case ASNode::Continue: 
                actions.push_back(new ValueAction(257, 0)); 
                break;
		    case ASNode::Return: 
                generateReturn(node, info, actions); 
                break;
  		    case ASNode::Value: 
                generateValue(node, info, actions); 
                break;
 		    case ASNode::Constant: 
                generateConstant(node, info, actions); 
                break;
 		    case ASNode::Number: 
                generateNumber(node, info, actions); 
                break;
 		    case ASNode::String: 
                generateString(node, info, actions); 
                break;
 		    case ASNode::Identifier: 
                generateIdentifier(node, info, actions); 
                break;
 		    case ASNode::Attribute:
                generateAttribute(node, info, actions); 
			    break;
 		    case ASNode::Method:
                generateMethod(node, info, actions); 
			    break;
		    case ASNode::NewObject:
                generateNew(node, info, actions); 
                break;
 		    case ASNode::Subscript:
                generateSubscript(node, info, actions);
			    break;
		    case ASNode::Function:
			    generateFunction(node, info, actions);
			    break;
		    case ASNode::DefineArray:
			    generateDefineArray(node, info, actions);
			    break;
		    case ASNode::DefineObject:
			    generateDefineObject(node, info, actions);
			    break;
		    case ASNode::DefineFunction:
			    generateDefineFunction(node, info, actions);
			    break;
		    case ASNode::DefineMethod:
			    generateDefineMethod(node, info, actions);
			    break;
		    case ASNode::DefineAttribute:
			    generateDefineAttribute(node, info, actions);
			    break;
		    case ASNode::DefineVariable:
			    generateDefineVariable(node, info, actions);
			    break;
		    case ASNode::PreInc:
		    case ASNode::PreDec:
			    generatePre(node, info, actions);
			    break;
		    case ASNode::PostInc:
		    case ASNode::PostDec:
                generatePost(node, info, actions);
			    break;
		    case ASNode::Plus:
		    case ASNode::Minus:
                generateSign(node, info, actions);
			    break;
		    case ASNode::Not:
                generateNot(node, info, actions);
			    break;
            case ASNode::BitNot:
                generateBitNot(node, info, actions);
			    break;
            case ASNode::DeleteObject:
                generateDelete(node, info, actions);
                break;
		    case ASNode::Add:
		    case ASNode::Sub:
		    case ASNode::Mul:
		    case ASNode::Div:
		    case ASNode::Mod:
		    case ASNode::BitAnd:
		    case ASNode::BitOr:
		    case ASNode::BitXOr:
		    case ASNode::LSL:
		    case ASNode::LSR:
		    case ASNode::ASR:
		    case ASNode::Equal:
		    case ASNode::NotEqual:
		    case ASNode::LessThan:
		    case ASNode::GreaterThan:
		    case ASNode::LessThanEqual:
		    case ASNode::GreaterThanEqual:
		    case ASNode::And:
		    case ASNode::Or:
            case ASNode::InstanceOf:
			    generateBinary(node, info, actions);
			    break;
		    case ASNode::Select:
                generateSelect(node, info, actions);
			    break;
		    case ASNode::Assign:
		    case ASNode::AssignAdd:
		    case ASNode::AssignSub:
		    case ASNode::AssignMul:
		    case ASNode::AssignDiv:
		    case ASNode::AssignMod:
		    case ASNode::AssignBitAnd:
		    case ASNode::AssignBitOr:
		    case ASNode::AssignBitXOr:
		    case ASNode::AssignLSL:
		    case ASNode::AssignLSR:
		    case ASNode::AssignASR:
			    generateAssignment(node, info, actions);
			    break;
   		    default:
    		    break;
        }
    }
	void generateScript(ASNode* node, ASInfo* info, list<Coding*>& actions)
	{
        list<Coding*>array;

        ASNode** ptr = node->getChildren();
        int count = node->count();
        int i=0;

        if (node->getType() == ASNode::Array && info->useStrings)
			array.push_back(new TableAction(info->strings));
    
        for (i=0; i<count; i++, ptr++)
        {
            discardValues(*ptr);
            generate(*ptr, info, array);
        }

        switch (node->getType())
        {
            case ASNode::Array: 
                actions.push_back(new ASArray(Coding::Array, array)); 
                break;
            case ASNode::Button: 
                actions.push_back(new ASArray(Coding::Button, array)); 
                break;
            case ASNode::MovieClip: 
                actions.push_back(new ASArray(Coding::MovieClip, array)); 
                break;
        }
    }
    void generateList(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** ptr = node->getChildren();
        int count = node->count();
        int i=0;

        for (i=0; i<count; i++, ptr++)
        {
            discardValues(*ptr);
            generate(*ptr, info, actions);
        }
    }
    void generateExpressionList(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** ptr = node->getChildren();
        int count = node->count();
        int i=0;

        for (i=0; i<count; i++, ptr++)
        {
            generate(*ptr, info, actions);

 //           if ((node->getStatus() == DISCARD))
 //           {
//                actions.push_back(new PushAction(new RegisterIndex(0)));
 //               actions.push_back(new Action(Coding::Pop));
 //           }
        }
    }
    void generateIf(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        unsigned int size = node->count();

        list<Coding*>trueActions;
        int offsetToNext = 0;

        list<Coding*>falseActions;
        int offsetToEnd = 0;

        bool addJump = false;

        /*
         * Fall through the different number of children
         */ 
        switch (size)
        {
        case 3:
			discardValues(children[2]);
			generate(children[2], info, falseActions);
			offsetToEnd = actionLength(falseActions);
            addJump = offsetToEnd != 0;					
        case 2:
			discardValues(children[1]);
			generate(children[1], info, trueActions);
            offsetToNext = actionLength(trueActions);								
        case 1:
			generate(*children, info, actions);
        }

#ifdef _DEBUG  
        /*
         * if the statements in the true clause end with break or continue 
         * then there is no need to jump to the end of the if statement
         */
        if (trueActions.empty() && size == 3)
        {
            trueActions.push_back(new ValueAction(Coding::Jump, 0));
            offsetToNext += 5;
            addJump = false;
        }
#endif
/*
        if (trueActions.empty() == false)
        {
            int lastType = trueActions.back()->getType();
            
            if (lastType == 256 || lastType == 257)
                addJump = false;
        }
*/        
        if (addJump)
            offsetToNext += 5; // Length of jump tag
            
        actions.push_back(new Action(Coding::Not));
        actions.push_back(new ValueAction(Coding::If, offsetToNext));
        
        for (list<Coding*>::iterator i=trueActions.begin(); i != trueActions.end(); i++)
		    actions.push_back(*i);
        
        if (addJump == true && offsetToEnd > 0)
            actions.push_back(new ValueAction(Coding::Jump, offsetToEnd));
            
        for (list<Coding*>::iterator i=falseActions.begin(); i != falseActions.end(); i++)
		    actions.push_back(*i);
    }
    void generateDo(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();

        list<Coding*>block;
        int blockLength = 0;

        list<Coding*>condition;
        int conditionLength = 0;

		discardValues(*children);
		generate(*children, info, block);
		blockLength = actionLength(block);

        generate(children[1], info, condition);
		conditionLength = actionLength(condition) + 5; // include if
        condition.push_back(new ValueAction(Coding::If, -(blockLength+conditionLength)));

		// Replace any break and continue place holders with jump statements.
        int currentLength = 0;

		for (list<Coding*>::iterator i = block.begin(); i != block.end(); i++)
		{
			currentLength += (*i)->getLength(info->version);
        
			if ((*i)->getType() == 256)
            {
                ValueAction* action = static_cast<ValueAction*>(*i);

                action->setType(Coding::Jump);
                action->setValue(blockLength+conditionLength-currentLength);
            }
			else if ((*i)->getType() == 257)
            {
                ValueAction* action = static_cast<ValueAction*>(*i);

                action->setType(Coding::Jump);
                action->setValue(blockLength-currentLength);
            }
		}

        for (list<Coding*>::iterator i=block.begin(); i != block.end(); i++)
		    actions.push_back(*i);

        for (list<Coding*>::iterator i=condition.begin(); i != condition.end(); i++)
		    actions.push_back(*i);
    }
    void generateWhile(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        unsigned int size = node->count();

        list<Coding*>block;
        int blockLength = 0;

        list<Coding*>condition;
        int conditionLength = 0;

        /*
         * Drop through table generating actions for each child.
         */
        switch (size)
        {
        case 2:
			discardValues(children[1]);
			generate(children[1], info, block);
		    blockLength = actionLength(block) + 5; // include jump 							
        case 1:
		    generate(*children, info, condition);
            condition.push_back(new Action(Coding::Not));
            condition.push_back(new ValueAction(Coding::If, blockLength)); 
		    conditionLength = actionLength(condition);								
            block.push_back(new ValueAction(Coding::Jump, -(conditionLength+blockLength)));
        }

		// Replace any break and continue place holders with jump statements.
		int currentLength = conditionLength;
    
		for (list<Coding*>::iterator i = block.begin(); i != block.end(); i++)
		{
			currentLength += (*i)->getLength(info->version);

			if ((*i)->getType() == 256)
            {
                ValueAction* action = static_cast<ValueAction*>(*i);

                action->setType(Coding::Jump);
                action->setValue(blockLength+conditionLength-currentLength);
            }
			else if ((*i)->getType() == 257)
            {
                ValueAction* action = static_cast<ValueAction*>(*i);

                action->setType(Coding::Jump);
                action->setValue(-currentLength);
            }
		}

        for (list<Coding*>::iterator i=condition.begin(); i != condition.end(); i++)
		    actions.push_back(*i);

        for (list<Coding*>::iterator i=block.begin(); i != block.end(); i++)
		    actions.push_back(*i);
    }
    void generateFor(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        unsigned int size = node->count();

	    list<Coding*>initializeActions;
	    list<Coding*>conditionActions;
	    list<Coding*>iteratorActions;
	    list<Coding*>blockActions;

	    int initializeLength = 0;
	    int conditionLength = 0;
	    int blockLength = 0;
	    int iteratorLength = 0;

        /*
         * For loops should always have four children
         */
		generate(*children, info, initializeActions);
		initializeLength = actionLength(initializeActions);								

        generate(children[1], info, conditionActions);
		conditionLength = actionLength(conditionActions);								

		discardValues(children[2]);
		generate(children[2], info, iteratorActions);
		iteratorLength = actionLength(iteratorActions);								
            
		discardValues(children[3]);
		generate(children[3], info, blockActions);
		blockLength = actionLength(blockActions);								

        /*
         * Flash Compatibility: Check to see if a literal has just been pushed 
         * onto the the stack and test whether the value would evaluate to true.
         * If so set the value to false to avoid adding NOT action.
         */
        if (conditionLength > 0)
	    {
		    Coding* lastAction = conditionActions.back();
            int offset = blockLength+iteratorLength+5;

            if (lastAction->getType() == Coding::Push)
		    {
			    PushAction* push = static_cast<PushAction*>(lastAction);
			    Value* lastValue = push->back();

                if (lastValue->getType() == Value::_Boolean)
			    {
    			    Boolean* value = static_cast<Boolean*>(lastValue);

				    if (value->boolValue())
				    {
					    push->replace_back(new Boolean(false));
					    conditionActions.push_back(new ValueAction(Coding::If, offset));
					    conditionLength += 5;
				    }
			    }
			    else if (lastValue->getType() == Value::_Integer)
			    {
    			    Integer* value = static_cast<Integer*>(lastValue);

				    if (value->intValue() > 0)
				    {
					    push->replace_back(new Integer(0));
					    conditionActions.push_back(new ValueAction(Coding::If, offset));
					    conditionLength += 5;
				    }
			    }
			    else if (lastValue->getType() == Value::_Double)
			    {
    			    Double* value = static_cast<Double*>(lastValue);

				    if (value->doubleValue() > 0.0)
				    {
					    push->replace_back(new Double(0));
					    conditionActions.push_back(new ValueAction(Coding::If, offset));
					    conditionLength += 5;
				    }
			    }
			    else if (lastValue->getType() == Value::_String)
			    {
    			    String* value = static_cast<String*>(lastValue);

				    if (value->stringValue() != "0")
				    {
					    push->replace_back(new String("0"));
					    conditionActions.push_back(new ValueAction(Coding::If, offset));
					    conditionLength += 5;
				    }
			    }
		    }
		    else
		    {
                conditionActions.push_back(new Action(Coding::Not));
                conditionActions.push_back(new ValueAction(Coding::If, offset));
			    conditionLength += 6;
		    }
	    }

	    // Add the jump to the start of the condition block

	    iteratorLength += 5;
	    iteratorActions.push_back(new ValueAction(Coding::Jump, -(conditionLength+blockLength+iteratorLength)));

	    // Replace any break and continue place holders with jump statements.
	    int currentLength = conditionLength;

        for (list<Coding*>::iterator i = blockActions.begin(); i != blockActions.end(); i++)
	    {
		    currentLength += (*i)->getLength(info->version);
        
			if ((*i)->getType() == 256)
            {
                ValueAction* action = static_cast<ValueAction*>(*i);

                action->setType(Coding::Jump);
                action->setValue(blockLength+conditionLength+iteratorLength-currentLength);
            }
			else if ((*i)->getType() == 257)
            {
                ValueAction* action = static_cast<ValueAction*>(*i);

                action->setType(Coding::Jump);
                action->setValue(blockLength+conditionLength-currentLength);
            }
	    }

        for (list<Coding*>::iterator i=initializeActions.begin(); i != initializeActions.end(); i++)
            actions.push_back(*i);

        for (list<Coding*>::iterator i=conditionActions.begin(); i != conditionActions.end(); i++)
            actions.push_back(*i);

        for (list<Coding*>::iterator i=blockActions.begin(); i != blockActions.end(); i++)
            actions.push_back(*i);

        for (list<Coding*>::iterator i=iteratorActions.begin(); i != iteratorActions.end(); i++)
            actions.push_back(*i);
    }
    void generateForIn(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        unsigned int size = node->count();

	    list<Coding*>conditionActions;
	    list<Coding*>blockActions;

	    int conditionLength = 0;
	    int blockLength = 0;

	    addReference(actions, info, (children[1])->getValue());
	    actions.push_back(new Action(Coding::Enumerate));

	    // Set the enumerator variable with the current attribute

	    addReference(blockActions, info, (*children)->getValue());
	    addLiteral(blockActions, new RegisterIndex(0));		  
	    blockActions.push_back(new Action(Coding::SetVariable));
    	
	    // Translate the body of the for..in statement 
    	
	    if (size == 3)
	    {
		    discardValues(children[2]);
		    generate(children[2], info, blockActions);
	        blockLength = actionLength(blockActions) + 5; // includes jump
	    }

	    // Translate the clause of the for..in statement
	    conditionActions.push_back(new ValueAction(Coding::RegisterCopy, 0));
	    addLiteral(conditionActions, new Null());
	    conditionActions.push_back(new Action(Coding::Equals));
	    conditionActions.push_back(new ValueAction(Coding::If, blockLength)); 
	    conditionLength = actionLength(conditionActions);
	    // Add the jump to the start of the condition block
	    blockActions.push_back(new ValueAction(Coding::Jump, -(conditionLength+blockLength)));
        
	    // Replace any break and continue place holders with jump statements.
	    int currentLength = conditionLength;
        
	    for (list<Coding*>::iterator i=blockActions.begin(); i != blockActions.end(); i++)
	    {
		    currentLength += (*i)->getLength(info->version);
            
            if ((*i)->getType() == 256)
            {
                ValueAction* action = static_cast<ValueAction*>(*i);

                action->setType(Coding::Jump);
                action->setValue(blockLength-currentLength);
            }
			else if ((*i)->getType() == 257)
            {
                ValueAction* action = static_cast<ValueAction*>(*i);

                action->setType(Coding::Jump);
                action->setValue(-(conditionLength+currentLength));
            }
	    }
        
        for (list<Coding*>::iterator i=conditionActions.begin(); i != conditionActions.end(); i++)
            actions.push_back(*i);

        for (list<Coding*>::iterator i=blockActions.begin(); i != blockActions.end(); i++)
            actions.push_back(*i);
    }
    void generateWith(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** ptr = node->getChildren();
        int count = node->count();
        int i=0;

        list<Coding*>array;
        int length = 0;

        info->context.push_back("With");

        generate(*ptr++, info, actions);

        for (i=1; i<count; i++, ptr++)
        {
            discardValues(*ptr);
            generate(*ptr, info, array);
        }

		length = actionLength(array);
            
        actions.push_back(new ValueAction(Coding::With, length));

        for (list<Coding*>::iterator i = array.begin(); i != array.end(); i++)
		    actions.push_back(*i);

        info->context.pop_back();
    }
    void generateOn(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** ptr = node->getChildren();
        int count = node->count();

        int type = node->getType();
        int value = 0;

        int i=0;

        list<Coding*>array;

        if (type == ASNode::On)
        {
            for (i=0; i<count-1; i++, ptr++)
            {
                int code = getButtonEvent((*ptr)->getValue());

                if (code == 0)
                    value += (*ptr)->getValue()[0] << 9;
                else
                    value += code;
            }
        }
        else
        {
            for (i=0; i<count-1; i++, ptr++)
                value += getClipEvent((*ptr)->getValue());
        }

        if (info->useStrings)
			array.push_back(new TableAction(info->strings));
    
        generate(*ptr, info, array);

        actions.push_back(new ASEvent(type, value, array));
    }
    void generateReturn(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        int count = node->count();

        if (count == 0)
		{
			addLiteral(actions, new Void());
		}
		else
		{
            ASNode** ptr = node->getChildren();
            int i=0;

            for (i=0; i<count; i++, ptr++)
                generate(*ptr, info, actions);
		}
        actions.push_back(new Action(Coding::Return));
    }
    void generateValue(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        int count = node->count();

        /*
		 * If any of the children is a method call then generate the 
		 * actions for the method arguments. This ensures that the 
		 * arguments will be popped off the stack in the correct order.
		 */
        for (int i=count-1; i>=0; i--)
		{
            int childType = (*(children+i))->getType();
            string value = children[i]->getValue();

            unsigned int childCount = 0;

			if ((childType == ASNode::Function && value != "eval") || childType == ASNode::Method)
			{
				if ((childCount = (*(children+i))->count()) > 0)
				{
                    ASNode** grandChildren = (*(children+i))->getChildren();
                    unsigned int grandChildCount = (*(children+i))->count();

                    for (int j=grandChildCount-1; j>=0; j--)
						generate(*(grandChildren+j), info, actions);
                } 
                addLiteral(actions, childCount);
			}
		}				 
		/*
		 * Now generate the actions for each node that returns
	 	 * a value. Note that below methods do not generate 
		 * actions for their children since the parent node is 
	  	 * always a Value. Functions only do so if the parent 
		 * node is not a Value.
		 */
        generate(*children, info, actions);

        for (int i=1; i<count; i++)
        {
            if ((*(children+i))->getType() == ASNode::Function)
            {
                if (actions.back()->getType() == Coding::GetAttribute)
                {
                    Coding* last = actions.back();

                    actions.pop_back();
                    actions.push_back(new Action(Coding::ExecuteMethod));
                    delete last;
                }
                else
                {
                    actions.push_back(new Action(Coding::ExecuteFunction));
                }
            }
            else
                generate(*(children+i), info, actions);
        }
        
		if (node->getStatus() == DISCARD)
            actions.push_back(new Action(Coding::Pop));
    }
    void generateConstant(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
		if (isConstant(node->getValue()))
			addLiteral(actions, getConstant(node->getValue()));

		if ((node->getStatus() == DISCARD))
			actions.push_back(new Action(Coding::Pop));
    }
    void generateNumber(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
		string value(node->getValue());
        string zero("0");

        if (value == zero)
            addLiteral(actions, new Double(0));
        else if (value.substr(0, 2) == "0X" || value.substr(0, 2) == "0x")
            addLiteral(actions, new Integer(value));
		else if (value.find_first_of('.') != string::npos)
            addLiteral(actions, new Double(value));
		else
            addLiteral(actions, new Integer(value));

		if ((node->getStatus() == DISCARD))
			actions.push_back(new Action(Coding::Pop));
    }
    void generateString(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
		addReference(actions, info, node->getValue());

        if ((node->getStatus() == DISCARD))
            actions.push_back(new Action(Coding::Pop));
    }
    void generateIdentifier(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        string value = node->getValue();

		if (value == "null")
			addLiteral(actions, new Null());
		else if (value == "true")
			addLiteral(actions, new Boolean(true));
		else if (value == "false")
			addLiteral(actions, new Boolean(false));
		else if (isProperty(value))
		{
			if (info->inContext("With"))
			{
				addReference(actions, info, value);
                actions.push_back(new Action(Coding::GetVariable));
			}
			else if (info->inContext("setProperty"))
			{
				addLiteral(actions, getProperty(value));                
			}
			else
			{
				addReference(actions, info, "");
				addLiteral(actions, getProperty(value));                
                actions.push_back(new Action(Coding::GetProperty));
			}
		}
		else
		{
			addReference(actions, info, value);
            actions.push_back(new Action(Coding::GetVariable));
		}
		if ((node->getStatus() == DISCARD))
            actions.push_back(new Action(Coding::Pop));
    }
    void generateAttribute(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
		addReference(actions, info, node->getValue());
        actions.push_back(new Action(Coding::GetAttribute));

		if ((node->getStatus() == DISCARD))
            actions.push_back(new Action(Coding::Pop));
    }
    void generateMethod(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
		addReference(actions, info, node->getValue());
        actions.push_back(new Action(Coding::ExecuteMethod));
    }
    void generateNew(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** ptr = node->getChildren();
        unsigned int size = node->count();

        string value = node->getValue();

        for (int i=size-1; i>=0; i--)
			generate(ptr[i], info, actions);

		addLiteral(actions, size);
		addReference(actions, info, value);
        actions.push_back(new Action(Coding::NamedObject));
    }
    void generateSubscript(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        generate(*(node->getChildren()), info, actions);
        actions.push_back(new Action(Coding::GetAttribute));
    }
    void generateDefineArray(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** ptr = node->getChildren();
        int count = node->count();

        for (int i=count-1; i>=0; i--)
			generate(ptr[i], info, actions);

        addLiteral(actions, count);
        actions.push_back(new Action(Coding::NewArray));
    }
    void generateDefineObject(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** ptr = node->getChildren();
        int count = node->count();

        for (int i=0; i<count; i++, ptr++)
			generate(*ptr, info, actions);

        addLiteral(actions, count);
        actions.push_back(new Action(Coding::NewObject));
    }
    void generateDefineFunction(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        int count = node->count();

        string value = node->getValue();

        list<string>arguments;
        list<Coding*>block;

        if (count == 2)
		{
            if (children[0]->getType() == ASNode::List)
            {
                ASNode** grandChildren = children[0]->getChildren();
                unsigned int grandChildCount = children[0]->count();

                for (unsigned int i=0; i<grandChildCount; i++)
                    arguments.push_back(grandChildren[i]->getValue());
            }
            else
            {
                arguments.push_back((*children)->getValue());
            }
		}
		discardValues(*(children+count-1));
		generate(*(children+count-1), info, block);	
    				
		actions.push_back(new NewFunctionAction(value, arguments, block));
    }
    void generateDefineMethod(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        int count = node->count();

        list<Coding*>block;
        list<string>arguments;

        if (count == 2)
		{
            if (children[0]->getType() == ASNode::List)
            {
                ASNode** grandChildren = (*children)->getChildren();
                unsigned int grandChildCount = (*children)->count();

                for (unsigned int i=0; i<grandChildCount; i++, grandChildren++)
				    arguments.push_back((*grandChildren)->getValue());
            }
            else
            {
                arguments.push_back((*children)->getValue());
            }
		}
		generate(*(children+count-1), info, block);
    					
		actions.push_back(new NewFunctionAction("", arguments, block));
    }
    void generateDefineAttribute(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();

        generate(*children, info, actions);
        Coding* action = actions.back();
		actions.pop_back();	
        delete action;
		generate(children[1], info, actions);				
    }
    void generateDefineVariable(ASNode* node, ASInfo* info, list<Coding*>& actions)    
    {
        addReference(actions, info, node->getValue());
        actions.push_back(new Action(Coding::InitVariable));
    }
    void generatePre(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        int type = node->getType();

        generate(*children, info, actions);
        Coding* action = actions.back();
		actions.pop_back();
        delete action;
		generate(*children, info, actions);

        actions.push_back(new Action((type == ASNode::PreInc ? Coding::Increment : Coding::Decrement)));

		if ((node->getStatus() == DISCARD) == false)
            actions.push_back(new ValueAction(Coding::RegisterCopy, 0));

        actions.push_back(new Action(Coding::SetVariable));
    	
		if ((node->getStatus() == DISCARD) == false)
			addLiteral(actions, new RegisterIndex(0));		  
    }
    void generatePost(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        int type = node->getType();

		if ((node->getStatus() == DISCARD) == false)
			generate(*children, info, actions);

		generate(*children, info, actions);
        Coding* action = actions.back();
		actions.pop_back();
        delete action;
		generate(*children, info, actions);

        actions.push_back(new Action((type == ASNode::PostInc ? Coding::Increment : Coding::Decrement)));
        actions.push_back(new Action(Coding::SetVariable));
    }
    void generateSign(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        int type = node->getType();

		if ((*children)->getType() == ASNode::Number)
        {
            int value = Integer::hxtoi((*children)->getValue());

            addLiteral(actions, (type==ASNode::Plus ? value : -value));
        }
        else
		{
            if (type==ASNode::Plus)
            {
			    generate(*children, info, actions);
            }
            else
            {
			    addLiteral(actions, 0);
			    generate(*children, info, actions);

                actions.push_back(new Action(Coding::Subtract));
            }
		}
		if ((node->getStatus() == DISCARD))
            actions.push_back(new Action(Coding::Pop));
    }
    void generateNot(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();

        generate(*children, info, actions);
        actions.push_back(new Action(Coding::Not));

		if ((node->getStatus() == DISCARD))
            actions.push_back(new Action(Coding::Pop));
    }
    void generateBitNot(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();

        generate(*children, info, actions);

#ifdef WIN32
        unsigned long val[2];
        
        val[0] = 0xffe00000;
        val[1] = 0x41efffff;

	    addLiteral(actions, new Double(*(double*)val));
#endif
#ifndef WIN32
        unsigned int val[2];

        val[1] = 0x41efffff;
        val[0] = 0xffe00000;

	    addLiteral(actions, new Double(*(double*)val));
#endif

        actions.push_back(new Action(Coding::BitwiseXOr));

	    if ((node->getStatus() == DISCARD))
            actions.push_back(new Action(Coding::Pop));
    }
    void generateDelete(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        int count = node->count();

        for (int i=0; i<count; i++)
		    generate(children[i], info, actions);

		int lastType = actions.back()->getType();

		if (lastType == Coding::GetVariable)
        {
            Coding* action = actions.back();
            actions.pop_back();
            delete action;
        }

        actions.push_back(new Action(Coding::Delete));

		if ((node->getStatus() == DISCARD))
            actions.push_back(new Action(Coding::Pop));
    }
    void generateBinary(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        int count = node->count();

        int type = node->getType();

        int i=0;

	    list<Coding*>array;
	    int offset = 0;

	    /*
		 * For most node types we want to generate the actions for 
		 * the child nodes (if any) before adding the actions for 
		 * node type.
		 */ 
	    switch (type) 
	    {
		    // > and <= are synthesised using < and !, see below.
            case ASNode::GreaterThan:
		    case ASNode::LessThanEqual:
			    for (i=count-1; i>=0; i--)
				    generate(children[i], info, actions);
			    break;
		    // Code Logical And/Or generated using if actions, see below.
		    case ASNode::And: 
		    case ASNode::Or:
			    break;
		    default:
			    for (i=0; i<count; i++)
				    generate(children[i], info, actions);
			    break;
	    }

	    switch (type) 
	    {
		    case ASNode::Add: actions.push_back(new Action(Coding::Add)); break;
		    case ASNode::Sub: actions.push_back(new Action(Coding::Subtract)); break;
		    case ASNode::Mul: actions.push_back(new Action(Coding::Multiply)); break;
		    case ASNode::Div: actions.push_back(new Action(Coding::Divide)); break;
		    case ASNode::Mod: actions.push_back(new Action(Coding::Modulo)); break;
		    case ASNode::BitAnd: actions.push_back(new Action(Coding::BitwiseAnd)); break;
		    case ASNode::BitOr: actions.push_back(new Action(Coding::BitwiseOr)); break;
		    case ASNode::BitXOr: actions.push_back(new Action(Coding::BitwiseXOr)); break;
		    case ASNode::LSL: actions.push_back(new Action(Coding::LogicalShiftLeft)); break;
		    case ASNode::LSR: actions.push_back(new Action(Coding::LogicalShiftRight)); break;
		    case ASNode::ASR: actions.push_back(new Action(Coding::ArithmeticShiftRight)); break;
		    case ASNode::Equal: actions.push_back(new Action(Coding::Equals)); break;
		    case ASNode::LessThan: actions.push_back(new Action(Coding::Less)); break;
		    case ASNode::GreaterThan: actions.push_back(new Action(Coding::Less)); break;
		    case ASNode::InstanceOf: actions.push_back(new Action(Coding::InstanceOf)); break;
		    case ASNode::NotEqual: 
                actions.push_back(new Action(Coding::Equals)); 
                actions.push_back(new Action(Coding::Not)); 
                break;
		    case ASNode::LessThanEqual:
		    case ASNode::GreaterThanEqual:
			    actions.push_back(new Action(Coding::Less));
			    actions.push_back(new Action(Coding::Not));
			    break;
		    case ASNode::And:
            case ASNode::Or:
			    array.push_back(new Action(Coding::Pop));
    				
			    generate(*(children+1), info, array);
			    offset = actionLength(array);
    	
			    generate(*children, info, actions);

			    actions.push_back(new Action(Coding::Duplicate));

                if (type == ASNode::And)
			        actions.push_back(new Action(Coding::Not));
    	                
			    actions.push_back(new ValueAction(Coding::If, offset));

                for (list<Coding*>::iterator i=array.begin(); i != array.end(); i++)
                    actions.push_back(*i);
			    break;
		    default:
			    break;
	    }
	    if ((node->getStatus() == DISCARD))
		    actions.push_back(new Action(Coding::Pop));
    }	
    void generateSelect(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();

        list<Coding*>trueActions;
        int offsetToEnd = 0;

        list<Coding*>falseActions;
        int offsetToNext = 0;

		generate(children[2], info, falseActions);
  		offsetToNext = actionLength(falseActions) + 5;
            
		generate(children[1], info, trueActions);    
		offsetToEnd = actionLength(trueActions);

		generate(*children, info, actions);

        actions.push_back(new ValueAction(Coding::If, offsetToNext));

        for (list<Coding*>::iterator i=falseActions.begin(); i != falseActions.end(); i++)
		    actions.push_back(*i);
        
        actions.push_back(new ValueAction(Coding::Jump, offsetToEnd));
            
        for (list<Coding*>::iterator i=trueActions.begin(); i != trueActions.end(); i++)
		    actions.push_back(*i);

        if ((node->getStatus() == DISCARD))
            actions.push_back(new Action(Coding::Pop));
    }
    void generateAssignment(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        int type = node->getType();

	    generate(*children, info, actions);
    	
	    int lastType = actions.back()->getType();
    	
	    if (lastType == Coding::GetVariable || 
            lastType == Coding::GetAttribute || 
            lastType == Coding::GetProperty || 
            lastType == Coding::InitVariable)
        {
            Coding* last = actions.back();
            actions.pop_back();
            delete last;
        }

        if (type != ASNode::Assign)
		    generate(*children, info, actions);

	    generate(children[1], info, actions);

        if (node->getParent()->getType() == ASNode::Assign)
		    actions.push_back(new ValueAction(Coding::RegisterCopy, 0));

	    switch (type)
	    {
		    case ASNode::AssignAdd:
			    actions.push_back(new Action(Coding::Add));
			    break;
		    case ASNode::AssignSub:
			    actions.push_back(new Action(Coding::Subtract));
			    break;
		    case ASNode::AssignMul:
			    actions.push_back(new Action(Coding::Multiply));
			    break;
		    case ASNode::AssignDiv:
			    actions.push_back(new Action(Coding::Divide));
			    break;
		    case ASNode::AssignMod:
			    actions.push_back(new Action(Coding::Modulo));
			    break;
		    case ASNode::AssignBitAnd:
			    actions.push_back(new Action(Coding::BitwiseAnd));
			    break;
		    case ASNode::AssignBitOr:
			    actions.push_back(new Action(Coding::BitwiseOr));
			    break;
		    case ASNode::AssignBitXOr:
			    actions.push_back(new Action(Coding::BitwiseXOr));
			    break;
		    case ASNode::AssignLSL:
			    actions.push_back(new Action(Coding::LogicalShiftLeft));
			    break;
		    case ASNode::AssignLSR:
			    actions.push_back(new Action(Coding::LogicalShiftRight));
			    break;
		    case ASNode::AssignASR:
			    actions.push_back(new Action(Coding::ArithmeticShiftRight));
			    break;
		    default:
			    break;
	    }
        
	    if (lastType == Coding::GetProperty)
		    actions.push_back(new Action(Coding::SetProperty));
	    else if (lastType == Coding::GetAttribute)
        {
		    actions.push_back(new Action(Coding::SetAttribute));

            if (node->getParent()->getType() == ASNode::Assign)
                actions.push_back(new PushAction(new RegisterIndex(0)));
        }
	    else if (lastType == Coding::GetVariable)
        {
            if (node->getParent()->getType() == ASNode::ExpressionList)
		        actions.push_back(new ValueAction(Coding::RegisterCopy, 0));

		    actions.push_back(new Action(Coding::SetVariable));

            if (node->getParent()->getType() == ASNode::Assign)
                actions.push_back(new PushAction(new RegisterIndex(0)));
        }
	    else if (lastType == Coding::InitVariable)
		    actions.push_back(new Action(Coding::InitVariable));
    }	
    void generateFunction(ASNode* node, ASInfo* info, list<Coding*>& actions)
    {
        ASNode** children = node->getChildren();
        int count = node->count();

        int type = node->getType();
        string value = node->getValue();

        int i=0;

        if (type == ASNode::Function && value == "getProperty")
            info->context.push_back("getProperty");

        if (isFunction(value))
	    {
		    if (value == "delete")
		    {
			    generate(*children, info, actions);

			    int lastType = actions.back()->getType();

			    if (lastType == Coding::GetVariable)
                {
                    Coding* action = actions.back();
                    actions.pop_back();
                    delete action;
                }
			    actions.push_back(new Action(Coding::Delete));
		    }
		    else if (value == "duplicateMovieClip")
		    {
			    generate(*children, info, actions);
			    generate(*(children+1), info, actions);

                if (children[2]->getType() == ASNode::Number)
			    {
                    int level = 16384 + Integer::hxtoi(children[2]->getValue());
				    addLiteral(actions, new Integer(level));
			    }
			    else
			    {
				    addLiteral(actions, new Integer(16384));
				    generate(children[2], info, actions);
				    actions.push_back(new Action(Coding::Add));
			    }
			    actions.push_back(new Action(Coding::CloneSprite));
		    }
		    else if (value == "eval")
		    {
			    generate(*children, info, actions);

                if (node->getParent()->getType() == ASNode::Value)
                {
                    int index = node->getParent()->indexOf(node);

                    if (index > -1 && index < (int)(node->getParent()->count() - 1))
                    {
                        int siblingType = node->getParent()->get(index+1)->getType();

                        if (siblingType == ASNode::Function || siblingType == ASNode::Method)
                            ;
                        else
                            actions.push_back(new Action(Coding::GetVariable));
                    }
                }
                else if (node->getParent()->getType() != ASNode::Value && node->count() == 1 && children[0]->getType() != ASNode::Number && children[0]->getType() != ASNode::String)
                    actions.push_back(new Action(Coding::GetVariable));
		    }
		    else if (value == "fscommand")
		    {
			    bool isCommandString = (*children)->getType() == ASNode::String;
			    bool isArgumentString = children[1]->getType() == ASNode::String;

			    if (isCommandString && isArgumentString)
			    {
				    actions.push_back(new StringAction(Coding::GetUrl, (*children)->getValue(), children[1]->getValue()));
			    }
			    else
			    {
				    if (isCommandString)
				    {
					    addReference(actions, info, (*children)->getValue());
				    }
				    else
				    {
					    addReference(actions, info, "FSCommand:");
					    generate(*children, info, actions);
					    actions.push_back(new Action(Coding::StringAdd));
				    }
				    generate(children[1], info, actions);

				    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToLevel));
			    }
		    }
		    else if (value == "getProperty")
		    {
			    int propertyValue = getProperty(children[1]->getValue());

			    generate(*children, info, actions);
			    addLiteral(actions, new Integer(propertyValue));
			    actions.push_back(new Action(Coding::GetProperty));
		    }
		    else if (value == "getURL")
		    {
                string get("get");
                string GET("GET");
                string post("post");
                string POST("POST");


			    switch(count)
			    {
				    case 1:        
					    if ((*children)->getType() == ASNode::String)
					    {
						    actions.push_back(new StringAction(Coding::GetUrl, (*children)->getValue(), ""));
					    }
					    else
					    {
						    generate(*children, info, actions);
						    addReference(actions, info, "");
						    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToLevel));
					    }
					    break;
				    case 2:
					    if ((*children)->getType() == ASNode::String && children[1]->getType() == ASNode::String)
					    {
						    actions.push_back(new StringAction(Coding::GetUrl, (*children)->getValue(), children[1]->getValue()));
					    }
					    else 
					    {
						    generate(*children, info, actions);
						    generate(children[1], info, actions);
						    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToLevel));
					    }
					    break;
				    case 3:
					    generate(*children, info, actions);
					    generate(children[1], info, actions);
    					
					    if (children[2]->getValue() == get || children[2]->getValue() == GET)
						    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToLevelWithGet));
					    else if (children[2]->getValue() == post || children[2]->getValue() == POST)
						    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToLevelWithPost));
					    else
						    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToLevel));
					    break;
				    default:
					    break;
			    }
		    }
		    else if (value == "getVersion")
		    {
			    addLiteral(actions, new String("/:$version"));
			    actions.push_back(new Action(Coding::GetVariable));
		    }
		    else if (value == "gotoAndPlay")
		    {
			    int index = node->count()-1;
            
			    if (children[index]->getType() == ASNode::Number)
			    {
				    int frameNumber = Integer::hxtoi(children[index]->getValue()) - 1;

				    actions.push_back(new ValueAction(Coding::GotoFrame, frameNumber));
				    actions.push_back(new Action(Coding::Play));
			    }
			    else
			    {
				    generate(children[index], info, actions);
				    actions.push_back(new ValueAction(Coding::GotoFrame2, 1));
			    }
		    }
		    else if (value == "gotoAndStop")
		    {
			    int index = node->count()-1;
            
			    if (children[index]->getType() == ASNode::Number)
			    {
				    int frameNumber = Integer::hxtoi(children[index]->getValue()) - 1;
				    actions.push_back(new ValueAction(Coding::GotoFrame, frameNumber));
			    }
			    else
			    {
				    generate(children[index], info, actions);
				    actions.push_back(new ValueAction(Coding::GotoFrame2, 0));
			    }
		    }
		    else if (value == "hitTest")
		    {
			    for (i=count-1; i>=0; i--)
				    generate(children[i], info, actions);

			    addLiteral(actions, count);
			    addReference(actions, info, value);
			    actions.push_back(new Action(Coding::ExecuteFunction));
		    }
		    else if (value == "loadMovie")
		    {
                string get("get");
                string GET("GET");

			    switch(count)
			    {
				    case 2:
					    if (children[1]->getType() == ASNode::Number)
					    {
                            string arg = "_level";
                            arg += children[1]->getValue();

						    actions.push_back(new StringAction(Coding::GetUrl, (*children)->getValue(), arg));
					    }
					    else 
					    {
                            generate(*children, info, actions);
						    generate(children[1], info, actions);
    						
						    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToTarget));
					    }
					    break;
				    case 3:
						generate(*children, info, actions);
						generate(children[1], info, actions);

					    if (children[2]->getValue() == get || children[2]->getValue() == GET)
						    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToTargetWithGet));
					    else
						    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToTargetWithPost));
					    break;
				    default:
					    break;
			    }
		    }
		    else if (value == "loadVariables")
		    {
                string get("get");
                string GET("GET");

                switch(count)
			    {
				    case 2:
					    generate(*children, info, actions);
					    generate(children[1], info, actions);
    					
					    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::VariablesToTarget));
					    break;
				    case 3:
					    generate(*children, info, actions);
					    generate(children[1], info, actions);

					    if (children[2]->getValue() == get || children[2]->getValue() == GET)
						    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::VariablesToTargetWithGet));
					    else
						    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::VariablesToTargetWithPost));
					    break;
				    default:
					    break;
			    }
		    }
		    else if (value == "nextFrame")
		    {
			    actions.push_back(new Action(Coding::NextFrame));
		    }
		    else if (value == "nextScene")
		    {
			    actions.push_back(new ValueAction(Coding::GotoFrame, 0));
		    }
		    else if (value == "Number")
		    {
			    generate(*children, info, actions);
			    actions.push_back(new Action(Coding::ToNumber));
		    }
		    else if (value == "play")
		    {
			    actions.push_back(new Action(Coding::Play));
		    }
		    else if (value == "prevFrame")
		    {
			    actions.push_back(new Action(Coding::PrevFrame));
		    }
		    else if (value == "prevScene")
		    {
			    actions.push_back(new ValueAction(Coding::GotoFrame, 0));
		    }
		    else if (value == "print")
		    {
			    addReference(actions, info, children[1]->getValue());
			    generate(*children, info, actions);
			    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToLevel));
		    }
		    else if (value == "printAsBitmap")
		    {
			    addReference(actions, info, children[1]->getValue());
			    generate(*children, info, actions);
			    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToLevel));
		    }
		    else if (value == "removeMovieClip")
		    {
			    for (i=0; i<count; i++, children++)
				    generate(*children, info, actions);

			    actions.push_back(new Action(Coding::RemoveSprite));
		    }
		    else if (value == "set")
		    {
			    for (i=0; i<count; i++, children++)
				    generate(*children, info, actions);

			    actions.push_back(new Action(Coding::SetVariable));
		    }
		    else if (value == "setProperty")
		    {
			    for (i=0; i<count; i++, children++)
				    generate(*children, info, actions);

			    actions.push_back(new Action(Coding::SetProperty));
		    }
		    else if (value == "startDrag")
		    {
			    if (count > 2) {
				    generate(children[2], info, actions);
				    generate(children[3], info, actions);
				    generate(children[4], info, actions);
				    generate(children[5], info, actions);
				    addLiteral(actions, new Integer(1));
				    generate(children[1], info, actions);
			    }
			    else if (count == 2) {
				    addLiteral(actions, 0);
				    generate(children[1], info, actions);
			    }
			    else
			    {
				    addLiteral(actions, 0);
				    addLiteral(actions, 0);
			    }
			    generate(*children, info, actions);

			    actions.push_back(new Action(Coding::StartDrag));
		    }
		    else if (value == "stop")
		    {
			    actions.push_back(new Action(Coding::Stop));
		    }
		    else if (value == "stopAllSounds")
		    {
			    actions.push_back(new Action(Coding::StopSounds));
		    }
		    else if (value == "stopDrag")
		    {
			    actions.push_back(new Action(Coding::EndDrag));
		    }
		    else if (value == "String")
		    {
			    generate(*children, info, actions);
			    actions.push_back(new Action(Coding::ToString));
		    }
		    else if (value == "targetPath")
		    {
			    for (i=0; i<count; i++, children++)
				    generate(*children, info, actions);

			    actions.push_back(new Action(Coding::GetTarget));
		    }
		    else if (value == "toggleHighQuality")
		    {
			    actions.push_back(new Action(Coding::ToggleQuality));
		    }
		    else if (value == "trace")
		    {
			    for (i=0; i<count; i++, children++)
				    generate(*children, info, actions);

                actions.push_back(new Action(Coding::Trace));
		    }
		    else if (value == "typeof")
		    {
			    for (i=0; i<count; i++, children++)
				    generate(*children, info, actions);

			    actions.push_back(new Action(Coding::GetType));
		    }
		    else if (value == "unloadMovie")
		    {
			    if ((*children)->getType() == ASNode::Number)
			    {
                    string arg = "_level";
                    arg += children[0]->getValue();

				    actions.push_back(new StringAction(Coding::GetUrl, "", arg.c_str()));
			    }
			    else
			    {
				    addLiteral(actions, new String(""));
				    generate(*children, info, actions);
				    actions.push_back(new ValueAction(Coding::GetUrl2, Coding::MovieToTarget));
			    }
		    }
		    else if (value == "void")
		    {
			    for (i=0; i<count; i++, children++)
				    generate(*children, info, actions);

			    actions.push_back(new Action(Coding::Pop));
			    addLiteral(actions, new Void());
		    }
		    else 
		    {
			    for (i=0; i<count; i++, children++)
				    generate(*children, info, actions);

			    addReference(actions, info, value);
			    actions.push_back(new Action(Coding::ExecuteFunction));
		    }
	    }
	    else
	    {
		    if (value == "parseInt")
		    {
			    for (i=count-1; i>=0; i--)
				    generate(children[i], info, actions);

			    addLiteral(actions, count);
			    addReference(actions, info, value);
			    actions.push_back(new Action(Coding::ExecuteFunction));
		    }
            else
            {
			    for (i=count-1; i>=0; i--)
				    generate(children[i], info, actions);

                addLiteral(actions, count);
                addReference(actions, info, value);
                actions.push_back(new Action(Coding::ExecuteFunction));
            }
	    }	
	    if ((node->getStatus() == DISCARD) && isValueFunction(value))
			actions.push_back(new Action(Coding::Pop));

        if (type == ASNode::Function && value == "getProperty")
            info->context.push_back("getProperty");
   }

    void addReference(list<Coding*>& actions, ASInfo* info, string literal)
    {
        int index = info->indexOf(literal);

        if (actions.size() > 0)
	    {
		    int lastType = actions.back()->getType();
        
		    if (lastType == Coding::Push)
            {
                PushAction* push = static_cast<PushAction*>(actions.back());

                if (info->useStrings && index != -1)
                   push->add(new TableIndex(index));
                else
                    push->add(new String(literal));
            }
		    else
            {
                if (info->useStrings && index != -1)
			        actions.push_back(new PushAction(new TableIndex(index)));
                else
			        actions.push_back(new PushAction(new String(literal)));
            }
	    }
	    else
	    {
            if (info->useStrings && index != -1)
			    actions.push_back(new PushAction(new TableIndex(index)));
            else
			    actions.push_back(new PushAction(new String(literal)));
	    }
    }
    void addLiteral(list<Coding*>& actions, int literal)
    {
        Value* value = NULL;

        if (literal == 0)
            value = new Double(0.0);
        else
            value = new Integer(literal);

        addLiteral(actions, value);
    }

    void addLiteral(list<Coding*>& actions, translate::Value* literal)
    {
/*
        if (literal->getType() == Value::_Integer)
        {
            Integer* integer = static_cast<Integer*>(literal);

            if (integer->intValue() == 0)
            {
                delete literal;
                literal = new Double(0.0);
            }
        }
*/
        if (actions.size() > 0)
	    {
		    int lastType = actions.back()->getType();
        
		    if (lastType == Coding::Push)
            {
                PushAction* push = static_cast<PushAction*>(actions.back());
                push->add(literal);
            }
		    else
			    actions.push_back(new PushAction(literal));
	    }
	    else
	    {
		    actions.push_back(new PushAction(literal));
	    }
    }

    int actionLength(list<Coding*>& array)
    {
	    int length = 0;
    	
        for (list<Coding*>::iterator i = array.begin(); i != array.end(); i++)
            length += (*i)->getLength(0);

	    return length;
    }	
    void discardValues(ASNode* node)
    {
	    node->setStatus(DISCARD);
    	
	    if (node->getType() == ASNode::List)
	    {
            ASNode** children = node->getChildren();
            int count = node->count();

		    for (int i=0; i<count; i++, children++)
			    discardValues(*children);
	    }
    }

    string pathToFile(string fileName)
    {
        list<string>::iterator i = pathNames.begin();
        string pathname = "";
        string canonpath = "";
        bool search = true;

        if (fileName.at(0) == '"')
           fileName = fileName.substr(1);
        if (fileName.at(fileName.length()-1) == '"')
           fileName = fileName.substr(0, fileName.length()-1);

        while (search && i != pathNames.end())
        {
            pathname = *i + separator + fileName;

            for (unsigned int i=0; i<pathname.length(); i++)
            {
#ifdef WIN32
                if (pathname.at(i) == '/') 
                    canonpath.append(1, separator);
#else
                if (pathname.at(i) == '\\') 
                    canonpath.append(1, separator);
#endif
                else
                    canonpath.append(1, pathname.at(i));
            }

            FILE* input = fopen(canonpath.c_str(), "rb");

            if (input != 0)
            {
                pathname = canonpath;
                search = false;
            }
            fclose(input);
        }
        return search ? "" : pathname;
    }

#ifdef WIN32
    static const char separator = '\\';
#endif
#ifndef WIN32
    static const char separator = '/';
#endif
    stringstream script;

    string message;
    string filename;
    string line;
    int lineNumber;
    int columnNumber;
    int error;

    unsigned char* data;
    size_t length;

    map<string, int>buttonEvents;
    map<string, int>clipEvents;
    map<string, Value*>constants;
    map<string, int>properties;
	map<string, string>definitions;

    set<string>functions;
    set<string>valueFunctions;

    vector<string>files;
    vector<int>lines;
    vector<string>codes;
    list<string>pathNames;
};

ASParser* CALL Parser()
{
    ASParser* parser = new ASParserImpl();

    return parser;
}

}
