/*
 *  FSCoordTransform.cpp
 *  Transform SWF
 *
 *  Created by smackay on Tue Feb 18 2003.
 *  Copyright (c) 2001-2003 Flagstone Software Ltd. All rights reserved.
 *
 *  This file contains Original Code and/or Modifications of Original Code as defined in
 *  and that are subject to the Flagstone Software Source License Version 1.0 (the
 *  'License'). You may not use this file except in compliance with the License. Please
 *  obtain a copy of the License at http://www.flagstonesoftware.com/licenses/source.html
 *  and read it before using this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an 
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone 
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY 
 *  RIGHTS. Please see the License for the specific language governing rights and limitations 
 *  under the License.
 */

#include "FSCoordTransform.h"

#include <math.h>

#define PI 3.14159265

#include "FSInputStream.h"
#include "FSOutputStream.h"

using namespace transform;

namespace transform
{
    FSCoordTransform::FSCoordTransform(FSInputStream* aStream)
    {
        for(int i=0; i<3; i++)
            for (int j = 0; j<3; j++)
                matrix[i][j] =  (i == j) ? 1.0f : 0.0f;

        decodeFromStream(aStream);
    }

    FSCoordTransform::FSCoordTransform()
    {
        for(int i=0; i<3; i++)
            for (int j = 0; j<3; j++)
                matrix[i][j] =  (i == j) ? 1.0f : 0.0f;
    }

    FSCoordTransform::FSCoordTransform(int x, int y)
    {
        for(int i=0; i<3; i++)
            for (int j = 0; j<3; j++)
                matrix[i][j] =  (i == j) ? 1.0f : 0.0f;

        matrix[0][2] = (float)x;
        matrix[1][2] = (float)y;
    }

    FSCoordTransform::FSCoordTransform(int x, int y, double scaleX, double scaleY)
    {
        for(int i=0; i<3; i++)
            for (int j = 0; j<3; j++)
                matrix[i][j] =  (i == j) ? 1.0f : 0.0f;

        matrix[0][0] = (float)scaleX;
        matrix[1][1] = (float)scaleY;
        matrix[0][2] = (float)x;
        matrix[1][2] = (float)y;
    }
    
    FSCoordTransform::FSCoordTransform(const float aMatrix[][3])
    {
        setMatrix(aMatrix);
    }

    FSCoordTransform* FSCoordTransform::clone() const
    {
        return new FSCoordTransform(*this);
    }
    
    const char* FSCoordTransform::className() const
    {
        const static char _name[] = "FSCoordTransform";

        return _name;
    }

    void FSCoordTransform::translate(int x, int y)
    {
        float m[3][3] = { 
            {1.0f, 0.0f, (float)x}, 
            {0.0f, 1.0f, (float)y}, 
            {0.0f, 0.0f, 1.0f}
        };
        
        composite(m);
    }

    void FSCoordTransform::scale(double x, double y)
    {
        float m[3][3] = { 
            {(float)x, 0.0f, 0.0f}, 
            {0.0f, (float)y, 0.0f}, 
            {0.0f, 0.0f, 1.0f}
        };
        
        composite(m);
    }

    void FSCoordTransform::rotate(double angle)
    {
        float m[3][3] = { 
            {1.0f, 0.0f, 0.0f}, 
            {0.0f, 1.0f, 0.0f}, 
            {0.0f, 0.0f, 1.0f}
        };
        
        m[0][0] = (float)cos(angle*PI/180);
        m[0][1] = -(float)sin(angle*PI/180);
        m[1][0] = (float)sin(angle*PI/180);
        m[1][1] = (float)cos(angle*PI/180);

        composite(m);
    }

    void FSCoordTransform::shear(double x, double y)
    {
        float m[3][3] = { 
            {1.0f, (float)y, 0.0f}, 
            {(float)x, 1.0f, 0.0f}, 
            {0.0f, 0.0f, 1.0f}
        };
        
        composite(m);
    }

    void FSCoordTransform::transformPoint(int& x, int& y)
    {
        float point[3] = { (float)x, (float)y, 1.0f };
        
        x = (int)(matrix[0][0] * point[0] +  matrix[0][1] * point[1] +  matrix[0][2] * point[2]);
        y = (int)(matrix[1][0] * point[0] +  matrix[1][1] * point[1] +  matrix[1][2] * point[2]);
    }

