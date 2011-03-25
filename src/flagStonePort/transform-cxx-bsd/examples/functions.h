/*
 *  Functions.h
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

void getOptions(int argc, const char * args[], map< string, string>& options);
bool definedOption(map<string, string>& options, string optionName);
int intOption(map<string, string>& options, string optionName);
string stringOption(map<string, string>& options, string optionName);
void saveMovie(FSMovie& movie, string path, string filename);