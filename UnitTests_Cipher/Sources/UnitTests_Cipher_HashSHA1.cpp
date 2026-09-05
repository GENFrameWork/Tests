/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_HashSHA1.cpp
*
* @class      UNITTESTS_CIPHER_HASHSHA1
* @brief      Cipher unit tests for HASHSHA1 class
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

#include "UnitTests_Cipher_HashSHA1.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "HashSHA1.h"
#include "XBuffer.h"
#include "XString.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_HASHSHA1
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHSHA1_CLASSNAME, KnownAnswerVector_EmptyString)
* @brief      FIPS 180 test vector: SHA1("") = da39a3ee5e6b4b0d3255bfef95601890afd80709.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHSHA1_CLASSNAME, KnownAnswerVector_EmptyString)
{
  HASHSHA1 hash;

  EXPECT_TRUE(hash.Do((XBYTE*)NULL, 0));

  XSTRING stringhex;
  EXPECT_TRUE(hash.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("da39a3ee5e6b4b0d3255bfef95601890afd80709"), true));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHSHA1_CLASSNAME, KnownAnswerVector_abc)
* @brief      FIPS 180 test vector: SHA1("abc") = a9993e364706816aba3e25717850c26c9cd0d89.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHSHA1_CLASSNAME, KnownAnswerVector_abc)
{
  HASHSHA1 hash;

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  XSTRING stringhex;
  EXPECT_TRUE(hash.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("a9993e364706816aba3e25717850c26c9cd0d89d"), true));
}


TEST(UNITTESTS_HASHSHA1_CLASSNAME, ResultSizeIsTwentyBytes)
{
  HASHSHA1 hash;

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  EXPECT_EQ(hash.GetDefaultSize(), 20);

  XDWORD resultsize = 0;
  XBYTE* result = hash.GetResult(resultsize);
  EXPECT_NE((void*)result, (void*)NULL);
  EXPECT_EQ(resultsize, (XDWORD)20);
}


TEST(UNITTESTS_HASHSHA1_CLASSNAME, MultiBlockMessageMatchesKnownVector)
{
  // FIPS 180 two-block test vector (fed as raw ASCII bytes, to stay independent of XSTRING's
  // internal wide-character encoding).
  HASHSHA1 hash;

  const char* input = "abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq";

  EXPECT_TRUE(hash.Do((XBYTE*)input, (XQWORD)strlen(input)));

  XSTRING stringhex;
  EXPECT_TRUE(hash.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("84983e441c3bd26ebaae4aa1f95129e5e54670f1"), true));
}


}
#endif
