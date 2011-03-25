/*
 *  FSTabOrder.h
 *  Transform SWF
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

#ifndef __FSTabOrder_h__
#define __FSTabOrder_h__ 1

#include "FSMovieObject.h"

namespace transform
{
/**
 * The %FSTabOrder class is used to set the tabbing order of text fields, movie clips and 
 * buttons visible on the display list.
 * 
<table class="datasheet">

<tr><th align="left" colspan="2">Attributes</th></tr>

<tr>
<td><a name="FSDefineVideo_0">type</a></td>
<td>Identifies the data structure when it is encoded. Read-only.</td>
</tr>

<tr>
<td><a name="FSDefineVideo_1">layer</a></td>
<td>The layer number which contains the object assigned to the tabbing order.</td>
</tr>

<tr>
<td><a name="FSDefineVideo_2">index</a></td>
<td>The index of the object in the tabbing order.</td>
</tr>

</table>

<h1 class="datasheet">History</h1>

<p>The FSTabOrder object represents the SetTabIndex tag in the Flash file specification . It was introduced in Flash 7.</p>

 */  
    class DLL_DECL FSTabOrder : public FSMovieObject
    {
public:
        FSTabOrder(FSInputStream* aStream);

		/**
		 * Construct a FSTabOrder object that set the tab order for the object on the display list
		 * at the specified layer.
		 *
		 * @param aLayer the layer number which contains the object assigned to the tabbing order.
		 * @param anIndex the index of the object in the tabbing order.
		 */
        FSTabOrder(int aLayer, int anIndex) : FSMovieObject(TabOrder), layer(aLayer), index(anIndex) {}

        FSTabOrder* clone() const { return new FSTabOrder(*this); }

        const char* className() const;

		/**
	 	 * Gets the layer number which contains the object assigned to the tabbing order.
		 *
		 * @return the layer number.
		 */
        int getLayer() const { return layer; }

		/**
		 * Gets the index of the object in the tabbing order.
		 *
		 * @return the index in the tabbing order.
		 */
        int getIndex() const { return index; }

		/**
		 * Sets the layer number which contains the object assigned to the tabbing order.
		 *
		 * @param aLayer the layer number.
		 */
		void setLayer(int aLayer) { layer = aLayer; }

		/**
		 * Sets the index of the object in the tabbing order.
		 *
		 * @param anIndex the index in the tabbing order.
		 */
        void setIndex(int anIndex) { index = anIndex; }

        int lengthInStream(FSOutputStream* aStream);
        void encodeToStream(FSOutputStream* aStream);
        void decodeFromStream(FSInputStream* aStream);
        
private:
	    int layer;
        int index;
    };
} 

#endif
