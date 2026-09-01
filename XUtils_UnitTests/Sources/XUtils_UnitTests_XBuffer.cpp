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


TEST(UNITTEST_XBUFFER_CLASSNAME, AddWithMaskAndExtractWithMaskRoundTrip)
{
  XBUFFER buffer;

  EXPECT_TRUE(buffer.AddWithMask((XCHAR*)__L("BWDQ"), (int)0x11, (int)0x2222, (XDWORD)0x33333333, (XQWORD)0x4444444444444444));

  EXPECT_EQ((XDWORD)(1+2+4+8), buffer.GetSize());

  XBYTE  bvar  = 0;
  XWORD  wvar  = 0;
  XDWORD dvar  = 0;
  XQWORD qvar  = 0;

  EXPECT_TRUE(buffer.ExtractWithMask((XCHAR*)__L("BWDQ"), 0, &bvar, &wvar, &dvar, &qvar));

  EXPECT_EQ((XBYTE)0x11, bvar);
  EXPECT_EQ((XWORD)0x2222, wvar);
  EXPECT_EQ((XDWORD)0x33333333, dvar);
  EXPECT_EQ((XQWORD)0x4444444444444444, qvar);
  EXPECT_EQ(0, buffer.GetSize());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, ComparePointerOverload)
{
  XBUFFER buffer1;
  XBUFFER buffer2;

  buffer1.Add((XBYTE)1);
  buffer1.Add((XBYTE)2);

  buffer2.Add((XBYTE)1);
  buffer2.Add((XBYTE)2);

  EXPECT_TRUE(buffer1.Compare(&buffer2));

  buffer2.Add((XBYTE)3);
  EXPECT_FALSE(buffer1.Compare(&buffer2));
}


TEST(UNITTEST_XBUFFER_CLASSNAME, FindStringOverload)
{
  // Find(XSTRING&,...) internally builds its own comparison XBUFFER via Add(XSTRING&,bool),
  // which (when normalize=false) stores each XCHAR as a full XDWORD -- so the haystack buffer
  // must be built the same way for byte offsets to line up.
  XBUFFER buffer;
  XSTRING haystack(__L("ABCDE"));
  XSTRING searchstring(__L("CD"));

  buffer.Add(haystack, false);

  int index = buffer.Find(searchstring, false, 0);
  EXPECT_EQ((int)(2*sizeof(XDWORD)), index);

  XSTRING notfoundstring(__L("ZZ"));
  index = buffer.Find(notfoundstring, false, 0);
  EXPECT_EQ(XBUFFER_INVALIDPOSITION, index);
}


TEST(UNITTEST_XBUFFER_CLASSNAME, SetAddBlockMemSizeAffectsAddedCapacity)
{
  XBUFFER buffer;

  EXPECT_TRUE(buffer.SetAddBlockMemSize(64));

  EXPECT_TRUE(buffer.Add((XBYTE)1));
  EXPECT_EQ(1, buffer.GetSize());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, PaddingGetTypeNowReflectsTheRequestedType)
{
  // FIXED: XBUFFER::Padding_Add() (XBuffer.cpp) now assigns `paddingtype = type;`, so
  // Padding_GetType() genuinely reflects the padding type that was last requested and applied,
  // instead of always reporting its Clean()-time default (XBUFFER_PADDINGTYPE_NONE).
  XBUFFER buffer;

  buffer.Add((XBYTE)1);
  buffer.Add((XBYTE)2);

  EXPECT_EQ(XBUFFER_PADDINGTYPE_NONE, buffer.Padding_GetType());

  EXPECT_TRUE(buffer.Padding_Add(8, XBUFFER_PADDINGTYPE_ZEROS));
  EXPECT_EQ(XBUFFER_PADDINGTYPE_ZEROS, buffer.Padding_GetType());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, BitSetDataAndBitSetBitsFree)
{
  XBUFFER buffer;

  EXPECT_TRUE(buffer.Bit_SetNBits(4));
  EXPECT_TRUE(buffer.Bit_AddData(0x0A));  // 1010
  EXPECT_TRUE(buffer.Bit_AddData(0x05));  // 0101

  // Source note: Bit_SetData() (unlike Bit_AddData()) does NOT merge its written bits with
  // whatever else already occupies the same byte(s) -- it Set()s the whole affected byte(s)
  // from only the new shifted value, so the neighbouring nibble sharing byte 0 gets clobbered
  // to 0 as a side effect here. This documents that real (not fixed) behavior rather than
  // assuming Bit_SetData is a clean bit-level in-place patch.
  EXPECT_TRUE(buffer.Bit_SetData(0x0F, 4, 4));
  EXPECT_EQ((XDWORD)0x0F, buffer.Bit_GetData(4, 4));
  EXPECT_EQ((XDWORD)0x00, buffer.Bit_GetData(0, 4));

  EXPECT_TRUE(buffer.Bit_SetBitsFree(3));
  EXPECT_EQ((XBYTE)3, buffer.Bit_GetBitsFree());
}


