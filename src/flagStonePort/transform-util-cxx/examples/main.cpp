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
#include <transform-util/transformutil.h>

using namespace std;
using namespace transform;

#include "functions.h"

#include "BasicButtons.hpp"
#include "BasicShapes.hpp"
#include "BasicSounds.hpp"
#include "ShowFontFile.hpp"
#include "ShowImage.hpp"
#include "StreamingSounds.hpp"

/**
 * Usage:
 *
 *  examples --example *i [ *i ]* [ --<optionName> [ <optionValue> ]* ]*
 *
 * *i - the name of the class that implements a specific example.
 *
 * <optionName> - arguments can be passed to examples by specifying the name of an option prefixed by '--' followed
 * by zero or more values. The individual example list the options that are supported
 *
 */
int main (int argc, const char * argv[])
{
    map<string, string> options;

    getOptions(argc, argv, options);

    string example = stringOption(options, "example");
cout<<example<<endl;
    if (example == "BasicButtons")         { BasicButtons example(options); }
    else if (example == "BasicShapes")     { BasicShapes example(options); }
    else if (example == "BasicSounds")     { BasicSounds example(options); }
    else if (example == "ShowFontFile")    { cout<<"mainde"<<endl;ShowFontFile example(options); }
    else if (example == "ShowImage")       { ShowImage example(options); }
    else if (example == "StreamingSounds") { StreamingSounds example(options); }
ShowFontFile example1(options);
    //ShowFontFile example();
    return 0;
}
