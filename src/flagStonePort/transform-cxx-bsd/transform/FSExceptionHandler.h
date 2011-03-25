/*
 *  FSExceptionHandler.h
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

#ifndef __FSExceptionHandler_h__
#define __FSExceptionHandler_h__ 1

#include "FSActionObject.h"
#include "FSVector.h"
#include "FSString.h"

#ifdef WIN32
#ifdef _WINDLL
DLL_TEMPLATE template class DLL_DECL transform::FSVector<transform::FSActionObject*>;
#endif // _WINDLL
#endif // WIN32

namespace transform
{
	/**
	 * The %FSExceptionHandler class is used to specify try..catch blocks so exceptions can be thrown 
	 * and handled when executing a series of actions.
	 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSExceptionHandler_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSExceptionHandler_1">register</a></td>
<td>The number of the register that the thrown object will be assigned to. Optional, Omitted if the variable attribute is set.</td>
</tr>

<tr>
<td><a name="FSExceptionHandler_2">variable</a></td>
<td>The variable in memory that the thrown object will be assigned to. Optional, Omitted if the register attribute is set.</td>
</tr>

<tr>
<td><a name="FSExceptionHandler_3">tryActions</a></td>
<td>The actions executed in the try block of the exception.</td>
</tr>

<tr>
<td><a name="FSExceptionHandler_4">catchActions </a></td>
<td>The actions executed in the catch block of the exception. Defining actions for the catch block is optional and may be set to the null object or an empty array if no actions will be executed.</td>
</tr>

<tr>
<td><a name="FSExceptionHandler_5">finalActions</a></td>
<td>The actions executed in a finally block of the exception. Defining actions for the finally block is optional and may be set to the null object or an empty array if no actions will be executed.</td>
</tr>

</table>

<p>The thrown object can be assigned to either one of the Flash Player's 256 internal registers or to a variable in memory. If a register number is set the variable name is set to null. Similarly if a variable name is set then the register number is set to zero.</p>

<p>The FSExceptionHandler class contains three arrays of actions supporting the standard syntax for an exception with try, catch and finally blocks. An exception is thrown by a Throw action which pops a value off the stack and assigns it to either a named variable or one of the Flash Player's internal registered so it can be processed by the actions in the catch block.</p>

<p>Exceptions may be nest to any level if a thrown exception is not handled by the immediate catch block it is propagated to the next handler in the exception hierarchy and so on until it is caught.</p>

<p>Both the catch and finally blocks are optional when defining an exception, the corresponding arguments in constructors and accessor methods may be set to null.</p>

<h1 class="datasheet">History</h1>

<p>The FSExceptionHandler represents the Try action introduced in Flash 7 and is used to directly support the exception handling syntax defined in ActionScript 2.0.</p>

	 */  
    class DLL_DECL FSExceptionHandler : public FSActionObject
    {
public:
        FSExceptionHandler(FSInputStream* aStream);

		/**
		 * Constructs a new exception handler with the thrown object assigned to a local variable.
		 *
		 * @param name the name of the variable that the thrown object will be assigned to.
	 	 * @param tryArray actions that will be executed in the try block of the exception.
		 * @param catchArray actions that will be executed in the catch block of the exception, if one is defined. This may be null is no catch block is required - the exception will be handled by another catch block higher in the exception tree.
		 * @param finalArray actions that will be executed in the finally block of the exception, if one is defined. This may be null is no finally block is required.
		 */
        FSExceptionHandler(const char* name, const FSVector<FSActionObject*>& tryArray, const FSVector<FSActionObject*>& catchArray, const FSVector<FSActionObject*>& finalArray) : 
			FSActionObject(ExceptionHandler),
			registerNumber(0),
			variable(name),
			tryLength(0),
			catchLength(0),
			finalLength(0),
			tryActions(tryArray),
			catchActions(catchArray),
			finalActions(finalArray)
			{}

		/**
	 	 * Constructs a new exception handler with the thrown object assigned to one of the 
		 * Flash Player's internal registers.
		 *
		 * @param index the number of the register that the thrown object will be assigned to.
		 * @param tryArray actions that will be executed in the try block of the exception.
		 * @param catchArray actions that will be executed in the catch block of the exception, if one is defined. This may be null is no catch block is required - the exception will be handled by another catche block higher in the exception tree.
		 * @param finalArray actions that will be executed in the finally block of the exception, if one is defined. This may be null is no finally block is required.
		 */
        FSExceptionHandler(int index, const FSVector<FSActionObject*>& tryArray, const FSVector<FSActionObject*>& catchArray, const FSVector<FSActionObject*>& finalArray) : 
			FSActionObject(ExceptionHandler),
			registerNumber(index),
			variable(), 
			tryLength(0),
			catchLength(0),
			finalLength(0),
			tryActions(tryArray),
			catchActions(catchArray),
			finalActions(finalArray)
			{}

        FSExceptionHandler(const FSExceptionHandler& rhs);

        ~FSExceptionHandler();

        FSExceptionHandler& operator= (const FSExceptionHandler& rhs);
        
        FSExceptionHandler* clone() const;

        const char* className() const;

        /** 
		 * Adds an action to the array of actions for the try block. The FSExceptionHandler object assumes 
		 * ownership of the action object.

            @param anAction a pointer to an action object.
            */
        void addToTry(FSActionObject* anAction) { tryActions.push_back(anAction); }

        /** Adds all the actions in an array to the array of actions for the try block. The FSExceptionHandler object assumes ownership of all the action objects in the array.

            @param anArray an array of pointers to action objects.
            */
        void addToTry(const FSVector<FSActionObject*>& anArray);

        /** 
		 * Adds an action to the array of actions for the catch block. The FSExceptionHandler object assumes 
		 * ownership of the action object.

            @param anAction a pointer to an action object.
            */
        void addToCatch(FSActionObject* anAction) { catchActions.push_back(anAction); }

        /** Adds all the actions in an array to the array of actions for the catch block. The FSExceptionHandler object assumes ownership of all the action objects in the array.

            @param anArray an array of pointers to action objects.
            */
        void addToCatch(const FSVector<FSActionObject*>& anArray);

        /** 
		 * Adds an action to the array of actions for the final block. The FSExceptionHandler object assumes 
		 * ownership of the action object.

            @param anAction a pointer to an action object.
            */
        void addToFinal(FSActionObject* anAction) { catchActions.push_back(anAction); }

        /** Adds all the actions in an array to the array of actions for the final block. The FSExceptionHandler object assumes ownership of all the action objects in the array.

            @param anArray an array of pointers to action objects.
            */
        void addToFinal(const FSVector<FSActionObject*>& anArray);

		/** Gets the name of the variable which the exception object is assigned to.

			@return the name of the function. Returns an empty string if the exception object
			will be assigned to a register.
			*/
		const char* getVariable() { return variable.c_str(); }
		
		/**
		* Sets the name of the variable that the exception object is assigned to.
		* 
		* @param name the name of the variable. May be an empty string if the exception object will
		* be signed to a register.
		*/
		void setVariable(const char* name) { 
			variable = name;
			registerNumber = 0;
		}

		/** 
		 * Gets the index of the register that the exception object is assigned to.
		 * 
		 * @return the number of register. Returns 0 if the exception object will be assigned
		 * to a local variable.
		 */
		int getRegister() { return registerNumber; }
		
		/**
		 * Sets the index of the register that the exception object is assigned to.
		 * 
		 * @param index the number of the register. May be 0 if the exception object
		 * will be assigned to a local variable.
		 */
		void setRegister(int index) { 
			registerNumber = index; 
			variable = "";
		}

        /** Get the array of actions that are executed in the try block.

            @return the array of action objects.
            */
        FSVector<FSActionObject*>& getTryActions() { return tryActions; }

        /** Set the array of actions that will be executed in the try block. The FSExceptionHandler object assumes ownership of all the action objects in the array.

            @param anArray the array of action objects.
            */
        void setTryActions(const FSVector<FSActionObject*>& anArray);

        /** Get the array of actions that are executed in the catch block.

            @return the array of action objects.
            */
        FSVector<FSActionObject*>& getCatchActions() { return catchActions; }

        /** Set the array of actions that will be executed in the catch block. The FSExceptionHandler object assumes ownership of all the action objects in the array.

            @param anArray the array of action objects.
            */
        void setCatchActions(const FSVector<FSActionObject*>& anArray);

		/** Get the array of actions that are executed in the final block.

            @return the array of action objects.
            */
        FSVector<FSActionObject*>& getFinalActions() { return finalActions; }

        /** Set the array of actions that will be executed in the final block. The FSExceptionHandler object assumes ownership of all the action objects in the array.

            @param anArray the array of action objects.
            */
        void setFinalActions(const FSVector<FSActionObject*>& anArray);

		int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);

private:
		int registerNumber;
		FSString variable;

		int tryLength;
		int catchLength;
		int finalLength;

        FSVector<FSActionObject*> tryActions;
        FSVector<FSActionObject*> catchActions;
        FSVector<FSActionObject*> finalActions;
    };
}

#endif
