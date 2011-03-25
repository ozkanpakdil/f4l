/*
 *  ASParser.h
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

#ifndef __ASParser_h__
#define __ASParser_h__ 1

#include "translate.h"

namespace translate 
{
class ASNode;
/**
 * ASParser translates ActionScript into a tree of ASNode objects which are then
 * encoded to the byte-codes and actions that will be executed by the Flash Player.
 *
\verbatim
    String script = "gotoFrame(1)";
    ASParser* parser = Parser();
    ASNode* root = parser->parse(script);
    int SWFVersion = 5;

    if (root)
    {
        size_t size = root->compile(SWFVersion);
        unsigned char* buf = new unsigned char[size];
        root->getCode(buf);
    }
\verbatim
 *
 * The version of Flash (swf) that the script is being encoded for must be passed
 * to the root ASNode when the tree of nodes is encoded. The format of the data 
 * structures that represent clip and button events changed when versions 6 and 
 * version 7 of the Flash File Format Specification was released.
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
 * The directories are searched in the order they were added to the array of paths
 * maintained by the parser.
 *
 * <b>Error Handling</b>\n
 * If an error occurs while parsing the script the parser returns 0. The functions
 * getFilename(), getLine(), getLineNumber() and getError() are used to return
 * information on the error:
 *
\verbatim
    string script = "gotoFrame(1)";
    ASParser* parser = Parser();
    ASNode* root = parser->parse(script.c_str());

    if (root == 0)
    {
       string filename = parser->getFilename();
       string line = parser->getLine();
       string message = parser->getMessage();
       int error = parser->getError();
       int lineNumber = parser->getLineNumber();
       int colNumber = parser->getColumnNumber();

       switch (error)
       {
           case ASParser::FILE_NOT_FOUND: ...
           case ASParser::READ_ERROR: ...
       }
    }
\endverbatim
 *
 */
class ASParser
{
public:
    enum ParseErrors {
        /**
         * The parser did not detect any errors.
         */
        OK,
        /**
         * A FileNotFound error is reported when the file referenced in  a #include 
         * directive cannot be opened.
         */
        FILE_NOT_FOUND,
        /**
         * A ReadError is reported when an error occurs while reading the file referenced
         * in a #include directive.
         */
        READ_ERROR,
        /**
         * A QuoteFileName error is reported if the filename refernced in a #include 
         * directive is not enclosed in double quotes.
         */
        QUOTE_FILE_NAME,
            /**
         * A ParseError error is used to report any exception thrown by the parser
         * while parsing a script.
         */
        PARSE_ERROR,
        /**
         * An OnOnly error occurs when on statements are mixed with other statements 
         * in a script. 
         */
        ON_ONLY,
        /**
         * An OnClipEventOnly error occurs when onClipEvent statements are mixed with
         * other statements in a script. 
         */
        ON_CLIP_EVENT_ONLY,
        /**
         * An UnknownMovieClipEvent error occurs when an unknown movie clip event
         * name is found in an OnClipEvent() statement. 
         */
        UNKNOWN_MOVIE_CLIP_EVENT,
        /**
         * An UnknownButtonEvent error occurs when an unknown button event name is
         * in an On() statement. 
         */
        UNKNOWN_BUTTON_EVENT,
        /**
         * A IncorrectArgumentCount error occurs when the wrong number of arguments are 
         * supplied to one of the built-in functions in Flash.
         */
        INCORRECT_ARGUMENT_COUNT,
        /**
         * A CannotUseBreak error occurs when a break statement is used outside of a 
         * loop statement.
         */
        CANNOT_USE_BREAK,
        /**
         * A CannotUseContinue error occurs when a continue statement is used outside of a 
         * loop statement.
         */
        CANNOT_USE_CONTINUE,
        /**
         * A CannotUseReturn error occurs when a return statement is used outside of a 
         * function definition.
         */
        CANNOT_USE_RETURN
    };
    /**
     * Add a path to the array of pathnames. The path should contain the system-dependent
     * separator.
     *
     * @param path a string containing the path to a directory.
     */
    virtual void CALL addPath(const char* path) = 0;
    /**
     * Returns a description of the error that occurred while parsing a script.
     *
     * @return an error description.
     */
    virtual const char* CALL getMessage() = 0;
    /**
     * Returns the name of the file that contained the line of code that generated 
     * an error while parsing a script.
     *
     * @return the name of the file which contained the line of code or an empty 
     * string if the line was in the 'root' script.
     */
    virtual const char* CALL getFilename() = 0;
    /**
     * Returns the number of the line of code that generated an error 
     * parsing a script.
     *
     * @return the number of the line which that triggered the error.
     */
    virtual int CALL getLineNumber() = 0;
    /**
     * Returns the number of the column in the line of code that generated an error 
     * parsing a script.
     *
     * @return the column in the line which that triggered the error.
     */
    virtual int CALL getColumnNumber() = 0;
    /**
     * Returns the line of code that generated an error while parsing a script.
     *
     * @return the line which that triggered the error.
     */
    virtual const char* CALL getLine() = 0;
    /**
     * Returns the type of error that occured while of parsing a script.
     *
     * @return a code identifying the error.
     */
    virtual int CALL getError() = 0;
    /**
     * Parses the ActionScript string, script, returning a pointer to the root
     * of an ASNode* tree if the script was parsed successfully or 0 if an 
     * error occurred.
     *
     * @param script a String containing the ActionScript code to parse.
     * @return a pointer to the root an ASNode* tree or 0 if an error occurred.
     */
    virtual ASNode* CALL parse(const char* script) = 0;
    /**
     * Compiles the tree of ASNodes into the binary representation of the byte-codes 
     * and actions that will be executed by the Flash Player.
     *
     * The ASParser only supports the version of ActionScript that was introduced 
     * with Flash 5 - earlier versions are not supported and the method will not
     * compile the node tree and return a length of zero.
     *
     * The Flash File Format Specification can change with each new release and the 
     * version of Flash must match the version number of the movie which the
     * compiled actions are added to, otherwise errors are likely when the Flash 
     * Player attempts to display the movie.
     *
     * If an error occurred while compiling the tree of ASNode objects method will
     * return a size of 0. The getError() method can be used to return a code
     * describing the type of error that occurred.
     *
     * @param node a tree of ASNodes representing a series of ActionScript statements.
     * @param version the version of Flash that the nodes should be compiled for.
     * @return the number of bytes that the ActionScript was compiled into, or 0 if 
     * an error occurred while compiling the node tree.
     */
    virtual size_t CALL compile(ASNode* node, int version) = 0;
    /**
     * Returns a copy of the binary encoded byte-codes and actions that the tree of 
     * nodes was compiled into. The buffer should be large enough to contain the compiled
     * data. The compile() method returns the length in bytes of the compiled nodes.
     *
     * @param buf a buffer large enough to hold the compiled nodes.
     * @return the number of bytes copied to the buffer.
     */
    virtual size_t CALL getCode(unsigned char* buf) = 0;
};

/**
 * Factory method to create an instance of the parser.
 *
 * @return a pointer to an ASParser object.
 */
extern "C" ASParser* CALL Parser();
}

#endif
