/*
 *  BasicShapes.cpp
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

#ifndef __BasicShapes_h__
#define __BasicShapes_h__ 1

/*
 * This example shows how the drawing commands available in the FSShapeConstructor
 * can be used to draw simple geometric shapes and arbitrary paths. The example 
 * draws a series of simple geometric shapes and discusses how the line and fill
 * styles are specified to render the paths drawn.
 *
 * To run this example, type the following on a command line:
 *
 *     examples --example BasicShapes [--resultDir path]
 *
 * where
 *
 *       resultDir is the directory where the Flash file generated by the example 
 *     is written to.
 *
 */
class BasicShapes
{
public:
	BasicShapes(map< string, string>& options)
	{
		FSShapeConstructor* path = ShapeConstructor();
        FSMovie movie;
	    
		/* 
		* The FSShapeConstructor allows coordinates to be specified either 
		* in twips or pixels. Pixels makes life a little easier.
		*/
		path->COORDINATES_ARE_PIXELS = true;
	    
		int width = 150;
		int height = 100;
		int cornerRadius = 10;
	    
		int identifier = 0;
	    
		/* 
		* The line and fill styles used to render the shapes should be 
		* specified before drawing starts. The line style is the most 
		* important since the thickness of the line determines the size of 
		* the bounding rectangle which must completely enclose the shape for 
		* it to be drawn correctly - particularly if overlapped by other 
		* shapes on different layers in the display list or when used to draw
		* buttons.
		* 
		* Here the same line and fill styles are being used to draw each of the 
		* shapes. More typically the line and fill styles would be set for 
		* each of the shapes drawn. The class provides getLineStyles() and 
		* getFillStyles() methods to access the line and fill style arrays 
		* allowing tight control over reusing or replacing styles as each
		* shape is drawn.
		*/
		FSColor lineColor = FSColorTable::black();
		FSColor fillColor = FSColorTable::red();

		FSSolidLine* lineStyle = new FSSolidLine(20, lineColor);
		FSSolidFill* fillStyle = new FSSolidFill(fillColor);

		path->addLineStyle(lineStyle);
		path->addFillStyle(fillStyle);

		delete lineStyle;
		delete fillStyle;
	    
		movie.setFrameRate(1.0f);
		movie.setFrameSize(FSBounds(-4000, -4000, 4000, 4000));
		movie.add(new FSSetBackgroundColor(FSColorTable::lightblue()));
	    
		/* Draw a rectangle with the origin at the centre of the shape.
		* 
		* First select the line and fill styles by specifying the order of the
		* styles added to the FSShapeConstructor earlier - the styles are stored
		* in two arrays one for the line styles and one for the fill styles.
		* 
		* All the methods used to draw geometric shapes allow the origin of the
		* shape to be specified. The coordinate system of the shape is separate
		* from the coordinate system of the movie. Specifying the origin controls 
		* how the shape is drawn relative to the point on the screen where it 
		* is placed.
		* 
		* The identifier variable is reused for each shape definition since they
		* are not referred to other than to place them on the display list using
		* the FSPlaceObject2 class.
		* 
		* All the methods provided to draw geometric shapes are implemented
		* using the methods that perform the basic drawing commands supported
		* by the FSShapeConstructor class. For example the rect() method used 
		* here is implemented as:
		* 
		* void rect(int x, int y, int width, int height)
		* {
		*     newPath();
		*     setStyle(0, 0);
		*     move(x-width/2, y-height/2);
		*     rline(width, 0);
		*     rline(0, height);
		*     rline(-width, 0);
		*     rline(0, -height);
		*     closePath();
		* }
		*/
		identifier = movie.newIdentifier();
	    
		path->selectStyle(0, 0, -1);
		path->rect(width/2, -height/2, width, height);

		/* Add the shape definition to the movie, place on the display list
		* and render the frame.
		*/
		movie.add(path->defineShape(identifier));
		movie.add(new FSPlaceObject2(identifier, 1, 0, 0));
		movie.add(new FSShowFrame());
	    
		/*
		* Draw a rectangle with rounded corners.
		* 
		* Here the first drawing command is a call to newPath() which clears
		* any path currently being drawn. It should be the first command before
		* and drawing or style selections are made.
		*/
		identifier = movie.newIdentifier();

		path->newPath();
		path->selectStyle(0, 0, -1);
		path->rect(width/2, height/2, width, height, cornerRadius);
		movie.add(path->defineShape(identifier));
		movie.add(new FSPlaceObject2(identifier, 1));
		movie.add(new FSShowFrame());

		/*
		* Draw a circle
		*/
		identifier = movie.newIdentifier();

		path->newPath();
		path->selectStyle(0, 0, -1);
		path->circle(-width/2, height/2, height/2);
		movie.add(path->defineShape(identifier));
		movie.add(new FSPlaceObject2(identifier, 1));
		movie.add(new FSShowFrame());
	    
		/*
		* Draw an ellipse
		*/
		identifier = movie.newIdentifier();

		path->newPath();
		path->selectStyle(0, 0, -1);
		path->ellipse(-width/2, -height/2, width/2, height/2);
		movie.add(path->defineShape(identifier));
		movie.add(new FSPlaceObject2(identifier, 1));
		movie.add(new FSShowFrame());
	    
		/*
		* Draw a polyline.
		* 
		* The first point of a polyline is a move relative to the current 
		* drawing point - which for a new path is (0,0). While the geometric
		* shapes drawn previous were all closed the polygon method can be 
		* used to draw part of a shape so the newPath() and styles must be 
		* explicitly specified to draw the shape.
		*/
		identifier = movie.newIdentifier();

		size_t size = 28;

		int points[] = { 
			0, -100, 
			10, 0, 
			0, 90, 
			90, 0, 
			0, 20,
			-90, 0,
			0, 90,
			-20, 0,
			0, -90,
			-90, 0,
			0, -20,
			90, 0,
			0, -90,
			10, 0
		};

		path->newPath();
		path->selectStyle(0, 0, -1);
		path->polygon(points, size);
		movie.add(path->defineShape(identifier));
		movie.add(new FSPlaceObject2(identifier, 1));
		movie.add(new FSShowFrame());
	    
		/*
		* Draw a cubic bezier curve
		* 
		* This simple curve is included to show how cubic Bezier curves are 
		* drawn. Flash only directly supports quadratic Bezier curves. Converting
		* from cubic to quadratic is mathematically difficult so the cubic curve
		* is flattened and drawn as a series of straight lines. The results are 
		* visually appealing and the slight increase in the size of the Flash 
		* file is compensated for by the increase in drawing performance.
		* 
		* Note that the path is closed before the shape is generated. The 
		* FSImageConstructor tracks the initial and current drawing points. When
		* a closePath() call is made it draws a straight line (if required)
		* between the current point and the initial point to ensure that the 
		* shape is closed and will be rendered correctly.
		*/
		identifier = movie.newIdentifier();

		path->newPath();
		path->selectStyle(0, 0, -1);
		path->curve(0, -100, 150, -100, 150, 0);
		path->closePath();

		movie.add(path->defineShape(identifier));
		movie.add(new FSPlaceObject2(identifier, 1));
		movie.add(new FSShowFrame());
	    
		saveMovie(movie, stringOption(options, "resultDir"), "BasicShapes.swf");

		delete path;
	}
};

#endif