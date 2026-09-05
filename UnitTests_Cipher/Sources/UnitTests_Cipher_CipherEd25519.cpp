/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherEd25519.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERED25519
* @brief      Cipher unit tests for CIPHERED25519 class
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

#include "UnitTests_Cipher_CipherEd25519.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherEd25519.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERED25519
{


TEST(UNITTESTS_CIPHERED25519_CLASSNAME, KeyPairCreateProducesExpectedSizes)
{
  CIPHERED25519 ed25519;

  XBUFFER privatekey;
  XBUFFER publickey;

  EXPECT_TRUE(ed25519.KeyPair_Create(privatekey, publickey));

  EXPECT_EQ(privatekey.GetSize(), (XDWORD)CIPHERED25519_PRIVATEKEYSIZE);
  EXPECT_EQ(publickey.GetSize(),  (XDWORD)CIPHERED25519_PUBLICKEYSIZE);
}


TEST(UNITTESTS_CIPHERED25519_CLASSNAME, PublicKeyCreateMatchesKeyPairCreate)
{
  CIPHERED25519 ed25519;

  XBUFFER privatekey;
  XBUFFER publickey;
  ASSERT_TRUE(ed25519.KeyPair_Create(privatekey, publickey));

  XBUFFER derivedpublickey;
  EXPECT_TRUE(ed25519.PublicKey_Create(privatekey, derivedpublickey));

  ASSERT_EQ(publickey.GetSize(), derivedpublickey.GetSize());
  EXPECT_EQ(0, memcmp(publickey.Get(), derivedpublickey.Get(), publickey.GetSize()));
}


TEST(UNITTESTS_CIPHERED25519_CLASSNAME, SignThenVerifyRoundtrip)
{
  CIPHERED25519 ed25519;

  XBUFFER privatekey;
  XBUFFER publickey;
  ASSERT_TRUE(ed25519.KeyPair_Create(privatekey, publickey));

  XBUFFER message;
  const char* text = "GEN Framework Ed25519 signature test.";
  message.Add((XBYTE*)text, (XDWORD)strlen(text));

  XBUFFER signature;
  EXPECT_TRUE(ed25519.Sign(privatekey, publickey, message, signature));
  EXPECT_EQ(signature.GetSize(), (XDWORD)CIPHERED25519_SIGNATURESIZE);

  EXPECT_TRUE(ed25519.Verify(publickey, message, signature));
}


TEST(UNITTESTS_CIPHERED25519_CLASSNAME, VerifyRejectsTamperedMessage)
{
  CIPHERED25519 ed25519;

  XBUFFER privatekey;
  XBUFFER publickey;
  ASSERT_TRUE(ed25519.KeyPair_Create(privatekey, publickey));

  XBUFFER message;
  const char* text = "Original message.";
  message.Add((XBYTE*)text, (XDWORD)strlen(text));

  XBUFFER signature;
  ASSERT_TRUE(ed25519.Sign(privatekey, publickey, message, signature));

  XBUFFER tampered;
  const char* tamperedtext = "Originab message."; // one byte flipped
  tampered.Add((XBYTE*)tamperedtext, (XDWORD)strlen(tamperedtext));

  EXPECT_FALSE(ed25519.Verify(publickey, tampered, signature));
}


TEST(UNITTESTS_CIPHERED25519_CLASSNAME, PublicKeyIsValidAcceptsGeneratedKeyRejectsGarbage)
{
  CIPHERED25519 ed25519;

  XBUFFER privatekey;
  XBUFFER publickey;
  ASSERT_TRUE(ed25519.KeyPair_Create(privatekey, publickey));

  EXPECT_TRUE(ed25519.PublicKey_IsValid(publickey));

  XBUFFER garbage;
  for(int c=0; c<CIPHERED25519_PUBLICKEYSIZE; c++) garbage.Add((XBYTE)0xFF);

  EXPECT_FALSE(ed25519.PublicKey_IsValid(garbage));
}


}
#endif
