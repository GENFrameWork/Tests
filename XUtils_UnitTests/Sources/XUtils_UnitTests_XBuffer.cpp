/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XBuffer.cpp
*
* @class      XUTILS_UNITTESTS_XBUFFER
* @brief      XUtils unit tests for XBuffer class
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XUtils_UnitTests_XBuffer.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XString.h"
#include "XBuffer.h"
#include "XVariant.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE      
namespace TEST_XBUFFER
{


TEST(UNITTEST_XBUFFER_CLASSNAME, ConstructorSize) 
{
  XBUFFER buffer((XDWORD)32);

  EXPECT_EQ(32, buffer.GetSize());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, ConstructorDefault)
{
  XBUFFER buffer;

  EXPECT_EQ(0, buffer.GetSize());
  EXPECT_TRUE(buffer.IsEmpty());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, ConstructorCopy)
{
  XBUFFER buffer1;

  buffer1.Add((XBYTE)1);
  buffer1.Add((XBYTE)2);
  buffer1.Add((XBYTE)3);

  XBUFFER buffer2(buffer1);

  EXPECT_EQ(buffer1.GetSize(), buffer2.GetSize());
  EXPECT_EQ(buffer1.GetByte(0), buffer2.GetByte(0));
  EXPECT_EQ(buffer1.GetByte(1), buffer2.GetByte(1));
  EXPECT_EQ(buffer1.GetByte(2), buffer2.GetByte(2));
}


TEST(UNITTEST_XBUFFER_CLASSNAME, SetSizeAndEmpty)
{
  XBUFFER buffer;

  EXPECT_TRUE(buffer.SetSize((XDWORD)16));
  EXPECT_EQ(16, buffer.GetSize());
  EXPECT_FALSE(buffer.IsEmpty());

  EXPECT_TRUE(buffer.Empty());
  EXPECT_EQ(0, buffer.GetSize());
  EXPECT_TRUE(buffer.IsEmpty());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, AddArrayAndGetArray)
{
  XBUFFER buffer;

  XBYTE  indata[4]  = { 10, 11, 12, 13 };
  XBYTE  outdata[4] = { 0,  0,  0,  0  };

  EXPECT_TRUE(buffer.Add(indata, 4));
  EXPECT_EQ(4, buffer.GetSize());

  EXPECT_TRUE(buffer.Get(outdata, 4, 0));
  EXPECT_EQ(outdata[0], 10);
  EXPECT_EQ(outdata[1], 11);
  EXPECT_EQ(outdata[2], 12);
  EXPECT_EQ(outdata[3], 13);
}


TEST(UNITTEST_XBUFFER_CLASSNAME, InsertByteInMiddle)
{
  XBUFFER buffer;

  buffer.Add((XBYTE)1);
  buffer.Add((XBYTE)3);

  EXPECT_TRUE(buffer.Insert((XBYTE)2, 1));

  EXPECT_EQ(3, buffer.GetSize());
  EXPECT_EQ(buffer.GetByte(0), 1);
  EXPECT_EQ(buffer.GetByte(1), 2);
  EXPECT_EQ(buffer.GetByte(2), 3);
}


TEST(UNITTEST_XBUFFER_CLASSNAME, SetByteAtPosition)
{
  XBUFFER buffer;

  buffer.Add((XBYTE)1);
  buffer.Add((XBYTE)2);
  buffer.Add((XBYTE)3);

  EXPECT_TRUE(buffer.Set((XBYTE)9, 1));
  EXPECT_EQ(3, buffer.GetSize());
  EXPECT_EQ(buffer.GetByte(0), 1);
  EXPECT_EQ(buffer.GetByte(1), 9);
  EXPECT_EQ(buffer.GetByte(2), 3);
}


TEST(UNITTEST_XBUFFER_CLASSNAME, DeleteByte)
{
  XBUFFER buffer;

  buffer.Add((XBYTE)1);
  buffer.Add((XBYTE)2);
  buffer.Add((XBYTE)3);

  EXPECT_TRUE(buffer.DeleteByte((XBYTE)2));
  EXPECT_EQ(2, buffer.GetSize());
  EXPECT_EQ(buffer.GetByte(0), 1);
  EXPECT_EQ(buffer.GetByte(1), 3);
}


TEST(UNITTEST_XBUFFER_CLASSNAME, CopyToAndCopyFrom)
{
  XBUFFER buffer1;
  XBUFFER buffer2;
  XBUFFER buffer3;

  buffer1.Add((XBYTE)7);
  buffer1.Add((XBYTE)8);
  buffer1.Add((XBYTE)9);

  EXPECT_TRUE(buffer1.CopyTo(buffer2));
  EXPECT_TRUE(buffer3.CopyFrom(buffer1));

  EXPECT_EQ(buffer1.GetSize(), buffer2.GetSize());
  EXPECT_EQ(buffer1.GetSize(), buffer3.GetSize());

  EXPECT_EQ(buffer1.GetByte(0), buffer2.GetByte(0));
  EXPECT_EQ(buffer1.GetByte(1), buffer2.GetByte(1));
  EXPECT_EQ(buffer1.GetByte(2), buffer2.GetByte(2));

  EXPECT_EQ(buffer1.GetByte(0), buffer3.GetByte(0));
  EXPECT_EQ(buffer1.GetByte(1), buffer3.GetByte(1));
  EXPECT_EQ(buffer1.GetByte(2), buffer3.GetByte(2));
}


TEST(UNITTEST_XBUFFER_CLASSNAME, AddDoubleAndGetDouble)
{
  XBUFFER buffer;
  double  value = 0.0;

  buffer.Add((double)1.25);
  EXPECT_EQ(8, buffer.GetSize());

  buffer.Get((double&)value, 0);
  EXPECT_DOUBLE_EQ(value, (double)1.25);
}


TEST(UNITTEST_XBUFFER_CLASSNAME, CompareAndOperators)
{
  XBUFFER buffer1;
  XBUFFER buffer2;

  buffer1.Add((XBYTE)1);
  buffer1.Add((XBYTE)2);
  buffer1.Add((XBYTE)3);

  buffer2.Add((XBYTE)1);
  buffer2.Add((XBYTE)2);
  buffer2.Add((XBYTE)3);

  bool cmp = buffer1.Compare(buffer2);

  EXPECT_TRUE(cmp);
  EXPECT_EQ(cmp, (buffer1 == buffer2));
  EXPECT_EQ(!cmp, (buffer1 != buffer2));

  buffer2.Add((XBYTE)4);

  cmp = buffer1.Compare(buffer2);

  EXPECT_FALSE(cmp);
  EXPECT_EQ(cmp, (buffer1 == buffer2));
  EXPECT_EQ(!cmp, (buffer1 != buffer2));
}


TEST(UNITTEST_XBUFFER_CLASSNAME, AddAll)
{
  XBUFFER buffer;

  buffer.Add((bool)true)  ;
  buffer.Add((XBYTE)  1)  ;
  buffer.Add((XWORD) 16)  ;
  buffer.Add((XDWORD)32)  ;
  buffer.Add((XQWORD)64)  ;
  buffer.Add((float)1.3)  ; 

  EXPECT_EQ(20, buffer.GetSize());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, AddBool)
{
  XBUFFER buffer;

  buffer.Add((bool)true);
  EXPECT_EQ(1,buffer.GetSize());  
}


TEST(UNITTEST_XBUFFER_CLASSNAME, AddByte)
{
  XBUFFER buffer;
 
  buffer.Add((XBYTE)1);
  EXPECT_EQ(1, buffer.GetSize()); 
}


TEST(UNITTEST_XBUFFER_CLASSNAME, AddWord)
{
  XBUFFER buffer;

  buffer.Add((XWORD)16);
  EXPECT_EQ(2, buffer.GetSize());  
}


TEST(UNITTEST_XBUFFER_CLASSNAME, AddDWord)
{
  XBUFFER buffer;

  buffer.Add((XDWORD)32);
  EXPECT_EQ(4, buffer.GetSize());  
}


TEST(UNITTEST_XBUFFER_CLASSNAME, AddQWord)
{
  XBUFFER buffer;

  buffer.Add((XQWORD)64);
  EXPECT_EQ(8, buffer.GetSize());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, AddFloat)
{
  XBUFFER buffer;
  
  buffer.Add((float)1.3);
  EXPECT_EQ(4, buffer.GetSize()); 
}  


TEST(UNITTEST_XBUFFER_CLASSNAME, GetByte)
{
  XBUFFER buffer;
  XBYTE   byte = 0;
 
  buffer.Add((XBYTE)1);
  buffer.Get((XBYTE&)byte, 0);

  EXPECT_EQ(byte, 1);
  EXPECT_EQ(1, buffer.GetSize());  
}


TEST(UNITTEST_XBUFFER_CLASSNAME, GetArrayByte)
{
  XBUFFER buffer;
  XBYTE   byte = 0;
 
  buffer.Add((XBYTE)50);
  buffer.Get((XBYTE&)byte, 0);
  
  EXPECT_EQ(byte, 50);
  EXPECT_EQ(1, buffer.GetSize());  
}


TEST(UNITTEST_XBUFFER_CLASSNAME, GetWord)
{
  XBUFFER buffer;
  XWORD   xword = 0;
 
  buffer.Add((XWORD)16);
  buffer.Get((XWORD&)xword, 0);

  EXPECT_EQ(xword, 16);
  EXPECT_EQ(2, buffer.GetSize());
  buffer.Empty();
}


TEST(UNITTEST_XBUFFER_CLASSNAME, GetDWord)
{
  XBUFFER buffer;
  XDWORD  xdword = 0;
 
  buffer.Add((XDWORD)32);
  buffer.Get((XDWORD&)xdword, 0);

  EXPECT_EQ(xdword, 32);
  EXPECT_EQ(4, buffer.GetSize());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, GetQWord)
{
  XBUFFER buffer;
  XQWORD  xqword= 0;
    
  buffer.Add((XQWORD)64);
  buffer.Get((XQWORD&)xqword, 0);

  EXPECT_EQ(xqword, 64);
  EXPECT_EQ(8, buffer.GetSize());  
}


TEST(UNITTEST_XBUFFER_CLASSNAME, GetFloat)
{
  XBUFFER buffer; 
  float   i;
 
  buffer.Add((float)1.6);
  buffer.Get((float&)i, 0);

  EXPECT_FLOAT_EQ(i, (float)1.6);
  EXPECT_EQ(4, buffer.GetSize());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractByte)
{
  XBUFFER buffer;
  XBYTE   byte;
  
  buffer.Add((XBYTE)1);
  buffer.Extract((XBYTE&)byte, 0);

  EXPECT_EQ(byte, 1);
  EXPECT_EQ(0, buffer.GetSize());  
}


TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractArrayByte)
{
  XBUFFER buffer;
  XBYTE   byte;

  buffer.Add((XBYTE)30);
  buffer.Extract((XBYTE&)byte, 0);

  EXPECT_EQ(byte, 30);
  EXPECT_EQ(0, buffer.GetSize());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractWord)
{
  XBUFFER buffer;
  XWORD   xword = 0;

  buffer.Add((XWORD)16);
  buffer.Extract((XWORD&)xword,0);

  EXPECT_EQ(xword, 16);
  EXPECT_EQ(0, buffer.GetSize());  
}


TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractDWord)
{
  XBUFFER buffer;
  XDWORD  xdword = 0;

  buffer.Add((XDWORD)32);
  buffer.Extract((XDWORD&)xdword, 0);

  EXPECT_EQ(xdword, 32);
  EXPECT_EQ(0, buffer.GetSize());  
}


TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractQWord)
{
  XBUFFER buffer;
  XQWORD  xqword = 0;
 
  buffer.Add((XQWORD)64);
  buffer.Extract((XQWORD&)xqword, 0);

  EXPECT_EQ(xqword, 64);
  EXPECT_EQ(0, buffer.GetSize());  
}


TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractFloat)
{
  XBUFFER buffer;
  float   i = 0.0f;

  buffer.Add((float)1.6);
  buffer.Extract((float&)i, 0);

  EXPECT_FLOAT_EQ(i, (float)1.6);
  EXPECT_EQ(0, buffer.GetSize());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, PositionAndGetDefault)
{
  XBUFFER buffer;
  XBYTE   byte1 = 0;
  XBYTE   byte2 = 0;

  buffer.Add((XBYTE)10);
  buffer.Add((XBYTE)20);

  buffer.ResetPosition();
  EXPECT_EQ(0, buffer.GetPosition());

  EXPECT_TRUE(buffer.Get((XBYTE&)byte1));
  EXPECT_TRUE(buffer.Get((XBYTE&)byte2));

  EXPECT_EQ((XBYTE)10, byte1);
  EXPECT_EQ((XBYTE)20, byte2);
  EXPECT_EQ(2, buffer.GetPosition());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, SetPosition)
{
  XBUFFER buffer;
  XBYTE   byte = 0;

  buffer.Add((XBYTE)1);
  buffer.Add((XBYTE)2);
  buffer.Add((XBYTE)3);

  EXPECT_TRUE(buffer.SetPosition(1));
  EXPECT_EQ(1, buffer.GetPosition());

  EXPECT_TRUE(buffer.Get((XBYTE&)byte));
  EXPECT_EQ((XBYTE)2, byte);
  EXPECT_EQ(2, buffer.GetPosition());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, InsertArrayAtBeginAndEnd)
{
  XBUFFER buffer;

  XBYTE inbegin[2] = { 1, 2 };
  XBYTE inend[2]   = { 5, 6 };

  buffer.Add((XBYTE)3);
  buffer.Add((XBYTE)4);

  EXPECT_TRUE(buffer.Insert(inbegin, 2, 0));
  EXPECT_TRUE(buffer.Add(inend, 2));

  EXPECT_EQ(6, buffer.GetSize());
  EXPECT_EQ((XBYTE)1, buffer.GetByte(0));
  EXPECT_EQ((XBYTE)2, buffer.GetByte(1));
  EXPECT_EQ((XBYTE)3, buffer.GetByte(2));
  EXPECT_EQ((XBYTE)4, buffer.GetByte(3));
  EXPECT_EQ((XBYTE)5, buffer.GetByte(4));
  EXPECT_EQ((XBYTE)6, buffer.GetByte(5));
}


