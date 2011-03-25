/*
 * FSShapeConstructor.h
 * Transform Utilities
 *
 * Copyright (c) 2001-2004 Flagstone Software Ltd.. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification, 
 * are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright notice, 
 *    this list of conditions and the following disclaimer in the documentation 
 *    and/or other materials provided with the distribution.
 *  * Neither the name of Flagstone Software Ltd. nor the names of its contributors 
 *    may be used to endorse or promote products derived from this software 
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND 
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED 
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. 
 * IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, 
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, 
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, 
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF 
 * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE 
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED 
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef __FSShapeConstructor_h__
#define __FSShapeConstructor_h__ 1

#include "FSTransformUtil.h"

using namespace transform;

namespace transform
{
    class FSDefineShape3;
    class FSLineStyle;
    class FSFillStyle;
/**
 * The FSShapeConstructor class is used to create shape definitions. Arbitrary paths can be 
 * created using a series of move, line or curve segments. Drawing operations using both
 * absolute coordinates and coordinates relative to the current point (updated after every 
 * operation) are supported. 
 * 
 * Cubic and quadratic curves are supported. Flash only supports quadratic curves so cubic 
 * curves are approximated by a series of line segments using (converting cubic to quadratic 
 * curves is mathematically difficult).
 * 
 * As a path is drawn the maximum and minimum x and y coordinates are recorded so that the 
 * bounding rectangle that completely encloses the shape can be defined. This is used when
 * creating shape definitions using the FSDefineShape, FSDefineShape2 or FSDefineShape3 classes.
 * 
 * The FSShapeConstructor class also supports a number of method to create closed paths that
 * represent different geometric shapes. Basic rectangles, ellipses and circles are supported.
 * More complex shapes can be drawn using the polygon() method which uses pairs of points to 
 * specified the vertices of an arbitrary shapes.
 * 
 * When drawing paths whether coordinates are specified in twips or pixels is controlled by 
 * the attributes COORDINATES_ARE_PIXELS. When true coordinates are specified in pixels,
 * while coordinates are specified in twips when false. 1 pixel == 20 twips. Internally all
 * coordinates are converted to twips to perform the actual drawing.
 * 
 * The styles used to draw the path and fill the area enclosed are specified using the index
 * position of the style object in the arrays of styles maintained by the shape definition
 * object (FSDefineShape, SDefineShape2 or FSDefineShape3) used to construct the final shape. 
 *  
 * <b>Examples</b>
 *
 * The following code samples illustrate how to use the FSShapeConstructor class create shapes.
 *
 * 1. Defining a rectangle using move and line drawing operations.\n
 * 
 *\verbatim
 *    FSShapeConstructor* path = ShapeConstructor();
 * 
 *    path->COORDINATES_ARE_PIXELS = true;
 * 
 *    int width = 200;
 *    int height = 100;
 *
 *    // Setting the line style before any drawing commands is important
 *    // so the thickness of the line can be taken into account when
 *    // calculating the bounding rectangle which must completely enclose
 *    // the shape so it will be drawn correctly.
 *
 *    FSSolidLine* lineStyle = new FSSolidLine(1, FSColorTable::black());
 *    FSSolidFill* fillStyle = new FSSolidFill(FSColorTable::red());
 *
 *    path->add(lineStyle);
 *    path->add(fillStyle);
 *
 *    delete lineStyle;
 *    delete fillStyle;
 *
 *    path->newPath();                   // start a new path
 *    path->selectStyle(1, 1, -1);       // select the first line and fill style objects
 *    path->move(-width/2, -height/2);   // Move to the top left corner
 *    path->rline(width, 0);             // Draw the sides of the rectangle
 *    path->rline(0, height);
 *    path->rline(-width, 0);
 *    path->rline(0, -height);
 *    path->closePath();                 // close the path to correctly seal the line ends.
 * 
 *    // Now define the shape.
 * 
 *    FSDefineShape3* rect = path->defineShape(movie.newIdentifier());
 * 
 * \endverbatim
 *
 * 2. Defining a rectangle using the path creation method.\n
 * 
 *\verbatim
 *    FSShapeConstructor* path = ShapeConstructor();
 * 
 *    path->COORDINATES_ARE_PIXELS = true;
 *
 *    // Define the origin for the shape so the bottom left corner of the 
 *    // rectangle will appear at the coordinates the shape is place at 
 *    // using the FSPlaceObject or FSPlaceObject2 class.
 * 
 *    int xorigin = 100;
 *    int yorigin = -50;
 * 
 *    int width = 200;
 *    int height = 100;
 *    int cornerRadius = 10
 *
 *    FSSolidLine* lineStyle = new FSSolidLine(1, FSColorTable::black());
 *    FSSolidFill* fillStyle = new FSSolidFill(FSColorTable::red());
 *
 *    path->add(lineStyle);
 *    path->add(fillStyle);
 *
 *    delete lineStyle;
 *    delete fillStyle;
 *
 *    // Create a rectangle with rounded corners.
 * 
 *    path->rect(xorign, yorigin, width, height, cornerRadius);
 * 
 *    // Now define the shape.
 * 
 *    FSDefineShape3* rect = path->defineShape(movie.newIdentifier());
 *
 *\endverbatim
 *
 */
