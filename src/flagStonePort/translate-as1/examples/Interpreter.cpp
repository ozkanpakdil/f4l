/*
 *  Interpreter.cpp
 *  Translate AS1
 *
 *  Created by smackay on Tue Jul 14 2004.
 *  Copyright (c) 2004 Flagstone Software Ltd. All rights reserved.
 *
 *  This code is distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 *  EXPRESS OR IMPLIED, AND Flagstone HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING
 *  WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *  PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
 */

#include "functions.hpp"
#include <translate-as1/translate.h>

#include <sstream>
#include <fstream>
#include <iostream>

using namespace translate;

/*
 * Recursive function for displaying the tree of nodes generated
 * when a script is parsed.
 */
void show(ASNode* node, ostringstream& buffer, string prefix)
{
    unsigned int count = node->count();
    ASNode** children = node->getChildren();

	buffer.write(prefix.c_str(), (std::streamsize)prefix.length());
    buffer << node->toString();
    buffer << '\n';

    for (unsigned int i=0; i<count; i++)
        show(children[i], buffer, prefix + "  ");
}

/**
 * Interpreter is a simple command-line interpreter that allows the 
 * ActionScript grammar to be tested and sample swf files to be generated.
 *
 * Synopsis:
 *
 * interpreter --file filename [ --show filename ] [ --encode filename ]
 *     [ --log filename ]
 *
 * where
 *
 *   --file filename   is a text file containing ActionScript statements. 
 *
 *   --show filename   is the name of a file where a description of the 
 *                     node tree will be written. 
 *
 *   --encode filename is the name of a file where the compiled code will
 *                     be written.
 *
 *   --log filename    is the name of a file where any errors detected will
 *                     be written. Errors are also reported on cerr.
 */
