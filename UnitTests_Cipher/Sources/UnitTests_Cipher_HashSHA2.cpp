/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_HashSHA2.cpp
*
* @class      UNITTESTS_CIPHER_HASHSHA2
* @brief      Cipher unit tests for HASHSHA2 class
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

#include "UnitTests_Cipher_HashSHA2.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "HashSHA2.h"
#include "XBuffer.h"
#include "XString.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_HASHSHA2
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHSHA2_CLASSNAME, KnownAnswerVector_SHA256_abc)
* @brief      FIPS 180-4 test vector: SHA-256("abc") =
*             ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHSHA2_CLASSNAME, KnownAnswerVector_SHA256_abc)
{
  HASHSHA2 hash(HASHSHA2TYPE_256);

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  EXPECT_EQ(hash.GetDefaultSize(), HASHSHA2_256_DIGEST_SIZE);

  XSTRING stringhex;
  EXPECT_TRUE(hash.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("ba7816bf8f01cfea414140de5dae2223b00361a396177a9cb410ff61f20015ad"), true));
}


TEST(UNITTESTS_HASHSHA2_CLASSNAME, KnownAnswerVector_SHA256_EmptyString)
{
  HASHSHA2 hash(HASHSHA2TYPE_256);

  EXPECT_TRUE(hash.Do((XBYTE*)NULL, 0));

  XSTRING stringhex;
  EXPECT_TRUE(hash.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("e3b0c44298fc1c149afbf4c8996fb92427ae41e4649b934ca495991b7852b855"), true));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHSHA2_CLASSNAME, KnownAnswerVector_SHA224_abc)
* @brief      FIPS 180-4 test vector: SHA-224("abc") = 23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHSHA2_CLASSNAME, KnownAnswerVector_SHA224_abc)
{
  HASHSHA2 hash(HASHSHA2TYPE_224);

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  EXPECT_EQ(hash.GetDefaultSize(), HASHSHA2_224_DIGEST_SIZE);

  XSTRING stringhex;
  EXPECT_TRUE(hash.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("23097d223405d8228642a477bda255b32aadbce4bda0b3f7e36c9da7"), true));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHSHA2_CLASSNAME, KnownAnswerVector_SHA384_abc)
* @brief      FIPS 180-4 test vector: SHA-384("abc") =
*             cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHSHA2_CLASSNAME, KnownAnswerVector_SHA384_abc)
{
  HASHSHA2 hash(HASHSHA2TYPE_384);

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  EXPECT_EQ(hash.GetDefaultSize(), HASHSHA2_384_DIGEST_SIZE);

  XSTRING stringhex;
  EXPECT_TRUE(hash.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("cb00753f45a35e8bb5a03d699ac65007272c32ab0eded1631a8b605a43ff5bed8086072ba1e7cc2358baeca134c825a7"), true));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHSHA2_CLASSNAME, KnownAnswerVector_SHA512_abc)
* @brief      FIPS 180-4 test vector: SHA-512("abc") =
*             ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHSHA2_CLASSNAME, KnownAnswerVector_SHA512_abc)
{
  HASHSHA2 hash(HASHSHA2TYPE_512);

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  EXPECT_EQ(hash.GetDefaultSize(), HASHSHA2_512_DIGEST_SIZE);

  XSTRING stringhex;
  EXPECT_TRUE(hash.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("ddaf35a193617abacc417349ae20413112e6fa4e89a97ea20a9eeee64b55d39a2192992a274fc1a836ba3c23a3feebbd454d4423643ce80e2a9ac94fa54ca49f"), true));
}


}
#endif
