/*
 *  FSNewFunction.h
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

#ifndef __FSNewFunction_h__
#define __FSNewFunction_h__

#include "FSActionObject.h"

#include "FSString.h"
#include "FSVector.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSString>;
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSActionObject*>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * The %FSNewFunction action is used to create a user-defined function.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSNewFunction_0">type</a></td>
<td>Identifies the data structure when it is encoded. The type attribute is read-only and may be used when iterating through an array of FSActionObjects to identify the object class without using run-time type checking.</td>
</tr>

<tr>
<td><a name="FSNewFunction_1">name</a></td>
<td>A string defining the name of the function.</td>
</tr>

<tr>
<td><a name="FSNewFunction_2">arguments</a></td>
<td>An array containing the names of the arguments. The order of the strings in the argument array indicate the order in which the values will be popped off the stack when the function is executed. The fist argument is popped from the stack first.</td>
</tr>

<tr>
<td><a name="FSNewFunction_3">actions</a></td>
<td>An array containing the actions that are executed.</td>
</tr>

</table>

<p>User-defined functions are also used to create methods for user-defined objects. The name of the function is omitted and the function definition is assigned to a variable which allows it to be referenced at a alter time. See the example below:</p>

<p>The arguments supplied to the function can be referenced by the name supplied in the arguments array.</p>

<p>All the action objects added are owned by the function. They will be deleted when the function definition is deleted.</p>

<h1 class="datasheet">Examples</h1>

<p>1. Define a function<br/>
Define a function that increments the value passed to it:</p>

<pre>
// List the names of the arguments

ArrayList arguments = new ArrayList();

arguments.add("value");

// Now define the actions performed by the function. Values passed to the function
// can be referenced by the name defined in the array of arguments.

ArrayList actions = new ArrayList();

actions.add(new FSPush("value"));
actions.add(FSAction.GetVariable());
actions.add(new FSPush(1));
actions.add(FSAction.Add());
actions.add(FSAction.Return());
actions.add(new FSNewFunction("increment", arguments, actions));
</pre>

<p>The function can then be referenced using it's name:</p>

<pre>
actions.add(new FSPush(1));
actions.add(new FSPush("increment"));
actions.add(FSAction.ExecuteFunction());
</pre>

<p>2. Defining a method.<br/>
When creating a user-defined object the name of the function can be omitted. Simply assign the function definition to a variable:</p>

<pre>
actions.add(new FSPush(methodVariable));

FSVector<FSString> arguments;

arguments.push_back("value");

ArrayList actions = new ArrayList();

actions.add(new FSPush("value"));
actions.add(FSAction.GetVariable());
actions.add(new FSPush(1));
actions.add(FSAction.Add());
actions.add(FSAction.Return());
actions.add(new FSNewFunction(arguments, actions));
actions.add(FSAction.SetVariable()));
</pre>

<p>The function can then be executed by pushing the arguments onto the stack then calling the function assigned to the variable:</p>

<pre>
// Push argument(s) onto stack

actions.add(new FSPush(1));

// Get the variable that contains the function

actions.add(new FSPush(methodVariable));
actions.add(FSAction.GetVariable());

// Execute the function
actions.add(FSAction.ExecuteFunction());
</pre>

<h1 class="datasheet">History</h1>

<p>The FSNewFunction class represents the ActionDefineFunction action of the Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 5.</p>

 */  
    class DLL_DECL FSNewFunction : public FSActionObject
    {
public:
        FSNewFunction(FSInputStream* aStream);

        FSNewFunction() : FSActionObject(NewFunction), name(), arguments(), actions() {}

        /** Constructs an FSNewFunction with the specified name, argument names and actions to be executed. The order of the strings in the argument array indicate the order in which the values will be popped off the stack when the function is executed. The first argument is popped from the stack first. All the action objects added are owned by the FSNewFunction object. They will be deleted when it is deleted.
    
            @param aString the name of the function.
            @param argumentArray an array of Strings listing the names of the arguments.
            @param actionArray the array of actions that define the operation performed by the function.
            */
        FSNewFunction(const char* aString, const FSVector<FSString>& argumentArray, const FSVector<FSActionObject*>& actionArray) : FSActionObject(NewFunction), name(aString), arguments(argumentArray), actions(actionArray) {}

        /** Constructs an anonymous FSNewFunction with the specified argument names and actions to be executed. Use this constructor when defining functions that will be assigned to object variables and used as methods. All the action objects added are owned by the FSNewFunction object. They will be deleted when it is deleted.

            @param argumentArray an array of Strings listing the names of the arguments.
            @param actionArray the array of actions that define the operation performed by the function.
            */
        FSNewFunction(const FSVector<FSString>& argumentArray, const FSVector<FSActionObject*>& actionArray) : FSActionObject(NewFunction), name(), arguments(argumentArray), actions(actionArray) {}

        FSNewFunction(const FSNewFunction& rhs);

        ~FSNewFunction();

        FSNewFunction* clone() const { return new FSNewFunction(*this); }

        const char* className() const;

        FSNewFunction& operator= (const FSNewFunction& rhs);

        /** Add the name of an argument to the end of the arguments array.

            @param aString the name of a argument.
            */
        void add(const char* aString) { arguments.push_back(FSString(aString)); }

        /** Add the name of an argument to the end of the arguments array.

            @param aString the name of a argument.
            */
        void add(const FSString& aString) { arguments.push_back(aString); }

        /** Adds all the strings in the array to the end of the arguments array.

            @param anArray of strings.
            @param size the number of strings in the array.
            */
        void add(const char* anArray[], int size)
        {
            for (int i=0; i<size; i++)
                arguments.push_back(FSString(anArray[i]));
        }

        /** Adds all the string objects in the array to the end of the arguments array.

            @param anArray of FSString objects.
            */
        void add(const FSVector<FSString>& anArray)
        {
            for (FSVector<FSString>::const_iterator i = anArray.begin(); i != anArray.end(); i++)
                arguments.push_back(*i);
        }

        /** Add an action to the end of the actions array. The action is owned by the FSNewFunction object.

            @param anAction an FSActionObject.
            */
        void add(FSActionObject* anAction) { actions.push_back(anAction); }

        /** Adds all the action objects in the array to the end of the actions array. All the action objects added are owned by the FSNewFunction object.

            @param anArray of FSActionObject objects.
            */
        void add(const FSVector<FSActionObject*>& anArray);

        /** Gets the name of the function.

            @return the name of the function.
            */
        const char* getName() { return name.c_str(); }

        /** Gets the names of the function arguments.

            @return the array of argument names.
            */
        FSVector<FSString>& getArguments() { return arguments; } 

        /** Gets the actions.

            @return the array of actions executed.
            */
        FSVector<FSActionObject*>& getActions() { return actions; }

        /** Sets the name of the function.

            @param aString the name of the function.
            */
        void setName(const char* aString) { name = aString; }

        /** Sets the names of the function arguments. 

            @param anArray an array of Strings listing the names of the arguments.
            */
        void setArguments(const FSVector<FSString>& anArray) { arguments = anArray; }

        /** Sets the actions. All the action objects added are owned by the FSNewFunction object.

            @param anArray the array of actions that define the operation performed by the function.
            */
        void setActions(const FSVector<FSActionObject*>& anArray);

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSString name;
        FSVector<FSString> arguments;
        FSVector<FSActionObject*> actions;
    };
}

#endif
