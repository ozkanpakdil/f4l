/*
 *  DrawingShapes.cpp
 *  Transform Examples
 *
 *  Created by smackay on Thu May 08 2003.
 *  Copyright (c) 2001-2004 Flagstone Software Ltd. All rights reserved.
 *
 *  This code is distributed on an 'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER
 *  EXPRESS OR IMPLIED, AND Flagstone HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING
 *  WITHOUT LIMITATION, ANY WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
 *  PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY RIGHTS.
 */

#ifndef __DrawingShapes_h__
#define __DrawingShapes_h__ 1

/*
 * DrawingShapes illustrates how to use the FSDefineShape class to draw shapes. Two
 * other classes, FSDefineShape2 and FSDefineShape3 are provided in the Transform
 * library. FSDefineShape2 allows a large number of line or fill styles to defined
 * (more than 65535 which is rarely required if ever). FSDefineShape3 supports
 * transparent colours. The classes are used in exactly the same way as FSDefineShape.
 *
 * To run this example, type the following on a command line:
 *
 * examples --example DrawingShapes [--resultDir path]
 *
 * where
 *
 *     resultDir is the directory where the Flash file generated by the example 
 *     is written to.
 *
 * This example draws two overlapping quarter circles in front of a square and
 * placed in the centre of the screen. While this example is trivial it illustrates
 * the different mechanisms used when drawing shapes.
 *
 * To draw a shape the following information is required:
 *
 * identifier - an identifier, unique within a given movie, that is used to refer to
 * the FSDefineShape object.
 *
 * bounds - an FSBounds object that defines the bounding box inside which the shape is
 * drawn.
 *
 * line styles - an array of FSSolidLine objects that describe how the outline path,
 * if any, of a shape is stroked.
 *
 * fill styles - an array of FSSolidFill, FSBitmapFill or FSGradientFill objects that
 * define how the enclosed area of the shape will be filled.
 *
 * shape - an FSShape object containing the commands that select the line and fill 
 * styles and draw the shape.
 */
