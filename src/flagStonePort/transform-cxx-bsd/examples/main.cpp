/*
 *  main.cpp
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

using namespace std;
using namespace transform;

#include "functions.h"

#include "MovieBasics.hpp"
#include "DisplayList.hpp"
#include "DrawingShapes.hpp"
#include "LineStyles.hpp"
#include "FillStyles.hpp"
#include "Transforms.hpp"

/**
 * Usage:
 *
 *  examples --example *i [ *i ]* [ --<optionName> [ <optionValue> ]* ]*
 *
 * *i - the name of the class that implements a specific example.
 *
 * <optionName> - arguments can be passed to examples by specifying the name of an option prefixed by '--' followed
 * by zero or more values. Each example list the options that are supported
 *
 */
int main (int argc, const char * argv[])
{
    map<string, string> options;

    getOptions(argc, argv, options);

    string example = stringOption(options, "example");

    if (example == "MovieBasics")          { MovieBasics example(options); }
    else if (example == "DisplayList")     { DisplayList example(options); }
    else if (example == "DrawingShapes")   { DrawingShapes example(options); }
    else if (example == "LineStyles")      { LineStyles example(options); }
    else if (example == "FillStyles")      { FillStyles example(options); }
    else if (example == "Transforms")      { Transforms example(options); }
    
    return 0;
}


