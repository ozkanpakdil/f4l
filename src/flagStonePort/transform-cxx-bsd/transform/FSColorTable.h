/*
 *  FSColorTable.h
 *  Transform SWF
 *
 *  Created by smackay on Tue Feb 18 2003.
 *  Copyright (c) 2002 Flagstone Software Ltd. All rights reserved.
 *
 *  This file is part of the Transform SWF library. You may not use this file except in
 *  compliance with the terms of the license (the 'License') that accompanied this file.
 *
 *  The Original Code and all software distributed under the License are distributed on an 
 *  'AS IS' basis, WITHOUT WARRANTY OF ANY KIND, EITHER EXPRESS OR IMPLIED, AND Flagstone 
 *  HEREBY DISCLAIMS ALL SUCH WARRANTIES, INCLUDING WITHOUT LIMITATION, ANY WARRANTIES OF 
 *  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND NONINFRINGEMENT OF THIRD PARTY 
 *  RIGHTS. Please see the License for the specific language governing rights and limitations 
 *  under the License.
 */

#ifndef __FSColorTable_h__
#define __FSColorTable_h__ 1

#include "FSColor.h"

namespace transform
{
/** 
 * The %FSColorTable class contains a set of factory methods to generate %FSColor objects 
 * for each of the colours defined in the Netscape Colour Table. 
 *
 * <div class="code">
 *		%FSColor aColor = %FSColorTable::%aliceblue();
 * </div>
 * 
 * <p>Each entry in the colour table returns and array of integers that define the values 
 * for the red, green and blue colour channels. To define a transparent colour for use 
 * with an object that support transparent colours such as the FSDefineShape3 class use 
 * the following code fragment:</p>
 * 
 * <div class="code">
 *		%FSColor aColor = %FSColorTable::%aliceblue(128);
 * </div>
 * 
 * <p>Transparent colours are created by specifying the level of transparency, in the range 
 * 0..255, where 0 is completely transparent and 255 is completely opaque.</P>

\htmlonly
<center>
<table BORDER="1" BGCOLOR="#FFFFFF" CELLPADDING="5" CELLSPACING="4" width="90%">
<TR>
<TD ALIGN="center" BGCOLOR="aliceblue" WIDTH="15%">aliceblue<BR>F0F8FF</TD>
<TD ALIGN="center" BGCOLOR="antiquewhite" WIDTH="15%">antiquewhite<BR>FAEBD7</TD>
<TD ALIGN="center" BGCOLOR="aqua" WIDTH="15%">aqua<BR>00FFFF</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="aquamarine" WIDTH="15%">aquamarine<BR>7FFFD4</TD>
<TD ALIGN="center" BGCOLOR="azure" WIDTH="15%">azure<BR>F0FFFF</TD>
<TD ALIGN="center" BGCOLOR="beige" WIDTH="15%">beige<BR>F5F5DC</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="bisque" WIDTH="15%">bisque<BR>FFE4C4</TD>
<TD ALIGN="center" BGCOLOR="burlywood" WIDTH="15%">burlywood<BR>DEB887</TD>
<TD ALIGN="center" BGCOLOR="blanchedalmond" WIDTH="15%">blanchedalmond<BR>FFEBCD</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="blue" WIDTH="15%">blue<BR>0000FF</TD>
<TD ALIGN="center" BGCOLOR="bluevoilet" WIDTH="15%">blueviolet<BR>8A2BE2</TD>
<TD ALIGN="center" BGCOLOR="brown" WIDTH="15%">brown<BR>A52A2A</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="black" WIDTH="15%"><FONT COLOR="FFFFFF">black<BR>000000</FONT></TD>
<TD ALIGN="center" BGCOLOR="cadetblue" WIDTH="15%">cadetblue<BR>5F9EA0</TD>
<TD ALIGN="center" BGCOLOR="chartreuse" WIDTH="15%">chartreuse<BR>7FFF00</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="chocolate" WIDTH="15%">chocolate<BR>D2691E</TD>
<TD ALIGN="center" BGCOLOR="coral" WIDTH="15%">coral<BR>FF7F50</TD>
<TD ALIGN="center" BGCOLOR="cornflowerblue" WIDTH="15%">cornflowerblue<BR>6495ED</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="cornsilk" WIDTH="15%">cornsilk<BR>FFF8DC</TD>
<TD ALIGN="center" BGCOLOR="crimson" WIDTH="15%">crimson<BR>DC143C</TD>
<TD ALIGN="center" BGCOLOR="cyan" WIDTH="15%">cyan<BR>00FFFF</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="darkblue" WIDTH="15%">darkblue<BR>00008B</TD>
<TD ALIGN="center" BGCOLOR="darkcyan" WIDTH="15%">darkcyan<BR>008B8B</TD>
<TD ALIGN="center" BGCOLOR="darkgoldenrod" WIDTH="15%">darkgoldenrod<BR>B8860B</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="darkgray" WIDTH="15%">darkgray<BR>A9A9A9</TD>
<TD ALIGN="center" BGCOLOR="darkgreen" WIDTH="15%">darkgreen<BR>006400</TD>
<TD ALIGN="center" BGCOLOR="darkkhaki" WIDTH="15%">darkkhaki<BR>BDB76B</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="darkmagenta" WIDTH="15%">darkmagenta<BR>8B008B</TD>
<TD ALIGN="center" BGCOLOR="darkolivegreen" WIDTH="15%">darkolivegreen<BR>556B2F</TD>
<TD ALIGN="center" BGCOLOR="darkorange" WIDTH="15%">darkorange<BR>FF8C00</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="darkorchid" WIDTH="15%">darkorchid<BR>9932CC</TD>
<TD ALIGN="center" BGCOLOR="darkred" WIDTH="15%">darkred<BR>8B0000</TD>
<TD ALIGN="center" BGCOLOR="darksalmon" WIDTH="15%">darksalmon<BR>E9967A</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="darkseagreen" WIDTH="15%">darkseagreen<BR>8FBC8F</TD>
<TD ALIGN="center" BGCOLOR="darkslateblue" WIDTH="15%">darkslateblue<BR>483D8B</TD>
<TD ALIGN="center" BGCOLOR="darkslategray" WIDTH="15%">darkslategray<BR>2F4F4F</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="darkturquoise" WIDTH="15%">darkturquoise<BR>00CED1</TD>
<TD ALIGN="center" BGCOLOR="darkviolet" WIDTH="15%">darkviolet<BR>9400D3</TD>
<TD ALIGN="center" BGCOLOR="deeppink" WIDTH="15%">deeppink<BR>FF1493</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="deepskyblue" WIDTH="15%">deepskyblue<BR>00BFFF</TD>
<TD ALIGN="center" BGCOLOR="dimgray" WIDTH="15%">dimgray<BR>696969</TD>
<TD ALIGN="center" BGCOLOR="dodgerblue" WIDTH="15%">dodgerblue<BR>1E90FF</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="firebrick" WIDTH="15%">firebrick<BR>B22222</TD>
<TD ALIGN="center" BGCOLOR="floralwhite" WIDTH="15%">floralwhite<BR>FFFAF0</TD>
<TD ALIGN="center" BGCOLOR="forestgreen" WIDTH="15%">forestgreen<BR>228B22</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="fuchsia" WIDTH="15%">fuchsia<BR>FF00FF</TD>
<TD ALIGN="center" BGCOLOR="gainsboro" WIDTH="15%">gainsboro<BR>DCDCDC</TD>
<TD ALIGN="center" BGCOLOR="ghostwhite" WIDTH="15%">ghostwhite<BR>F8F8FF</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="gold" WIDTH="15%">gold<BR>FFD700</TD>
<TD ALIGN="center" BGCOLOR="goldenrod" WIDTH="15%">goldenrod<BR>DAA520</TD>
<TD ALIGN="center" BGCOLOR="gray" WIDTH="15%">gray<BR>808080</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="green" WIDTH="15%">green<BR>008000</TD>
<TD ALIGN="center" BGCOLOR="greenyellow" WIDTH="15%">greenyellow<BR>ADFF2F</TD>
<TD ALIGN="center" BGCOLOR="honeydew" WIDTH="15%">honeydew<BR>F0FFF0</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="hotpink" WIDTH="15%">hotpink<BR>FF69B4</TD>
<TD ALIGN="center" BGCOLOR="indianred" WIDTH="15%">indianred<BR>CD5C5C</TD>
<TD ALIGN="center" BGCOLOR="indigo" WIDTH="15%">Indigo<BR>4B0082</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="ivory" WIDTH="15%">ivory<BR>FFFFF0</TD>
<TD ALIGN="center" BGCOLOR="khaki" WIDTH="15%">khaki<BR>F0E68C</TD>
<TD ALIGN="center" BGCOLOR="lavender" WIDTH="15%">lavender<BR>E6E6FA</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="lavenderblush" WIDTH="15%">lavenderblush<BR>FFF0F5</TD>
<TD ALIGN="center" BGCOLOR="lawngreen" WIDTH="15%">lawngreen<BR>7CFC00</TD>
<TD ALIGN="center" BGCOLOR="lemonchiffon" WIDTH="15%">lemonchiffon<BR>FFFACD</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="lightblue" WIDTH="15%">lightblue<BR>ADD8E6</TD>
<TD ALIGN="center" BGCOLOR="lightcoral" WIDTH="15%">lightcoral<BR>F08080</TD>
<TD ALIGN="center" BGCOLOR="lightcyan" WIDTH="15%">lightcyan<BR>E0FFFF</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="lightgoldenrodyellow" WIDTH="15%">lightgoldenrodyellow<BR>FAFAD2</TD>
<TD ALIGN="center" BGCOLOR="lightgreen" WIDTH="15%">lightgreen<BR>90EE90</TD>
<TD ALIGN="center" BGCOLOR="lightgrey" WIDTH="15%">lightgrey<BR>D3D3D3</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="lightpink" WIDTH="15%">lightpink<BR>FFB6C1</TD>
<TD ALIGN="center" BGCOLOR="lightsalmon" WIDTH="15%">lightsalmon<BR>FFA07A</TD>
<TD ALIGN="center" BGCOLOR="lightseagreen" WIDTH="15%">lightseagreen<BR>20B2AA</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="lightskyblue" WIDTH="15%">lightskyblue<BR>87CEFA</TD>
<TD ALIGN="center" BGCOLOR="lightslategray" WIDTH="15%">lightslategray<BR>778899</TD>
<TD ALIGN="center" BGCOLOR="lightsteelblue" WIDTH="15%">lightsteelblue<BR>B0C4DE</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="lightyellow" WIDTH="15%">lightyellow<BR>FFFFE0</TD>
<TD ALIGN="center" BGCOLOR="lime" WIDTH="15%">lime<BR>00FF00</TD>
<TD ALIGN="center" BGCOLOR="limegreen" WIDTH="15%">limegreen<BR>32CD32</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="linen" WIDTH="15%"><font COLOR="#000000">linen<BR>FAF0E6</TD>
<TD ALIGN="center" BGCOLOR="magenta" WIDTH="15%">magenta<BR>FF00FF</TD>
<TD ALIGN="center" BGCOLOR="maroon" WIDTH="15%">maroon<BR>800000</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="mediumaquamarine" WIDTH="15%">mediumauqamarine<BR>66CDAA</TD>
<TD ALIGN="center" BGCOLOR="mediumblue" WIDTH="15%">mediumblue<BR>0000CD</TD>
<TD ALIGN="center" BGCOLOR="mediumorchid" WIDTH="15%">mediumorchid<BR>BA55D3</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="mediumpurple" WIDTH="15%">mediumpurple<BR>9370D8</TD>
<TD ALIGN="center" BGCOLOR="mediumseagreen" WIDTH="15%">mediumseagreen<BR>3CB371</TD>
<TD ALIGN="center" BGCOLOR="mediumslateblue" WIDTH="15%">mediumslateblue<BR>7B68EE</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="mediumspringgreen" WIDTH="15%">mediumspringgreen<BR>00FA9A</TD>
<TD ALIGN="center" BGCOLOR="mediumturquoise" WIDTH="15%">mediumturquoise<BR>48D1CC</TD>
<TD ALIGN="center" BGCOLOR="mediumvioletred" WIDTH="15%">mediumvioletred<BR>C71585</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="midnightblue" WIDTH="15%">midnightblue<BR>191970</TD>
<TD ALIGN="center" BGCOLOR="mintcream" WIDTH="15%">mintcream<BR>F5FFFA</TD>
<TD ALIGN="center" BGCOLOR="mistyrose" WIDTH="15%">mistyrose<BR>FFE4E1</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="moccasin" WIDTH="15%">moccasin<BR>FFE4B5</TD>
<TD ALIGN="center" BGCOLOR="navajowhite" WIDTH="15%">navajowhite<BR>FFDEAD</TD>
<TD ALIGN="center" BGCOLOR="navy" WIDTH="15%">navy<BR>000080</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="oldlace" WIDTH="15%">oldlace<BR>FDF5E6</TD>
<TD ALIGN="center" BGCOLOR="olive" WIDTH="15%">olive<BR>808000</TD>
<TD ALIGN="center" BGCOLOR="olivedrab" WIDTH="15%">olivedrab<BR>688E23</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="orange" WIDTH="15%">orange<BR>FFA500</TD>
<TD ALIGN="center" BGCOLOR="orangered" WIDTH="15%">orangered<BR>FF4500</TD>
<TD ALIGN="center" BGCOLOR="orchid" WIDTH="15%">orchid<BR>DA70D6</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="palegoldenrod" WIDTH="15%">palegoldenrod<BR>EEE8AA</TD>
<TD ALIGN="center" BGCOLOR="palegreen" WIDTH="15%">palegreen<BR>98FB98</TD>
<TD ALIGN="center" BGCOLOR="paleturquoise" WIDTH="15%">paleturquoise<BR>AFEEEE</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="palevioletred" WIDTH="15%">palevioletred<BR>D87093</TD>
<TD ALIGN="center" BGCOLOR="papayawhip" WIDTH="15%">papayawhip<BR>FFEFD5</TD>
<TD ALIGN="center" BGCOLOR="peachpuff" WIDTH="15%">peachpuff<BR>FFDAB9</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="peru" WIDTH="15%">peru<BR>CD853F</TD>
<TD ALIGN="center" BGCOLOR="pink" WIDTH="15%">pink<BR>FFC0CB</TD>
<TD ALIGN="center" BGCOLOR="plum" WIDTH="15%">plum<BR>DDA0DD</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="powderblue" WIDTH="15%">powderblue<BR>B0E0E6</TD>
<TD ALIGN="center" BGCOLOR="purple" WIDTH="15%">purple<BR>800080</TD>
<TD ALIGN="center" BGCOLOR="red" WIDTH="15%">red<BR>FF0000</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="rosybrown" WIDTH="15%">rosybrown<BR>BC8F8F</TD>
<TD ALIGN="center" BGCOLOR="royalblue" WIDTH="15%">royalblue<BR>4169E1</TD>
<TD ALIGN="center" BGCOLOR="saddlebrown" WIDTH="15%">saddlebrown<BR>8B4513</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="salmon" WIDTH="15%">salmon<BR>FA8072</TD>
<TD ALIGN="center" BGCOLOR="sandybrown" WIDTH="15%">sandybrown<BR>F4A460</TD>
<TD ALIGN="center" BGCOLOR="seagreen" WIDTH="15%">seagreen<BR>2E8B57</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="seashell" WIDTH="15%">seashell<BR>FFF5EE</TD>
<TD ALIGN="center" BGCOLOR="sienna" WIDTH="15%">sienna<BR>A0522D</TD>
<TD ALIGN="center" BGCOLOR="silver" WIDTH="15%">silver<BR>C0C0C0</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="skyblue" WIDTH="15%">skyblue<BR>87CEEB</TD>
<TD ALIGN="center" BGCOLOR="slateblue" WIDTH="15%">slateblue<BR>6A5ACD</TD>
<TD ALIGN="center" BGCOLOR="slategray" WIDTH="15%">slategray<BR>708090</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="snow" WIDTH="15%">snow<BR>FFFAFA</TD>
<TD ALIGN="center" BGCOLOR="springgreen" WIDTH="15%">springgreen<BR>00FF7F</TD>
<TD ALIGN="center" BGCOLOR="steelblue" WIDTH="15%">steelblue<BR>4682B4</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="tan" WIDTH="15%">tan<BR>D2B48C</TD>
<TD ALIGN="center" BGCOLOR="teal" WIDTH="15%">teal<BR>008080</TD>
<TD ALIGN="center" BGCOLOR="thistle" WIDTH="15%">thistle<BR>D8BFD8</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="tomato" WIDTH="15%">tomato<BR>FF6347</TD>
<TD ALIGN="center" BGCOLOR="turquoise" WIDTH="15%">turquoise<BR>40E0D0</TD>
<TD ALIGN="center" BGCOLOR="violet" WIDTH="15%">violet<BR>EE82EE</TD>
</TR>
<TR>
<TD ALIGN="center" BGCOLOR="wheat" WIDTH="15%">wheat<BR>F5DEB3<BR></TD>
<TD ALIGN="center" BGCOLOR="white" WIDTH="15%">white<BR>FFFFFF</TD>
<TD ALIGN="center" BGCOLOR="whitesmoke" WIDTH="15%">whitesmoke<BR>F5F5F5</TD>
</TR>
</table>
</center>
\endhtmlonly

*/
    class DLL_DECL FSColorTable 
    {
public:
		/** Definition of the color, aliceblue from the Netscape color table. */
		static FSColor aliceblue(int alpha=255) { return FSColor(0xF0, 0xF8, 0xFF, alpha); }
		/** Definition of the color, antiquewhite from the Netscape color table. */
		static FSColor antiquewhite(int alpha=255) { return FSColor(0xFA, 0xEB, 0xD7, alpha); }
		/** Definition of the color, aqua from the Netscape color table. */
		static FSColor aqua(int alpha=255) { return FSColor(0x00, 0xFF, 0xFF, alpha); }
		/** Definition of the color, aquamarine from the Netscape color table. */
		static FSColor aquamarine(int alpha=255) { return FSColor(0x7F, 0xFF, 0xD4, alpha); }
		/** Definition of the color, azure from the Netscape color table. */
		static FSColor azure(int alpha=255) { return FSColor(0xF0, 0xFF, 0xFF, alpha); }
		/** Definition of the color, beige from the Netscape color table. */
		static FSColor beige(int alpha=255) { return FSColor(0xF5, 0xF5, 0xDC, alpha); }
		/** Definition of the color, bisque from the Netscape color table. */
		static FSColor bisque(int alpha=255) { return FSColor(0xFF, 0xE4, 0xC4, alpha); }
		/** Definition of the color, black from the Netscape color table. */
		static FSColor black(int alpha=255) { return FSColor(0x00, 0x00, 0x00, alpha); }
		/** Definition of the color, blanchedalmond from the Netscape color table. */
		static FSColor blanchedalmond(int alpha=255) { return FSColor(0xFF, 0xEB, 0xCD, alpha); }
		/** Definition of the color, blue from the Netscape color table. */
		static FSColor blue(int alpha=255) { return FSColor(0x00, 0x00, 0xFF, alpha); }
		/** Definition of the color, blueviolet from the Netscape color table. */
		static FSColor blueviolet(int alpha=255) { return FSColor(0x8A, 0x2B, 0xE2, alpha); }
		/** Definition of the color, brown from the Netscape color table. */
		static FSColor brown(int alpha=255) { return FSColor(0xA5, 0x2A, 0x2A, alpha); }
		/** Definition of the color, burlywood from the Netscape color table. */
		static FSColor burlywood(int alpha=255) { return FSColor(0xDE, 0xB8, 0x87, alpha); }
		/** Definition of the color, cadetblue from the Netscape color table. */
		static FSColor cadetblue(int alpha=255) { return FSColor(0x5F, 0x9E, 0xA0, alpha); }
		/** Definition of the color, chartreuse from the Netscape color table. */
		static FSColor chartreuse(int alpha=255) { return FSColor(0x7F, 0xFF, 0x00, alpha); }
		/** Definition of the color, chocolate from the Netscape color table. */
		static FSColor chocolate(int alpha=255) { return FSColor(0xD2, 0x69, 0x1E, alpha); }
		/** Definition of the color, coral from the Netscape color table. */
		static FSColor coral(int alpha=255) { return FSColor(0xFF, 0x7F, 0x50, alpha); }
		/** Definition of the color, cornflowerblue from the Netscape color table. */
		static FSColor cornflowerblue(int alpha=255) { return FSColor(0x64, 0x95, 0xED, alpha); }
		/** Definition of the color, cornsilk from the Netscape color table. */
		static FSColor cornsilk(int alpha=255) { return FSColor(0xFF, 0xF8, 0xDC, alpha); }
		/** Definition of the color, crimson from the Netscape color table. */
		static FSColor crimson(int alpha=255) { return FSColor(0xDC, 0x14, 0x3C, alpha); }
		/** Definition of the color, cyan from the Netscape color table. */
		static FSColor cyan(int alpha=255) { return FSColor(0x00, 0xFF, 0xFF, alpha); }
		/** Definition of the color, darkblue from the Netscape color table. */
		static FSColor darkblue(int alpha=255) { return FSColor(0x00, 0x00, 0x8B, alpha); }
		/** Definition of the color, darkcyan from the Netscape color table. */
		static FSColor darkcyan(int alpha=255) { return FSColor(0x00, 0x8B, 0x8B, alpha); }
		/** Definition of the color, darkgoldenrod from the Netscape color table. */
		static FSColor darkgoldenrod(int alpha=255) { return FSColor(0xB8, 0x86, 0x0B, alpha); }
		/** Definition of the color, darkgray from the Netscape color table. */
		static FSColor darkgray(int alpha=255) { return FSColor(0xA9, 0xA9, 0xA9, alpha); }
		/** Definition of the color, darkgreen from the Netscape color table. */
		static FSColor darkgreen(int alpha=255) { return FSColor(0x00, 0x64, 0x00, alpha); }
		/** Definition of the color, darkkhaki from the Netscape color table. */
		static FSColor darkkhaki(int alpha=255) { return FSColor(0xBD, 0xB7, 0x6B, alpha); }
		/** Definition of the color, darkmagenta from the Netscape color table. */
		static FSColor darkmagenta(int alpha=255) { return FSColor(0x8B, 0x00, 0x8B, alpha); }
		/** Definition of the color, darkolivegreen from the Netscape color table. */
		static FSColor darkolivegreen(int alpha=255) { return FSColor(0x55, 0x6B, 0x2F, alpha); }
		/** Definition of the color, darkorange from the Netscape color table. */
		static FSColor darkorange(int alpha=255) { return FSColor(0xFF, 0x8C, 0x00, alpha); }
		/** Definition of the color, darkorchid from the Netscape color table. */
		static FSColor darkorchid(int alpha=255) { return FSColor(0x99, 0x32, 0xCC, alpha); }
		/** Definition of the color, darkred from the Netscape color table. */
		static FSColor darkred(int alpha=255) { return FSColor(0x8B, 0x00, 0x00, alpha); }
		/** Definition of the color, darksalmon from the Netscape color table. */
		static FSColor darksalmon(int alpha=255) { return FSColor(0xE9, 0x96, 0x7A, alpha); }
		/** Definition of the color, darkseagreen from the Netscape color table. */
		static FSColor darkseagreen(int alpha=255) { return FSColor(0x8F, 0xBC, 0x8F, alpha); }
		/** Definition of the color, darkslateblue from the Netscape color table. */
		static FSColor darkslateblue(int alpha=255) { return FSColor(0x48, 0x3D, 0x8B, alpha); }
		/** Definition of the color, darkslategray from the Netscape color table. */
		static FSColor darkslategray(int alpha=255) { return FSColor(0x2F, 0x4F, 0x4F, alpha); }
		/** Definition of the color, darkturquoise from the Netscape color table. */
		static FSColor darkturquoise(int alpha=255) { return FSColor(0x00, 0xCE, 0xD1, alpha); }
		/** Definition of the color, darkviolet from the Netscape color table. */
		static FSColor darkviolet(int alpha=255) { return FSColor(0x94, 0x00, 0xD3, alpha); }
		/** Definition of the color, deeppink from the Netscape color table. */
		static FSColor deeppink(int alpha=255) { return FSColor(0xFF, 0x14, 0x93, alpha); }
		/** Definition of the color, deepskyblue from the Netscape color table. */
		static FSColor deepskyblue(int alpha=255) { return FSColor(0x00, 0xBF, 0xFF, alpha); }
		/** Definition of the color, dimgray from the Netscape color table. */
		static FSColor dimgray(int alpha=255) { return FSColor(0x69, 0x69, 0x69, alpha); }
		/** Definition of the color, dodgerblue from the Netscape color table. */
		static FSColor dodgerblue(int alpha=255) { return FSColor(0x1E, 0x90, 0xFF, alpha); }
		/** Definition of the color, firebrick from the Netscape color table. */
		static FSColor firebrick(int alpha=255) { return FSColor(0xB2, 0x22, 0x22, alpha); }
		/** Definition of the color, floralwhite from the Netscape color table. */
		static FSColor floralwhite(int alpha=255) { return FSColor(0xFF, 0xFA, 0xF0, alpha); }
		/** Definition of the color, forestgreen from the Netscape color table. */
		static FSColor forestgreen(int alpha=255) { return FSColor(0x22, 0x8B, 0x22, alpha); }
		/** Definition of the color, fuchsia from the Netscape color table. */
		static FSColor fuchsia(int alpha=255) { return FSColor(0xFF, 0x00, 0xFF, alpha); }
		/** Definition of the color, gainsboro from the Netscape color table. */
		static FSColor gainsboro(int alpha=255) { return FSColor(0xDC, 0xDC, 0xDC, alpha); }
		/** Definition of the color, ghostwhite from the Netscape color table. */
		static FSColor ghostwhite(int alpha=255) { return FSColor(0xF8, 0xF8, 0xFB, alpha); }
		/** Definition of the color, gold from the Netscape color table. */
		static FSColor gold(int alpha=255) { return FSColor(0xFF, 0xD7, 0x00, alpha); }
		/** Definition of the color, goldenrod from the Netscape color table. */
		static FSColor goldenrod(int alpha=255) { return FSColor(0xDA, 0xA5, 0x20, alpha); }
		/** Definition of the color, gray from the Netscape color table. */
		static FSColor gray(int alpha=255) { return FSColor(0x80, 0x80, 0x80, alpha); }
		/** Definition of the color, green from the Netscape color table. */
		static FSColor green(int alpha=255) { return FSColor(0x00, 0x80, 0x00, alpha); }
		/** Definition of the color, greenyellow from the Netscape color table. */
		static FSColor greenyellow(int alpha=255) { return FSColor(0xAD, 0xFF, 0x2F, alpha); }
		/** Definition of the color, honeydew from the Netscape color table. */
		static FSColor honeydew(int alpha=255) { return FSColor(0xF0, 0xFF, 0xF0, alpha); }
		/** Definition of the color, hotpink from the Netscape color table. */
		static FSColor hotpink(int alpha=255) { return FSColor(0xFF, 0x69, 0xB4, alpha); }
		/** Definition of the color, indianred from the Netscape color table. */
		static FSColor indianred(int alpha=255) { return FSColor(0xCD, 0x5C, 0x5C, alpha); }
		/** Definition of the color, indigo from the Netscape color table. */
		static FSColor indigo(int alpha=255) { return FSColor(0x4B, 0x00, 0x82, alpha); }
		/** Definition of the color, ivory from the Netscape color table. */
		static FSColor ivory(int alpha=255) { return FSColor(0xFF, 0xFF, 0xF0, alpha); }
		/** Definition of the color, khaki from the Netscape color table. */
		static FSColor khaki(int alpha=255) { return FSColor(0xF0, 0xE6, 0x8C, alpha); }
		/** Definition of the color, lavender from the Netscape color table. */
		static FSColor lavender(int alpha=255) { return FSColor(0xE6, 0xE6, 0xFA, alpha); }
		/** Definition of the color, lavenderblush from the Netscape color table. */
		static FSColor lavenderblush(int alpha=255) { return FSColor(0xFF, 0xF0, 0xF5, alpha); }
		/** Definition of the color, lawngreen from the Netscape color table. */
		static FSColor lawngreen(int alpha=255) { return FSColor(0x7C, 0xFC, 0x00, alpha); }
		/** Definition of the color, lemonchiffon from the Netscape color table. */
		static FSColor lemonchiffon(int alpha=255) { return FSColor(0xFF, 0xFA, 0xCD, alpha); }
		/** Definition of the color, lightblue from the Netscape color table. */
		static FSColor lightblue(int alpha=255) { return FSColor(0xAD, 0xD8, 0xE6, alpha); }
		/** Definition of the color, lightcoral from the Netscape color table. */
		static FSColor lightcoral(int alpha=255) { return FSColor(0xF0, 0x80, 0x80, alpha); }
		/** Definition of the color, lightcyan from the Netscape color table. */
		static FSColor lightcyan(int alpha=255) { return FSColor(0xE0, 0xFF, 0xFF, alpha); }
		/** Definition of the color, lightgoldenrodyellow from the Netscape color table. */
		static FSColor lightgoldenrodyellow(int alpha=255) { return FSColor(0xFA, 0xFA, 0xD2, alpha); }
		/** Definition of the color, lightgreen from the Netscape color table. */
		static FSColor lightgreen(int alpha=255) { return FSColor(0x90, 0xEE, 0x90, alpha); }
		/** Definition of the color, lightgrey from the Netscape color table. */
		static FSColor lightgrey(int alpha=255) { return FSColor(0xD3, 0xD3, 0xD3, alpha); }
		/** Definition of the color, lightpink from the Netscape color table. */
		static FSColor lightpink(int alpha=255) { return FSColor(0xFF, 0xB6, 0xC1, alpha); }
		/** Definition of the color, lightsalmon from the Netscape color table. */
		static FSColor lightsalmon(int alpha=255) { return FSColor(0xFF, 0xA0, 0x7A, alpha); }
		/** Definition of the color, lightseagreen from the Netscape color table. */
		static FSColor lightseagreen(int alpha=255) { return FSColor(0x20, 0xB2, 0xAA, alpha); }
		/** Definition of the color, lightskyblue from the Netscape color table. */
		static FSColor lightskyblue(int alpha=255) { return FSColor(0x87, 0xCE, 0xFA, alpha); }
		/** Definition of the color, lightslategray from the Netscape color table. */
		static FSColor lightslategray(int alpha=255) { return FSColor(0x77, 0x88, 0x99, alpha); }
		/** Definition of the color, lightsteelblue from the Netscape color table. */
		static FSColor lightsteelblue(int alpha=255) { return FSColor(0xB0, 0xC4, 0xDE, alpha); }
		/** Definition of the color, lightyellow from the Netscape color table. */
		static FSColor lightyellow(int alpha=255) { return FSColor(0xFF, 0xFF, 0xE0, alpha); }
		/** Definition of the color, lime from the Netscape color table. */
		static FSColor lime(int alpha=255) { return FSColor(0x00, 0xFF, 0x00, alpha); }
		/** Definition of the color, limegreen from the Netscape color table. */
		static FSColor limegreen(int alpha=255) { return FSColor(0x32, 0xCD, 0x32, alpha); }
		/** Definition of the color, linen from the Netscape color table. */
		static FSColor linen(int alpha=255) { return FSColor(0xFA, 0xF0, 0xE6, alpha); }
		/** Definition of the color, magenta from the Netscape color table. */
		static FSColor magenta(int alpha=255) { return FSColor(0xFF, 0x00, 0xFF, alpha); }
		/** Definition of the color, maroon from the Netscape color table. */
		static FSColor maroon(int alpha=255) { return FSColor(0x80, 0x00, 0x00, alpha); }
		/** Definition of the color, mediumaquamarine from the Netscape color table. */
		static FSColor mediumaquamarine(int alpha=255) { return FSColor(0x66, 0xCD, 0xAA, alpha); }
		/** Definition of the color, mediumblue from the Netscape color table. */
		static FSColor mediumblue(int alpha=255) { return FSColor(0x00, 0x00, 0xCD, alpha); }
		/** Definition of the color, mediumorchid from the Netscape color table. */
		static FSColor mediumorchid(int alpha=255) { return FSColor(0xBA, 0x55, 0xD3, alpha); }
		/** Definition of the color, mediumpurple from the Netscape color table. */
		static FSColor mediumpurple(int alpha=255) { return FSColor(0x93, 0x70, 0xDB, alpha); }
		/** Definition of the color, mediumseagreen from the Netscape color table. */
		static FSColor mediumseagreen(int alpha=255) { return FSColor(0x3C, 0xB3, 0x71, alpha); }
		/** Definition of the color, mediumslateblue from the Netscape color table. */
		static FSColor mediumslateblue(int alpha=255) { return FSColor(0x7B, 0x68, 0xEE, alpha); }
		/** Definition of the color, mediumspringgreen from the Netscape color table. */
		static FSColor mediumspringgreen(int alpha=255) { return FSColor(0x00, 0xFA, 0x9A, alpha); }
		/** Definition of the color, mediumturquoise from the Netscape color table. */
		static FSColor mediumturquoise(int alpha=255) { return FSColor(0x48, 0xD1, 0xCC, alpha); }
		/** Definition of the color, mediumvioletred from the Netscape color table. */
		static FSColor mediumvioletred(int alpha=255) { return FSColor(0xC7, 0x15, 0x85, alpha); }
		/** Definition of the color, midnightblue from the Netscape color table. */
		static FSColor midnightblue(int alpha=255) { return FSColor(0x19, 0x19, 0x70, alpha); }
		/** Definition of the color, mintcream from the Netscape color table. */
		static FSColor mintcream(int alpha=255) { return FSColor(0xF5, 0xFF, 0xFA, alpha); }
		/** Definition of the color, mistyrose from the Netscape color table. */
		static FSColor mistyrose(int alpha=255) { return FSColor(0xFF, 0xE4, 0xE1, alpha); }
		/** Definition of the color, moccasin from the Netscape color table. */
		static FSColor moccasin(int alpha=255) { return FSColor(0xFF, 0xE4, 0xB5, alpha); }
		/** Definition of the color, navajowhite from the Netscape color table. */
		static FSColor navajowhite(int alpha=255) { return FSColor(0xFF, 0xDE, 0xAD, alpha); }
		/** Definition of the color, navy from the Netscape color table. */
		static FSColor navy(int alpha=255) { return FSColor(0x00, 0x00, 0x80, alpha); }
		/** Definition of the color, oldlace from the Netscape color table. */
		static FSColor oldlace(int alpha=255) { return FSColor(0xFD, 0xF5, 0xE6, alpha); }
		/** Definition of the color, olive from the Netscape color table. */
		static FSColor olive(int alpha=255) { return FSColor(0x80, 0x80, 0x00, alpha); }
		/** Definition of the color, olivedrab from the Netscape color table. */
		static FSColor olivedrab(int alpha=255) { return FSColor(0x6B, 0x8E, 0x23, alpha); }
		/** Definition of the color, orange from the Netscape color table. */
		static FSColor orange(int alpha=255) { return FSColor(0xFF, 0xA5, 0x00, alpha); }
		/** Definition of the color, orangered from the Netscape color table. */
		static FSColor orangered(int alpha=255) { return FSColor(0xFF, 0x45, 0x00, alpha); }
		/** Definition of the color, orchid from the Netscape color table. */
		static FSColor orchid(int alpha=255) { return FSColor(0xDA, 0x70, 0xD6, alpha); }
		/** Definition of the color, palegoldenrod from the Netscape color table. */
		static FSColor palegoldenrod(int alpha=255) { return FSColor(0xEE, 0xE8, 0xAA, alpha); }
		/** Definition of the color, palegreen from the Netscape color table. */
		static FSColor palegreen(int alpha=255) { return FSColor(0x98, 0xFB, 0x98, alpha); }
		/** Definition of the color, paleturquoise from the Netscape color table. */
		static FSColor paleturquoise(int alpha=255) { return FSColor(0xAF, 0xEE, 0xEE, alpha); }
		/** Definition of the color, palevioletred from the Netscape color table. */
		static FSColor palevioletred(int alpha=255) { return FSColor(0xDB, 0x70, 0x93, alpha); }
		/** Definition of the color, papayawhip from the Netscape color table. */
		static FSColor papayawhip(int alpha=255) { return FSColor(0xFF, 0xEF, 0xD5, alpha); }
		/** Definition of the color, peachpuff from the Netscape color table. */
		static FSColor peachpuff(int alpha=255) { return FSColor(0xFF, 0xDA, 0xB9, alpha); }
		/** Definition of the color, peru from the Netscape color table. */
		static FSColor peru(int alpha=255) { return FSColor(0xCD, 0x85, 0x3F, alpha); }
		/** Definition of the color, pink from the Netscape color table. */
		static FSColor pink(int alpha=255) { return FSColor(0xFF, 0xC0, 0xCB, alpha); }
		/** Definition of the color, plum from the Netscape color table. */
		static FSColor plum(int alpha=255) { return FSColor(0xDD, 0xA0, 0xDD, alpha); }
		/** Definition of the color, powderblue from the Netscape color table. */
		static FSColor powderblue(int alpha=255) { return FSColor(0xB0, 0xE0, 0xE6, alpha); }
		/** Definition of the color, purple from the Netscape color table. */
		static FSColor purple(int alpha=255) { return FSColor(0x80, 0x00, 0x80, alpha); }
		/** Definition of the color, red from the Netscape color table. */
		static FSColor red(int alpha=255) { return FSColor(0xFF, 0x00, 0x00, alpha); }
		/** Definition of the color, rosybrown from the Netscape color table. */
		static FSColor rosybrown(int alpha=255) { return FSColor(0xBC, 0x8F, 0x8F, alpha); }
		/** Definition of the color, royalblue from the Netscape color table. */
		static FSColor royalblue(int alpha=255) { return FSColor(0x41, 0x69, 0xE1, alpha); }
		/** Definition of the color, saddlebrown from the Netscape color table. */
		static FSColor saddlebrown(int alpha=255) { return FSColor(0x8B, 0x45, 0x13, alpha); }
		/** Definition of the color, salmon from the Netscape color table. */
		static FSColor salmon(int alpha=255) { return FSColor(0xFA, 0x80, 0x72, alpha); }
		/** Definition of the color, sandybrown from the Netscape color table. */
		static FSColor sandybrown(int alpha=255) { return FSColor(0xF4, 0xA4, 0x60, alpha); }
		/** Definition of the color, seagreen from the Netscape color table. */
		static FSColor seagreen(int alpha=255) { return FSColor(0x2E, 0x8B, 0x57, alpha); }
		/** Definition of the color, seashell from the Netscape color table. */
		static FSColor seashell(int alpha=255) { return FSColor(0xFF, 0xF5, 0xEE, alpha); }
		/** Definition of the color, sienna from the Netscape color table. */
		static FSColor sienna(int alpha=255) { return FSColor(0xA0, 0x52, 0x2d, alpha); }
		/** Definition of the color, silver from the Netscape color table. */
		static FSColor silver(int alpha=255) { return FSColor(0xC0, 0xC0, 0xC0, alpha); }
		/** Definition of the color, skyblue from the Netscape color table. */
		static FSColor skyblue(int alpha=255) { return FSColor(0x87, 0xCE, 0xEB, alpha); }
		/** Definition of the color, slateblue from the Netscape color table. */
		static FSColor slateblue(int alpha=255) { return FSColor(0x6A, 0x5A, 0xCD, alpha); }
		/** Definition of the color, slategray from the Netscape color table. */
		static FSColor slategray(int alpha=255) { return FSColor(0x70, 0x80, 0x90, alpha); }
		/** Definition of the color, snow from the Netscape color table. */
		static FSColor snow(int alpha=255) { return FSColor(0xFF, 0xFA, 0xFA, alpha); }
		/** Definition of the color, springgreen from the Netscape color table. */
		static FSColor springgreen(int alpha=255) { return FSColor(0x00, 0xFF, 0x7F, alpha); }
		/** Definition of the color, steelblue from the Netscape color table. */
		static FSColor steelblue(int alpha=255) { return FSColor(0x46, 0x82, 0xB4, alpha); }
		/** Definition of the color, tan from the Netscape color table. */
		static FSColor tan(int alpha=255) { return FSColor(0xD2, 0xB4, 0x8C, alpha); }
		/** Definition of the color, teal from the Netscape color table. */
		static FSColor teal(int alpha=255) { return FSColor(0x00, 0x80, 0x80, alpha); }
		/** Definition of the color, thistle from the Netscape color table. */
		static FSColor thistle(int alpha=255) { return FSColor(0xD8, 0xBF, 0xD8, alpha); }
		/** Definition of the color, tomato from the Netscape color table. */
		static FSColor tomato(int alpha=255) { return FSColor(0xFF, 0x63, 0x47, alpha); }
		/** Definition of the color, turquoise from the Netscape color table. */
		static FSColor turquoise(int alpha=255) { return FSColor(0x40, 0xE0, 0xD0, alpha); }
		/** Definition of the color, violet from the Netscape color table. */
		static FSColor violet(int alpha=255) { return FSColor(0xEE, 0x82, 0xEE, alpha); }
		/** Definition of the color, wheat from the Netscape color table. */
		static FSColor wheat(int alpha=255) { return FSColor(0xF5, 0xDE, 0xB3, alpha); }
		/** Definition of the color, white from the Netscape color table. */
		static FSColor white(int alpha=255) { return FSColor(0xFF, 0xFF, 0xFF, alpha); }
		/** Definition of the color, whitesmoke from the Netscape color table. */
		static FSColor whitesmoke(int alpha=255) { return FSColor(0xF5, 0xF5, 0xF5, alpha); }
		/** Definition of the color, yellow from the Netscape color table. */
		static FSColor yellow(int alpha=255) { return FSColor(0xFF, 0xFF, 0x00, alpha); }
		/** Definition of the color, yellowgreen from the Netscape color table. */
		static FSColor yellowgreen(int alpha=255) { return FSColor(0x9A, 0xCD, 0x32, alpha); } 
    };
} 

#endif