int main (int argc, const char * argv[])
{
    map<string, string>options;

    getOptions(argc, argv, options);
    
    string scriptFile = stringOption(options, "file");
    bool showTree = definedOption(options, "show");
    bool encode = definedOption(options, "encode");
    bool log = definedOption(options, "log");

    /*
     * Wrapping the script filename in a #include directive
     * is the simplest way of passing the code to the parser.
     *
     * The path to the file should contain slashes since 
     * backslashes will be interpreted as escape markers.
     */
    string pathname;
    string script;

    for (unsigned int i=0; i<scriptFile.length(); i++)
    {
        if (scriptFile.at(i) == '\\') 
            pathname.append(1, '/');
        else
            pathname.append(1, scriptFile.at(i));
    }
    
    script = "#include \"" + pathname + "\"\n";

    ASParser* parser = Parser();
    ASNode* root = parser->parse(script.c_str());

    /*
     * If the script was parsed successfully then optionally display the
     * list of nodes generated and compile them to generate the binary
     * encoded data that can be added to a Flash (.swf) file.
     */
    if (root != 0)
    {
        if (showTree)
        {
            string treeFile = stringOption(options, "show");

            ostringstream buffer(ostringstream::out);
            fstream out(treeFile.c_str(), fstream::out);

            show(root, buffer, "");

            out << buffer.str().c_str();

            out.close();
        }

        if (encode)
        {
            ofstream out;
       
            string swfFile = stringOption(options, "encode");

           /*
             * Compile the tree of nodes. The nodes are compiled for
             * Flash Version 5. The version number is required as the
             * Flash binary format changed when Macromedia released 
             * versions 6 and 7 (MX and MX 2004 respectively).
             */
            size_t size = parser->compile(root, 5);

            unsigned char* encodedActions = new unsigned char[size];
            parser->getCode(encodedActions);

            /*
             * The files containing the compiled scripts are hard-wired
             * with the encoded versions of the DefineShape, DefineButton
             * and PlaceObject2 data structures required to display the 
             * file correctly written 'manually' to the specified output
             * file.
             */
            out.open(swfFile.c_str(), fstream::out | fstream::binary);

            unsigned char signature[] = { 0x46, 0x57, 0x53, 0x05 };

		    for (int i=0; i<4; i++)
			    out << signature[i];

            /*
             * The type of the root node identifies the type of script 
             * that was compiled. ActionScript contains the on() statement
             * to define button events and onClipEvent() to define movie
             * clip events. Scripts containing other types of statements
             * at the top-level define the actions executed when a given
             * frame is displayed.
             */
            if (root->getType() == ASNode::Array)
            {
		        int actionLength = (int)size + 1;
		        int fileLength = 35 + actionLength;

		        for (unsigned int i=0; i<4; i++, fileLength >>= 8)
			        out << (unsigned char)fileLength;
        	    
                /*
                 * Specify the size of the movie player screen, the number 
                 * of frames, the frame rate and the background colour.
                 */
		        unsigned char header[] = { 
			        0x68, 0x00, 0x1f, 0x40, 0x00, 0x07, 0xd0, 0x00,
			        0x00, 0x0c, 0x01, 0x00, 0x43, 0x02, 0xff, 0xff,
			        0xff, 0x3f, 0x03
		        };
        				
		        for (unsigned int i=0; i<19; i++)
			        out << header[i];
        					
		        for (unsigned int i=0; i<4; i++, actionLength >>= 8)
			        out << (unsigned char)actionLength;

                for (unsigned int i=0; i<size; i++)
			        out << (unsigned char)encodedActions[i];

                out << (unsigned char)0;
            }
            else if (root->getType() == ASNode::Button)
            {
		        int actionLength = (int)size + 13;
                int fileLength = 131 + actionLength;

		        for (unsigned int i=0; i<4; i++, fileLength >>= 8)
			        out << (unsigned char)fileLength;
        			
                /*
                 * Specify the size of the movie player screen, the number 
                 * of frames, the frame rate, the background colour, the 
                 * shape used to draw the button and the define button 
                 * object without the button events which define the 
                 * button's behaviour.
                 */
		        unsigned char header[] = { 
			        0x78, 0x00, 0x05, 0x5f, 0x00, 0x00, 0x0f, 0xa0, 
                    0x00, 0x00, 0x0c, 0x01, 0x00, 0x43, 0x02, 0xff, 
                    0xff, 0xff, 0xbf, 0x00, 0x4d, 0x00, 0x00, 0x00,
                    0x01, 0x00, 0x64, 0x63, 0xb4, 0xcd, 0x21, 0x2e, 
                    0x90, 0x01, 0x00, 0x00, 0xcc, 0x66, 0x01, 0x14, 
                    0x00, 0x00, 0x33, 0x66, 0x11, 0x35, 0x89, 0x18, 
                    0x83, 0x3d, 0x37, 0xf4, 0xd7, 0xd2, 0x70, 0x01, 
                    0x4d, 0x27, 0x00, 0x17, 0xf7, 0x28, 0xd3, 0x7f, 
                    0x72, 0x90, 0x00, 0xb3, 0xf4, 0x80, 0x0b, 0x3e, 
                    0x80, 0xf2, 0x8d, 0x28, 0x0f, 0x29, 0x2d, 0x90, 
                    0x01, 0x4a, 0xd9, 0x00, 0x08, 0x0c, 0xd7, 0x52,
                    0x80, 0xcd, 0x78, 0x00, 0x4c, 0x34, 0x80, 0x04, 
                    0xc3, 0x7f, 0x4d, 0x70, 0x00, 0xbf, 0x08
		        };

                for (unsigned int i=0; i<103; i++)
			        out << header[i];
        					
		        for (unsigned int i=0; i<4; i++, actionLength >>= 8)
			        out << (unsigned char)actionLength;

		        unsigned char body[] = { 
			        0x01, 0x00, 0x00, 0x08, 0x00, 0x01, 0x01, 0x00,
			        0x01, 0x00, 0x00, 0x00, 0x00
		        };
        		
		        for (unsigned int i=0; i<13; i++)
			        out << (unsigned char)body[i];

                for (unsigned int i=0; i<size; i++)
			        out << (unsigned char)encodedActions[i];
 
                /*
                 * Write out a PlaceObject2 to display the button.
                 */
            	unsigned char tail[] = {
                    0x8a, 0x06, 0x06, 0x01, 0x00, 0x02, 0x00, 0x1c, 
                    0xad, 0x31, 0xd7, 0x80
		        };
        		
		        for (unsigned int i=0; i<12; i++)
			        out << (unsigned char)tail[i];
            }
            else if (root->getType() == ASNode::MovieClip)
            {
		        int actionLength = (int)size + 9;
                int fileLength = 99 + actionLength;

		        for (unsigned int i=0; i<4; i++, fileLength >>= 8)
			        out << (unsigned char)fileLength;
        			
                /*
                 * Specify the size of the movie player screen, the number 
                 * of frames, the frame rate, the background colour, the 
                 * shape used to draw the button, a movie clip definition
                 * and the first part of a PlaceObject2 structure without
                 * the clip events which define the movie clips behaviour.
                 */
		        unsigned char header[] = { 
			        0x68, 0x00, 0x1f, 0x40, 0x00, 0x07, 0xd0, 0x00,
			        0x00, 0x0c, 0x01, 0x00, 0x43, 0x02, 0xff, 0xff,
			        0xff, 0xbf, 0x00, 0x24, 0x00, 0x00, 0x00, 0x01, 
                    0x00, 0x5d, 0x93, 0x4d, 0xba, 0xd0, 0xa6, 0x80, 
                    0x01, 0x00, 0xff, 0xff, 0xff, 0x01, 0x14, 0x00, 
                    0x00, 0x00, 0x00, 0x11, 0x35, 0x69, 0x8c, 0xa1, 
                    0xfd, 0x16, 0x75, 0xcb, 0x5e, 0xfa, 0x13, 0x1b, 
                    0x95, 0x42, 0x80, 0xff, 0x09, 0x10, 0x00, 0x00, 
                    0x00, 0x02, 0x00, 0x01, 0x00, 0x86, 0x06, 0x06, 
                    0x01, 0x00, 0x01, 0x00, 0x00, 0x40, 0x00, 0x00, 
                    0x00, 0xbf, 0x06
                };

		        for (unsigned int i=0; i<83; i++)
			        out << header[i];
        					
		        for (unsigned int i=0; i<4; i++, actionLength >>= 8)
			        out << (unsigned char)actionLength;

		        unsigned char body[] = { 
                    0x86, 0x01, 0x00, 0x02, 0x00, 0x18, 0xdf, 0x4a, 
                    0xcc 
                };

		        for (unsigned int i=0; i<9; i++)
			        out << (unsigned char)body[i];

                for (unsigned int i=0; i<size; i++)
			        out << (unsigned char)encodedActions[i];
            }
            /*
             * Write out a ShowFrame instruction followed by the end of 
             * file marker.
             */ 
            out << (unsigned char)64;
            out << (unsigned char)0;
            out << (unsigned char)0;
            out << (unsigned char)0;

            out.close();

            delete encodedActions;
        }
    }
    else
    {
        /*
         * An error occurred while parsing the script.
         */
        string errorName;

        switch (parser->getError())
        {
        case ASParser::READ_ERROR: errorName = "An error occurred while reading the script."; break;
        case ASParser::PARSE_ERROR: errorName = "An error occurred while compiling the script."; break;
        }
            
        cerr << errorName << endl;
        cerr << parser->getMessage() << endl;
        cerr << parser->getFilename() << ": Line " << parser->getLineNumber() << endl;
        cerr << parser->getLine() << endl;
        
        if (log)
        {
            string logFile = stringOption(options, "log");
            fstream errLog(logFile.c_str(), fstream::out);

            errLog << errorName << endl;
            errLog << parser->getMessage() << endl;
            errLog << "Line " << parser->getLineNumber() << ": ";
            errLog << parser->getLine() << endl;
            
            errLog.close();
        }
    }
    delete root;
    delete parser;

    return 0;
}
