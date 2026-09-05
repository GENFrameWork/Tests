/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_HashCKS16.cpp
*
* @class      UNITTESTS_CIPHER_HASHCKS16
* @brief      Cipher unit tests for HASHCKS16 class
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

#include "UnitTests_Cipher_HashCKS16.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "HashCKS16.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_HASHCKS16
{


TEST(UNITTESTS_HASHCKS16_CLASSNAME, DeterministicForSameInput)
{
  HASHCKS16 hash1;
  HASHCKS16 hash2;

  XBYTE input[] = { 'G','E','N',' ','C','i','p','h','e','r' };

  EXPECT_TRUE(hash1.Do(input, sizeof(input)));
  EXPECT_TRUE(hash2.Do(input, sizeof(input)));

  EXPECT_EQ(hash1.GetResultCKS16(), hash2.GetResultCKS16());
}


TEST(UNITTESTS_HASHCKS16_CLASSNAME, DifferentInputsLikelyDifferentChecksum)
{
  HASHCKS16 hash1;
  HASHCKS16 hash2;

  XBYTE input1[] = { 'A','B','C' };
  XBYTE input2[] = { 'X','Y','Z' };

  EXPECT_TRUE(hash1.Do(input1, sizeof(input1)));
  EXPECT_TRUE(hash2.Do(input2, sizeof(input2)));

  EXPECT_NE(hash1.GetResultCKS16(), hash2.GetResultCKS16());
}


TEST(UNITTESTS_HASHCKS16_CLASSNAME, ResultSizeIsTwoBytes)
{
  HASHCKS16 hash;

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  EXPECT_EQ(hash.GetDefaultSize(), 2);

  XDWORD resultsize = 0;
  XBYTE* result = hash.GetResult(resultsize);
  EXPECT_NE((void*)result, (void*)NULL);
  EXPECT_EQ(resultsize, (XDWORD)2);
}


TEST(UNITTESTS_HASHCKS16_CLASSNAME, ResetResultBackToZero)
{
  HASHCKS16 hash;

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  EXPECT_TRUE(hash.ResetResult());
  EXPECT_EQ(hash.GetResultCKS16(), (XWORD)0x0000);
}


TEST(UNITTESTS_HASHCKS16_CLASSNAME, EmptyInputIsRejected)
{
  // HASHCKS16::Do() documents "if(!size) return false;" (HashCKS16.cpp) -- confirmed real behavior.
  HASHCKS16 hash;

  EXPECT_FALSE(hash.Do((XBYTE*)NULL, 0));
}


}
#endif