TEST(UNITTEST_XBUFFER_CLASSNAME, GetPtrCharAndGetPtrWord)
{
  XBUFFER buffer;

  buffer.Add((XBYTE)'H');
  buffer.Add((XBYTE)'I');
  buffer.Add((XBYTE)0);

  char* charptr = buffer.GetPtrChar();
  ASSERT_TRUE(charptr != NULL);
  EXPECT_EQ('H', charptr[0]);
  EXPECT_EQ('I', charptr[1]);

  XWORD* wordptr = buffer.GetPtrWord();
  ASSERT_TRUE(wordptr != NULL);
  EXPECT_EQ((void*)buffer.Get(), (void*)wordptr);
}


TEST(UNITTEST_XBUFFER_CLASSNAME, GetOutOfRangePSizeReadsPastRemainingSize)
{
  // Source bug (not fixed, XBuffer.cpp XBUFFER::Get(XBYTE*,int,int)): the bounds check
  // "if((!buffer) || (pos>(int)size))" only rejects a start position beyond the buffer,
  // it never validates that pos+psize stays within size, unlike the sibling Extract()
  // (which does clamp). Calling Get() with a psize that overruns the remaining buffer
  // therefore still returns true (no failure signalled) instead of failing/clamping.
  XBUFFER buffer;

  buffer.Add((XBYTE)1);
  buffer.Add((XBYTE)2);

  XBYTE outdata[8] = { 0 };

  // Buffer only has 2 bytes total, ask for 8 starting at position 0: real XUtils behavior
  // does NOT fail (would be expected to, given the requested range overruns the buffer).
  bool status = buffer.Get(outdata, 8, 0);
  EXPECT_TRUE(status);
}


TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractOverlappingRangeUsesMemmoveSafely)
{
  XBUFFER buffer;

  for(XBYTE c=0; c<10; c++)
    {
      buffer.Add((XBYTE)c);
    }

  // Extract a middle chunk whose removal shifts a later, overlapping remainder --
  // regression test for the historical overlapping-memcpy bug documented in XBuffer.cpp
  // (Extract switched from memcpy to memmove specifically for this scenario).
  XBYTE outdata[3] = { 0 };
  EXPECT_TRUE(buffer.Extract(outdata, 2, 3));  // (pbuffer, ppos, psize): start at 2, take 3 bytes

  EXPECT_EQ((XBYTE)2, outdata[0]);
  EXPECT_EQ((XBYTE)3, outdata[1]);
  EXPECT_EQ((XBYTE)4, outdata[2]);

  EXPECT_EQ(7, buffer.GetSize());
  EXPECT_EQ((XBYTE)0, buffer.GetByte(0));
  EXPECT_EQ((XBYTE)1, buffer.GetByte(1));
  EXPECT_EQ((XBYTE)5, buffer.GetByte(2));
  EXPECT_EQ((XBYTE)9, buffer.GetByte(6));
}


}


#endif


