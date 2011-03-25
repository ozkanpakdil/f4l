/*
 *  Functions.cpp
 *  Transform Examples
 *
 *  Created by smackay on Mon Feb 10 2003.
 *  Copyright (c) 2001-2004 Flagstone Software Ltd. All rights reserved.
 *
 *  This code is distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 *  EXPRESS OR IMPLIED, AND Flagstone HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING
 *  WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *  PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
 */

#include <string>
#include <vector>
#include <map>
#include <iostream>

#include <transform/transform.h>
#include <transform-util/transformutil.h>

using namespace std;
using namespace transform;

/** 
 * Parse the command line arguments. The name of an argument is prefixed  by '--'. 
 * Zero or more values may follow an argument name until the next argument name is 
 * detected. The values for    an argument are placed in an array and are stored in a 
 * map with the argument name used as the key. 
 *
 * @param argc the number of command-line arguments.
 * @param args a pointer to an array of strings containing the command-line arguments.
 * @param options a reference to a map used to store the arguments and associated values.
 */
void getOptions(int argc, const char * args[], map< string, string>& options)
{
    for (int i=1; i<argc; i++)
    {
        string anOption = args[i];

        if (anOption.substr(0, 2) == "--")
        {
            string optionName = anOption.substr(2);
            string optionValue;

            if (++i < argc)
            {
                optionValue = args[i];

                if (optionValue.substr(0, 2) == "--")
                    options[optionName] = "";
            }
            options[optionName] = optionValue;
        }
    }
}

/**
 * Returns true if an option was specified on the command line, false otherwise.
 */
bool definedOption(map<string, string>& options, string optionName)
{
    bool value = false;

    if (options.find(optionName) != options.end())
        value = true;

    return value;
}

/**
 * Returns an option value converted to an integer.
 */
int intOption(map<string, string>& options, string optionName)
{
    int value = 0;

    if (options.find(optionName) != options.end())
    {
        string str = options[optionName];
        sscanf(str.c_str(), "%d", &value);
    }
    return value;
}

/**
 * Returns an option value as a string.
 */
string stringOption(map<string, string>& options, string optionName)
{
    string value;

    if (options.find(optionName) != options.end())
        value = options[optionName];

    if (value.length() > 0)
    {
	    if (value.at(0) == '"')
	        value = value.substr(1);
	    if (value.at(value.length()-1) == '"')
	        value = value.substr(0, value.length()-2);
    }
    return value;
}

/**
 * saveMovie is used to encode the objects and write them to the specified Flash file.
 * This method is used a simple wrapper for the FSMovie object's encodeToFile() method
 * so any excptions thrown when encoding the file can be handled without making the 
 * code to generate the movie look any more complicated than necessary.
 *
 * @param the full path to the file.
 */
void saveMovie(FSMovie& movie, string path, string filename)
{
#ifdef WIN32
    char separator = '\\';
#else
    char separator = '/';
#endif

    string filepath(filename);
    
    if (path.length() > 0)
        filepath = path + separator + filepath;

    try 
    {
        movie.encodeToFile(filepath.c_str());
    }
    catch (FSException e)
    {
        /* 
         * Several exceptions could be thrown to get to this point. FSMovie will 
         * throw an FSFileOpenException, FSAccessException or FSFormatException 
         * if the file cannot be opened for writing, an error occurs while writing
         * to the file or if an error occurs while encoding the Flash data, respectively.
         * 
         * All the exceptions thrown contain a message which describes why the
         * exception was thrown so handling them all in the same way is sufficient
         * for the purposes of the examples.
         */
        cerr << e.what();
    }
}