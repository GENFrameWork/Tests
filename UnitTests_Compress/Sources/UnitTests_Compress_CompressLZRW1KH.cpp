/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Compress_CompressLZRW1KH.cpp
*
* @class      UNITTESTS_COMPRESS_COMPRESSLZRW1KH
* @brief      Compress unit tests for COMPRESS_LZRW1KH class
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

#include "UnitTests_Compress_CompressLZRW1KH.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CompressLZRW1KH.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_COMPRESSLZRW1KH
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void FillPseudoRandom(XBYTE* buffer,XDWORD size,XDWORD seed)
* @brief      Deterministic pseudo-random byte generator (simple LCG) used to build incompressible-ish
*             fixtures without depending on platform <random> facilities or any external data file.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
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
* @brief      Shared Compress()->Decompress() round-trip helper: compresses 'origin'/'size' with a fresh
*             COMPRESS_LZRW1KH instance and verifies the decompressed bytes exactly match the input. Both
*             XBUFFER targets are pre-Resize()d with generous headroom -- CompressionBuffer()/
*             DecompressionBuffer() write directly into buffer->Get() with no bounds checking of their own
*             (CompressLZRW1KH.cpp), and XBUFFER::Get() returns NULL for a still-zero-size buffer
*             (XBuffer.cpp), so an un-Resize()d XBUFFER would make the compressor write through a NULL
*               pointer.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
static void RoundTrip(XBYTE* origin, XDWORD size)
{
  COMPRESS_LZRW1KH compressor;

  XBUFFER compressed;
  compressed.Resize(size + 64);

  ASSERT_TRUE(compressor.Compress(origin, size, &compressed));

  COMPRESS_LZRW1KH decompressor;

  XBUFFER decompressed;
  decompressed.Resize(size ? size : 1);

  ASSERT_TRUE(decompressor.Decompress(compressed.Get(), compressed.GetSize(), &decompressed));

  ASSERT_EQ(decompressed.GetSize(), size);

  if(size)
    {
      EXPECT_EQ(memcmp(decompressed.Get(), origin, size), 0);
    }
}


TEST(UNITTESTS_COMPRESSLZRW1KH_CLASSNAME, RoundTrip_LongRepeatedRun)
{
  // Highly compressible: a long run of the same byte should trigger the run-length branch
  // (CompressionBuffer's "if(size >= 16)" case, CompressLZRW1KH.cpp).
  XBYTE origin[600];
  memset(origin, 'A', sizeof(origin));

  RoundTrip(origin, sizeof(origin));
}


TEST(UNITTESTS_COMPRESSLZRW1KH_CLASSNAME, RoundTrip_RepeatedPattern)
{
  // A repeating multi-byte pattern exercises GetMatch()'s hash-based back-reference path rather
  // than the flat run-length path.
  XBYTE origin[512];
  for(XDWORD c = 0; c < sizeof(origin); c++) origin[c] = (XBYTE)('a' + (c % 5));

  RoundTrip(origin, sizeof(origin));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSLZRW1KH_CLASSNAME, CopiedFallbackPathRoundTripsCorrectly)
