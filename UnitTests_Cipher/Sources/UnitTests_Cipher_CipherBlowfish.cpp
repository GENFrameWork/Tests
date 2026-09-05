/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherBlowfish.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERBLOWFISH
* @brief      Cipher unit tests for CIPHERBLOWFISH class
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

#include "UnitTests_Cipher_CipherBlowfish.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherBlowfish.h"
#include "CipherKeySymmetrical.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERBLOWFISH
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_CIPHERBLOWFISH_CLASSNAME, ECBChainingModeIsUnreachableViaThePublicAPI)
* @brief      Documents a confirmed GEN defect (see /tmp/work/CIPHER_REVIEW_FINDINGS.md):
*             CIPHERBLOWFISH::Cipher()/Uncipher() (CipherBlowfish.cpp) both `switch` on
*             GetChainingMode() and fold CIPHERCHAININGMODE_ECB into the same `status = false;`
*             branch as CIPHERCHAININGMODE_UNKNOWN -- unlike CIPHERAES and CIPHERDES, which both
*             DO implement an ECB case. The private BlowfishCipher_ECB() primitive is fully
*             implemented and is even used internally as the building block for CBC/CFB/CTR, but is
*             never reachable on its own via the public Cipher()/Uncipher() API when
*             CIPHERCHAININGMODE_ECB is selected -- it is dead code from the chaining-mode
*             dispatcher's point of view. This test records the actual (broken) behavior.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_CIPHERBLOWFISH_CLASSNAME, ECBChainingModeIsUnreachableViaThePublicAPI)
{
  XBYTE keybytes[16];
  for(int c=0; c<16; c++) keybytes[c] = (XBYTE)(c + 1);

  XBYTE plaintext[8] = { 'B','l','o','w','f','s','h','!' };

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHERBLOWFISH cipher;
  cipher.SetChainingMode(CIPHERCHAININGMODE_ECB);
  ASSERT_TRUE(cipher.SetKey(&key));

  // ACTUAL (buggy) behavior: ECB is dispatched to the same "status = false" branch as UNKNOWN.
  EXPECT_FALSE(cipher.Cipher(plaintext, sizeof(plaintext)));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_CIPHERBLOWFISH_CLASSNAME, EightByteInitVectorIsSilentlyIgnoredByCipher)
* @brief      Documents a second, independent confirmed GEN defect (see
*             /tmp/work/CIPHER_REVIEW_FINDINGS.md): CIPHERBLOWFISH_BLOCKSIZE is 8 (Blowfish's real
*             block/IV size), yet CIPHERBLOWFISH::Cipher() only honors an init vector when
*             "inivector->GetSize()>=16" (CipherBlowfish.cpp), while CIPHERBLOWFISH::Uncipher() uses
*             a DIFFERENT, correct-for-Blowfish threshold of ">=8" for the very same check. A caller
*             who (reasonably) sets an 8-byte IV -- the size CIPHERBLOWFISH_BLOCKSIZE itself
*             documents -- gets it silently ignored (replaced with an all-zero IV) on the encrypt
*             side but honored on the decrypt side, corrupting every CBC/CFB/CTR round trip. This
*             test proves it: Cipher() with an 8-byte IV produces the SAME ciphertext as Cipher()
*             with SetInitVector() never called at all (both silently fall back to an all-zero IV).
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_CIPHERBLOWFISH_CLASSNAME, EightByteInitVectorIsSilentlyIgnoredByCipher)
{
  XBYTE keybytes[8] = { 0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF };
  XBYTE ivbytes[8]  = { 0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10 };
  XBYTE plaintext[8] = { 'A','B','C','D','E','F','G','H' };

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHERBLOWFISH cipherwithiv;
  cipherwithiv.SetChainingMode(CIPHERCHAININGMODE_CBC);
  ASSERT_TRUE(cipherwithiv.SetInitVector(ivbytes, sizeof(ivbytes)));
  ASSERT_TRUE(cipherwithiv.SetKey(&key));
  ASSERT_TRUE(cipherwithiv.Cipher(plaintext, sizeof(plaintext)));
  XBUFFER resultwithiv(*cipherwithiv.GetResult());

  CIPHERBLOWFISH cipherwithoutiv;
  cipherwithoutiv.SetChainingMode(CIPHERCHAININGMODE_CBC);
  ASSERT_TRUE(cipherwithoutiv.SetKey(&key));
  ASSERT_TRUE(cipherwithoutiv.Cipher(plaintext, sizeof(plaintext)));
  XBUFFER resultwithoutiv(*cipherwithoutiv.GetResult());

  // ACTUAL (buggy) behavior: the explicitly-set, correctly-sized 8-byte IV made no difference.
  ASSERT_EQ(resultwithiv.GetSize(), resultwithoutiv.GetSize());
  EXPECT_EQ(0, memcmp(resultwithiv.Get(), resultwithoutiv.Get(), resultwithiv.GetSize()));
}


