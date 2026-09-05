/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_HashCRC16.cpp
*
* @class      UNITTESTS_CIPHER_HASHCRC16
* @brief      Cipher unit tests for HASHCRC16 class
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

#include "UnitTests_Cipher_HashCRC16.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "HashCRC16.h"
#include "XBuffer.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_HASHCRC16
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHCRC16_CLASSNAME, KnownAnswerVector_123456789)
* @brief      Verifies HASHCRC16::Do() against the standard CRC-16/ARC check value for the ASCII string
*             "123456789" (0xBB3D) -- the table in HashCRC16.cpp (0x0000,0xC0C1,0xC181,... with an initial
*             value of 0x0000 and no output XOR, both confirmed by reading HashCRC16.cpp) is the well known
*             reflected CRC-16 lookup table for polynomial 0x8005 (CRC-16/ARC, a.k.a. CRC-16/IBM).
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHCRC16_CLASSNAME, KnownAnswerVector_123456789)
{
  HASHCRC16 hash;

  XBYTE input[] = { '1','2','3','4','5','6','7','8','9' };

  EXPECT_TRUE(hash.Do(input, sizeof(input)));
  EXPECT_EQ(hash.GetResultCRC16(), (XWORD)0xBB3D);
}


TEST(UNITTESTS_HASHCRC16_CLASSNAME, EmptyInputIsRejected)
{
  // HASHCRC16::Do() documents "if(!size) return false;" (HashCRC16.cpp) -- a zero-size request is
  // rejected, unlike XRAND::Generate()'s documented zero-size no-op success. Confirmed real
  // behavior, not assumed.
  HASHCRC16 hash;

  EXPECT_FALSE(hash.Do((XBYTE*)NULL, 0));
  EXPECT_EQ(hash.GetResultCRC16(), (XWORD)0x0000);
}


TEST(UNITTESTS_HASHCRC16_CLASSNAME, ResultSizeAndTypeAreCoherent)
{
  HASHCRC16 hash;

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));

  EXPECT_EQ(hash.GetDefaultSize(), 2);

  XDWORD resultsize = 0;
  XBYTE* result = hash.GetResult(resultsize);
  EXPECT_NE((void*)result, (void*)NULL);
  EXPECT_EQ(resultsize, (XDWORD)2);
}


TEST(UNITTESTS_HASHCRC16_CLASSNAME, ResetResultBackToZero)
{
  HASHCRC16 hash;

  XBYTE input[] = { 'a','b','c' };
  EXPECT_TRUE(hash.Do(input, sizeof(input)));
  EXPECT_NE(hash.GetResultCRC16(), (XWORD)0x0000);

  EXPECT_TRUE(hash.ResetResult());
  EXPECT_EQ(hash.GetResultCRC16(), (XWORD)0x0000);
}


TEST(UNITTESTS_HASHCRC16_CLASSNAME, DoOnBufferMatchesDoOnRawBytes)
{
  HASHCRC16 hashraw;
  HASHCRC16 hashbuffer;

  XBYTE input[] = { 'G','E','N',' ','F','r','a','m','e','W','o','r','k' };

  EXPECT_TRUE(hashraw.Do(input, sizeof(input)));

  XBUFFER xbuffer;
  xbuffer.Add(input, sizeof(input));
  EXPECT_TRUE(hashbuffer.Do(xbuffer));

  EXPECT_EQ(hashraw.GetResultCRC16(), hashbuffer.GetResultCRC16());
}


}
#endif