class DrawingShapes
{
public:
    DrawingShapes(map<string, string>& options)
    {
        FSMovie movie;

        /*
        * The FSMovie object manages the unique identifiers that will be assigned to
        * each object that defines shapes, buttons, sounds, etc.
        */
        int identifier = movie.newIdentifier();

        /*
        * The bounding box for a shape defines both the physical dimensions of the shape
        * and the coordinate range used when specifying the drawing commands. The bounding
        * rectangle is defined by specifying the coordinates of the top left and the bottom
        * right corners. The positive x-axis extends from the left to right of the screen
        * and the positive y-axis extends from the top to bottom of the screen.
        *
        * The coordinates range for the shape defines a bounding rectangle 6000 twips by
        * 600 twips (300 pixels by 300 pixels with the center of the shape at the 
        * coordinates (0, 0).
        *
        * The coordinates used to define the shape are relative to the screen coordinates
        * when the shape is placed on the display list, allowing the same definition to be
        * used to draw shapes at different locations on the screen. Specifying the origin
        * of the shape to be at the coordinates (0, 0) simplifies placing the shapes using
        * the FSPlaceObject or FSPlaceObject2 classes.
        */
        FSBounds bounds(-3000, -3000, 3000, 3000);

        /*
        * Define the line style used to draw the background square.
        */
        FSVector<FSLineStyle*> lineStyles;

        lineStyles.push_back(new FSSolidLine(20, FSColorTable::black()));

        /*
        * Define the the solid yellow fill style for the rectangle drawn into
        * the background.
        */
        FSVector<FSFillStyle*> fillStyles;

        fillStyles.push_back(new FSSolidFill(FSColorTable::yellow()));

        /*
        * Construct the shape that will contain the individual commands that
        * describe how the shape is drawn.
        */
        FSShape shape;

        /*
        * The first object in any shape is an instance of the FSShapeStyle class
        * which selects the line and fill styles. The initial drawing point is
        * located at (0,0) so the FSShapeStyle object also specifies a
        * move to change the location of the drawing point.
        *
        * Indices into the array of line and fill styles start at 1. An index of 0
        * indicates that no current style is selected.
        */
        shape.add(new FSShapeStyle(1, 1, 0, 3000, -3000));

        // Draw the background square.
        
        shape.add(new FSLine(-6000, 0));
        shape.add(new FSLine(0, 6000));
        shape.add(new FSLine(6000, 0));
        shape.add(new FSLine(0, -6000));

        /*
        * Define a new set of line styles and fill styles that are used to draw the
        * quarter circles. While the styles used could have been placed in the original
        * styles arrays the FSShapeStyle object can also be used the change the set
        * of styles used as a shape is being drawn.
        *
        * Two line styles, 1 pixel and 5 pixels wide are define. Each line is drawn using
        * a solid black colour.
        */
        FSVector<FSLineStyle*> newLineStyles = FSVector<FSLineStyle*>();

        newLineStyles.push_back(new FSSolidLine(20, FSColorTable::black()));
        newLineStyles.push_back(new FSSolidLine(100, FSColorTable::black()));

        /*
        * Define the styles used to fill the different parts of the shape using a solid
        * colour. The quarter circles are filled with a solid red and blue colour. In
        * the area where they overlap the colour is solid green.
        */
        FSVector<FSFillStyle*> newFillStyles = FSVector<FSFillStyle*>();

        newFillStyles.push_back(new FSSolidFill(FSColorTable::red()));
        newFillStyles.push_back(new FSSolidFill(FSColorTable::green()));
        newFillStyles.push_back(new FSSolidFill(FSColorTable::blue()));

        /*
        * Select the new line and fill styles and specify the new drawing point from
        * where the first quarter circle will be drawn.
        */
        shape.add(new FSShapeStyle(1, 1, 0, 500, -2500, newLineStyles, newFillStyles));

        /*
        * Start drawing the first quarter circle. Since this part of the shape is
        * defined later in the shape it will be displayed in front of the square
        * when the shape is rendered.
        */
        shape.add(new FSCurve(-3000, 0, 0, 3000));
        shape.add(new FSLine(2000, 0));

        // Fill the overlapping area to the right of the line being
        // drawn with a solid green.
        
        shape.add(new FSShapeStyle(2, 1, 2));
        shape.add(new FSLine(0, -1000));
        shape.add(new FSLine(1000, 0));

        // Draw the non-overlapping part of the second quarter circle.
        // The area to the right of the line is filled with a solid blue.
        
        shape.add(new FSShapeStyle(2, 0, 3));
        shape.add(new FSLine(2000, 0));
        shape.add(new FSCurve(0, 3000, -3000, 0));
        shape.add(new FSLine(0, -2000));

        // Complete the overlapping area to the left of the line being drawn.
        
        shape.add(new FSShapeStyle(1, 2, 3));
        shape.add(new FSLine(1000, 0));
        shape.add(new FSLine(0, -1000));

        // Change the fill style to complete the first quarter circle and
        // close the path being drawn.

        shape.add(new FSShapeStyle(1, 1, 0));
        shape.add(new FSLine(0, -2000));

        /*
        * Define the shape starting with the original set of line and filled styles. 
        */
        FSDefineShape* defineShape = new FSDefineShape(identifier, bounds, fillStyles, lineStyles, shape);

        /*
        * Add all the remaining objects required to create the movie. 
        */
        movie.setFrameSize(FSBounds(-4000, -4000, 4000, 4000));
        movie.setFrameRate(1.0f);

        movie.add(new FSSetBackgroundColor(FSColorTable::lightblue()));

        // Add the definition of the shape to the movie. An object must be defined
        // before it can be placed on the display list.
        
        movie.add(defineShape);

        // Place the shape on the display list located in the centre of the screen.
        
        movie.add(new FSPlaceObject(identifier, 1, 0, 0));

        movie.add(new FSShowFrame());

        saveMovie(movie, stringOption(options, "resultDir"), "DrawingShapes.swf");
    }
};

#endif