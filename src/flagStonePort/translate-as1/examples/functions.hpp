/*
 *  Functions.hpp
 *  Transform Examples
 *
 *  Created by smackay on Tue Jul 14 2004.
 *  Copyright (c) 2004 Flagstone Software Ltd. All rights reserved.
 *
 *  This code is distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 *  EXPRESS OR IMPLIED, AND Flagstone HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING
 *  WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *  PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
 */

#ifndef __Functions_h__
#define __Functions_h__ 1

#include <string>
#include <map>

using namespace std;

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
bool definedOption(map< string, string>& options, string optionName)
{
    bool value = false;

    if (options.find(optionName) != options.end())
        value = true;

    return value;
}

/**
 * Returns an option value converted to an integer.
 */
int intOption(map< string, string>& options, string optionName)
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
string stringOption(map< string, string>& options, string optionName)
{
    string value;

    if (options.find(optionName) != options.end())
        value = options[optionName];

    if (value.at(0) == '"')
        value = value.substr(1);
    if (value.at(value.length()-1) == '"')
        value = value.substr(0, value.length()-1);

    if (value.length() > 0)
    {
	    if (value.at(0) == '"')
	        value = value.substr(1);
	    if (value.at(value.length()-1) == '"')
	        value = value.substr(0, value.length()-2);
    }
    return value;
}

#endif
