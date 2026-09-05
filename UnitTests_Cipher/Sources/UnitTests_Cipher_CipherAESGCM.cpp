/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherAESGCM.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERAESGCM
* @brief      Cipher unit tests for CIPHERAESGCM class
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

#include "UnitTests_Cipher_CipherAESGCM.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherAESGCM.h"
#include "CipherKeySymmetrical.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERAESGCM
{


TEST(UNITTESTS_CIPHERAESGCM_CLASSNAME, IsAEADReportsExpectedSizes)
{
  CIPHERAESGCM cipher;

  EXPECT_TRUE(cipher.IsAEAD());
  EXPECT_EQ(cipher.GetAEADNonceSize(), (XDWORD)CIPHERAESGCM_NONCESIZE);
  EXPECT_EQ(cipher.GetAEADTagSize(), (XDWORD)CIPHERAESGCM_TAGSIZE);
}


TEST(UNITTESTS_CIPHERAESGCM_CLASSNAME, CipherThenUncipherAEADRoundtrip)
{
  XBYTE keybytes[32];
  for(int c=0; c<32; c++) keybytes[c] = (XBYTE)c;

  XBUFFER nonce;
  for(int c=0; c<CIPHERAESGCM_NONCESIZE; c++) nonce.Add((XBYTE)(0x90 + c));

  XBUFFER additionaldata;
  additionaldata.Add((XBYTE*)"header", 6);

  const char* message = "AES-GCM authenticated encryption round trip test.";
  XDWORD messagesize = (XDWORD)strlen(message);

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHERAESGCM ciphercipher;
  ASSERT_TRUE(ciphercipher.SetKey(&key));

  XBYTE plaintext[128];
  memcpy(plaintext, message, messagesize);

  XBUFFER tag;
  EXPECT_TRUE(ciphercipher.CipherAEAD(plaintext, messagesize, nonce, additionaldata, tag));
  EXPECT_EQ(tag.GetSize(), (XDWORD)CIPHERAESGCM_TAGSIZE);

  XBUFFER ciphertext(*ciphercipher.GetResult());
  ASSERT_EQ(ciphertext.GetSize(), messagesize);
  EXPECT_NE(0, memcmp(ciphertext.Get(), message, messagesize));

  CIPHERAESGCM cipheruncipher;
  ASSERT_TRUE(cipheruncipher.SetKey(&key));

  EXPECT_TRUE(cipheruncipher.UncipherAEAD(ciphertext.Get(), ciphertext.GetSize(), nonce, additionaldata, tag));

  XBUFFER* result = cipheruncipher.GetResult();
  ASSERT_NE(result, (XBUFFER*)NULL);
  ASSERT_EQ(result->GetSize(), messagesize);
  EXPECT_EQ(0, memcmp(result->Get(), message, messagesize));
}


TEST(UNITTESTS_CIPHERAESGCM_CLASSNAME, UncipherWithTamperedTagFails)
{
  XBYTE keybytes[16];
  for(int c=0; c<16; c++) keybytes[c] = (XBYTE)(0xC0 + c);

  XBUFFER nonce;
  for(int c=0; c<CIPHERAESGCM_NONCESIZE; c++) nonce.Add((XBYTE)c);

  XBUFFER additionaldata;

  XBYTE plaintext[16];
  memset(plaintext, 0x11, sizeof(plaintext));

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHERAESGCM ciphercipher;
  ASSERT_TRUE(ciphercipher.SetKey(&key));

  XBUFFER tag;
  ASSERT_TRUE(ciphercipher.CipherAEAD(plaintext, sizeof(plaintext), nonce, additionaldata, tag));

  XBUFFER ciphertext(*ciphercipher.GetResult());

  // Corrupt one byte of the authentication tag: decryption must be rejected, not silently
  // produce (wrong) plaintext -- this is the whole point of an AEAD tag.
  XBYTE corruptbyte = tag.Get()[0] ^ 0xFF;
  tag.Set(corruptbyte, 0);

  CIPHERAESGCM cipheruncipher;
  ASSERT_TRUE(cipheruncipher.SetKey(&key));

  EXPECT_FALSE(cipheruncipher.UncipherAEAD(ciphertext.Get(), ciphertext.GetSize(), nonce, additionaldata, tag));
}


}
#endif
