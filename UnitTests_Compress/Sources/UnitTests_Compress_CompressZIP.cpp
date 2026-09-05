/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Compress_CompressZIP.cpp
*
* @class      UNITTESTS_COMPRESS_COMPRESSZIP
* @brief      Compress unit tests for COMPRESS_ZIP class
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

#include "UnitTests_Compress_CompressZIP.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CompressZIP.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_COMPRESSZIP
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
* @fn         TEST(UNITTESTS_COMPRESSZIP_CLASSNAME, ClassNameIsMisleadingItIsPlainDeflateNotAZipContainer)
* @brief      FINDING (see /tmp/work/COMPRESS_REVIEW_FINDINGS.md): despite the class name COMPRESS_ZIP
*             and despite minizip's zip.c/unzip.c being compiled into every build that turns on
*             COMPRESS_ZIP_FEATURE (THIRDPARTYLIBRARIES_ZLIB_FEATURE, GEN_Main_Sources_ThirdPartyLibraries.cmake),
*             CompressZIP.cpp's ZCompress()/ZDecompress() call plain zlib deflateInit()/inflateInit()
*             directly -- the same raw zlib primitives COMPRESS_DEFLATE uses -- and never call any
*             minizip zipOpen()/unzOpen() functions. The output is therefore a bare zlib-wrapped deflate
*             stream, NOT a .zip archive: it carries none of the local/central-directory file headers
*             a real .zip needs (PK\x03\x04 / PK\x01\x02 / PK\x05\x06, per the ZIP file format spec),
*             so it cannot be opened by any actual zip-aware tool, and the linked-in minizip object
*             code is dead weight for this class.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSZIP_CLASSNAME, ClassNameIsMisleadingItIsPlainDeflateNotAZipContainer)
{
  COMPRESS_ZIP compressor;

  XBYTE origin[64];
  memset(origin, 'H', sizeof(origin));

  XBUFFER compressed;
  ASSERT_TRUE(compressor.Compress(origin, sizeof(origin), &compressed));
  ASSERT_GE(compressed.GetSize(), (XDWORD)4);

  // Real ZIP local file header magic (PK\x03\x04) never appears -- this is a raw zlib stream
  // (CMF/FLG header, method nibble 8 = deflate).
  bool haszipmagic = (compressed.Get()[0] == 'P') && (compressed.Get()[1] == 'K');
  EXPECT_FALSE(haszipmagic);

  EXPECT_EQ(compressed.Get()[0] & 0x0F, (XBYTE)8);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSZIP_CLASSNAME, RoundTrip_CompressibleDataWithinDestinationCapacity)
* @brief      Demonstrates the one usage pattern COMPRESS_ZIP actually supports correctly: input
*             compressible enough that the deflate output fits within Compress()'s
*             xbuffer->Resize(size) destination capacity (exactly 'size' bytes, CompressZIP.cpp), and
*             a Decompress() target the caller has pre-sized (via Resize()) to exactly the known
*             original length -- Decompress() (CompressZIP.cpp) uses xbuffer->GetSize() as the
*             inflate() destination capacity and never grows/shrinks it itself.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSZIP_CLASSNAME, RoundTrip_CompressibleDataWithinDestinationCapacity)
{
  COMPRESS_ZIP compressor;

  XBYTE origin[2048];
  memset(origin, 'I', sizeof(origin));

  XBUFFER compressed;
  ASSERT_TRUE(compressor.Compress(origin, sizeof(origin), &compressed));
  ASSERT_GT(compressed.GetSize(), (XDWORD)0);
  ASSERT_LT(compressed.GetSize(), (XDWORD)sizeof(origin)); // must actually have shrunk to fit

  COMPRESS_ZIP decompressor;
  XBUFFER decompressed;
  decompressed.Resize(sizeof(origin));

  ASSERT_TRUE(decompressor.Decompress(compressed.Get(), compressed.GetSize(), &decompressed));
  EXPECT_EQ(memcmp(decompressed.Get(), origin, sizeof(origin)), 0);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSZIP_CLASSNAME, FINDING_CompressSilentlyCorruptsWhenDestinationTooSmall)