TEST(UNITTESTS_CIPHERBLOWFISH_CLASSNAME, CipherThenUncipherRoundtrip_CBC_PKCS7)
{
  XBYTE keybytes[8] = { 0x01,0x23,0x45,0x67,0x89,0xAB,0xCD,0xEF };

  // A full 16-byte IV is used here (rather than Blowfish's real 8-byte CIPHERBLOWFISH_BLOCKSIZE)
  // specifically to sidestep the EightByteInitVectorIsSilentlyIgnoredByCipher defect documented
  // above and above all: this lets this test isolate and demonstrate the SEPARATE
  // padding-removal defect below. Only the first CIPHERBLOWFISH_BLOCKSIZE (8) bytes are ever
  // actually used by BlowfishCipher_CBC.
  XBYTE ivbytes[16] = { 0xFE,0xDC,0xBA,0x98,0x76,0x54,0x32,0x10, 0,0,0,0,0,0,0,0 };

  const char* message = "Blowfish CBC round trip message longer than one block.";
  XDWORD messagesize = (XDWORD)strlen(message);

  CIPHERKEYSYMMETRICAL key;
  ASSERT_TRUE(key.Set(keybytes, sizeof(keybytes)));

  CIPHERBLOWFISH ciphercipher;
  ciphercipher.SetChainingMode(CIPHERCHAININGMODE_CBC);
  ciphercipher.SetPaddingType(XBUFFER_PADDINGTYPE_PKCS7);
  ASSERT_TRUE(ciphercipher.SetInitVector(ivbytes, sizeof(ivbytes)));
  ASSERT_TRUE(ciphercipher.SetKey(&key));
  ASSERT_TRUE(ciphercipher.Cipher((XBYTE*)message, messagesize));

  XBUFFER ciphertext(*ciphercipher.GetResult());
  EXPECT_EQ(ciphertext.GetSize() % 8, (XDWORD)0);

  CIPHERBLOWFISH cipheruncipher;
  cipheruncipher.SetChainingMode(CIPHERCHAININGMODE_CBC);
  cipheruncipher.SetPaddingType(XBUFFER_PADDINGTYPE_PKCS7);
  ASSERT_TRUE(cipheruncipher.SetInitVector(ivbytes, sizeof(ivbytes)));
  ASSERT_TRUE(cipheruncipher.SetKey(&key));
  ASSERT_TRUE(cipheruncipher.Uncipher(ciphertext));

  XBUFFER* result = cipheruncipher.GetResult();
  ASSERT_NE(result, (XBUFFER*)NULL);

  // Same confirmed padding-removal defect as CIPHERAES (see
  // UnitTests_Cipher_CipherAES.cpp's CipherThenUncipherRoundtrip_AES256_CBC_PKCS7 and
  // /tmp/work/CIPHER_REVIEW_FINDINGS.md): CIPHERBLOWFISH::Uncipher() also calls
  // "result->Padding_Delete()" on a `result` buffer that never had Padding_Add() called on it, so
  // the PKCS7 padding is never actually stripped. The core cipher itself is correct.
  EXPECT_EQ(result->GetSize(), ciphertext.GetSize());
  EXPECT_NE(result->GetSize(), messagesize);

  ASSERT_GE(result->GetSize(), messagesize);
  EXPECT_EQ(0, memcmp(result->Get(), message, messagesize));
}


TEST(UNITTESTS_CIPHERBLOWFISH_CLASSNAME, CipherWithoutKeyFails)
{
  CIPHERBLOWFISH cipher;

  XBYTE plaintext[8];
  memset(plaintext, 0, sizeof(plaintext));

  EXPECT_FALSE(cipher.Cipher(plaintext, sizeof(plaintext)));
}


}
#endif
