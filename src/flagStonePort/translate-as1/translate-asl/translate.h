/*
 * translate.h
 * Transform Utilities
 *
 * Created by smackay on Mon Jun 28 2004.
 * Copyright (c) 2004 Flagstone Software Ltd. All rights reserved.
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

#ifndef __translate_h__
#define __translate_h__ 1

/**
 * \mainpage 
 * The ASParser framework is a collection of classes used to implement a compiler 
 * for Macromedia's ActionScript Version 1.0. ActionScript statements are parsed 
 * to generate the byte-codes and actions that will be executed by the Flash Player.
 * 
 * The process of compiling a script take two steps. The script is parsed and 
 * converted into a tree of ASNodes then it is encoded to generate the binary
 * data in the Flash (SWF) File Format which specifies the byte-codes and actions
 * executed by the Flash Player.
 * 
\verbatim
     string script = "a = b + c;"
     int swfVersion = 5;
 
     ASParser* parser = Parser();
     ASNode* root = parser->parse(script);
 
     size_t numberOfBytes = parser->compile(root, swfVersion);
     unsigned char* data = new unsigned char[numberOfBytes];

     parser->getCode(data);
\endverbatim
 *
 * When the tree of ASNodes is compiled the version of Flash that the ASNodes will 
 * be encoded to is passed along with the root node. The file format of the data 
 * structures used to represent movie clip events and button events changed when 
 * Macromedia released Versions 6 an 7 of the Flash File Format Specification 
 * respectively so the version number is required to compile the nodes correctly.
 * 
 * <b>Frames, Buttons or Movie Clips</b>\n
 * The parser can be used to compile scripts that are executed when, a frame is 
 * displayed, an event occurs in a button or an event occurs in a movie clip.
 * 
 * Scripts that will be executed when a frame is displayed can be encoded then 
 * added to an FSDoAction object.
 * 
\verbatim
     string script = "gotoFrame(1)";
 
     ASNode* root = parser->parse(script.c_str());
     size_t size = parser->compile(root, swfVersion);

     unsigned char* actions = new unsigned char[size];
     parser->getCode(actions);
     
     FSDoAction* frameActions = new FSDoAction(actions);
 
     movie.add(frameActions);
 \endverbatim
 * 
 * For actions executed when an event in a button occurs there are two options
 * for writing a script, either specify the actions for an individual button event 
 * or for all the events that a button responds to in a single script.
 * 
 * When specifying the actions that are executed in response to a set of one or 
 * more events the encoded actions are added to an FSButtonEvent object:
 * 
 \verbatim
     string script = "gotoFrame(1)";
     int event = FSButtonEvent::Release;
 
     ASNode* root = parser->parse(script.c_str());
     size_t size = parser->compile(root, swfVersion);

     unsigned char* actions = new unsigned char[size];
     parser->getCode(actions);

     FSButtonEvent* eventActions = new FSButtonEvent(event, actions);
     ...
     button->add(eventActions);
     ...
     movie->add(button);
 \endverbatim
 * 
 * For specifying multiple events ActionScript provides the on() block construct.
 * When used in a script the nodes are encoded as an array of button event objects
 * and are added to an FSDefineButton2 object:
 * 
 \verbatim
     // This script advances the movie by 10 frames each time a 
     // button is clicked.
 
     string script = "
         on (press)
         {
             frameNumber = currentFrame + 10;
         }
   
         on (release)
         {
             currentFrame = frameNumber
             gotoFrame(frameNumber);
         }
     ";
 
     ASNode* root = parser->parse(script.c_str());
     size_t size = parser->compile(actions, swfVersion);

     unsigned char* actions = new unsigned char[size];
     parser->getCode(actions);
     ...
     button->add(actions);
     ...
     movie->add(button);
 \endverbatim
 * 
 * NOTE: Although a script can contain more than one on() block, other statements 
 * cannot be mixed with on() statements. The parser will generate an error.
 * 
 * For movie clip events the siutation is similar to generating actions for 
 * buttons. ActionScript contains the onClipEvent() block to allow actions to be
 * specified for all the events a movie clip responds to in a single script.
 * 
 * Specify the actions for a single event:
 * 
 \verbatim
     string script = "startDrag();";
     int event = FSClipEvent::MouseDown;
 
     ASNode* root = parser->parse(script.c_str());
     size_t size = parser->compile(root, swfVersion);

     unsigned char* actions = new unsigned char[size];
     parser->getCode(actions);
     FSClipEvent* eventActions = new FSClipEvent(event, actions);
     ...
     placeObject->add(eventActions);
 \endverbatim
 * 
 * Specify the actions for more than one event.
 * 
 \verbatim
     // Drag the mouse clip around the screen with the mouse
 
     String script = "
         on (mouseDown)
         {
             startDrag();
         }
   
         on (mouseUp)
         {
             stopDrag();
         }
     ";
 
     ASNode* root = parser->parse(script.c_str());
     size_t size = parser->compile(root, swfVersion);

     unsigned char* events = new unsigned char[size];
     parser->getCode(events);
     ...
     placeObject->add(encodedEvents);
 * \endverbatim 
 * 
 * NOTE: As with button events a script can contain more than one onClipEvent() 
 * block, other statements cannot be mixed with onClipEvent() statements. The 
 * parser will generate an error.
 * 
 * <b>Using ASNodes</b>\n
 * Generating ASNodes as an intermediate step has two advantages: sections of 
 * frequently used code can be parsed once and then encoded in the different 
 * objects added to a movie greatly improving performance. For simple scripts 
 * trees of ASNodes can be constructed 'manually' - again eliminating the overhead
 * of the parser.
 * 
 \verbatim
     ASNode* a = ValueASNode(ASNode::Identifier, "a");
     ASNode* b = ValueASNode(ASNode::Identifier, "b");
     ASNode* c = ValueASNode(ASNode::Identifier, "c");
 
     ASNode* add = BinaryASNode(ASNode::Add, a, b);
     ASNode* assign = BinaryASNode(a, add);
 \endverbatim
 * 
 * The ASNode class defines a full range of node types ranging from specifying 
 * literals through to complex structures such as iterative and conditional 
 * constructs such as for loops and if/else blocks.
 * 
 * The framework contains an example Interpreter class which can be used to 
 * parse scripts and display a list of ASNode objects that a script is translated
 * into.
 *
 * <b>Search Paths</b>\n
 * ActionScript supports #include directives which allow scripts to be nested.
 * When the script is preprocessed the current working directory is checked for 
 * for the file specified. The parser also supports search paths which is a list
 * of directories which should also be checked for the file.
 *
 * The addPath() method can be used to add to the list of directories to search.
 * The current working directory (".") is placed by default.
 *
 * <b>Error Handling</b>\n
 * The parser will return NULL if it detects an error in the syntax of the script 
 * it is parsing. The parser which has four methods for identifying the line 
 * in the script that triggered the error:
 * 
 * getFilename() returns the name of the file that contained the script that 
 * caused the error. Scripts are passed as strings to the parser however #include
 * directives can be used to load files containing ActionScript and can be nested
 * to any depth. If an error occurs in the script passed directly to the parser 
 * then this method will return the string "Main", otherwise the name of the 
 * file that contains the line that caused the error is returned.
 * 
 * getError() returns a string error code that identifies the type of error
 * that occured, e.g. "FileNotFound". The string can be used as a key to generate 
 * a localized error message. The ASParser class contains a list of error keys.
 * 
 * getLineNumber() returns the line number (starting at 1) in the script where 
 * the error was found.
 * 
 * getColumnNumber() returns the column number (starting at 1) in the line of code
 * where the error was found.
 * 
 * getLine() returns the line of code that caused the error.
 *
 * getMessage() returns the error message generated by the parser when an error 
 * occurred.
 *
 \verbatim
    ASNode* root = NULL;
    
    if ((root = parser->parse(script)) == NULL)
    {
        string filename = parser->getFilename();
        string line = parser->getLine();
        string message = parser->getMessage();
        string error = parser->getError();
        int lineNumber = parser->getLineNumber();
        int colNumber = parser->getColumnNumber();

        switch (error)
        {
            case ASParser::FILE_NOT_FOUND: ...
            case ASParser::READ_ERROR: ...
            ...
        }
    }
\endverbatim 
 */

#include "ASTranslate.h"
#include "ASParser.h"
#include "ASNode.h"

#endif /* __translate_h__ */
