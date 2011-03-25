/*
 *  FSNewFunction22.h
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

#ifndef __FSNewFunction2_h__
#define __FSNewFunction2_h__

#include "FSActionObject.h"

#include "FSRegisterVariable.h"
#include "FSVector.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSRegisterVariable>;
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSActionObject*>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
/**
 * The %FSNewFunction2 action is used to create a user-defined function.
 * 
<p>It was added in Flash 7 to improve the performance of function calls by allowing 
variables to be pre-loaded to a set of up to 256 internal registers and controlling 
the loading of pre-defined variables such as <em>_root</em>, <em>_parent</em>, 
<em>_global</em>, <em>super</em>, <em>this</em> and the <em>arguments</em> array 
containing the arguments passed to the function.</p>

<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSNewFunction2_1">name</a></td>
<td>A string defining the name of the function.</td>
</tr>

<tr>
<td><a name="FSNewFunction2_2">registerCount</a></td>
<td>The number of registers, up to 256, to allocate for storing variables.</td>
</tr>

<tr>
<td><a name="FSNewFunction2_3">optimizations</a></td>
<td>A code consisting of a number of flags that control the execution environment 
for the function.</td>
</tr>

<tr>
<td><a name="FSNewFunction2_4">arguments</a></td>
<td>An array of FSRegisterVariable objects containing the names of the arguments 
and whether they will be assigned to internal registers or defined in memory as 
local variables. The order of the FSRegisterVariable objects in the argument 
array indicate the order in which the values will be popped off the stack when 
the function is executed. The fist argument is popped from the stack first.</td>
</tr>

<tr>
<td><a name="FSNewFunction2_5">actions</a></td>
<td>An array containing the actions that are executed.</td>
</tr>

</table>

<p>The optimization attribute is a compound code, containing a number of flags that 
control how the environment of the function is initialised. Controlling the pre-defined 
variables that are created and pre-loading them into registers can significantly 
improve performance.</p>

<table class="datasheet">
<tr>
<th align="left">Environment</th>
<th align="left">Description</th>
</tr>

<tr><td>CreateSuper</td><td>Create and initialise the <em>super</em> variable with the parent class of the function.</td></tr>
<tr><td>CreateArguments</a></td><td>Create the <em>arguments</em> variable which contains the arguments passed to the function.</td></tr>
<tr><td>CreateThis</td><td>Create the and initialise the <em>this</em> variable with the object.</td></tr>
<tr><td>LoadThis</td><td>Pre-load the <em>this</em> variable into register number 1.</td></tr>
<tr><td>LoadArguments</td><td>Pre-load the <em>parent</em> variable into register number 2.</td></tr>
<tr><td>LoadSuper</td><td>Pre-load the <em>super</em> variable into register number 3.</td></tr>
<tr><td>LoadRoot</td><td>Pre-load the <em>_root</em> variable into register number 4.</td></tr>
<tr><td>LoadParent</td><td>Pre-load the <em>_parent</em> variable into register number 5.</td></tr>
<tr><td>LoadGlobal</td><td>Pre-load the <em>_global</em> variable into register number 5.</td></tr>
</table>

<p>The register numbers that the predefined variables, <em>this</em>, <em>parent</em>, 
<em>super</em>, <em>_root</em>, <em>_parent</em> and <em>_global</em> are assigned 
to are fixed. When specifying which of the functions arguments are also assigned 
to registers it is important avoid these locations otherwise the variables will 
be overwritten.</p>

<p>User-defined functions are also used to create methods for user-defined objects. 
The name of the function is omitted and the function definition is assigned to a 
variable which allows it to be referenced at a alter time. See the example below.</p>

<p>The arguments supplied to the function can be referenced by the name supplied 
in the arguments array.</p>

<p>All the action objects added are owned by the function. They will be deleted 
when the function definition is deleted.</p>

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
actions.add(new FSNewFunction2("increment", arguments, actions));
</pre>

<p>The function can then be referenced using it's name:</p>

<pre>
actions.add(new FSPush(1));
actions.add(new FSPush("increment"));
actions.add(FSAction.ExecuteFunction());
</pre>

<p>2. Defining a method.<br/>
When creating a user-defined object the name of the function can be omitted. 
Simply assign the function definition to a variable:</p>

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
actions.add(new FSNewFunction2(arguments, actions));
actions.add(FSAction.SetVariable()));
</pre>

<p>The function can then be executed by pushing the arguments onto the stack 
then calling the function assigned to the variable:</p>

<pre>
// Push argument(s) onto stack

actions.add(new FSPush(1));

// Get the variable that contains the function

actions.add(new FSPush(methodVariable));
actions.add(FSAction.GetVariable());

// Execute the function
actions.add(FSAction.ExecuteMethod());
</pre>

<p>3. Controlling the execution environment.<br/>
The code that defines the optimizations that improve execution performance is 
created by bitwise-ORing the individual flags together.</p>

<pre> 
int optimizations = FSNewFunction2.CreateSuper |  FSNewFunction2.PreloadSuper;
</pre>

<h1 class="datasheet">History</h1>

<p>The FSNewFunction class represents the ActionDefineFunction2 action of the 
Macromedia Flash (SWF) File Format Specification. It was introduced in Flash 7.</p>

 */  
    class DLL_DECL FSNewFunction2 : public FSActionObject
    {
public:
		enum optimizationType {
			LoadParent = 1, ///< Load the predefine variable, <em>_parent</em>, into register 5.
			LoadRoot = 2, ///< Load the predefine variable, <em>_root</em>, into register 4.
			CreateSuper = 4, ///< Create and initialized the predefined variable, <em>super</em>.
			LoadSuper = 8, ///< Load the predefined variable, <em>super</em>, into register 3.
			CreateArguments = 16, ///< Create and initialized the predefined variable, <em>arguments</em>.
			LoadArguments = 32, ///< Load the predefined variable, <em>arguments</em>, into register 2.
			CreateThis = 64, ///< Create and initialized the predefined variable, <em>this</em>.
			LoadThis = 128, ///< Load the predefined variable, <em>this</em>, into register 1.
			LoadGlobal = 32768 ///< Load the predefine variable, <em>_global</em>, into register 6.
		};

		FSNewFunction2(FSInputStream* aStream);

        FSNewFunction2() : FSActionObject(NewFunction2), 
			name(), 
			registerCount(0), 
			optimizations(0), 
			arguments(), 
			actions(),
			actionsLength(0)
		{}

		/** 
		 * Constructs an FSNewFunction2 with the specified name, argument names and actions to 
		 * be executed. The order of the RegisterVariables in the argument array indicate the order in 
		 * which the values will be popped off the stack when the function is executed. The 
		 * first argument is popped from the stack first.

			@param aString the name of the function.
			@param argumentArray an array of RegisterVariables listing the names of the arguments.
			@param actionArray the array of actions that define the operation performed by the function.
			*/
        FSNewFunction2(const char* aString, const FSVector<FSRegisterVariable>& argumentArray, const FSVector<FSActionObject*>& actionArray) : 
			FSActionObject(NewFunction2), 
			name(aString), 
			registerCount(0), 
			optimizations(0), 
			arguments(argumentArray), 
			actions(actionArray),
			actionsLength(0)
			{}

        /** 
		 * Constructs an anonymous FSNewFunction2 with the specified argument names and actions to be 
		 * executed. Use this constructor when defining functions that will be assigned to object variables 
		 * and used as methods. All the action objects added are owned by the FSNewFunction2 object. 
		 * They will be deleted when it is deleted.

			@param argumentArray an array of RegisterVariables listing the names of the arguments.
            @param actionArray the array of actions that define the operation performed by the function.
            */
        FSNewFunction2(const FSVector<FSRegisterVariable>& argumentArray, const FSVector<FSActionObject*>& actionArray) : 
			FSActionObject(NewFunction2), 
			name(), 
			registerCount(0), 
			optimizations(0), 
			arguments(argumentArray), 
			actions(actionArray),
			actionsLength(0)
			{}

        FSNewFunction2(const FSNewFunction2& rhs);

        ~FSNewFunction2();

        FSNewFunction2* clone() const { return new FSNewFunction2(*this); }

        const char* className() const;

        FSNewFunction2& operator= (const FSNewFunction2& rhs);

		/** Adds the name of an argument to the array of argument names.

			@param anArgument the name of an argument passed to the FSNewFunction object.
			*/
        void add(FSRegisterVariable& anArgument) { arguments.push_back(anArgument); }

		/** Adds all the register variables in the array to the end of the arguments array.

            @param anArray of FSRegisterVariable objects identifying the argument names and 
			the registers that may be optionally loaded into.
            */
        void add(const FSVector<FSRegisterVariable>& anArray);

        /** Add an action to the end of the actions array. The action is owned by the FSNewFunction2 object.

            @param anAction an FSActionObject.
            */
        void add(FSActionObject* anAction) { actions.push_back(anAction); }

        /** Adds all the action objects in the array to the end of the actions array. All the action objects added are owned by the FSNewFunction2 object.

            @param anArray of FSActionObject objects.
            */
        void add(const FSVector<FSActionObject*>& anArray);

        /** Gets the name of the function.

            @return the name of the function.
            */
        const char* getName() { return name.c_str(); }

        /** Sets the name of the function.

            @param aString the name of the function.
            */
        void setName(const char* aString) { name = aString; }

		/** 
		 * Gets the number of registers to allocate for function variables.
	 	 * 
		 * @return the number of registers to allocate.
		 */
		int getRegisterCount() { return registerCount; }
		
		/**
		 * Sets the number of registers to allocate for function variables. Up to
		 * 256 registers may be allocated for each function.
		 * 
		 * @param count the number of registers to allocate.
		 */
		void setRegisterCount(int count) { registerCount = count; }

		/** 
		 * Get the code containing the compound flags that control the execution environment
		 * of the function or method.
		 *
		 * @return the code for the optimizations.
		 */
		int getOptimizations() { return optimizations; }
		
		/** 
		 * Set the code containing the compound flags that control the execution environment
		 * of the function or method.
		 *
		 * @param code the compound code can be created by bitwise-ORing the constants that 
		 * identify the optimizations performed.
		 */
		void setOptimizations(int code) { optimizations = code; }

        /** Gets the names of the function arguments.

            @return the array of argument names.
            */
        FSVector<FSRegisterVariable>& getArguments() { return arguments; } 

        /** Sets the names of the function arguments. 

            @param anArray an array of Strings listing the names of the arguments.
            */
        void setArguments(const FSVector<FSRegisterVariable>& anArray) { arguments = anArray; }

        /** Gets the actions.

            @return the array of actions executed.
            */
        FSVector<FSActionObject*>& getActions() { return actions; }

        /** Sets the actions. All the action objects added are owned by the FSNewFunction2 object.

            @param anArray the array of actions that define the operation performed by the function.
            */
        void setActions(const FSVector<FSActionObject*>& anArray);

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
        FSString name;

		int registerCount;
		int optimizations;

		FSVector<FSRegisterVariable> arguments;
        FSVector<FSActionObject*> actions;

		int actionsLength;
    };
}

#endif
