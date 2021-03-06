/*
 *  BasicSounds.cpp
 *  Transform Examples
 *
 *  Created by smackay on Tue Jun 02 2004.
 *  Copyright (c) 2001-2004 Flagstone Software Ltd. All rights reserved.
 *
 *  This code is distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 *  EXPRESS OR IMPLIED, AND Flagstone HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING
 *  WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *  PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
 */

#ifndef __BasicSounds_h__
#define __BasicSounds_h__ 1

/*
 * This example shows how the FSSoundConstructor class can be used to generate
 * the objects used to play a sound in a movie.
 *
 * To run this example, type the following on a command line:
 *
 *     examples --example BasicSounds --file sound-file [--resultDir path]
 *
 * where
 *
 *     sound-file is the path to a file containing a WAVE or MP3 format sound.
 *
 *     resultDir is the directory where the Flash file generated by the example 
 *     is written to.
 *
 * The code generates a Flash file with the same name as the sound file, only 
 * with an 'swf' extension appended.
 *
 */
class BasicSounds
{
public:
	BasicSounds(map< string, string>& options)
	{
		string soundFile = stringOption(options, "file");

		FSSoundConstructor* soundGenerator = SoundConstructor();
		FSMovie movie;

		int status = TransformUtil::OK;

		if ((status = soundGenerator->setSoundFromFile(soundFile.c_str())) != TransformUtil::OK)
		{
			switch (status)
			{
				case TransformUtil::FileNotFound:
					cout << "Could not find sound file" << endl; break;
				case TransformUtil::ReadError:
					cout << "Could not read sound file" << endl; break;
				case TransformUtil::FormatError:
					cout << "Could not read sound file" << endl; break;
			}
		}

		if (status == TransformUtil::OK) 
		{
			float framesPerSecond = 12.0f;
			int soundId = movie.newIdentifier();

			/*
			* Calculate the time it takes to play the sound and the number of frames 
			* this represents.
			*/
			float duration = ((float) soundGenerator->getSamplesPerChannel()) / 
				((float) soundGenerator->getSampleRate());
	            
			int numberOfFrames = (int) (duration * framesPerSecond);
	        
			/* 
			* Add all the objects together to create the movie.
			*/
			movie.setFrameSize(FSBounds(0, 0, 8000, 4000));
			movie.setFrameRate(framesPerSecond);
			movie.add(new FSSetBackgroundColor(FSColorTable::lightblue()));

			/* 
			* An FSSoundStreamHeader2 object defines the attributes of the streaming sound.
			*/
			movie.add(soundGenerator->defineSound(soundId));

			/*
			* Signal the Flash Player to begin playing the sound.
			*/
			movie.add(new FSStartSound(FSSound(soundId, FSSound::Start)));

			/* 
			* Add enough frames to give the sound time to play.
			*/
			for (int i=0; i<numberOfFrames; i++)
				movie.add(new FSShowFrame());
	        
		    saveMovie(movie, stringOption(options, "resultDir"), "BasicSounds.swf");
		}
		delete soundGenerator;
	}
};

#endif