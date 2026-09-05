/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_HashMD5.cpp
*
* @class      UNITTESTS_CIPHER_HASHMD5
* @brief      Cipher unit tests for HASHMD5 class
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

#include "UnitTests_Cipher_HashMD5.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "HashMD5.h"
#include "XBuffer.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_HASHMD5
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHMD5_CLASSNAME, KnownAnswerVector_EmptyString)
* @brief      RFC 1321 test vector: MD5("") = d41d8cd98f00b204e9800998ecf8427e.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHMD5_CLASSNAME, KnownAnswerVector_EmptyString)
{
  HASHMD5 hash;

  EXPECT_TRUE(hash.Do((XBYTE*)NULL, 0));

  XSTRING stringhex;
  EXPECT_TRUE(hash.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("d41d8cd98f00b204e9800998ecf8427e"), true));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHMD5_CLASSNAME, KnownAnswerVector_abc)
* @brief      RFC 1321 test vector: MD5("abc") = 900150983cd24fb0d6963f7d28e17f72.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHMD5_CLASSNAME, KnownAnswerVector_abc)
{
  HASHMD5 hash;

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  XSTRING stringhex;
  EXPECT_TRUE(hash.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("900150983cd24fb0d6963f7d28e17f72"), true));
}


TEST(UNITTESTS_HASHMD5_CLASSNAME, ResultSizeIsSixteenBytes)
{
  HASHMD5 hash;

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  EXPECT_EQ(hash.GetDefaultSize(), 16);

  XDWORD resultsize = 0;
  XBYTE* result = hash.GetResult(resultsize);
  EXPECT_NE((void*)result, (void*)NULL);
  EXPECT_EQ(resultsize, (XDWORD)16);
}


TEST(UNITTESTS_HASHMD5_CLASSNAME, DoOnBufferMatchesDoOnRawBytes)
{
  HASHMD5 hashraw;
  HASHMD5 hashbuffer;

  XBYTE input[] = { 'G','E','N',' ','F','r','a','m','e','W','o','r','k' };

  EXPECT_TRUE(hashraw.Do(input, sizeof(input)));

  XBUFFER xbuffer;
  xbuffer.Add(input, sizeof(input));
  EXPECT_TRUE(hashbuffer.Do(xbuffer));

  XSTRING stringhexraw;
  XSTRING stringhexbuffer;
  EXPECT_TRUE(hashraw.GetResultString(stringhexraw));
  EXPECT_TRUE(hashbuffer.GetResultString(stringhexbuffer));

  EXPECT_EQ(0, stringhexraw.Compare(stringhexbuffer, true));
}


TEST(UNITTESTS_HASHMD5_CLASSNAME, DifferentInputsProduceDifferentDigest)
{
  HASHMD5 hash1;
  HASHMD5 hash2;

  XBYTE input1[] = { 'a','b','c' };
  XBYTE input2[] = { 'a','b','d' };

  EXPECT_TRUE(hash1.Do(input1, sizeof(input1)));
  EXPECT_TRUE(hash2.Do(input2, sizeof(input2)));

  XSTRING stringhex1;
  XSTRING stringhex2;
  EXPECT_TRUE(hash1.GetResultString(stringhex1));
  EXPECT_TRUE(hash2.GetResultString(stringhex2));

  EXPECT_NE(0, stringhex1.Compare(stringhex2, true));
}


}
#endif