TEST(UNITTEST_XBUFFER_CLASSNAME, FillBufferAndGetPointers)
{
  XBUFFER buffer;

  EXPECT_TRUE(buffer.Resize((XDWORD)8));

  EXPECT_TRUE(buffer.FillBuffer((XBYTE)0xAA));

  XBYTE* ptr = buffer.Get();
  EXPECT_TRUE(ptr != NULL);

  for(int c=0; c<(int)buffer.GetSize(); c++)
    {
      EXPECT_EQ((XBYTE)0xAA, ptr[c]);
    }
}


TEST(UNITTEST_XBUFFER_CLASSNAME, Swap)
{
  XBUFFER buffer;

  buffer.Add((XBYTE)1);
  buffer.Add((XBYTE)2);
  buffer.Add((XBYTE)3);
  buffer.Add((XBYTE)4);

  EXPECT_TRUE(buffer.Swap());

  EXPECT_EQ((XBYTE)4, buffer.GetByte(0));
  EXPECT_EQ((XBYTE)3, buffer.GetByte(1));
  EXPECT_EQ((XBYTE)2, buffer.GetByte(2));
  EXPECT_EQ((XBYTE)1, buffer.GetByte(3));
}


TEST(UNITTEST_XBUFFER_CLASSNAME, CompareWithRawBuffer)
{
  XBUFFER buffer;

  XBYTE data[3] = { 9, 8, 7 };

  EXPECT_TRUE(buffer.Add(data, 3));
  EXPECT_TRUE(buffer.Compare(data, 3));

  data[1] = 0;
  EXPECT_FALSE(buffer.Compare(data, 3));
}


