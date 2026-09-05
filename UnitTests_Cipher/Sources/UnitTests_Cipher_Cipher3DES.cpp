/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_Cipher3DES.cpp
*
* @class      UNITTESTS_CIPHER_CIPHER3DES
* @brief      Cipher unit tests for CIPHER3DES class
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

#include "UnitTests_Cipher_Cipher3DES.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "Cipher3DES.h"
#include "CipherKeySymmetrical.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHER3DES
{


// NOTE: no hand-verified NIST 3DES known-answer vector is used here (unlike CIPHERDES's textbook
// single-DES vector) -- per this project's round-trip-first policy for the less trivial algorithms,
// correctness is exercised via Cipher()/Uncipher() round trips instead of a hard-coded ciphertext.
TEST(UNITTESTS_CIPHER3DES_CLASSNAME, CipherThenUncipherRoundtrip_TripleKeyCBC)
{
  XBYTE keybytes[24];
  for(int c=0; c<24; c++) keybytes[c] = (XBYTE)(c + 1);

  XBYTE ivbytes[8] = { 0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08 };
  XBYTE plaintext[16] = { 'T','r','i','p','l','e',' ','D','E','S',' ','t','e','s','t','!' };

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHER3DES ciphercipher;
  ciphercipher.SetChainingMode(CIPHERCHAININGMODE_CBC);
  ASSERT_TRUE(ciphercipher.SetInitVector(ivbytes, sizeof(ivbytes)));
  ASSERT_TRUE(ciphercipher.SetKey(&key));
  ASSERT_TRUE(ciphercipher.Cipher(plaintext, sizeof(plaintext)));

  XBUFFER ciphertext(*ciphercipher.GetResult());
  EXPECT_EQ(ciphertext.GetSize(), (XDWORD)sizeof(plaintext));
  EXPECT_NE(0, memcmp(ciphertext.Get(), plaintext, sizeof(plaintext)));

  CIPHER3DES cipheruncipher;
  cipheruncipher.SetChainingMode(CIPHERCHAININGMODE_CBC);
  ASSERT_TRUE(cipheruncipher.SetInitVector(ivbytes, sizeof(ivbytes)));
  ASSERT_TRUE(cipheruncipher.SetKey(&key));
  ASSERT_TRUE(cipheruncipher.Uncipher(ciphertext));

  XBUFFER* result = cipheruncipher.GetResult();
  ASSERT_NE(result, (XBUFFER*)NULL);
  ASSERT_EQ(result->GetSize(), (XDWORD)sizeof(plaintext));
  EXPECT_EQ(0, memcmp(result->Get(), plaintext, sizeof(plaintext)));
}


TEST(UNITTESTS_CIPHER3DES_CLASSNAME, CipherThenUncipherRoundtrip_DoubleKeyECB)
{
  XBYTE keybytes[16];
  for(int c=0; c<16; c++) keybytes[c] = (XBYTE)(0xA0 + c);

  XBYTE plaintext[8] = { 'A','B','C','D','E','F','G','H' };

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHER3DES ciphercipher;
  ciphercipher.SetChainingMode(CIPHERCHAININGMODE_ECB);
  ASSERT_TRUE(ciphercipher.SetKey(&key));
  ASSERT_TRUE(ciphercipher.Cipher(plaintext, sizeof(plaintext)));

  XBUFFER ciphertext(*ciphercipher.GetResult());

  CIPHER3DES cipheruncipher;
  cipheruncipher.SetChainingMode(CIPHERCHAININGMODE_ECB);
  ASSERT_TRUE(cipheruncipher.SetKey(&key));
  ASSERT_TRUE(cipheruncipher.Uncipher(ciphertext));

  XBUFFER* result = cipheruncipher.GetResult();
  ASSERT_NE(result, (XBUFFER*)NULL);
  ASSERT_EQ(result->GetSize(), (XDWORD)sizeof(plaintext));
  EXPECT_EQ(0, memcmp(result->Get(), plaintext, sizeof(plaintext)));
}


}
#endif
