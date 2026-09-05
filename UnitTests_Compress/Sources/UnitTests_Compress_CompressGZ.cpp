/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Compress_CompressGZ.cpp
*
* @class      UNITTESTS_COMPRESS_COMPRESSGZ
* @brief      Compress unit tests for COMPRESS_GZ class
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

#include "UnitTests_Compress_CompressGZ.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CompressGZ.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_COMPRESSGZ
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
* @brief      Shared Compress()->Decompress() round-trip helper. COMPRESS_GZ streams both directions
*             through XBUFFER::Add() (CompressGZ.cpp), so unlike COMPRESS_LZW/COMPRESS_LZRW1KH the
*             caller does not need to pre-size either buffer at all.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
static void RoundTrip(XBYTE* origin, XDWORD size)
{
  COMPRESS_GZ compressor;

  XBUFFER compressed;
  ASSERT_TRUE(compressor.Compress(origin, size, &compressed));
  ASSERT_GT(compressed.GetSize(), (XDWORD)0);

  // gzip magic number (RFC 1952): 0x1F 0x8B.
  ASSERT_GE(compressed.GetSize(), (XDWORD)2);
  EXPECT_EQ(compressed.Get()[0], (XBYTE)0x1F);
  EXPECT_EQ(compressed.Get()[1], (XBYTE)0x8B);

  COMPRESS_GZ decompressor;

  XBUFFER decompressed;
  ASSERT_TRUE(decompressor.Decompress(compressed.Get(), compressed.GetSize(), &decompressed));

  ASSERT_EQ(decompressed.GetSize(), size);
  if(size) EXPECT_EQ(memcmp(decompressed.Get(), origin, size), 0);
}


TEST(UNITTESTS_COMPRESSGZ_CLASSNAME, RoundTrip_LongRepeatedRun)
{
  XBYTE origin[4096];
  memset(origin, 'C', sizeof(origin));

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSGZ_CLASSNAME, RoundTrip_RepeatedPattern)
{
  XBYTE origin[2048];
  for(XDWORD c = 0; c < sizeof(origin); c++) origin[c] = (XBYTE)('a' + (c % 7));

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSGZ_CLASSNAME, RoundTrip_PseudoRandomIncompressible)
{
  XBYTE origin[3000];
  FillPseudoRandom(origin, sizeof(origin), 0x1234ABCD);

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSGZ_CLASSNAME, RoundTrip_SingleByte)
{
  XBYTE origin[1] = { 'Z' };

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSGZ_CLASSNAME, RoundTrip_LargerThanOneChunk)
{
  // COMPRESS_GZ_CHUNK is 16384 (CompressGZ.h): exercise more than one Add() iteration in both
  // ZCompress() and ZDecompress().
  XBUFFER origin;
  origin.Resize(40000);
  FillPseudoRandom(origin.Get(), 40000, 0x99887766);

  RoundTrip(origin.Get(), 40000);
}


TEST(UNITTESTS_COMPRESSGZ_CLASSNAME, CompressRejectsNullSource)
{
  COMPRESS_GZ compressor;
  XBUFFER buffer;

  EXPECT_FALSE(compressor.Compress((XBYTE*)NULL, 4, &buffer));
}


TEST(UNITTESTS_COMPRESSGZ_CLASSNAME, CompressRejectsZeroSize)
{
  COMPRESS_GZ compressor;
  XBYTE origin[] = { 'a' };
  XBUFFER buffer;

  EXPECT_FALSE(compressor.Compress(origin, 0, &buffer));
}


TEST(UNITTESTS_COMPRESSGZ_CLASSNAME, CompressRejectsNullBuffer)
{
  COMPRESS_GZ compressor;
  XBYTE origin[] = { 'a' };

  EXPECT_FALSE(compressor.Compress(origin, sizeof(origin), (XBUFFER*)NULL));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSGZ_CLASSNAME, DecompressRejectsTruncatedGzipStream)
* @brief      A gzip stream cut off before its end never reaches Z_STREAM_END inside inflate();
*             ZDecompress() (CompressGZ.cpp) maps every non-OK/non-STREAM_END zlib result (including
*             Z_BUF_ERROR from starved input) to Z_DATA_ERROR, and Decompress() then clears the
*             target XBUFFER and returns false -- confirmed real behavior, not merely read from
*             source: a genuinely truncated real gzip stream is used below.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSGZ_CLASSNAME, DecompressRejectsTruncatedGzipStream)
{
  COMPRESS_GZ compressor;

  XBYTE origin[2048];
  memset(origin, 'D', sizeof(origin));

  XBUFFER compressed;
  ASSERT_TRUE(compressor.Compress(origin, sizeof(origin), &compressed));
  ASSERT_GT(compressed.GetSize(), (XDWORD)8);

  XDWORD truncatedsize = compressed.GetSize() / 2;

  COMPRESS_GZ decompressor;
  XBUFFER decompressed;

  EXPECT_FALSE(decompressor.Decompress(compressed.Get(), truncatedsize, &decompressed));
  EXPECT_EQ(decompressed.GetSize(), (XDWORD)0);
}


TEST(UNITTESTS_COMPRESSGZ_CLASSNAME, DecompressRejectsGarbageData)
{
  COMPRESS_GZ decompressor;

  XBYTE garbage[32];
  FillPseudoRandom(garbage, sizeof(garbage), 0xDEAD);

  XBUFFER decompressed;

  EXPECT_FALSE(decompressor.Decompress(garbage, sizeof(garbage), &decompressed));
  EXPECT_EQ(decompressed.GetSize(), (XDWORD)0);
}


}
#endif
