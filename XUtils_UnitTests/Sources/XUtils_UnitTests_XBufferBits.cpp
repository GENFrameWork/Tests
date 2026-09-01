/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XBufferBits.cpp
*
* @class      XUTILS_UNITTESTS_XBUFFERBITS
* @brief      XUtils unit tests for XBufferBits class
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

#include "XUtils_UnitTests_XBufferBits.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XBufferBits.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XBUFFERBITS
{


// 0xB2 = 1011 0010, 0x01 = 0000 0001 : two bytes used across most tests below so bit indices are
// easy to reason about (MSB-first reading, as ReadU()/WriteU() shift from bit (n-1) down to 0).
static void FillTwoByteBuffer(XBUFFER& buffer)
{
  buffer.Set((XBYTE)0xB2, 0);
  buffer.Set((XBYTE)0x01, 1);
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, ConstructorStartsByteAlignedAtBitZero)
{
  XBUFFER buffer((XDWORD)2);
  FillTwoByteBuffer(buffer);

  XBUFFERBITS bits(&buffer);

  EXPECT_TRUE(bits.IsByteAligned());
  EXPECT_EQ((XDWORD)0, bits.GetBitPosition());
  EXPECT_FALSE(bits.IsEOF());
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, ReadU1AtBitZeroReturnsMSBOfFirstByte)
{
  XBUFFER buffer((XDWORD)2);
  FillTwoByteBuffer(buffer);

  XBUFFERBITS bits(&buffer);

  // 0xB2 = 1011 0010 -> first (bit 0) bit read is the MSB: 1
  EXPECT_EQ((XDWORD)1, bits.ReadU1());
  EXPECT_FALSE(bits.IsByteAligned());
  EXPECT_EQ((XDWORD)1, bits.GetBitPosition());
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, ReadU1SequenceMatchesKnownBitPattern)
{
  XBUFFER buffer((XDWORD)2);
  FillTwoByteBuffer(buffer);

  XBUFFERBITS bits(&buffer);

  // 0xB2 = 1,0,1,1,0,0,1,0 (MSB first)
  EXPECT_EQ((XDWORD)1, bits.ReadU1());
  EXPECT_EQ((XDWORD)0, bits.ReadU1());
  EXPECT_EQ((XDWORD)1, bits.ReadU1());
  EXPECT_EQ((XDWORD)1, bits.ReadU1());
  // Middle bit of the buffer (bit index 4 out of 16 total bits)
  EXPECT_EQ((XDWORD)0, bits.ReadU1());
  EXPECT_EQ((XDWORD)0, bits.ReadU1());
  EXPECT_EQ((XDWORD)1, bits.ReadU1());
  EXPECT_EQ((XDWORD)0, bits.ReadU1());

  EXPECT_TRUE(bits.IsByteAligned());
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, ReadU1LastBitOfBufferMatchesLSBOfLastByte)
{
  XBUFFER buffer((XDWORD)2);
  FillTwoByteBuffer(buffer);

  XBUFFERBITS bits(&buffer);

  bits.SkipU(15); // skip to the very last bit (bit index 15, zero-based)

  // 0x01 = 0000 0001 -> last bit (LSB of second byte) is 1
  EXPECT_EQ((XDWORD)1, bits.ReadU1());
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, PeekU1DoesNotAdvancePosition)
{
  XBUFFER buffer((XDWORD)2);
  FillTwoByteBuffer(buffer);

  XBUFFERBITS bits(&buffer);

  EXPECT_EQ((XDWORD)1, bits.PeekU1());
  EXPECT_EQ((XDWORD)1, bits.PeekU1()); // still bit 0, still 1
  EXPECT_EQ((XDWORD)0, bits.GetBitPosition());

  EXPECT_EQ((XDWORD)1, bits.ReadU1()); // now actually consume it
  EXPECT_EQ((XDWORD)1, bits.GetBitPosition());
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, ReadUReadsMultipleBitsAsNibble)
{
  XBUFFER buffer((XDWORD)2);
  FillTwoByteBuffer(buffer);

  XBUFFERBITS bits(&buffer);

  // First nibble of 0xB2 (1011) read MSB-first as a 4-bit unsigned value
  EXPECT_EQ((XDWORD)0x0B, bits.ReadU(4));
  // Second nibble (0010)
  EXPECT_EQ((XDWORD)0x02, bits.ReadU(4));
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, PeekUDoesNotAdvancePosition)
{
  XBUFFER buffer((XDWORD)2);
  FillTwoByteBuffer(buffer);

  XBUFFERBITS bits(&buffer);

  EXPECT_EQ((XDWORD)0x0B, bits.PeekU(4));
  EXPECT_EQ((XDWORD)0x0B, bits.ReadU(4)); // unaffected by the peek above
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, SkipU1AdvancesOneBitWithoutReturningValue)
{
  XBUFFER buffer((XDWORD)2);
  FillTwoByteBuffer(buffer);

  XBUFFERBITS bits(&buffer);

  bits.SkipU1();
  // Bit 1 of 0xB2 (1011 0010) is 0
  EXPECT_EQ((XDWORD)0, bits.ReadU1());
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, IsEOFTrueOnlyAfterConsumingWholeBuffer)
{
  XBUFFER buffer((XDWORD)1);
  buffer.Set((XBYTE)0xFF, 0);

  XBUFFERBITS bits(&buffer);

  EXPECT_FALSE(bits.IsEOF());
  bits.ReadU(8);
  EXPECT_TRUE(bits.IsEOF());
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, IsOverrunBecomesTrueWhenReadingPastEOF)
{
  XBUFFER buffer((XDWORD)1);
  buffer.Set((XBYTE)0xFF, 0);

  XBUFFERBITS bits(&buffer);

  bits.ReadU(8);        // consume the entire (single-byte) buffer
  EXPECT_FALSE(bits.IsOverrun()); // freshly re-byte-aligned (bits_left == 8), not yet overrun

  bits.ReadU1();        // read past the end
  EXPECT_TRUE(bits.IsEOF());
  EXPECT_TRUE(bits.IsOverrun());
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, GetBytePositionNowReportsTheAdvancingOffsetCorrectly)
{
  // FIXED: XBUFFERBITS::GetBytePosition() (XBufferBits.cpp) now returns
  // (XDWORD)(p - xbuffer->Get()), the correct subtraction order. Previously it returned
  // (XDWORD)(xbuffer->Get() - p), which happened to be 0 at construction (p == xbuffer->Get())
  // but wrapped around to a huge unsigned value as soon as p advanced past the first byte.
  XBUFFER buffer((XDWORD)2);
  FillTwoByteBuffer(buffer);

  XBUFFERBITS bits(&buffer);

  EXPECT_EQ((XDWORD)0, bits.GetBytePosition());

  bits.ReadU(8); // consume the whole first byte, p advances by one

  EXPECT_EQ((XDWORD)1, bits.GetBytePosition());
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, SetPositionMovesToRequestedByte)
{
  XBUFFER buffer((XDWORD)2);
  FillTwoByteBuffer(buffer);

  XBUFFERBITS bits(&buffer);

  bits.SetPosition(1, 0);

  // 0x01 = 0000 0001, freshly (re)byte-aligned at the second byte
  EXPECT_TRUE(bits.IsByteAligned());
  EXPECT_EQ((XDWORD)0, bits.ReadU1());
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, WriteU1ThenReadU1RoundTrips)
{
  XBUFFER buffer((XDWORD)1);
  buffer.Set((XBYTE)0x00, 0);

  XBUFFERBITS writer(&buffer);
  writer.WriteU1(1);
  writer.WriteU1(0);
  writer.WriteU1(1);
  writer.WriteU1(1);
  writer.WriteU1(0);
  writer.WriteU1(0);
  writer.WriteU1(1);
  writer.WriteU1(0);

  // Should have reconstructed 0xB2 = 1011 0010 byte-by-byte
  EXPECT_EQ((XBYTE)0xB2, *buffer.Get());

  XBUFFERBITS reader(&buffer);
  EXPECT_EQ((XDWORD)0xB2, reader.ReadU(8));
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, WriteUThenReadURoundTrips)
{
  XBUFFER buffer((XDWORD)1);
  buffer.Set((XBYTE)0x00, 0);

  XBUFFERBITS writer(&buffer);
  writer.WriteU(8, 0xA5);

  XBUFFERBITS reader(&buffer);
  EXPECT_EQ((XDWORD)0xA5, reader.ReadU(8));
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, WriteUEThenReadUERoundTripsKnownExpGolombValues)
{
  XBUFFER buffer((XDWORD)4);
  buffer.Set((XBYTE)0x00, 0);
  buffer.Set((XBYTE)0x00, 1);
  buffer.Set((XBYTE)0x00, 2);
  buffer.Set((XBYTE)0x00, 3);

  XDWORD values[] = { 0, 1, 2, 3, 4, 10, 100 };

  for(XDWORD v = 0; v < 7; v++)
    {
      XBUFFER vbuffer((XDWORD)4);
      vbuffer.Set((XBYTE)0x00, 0);
      vbuffer.Set((XBYTE)0x00, 1);
      vbuffer.Set((XBYTE)0x00, 2);
      vbuffer.Set((XBYTE)0x00, 3);

      XBUFFERBITS writer(&vbuffer);
      writer.WriteUE(values[v]);

      XBUFFERBITS reader(&vbuffer);
      EXPECT_EQ(values[v], reader.ReadUE());
    }
}


TEST(UNITTEST_XBUFFERBITS_CLASSNAME, WriteSEThenReadSERoundTripsKnownSignedValues)
{
  int values[] = { 0, 1, -1, 2, -2, 3, -3 };

  for(int v = 0; v < 7; v++)
    {
      XBUFFER buffer((XDWORD)4);
      buffer.Set((XBYTE)0x00, 0);
      buffer.Set((XBYTE)0x00, 1);
      buffer.Set((XBYTE)0x00, 2);
      buffer.Set((XBYTE)0x00, 3);

      XBUFFERBITS writer(&buffer);
      writer.WriteSE(values[v]);

      XBUFFERBITS reader(&buffer);
      EXPECT_EQ(values[v], reader.ReadSE());
    }
}


}
#endif
