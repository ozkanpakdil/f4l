/*
 * FSShapeConstructor.cpp
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

#include "FSShapeConstructor.h"
#include <transform/transform.h>

using namespace transform;

namespace transform {

class FSShapeConstructorImpl : public FSShapeConstructor
{
public:
    FSShapeConstructorImpl() 
        : pathInProgress(false)
        , initialX(0)
        , initialY(0)
        , currentX(0)
        , currentY(0)
        , controlX(0)
        , controlY(0)
        , minX(0)
        , minY(0)
        , maxX(0)
        , maxY(0)
        , lineStyle(0)
        , lineWidth(0)
        , objects()
        , lineStyles()
        , fillStyles()
    {
        COORDINATES_ARE_PIXELS = false;

        Px[0] = 0.0;
        Px[1] = 0.0;
        Px[2] = 0.0;
        Px[3] = 0.0;

        Py[0] = 0.0;
        Py[1] = 0.0;
        Py[2] = 0.0;
        Py[3] = 0.0;
    }
    
    ~FSShapeConstructorImpl()
    {
        for (FSVector<FSShapeObject*>::iterator i = objects.begin(); i != objects.end(); i++)
        {
            delete *i;
            *i = 0;
        }
         
        for (FSVector<FSLineStyle*>::iterator i = lineStyles.begin(); i != lineStyles.end(); i++)
        {
            delete *i;
            *i = 0;
        }
       
        for (FSVector<FSFillStyle*>::iterator i = fillStyles.begin(); i != fillStyles.end(); i++)
        {
            delete *i;
            *i = 0;
        }
    }
    void operator delete(void* p)
    {
        ::operator delete(p);
    }
    void CALL destroy()
    {
        delete this;
    }
    void CALL setLineStyle(int index, FSLineStyle* aLineStyle)
    {
        delete lineStyles[index];

        lineStyles[index] = aLineStyle->clone();
    }
    void CALL addLineStyle(FSLineStyle* aLineStyle)
    {
        lineStyles.push_back(aLineStyle->clone());
    }
    void CALL setFillStyle(int index, FSFillStyle* aFillStyle)
    {
        delete fillStyles[index];

        switch(aFillStyle->getType())
        {
            case FSFillStyle::Solid: 
                fillStyles[index] = new FSSolidFill(*(FSSolidFill*)aFillStyle); 
                break;
            case FSFillStyle::ClippedBitmap: 
            case FSFillStyle::TiledBitmap: 
                fillStyles[index] = new FSBitmapFill(*(FSBitmapFill*)aFillStyle); 
                break;
            case FSFillStyle::LinearGradient: 
            case FSFillStyle::RadialGradient: 
                fillStyles[index] = new FSGradientFill(*(FSGradientFill*)aFillStyle); 
                break;
        }
    }
    void CALL addFillStyle(FSFillStyle* aFillStyle)
    {
        switch(aFillStyle->getType())
        {
            case FSFillStyle::Solid: 
                fillStyles.push_back(new FSSolidFill(*(FSSolidFill*)aFillStyle)); 
                break;
            case FSFillStyle::ClippedBitmap: 
            case FSFillStyle::TiledBitmap: 
                fillStyles.push_back(new FSBitmapFill(*(FSBitmapFill*)aFillStyle)); 
                break;
            case FSFillStyle::LinearGradient: 
            case FSFillStyle::RadialGradient: 
                fillStyles.push_back(new FSGradientFill(*(FSGradientFill*)aFillStyle)); 
                break;
        }
    }
    void CALL selectLineStyle(int index)
    {
        lineStyle = index;
        lineWidth = ((FSSolidLine*)(lineStyles[index]))->getWidth();

        objects.push_back(new FSShapeStyle(index+1, Transform::VALUE_NOT_SET, Transform::VALUE_NOT_SET));
    }   
    void CALL selectFillStyle(int index)
    {
        objects.push_back(new FSShapeStyle(Transform::VALUE_NOT_SET, index+1, Transform::VALUE_NOT_SET));
    }  
    void CALL selectAltStyle(int index)
    {
        objects.push_back(new FSShapeStyle(Transform::VALUE_NOT_SET, Transform::VALUE_NOT_SET, index+1));
    }
    void CALL selectStyle(int lineIndex, int fillIndex, int altIndex)
    {
        int lindex = (lineIndex >= 0) ? lineIndex+1 : Transform::VALUE_NOT_SET;
        int findex = (fillIndex >= 0) ? fillIndex+1 : Transform::VALUE_NOT_SET;
        int aindex = (altIndex >= 0) ? altIndex+1 : Transform::VALUE_NOT_SET;

        if (lineIndex >= 0)
        {
            lineStyle = lineIndex;
            lineWidth = ((FSSolidLine*)(lineStyles[lineIndex]))->getWidth();
        }
        objects.push_back(new FSShapeStyle(lindex, findex, aindex));
    }
    FSDefineShape3* CALL defineShape(int identifier)
    {
        FSVector<transform::FSShapeObject*> newObjects(objects.size());
        FSVector<transform::FSLineStyle*> newLineStyles(lineStyles.size());
        FSVector<transform::FSFillStyle*> newFillStyles(fillStyles.size());

        int index = 0;

        for (FSVector<FSShapeObject*>::const_iterator i = objects.begin(); i != objects.end(); i++, index++)
            newObjects[index] = (*i)->clone();

        index = 0;
        
        for (FSVector<FSFillStyle*>::const_iterator i = fillStyles.begin(); i != fillStyles.end(); i++, index++)
            newFillStyles[index] = (*i)->clone();

        index = 0;
        
        for (FSVector<FSLineStyle*>::const_iterator i = lineStyles.begin(); i != lineStyles.end(); i++, index++)
            newLineStyles[index] = (*i)->clone();
        
        return new FSDefineShape3(identifier, FSBounds(minX, minY, maxX, maxY), newFillStyles, newLineStyles, FSShape(newObjects));
    }

    void CALL newPath()
    {
        pathInProgress = false;
        
        setInitial(0, 0);
        setCurrent(0, 0);
        setControl(0, 0);
        setBounds(0, 0, 0, 0);
        
        for (FSVector<FSShapeObject*>::iterator i = objects.begin(); i != objects.end(); i++)
        {
            delete *i;
            *i = 0;
        }
         
          objects.resize(0);

        lineStyle = 0;
        lineWidth = 0;
    }    
    void CALL closePath()
    {
        int dx = initialX - currentX;
        int dy = initialY - currentY;
        
        if (dx != 0 || dy != 0)
            objects.push_back(new FSLine(dx, dy));
            
        setCurrent(initialX, initialY);
    }  
    void CALL move(int x, int y)
    {
        x = COORDINATES_ARE_PIXELS ? x * 20 : x;
        y = COORDINATES_ARE_PIXELS ? y * 20 : y;
        
        objects.push_back(new FSShapeStyle(x, y));

        setControl((currentX+x)/2, (currentY+y)/2);
        setCurrent(x, y);
        setInitial(x, y);
    }   
    void CALL moveForFont(int x, int y)
    {
        x = COORDINATES_ARE_PIXELS ? x * 20 : x;
        y = COORDINATES_ARE_PIXELS ? y * 20 : y;
        
        objects.push_back(new FSShapeStyle(1, Transform::VALUE_NOT_SET, 1, x, y));

        setControl((currentX+x)/2, (currentY+y)/2);
        setCurrent(x, y);
        setInitial(x, y);
    } 
    void CALL rmove(int x, int y)
    {
        x = COORDINATES_ARE_PIXELS ? x * 20 : x;
        y = COORDINATES_ARE_PIXELS ? y * 20 : y;
        
        objects.push_back(new FSShapeStyle(x+currentX, y+currentY)); 

        setControl(currentX+x/2, currentY+y/2);
        setCurrent(currentX+x, currentY+y);
   } 
    void CALL line(int x, int y)
    {
        x = (COORDINATES_ARE_PIXELS ? x * 20 : x) - currentX;
        y = (COORDINATES_ARE_PIXELS ? y * 20 : y) - currentY;

        objects.push_back(new FSLine(x, y));
        
        if (pathInProgress == false)
        {
            setInitial(currentX, currentY);
            pathInProgress = true;
        }
        setControl(currentX+x/2, currentY+y/2);
        setCurrent(currentX+x, currentY+y);
    }
    void CALL rline(int x, int y)
    {
        x = COORDINATES_ARE_PIXELS ? x * 20 : x;
        y = COORDINATES_ARE_PIXELS ? y * 20 : y;

        objects.push_back(new FSLine(x, y));

        if (pathInProgress == false)
        {
            setInitial(currentX, currentY);
            pathInProgress = true;
        }
        setControl(currentX+x/2, currentY+y/2);
        setCurrent(currentX+x, currentY+y);
    }
    void CALL curve(int x1, int y1, int x, int y)
    {
        x1 = (COORDINATES_ARE_PIXELS ? x1 * 20 : x1) - currentX;
        y1 = (COORDINATES_ARE_PIXELS ? y1 * 20 : y1) - currentY;
        x = (COORDINATES_ARE_PIXELS ? x * 20 : x) - currentX - x1;
        y = (COORDINATES_ARE_PIXELS ? y * 20 : y) - currentY - y1;

        objects.push_back(new FSCurve(x1, y1, x, y));

        if (pathInProgress == false)
        {
            setInitial(currentX, currentY);
            pathInProgress = true;
        }
        setControl(currentX+x1, currentY+y1);
        setCurrent(currentX+x1+x, currentY+y1+y);
    }
    void CALL rcurve(int x1, int y1, int x, int y)
    {
        x1 = COORDINATES_ARE_PIXELS ? x1 * 20 : x1;
        y1 = COORDINATES_ARE_PIXELS ? y1 * 20 : y1;
        x = COORDINATES_ARE_PIXELS ? x * 20 : x;
        y = COORDINATES_ARE_PIXELS ? y * 20 : y;

        objects.push_back(new FSCurve(x1, y1, x, y));

        if (pathInProgress == false)
        {
            setInitial(currentX, currentY);
            pathInProgress = true;
        }
 
        setControl(currentX+x1, currentY+y1);
        setCurrent(currentX+x1+x, currentY+y1+y);
    }
    void CALL curve(int x1, int y1, int x2, int y2, int x, int y)
    {
        Px[0] = currentX;
        Py[0] = currentY;
        Px[1] = COORDINATES_ARE_PIXELS ? x1 * 20 : x1;
        Py[1] = COORDINATES_ARE_PIXELS ? y1 * 20 : y1;
        Px[2] = COORDINATES_ARE_PIXELS ? x2 * 20 : x2;
        Py[2] = COORDINATES_ARE_PIXELS ? y2 * 20 : y2;
        Px[3] = COORDINATES_ARE_PIXELS ? x * 20 : x;
        Py[3] = COORDINATES_ARE_PIXELS ? y * 20 : y;
        
        flatten();
    }
    void CALL rcurve(int x1, int y1, int x2, int y2, int x, int y)
    {
        Px[0] = currentX;
        Py[0] = currentY;
        Px[1] = currentX + (COORDINATES_ARE_PIXELS ? x1 * 20 : x1);
        Py[1] = currentY + (COORDINATES_ARE_PIXELS ? y1 * 20 : y1);
        Px[2] = currentX + (COORDINATES_ARE_PIXELS ? x2 * 20 : x2);
        Py[2] = currentY + (COORDINATES_ARE_PIXELS ? y2 * 20 : y2);
        Px[3] = currentX + (COORDINATES_ARE_PIXELS ? x * 20 : x);
        Py[3] = currentY + (COORDINATES_ARE_PIXELS ? y * 20 : y);
        
        flatten();
    }
    void CALL reflect(int x, int y)
    {
        int x1 = currentX - controlX;
        int y1 = currentY - controlY;
        
        x = (COORDINATES_ARE_PIXELS ? x * 20 : x) - currentX;
        y = (COORDINATES_ARE_PIXELS ? y * 20 : y) - currentY;

        objects.push_back(new FSCurve(x1, y1, x, y));

        if (pathInProgress == false)
        {
            setInitial(currentX, currentY);
            pathInProgress = true;
        }
 
        setControl(x1+currentX, y1+currentY);
        setCurrent(x+currentX, y+currentY);
    }
    void CALL rreflect(int x, int y)
    {
        int x1 = currentX - controlX;
        int y1 = currentY - controlY;

        x = COORDINATES_ARE_PIXELS ? x * 20 : x;
        y = COORDINATES_ARE_PIXELS ? y * 20 : y;

        objects.push_back(new FSCurve(x1, y1, x, y));

        if (pathInProgress == false)
        {
            setInitial(currentX, currentY);
            pathInProgress = true;
        }
 
        setControl(x1+currentX, y1+currentY);
        setCurrent(x+currentX, y+currentY);
    }
    void CALL reflect(int x2, int y2, int x, int y)
    {
        int x1 = currentX - controlX;
        int y1 = currentY - controlY;

        x2 = (COORDINATES_ARE_PIXELS ? x2 * 20 : x2) - currentX;
        y2 = (COORDINATES_ARE_PIXELS ? y2 * 20 : y2) - currentY;

        x = (COORDINATES_ARE_PIXELS ? x * 20 : x) - currentX;
        y = (COORDINATES_ARE_PIXELS ? y * 20 : y) - currentY;

        rcurve(x1, y1, x2, y2, x, y);
    }
    void CALL rreflect(int x2, int y2, int x, int y)
    {
        int x1 = currentX - controlX;
        int y1 = currentY - controlY;

        x2 = COORDINATES_ARE_PIXELS ? x2 * 20 : x2;
        y2 = COORDINATES_ARE_PIXELS ? y2 * 20 : y2;

        x = COORDINATES_ARE_PIXELS ? x * 20 : x;
        y = COORDINATES_ARE_PIXELS ? y * 20 : y;

        rcurve(x1, y1, x2, y2, x, y);
    }
    void CALL rect(int x, int y, int width, int height)
    {
        newPath();
        selectStyle(0, 0, -1);
        move(x-width/2, y-height/2);
        rline(width, 0);
        rline(0, height);
        rline(-width, 0);
        rline(0, -height);
        closePath();
    }
    void CALL rect(int width, int height)
    {
        rect(0, 0, width, height);
    }
    void CALL rect(int x, int y, int width, int height, int radius)
    {
        int shortestSide = (height < width) ? height : width;
    
        if (radius > shortestSide/2)
            radius = shortestSide/2;
    
        newPath();
        selectStyle(0, 0, -1);
        move(x, y-height/2);
        rline(width/2-radius, 0);
        rcurve(radius, 0, 0, radius);
        rline(0, height - 2*radius);
        rcurve(0, radius, -radius, 0);
        rline(-(width-2*radius), 0);
        rcurve(-radius, 0, 0, -radius);
        rline(0, -(height-2*radius));
        rcurve(0, -radius, radius, 0);
        closePath();
    }
    void CALL rect(int width, int height, int radius)
    {
        rect(0, 0, width, height, radius);
    }
    void CALL ellipse(int x, int y, int rx, int ry)
    {
        int startX = (int) (0.707 * rx) + x;
        int startY = (int) (0.707 * ry) + y;

        int ax = (int) (0.293 * rx);
        int ay = (int) (0.293 * ry);
        int cx = (int) (0.414 * rx);
        int cy = (int) (0.414 * ry);
            
        newPath();
        selectStyle(0, 0, -1);
        move(startX, startY);
        rcurve(-ax, ay, -cx, 0);
        rcurve(-cx, 0, -ax, -ay);
        rcurve(-ax, -ay, 0, -cy);
        rcurve(0, -cy,  ax, -ay);
        rcurve(ax, -ay, cx, 0);
        rcurve(cx, 0,  ax, ay);
        rcurve(ax, ay, 0, cy);
        rcurve(0, cy, -ax, ay);
        closePath();
    }
    void CALL ellipse(int rx, int ry)
    {
        ellipse(0, 0, rx, ry);
    }
    void CALL circle(int x, int y, int r)
    {
        ellipse(x, y, r, r);
    }
    void CALL circle(int r)
    {
        ellipse(0, 0, r, r);
    }
    void CALL polygon(int points[], size_t size)
    {
        unsigned int i;
        size_t length = size;
        
        if (length % 2 == 1)
            length -= 1;
        
        rmove(points[0], points[1]);

        for (i=2; i<length; i+=2)
            rline(points[i], points[i+1]);
            
        closePath();
    }


private:
    void setInitial(int x, int y)
    {
        initialX = x;
        initialY = y;
    }
    void setCurrent(int x, int y)
    {
        currentX = x;
        currentY = y;
        
        if ((x - lineWidth/2) < minX) minX = x - lineWidth/2;
        if ((y - lineWidth/2) < minY) minY = y - lineWidth/2;
        if ((x + lineWidth/2) > maxX) maxX = x + lineWidth/2;
        if ((y + lineWidth/2) > maxY) maxY = y + lineWidth/2;
    }
    void setControl(int x, int y)
    {
        controlX = x;
        controlY = y;

        if ((x - lineWidth/2) < minX) minX = x - lineWidth/2;
        if ((y - lineWidth/2) < minY) minY = y - lineWidth/2;
        if ((x + lineWidth/2) > maxX) maxX = x + lineWidth/2;
        if ((y + lineWidth/2) > maxY) maxY = y + lineWidth/2;
    }
    void setBounds(int xl, int yl, int xu, int yu)
    {
        minX = xl;
        minY = yl;
        maxX = xu;
        maxY = yu;
    }
    void flatten()
    {
        double Qx[] = {0.0, 0.0, 0.0, 0.0};
        double Qy[] = {0.0, 0.0, 0.0, 0.0};

        double u;
        double Ax, Ay, Bx, By;

        for (;;) 
        {
            Ax = 2.0 * Px[0] + Px[3] - 3.0 * Px[1];  Ax *= Ax;
            Bx = 2.0 * Px[3] + Px[0] - 3.0 * Px[2];  Bx *= Bx;
        
            if (Ax < Bx) Ax = Bx;

            Ay = 2.0 * Py[0] + Py[3] - 3.0 * Py[1];  Ay *= Ay;
            By = 2.0 * Py[3] + Py[0] - 3.0 * Py[2];  By*= By;
        
            if (Ay < By) Ay = By;

            if ((Ax + Ay) < 0.25) // flatten limit
            {
                objects.push_back(new FSLine((int)(Px[3])-currentX, (int)(Py[3])-currentY));
                setControl((int)(Px[1]), (int)(Py[1]));
                setControl((int)(Px[2]), (int)(Py[2]));
                setCurrent((int)(Px[3]), (int)(Py[3]));
                break;
            }
            else 
            {
                Qx[3] = Px[3];
                u = (Px[1] + Px[2]) / 2;
                Px[1] = (Px[0] + Px[1]) / 2;
                Qx[2] = (Px[2] + Px[3]) / 2;
                Px[2] = (Px[1] + u) / 2;
                Qx[1] = (u + Qx[2]) / 2;
                Px[3] = Qx[0] = (Px[2] + Qx[1]) / 2;

                Qy[3] = Py[3];
                u = (Py[1] + Py[2]) / 2;
                Py[1] = (Py[0] + Py[1]) / 2;
                Qy[2] = (Py[2] + Py[3]) / 2;
                Py[2] = (Py[1] + u) / 2;
                Qy[1] = (u + Qy[2]) / 2;
                Py[3] = Qy[0] = (Py[2] + Qy[1]) / 2;

                flatten();
                  
                Px[0] = Qx[0];
                Py[0] = Qy[0];
                Px[1] = Qx[1];
                Py[1] = Qy[1];
                Px[2] = Qx[2];
                Py[2] = Qy[2];
                Px[3] = Qx[3];
                Py[3] = Qy[3];
                  
                continue;
            }
        }
    }

    bool pathInProgress;
    
    int initialX;
    int initialY;
    
    int currentX;
    int currentY;
    
    int controlX;
    int controlY;

    int minX;
    int minY;
    int maxX;
    int maxY;
    
    int lineStyle;
    int lineWidth;
    
    FSVector<transform::FSShapeObject*> objects;
    FSVector<transform::FSLineStyle*> lineStyles;
    FSVector<transform::FSFillStyle*> fillStyles;

    double Px[4];
    double Py[4];
};

extern "C" FSShapeConstructor* ShapeConstructor()
{
    return new FSShapeConstructorImpl();
}

}

