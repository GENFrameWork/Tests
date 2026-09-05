/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherECDSA.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERECDSA
* @brief      Cipher unit tests for CIPHERECDSA class
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

#include "UnitTests_Cipher_CipherECDSA.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherECDSA.h"
#include "CipherKeyECDSA.h"
#include "HashSHA2.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERECDSA
{


TEST(UNITTESTS_CIPHERECDSA_CLASSNAME, KeyPairCreateProducesUncompressedPublicKey)
{
  CIPHERECDSA ecdsa(CIPHERTYPE_ECDSA_SECP256R1);

  XBUFFER privatekey;
  XBUFFER publickey;

  EXPECT_TRUE(ecdsa.KeyPair_Create(privatekey, publickey));

  EXPECT_EQ(privatekey.GetSize(), (XDWORD)32); // secp256r1 scalar size
  EXPECT_EQ(publickey.GetSize(), (XDWORD)65);  // 0x04 || X(32) || Y(32)
  EXPECT_EQ(publickey.GetByte(0), (XBYTE)0x04);
}


TEST(UNITTESTS_CIPHERECDSA_CLASSNAME, SignThenVerifyRoundtrip)
{
  CIPHERECDSA keygen(CIPHERTYPE_ECDSA_SECP256R1);

  XBUFFER privatekeybytes;
  XBUFFER publickeybytes;
  ASSERT_TRUE(keygen.KeyPair_Create(privatekeybytes, publickeybytes));

  CIPHERKEYECDSA privatekey;
  privatekey.SetType(CIPHERKEYTYPE_ECDSA_SECP256R1_PRIVATE);
  ASSERT_TRUE(privatekey.Set(privatekeybytes));

  CIPHERKEYECDSA publickey;
  publickey.SetType(CIPHERKEYTYPE_ECDSA_SECP256R1_PUBLIC);
  ASSERT_TRUE(publickey.Set(publickeybytes));

  CIPHERECDSA signer(CIPHERTYPE_ECDSA_SECP256R1);
  ASSERT_TRUE(signer.SetKey(&privatekey));

  HASHSHA2 sha256(HASHSHA2TYPE_256);
  const char* message = "GEN Framework ECDSA P-256 signature test.";
  XDWORD messagesize = (XDWORD)strlen(message);

  EXPECT_TRUE(signer.Sign((XBYTE*)message, messagesize, &sha256));
  XBUFFER signature(*signer.GetResult());
  EXPECT_GT(signature.GetSize(), (XDWORD)0);

  CIPHERECDSA verifier(CIPHERTYPE_ECDSA_SECP256R1);
  ASSERT_TRUE(verifier.SetKey(&publickey));

  HASHSHA2 sha256verify(HASHSHA2TYPE_256);
  EXPECT_TRUE(verifier.Verify((XBYTE*)message, messagesize, signature, &sha256verify));
}


TEST(UNITTESTS_CIPHERECDSA_CLASSNAME, VerifyRejectsTamperedMessage)
{
  CIPHERECDSA keygen(CIPHERTYPE_ECDSA_SECP256R1);

  XBUFFER privatekeybytes;
  XBUFFER publickeybytes;
  ASSERT_TRUE(keygen.KeyPair_Create(privatekeybytes, publickeybytes));

  CIPHERKEYECDSA privatekey;
  privatekey.SetType(CIPHERKEYTYPE_ECDSA_SECP256R1_PRIVATE);
  ASSERT_TRUE(privatekey.Set(privatekeybytes));

  CIPHERKEYECDSA publickey;
  publickey.SetType(CIPHERKEYTYPE_ECDSA_SECP256R1_PUBLIC);
  ASSERT_TRUE(publickey.Set(publickeybytes));

  CIPHERECDSA signer(CIPHERTYPE_ECDSA_SECP256R1);
  ASSERT_TRUE(signer.SetKey(&privatekey));

  HASHSHA2 sha256(HASHSHA2TYPE_256);
  const char* message = "Original message.";
  ASSERT_TRUE(signer.Sign((XBYTE*)message, (XDWORD)strlen(message), &sha256));
  XBUFFER signature(*signer.GetResult());

  CIPHERECDSA verifier(CIPHERTYPE_ECDSA_SECP256R1);
  ASSERT_TRUE(verifier.SetKey(&publickey));

  const char* tamperedmessage = "Originab message."; // one byte flipped
  HASHSHA2 sha256verify(HASHSHA2TYPE_256);
  EXPECT_FALSE(verifier.Verify((XBYTE*)tamperedmessage, (XDWORD)strlen(tamperedmessage), signature, &sha256verify));
}


TEST(UNITTESTS_CIPHERECDSA_CLASSNAME, SharedSecretMatchesBothDirections)
{
  // ECDH: two independent key pairs, each side computes the shared secret from its own private
  // key and the other side's public key -- both must agree.
  CIPHERECDSA keygena(CIPHERTYPE_ECDSA_SECP256R1);
  CIPHERECDSA keygenb(CIPHERTYPE_ECDSA_SECP256R1);

  XBUFFER privatea, publica;
  XBUFFER privateb, publicb;
  ASSERT_TRUE(keygena.KeyPair_Create(privatea, publica));
  ASSERT_TRUE(keygenb.KeyPair_Create(privateb, publicb));

  CIPHERECDSA ecdsa(CIPHERTYPE_ECDSA_SECP256R1);

  XBUFFER sharedsecretA;
  XBUFFER sharedsecretB;

  EXPECT_TRUE(ecdsa.SharedSecret_Create(privatea, publicb, sharedsecretA));
  EXPECT_TRUE(ecdsa.SharedSecret_Create(privateb, publica, sharedsecretB));

  ASSERT_EQ(sharedsecretA.GetSize(), sharedsecretB.GetSize());
  ASSERT_GT(sharedsecretA.GetSize(), (XDWORD)0);
  EXPECT_EQ(0, memcmp(sharedsecretA.Get(), sharedsecretB.Get(), sharedsecretA.GetSize()));
}


TEST(UNITTESTS_CIPHERECDSA_CLASSNAME, PublicKeyCheckRejectsGarbage)
{
  CIPHERECDSA ecdsa(CIPHERTYPE_ECDSA_SECP256R1);

  XBUFFER garbage;
  for(int c=0; c<65; c++) garbage.Add((XBYTE)0xAB);

  EXPECT_FALSE(ecdsa.PublicKey_Check(garbage));
}


}
#endif
