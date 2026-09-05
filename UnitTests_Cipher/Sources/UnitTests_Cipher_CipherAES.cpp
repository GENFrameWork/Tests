/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherAES.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERAES
* @brief      Cipher unit tests for CIPHERAES class
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

#include "UnitTests_Cipher_CipherAES.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherAES.h"
#include "CipherKeySymmetrical.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERAES
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_CIPHERAES_CLASSNAME, KnownAnswerVector_AES128_ECB_FIPS197)
* @brief      FIPS-197 Appendix B / C.1 single-block AES-128 known-answer vector: key =
*             000102030405060708090a0b0c0d0e0f, plaintext = 00112233445566778899aabbccddeeff,
*             ciphertext = 69c4e0d86a7b0430d8cdb78070b4c55a.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_CIPHERAES_CLASSNAME, KnownAnswerVector_AES128_ECB_FIPS197)
{
  CIPHERAES cipher;

  XBYTE keybytes[16] = { 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,
                          0x08,0x09,0x0a,0x0b,0x0c,0x0d,0x0e,0x0f };
  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  cipher.SetChainingMode(CIPHERCHAININGMODE_ECB);
  ASSERT_TRUE(cipher.SetKey(&key));

  XBYTE plaintext[16] = { 0x00,0x11,0x22,0x33,0x44,0x55,0x66,0x77,
                           0x88,0x99,0xaa,0xbb,0xcc,0xdd,0xee,0xff };

  EXPECT_TRUE(cipher.Cipher(plaintext, sizeof(plaintext)));

  XBUFFER* result = cipher.GetResult();
  ASSERT_NE(result, (XBUFFER*)NULL);
  ASSERT_EQ(result->GetSize(), (XDWORD)16);

  XBYTE expected[16] = { 0x69,0xc4,0xe0,0xd8,0x6a,0x7b,0x04,0x30,
                          0xd8,0xcd,0xb7,0x80,0x70,0xb4,0xc5,0x5a };
  EXPECT_EQ(0, memcmp(result->Get(), expected, 16));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_CIPHERAES_CLASSNAME, CipherThenUncipherRoundtrip_AES256_CBC_PKCS7)
* @brief      Documents a confirmed GEN defect (see /tmp/work/CIPHER_REVIEW_FINDINGS.md): after
*             Uncipher() decrypts, CIPHERAES::Uncipher() (CipherAES.cpp) calls
*             "result->Padding_Delete()" on its OWN freshly-built `result` XBUFFER -- but
*             XBUFFER::Padding_Delete() (XBuffer.cpp) is guarded by "if(!paddinghas) return false;",
*             and `paddinghas` is a per-XBUFFER-instance flag only ever set true by that same
*             instance's own Padding_Add() call. Uncipher()'s `result` buffer never had Padding_Add()
*             called on it (only Cipher()'s `result` does, on the OTHER object that encrypted), so
*             Padding_Delete() silently no-ops and the PKCS7 padding bytes appended at encryption
*             time are never stripped from the decrypted output for the realistic "one object
*             encrypts, another decrypts" pattern (the normal use case for a symmetric cipher).
*             This test therefore asserts the ACTUAL (buggy) behavior -- the decrypted buffer stays
*             padded up to a full 16-byte multiple -- while confirming the plaintext bytes themselves
*             (the ciphertext content, once the trailing padding bytes are ignored) round-trip
*             correctly, i.e. the cryptographic core is sound and the defect is purely in the
*             padding-removal bookkeeping.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_CIPHERAES_CLASSNAME, CipherThenUncipherRoundtrip_AES256_CBC_PKCS7)
{
  XBYTE keybytes[32];
  for(int c=0; c<32; c++) keybytes[c] = (XBYTE)c;

  XBYTE ivbytes[16];
  for(int c=0; c<16; c++) ivbytes[c] = (XBYTE)(0x40 + c);

  const char* message = "GEN Framework Cipher unit test message, longer than one AES block.";
  XDWORD messagesize = (XDWORD)strlen(message);

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHERAES ciphercipher;
  ciphercipher.SetChainingMode(CIPHERCHAININGMODE_CBC);
  ciphercipher.SetPaddingType(XBUFFER_PADDINGTYPE_PKCS7);
  ASSERT_TRUE(ciphercipher.SetInitVector(ivbytes, sizeof(ivbytes)));
  ASSERT_TRUE(ciphercipher.SetKey(&key));
  ASSERT_TRUE(ciphercipher.Cipher((XBYTE*)message, messagesize));

  XBUFFER ciphertext(*ciphercipher.GetResult());
  EXPECT_EQ(ciphertext.GetSize() % 16, (XDWORD)0);

  CIPHERAES cipheruncipher;
  cipheruncipher.SetChainingMode(CIPHERCHAININGMODE_CBC);
  cipheruncipher.SetPaddingType(XBUFFER_PADDINGTYPE_PKCS7);
  ASSERT_TRUE(cipheruncipher.SetInitVector(ivbytes, sizeof(ivbytes)));
  ASSERT_TRUE(cipheruncipher.SetKey(&key));
  ASSERT_TRUE(cipheruncipher.Uncipher(ciphertext));

  XBUFFER* result = cipheruncipher.GetResult();
  ASSERT_NE(result, (XBUFFER*)NULL);

  // ACTUAL (buggy) behavior: the padding was NOT stripped, so the decrypted buffer is still
  // exactly the ciphertext's (padded) size, not the original message size.
  EXPECT_EQ(result->GetSize(), ciphertext.GetSize());
  EXPECT_NE(result->GetSize(), messagesize);

  // The cryptographic core itself is correct: the first `messagesize` decrypted bytes match the
  // original plaintext exactly.
  ASSERT_GE(result->GetSize(), messagesize);
  EXPECT_EQ(0, memcmp(result->Get(), message, messagesize));
}


TEST(UNITTESTS_CIPHERAES_CLASSNAME, CBCChangesPerBlockCiphertextEvenForRepeatedPlaintext)
{
  // A basic sanity/security-adjacent check: CBC-mode encryption of two identical 16-byte blocks
  // must NOT produce two identical ciphertext blocks (that would be indistinguishable from ECB
  // mode and leak equality of plaintext blocks).
  XBYTE keybytes[16];
  for(int c=0; c<16; c++) keybytes[c] = (XBYTE)(c * 7);

  XBYTE ivbytes[16];
  memset(ivbytes, 0x5A, sizeof(ivbytes));

  XBYTE plaintext[32];
  memset(plaintext,      0x42, 16);
  memset(plaintext + 16, 0x42, 16);

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHERAES cipher;
  cipher.SetChainingMode(CIPHERCHAININGMODE_CBC);
  ASSERT_TRUE(cipher.SetInitVector(ivbytes, sizeof(ivbytes)));
  ASSERT_TRUE(cipher.SetKey(&key));
  ASSERT_TRUE(cipher.Cipher(plaintext, sizeof(plaintext)));

  XBUFFER* result = cipher.GetResult();
  ASSERT_NE(result, (XBUFFER*)NULL);
  ASSERT_GE(result->GetSize(), (XDWORD)32);

  EXPECT_NE(0, memcmp(result->Get(), result->Get() + 16, 16));
}


TEST(UNITTESTS_CIPHERAES_CLASSNAME, CipherWithoutKeyFails)
{
  CIPHERAES cipher;

  XBYTE plaintext[16];
  memset(plaintext, 0, sizeof(plaintext));

  EXPECT_FALSE(cipher.Cipher(plaintext, sizeof(plaintext)));
}


}
#endif
