/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Compress_CompressBase.cpp
*
* @class      UNITTESTS_COMPRESS_COMPRESSBASE
* @brief      Compress unit tests for COMPRESSBASE class
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

#include "UnitTests_Compress_CompressBase.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CompressBase.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_COMPRESSBASE
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, DefaultConstructorTypeIsNone)
* @brief      COMPRESSBASE::COMPRESSBASE() calls SetType() with its default argument
*             (COMPRESSBASE_TYPE_NONE, CompressBase.h), so a freshly-constructed instance reports
*             COMPRESSBASE_TYPE_NONE from GetType().
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, DefaultConstructorTypeIsNone)
{
  COMPRESSBASE compress;

  EXPECT_EQ(compress.GetType(), COMPRESSBASE_TYPE_NONE);
}


TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, ConstructorWithTypeSetsType)
{
  COMPRESSBASE compress(COMPRESSBASE_TYPE_LZW);

  EXPECT_EQ(compress.GetType(), COMPRESSBASE_TYPE_LZW);
}


TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, SetTypeReturnsAndStoresValue)
{
  COMPRESSBASE compress;

  EXPECT_EQ(compress.SetType(COMPRESSBASE_TYPE_GZ), COMPRESSBASE_TYPE_GZ);
  EXPECT_EQ(compress.GetType(), COMPRESSBASE_TYPE_GZ);
}


TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, SetTypeDefaultArgumentResetsToNone)
{
  COMPRESSBASE compress(COMPRESSBASE_TYPE_ZIP);

  EXPECT_EQ(compress.GetType(), COMPRESSBASE_TYPE_ZIP);

  compress.SetType();

  EXPECT_EQ(compress.GetType(), COMPRESSBASE_TYPE_NONE);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, XBufferCompressIsAPassthroughCopy)
* @brief      COMPRESSBASE::Compress(XBYTE*,XDWORD,XBUFFER*) is documented (CompressBase.cpp) as a no-op
*             passthrough for the base class: it memcpy()s origin straight into buffer->Get() and then
*             SetSize()s the buffer to match -- no actual compression happens at this level (only the
*             concrete COMPRESS_LZW/COMPRESS_LZRW1KH/etc. subclasses implement real algorithms). The
*             caller must pre-size the XBUFFER (Resize()) since XBUFFER::Get() returns NULL for a
*             zero-size buffer (XBuffer.cpp) and would otherwise make the internal memcpy() write into
*             a NULL destination.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, XBufferCompressIsAPassthroughCopy)
{
  COMPRESSBASE compress;

  XBYTE origin[] = { 'a','b','c','d','e' };
  XBUFFER buffer;
  buffer.Resize(sizeof(origin));

  EXPECT_TRUE(compress.Compress(origin, sizeof(origin), &buffer));

  EXPECT_EQ(buffer.GetSize(), (XDWORD)sizeof(origin));
  EXPECT_EQ(memcmp(buffer.Get(), origin, sizeof(origin)), 0);
}


TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, XBufferDecompressIsAPassthroughCopy)
{
  COMPRESSBASE compress;

  XBYTE origin[] = { 'x','y','z' };
  XBUFFER buffer;
  buffer.Resize(sizeof(origin));

  EXPECT_TRUE(compress.Decompress(origin, sizeof(origin), &buffer));

  EXPECT_EQ(buffer.GetSize(), (XDWORD)sizeof(origin));
  EXPECT_EQ(memcmp(buffer.Get(), origin, sizeof(origin)), 0);
}


TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, XBufferCompressRejectsNullOrigin)
{
  COMPRESSBASE compress;
  XBUFFER buffer;
  buffer.Resize(4);

  EXPECT_FALSE(compress.Compress((XBYTE*)NULL, 4, &buffer));
}


TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, XBufferCompressRejectsZeroSize)
{
  COMPRESSBASE compress;
  XBYTE origin[] = { 'a' };
  XBUFFER buffer;
  buffer.Resize(4);

  EXPECT_FALSE(compress.Compress(origin, 0, &buffer));
}


TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, XBufferCompressRejectsNullBuffer)
{
  COMPRESSBASE compress;
  XBYTE origin[] = { 'a' };

  EXPECT_FALSE(compress.Compress(origin, sizeof(origin), (XBUFFER*)NULL));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, ParamVariantCompressAlwaysReturnsFalse)
* @brief      COMPRESSBASE::Compress(XBYTE*,XDWORD,void*) (the byte-callback variant, driving
*             CompressResult() once per input byte) is documented (CompressBase.cpp) to end with an
*             unconditional "return false;" even when every CompressResult() call along the way trivially
*             succeeds (the base CompressResult() itself also always returns false, its two branches
*             being empty stubs) -- so this overload can never report success at the COMPRESSBASE level.
*             Confirmed real behavior, not merely read from source.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, ParamVariantCompressAlwaysReturnsFalse)
{
  COMPRESSBASE compress;
  XBYTE origin[] = { 'a','b','c' };

  EXPECT_FALSE(compress.Compress(origin, sizeof(origin), (void*)NULL));
}


TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, ParamVariantDecompressAlwaysReturnsFalse)
{
  COMPRESSBASE compress;
  XBYTE origin[] = { 'a','b','c' };

  EXPECT_FALSE(compress.Decompress(origin, sizeof(origin), (void*)NULL));
}


TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, ParamVariantCompressRejectsNullOrigin)
{
  COMPRESSBASE compress;

  EXPECT_FALSE(compress.Compress((XBYTE*)NULL, 3, (void*)NULL));
}


TEST(UNITTESTS_COMPRESSBASE_CLASSNAME, CompressResultBaseAlwaysReturnsFalse)
{
  COMPRESSBASE compress;

  EXPECT_FALSE(compress.CompressResult(true, 'a', (void*)NULL));
  EXPECT_FALSE(compress.CompressResult(false, 'a', (void*)NULL));
}


}
#endif
