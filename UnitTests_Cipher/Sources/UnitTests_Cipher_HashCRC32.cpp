/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_HashCRC32.cpp
*
* @class      UNITTESTS_CIPHER_HASHCRC32
* @brief      Cipher unit tests for HASHCRC32 class
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

#include "UnitTests_Cipher_HashCRC32.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "HashCRC32.h"
#include "XBuffer.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_HASHCRC32
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHCRC32_CLASSNAME, KnownAnswerVector_123456789)
* @brief      Verifies HASHCRC32::Do() against the standard CRC-32 (IEEE 802.3 / zlib) check value for
*             "123456789" (0xCBF43926) -- HASHCRC32_INI is 0xEDB88320 (HashCRC32.cpp), the canonical
*             reflected polynomial representation of the standard CRC-32 algorithm.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHCRC32_CLASSNAME, KnownAnswerVector_123456789)
{
  HASHCRC32 hash;

  XBYTE input[] = { '1','2','3','4','5','6','7','8','9' };

  EXPECT_TRUE(hash.Do(input, sizeof(input)));
  EXPECT_EQ(hash.GetResultCRC32(), (XDWORD)0xCBF43926);
}


TEST(UNITTESTS_HASHCRC32_CLASSNAME, EmptyInputIsRejected)
{
  // HASHCRC32::Do() documents "if(!size) return false;" (HashCRC32.cpp) -- confirmed real behavior.
  HASHCRC32 hash;

  EXPECT_FALSE(hash.Do((XBYTE*)NULL, 0));
  EXPECT_EQ(hash.GetResultCRC32(), (XDWORD)0x00000000);
}


TEST(UNITTESTS_HASHCRC32_CLASSNAME, ResultSizeIsFourBytes)
{
  HASHCRC32 hash;

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  EXPECT_EQ(hash.GetDefaultSize(), 4);

  XDWORD resultsize = 0;
  XBYTE* result = hash.GetResult(resultsize);
  EXPECT_NE((void*)result, (void*)NULL);
  EXPECT_EQ(resultsize, (XDWORD)4);
}


TEST(UNITTESTS_HASHCRC32_CLASSNAME, ResetResultBackToZero)
{
  HASHCRC32 hash;

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));
  EXPECT_NE(hash.GetResultCRC32(), (XDWORD)0x00000000);

  EXPECT_TRUE(hash.ResetResult());
  EXPECT_EQ(hash.GetResultCRC32(), (XDWORD)0x00000000);
}


TEST(UNITTESTS_HASHCRC32_CLASSNAME, GetResultStringProducesHexDigits)
{
  HASHCRC32 hash;

  XBYTE input[] = { '1','2','3','4','5','6','7','8','9' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  XSTRING stringhex;
  EXPECT_TRUE(hash.GetResultString(stringhex));
  EXPECT_GT(stringhex.GetSize(), (XDWORD)0);
}


}
#endif