TEST(UNITTEST_XBUFFER_CLASSNAME, FindSubBuffer)
{
  XBUFFER buffer;
  XBUFFER subbuffer;

  buffer.Add((XBYTE)1);
  buffer.Add((XBYTE)2);
  buffer.Add((XBYTE)3);
  buffer.Add((XBYTE)4);
  buffer.Add((XBYTE)5);

  subbuffer.Add((XBYTE)3);
  subbuffer.Add((XBYTE)4);

  int index = buffer.Find(&subbuffer, 0);
  EXPECT_EQ(2, index);

  index = buffer.Find(&subbuffer, 3);
  EXPECT_EQ(XBUFFER_INVALIDPOSITION, index);
}


TEST(UNITTEST_XBUFFER_CLASSNAME, PaddingAddAndDelete)
{
  XBUFFER buffer;

  buffer.Add((XBYTE)1);
  buffer.Add((XBYTE)2);
  buffer.Add((XBYTE)3);

  EXPECT_FALSE(buffer.Padding_Has());
  EXPECT_TRUE(buffer.Padding_Add(8, XBUFFER_PADDINGTYPE_PKCS5));

  EXPECT_TRUE(buffer.Padding_Has());
  EXPECT_EQ((XBYTE)5, buffer.Padding_GetSize());
  EXPECT_EQ(8, buffer.GetSize());

  EXPECT_EQ((XBYTE)5, buffer.GetLastByte());

  EXPECT_TRUE(buffer.Padding_Delete());
  EXPECT_FALSE(buffer.Padding_Has());
  EXPECT_EQ(3, buffer.GetSize());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, BitAddAndGetData)
{
  XBUFFER buffer;

  EXPECT_TRUE(buffer.Bit_SetNBits(4));

  EXPECT_TRUE(buffer.Bit_AddData(0x0A));  // 1010
  EXPECT_TRUE(buffer.Bit_AddData(0x05));  // 0101

  EXPECT_EQ((XBYTE)0, buffer.Bit_GetBitsFree());

  XDWORD data1 = buffer.Bit_GetData(0, 4);
  XDWORD data2 = buffer.Bit_GetData(4, 4);

  EXPECT_EQ((XDWORD)0x0A, data1);
  EXPECT_EQ((XDWORD)0x05, data2);
}