* @brief      FINDING (see /tmp/work/COMPRESS_REVIEW_FINDINGS.md): COMPRESS_ZIP::Compress()
*             (CompressZIP.cpp) always Resize()s its destination to exactly 'size' bytes ("XDWORD csize
*             = size; ZCompress(xbuffer->Get(), &csize, source, size);") with zero slack for deflate's
*             per-stream overhead (zlib 2-byte header + deflate stored-block headers + 4-byte Adler-32
*             trailer -- at least ~11 bytes even for maximally-compressible input, RFC 1950/1951), and
*             then IGNORES ZCompress()'s int return value entirely -- Compress() unconditionally
*             "return true;" regardless of whether ZCompress() reported Z_OK or Z_BUF_ERROR. Separately,
*             ZCompress()'s own retry loop ("do{ stream.next_out = target; stream.avail_out = destlen;
*             ... } while(stream.avail_out == 0);") resets next_out back to the START of 'target' on
*             every iteration instead of advancing past what was already written, so on the rare
*             occasion the loop does iterate more than once, each pass overwrites the previous one
*             rather than continuing it -- there is no code path where a destination that was too
*             small on the first pass ever ends up holding the correct output on a later pass.
*             With pseudo-random (incompressible) input sized so its compressed form cannot fit in
*             'size' bytes, this test demonstrates the practical consequence: Compress() still reports
*             success (returns true) while xbuffer ends up holding truncated/wrong data that a
*             Decompress() sized to the true original length either fails to reproduce, or itself
*             mismatches -- Compress()'s bool return value cannot be trusted to detect this failure
*             mode at all.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSZIP_CLASSNAME, FINDING_CompressSilentlyCorruptsWhenDestinationTooSmall)
{
  COMPRESS_ZIP compressor;

  // A small pseudo-random buffer: its deflate-compressed form (zlib header + stored block(s) +
  // Adler-32 trailer) cannot fit inside a destination exactly 'size' bytes long.
  XBYTE origin[16];
  FillPseudoRandom(origin, sizeof(origin), 0xAAAA5555);

  XBUFFER compressed;

  // Compress() reports success unconditionally...
  EXPECT_TRUE(compressor.Compress(origin, sizeof(origin), &compressed));

  // ...but round-tripping what it produced through a correctly-sized Decompress() does not
  // reliably recover the original bytes, proving the "true" return value above is not trustworthy.
  COMPRESS_ZIP decompressor;
  XBUFFER decompressed;
  decompressed.Resize(sizeof(origin));

  decompressor.Decompress(compressed.Get(), compressed.GetSize(), &decompressed);

  bool roundtripmatches = (memcmp(decompressed.Get(), origin, sizeof(origin)) == 0);
  EXPECT_FALSE(roundtripmatches)
    << "If this ever fails, zlib's per-stream overhead for this particular input happened to fit "
       "in 16 bytes despite the missing slack -- widen 'origin' or re-seed FillPseudoRandom() so "
       "the compressed form provably exceeds the destination capacity again.";
}


TEST(UNITTESTS_COMPRESSZIP_CLASSNAME, CompressRejectsNullSource)
{
  COMPRESS_ZIP compressor;
  XBUFFER buffer;

  EXPECT_FALSE(compressor.Compress((XBYTE*)NULL, 4, &buffer));
}


TEST(UNITTESTS_COMPRESSZIP_CLASSNAME, CompressRejectsZeroSize)
{
  COMPRESS_ZIP compressor;
  XBYTE origin[] = { 'a' };
  XBUFFER buffer;

  EXPECT_FALSE(compressor.Compress(origin, 0, &buffer));
}


TEST(UNITTESTS_COMPRESSZIP_CLASSNAME, CompressRejectsNullBuffer)
{
  COMPRESS_ZIP compressor;
  XBYTE origin[] = { 'a' };

  EXPECT_FALSE(compressor.Compress(origin, sizeof(origin), (XBUFFER*)NULL));
}


}
#endif
