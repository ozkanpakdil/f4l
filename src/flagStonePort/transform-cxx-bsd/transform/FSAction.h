/*
 *  Transform.h
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

#ifndef __FSAction_h__
#define __FSAction_h__ 1

#include "FSActionObject.h"

namespace transform
{
/** 
The %FSAction class is used to represent stack-based actions, defined by simple byte-codes, that are executed by the Flash Player.

<p>The operations supported by the FSAction class are:</p>

<h1 class="datasheet">Stack Manipulation</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>Pop</td>
    <td>Pop value from the top of the stack.</td>
    <td nowrap>(valueA -- )</td>
    <td nowrap>(4 -- )</td></tr>
<tr valign="top"><td>Duplicate</td>
    <td>Duplicate the value at the top of the stack.</td>
    <td nowrap>(valueA -- valueA valueA)</td>
    <td nowrap>(4 -- 4 4)</td></tr>
<tr valign="top"><td>Swap</td>
    <td>Swap the top two values on the stack.</td>
    <td nowrap>(valueA valueB -- valueB valueA)</td>
    <td nowrap>(4 3 -- 3 4)</td></tr>
</table>

<p>FSPush is used to push literals onto the Stack. See also FSRegisterCopy which 
copies the value on top of the Stack to one of the Flash Player's internal 
registers.</p>
    
<h1 class="datasheet">Arithmetic</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>Add</td>
    <td>Arithmetic Add: A + B</td>
    <td nowrap>(numA numB -- num)</td>
    <td nowrap>(4 3 -- 7)</td></tr>
<tr valign="top"><td>Subtract</td>
    <td>Arithmetic Subtract: A - B</td>
    <td nowrap>(numA numB -- num)</td>
    <td nowrap>(4 3 -- 1)</td></tr>
<tr valign="top"><td>Multiply</td>
    <td>Arithmetic Multiply: A * B</td>
    <td nowrap>(numA numB -- num)</td>
    <td nowrap>(4 3 -- 12)</td></tr>
<tr valign="top"><td>Divide</td>
    <td>Arithmetic Divide: A / B</td>
    <td nowrap>(numA numB -- num)</td>
    <td nowrap>(4 3 -- 1.333)</td></tr>
<tr valign="top"><td>Modulo</td>
    <td>Arithmetic Modulo: A % B</td>
    <td nowrap>(numA numB -- num)</td>
    <td nowrap>(4 3 -- 1)</td></tr>
<tr valign="top"><td>Increment</td>
    <td>Add 1 to the value on the stack.</td>
    <td nowrap>(num -- num)</td>
    <td nowrap>(3 -- 4)</td></tr>
<tr valign="top"><td>Decrement</td>
    <td>Subtracted 1 from the value on the stack.</td>
    <td nowrap>(num -- num)</td>
    <td nowrap>(4 -- 3)</td></tr>
</table>

<p>Arithmetic add is supported by two actions. IntegerAdd was introduced in Flash 4. 
It was replaced in Flash 5 by the more flexible Add action which is able to add 
any two numbers and also concatenate strings. If a string and a number are added 
then the number is converted to its string representation before concatenation.</p>

<h1 class="datasheet">Comparison</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>Less</td>
    <td>LessThan: A &lt; B</td>
    <td nowrap>(numA numB -- boolean)</td>
    <td nowrap>(10 9 -- 0 )</tr>
<tr valign="top"><td>StringLess</td>
    <td>String compare: stringA &lt; stringB</td>
    <td nowrap>(stringA stringB -- boolean)</td>
    <td nowrap>("abc" "ab" -- 0)</td></tr>
<tr valign="top"><td>Equals</td>
    <td>Equals: A == B</td>
    <td nowrap>(numA numB -- boolean)</td>
    <td nowrap>(23 23 -- 1 )</tr>
<tr valign="top"><td>StringEquals</td>
    <td>String compare: stringA == stringB</td>
    <td nowrap>(stringA stringB -- boolean)</td>
    <td nowrap>("abc" "abc" -- 1)</td></tr>
<tr valign="top"><td>StrictEquals</td>
    <td>Equals: A === B, are the types as well as the values equal.</td>
    <td nowrap>(valueA valueB -- boolean)</td>
    <td nowrap>("23" 23 -- 0 )</tr>
<tr valign="top"><td>Greater</td>
    <td>Greater Than: A > B</td>
    <td nowrap>(numA numB -- boolean)</td>
    <td nowrap>(10 9 -- 0 )</tr>
<tr valign="top"><td>StringGreater</td>
    <td>String compare: stringA > stringB</td>
    <td nowrap>(stringA stringB -- boolean)</td>
    <td nowrap>("abc" "ab" -- 0)</td></tr>
</table>

<p>The less than comparison is supported by IntegerLess introduced in Flash 4 
and Less introduced in Flash 5. The Less action is more flexible allowing comparison 
between any combination of two numbers and strings. In Flash 4 comparisons were 
only supported on values of the same type using either IntegerLess or StringLess.</p>

<p>The equals comparison is supported by IntegerEquals introduced in Flash 4 and 
Equals introduced in Flash 5. The Equals action is more flexible allowing 
comparison between any combination of two numbers and strings. In Flash 4 
comparisons were only supported on values of the same type using either
IntegerEquals or StringEquals.</p>
    
<h1 class="datasheet">Logical</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>And</td>
    <td>Logical And: A &amp;&amp; B</td>
    <td nowrap>(numA numB -- boolean)</td>
    <td nowrap>(3 0 -- 0)</td></tr>
<tr valign="top"><td>Or</td>
    <td>Logical Or: A || B</td>
    <td nowrap>(numA numB -- boolean)</td>
    <td nowrap>(3 0 -- 1)</td></tr>
<tr valign="top"><td>Not</td>
    <td>Logical Not: !A</td>
    <td nowrap>(num -- boolean)</td>
    <td nowrap>(3 -- 0)</td></tr>
</table>
    
<h1 class="datasheet">Bitwise</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>BitwiseAnd</td>
    <td>Bitwise And: A &amp; B</td>
    <td nowrap>(numA numB -- num)</td>
    <td nowrap>(5 4 -- 4)</td></tr>
<tr valign="top"><td>BitwiseOr</td>
    <td>Bitwise Or: A | B</td>
    <td nowrap>(numA numB -- num)</td>
    <td nowrap>(5 4 -- 5)</td></tr>
<tr valign="top"><td>BitwiseXOr</td>
    <td>Bitwise Exclusive-Or: A ^ B</td>
    <td nowrap>(numA numB -- num)</td>
    <td nowrap>(5 4 -- 1)</td></tr>
<tr valign="top"><td>LogicalShiftLeft</td>
    <td>Logical Shift Left: A << B</td>
    <td nowrap>(numA numB -- num)</td>
    <td nowrap>(4 1 -- 8)</td></tr>
<tr valign="top"><td>LogicalShiftRight</td>
    <td>Logical Shift Right: A >>> B</td>
    <td nowrap>(numA numB -- num)</td>
    <td nowrap>(8 1 -- 4)</td></tr>
<tr valign="top"><td>ArithmeticShiftRight</td>
    <td>Arithmetic Shift Right (sign extension): A >> B</td>
    <td nowrap>(numA numB -- num)</td>
    <td nowrap>(-1 1 -- -1)</td></tr>
</table>

<h1 class="datasheet">String</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>StringAdd</td>
    <td>Concatenate two strings</td>
    <td nowrap>(string string -- string)</td>
    <td nowrap>("ab" "cd" -- "abcd")</td></tr>
<tr valign="top"><td>StringLength</td>
    <td>Returns the length of a string</td>
    <td nowrap>(string -- num)</td>
    <td nowrap>("abc" -- 3)</td></tr>
<tr valign="top"><td>MBStringLength</td>
    <td>Returns the length of a string that contains characters from an extended set such as Unicode.</td>
    <td nowrap>(string -- num)</td>
    <td nowrap>("abc" -- 3)</td></tr>
<tr valign="top"><td>StringExtract</td>
    <td>Substring. Extract <I>count</I> characters from string starting at position <em>index</em>.</td>
    <td nowrap>(count index string -- string)</td>
    <td nowrap>(3 2 "abcde" -- "bcd")</td></tr>
<tr valign="top"><td>MBStringExtract</td>
    <td>Multi-byte Substring. Extract <I>count</I> characters from string starting at position <em>index</em>.</td>
    <td nowrap>(count index string -- string)</td>
    <td nowrap>(3 2 "abcde" -- "bcd")</td></tr>
</table>

<h1 class="datasheet">Type Conversion</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>ToInteger</td>
    <td>Converts the value to an integer</td>
    <td nowrap> ( num -- num)</td>
    <td nowrap> ( 3.2 -- 3 )</tr>
<tr valign="top"><td>ToNumber</td>
    <td>Converts the string value to a number.</td>
    <td nowrap> ( string -- num)</td>
    <td nowrap> ( "3.2" -- 3.2 )</tr>
<tr valign="top"><td>ToString</td>
    <td>Converts the value to a string.</td>
    <td nowrap> ( num -- string)</td>
    <td nowrap> ( 3.2 -- "3.2" )</tr>
<tr valign="top"><td>CharToAscii</td>
    <td>Convert the first character of a string to its ASCII value.</td>
    <td nowrap>(string -- num)</td>
    <td nowrap>("abc" -- 97)</td></tr>
<tr valign="top"><td>MBCharToAscii</td>
    <td>Convert the first character of string to its Unicode value.</td>
    <td nowrap>(string -- num)</td>
    <td nowrap>("abc" -- 61)</td></tr>
<tr valign="top"><td>AsciiToChar</td>
    <td>Convert the ASCII value to the equivalent character.</td>
    <td nowrap>(num -- string)</td>
    <td nowrap>(97 -- "a")</td></tr>
<tr valign="top"><td>MBAsciiToChar</td>
    <td>Convert a Unicode value to the equivalent character.</td>
    <td nowrap>(num -- string)</td>
    <td nowrap>(61 -- "a")</td></tr>
</table>

<h1 class="datasheet">Variables</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>GetVariable</td>
    <td>Push the value for the specified variable on the stack</td>
    <td nowrap>(variableName -- value)</td>
    <td nowrap>("FlashVersion" -- 4)</td></tr>
<tr valign="top"><td>SetVariable</td>
    <td>Set the value of the specified variable</td>
    <td nowrap>(variableName value --)</td>
    <td nowrap>("Var1" 123 --)</td></tr>
<tr valign="top"><td>GetType</td>
    <td>Returns the type of the object or value at the top of the stack.</td>
    <td nowrap>(value -- value type)</td>
    <td nowrap>(--)</td></tr>
<tr valign="top"><td>NewVariable</td>
    <td>Create a new user-defined variable.</td>
    <td nowrap>(name --)</td>
    <td nowrap>("x" --)</td></tr>
<tr valign="top"><td>InitVariable</td>
    <td>Create and initialise a user-defined variable.</td>
    <td nowrap>(value name --)</td>
    <td nowrap>(1 "x" --)</td></tr>
<tr valign="top"><td>NewArray</td>
    <td>Create an array.</td>
    <td nowrap>(value+ count -- array)</td>
    <td nowrap>(1 2 3 4 4 -- array)</td></tr>
<tr valign="top"><td>DeleteVariable</td>
    <td>Deletes a variable, returning true if the variable was deleted, false otherwise.</td>
    <td nowrap>(name -- boolean)</td>
    <td nowrap>("x" -- 1)</td></tr>
<tr valign="top"><td>Delete</td>
    <td>Deletes an object or variable, returning true if the object was deleted, false otherwise.</td>
    <td nowrap>(name -- boolean)</td>
    <td nowrap>("x" -- 1)</td></tr>
</table>

<h1 class="datasheet">Functions</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>ExecuteFunction</td>
    <td>Execute the built-in function.</td>
    <td nowrap>(arg* functionName -- result*)</td>
    <td nowrap>(12.3 "isFinite" -- "1")</td></tr>
<tr valign="top"><td>Return</td>
    <td>Return control from the function.</td>
    <td nowrap>(--)</td>
    <td nowrap>(--)</td></tr>
</table>

<h1 class="datasheet">Objects</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>GetAttribute</td>
    <td>Push the value of an objects attribute on the stack</td>
    <td nowrap>(string string -- value)</td>
    <td nowrap>("Key" "SPACE" -- 32)</td></tr>
<tr valign="top"><td>SetAttribute</td>
    <td>Set the value of a attribute of an object</td>
    <td nowrap>(variable string value --)</td>
    <td nowrap>(&lt;_root&gt; "variable" 1 --)</td></tr>
<tr valign="top"><td>ExecuteMethod</td>
    <td>Execute a method of an object</td>
    <td nowrap>(string string -- value)</td>
    <td nowrap>("Key" "getCode" -- num)</td></tr>
<tr valign="top"><td>NewMethod</td>
    <td>Define a new method for an object</td>
    <td nowrap>&nbsp;</td>
    <td nowrap>&nbsp;</td></tr>
<tr valign="top"><td>NamedObject</td>
    <td>Construct an instance of a built-in object.</td>
    <td nowrap>(arg* count className -- instance)</td>
    <td nowrap>("My String" 1 "String" -- instance)</td></tr>
<tr valign="top"><td>NewObject</td>
    <td>Define a new class.</td>
    <td nowrap>((name value)* count -- instance)</td>
    <td nowrap>("Account" "123456" 1 -- value)</td></tr>
<tr valign="top"><td>Enumerate</td>
    <td>Enumerate through the attributes of the object referenced by the name of the variable on the stack.</td>
    <td nowrap>( "var" -- )</td>
    <td nowrap>( -- )</td></tr>
<tr valign="top"><td>EnumerateObject</td>
    <td>Enumerate through the attributes of the object on the stack.</td>
    <td nowrap>( "var" -- )</td>
    <td nowrap>( -- )</td></tr>
</table>

<h1 class="datasheet">Movie Control</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>GetTarget</td>
    <td>Returns a string representing the path to the movie clip in which the current action is executed.</td>
    <td nowrap>(-- clipName )</td>
    <td nowrap>( -- "_root/MovieClip")</td></tr>
<tr valign="top"><td>SetTarget2</td>
    <td>Change the context of the Flash Player so subsequent actions are applied to the movie clip, <i>clipName</i>.</td>
    <td nowrap>(clipName -- )</td>
    <td nowrap>("MovieClip" --)</td></tr>
<tr valign="top"><td>GetProperty</td>
    <td>Push the value of the specified property on the stack. Properties are identified by reserved values, see the FSPush class for more details.</td>
    <td nowrap>(value -- value)</td>
    <td nowrap>( &lt;_totalframes&gt; -- 36 )</td></tr>
<tr valign="top"><td>SetProperty</td>
    <td>Set the value of a property</td>
    <td nowrap>(value propertyName --)</td>
    <td nowrap>( 8000 &lt;_width&gt; -- )</td></tr>
<tr valign="top"><td>CloneSprite</td>
    <td>Duplicate a movie clip <i>clipName</i>, on the display list layer <i>depth</i> with the name <i>newName</i>.</td>
    <td nowrap>( depth clipName newName --)</td>
    <td nowrap>( 19 "_root/MovieClip" "newClip" -- )</td></tr>
<tr valign="top"><td>RemoveSprite</td>
    <td>Delete a movie clip</td>
    <td nowrap>( clipName --)</td>
    <td nowrap>( "_root/MovieClip" -- )</td></tr>
<tr valign="top"><td>StartDrag</td>
    <td>Starts dragging a movie clip with an optional constraining rectangle defined by the corner points (x1,y1), (x2,y2).</td>
    <td nowrap>( x1 y1 x2 y2 1 clipName --)<br><br>( 0 clipName --)</td>
    <td nowrap>( 0 0 400 400 1 "movieClip" - )<br><br>( 0 "movieClip" - )</td></tr>
<tr valign="top"><td>EndDrag</td>
    <td>Stops dragging a movie clip</td>
    <td nowrap>(--)</td>
    <td nowrap>&nbsp;</td></tr>
<tr valign="top"><td>NextFrame</td>
    <td>Go to the next frame of the current movie</td>
    <td nowrap>(--)</td>
    <td nowrap>&nbsp;</td></tr>
<tr valign="top"><td>PreviousFrame</td>
    <td>Go to the previous frame of the current movie</td>
    <td nowrap>(-- )</td&nbsp;>
    <td nowrap>&nbsp;</td></tr>
<tr valign="top"><td>Play</td>
    <td>Start playing the current movie at the current frame</td>
    <td nowrap>(--)</td>
    <td nowrap>&nbsp;</td></tr>
<tr valign="top"><td>Stop</td>
    <td>Stop playing the current movie</td>
    <td nowrap>(--)</td>
    <td nowrap>&nbsp;</td></tr>
<tr valign="top"><td>ToggleQuality</td>
    <td>Toggle the movie between high and low quality</td>
    <td nowrap>(--)</td>
    <td nowrap>&nbsp;</td></tr>
<tr valign="top"><td>StopSounds</td>
    <td>Stop playing all sounds</td>
    <td nowrap>(--)</td>
    <td nowrap>&nbsp;</td></tr>
</table>    
    
<h1 class="datasheet">ActionScript 2.0</h1>

<p>Starting with Flash 6 Macromedia extended the syntax of ActionScript to make 
it more object-oriented, moving the language closer to Java than JavaScript. 
Several actions were added to support the new keywords introduced into ActionScript 
2.0.</p>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>InstanceOf</td>
    <td>Return true or false to the stack if the object can be created using the constructor function.</td>
    <td nowrap>( object function -- true | false)</td>
    <td nowrap>&nbsp;</td></tr>
<tr valign="top"><td>Implements</td>
    <td>Identifies a class implements a defined interface.</td>
    <td nowrap>( (function) count function --)</td>
    <td nowrap>&nbsp;</td></tr>
<tr valign="top"><td>Extends</td>
    <td>Identifies that a class inherits from a class - used to increase the execution speed of ActionScript code.</td>
    <td nowrap>( subclass superclass --)</td>
    <td nowrap>&nbsp;</td></tr>
<tr valign="top"><td>Cast</td>
    <td>Casts the type of an object on the stack, returning the object if it is the same type as the constructor function, null otherwise.</td>
    <td nowrap>(function object -- object | null)</td>
    <td nowrap>&nbsp;</td></tr>
<tr valign="top"><td>Throw</td>
    <td>Throw an exception.</td>
    <td nowrap>(--)</td>
    <td nowrap>&nbsp;</td></tr>
</table>
    
<h1 class="datasheet">Miscellaneous</h1>

<table class="actions">

<tr><th>Action</th><th>Description</th><th>Stack Notation</th><th>Example</th></tr>

<tr valign="top"><td>Trace</td>
    <td>Append value to debugging window</td>
    <td nowrap>(value --)</td>
    <td nowrap>("X = 3" --)</td></tr>
<tr valign="top"><td>GetTime</td>
    <td>Push the number of milliseconds that have elapsed since the player started on the stack.</td>
    <td nowrap>(-- num)</td>
    <td nowrap>(-- 1274832)</td></tr>
<tr valign="top"><td>RandomNumber</td>
    <td>Push a random number on the stack.</td>
    <td nowrap>(maximumValue -- num)</td>
    <td nowrap>(10 -- 3)</td></tr>
</table>

<p><b>Notes</b></p>

<ul>
<li>The Add action was updated in Flash 5 so it can be used to perform arithmetic add and string concatenation depending on whether the values on the stack can be interpreted as numeric values or strings. The original add action (Code = 10) should not be used.</li>

<li>For the division operation, if a divide by zero error occurs then the string "#ERROR" is pushed onto the stack.</li>

<li>The Equals and Less actions were updated in Flash 5 so it can be used to perform arithmetic and string comparison depending on whether the values on the stack can be interpreted as numeric values or strings. The original Less action (code = 15) and Equals action (code = 14) should not be used.</li>

<li>Type conversion of string characters is now handled by the String object, introduced in Flash 5. The ToInteger action is now supported by the Math object also introduced in Flash 5. The type conversion functions are only included for completeness.</li>

<li>Flash version 5 supports built-in and user defined objects. For a full description of the objects supported please consult an ActionScript 5 reference guide.</li>
</ul>

<h1 class="datasheet">Examples</h1>

<p>The FSActionObject class defines a series of constants that lists the type of actions supported in the current release. Actions may be created by specifying the action type in the constructor:</p>

<pre>
FSAction anAction = new FSAction(FSAction.Add);
</pre>

<p>The FSPush class is used to push values onto the Flash Player's stack before an action is executed. For example to execute the expression (1+2)*3 when a frame is displayed the following sequence of actions are created:</p>

<pre>
FSDoAction frameAction = new FSDoAction();

frameAction.add(new FSPush(1));
frameAction.add(new FSPush(2));
frameAction.add(new FSAction(FSAction.Add));
frameAction.add(new FSPush(3));
frameAction.add(new FSAction(FSAction.Multiply));
</pre>

<p>The Flash Player also supported classes and object that represent different complex data types and system resources such as the mouse. These objects and the functions they support are referenced by name. String containing the names and the values (and number) of the arguments required are pushed onto the stack:</p>

<pre>
// Push the arguments followed by the number of arguments onto the stack

frameAction.add(new FSPush(aValue));
frameAction.add(new FSPush(aValue));
frameAction.add(new FSPush(2));

// Place the name on the stack then execute the function.

frameAction.add(new FSPush("FunctionName"));
frameAction.add(new FSAction(FSAction.ExecuteFunction));
</pre>

<p>To execute a method on a given object a reference to the object is retrieved and the name of the method and any arguments are specified. For example to play a movie clip starting at a named frame:</p>

<pre>
// Push the arguments followed by the number of arguments onto the stack

frameAction.add(new FSPush("frameName"));
frameAction.add(new FSPush(1));

// Get a reference to the object.

frameAction.add(new FSPush("_root"));
frameAction.add(new FSPush("movieClip"));
frameAction.add(new FSAction(FSAction.GetAttribute));

// Place the name of the method on the stack then execute it.

frameAction.add(new FSPush("gotoAndPlay"));
frameAction.add(new FSAction(FSAction.ExecuteMethod));
</pre>

<p>Note: The FSPush class allows more than one value to be pushed onto the stack at a time. In the above examples separate FSPush objects are created to make the code a little more readable.</p> */  
    class DLL_DECL FSAction : public FSActionObject
    {
public:
        /** Definition of the different type of stack based action supported by the Flash Player.
        */
        enum stackActions { 
            NextFrame = 4,
            PrevFrame = 5, 
            Play = 6, 
            Stop = 7, 
            ToggleQuality = 8, 
            StopSounds = 9, 
            IntegerAdd = 10, 
            Subtract = 11, 
            Multiply = 12, 
            Divide = 13, 
            IntegerEquals = 14, 
            IntegerLess = 15, 
            And = 16, 
            Or = 17, 
            Not = 18, 
            StringEquals = 19, 
            StringLength = 20, 
            StringExtract = 21, 
            Pop= 23, 
            ToInteger = 24, 
            GetVariable= 28, 
            SetVariable = 29, 
            SetTarget2 = 32, 
            StringAdd = 33, 
            GetProperty = 34, 
            SetProperty = 35, 
            CloneSprite = 36, 
            RemoveSprite = 37, 
            Trace = 38, 
            StartDrag = 39, 
            EndDrag = 40, 
            StringLess = 41, 
// Flash 7
            Throw = 42, 
            Cast = 43, 
            Implements = 44, 
// End Flash 7
            RandomNumber = 48, 
            MBStringLength = 49, 
            CharToAscii = 50, 
            AsciiToChar = 51, 
            GetTime = 52, 
            MBStringExtract = 53, 
            MBCharToAscii = 54, 
            MBAsciiToChar = 55, 
            DeleteVariable = 58, 
            Delete = 59, 
            InitVariable = 60, 
            ExecuteFunction = 61, 
            Return = 62, 
            Modulo = 63, 
            NamedObject = 64, 
            NewVariable = 65, 
            NewArray = 66, 
            NewObject = 67, 
            GetType = 68, 
            GetTarget = 69, 
            Enumerate = 70, 
            Add = 71, 
            Less = 72, 
            Equals = 73, 
            ToNumber = 74, 
            ToString = 75, 
            Duplicate = 76, 
            Swap = 77, 
            GetAttribute = 78, 
            SetAttribute = 79, 
            Increment = 80, 
            Decrement = 81, 
            ExecuteMethod = 82, 
            NewMethod = 83,
// Flash 6
            InstanceOf = 84, 
            EnumerateObject = 85, 
// End Flash 6
            BitwiseAnd = 96, 
            BitwiseOr = 97, 
            BitwiseXOr = 98, 
            LogicalShiftLeft = 99, 
            ArithmeticShiftRight = 100, 
            LogicalShiftRight = 101,
// Flash 6
            StrictEquals = 102, 
            Greater = 103,
            StringGreater = 104,
// End Flash 6
// Flash 7
            Extends = 105
// End Flash 7
        };

        FSAction(FSInputStream* aStream);

        /** Constructs an action with the specified type. 

        @param aType the code used to denote the type of action performed.
        */
        FSAction(int aType) : FSActionObject(aType) {}

        FSAction* clone() const { return new FSAction(*this); }
        
        const char* className() const;

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
    };
}

#endif