TEST(UNITTEST_XBUFFER_CLASSNAME, Base64RoundTrip)
{
  XBUFFER buffer1;
  XBUFFER buffer2;
  XSTRING stringbase64;

  XBYTE data[3] = { 'A', 'B', 'C' };

  EXPECT_TRUE(buffer1.Add(data, 3));

  EXPECT_TRUE(buffer1.ConvertToBase64(stringbase64));
  EXPECT_FALSE(stringbase64.IsEmpty());

  EXPECT_TRUE(buffer2.ConvertFromBase64(stringbase64));
  EXPECT_TRUE(buffer1.Compare(buffer2));
}


TEST(UNITTEST_XBUFFER_CLASSNAME, DecodeBCD)
{
  XBUFFER buffer;

  buffer.Add((XBYTE)0x12);
  buffer.Add((XBYTE)0x34);

  EXPECT_EQ((XDWORD)1234, buffer.DecodeBCD(0, 2));
}


TEST(UNITTEST_XBUFFER_CLASSNAME, DecodeBCDLong)
{
  XBUFFER buffer;

  buffer.Add((XBYTE)0x98);
  buffer.Add((XBYTE)0x76);
  buffer.Add((XBYTE)0x54);
  buffer.Add((XBYTE)0x32);

  EXPECT_EQ((XQWORD)98765432, buffer.DecodeBCDLong(0, 4));
}


TEST(UNITTEST_XBUFFER_CLASSNAME, EndianGlobalAndLocal)
{
  XBUFFER buffer;

  bool globalold = buffer.GetGlobalHardwareUseLittleEndian();

  XBUFFER::SetGlobalHardwareUseLittleEndian(true);
  EXPECT_TRUE(buffer.GetGlobalHardwareUseLittleEndian());

  XBUFFER::SetGlobalHardwareUseLittleEndian(false);
  EXPECT_FALSE(buffer.GetGlobalHardwareUseLittleEndian());

  buffer.SetLocalHardwareUseLittleEndian(true);
  EXPECT_TRUE(buffer.GetLocalHardwareUseLittleEndian());

  buffer.SetLocalHardwareUseLittleEndian(false);
  EXPECT_FALSE(buffer.GetLocalHardwareUseLittleEndian());

  XBUFFER::SetGlobalHardwareUseLittleEndian(globalold);
}


}


#endif


