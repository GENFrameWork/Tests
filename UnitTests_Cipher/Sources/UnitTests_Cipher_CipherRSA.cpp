/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherRSA.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERRSA
* @brief      Cipher unit tests for CIPHERRSA class
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

#include "UnitTests_Cipher_CipherRSA.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherRSA.h"
#include "CipherKeyPublicRSA.h"
#include "CipherKeyPrivateRSA.h"
#include "HashSHA2.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERRSA
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @class      CIPHERRSAFIXTURE
* @brief      Generates one real 2048-bit RSA key pair once (GenerateKeys() takes several seconds
*             of pure-C++ big-integer math -- confirmed ~4.5s on this sandbox -- so it is generated
*             a single time and shared across all tests in this suite instead of once per test).
*
* --------------------------------------------------------------------------------------------------------------------*/
class CIPHERRSAFIXTURE : public ::testing::Test
{
  public:

    static void SetUpTestSuite()
    {
      rsa = new CIPHERRSA();
      publickey = new CIPHERKEYPUBLICRSA();
      privatekey = new CIPHERKEYPRIVATERSA();

      ASSERT_TRUE(rsa->GenerateKeys(2048, 65537, *publickey, *privatekey));
    }

    static void TearDownTestSuite()
    {
      delete rsa;
      delete publickey;
      delete privatekey;

      rsa = NULL;
      publickey = NULL;
      privatekey = NULL;
    }

    static CIPHERRSA*             rsa;
    static CIPHERKEYPUBLICRSA*    publickey;
    static CIPHERKEYPRIVATERSA*   privatekey;
};

CIPHERRSA*           CIPHERRSAFIXTURE::rsa        = NULL;
CIPHERKEYPUBLICRSA*  CIPHERRSAFIXTURE::publickey  = NULL;
CIPHERKEYPRIVATERSA* CIPHERRSAFIXTURE::privatekey = NULL;


TEST_F(CIPHERRSAFIXTURE, GeneratedKeysHaveExpectedSize)
{
  EXPECT_EQ(publickey->GetSizeInBits(), 2048);
  EXPECT_EQ(privatekey->GetSizeInBits(), 2048);
}


