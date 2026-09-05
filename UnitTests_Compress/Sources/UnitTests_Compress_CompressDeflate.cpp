/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Compress_CompressDeflate.cpp
*
* @class      UNITTESTS_COMPRESS_COMPRESSDEFLATE
* @brief      Compress unit tests for COMPRESS_DEFLATE class
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

#include "UnitTests_Compress_CompressDeflate.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CompressDeflate.h"
#include "XBuffer.h"

#include <zlib.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_COMPRESSDEFLATE
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


static void RoundTrip(XBYTE* origin, XDWORD size)
{
  COMPRESS_DEFLATE compressor;

  XBUFFER compressed;
  ASSERT_TRUE(compressor.Compress(origin, size, &compressed));
  ASSERT_GT(compressed.GetSize(), (XDWORD)0);

  COMPRESS_DEFLATE decompressor;

  XBUFFER decompressed;
  ASSERT_TRUE(decompressor.Decompress(compressed.Get(), compressed.GetSize(), &decompressed));

  ASSERT_EQ(decompressed.GetSize(), size);
  if(size) EXPECT_EQ(memcmp(decompressed.Get(), origin, size), 0);
}


TEST(UNITTESTS_COMPRESSDEFLATE_CLASSNAME, RoundTrip_LongRepeatedRun)
{
  XBYTE origin[4096];
  memset(origin, 'E', sizeof(origin));

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSDEFLATE_CLASSNAME, RoundTrip_RepeatedPattern)
{
  XBYTE origin[2048];
  for(XDWORD c = 0; c < sizeof(origin); c++) origin[c] = (XBYTE)('a' + (c % 11));

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSDEFLATE_CLASSNAME, RoundTrip_PseudoRandomIncompressible)
{
  XBYTE origin[3000];
  FillPseudoRandom(origin, sizeof(origin), 0x55AA55AA);

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSDEFLATE_CLASSNAME, RoundTrip_SingleByte)
{
  XBYTE origin[1] = { 'Z' };

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSDEFLATE_CLASSNAME, CompressProducesZlibWrappedHeader)
{
  // RFC 1950: a zlib stream's first byte's low nibble (CMF & 0x0F) is the compression method (8 =
  // deflate), and the 16-bit big-endian header (CMF<<8|FLG) must be a multiple of 31 -- confirmed
  // real behavior of COMPRESS_DEFLATE::Compress() (CompressDeflate.cpp), which always produces the
  // RFC-correct zlib-wrapped form (COMPRESS_DEFLATE_WINDOWBITS = 15, positive).
  COMPRESS_DEFLATE compressor;

  XBYTE origin[256];
  memset(origin, 'F', sizeof(origin));

  XBUFFER compressed;
  ASSERT_TRUE(compressor.Compress(origin, sizeof(origin), &compressed));
  ASSERT_GE(compressed.GetSize(), (XDWORD)2);

  XBYTE cmf = compressed.Get()[0];
  XBYTE flg = compressed.Get()[1];

  EXPECT_EQ(cmf & 0x0F, (XBYTE)8);
  EXPECT_EQ(((XWORD)cmf << 8 | flg) % 31, (XWORD)0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSDEFLATE_CLASSNAME, DecompressFallsBackToRawDeflate)
* @brief      Verifies the documented raw-deflate fallback (CompressDeflate.h/.cpp): a genuinely raw
*             (headerless, RFC 1951) deflate stream -- produced here directly via zlib's own
*             deflateInit2() with negative windowBits, independently of COMPRESS_DEFLATE -- fails the
*             first zlib-wrapped ZDecompress() attempt but is still decoded correctly by the second
*             attempt (-COMPRESS_DEFLATE_WINDOWBITS).
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSDEFLATE_CLASSNAME, DecompressFallsBackToRawDeflate)
{
  XBYTE origin[1024];
  for(XDWORD c = 0; c < sizeof(origin); c++) origin[c] = (XBYTE)('g' + (c % 13));

  z_stream stream;
  stream.zalloc = Z_NULL;
  stream.zfree  = Z_NULL;
  stream.opaque = Z_NULL;

  ASSERT_EQ(deflateInit2(&stream, -1, Z_DEFLATED, -15, 8, Z_DEFAULT_STRATEGY), Z_OK);

  XBYTE rawdeflate[2048];
  stream.next_in   = origin;
  stream.avail_in  = sizeof(origin);
  stream.next_out  = rawdeflate;
  stream.avail_out = sizeof(rawdeflate);

  ASSERT_EQ(deflate(&stream, Z_FINISH), Z_STREAM_END);
  XDWORD rawsize = sizeof(rawdeflate) - stream.avail_out;
  deflateEnd(&stream);

  COMPRESS_DEFLATE decompressor;
  XBUFFER decompressed;

  ASSERT_TRUE(decompressor.Decompress(rawdeflate, rawsize, &decompressed));
  ASSERT_EQ(decompressed.GetSize(), (XDWORD)sizeof(origin));
  EXPECT_EQ(memcmp(decompressed.Get(), origin, sizeof(origin)), 0);
}


TEST(UNITTESTS_COMPRESSDEFLATE_CLASSNAME, CompressRejectsNullSource)
{
  COMPRESS_DEFLATE compressor;
  XBUFFER buffer;

  EXPECT_FALSE(compressor.Compress((XBYTE*)NULL, 4, &buffer));
}


TEST(UNITTESTS_COMPRESSDEFLATE_CLASSNAME, CompressRejectsZeroSize)
{
  COMPRESS_DEFLATE compressor;
  XBYTE origin[] = { 'a' };
  XBUFFER buffer;

  EXPECT_FALSE(compressor.Compress(origin, 0, &buffer));
}


TEST(UNITTESTS_COMPRESSDEFLATE_CLASSNAME, DecompressRejectsGarbageDataInBothFormats)
{
  COMPRESS_DEFLATE decompressor;

  XBYTE garbage[32];
  FillPseudoRandom(garbage, sizeof(garbage), 0xF00D);

  XBUFFER decompressed;

  EXPECT_FALSE(decompressor.Decompress(garbage, sizeof(garbage), &decompressed));
  EXPECT_EQ(decompressed.GetSize(), (XDWORD)0);
}


}
#endif
