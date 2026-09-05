/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_HashWhirlpool.cpp
*
* @class      UNITTESTS_CIPHER_HASHWHIRLPOOL
* @brief      Cipher unit tests for HASHWHIRLPOOL class
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

#include "UnitTests_Cipher_HashWhirlpool.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "HashWhirlpool.h"
#include "XBuffer.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_HASHWHIRLPOOL
{


TEST(UNITTESTS_HASHWHIRLPOOL_CLASSNAME, ResultSizeIsSixtyFourBytes)
{
  HASHWHIRLPOOL hash;

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  EXPECT_EQ(hash.GetDefaultSize(), HASHWHIRLPOOL_DIGESTBYTES);

  XDWORD resultsize = 0;
  XBYTE* result = hash.GetResult(resultsize);
  EXPECT_NE((void*)result, (void*)NULL);
  EXPECT_EQ(resultsize, (XDWORD)HASHWHIRLPOOL_DIGESTBYTES);
}


TEST(UNITTESTS_HASHWHIRLPOOL_CLASSNAME, DeterministicForSameInput)
{
  HASHWHIRLPOOL hash1;
  HASHWHIRLPOOL hash2;

  XBYTE input[] = { 'G','E','N',' ','F','r','a','m','e','W','o','r','k' };

  EXPECT_TRUE(hash1.Do(input, sizeof(input)));
  EXPECT_TRUE(hash2.Do(input, sizeof(input)));

  XSTRING stringhex1;
  XSTRING stringhex2;
  EXPECT_TRUE(hash1.GetResultString(stringhex1));
  EXPECT_TRUE(hash2.GetResultString(stringhex2));

  EXPECT_EQ(0, stringhex1.Compare(stringhex2, true));
}


TEST(UNITTESTS_HASHWHIRLPOOL_CLASSNAME, EmptyAndNonEmptyInputsDiffer)
{
  HASHWHIRLPOOL hashempty;
  HASHWHIRLPOOL hashabc;

  XBYTE input[] = { 'a','b','c' };

  EXPECT_TRUE(hashempty.Do((XBYTE*)NULL, 0));
  EXPECT_TRUE(hashabc.Do(input, sizeof(input)));

  XSTRING stringhexempty;
  XSTRING stringhexabc;
  EXPECT_TRUE(hashempty.GetResultString(stringhexempty));
  EXPECT_TRUE(hashabc.GetResultString(stringhexabc));

  EXPECT_NE(0, stringhexempty.Compare(stringhexabc, true));
}


TEST(UNITTESTS_HASHWHIRLPOOL_CLASSNAME, DoOnBufferMatchesDoOnRawBytes)
{
  HASHWHIRLPOOL hashraw;
  HASHWHIRLPOOL hashbuffer;

  XBYTE input[] = { 'a','b','c' };

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


}
#endif
