<?xml version='1.0' encoding='ISO-8859-1' standalone='yes' ?>
<tagfile>
  <compound kind="page">
    <name>index</name>
    <title>Transform Utilities</title>
    <filename>index</filename>
  </compound>
  <compound kind="class">
    <name>transform::FSCodec</name>
    <filename>classtransform_1_1FSCodec.html</filename>
    <member kind="enumeration">
      <name>ByteOrder</name>
      <anchor>w2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>LittleEndian</name>
      <anchor>w2w0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>BigEndian</name>
      <anchor>w2w1</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual ByteOrder CALL</type>
      <name>getByteOrder</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a0</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setByteOrder</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a1</anchor>
      <arglist>(ByteOrder order)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t CALL</type>
      <name>getDataSize</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t CALL</type>
      <name>getData</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a3</anchor>
      <arglist>(unsigned char *bytes)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>setDataFromFile</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a4</anchor>
      <arglist>(const char *filename)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setData</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a5</anchor>
      <arglist>(const unsigned char *bytes, size_t size)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int CALL</type>
      <name>getPointer</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a6</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setPointer</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a7</anchor>
      <arglist>(unsigned int offset)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>adjustPointer</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a8</anchor>
      <arglist>(int offset)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>alignToByte</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool CALL</type>
      <name>eof</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a10</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool CALL</type>
      <name>findBits</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a11</anchor>
      <arglist>(int value, unsigned int numberOfBits, int step)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual bool CALL</type>
      <name>findWord</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a12</anchor>
      <arglist>(int value, unsigned int numberOfBytes, int step)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int CALL</type>
      <name>readBits</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a13</anchor>
      <arglist>(unsigned int numberOfBits)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>readSignedBits</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a14</anchor>
      <arglist>(unsigned int numberOfBits)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int CALL</type>
      <name>readWord</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a15</anchor>
      <arglist>(unsigned int numberOfBytes)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>readSignedWord</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a16</anchor>
      <arglist>(unsigned int numberOfBytes)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>writeBits</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a17</anchor>
      <arglist>(int value, unsigned int numberOfBits)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>writeWord</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a18</anchor>
      <arglist>(int value, unsigned int numberOfBytes)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>readBytes</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a19</anchor>
      <arglist>(unsigned char *bytes, size_t size)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>writeBytes</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a20</anchor>
      <arglist>(const unsigned char *bytes, size_t size)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual float CALL</type>
      <name>readFixedBits</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a21</anchor>
      <arglist>(unsigned int numberOfBits, unsigned int fractionSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>writeFixedBits</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a22</anchor>
      <arglist>(float value, unsigned int numberOfBits, unsigned int fractionSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned char CALL</type>
      <name>readByte</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a23</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned short CALL</type>
      <name>readShort</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a24</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual short CALL</type>
      <name>readSignedShort</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a25</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int CALL</type>
      <name>readInt</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a26</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>destroy</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a27</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator delete</name>
      <anchorfile>classtransform_1_1FSCodec.html</anchorfile>
      <anchor>a28</anchor>
      <arglist>(void *p)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>transform::FSImageConstructor</name>
    <filename>classtransform_1_1FSImageConstructor.html</filename>
    <member kind="enumeration">
      <name>ImageFormat</name>
      <anchor>w7</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>NONE</name>
      <anchor>w7w0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>JPEG</name>
      <anchor>w7w1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDX8</name>
      <anchor>w7w2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>IDXA</name>
      <anchor>w7w3</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RGB5</name>
      <anchor>w7w4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RGB8</name>
      <anchor>w7w5</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>RGBA</name>
      <anchor>w7w6</anchor>
      <arglist></arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>setImageFromFile</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a0</anchor>
      <arglist>(const char *filename)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>setImage</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a1</anchor>
      <arglist>(const unsigned char *bytes, size_t size)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>getFormat</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int CALL</type>
      <name>getWidth</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a3</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int CALL</type>
      <name>getHeight</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t CALL</type>
      <name>getColorTableSize</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a5</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t CALL</type>
      <name>getColorTable</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a6</anchor>
      <arglist>(unsigned char *buffer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t CALL</type>
      <name>getIndexedImage</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a7</anchor>
      <arglist>(unsigned char *buffer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t CALL</type>
      <name>getColorImage</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a8</anchor>
      <arglist>(unsigned char *buffer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t CALL</type>
      <name>getJPEGImageSize</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t CALL</type>
      <name>getJPEGImage</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a10</anchor>
      <arglist>(unsigned char *buffer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setIndexedImage</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a11</anchor>
      <arglist>(int encoding, unsigned int imageWidth, unsigned int imageHeight, const unsigned char *table, size_t tableSize, const unsigned char *image)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setColorImage</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a12</anchor>
      <arglist>(int encoding, unsigned int imageWidth, unsigned int imageHeight, const unsigned char *image)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setJPEGImage</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a13</anchor>
      <arglist>(unsigned int imageWidth, unsigned int imageHeight, const unsigned char *image, size_t size)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSDefineObject *CALL</type>
      <name>defineImage</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a14</anchor>
      <arglist>(int identifier)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSDefineShape3 *CALL</type>
      <name>defineShape</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a15</anchor>
      <arglist>(int shapeIdentifier, int imageIdentifier, int xOrigin, int yOrigin, int borderWidth, const FSColor *borderColor)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>destroy</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a16</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator delete</name>
      <anchorfile>classtransform_1_1FSImageConstructor.html</anchorfile>
      <anchor>a17</anchor>
      <arglist>(void *p)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>transform::FSShapeConstructor</name>
    <filename>classtransform_1_1FSShapeConstructor.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setLineStyle</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a0</anchor>
      <arglist>(int index, FSLineStyle *aLineStyle)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>addLineStyle</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a1</anchor>
      <arglist>(FSLineStyle *aLineStyle)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setFillStyle</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a2</anchor>
      <arglist>(int index, FSFillStyle *aFillStyle)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>addFillStyle</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a3</anchor>
      <arglist>(FSFillStyle *aFillStyle)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>selectLineStyle</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a4</anchor>
      <arglist>(int index)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>selectFillStyle</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a5</anchor>
      <arglist>(int index)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>selectAltStyle</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a6</anchor>
      <arglist>(int index)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>selectStyle</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a7</anchor>
      <arglist>(int lineIndex, int fillIndex, int altIndex)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSDefineShape3 *CALL</type>
      <name>defineShape</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a8</anchor>
      <arglist>(int identifier)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>newPath</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a9</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>closePath</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a10</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>move</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a11</anchor>
      <arglist>(int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>rmove</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a12</anchor>
      <arglist>(int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>line</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a13</anchor>
      <arglist>(int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>rline</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a14</anchor>
      <arglist>(int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>curve</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a15</anchor>
      <arglist>(int x1, int y1, int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>rcurve</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a16</anchor>
      <arglist>(int x1, int y1, int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>curve</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a17</anchor>
      <arglist>(int x1, int y1, int x2, int y2, int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>rcurve</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a18</anchor>
      <arglist>(int x1, int y1, int x2, int y2, int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>reflect</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a19</anchor>
      <arglist>(int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>rreflect</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a20</anchor>
      <arglist>(int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>reflect</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a21</anchor>
      <arglist>(int x2, int y2, int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>rreflect</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a22</anchor>
      <arglist>(int x2, int y2, int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>rect</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a23</anchor>
      <arglist>(int x, int y, int width, int height)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>rect</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a24</anchor>
      <arglist>(int width, int height)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>rect</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a25</anchor>
      <arglist>(int x, int y, int width, int height, int radius)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>rect</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a26</anchor>
      <arglist>(int width, int height, int radius)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>ellipse</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a27</anchor>
      <arglist>(int x, int y, int rx, int ry)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>ellipse</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a28</anchor>
      <arglist>(int rx, int ry)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>circle</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a29</anchor>
      <arglist>(int x, int y, int r)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>circle</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a30</anchor>
      <arglist>(int r)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>polygon</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a31</anchor>
      <arglist>(int points[], size_t size)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>moveForFont</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a32</anchor>
      <arglist>(int x, int y)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>destroy</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a33</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator delete</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>a34</anchor>
      <arglist>(void *p)</arglist>
    </member>
    <member kind="variable">
      <type>bool</type>
      <name>COORDINATES_ARE_PIXELS</name>
      <anchorfile>classtransform_1_1FSShapeConstructor.html</anchorfile>
      <anchor>o0</anchor>
      <arglist></arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>transform::FSSoundConstructor</name>
    <filename>classtransform_1_1FSSoundConstructor.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>getFormat</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a0</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int CALL</type>
      <name>getNumberOfChannels</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a1</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int CALL</type>
      <name>getSamplesPerChannel</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a2</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int CALL</type>
      <name>getSampleRate</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a3</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual unsigned int CALL</type>
      <name>getSampleSize</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a4</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t CALL</type>
      <name>getSoundSize</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a5</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual size_t CALL</type>
      <name>getSound</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a6</anchor>
      <arglist>(unsigned char *buffer)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>setSoundFromFile</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a7</anchor>
      <arglist>(const char *filename)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>setSound</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a8</anchor>
      <arglist>(const unsigned char *bytes, size_t size)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setSound</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a9</anchor>
      <arglist>(int encoding, unsigned int channelCount, unsigned int sampleCount, unsigned int samplingRate, unsigned int samplingSize, const unsigned char *bytes, size_t size)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSDefineSound *CALL</type>
      <name>defineSound</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a10</anchor>
      <arglist>(int anIdentifier)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSSoundStreamHead2 *CALL</type>
      <name>streamHeader</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a11</anchor>
      <arglist>(unsigned int samplesPerBlock)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSSoundStreamBlock *CALL</type>
      <name>streamBlock</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a12</anchor>
      <arglist>(unsigned int blockNumber, unsigned int samplesPerBlock)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>destroy</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a13</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator delete</name>
      <anchorfile>classtransform_1_1FSSoundConstructor.html</anchorfile>
      <anchor>a14</anchor>
      <arglist>(void *p)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>transform::FSTextConstructor</name>
    <filename>classtransform_1_1FSTextConstructor.html</filename>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>setFontFromFile</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a0</anchor>
      <arglist>(const char *filename)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>setFont</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a1</anchor>
      <arglist>(const unsigned char *bytes, size_t numberOfBytes)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setIdentifier</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a2</anchor>
      <arglist>(int anIdentifier)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setSize</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a3</anchor>
      <arglist>(unsigned int fontSize)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>setColor</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a4</anchor>
      <arglist>(const FSColor *fontColor)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>canDisplayCharacters</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a5</anchor>
      <arglist>(const char *aString)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual int CALL</type>
      <name>canDisplayWideCharacters</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a6</anchor>
      <arglist>(const wchar_t *aString)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSDefineFont2 *CALL</type>
      <name>defineFont</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a7</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSDefineText2 *CALL</type>
      <name>defineText</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a8</anchor>
      <arglist>(int anIdentifier, const char *text)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSDefineText2 *CALL</type>
      <name>defineTextBlock</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a9</anchor>
      <arglist>(int anIdentifier, const char *lines[], size_t count, int lineSpacing)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSDefineText2 *CALL</type>
      <name>defineWideText</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a10</anchor>
      <arglist>(int anIdentifier, const wchar_t *text)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSDefineText2 *CALL</type>
      <name>defineWideTextBlock</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a11</anchor>
      <arglist>(int anIdentifier, const wchar_t *lines[], size_t count, int lineSpacing)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSBounds *CALL</type>
      <name>boundsForText</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a12</anchor>
      <arglist>(const char *text)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSBounds *CALL</type>
      <name>boundsForWideText</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a13</anchor>
      <arglist>(const wchar_t *text)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSDefineShape3 *CALL</type>
      <name>defineShape</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a14</anchor>
      <arglist>(int anIdentifier, const char *text)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual FSDefineShape3 *CALL</type>
      <name>defineWideShape</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a15</anchor>
      <arglist>(int anIdentifier, const wchar_t *text)=0</arglist>
    </member>
    <member kind="function" virtualness="pure">
      <type>virtual void CALL</type>
      <name>destroy</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a16</anchor>
      <arglist>()=0</arglist>
    </member>
    <member kind="function">
      <type>void</type>
      <name>operator delete</name>
      <anchorfile>classtransform_1_1FSTextConstructor.html</anchorfile>
      <anchor>a17</anchor>
      <arglist>(void *p)</arglist>
    </member>
  </compound>
  <compound kind="class">
    <name>transform::TransformUtil</name>
    <filename>classtransform_1_1TransformUtil.html</filename>
    <member kind="enumeration">
      <name>Status</name>
      <anchor>w4</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>OK</name>
      <anchor>w4w0</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FileNotFound</name>
      <anchor>w4w1</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>ReadError</name>
      <anchor>w4w2</anchor>
      <arglist></arglist>
    </member>
    <member kind="enumvalue">
      <name>FormatError</name>
      <anchor>w4w3</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>MAJOR</name>
      <anchorfile>classtransform_1_1TransformUtil.html</anchorfile>
      <anchor>s0</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>MINOR</name>
      <anchorfile>classtransform_1_1TransformUtil.html</anchorfile>
      <anchor>s1</anchor>
      <arglist></arglist>
    </member>
    <member kind="variable" static="yes">
      <type>static const int</type>
      <name>RELEASE</name>
      <anchorfile>classtransform_1_1TransformUtil.html</anchorfile>
      <anchor>s2</anchor>
      <arglist></arglist>
    </member>
  </compound>
</tagfile>