class FSShapeConstructor
{
public:
    /** 
     * The COORDINATES_ARE_PIXELS flag controls whether the coordinates passed to methods when creating 
     * a path of predefined shape are expressed in pixels (true) or twips (false).
     *
     * Flash coordinates are specified in twips (1 twip equals 1/1440th of an inch or 1/20th of a point). 
     * Allowing coordinates to be specified in pixels simplifies the drawing process avoiding the conversion 
     * to twips by multiplying each value by 20.
     */
    bool COORDINATES_ARE_PIXELS;
    /** Sets the line style at the index in the array of line styles.

        @param index the position in the array of line styles.
        @param aLineStyle a pointer to an FSLineStyle object.
        @throws ArrayIndexOutOfBounds if the index &lt; 0 or index &gt; array size.
        */
    virtual void CALL setLineStyle(int index, FSLineStyle* aLineStyle) = 0;
    /** Copy an FSLineStyle object to the array of line styles.

        @param aLineStyle a pointer to an FSLineStyle object.
        */
    virtual void CALL addLineStyle(FSLineStyle* aLineStyle) = 0;
    /** Copies the fill style to the specified index in the array of fill styles.

        @param index the position in the array of fill styles.
        @param aFillStyle a pointer to an FSFillStyle object.
        @throws ArrayIndexOutOfBounds if the index &lt; 0 or index &gt; array size.
        */
    virtual void CALL setFillStyle(int index, FSFillStyle* aFillStyle) = 0;

