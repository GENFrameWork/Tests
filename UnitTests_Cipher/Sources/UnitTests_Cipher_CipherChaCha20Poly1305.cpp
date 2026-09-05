/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherChaCha20Poly1305.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERCHACHA20POLY1305
* @brief      Cipher unit tests for CIPHERCHACHA20POLY1305 class
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

#include "UnitTests_Cipher_CipherChaCha20Poly1305.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherChaCha20Poly1305.h"
#include "CipherKeySymmetrical.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERCHACHA20POLY1305
{


TEST(UNITTESTS_CIPHERCHACHA20POLY1305_CLASSNAME, IsAEADReportsExpectedSizes)
{
  CIPHERCHACHA20POLY1305 cipher;

  EXPECT_TRUE(cipher.IsAEAD());
  EXPECT_EQ(cipher.GetAEADNonceSize(), (XDWORD)CIPHERCHACHA20POLY1305_NONCESIZE);
  EXPECT_EQ(cipher.GetAEADTagSize(), (XDWORD)CIPHERCHACHA20POLY1305_TAGSIZE);
}


TEST(UNITTESTS_CIPHERCHACHA20POLY1305_CLASSNAME, CipherThenUncipherAEADRoundtrip)
{
  XBYTE keybytes[CIPHERCHACHA20POLY1305_KEYSIZE];
  for(int c=0; c<CIPHERCHACHA20POLY1305_KEYSIZE; c++) keybytes[c] = (XBYTE)c;

  XBUFFER nonce;
  for(int c=0; c<CIPHERCHACHA20POLY1305_NONCESIZE; c++) nonce.Add((XBYTE)(0x50 + c));

  XBUFFER additionaldata;
  additionaldata.Add((XBYTE*)"aad", 3);

  const char* message = "ChaCha20-Poly1305 authenticated encryption round trip test.";
  XDWORD messagesize = (XDWORD)strlen(message);

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHERCHACHA20POLY1305 ciphercipher;
  ASSERT_TRUE(ciphercipher.SetKey(&key));

  XBYTE plaintext[128];
  memcpy(plaintext, message, messagesize);

  XBUFFER tag;
  EXPECT_TRUE(ciphercipher.CipherAEAD(plaintext, messagesize, nonce, additionaldata, tag));
  EXPECT_EQ(tag.GetSize(), (XDWORD)CIPHERCHACHA20POLY1305_TAGSIZE);

  XBUFFER ciphertext(*ciphercipher.GetResult());
  ASSERT_EQ(ciphertext.GetSize(), messagesize);
  EXPECT_NE(0, memcmp(ciphertext.Get(), message, messagesize));

  CIPHERCHACHA20POLY1305 cipheruncipher;
  ASSERT_TRUE(cipheruncipher.SetKey(&key));

  EXPECT_TRUE(cipheruncipher.UncipherAEAD(ciphertext.Get(), ciphertext.GetSize(), nonce, additionaldata, tag));

  XBUFFER* result = cipheruncipher.GetResult();
  ASSERT_NE(result, (XBUFFER*)NULL);
  ASSERT_EQ(result->GetSize(), messagesize);
  EXPECT_EQ(0, memcmp(result->Get(), message, messagesize));
}


TEST(UNITTESTS_CIPHERCHACHA20POLY1305_CLASSNAME, UncipherWithTamperedCiphertextFails)
{
  XBYTE keybytes[CIPHERCHACHA20POLY1305_KEYSIZE];
  memset(keybytes, 0x33, sizeof(keybytes));

  XBUFFER nonce;
  for(int c=0; c<CIPHERCHACHA20POLY1305_NONCESIZE; c++) nonce.Add((XBYTE)c);

  XBUFFER additionaldata;

  XBYTE plaintext[16];
  memset(plaintext, 0x22, sizeof(plaintext));

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHERCHACHA20POLY1305 ciphercipher;
  ASSERT_TRUE(ciphercipher.SetKey(&key));

  XBUFFER tag;
  ASSERT_TRUE(ciphercipher.CipherAEAD(plaintext, sizeof(plaintext), nonce, additionaldata, tag));

  XBUFFER ciphertext(*ciphercipher.GetResult());
  XBYTE corruptbyte = ciphertext.Get()[0] ^ 0xFF;
  ciphertext.Set(corruptbyte, 0);

  CIPHERCHACHA20POLY1305 cipheruncipher;
  ASSERT_TRUE(cipheruncipher.SetKey(&key));

  EXPECT_FALSE(cipheruncipher.UncipherAEAD(ciphertext.Get(), ciphertext.GetSize(), nonce, additionaldata, tag));
}


}
#endif