* @brief      Regression test for a FIXED finding (see /tmp/work/COMPRESS_REVIEW_FINDINGS.md):
*             CompressionBuffer()'s copy-fallback loop used to invoke
*             "CMPTARGET(true, y+1, source[y++])" as the for-loop's own increment expression, i.e.
*             target[y+1] = source[y++] with no sequence point between the index (y+1) and the
*             side-effecting data argument (source[y++]) -- confirmed live data corruption on this
*             toolchain (compressing {'Q','R','S'} used to drop 'S' and shift 'Q'/'R', producing
*             80 00 51 52 instead of 80 51 52 53), also flagged by the compiler's own
*             "-Wunsequenced" warning. CompressLZRW1KH.cpp now increments 'y' in the for-loop's own
*             increment clause instead of inside the macro call (DecompressionBuffer()'s mirroring
*             loop was fixed the same way), so this now asserts the CORRECT behavior: the payload is
*             copied verbatim and the round trip recovers the original bytes exactly. The same
*             COPIED fallback is what any input that doesn't compress well ends up using (tiny
*             inputs; near-incompressible pseudo-random data), so this is not a narrow corner case.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSLZRW1KH_CLASSNAME, CopiedFallbackPathRoundTripsCorrectly)
{
  XBYTE origin[3] = { 'Q', 'R', 'S' };

  COMPRESS_LZRW1KH compressor;
  XBUFFER compressed;
  compressed.Resize(sizeof(origin) + 64);

  ASSERT_TRUE(compressor.Compress(origin, sizeof(origin), &compressed));

  // CompressedCopyFlagOnUncompressibleTinyInput (below) already confirms the CMPFLAG_COPIED flag
  // byte and the sourcesize+1 total length are correct; this test confirms the payload in between
  // is now correct too.
  ASSERT_EQ(compressed.GetSize(), (XDWORD)(sizeof(origin) + 1));
  EXPECT_EQ(compressed.Get()[0], (XBYTE)0x80); // CMPFLAG_COPIED
  EXPECT_EQ(memcmp(compressed.Get() + 1, origin, sizeof(origin)), 0);

  // ...and, consequently, the round trip through Decompress() now recovers the original bytes.
  COMPRESS_LZRW1KH decompressor;
  XBUFFER decompressed;
  decompressed.Resize(sizeof(origin));

  ASSERT_TRUE(decompressor.Decompress(compressed.Get(), compressed.GetSize(), &decompressed));

  EXPECT_EQ(memcmp(decompressed.Get(), origin, sizeof(origin)), 0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSLZRW1KH_CLASSNAME, FINDING_GetMatchReadsUpToTwoBytesPastSourceForTinyInput)
* @brief      FINDING (see /tmp/work/COMPRESS_REVIEW_FINDINGS.md): COMPRESS_LZRW1KH::GetMatch()
*             (CompressLZRW1KH.cpp) unconditionally reads source[x+1] and source[x+2] to compute its
*             hash value on every iteration of CompressionBuffer()'s main loop, with no check that
*             sourcesize is at least 3 or that x+2 stays within sourcesize -- for a 1- or 2-byte input
*             this reads up to 2 bytes past the logical end of the caller's 'origin' buffer. This is a
*             separate defect from the CMPTARGET unsequenced-modification finding above (that one
*             corrupts the OUTPUT payload; this one over-reads the INPUT). This test allocates
*             'origin' with 2 bytes of trailing padding specifically so the over-read lands on bytes
*             that legitimately belong to this test's own stack array instead of unmapped/poisoned
*             memory, so the test itself does not crash -- the finding is that the real public API
*             (COMPRESS_LZRW1KH::Compress(XBYTE* origin, XDWORD size, ...)) has no such margin: a
*             caller who (correctly, per the documented signature) allocates 'origin' at exactly
*             'size' bytes for a 1- or 2-byte compression hands GetMatch() a real out-of-bounds read.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSLZRW1KH_CLASSNAME, FINDING_GetMatchReadsUpToTwoBytesPastSourceForTinyInput)
{
  COMPRESS_LZRW1KH compressor;

  XBYTE padded1[3] = { 'Q', 0, 0 }; // 2 bytes of padding past the logical 1-byte input
  XBUFFER compressed1;
  compressed1.Resize(64);
  EXPECT_TRUE(compressor.Compress(padded1, 1, &compressed1)); // must not crash

  XBYTE padded2[4] = { 'Q', 'R', 0, 0 }; // 2 bytes of padding past the logical 2-byte input
  XBUFFER compressed2;
  compressed2.Resize(64);
  EXPECT_TRUE(compressor.Compress(padded2, 2, &compressed2)); // must not crash
}


TEST(UNITTESTS_COMPRESSLZRW1KH_CLASSNAME, RoundTrip_EmptyInput)
{
  XBYTE dummy = 0;

  RoundTrip(&dummy, 0);
}


TEST(UNITTESTS_COMPRESSLZRW1KH_CLASSNAME, CompressedCopyFlagOnUncompressibleTinyInput)
{
  // When the compressed representation would not actually be shorter, CompressionBuffer() falls
  // back to a verbatim copy prefixed by CMPFLAG_COPIED (CompressLZRW1KH.cpp: "if(y > sourcesize)"),
  // returning (sourcesize+1). Two distinct bytes is short enough that this fallback always fires.
  COMPRESS_LZRW1KH compressor;

  XBYTE origin[4] = { 'Z', 'Y', 0, 0 }; // padded, see RoundTrip_SmallInputsPaddedForOverreadSafety
  XBUFFER compressed;
  compressed.Resize(64);

  ASSERT_TRUE(compressor.Compress(origin, 2, &compressed));

  EXPECT_EQ(compressed.GetSize(), (XDWORD)3); // sourcesize(2) + 1 flag byte
  EXPECT_EQ(compressed.Get()[0], (XBYTE)0x80); // CMPFLAG_COPIED
}


}
#endif