    /** Copies the fill style object to the array of fill styles.

        @param aFillStyle a pointer to an FSFillStyle object.
        */
    virtual void CALL addFillStyle(FSFillStyle* aFillStyle) = 0;
    /**
     * Selects the style used to draw the outline of the shape from the array of 
     * line styles.
     * 
     * @param index the position of the style used to draw the shape.
     */
    virtual void CALL selectLineStyle(int index) = 0;
    /**
     * Selects the style used to fill the contents of the shape from the array of 
     * fill styles.
     * 
     * @param index the position of the style used to fill the shape.
     */
    virtual void CALL selectFillStyle(int index) = 0;
    /**
     * Selects the style used to fill overlapping areas of the shape from the 
     * array of fill styles.
     * 
     * @param index the position of the style used to fill overlapping areas.
     */
    virtual void CALL selectAltStyle(int index) = 0;
    /**
     * Selects the styles used to draw the outline and fill the contents of the 
     * shape, including overlapping area, from the array of line and fill styles.
     *
     * The style indices are optional, allowing for example a line and fill style
     * to be specified by the overlapping fill style remaining underfined. This 
     * reduces the size of the encoded shape. To leave a style undefined set the 
     * index to a negative number.
     * 
     * @param lineIndex the position of the style used to draw the outline of the shape.
     * @param fillIndex the position of the style used to fill the shape.
     * @param altIndex the position of the style used to fill overlapping areas of the shape.
     */
    virtual void CALL selectStyle(int lineIndex, int fillIndex, int altIndex) = 0;
    /**
     * Generates a shape containing the current path and styles.
     *
     * The shape is constructed with copies of the style arrays and the shape representing the 
     * path drawn. This allows the number of styles to be changed without affecting previously
     * created shapes.
     *
     * @param identifier an unique identifier for the shape.
     */
    virtual FSDefineShape3* CALL defineShape(int identifier) = 0;
    /**
     * Creates a new path, discarding any path elements drawn.
     */
    virtual void CALL newPath() = 0;
    /**
     * Closes the current path by drawing a line from the current point to the starting point of the 
     * path. 
     */
    virtual void CALL closePath() = 0;
    /**
     * move to the point (x,y).
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x the x-coordinate of the point to move to.
     * @param y the y-coordinate of the point to move to.
     */
    virtual void CALL move(int x, int y) = 0;
    /**
     * move relative to the current point.
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x the distance along the x-axis.
     * @param y the distance along the y-axis.
     */
    virtual void CALL rmove(int x, int y) = 0;
    /**
     * draw a line from the current point to the point (x,y).
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x the x-coordinate of the end of the line.
     * @param y the y-coordinate of the end of the line.
     */
    virtual void CALL line(int x, int y) = 0;
    /**
     * draw a line relative to the current point.
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x the distance along the x-axis to the end of the line.
     * @param y the distance along the y-axis to the end of the line.
     */
    virtual void CALL rline(int x, int y) = 0;
    /**
     * draw a quadratic bezier curve from the current point to the point (x,y) with the control 
     * point (x1, y1).
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x1 the x-coordinate of the control point.
     * @param y1 the y-coordinate of the control point.
     * @param x the x-coordinate of the end of the curve.
     * @param y the y-coordinate of the end of the curve.
     */
    virtual void CALL curve(int x1, int y1, int x, int y) = 0;
    /**
     * draw a quadratic bezier curve relative to the current point to the point.
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x1 the distance along the x-axis from the current point to the control point.
     * @param y1 the distance along the y-axis from the current point to the control point.
     * @param x the distance along the x-axis from the current point to the end of the curve.
     * @param y the distance along the y-axis from the current point to the end of the curve.
     */
    virtual void CALL rcurve(int x1, int y1, int x, int y) = 0;
    /**
     * draw a cubic bezier curve from the current point to the point (x,y) with the off-curve control 
     * points (x1, y1) and (x2, y2).
     * 
     * IMPORTANT: Converting cubic bezier curves to the quadratic bezier curves supported by Flash is 
     * mathematically difficult. The cubic curve is approximated by a series of straight line segments. 
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x1 the x-coordinate of the first control point.
     * @param y1 the y-coordinate of the first control point.
     * @param x2 the x-coordinate of the second control point.
     * @param y2 the y-coordinate of the second control point.
     * @param x the x-coordinate of the end of the curve.
     * @param y the y-coordinate of the end of the curve.
     */
    virtual void CALL curve(int x1, int y1, int x2, int y2, int x, int y) = 0;
    /**
     * draw a cubic bezier curve relative to the current point.
     * 
     * IMPORTANT: Converting cubic bezier curves to the quadratic bezier curves supported by Flash is 
     * mathematically difficult. The cubic curve is approximated by a series of straight line segments. 
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x1 the distance along the x-axis from the current point to the first control point.
     * @param y1 the distance along the y-axis from the current point to the first control point.
     * @param x2 the distance along the x-axis from the current point to the second control point.
     * @param y2 the distance along the y-axis from the current point to the second control point.
     * @param x the distance along the x-axis from the current point to the end of the curve.
     * @param y the distance along the y-axis from the current point to the end of the curve.
     */
    virtual void CALL rcurve(int x1, int y1, int x2, int y2, int x, int y) = 0;
    /**
     * draw a quadratic bezier curve from the current point to the point (x,y) using the control point
     * for the previously drawn curve.
     * 
     * If no curve has been drawn previously then a control point midway along the previous line or 
     * move is used.
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x the x-coordinate of the end of the curve.
     * @param y the y-coordinate of the end of the curve.
     */
    virtual void CALL reflect(int x, int y) = 0;
    /**
     * draw a quadratic bezier curve relative to the current point to the point using the control point
     * for the previously drawn curve.
     * 
     * If no curve has been drawn previously then a control point midway along the previous line or 
     * move is used.
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x the distance along the x-axis from the current point to the end of the curve.
     * @param y the distance along the y-axis from the current point to the end of the curve.
     */
    virtual void CALL rreflect(int x, int y) = 0;
    /**
     * draw a cubic bezier curve from the current point to the point (x,y). The first control point
     * is the one defined for the previously drawn curve. The second controlk point is the 
     * coordinates (x2, y2).
     * 
     * If no curve has been drawn previously then a control point midway along the previous line or 
     * move is used.
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x2 the x-coordinate of the control point.
     * @param y2 the y-coordinate of the control point.
     * @param x the x-coordinate of the end of the curve.
     * @param y the y-coordinate of the end of the curve.
     */
    virtual void CALL reflect(int x2, int y2, int x, int y) = 0;
    /**
     * draw a cubic bezier curve relative to the current point. The first control point
     * is the one defined for the previously drawn curve. The second control point is the 
     * relative point (x2, y2).
     * 
     * If no curve has been drawn previously then a control point midway along the previous line or 
     * move is used.
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param x2 the distance along the x-axis from the current point to the second control point.
     * @param y2 the distance along the y-axis from the current point to the second control point.
     * @param x the distance along the x-axis from the current point to the end of the curve.
     * @param y the distance along the y-axis from the current point to the end of the curve.
     */
    virtual void CALL rreflect(int x2, int y2, int x, int y) = 0;
    /**
     * Creates a closed path in the shape of a rectangle with the specified width and height.
     * The center of the rectangle is located at the point (x,y).
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * The origin of the shape can be used to control the relative placement of the rectangle 
     * when it is placed on the Flash Player's display list using either the FSPlaceObject or 
     * FSPlaceObject2 class.
     * 
     * @param x the x-coordinate of the center of the rectangle.
     * @param y the y-coordinate of the center of the rectangle.
     * @param width the width of the rectangle.
     * @param height the height of the rectangle.
     */
    virtual void CALL rect(int x, int y, int width, int height) = 0;
    /**
     * Creates a closed path in the shape of a rectangle with the specified width and height.
     * The center of the rectangle is located at the point (0,0).
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param width the width of the rectangle.
     * @param height the height of the rectangle.
     */
    virtual void CALL rect(int width, int height) = 0;
    /**
     * Creates a closed path in the shape of a rectangle with rounded corners. The shape is drawn
     * with specified width and height and the radius argument specified the radius of the quarter 
     * circle used to draw the corners.
     * 
     * The center of the rectangle is located at the point (x,y).
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * The origin of the shape can be used to control the relative placement of the rectangle 
     * when it is placed on the Flash Player's display list using either the FSPlaceObject or 
     * FSPlaceObject2 class.
     * 
     * @param x the x-coordinate of the center of the rectangle.
     * @param y the y-coordinate of the center of the rectangle.
     * @param width the width of the rectangle.
     * @param height the height of the rectangle.
     * @param radius the radius of the quarter circle used to draw the corners.
     */
    virtual void CALL rect(int x, int y, int width, int height, int radius) = 0;
    /**
     * Creates a closed path in the shape of a rectangle with rounded corners. The shape is drawn
     * with specified width and height and the radius argument specified the radius of the quarter 
     * circle used to draw the corners. The center of the rectangle is located at the point (0,0).
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param width the width of the rectangle.
     * @param height the height of the rectangle.
     * @param radius the radius of the quarter circle used to draw the corners.
     */
    virtual void CALL rect(int width, int height, int radius) = 0;
    /**
     * Creates a closed path in the shape of an ellipse. The arguments rx and ry specify the radius 
     * of the ellipse in the x and y directions respectively.
     * 
     * The center of the ellipse is located at the point (x,y).
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * The origin of the shape can be used to control the relative placement of the ellipse 
     * when it is placed on the Flash Player's display list using either the FSPlaceObject or 
     * FSPlaceObject2 class.
     * 
     * @param x the x-coordinate of the center of the ellipse.
     * @param y the y-coordinate of the center of the ellipse.
     * @param rx the radius of the ellipse in the x direction.
     * @param ry the radius of the ellipse in the y direction.
     */
    virtual void CALL ellipse(int x, int y, int rx, int ry) = 0;
    /**
     * Creates a closed path in the shape of an ellipse. The arguments rx and ry specify the radius 
     * of the ellipse in the x and y directions respectively.
     * 
     * The center of the ellipse is located at the point (0,0).
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param rx the radius of the ellipse in the x direction.
     * @param ry the radius of the ellipse in the y direction.
     */
    virtual void CALL ellipse(int rx, int ry) = 0;
    /**
     * Creates a closed path in the shape of a circle. The center of the circle is located at 
     * the point (x,y) with radius r.
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * The origin of the shape can be used to control the relative placement of the circle 
     * when it is placed on the Flash Player's display list using either the FSPlaceObject or 
     * FSPlaceObject2 class.
     * 
     * @param x the x-coordinate of the center of the circle.
     * @param y the y-coordinate of the center of the circle.
     * @param r the radius of the circle.
     */
    virtual void CALL circle(int x, int y, int r) = 0;
    /**
     * Creates a closed path in the shape of a circle. The center of the circle is located at 
     * the point (0,0) with radius r.
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param r the radius of the circle.
     */
    virtual void CALL circle(int r) = 0;
    /**
     * Create a closed shape with vertices defines by pairs of coordinates from the array argument.
     * The first pair of points in the array specifies a move. Line segments a drawn relative to 
     * the current point which is updated after each segment is drawn.
     * 
     * If the number of points is an odd number then the last point will be ignored.
     * 
     * If the COORDINATES_ARE_PIXELS attribute is true then the coordinates are specified in pixels,
     * otherwise the coordinates are specified in twips.
     * 
     * @param points and array of coordinate pairs. The first pair of points defines the coordinates
     * of a move operation, successive pairs define the coordinates for relative lines.
     * @param size the number of elements in the array.
     */
    virtual void CALL polygon(int points[], size_t size) = 0;

    virtual void CALL moveForFont(int x, int y) = 0;
    /**
     * Deletes this object.
     */
	virtual void CALL destroy() = 0;
    /**
     * Deletes this object.
     *
     * @param p a pointer to a parser object.
     */
    void operator delete(void* p) 
    {
        if (p) 
        {
            FSShapeConstructor* constructor = static_cast<FSShapeConstructor*>(p);
            constructor->destroy();
        }
    }
};
/**
 * Factory function for creating an FSShapeConstructor object.
 */
extern "C" FSShapeConstructor* ShapeConstructor();
}

#endif // __FSShapeConstructor_h__

