/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Compress_CompressLZW.cpp
*
* @class      UNITTESTS_COMPRESS_COMPRESSLZW
* @brief      Compress unit tests for COMPRESS_LZW class
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

#include "UnitTests_Compress_CompressLZW.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CompressLZW.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_COMPRESSLZW
{


static void FillPseudoRandom(XBYTE* buffer, XDWORD size, XDWORD seed)
{
  XDWORD state = seed;

  for(XDWORD c = 0; c < size; c++)
    {
      state = (state * 1103515245u) + 12345u;
      buffer[c] = (XBYTE)((state >> 16) & 0xFF);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void RoundTrip(XBYTE* origin,XDWORD size)
* @brief      Shared Compress()->Decompress() round-trip helper. COMPRESS_LZW::Compress() (CompressLZW.cpp)
*             pre-Resize()s its own output buffer (size+LZW_MAX_OVERCMP) and shrinks it back to the real
*             compressed size, so the caller does not need to size the compressed XBUFFER. Decompress(),
*             by contrast, calls LZW_Decode() straight into xbuffer->Get() with no Resize()/SetSize() of
*             its own at all -- the caller MUST pre-size the decompression target to (at least) the known
*             original size, and GetSize() afterwards reports whatever the caller pre-set it to, not a
*             value computed from the actual decoded length (see the dedicated finding test below).
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
static void RoundTrip(XBYTE* origin, XDWORD size)
{
  COMPRESS_LZW compressor;

  XBUFFER compressed;

  ASSERT_TRUE(compressor.Compress(origin, size, &compressed));
  ASSERT_GT(compressed.GetSize(), (XDWORD)0);

  COMPRESS_LZW decompressor;

  XBUFFER decompressed;
  decompressed.Resize(size);

  ASSERT_TRUE(decompressor.Decompress(compressed.Get(), compressed.GetSize(), &decompressed));

  EXPECT_EQ(memcmp(decompressed.Get(), origin, size), 0);
}


TEST(UNITTESTS_COMPRESSLZW_CLASSNAME, RoundTrip_LongRepeatedRun)
{
  XBYTE origin[800];
  memset(origin, 'B', sizeof(origin));

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSLZW_CLASSNAME, RoundTrip_RepeatedPattern)
{
  XBYTE origin[512];
  for(XDWORD c = 0; c < sizeof(origin); c++) origin[c] = (XBYTE)('0' + (c % 10));

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSLZW_CLASSNAME, RoundTrip_PseudoRandomIncompressible)
{
  XBYTE origin[400];
  FillPseudoRandom(origin, sizeof(origin), 0xBADC0DE);

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSLZW_CLASSNAME, RoundTrip_SingleByte)
{
  XBYTE origin[1] = { 'Q' };

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSLZW_CLASSNAME, CompressRejectsNullSource)
{
  COMPRESS_LZW compressor;
  XBUFFER buffer;

  EXPECT_FALSE(compressor.Compress((XBYTE*)NULL, 4, &buffer));
}


TEST(UNITTESTS_COMPRESSLZW_CLASSNAME, CompressRejectsZeroSize)
{
  COMPRESS_LZW compressor;
  XBYTE origin[] = { 'a' };
  XBUFFER buffer;

  EXPECT_FALSE(compressor.Compress(origin, 0, &buffer));
}


TEST(UNITTESTS_COMPRESSLZW_CLASSNAME, CompressRejectsNullBuffer)
{
  COMPRESS_LZW compressor;
  XBYTE origin[] = { 'a' };

  EXPECT_FALSE(compressor.Compress(origin, sizeof(origin), (XBUFFER*)NULL));
}


TEST(UNITTESTS_COMPRESSLZW_CLASSNAME, DecompressRejectsNullBuffer)
{
  COMPRESS_LZW compressor;
  XBYTE origin[] = { 'a','b','c' };
  XBUFFER compressed;
  ASSERT_TRUE(compressor.Compress(origin, sizeof(origin), &compressed));

  COMPRESS_LZW decompressor;
  EXPECT_FALSE(decompressor.Decompress(compressed.Get(), compressed.GetSize(), (XBUFFER*)NULL));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSLZW_CLASSNAME, DecompressDoesNotUpdateBufferSizeToActualDecodedLength)
* @brief      FINDING (see /tmp/work/COMPRESS_REVIEW_FINDINGS.md): unlike Compress() (which ends with
*             "xbuffer->Resize(csize);" to shrink its output to the real compressed size,
*             CompressLZW.cpp), COMPRESS_LZW::Decompress() never calls Resize()/SetSize() on its target
*             XBUFFER at all -- it just writes through xbuffer->Get() via LZW_Decode(). This test
*             pre-sizes the decompression target LARGER than the real decoded length and shows
*             GetSize() afterwards still reports the caller's original (larger) pre-allocation, not the
*             actual number of decoded bytes -- an API asymmetry versus Compress() that silently hands
*             back a buffer whose declared size does not describe its real content, unlike
*             COMPRESS_LZRW1KH::Decompress() (which does call buffer->SetSize() with the real
*             decompressed length, CompressLZRW1KH.cpp).
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSLZW_CLASSNAME, DecompressDoesNotUpdateBufferSizeToActualDecodedLength)
{
  COMPRESS_LZW compressor;

  XBYTE origin[10] = { 'a','b','c','d','e','f','g','h','i','j' };
  XBUFFER compressed;
  ASSERT_TRUE(compressor.Compress(origin, sizeof(origin), &compressed));

  COMPRESS_LZW decompressor;

  XBUFFER decompressed;
  XDWORD oversizedcapacity = sizeof(origin) + 50; // deliberately larger than the real decoded length
  decompressed.Resize(oversizedcapacity);

  ASSERT_TRUE(decompressor.Decompress(compressed.Get(), compressed.GetSize(), &decompressed));

  // The real decoded content (first 10 bytes) is correct...
  EXPECT_EQ(memcmp(decompressed.Get(), origin, sizeof(origin)), 0);

  // ...but GetSize() still reports the caller's pre-allocated capacity, not sizeof(origin): the
  // function never shrank/updated it.
  EXPECT_EQ(decompressed.GetSize(), oversizedcapacity);
  EXPECT_NE(decompressed.GetSize(), (XDWORD)sizeof(origin));
}


}
#endif