    void FSCoordTransform::getMatrix(float aMatrix[3][3]) const
    {
        for(int i=0; i<3; i++)
            for (int j = 0; j<3; j++)
                aMatrix[i][j] = matrix[i][j];
    }
    
    void FSCoordTransform::setMatrix(const float aMatrix[][3])
    {
        for(int i=0; i<3; i++)
            for (int j = 0; j<3; j++)
                matrix[i][j] = aMatrix[i][j];
    }
    
    void FSCoordTransform::composite(const FSCoordTransform& transform)
    {
        float m1[3][3];
        float m2[3][3];

        getMatrix(m1);
        transform.getMatrix(m2);

        matrix[0][0] = m1[0][0] * m2[0][0] + m1[0][1] * m2[1][0] + m1[0][2] * m2[2][0];
        matrix[0][1] = m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1];
        matrix[0][2] = m1[0][0] * m2[0][2] + m1[0][1] * m2[1][2] + m1[0][2] * m2[2][2];

        matrix[1][0] = m1[1][0] * m2[0][0] + m1[1][1] * m2[1][0] + m1[1][2] * m2[2][0];
        matrix[1][1] = m1[1][0] * m2[0][1] + m1[1][1] * m2[1][1] + m1[1][2] * m2[2][1];
        matrix[1][2] = m1[1][0] * m2[0][2] + m1[1][1] * m2[1][2] + m1[1][2] * m2[2][2];