TEST_F(CIPHERRSAFIXTURE, CipherThenUncipherRoundtrip_PKCS1_V15)
{
  CIPHERRSA cipher;
  ASSERT_TRUE(cipher.SetKey(publickey));
  ASSERT_TRUE(cipher.SetKey(privatekey));

  const char* message = "GEN Framework RSA round trip.";
  XDWORD messagesize = (XDWORD)strlen(message);

  EXPECT_TRUE(cipher.Cipher((XBYTE*)message, messagesize, CIPHERKEYTYPE_RSA_PUBLIC));

  XBUFFER ciphertext(*cipher.GetResult());
  EXPECT_EQ(ciphertext.GetSize(), (XDWORD)256); // 2048 bits == 256 bytes modulus
  EXPECT_NE(0, memcmp(ciphertext.Get(), message, messagesize));

  EXPECT_TRUE(cipher.Uncipher(ciphertext.Get(), ciphertext.GetSize(), CIPHERKEYTYPE_RSA_PRIVATE));

  XBUFFER* result = cipher.GetResult();
  ASSERT_NE(result, (XBUFFER*)NULL);
  ASSERT_EQ(result->GetSize(), messagesize);
  EXPECT_EQ(0, memcmp(result->Get(), message, messagesize));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST_F(CIPHERRSAFIXTURE, Sign_PKCS1_V15_IsPermanentlyBroken_NoHashSetsItsOID)
* @brief      Documents a confirmed, severe GEN defect (see /tmp/work/CIPHER_REVIEW_FINDINGS.md):
*             CIPHERRSA::Sign_PKCS1_V15() (CipherRSA.cpp) requires "hash->GetOUINoSign()" to return a
*             non-empty XSTRING (the DigestInfo AlgorithmIdentifier OID for the chosen hash), and
*             fails immediately -- "if(!OUINoSignstring->GetSize()) return false;" -- when it is
*             empty. But NO HASH subclass anywhere in GEN/Cipher/ (confirmed via
*             `grep -rn OUInosignstring` across every Hash*.cpp) ever assigns
*             HASH::OUInosignstring; it is only ever read via GetOUINoSign(), never written, so it
*             stays permanently empty (HASH's default-constructed XSTRING) for every hash object
*             that ever exists. This makes RSA-PKCS1v1.5 signing -- the DEFAULT
*             CIPHERRSAPKCS1VERSION for both Sign() and Verify() -- unconditionally non-functional
*             for every caller, for every hash.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST_F(CIPHERRSAFIXTURE, Sign_PKCS1_V15_IsPermanentlyBroken_NoHashSetsItsOID)
{
  CIPHERRSA signer;
  ASSERT_TRUE(signer.SetKey(publickey));
  ASSERT_TRUE(signer.SetKey(privatekey));

  HASHSHA2 sha256(HASHSHA2TYPE_256);

  // Confirm the actual root cause: GetOUINoSign() really is empty on a freshly constructed hash.
  XSTRING* oid = sha256.GetOUINoSign();
  ASSERT_NE(oid, (XSTRING*)NULL);
  EXPECT_EQ(oid->GetSize(), (XDWORD)0);

  const char* message = "This message is signed with RSA-2048 / SHA-256.";
  XDWORD messagesize = (XDWORD)strlen(message);

  // ACTUAL (broken) behavior: Sign() with the default PKCS1v1.5 scheme always fails.
  EXPECT_FALSE(signer.Sign((XBYTE*)message, messagesize, CIPHERKEYTYPE_RSA_PRIVATE, &sha256));
}


TEST_F(CIPHERRSAFIXTURE, SignThenVerifyRoundtrip_PSS_SHA256)
{
  // Uses EMSA-PSS (CIPHERRSAPKCS1VERSIONV21) instead of the broken default PKCS1v1.5 scheme (see
  // Sign_PKCS1_V15_IsPermanentlyBroken_NoHashSetsItsOID above) -- PSS does not depend on
  // HASH::GetOUINoSign() and is confirmed to actually work.
  CIPHERRSA signer;
  ASSERT_TRUE(signer.SetKey(publickey));
  ASSERT_TRUE(signer.SetKey(privatekey));

  HASHSHA2 sha256(HASHSHA2TYPE_256);

  const char* message = "This message is signed with RSA-2048 / SHA-256 / PSS.";
  XDWORD messagesize = (XDWORD)strlen(message);

  EXPECT_TRUE(signer.Sign((XBYTE*)message, messagesize, CIPHERKEYTYPE_RSA_PRIVATE, &sha256, CIPHERRSAPKCS1VERSIONV21));

  XBUFFER signature(*signer.GetResult());
  EXPECT_EQ(signature.GetSize(), (XDWORD)256);

  HASHSHA2 sha256verify(HASHSHA2TYPE_256);
  CIPHERRSA verifier;
  ASSERT_TRUE(verifier.SetKey(publickey));

  EXPECT_TRUE(verifier.Verify((XBYTE*)message, messagesize, signature, &sha256verify, CIPHERRSAPKCS1VERSIONV21));
}


TEST_F(CIPHERRSAFIXTURE, PSSVerifyRejectsTamperedMessage)
{
  CIPHERRSA signer;
  ASSERT_TRUE(signer.SetKey(publickey));
  ASSERT_TRUE(signer.SetKey(privatekey));

  HASHSHA2 sha256(HASHSHA2TYPE_256);

  const char* message = "Original untampered message.";
  XDWORD messagesize = (XDWORD)strlen(message);

  ASSERT_TRUE(signer.Sign((XBYTE*)message, messagesize, CIPHERKEYTYPE_RSA_PRIVATE, &sha256, CIPHERRSAPKCS1VERSIONV21));
  XBUFFER signature(*signer.GetResult());

  const char* tamperedmessage = "Original untampered massage."; // one byte flipped ('e' -> 'a')

  HASHSHA2 sha256verify(HASHSHA2TYPE_256);
  CIPHERRSA verifier;
  ASSERT_TRUE(verifier.SetKey(publickey));

  EXPECT_FALSE(verifier.Verify((XBYTE*)tamperedmessage, (XDWORD)strlen(tamperedmessage), signature, &sha256verify, CIPHERRSAPKCS1VERSIONV21));
}


TEST_F(CIPHERRSAFIXTURE, GenerateKeysRejectsBelowMinimumBits)
{
  CIPHERRSA rsasmall;
  CIPHERKEYPUBLICRSA smallpublic;
  CIPHERKEYPRIVATERSA smallprivate;

  // CIPHERRSA_MINKEYBITS (2048) is documented as the minimum accepted by GenerateKeys() -- confirm
  // it is actually enforced, not just documented.
  EXPECT_FALSE(rsasmall.GenerateKeys(1024, 65537, smallpublic, smallprivate));
}


}
#endif
