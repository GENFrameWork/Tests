/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherDES.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERDES
* @brief      Cipher unit tests for CIPHERDES class
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

#include "UnitTests_Cipher_CipherDES.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherDES.h"
#include "CipherKeySymmetrical.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERDES
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_CIPHERDES_CLASSNAME, KnownAnswerVector_ECB)
* @brief      Classic textbook DES known-answer single-block test vector: key = 133457799BBCDFF1,
*             plaintext = 0123456789ABCDEF, ciphertext = 85E813540F0AB405 (FIPS 46-3 style example,
*             widely reproduced e.g. in the original DES specification worked example).
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_CIPHERDES_CLASSNAME, KnownAnswerVector_ECB)
{
  CIPHERDES cipher;

  XBYTE keybytes[8] = { 0x13,0x34,0x57,0x79,0x9B,0xBC,0xDF,0xF1 };
  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  cipher.SetChainingMode(CIPHERCHAININGMODE_ECB);
  ASSERT_TRUE(cipher.SetKey(&key));

  XBYTE plaintext[8] = { 0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF };

  EXPECT_TRUE(cipher.Cipher(plaintext, sizeof(plaintext)));

  XBUFFER* result = cipher.GetResult();
  ASSERT_NE(result, (XBUFFER*)NULL);
  ASSERT_EQ(result->GetSize(), (XDWORD)8);

  XBYTE expected[8] = { 0x85,0xE8,0x13,0x54,0x0F,0x0A,0xB4,0x05 };
  EXPECT_EQ(0, memcmp(result->Get(), expected, 8));
}


TEST(UNITTESTS_CIPHERDES_CLASSNAME, CipherThenUncipherRoundtripCBC)
{
  XBYTE keybytes[8] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 };
  XBYTE ivbytes[8]  = { 0x10,0x20,0x30,0x40,0x50,0x60,0x70,0x80 };
  XBYTE plaintext[16] = { 'G','E','N',' ','F','r','a','m','e','w','o','r','k','!','!','\0' };

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHERDES ciphercipher;
  ciphercipher.SetChainingMode(CIPHERCHAININGMODE_CBC);
  ASSERT_TRUE(ciphercipher.SetInitVector(ivbytes, sizeof(ivbytes)));
  ASSERT_TRUE(ciphercipher.SetKey(&key));
  ASSERT_TRUE(ciphercipher.Cipher(plaintext, sizeof(plaintext)));

  XBUFFER ciphertext(*ciphercipher.GetResult());

  CIPHERDES cipheruncipher;
  cipheruncipher.SetChainingMode(CIPHERCHAININGMODE_CBC);
  ASSERT_TRUE(cipheruncipher.SetInitVector(ivbytes, sizeof(ivbytes)));
  ASSERT_TRUE(cipheruncipher.SetKey(&key));
  ASSERT_TRUE(cipheruncipher.Uncipher(ciphertext));

  XBUFFER* result = cipheruncipher.GetResult();
  ASSERT_NE(result, (XBUFFER*)NULL);
  ASSERT_EQ(result->GetSize(), (XDWORD)sizeof(plaintext));
  EXPECT_EQ(0, memcmp(result->Get(), plaintext, sizeof(plaintext)));
}


TEST(UNITTESTS_CIPHERDES_CLASSNAME, CipherWithoutKeyFails)
{
  CIPHERDES cipher;

  XBYTE plaintext[8] = { 0,1,2,3,4,5,6,7 };
  EXPECT_FALSE(cipher.Cipher(plaintext, sizeof(plaintext)));
}


}
#endif