        matrix[2][0] = m1[2][0] * m2[0][0] + m1[2][1] * m2[1][0] + m1[2][2] * m2[2][0];
        matrix[2][1] = m1[2][0] * m2[0][1] + m1[2][1] * m2[1][1] + m1[2][2] * m2[2][1];
        matrix[2][2] = m1[2][0] * m2[0][2] + m1[2][1] * m2[1][2] + m1[2][2] * m2[2][2];
    }
    
    int FSCoordTransform::lengthInStream(FSOutputStream* aStream)
    {
        int numberOfBits = 7 + translateFieldSize()*2;
    
        if (containsScaling())
            numberOfBits += 5 + scaleFieldSize()*2;
    
        if (containsRotation())
            numberOfBits += 5 + rotateFieldSize()*2;
    
        numberOfBits += (numberOfBits % 8 > 0) ? 8 - (numberOfBits % 8) : 0;
    
        return numberOfBits>>3;
    }
    
    void FSCoordTransform::encodeToStream(FSOutputStream* aStream)
    {
        int translateBits = translateFieldSize();
        
#ifdef _DEBUG
        aStream->startEncoding(className());
#endif

        /*
         * The parent object decides whether to perform validation.
         */
        aStream->flush();
    
        aStream->write(containsScaling() ? 1 : 0, FSStream::UnsignedBit, 1);
    
        if (containsScaling())
        {
            int scaleBits = scaleFieldSize();
            
            aStream->write(scaleBits, FSStream::UnsignedBit, 5);
            aStream->write(matrix[0][0], 16, scaleBits);
            aStream->write(matrix[1][1], 16, scaleBits);
        }
    
        aStream->write(containsRotation() ? 1 : 0, FSStream::UnsignedBit, 1);
    
        if (containsRotation())
        {
            int rotateBits = rotateFieldSize();
            
            aStream->write(rotateBits, FSStream::UnsignedBit, 5);
            aStream->write(matrix[1][0], 16, rotateBits);
            aStream->write(matrix[0][1], 16, rotateBits);
        }
        aStream->write(translateBits, FSStream::UnsignedBit, 5);
        aStream->write((int)matrix[0][2], FSStream::SignedBit, translateBits);
        aStream->write((int)matrix[1][2], FSStream::SignedBit, translateBits);
    
        aStream->flush();

#ifdef _DEBUG
        aStream->endEncoding(className());
#endif
    }
    
    void FSCoordTransform::decodeFromStream(FSInputStream* aStream)
    {
        int scaleFieldSize = 0;
        int rotateFieldSize = 0;
        int translateFieldSize = 0;
    
#ifdef _DEBUG
        aStream->startDecoding(className());
#endif
        aStream->flush();

        bool _containsScaling = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
            
        if (_containsScaling)
        {
            scaleFieldSize = aStream->read(FSStream::UnsignedBit, 5);
            matrix[0][0] = aStream->read(FSStream::FixedInt, scaleFieldSize);
            matrix[1][1] = aStream->read(FSStream::FixedInt, scaleFieldSize);
        }
        else
        {
            aStream->read(FSStream::UnsignedBit, 0);
            aStream->read(FSStream::FixedInt, 0);
            aStream->read(FSStream::FixedInt, 0);
        }
    
        bool _containsRotation = aStream->read(FSStream::UnsignedBit, 1) != 0 ? true : false;
        
        if (_containsRotation)
        {
            rotateFieldSize = aStream->read(FSStream::UnsignedBit, 5);
            matrix[1][0] = aStream->read(FSStream::FixedInt, rotateFieldSize);
            matrix[0][1] = aStream->read(FSStream::FixedInt, rotateFieldSize);
        }
        else
        {
            aStream->read(FSStream::UnsignedBit, 0);
            aStream->read(FSStream::FixedInt, 0);
            aStream->read(FSStream::FixedInt, 0);
        }
    
        translateFieldSize = aStream->read(FSStream::UnsignedBit, 5);
        matrix[0][2] = (float)aStream->read(FSStream::SignedBit, translateFieldSize);
        matrix[1][2] = (float)aStream->read(FSStream::SignedBit, translateFieldSize);
        
        aStream->flush();

#ifdef _DEBUG
        aStream->endDecoding(className());
#endif
    }

    bool FSCoordTransform::isUnityTransform() const
    {
        bool isUnity = true;

        for(int i=0; i<3; i++)
            for (int j = 0; j<3; j++)
                isUnity = isUnity && matrix[i][j] == ((i == j) ? 1.0f : 0.0f);

        return isUnity;
    }

    bool FSCoordTransform::containsScaling() const
    { 
        return matrix[0][0] != 1.0f || matrix[1][1] != 1.0f;
    }
     
    bool FSCoordTransform::containsRotation()  const
    {
        return matrix[1][0] != 0.0f || matrix[0][1] != 0.0f;
    } 

    int FSCoordTransform::scaleFieldSize() const
    {
        float values[2] = { matrix[0][0], matrix[1][1] };
        
        return FSStream::FieldSize(values, 2, FSStream::FixedInt);
    }

    int FSCoordTransform::rotateFieldSize() const
    {
        float values[2] = { matrix[1][0], matrix[0][1] };

        return FSStream::FieldSize(values, 2, FSStream::FixedInt);
    }

    int FSCoordTransform::translateFieldSize() const
    {
        int values[2] = { (int)matrix[0][2], (int)matrix[1][2] };
        
        return FSStream::FieldSize(values, 2, true);
    }

    void FSCoordTransform::composite(float m[3][3])
    {
        matrix[0][0] = matrix[0][0] * m[0][0] + matrix[0][1] * m[1][0] + matrix[0][2] * m[2][0];
        matrix[0][1] = matrix[0][0] * m[0][1] + matrix[0][1] * m[1][1] + matrix[0][2] * m[2][1];
        matrix[0][2] = matrix[0][0] * m[0][2] + matrix[0][1] * m[1][2] + matrix[0][2] * m[2][2];

        matrix[1][0] = matrix[1][0] * m[0][0] + matrix[1][1] * m[1][0] + matrix[1][2] * m[2][0];
        matrix[1][1] = matrix[1][0] * m[0][1] + matrix[1][1] * m[1][1] + matrix[1][2] * m[2][1];
        matrix[1][2] = matrix[1][0] * m[0][2] + matrix[1][1] * m[1][2] + matrix[1][2] * m[2][2];

        matrix[2][0] = matrix[2][0] * m[0][0] + matrix[2][1] * m[1][0] + matrix[2][2] * m[2][0];
        matrix[2][1] = matrix[2][0] * m[0][1] + matrix[2][1] * m[1][1] + matrix[2][2] * m[2][1];
        matrix[2][2] = matrix[2][0] * m[0][2] + matrix[2][1] * m[1][2] + matrix[2][2] * m[2][2];
    }
}