/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_HashCOMP128v1.cpp
*
* @class      UNITTESTS_CIPHER_HASHCOMP128V1
* @brief      Cipher unit tests for HASHCOMP128V1 class
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

#include "UnitTests_Cipher_HashCOMP128v1.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "HashCOMP128v1.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_HASHCOMP128V1
{


// NOTE: no third-party COMP128v1 (GSM A3/A8) known-answer vector was hand-verified for this batch
// (unlike MD5/SHA1/SHA2, whose FIPS/RFC vectors are short and unambiguous), so these tests exercise
// structural contracts (fixed output sizes, determinism, sensitivity to the key) rather than a
// specific hard-coded SRES/Kc pair -- consistent with this project's rule of only asserting values
// that were actually confirmed, rather than a value that merely "looks right".
TEST(UNITTESTS_HASHCOMP128V1_CLASSNAME, DoRejectsWrongInputSize)
{
  HASHCOMP128V1 hash;

  XBYTE tooshort[8];
  memset(tooshort, 0, sizeof(tooshort));

  EXPECT_FALSE(hash.Do(tooshort, sizeof(tooshort)));
}


TEST(UNITTESTS_HASHCOMP128V1_CLASSNAME, DoProducesSRESAndKcOfDocumentedSize)
{
  HASHCOMP128V1 hash;

  XBYTE rand[HASHCOMP128V1_RAND_SIZE];
  XBYTE ki[HASHCOMP128V1_KI_SIZE];
  for(int c=0; c<HASHCOMP128V1_RAND_SIZE; c++) rand[c] = (XBYTE)c;
  for(int c=0; c<HASHCOMP128V1_KI_SIZE;   c++) ki[c]   = (XBYTE)(0xF0 + c);

  XBUFFER input;
  EXPECT_TRUE(hash.SetInput(rand, ki, input));
  EXPECT_EQ(input.GetSize(), (XDWORD)(HASHCOMP128V1_RAND_SIZE + HASHCOMP128V1_KI_SIZE));

  EXPECT_TRUE(hash.Do(input.Get(), input.GetSize()));
  EXPECT_EQ(hash.GetDefaultSize(), HASHCOMP128V1_RESULT_SIZE);

  XBUFFER sres;
  XBUFFER kc;
  EXPECT_TRUE(hash.GetSRES(sres));
  EXPECT_TRUE(hash.GetKc(kc));

  EXPECT_EQ(sres.GetSize(), (XDWORD)HASHCOMP128V1_SRES_SIZE);
  EXPECT_EQ(kc.GetSize(), (XDWORD)HASHCOMP128V1_KC_SIZE);
}


TEST(UNITTESTS_HASHCOMP128V1_CLASSNAME, DeterministicForSameRandAndKi)
{
  HASHCOMP128V1 hash1;
  HASHCOMP128V1 hash2;

  XBYTE rand[HASHCOMP128V1_RAND_SIZE];
  XBYTE ki[HASHCOMP128V1_KI_SIZE];
  for(int c=0; c<HASHCOMP128V1_RAND_SIZE; c++) rand[c] = (XBYTE)(c * 3);
  for(int c=0; c<HASHCOMP128V1_KI_SIZE;   c++) ki[c]   = (XBYTE)(c * 5);

  XBUFFER input1;
  XBUFFER input2;
  EXPECT_TRUE(hash1.SetInput(rand, ki, input1));
  EXPECT_TRUE(hash2.SetInput(rand, ki, input2));

  EXPECT_TRUE(hash1.Do(input1.Get(), input1.GetSize()));
  EXPECT_TRUE(hash2.Do(input2.Get(), input2.GetSize()));

  XBUFFER sres1, sres2;
  EXPECT_TRUE(hash1.GetSRES(sres1));
  EXPECT_TRUE(hash2.GetSRES(sres2));

  ASSERT_EQ(sres1.GetSize(), sres2.GetSize());
  EXPECT_EQ(0, memcmp(sres1.Get(), sres2.Get(), sres1.GetSize()));
}


TEST(UNITTESTS_HASHCOMP128V1_CLASSNAME, DifferentKiProducesDifferentSRES)
{
  HASHCOMP128V1 hash1;
  HASHCOMP128V1 hash2;

  XBYTE rand[HASHCOMP128V1_RAND_SIZE];
  XBYTE ki1[HASHCOMP128V1_KI_SIZE];
  XBYTE ki2[HASHCOMP128V1_KI_SIZE];
  for(int c=0; c<HASHCOMP128V1_RAND_SIZE; c++) rand[c] = (XBYTE)c;
  for(int c=0; c<HASHCOMP128V1_KI_SIZE;   c++) { ki1[c] = 0x00; ki2[c] = 0xFF; }

  XBUFFER input1;
  XBUFFER input2;
  EXPECT_TRUE(hash1.SetInput(rand, ki1, input1));
  EXPECT_TRUE(hash2.SetInput(rand, ki2, input2));

  EXPECT_TRUE(hash1.Do(input1.Get(), input1.GetSize()));
  EXPECT_TRUE(hash2.Do(input2.Get(), input2.GetSize()));

  XBUFFER sres1, sres2;
  EXPECT_TRUE(hash1.GetSRES(sres1));
  EXPECT_TRUE(hash2.GetSRES(sres2));

  ASSERT_EQ(sres1.GetSize(), sres2.GetSize());
  EXPECT_NE(0, memcmp(sres1.Get(), sres2.Get(), sres1.GetSize()));
}


}
#endif
