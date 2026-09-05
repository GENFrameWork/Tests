/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherECDSAX25519.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERECDSAX25519
* @brief      Cipher unit tests for CIPHERECDSAX25519 class
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

#include "UnitTests_Cipher_CipherECDSAX25519.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherECDSAX25519.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERECDSAX25519
{


TEST(UNITTESTS_CIPHERECDSAX25519_CLASSNAME, GenerateRandomPrivateKeyMarksItCreated)
{
  CIPHERECDSAX25519 x25519;

  EXPECT_FALSE(x25519.IsKeyCreated(CIPHERECDSAX25519_TYPEKEY_PRIVATE));
  EXPECT_TRUE(x25519.GenerateRandomPrivateKey());
  EXPECT_TRUE(x25519.IsKeyCreated(CIPHERECDSAX25519_TYPEKEY_PRIVATE));
}


TEST(UNITTESTS_CIPHERECDSAX25519_CLASSNAME, CreatePublicKeyRequiresPrivateKeyFirst)
{
  CIPHERECDSAX25519 x25519;

  ASSERT_TRUE(x25519.GenerateRandomPrivateKey());
  EXPECT_TRUE(x25519.CreatePublicKey());
  EXPECT_TRUE(x25519.IsKeyCreated(CIPHERECDSAX25519_TYPEKEY_PUBLIC));

  XBYTE* publickey = x25519.GetKey(CIPHERECDSAX25519_TYPEKEY_PUBLIC);
  ASSERT_NE(publickey, (XBYTE*)NULL);
}


TEST(UNITTESTS_CIPHERECDSAX25519_CLASSNAME, SharedSecretMatchesBothDirections)
{
  // X25519 ECDH: two independent parties, each computes CreateSharedKey() from its own private
  // key and the other party's public key -- both resulting shared keys must be identical.
  CIPHERECDSAX25519 partya;
  CIPHERECDSAX25519 partyb;

  ASSERT_TRUE(partya.GenerateRandomPrivateKey());
  ASSERT_TRUE(partya.CreatePublicKey());

  ASSERT_TRUE(partyb.GenerateRandomPrivateKey());
  ASSERT_TRUE(partyb.CreatePublicKey());

  XBYTE* publickeya = partya.GetKey(CIPHERECDSAX25519_TYPEKEY_PUBLIC);
  XBYTE* publickeyb = partyb.GetKey(CIPHERECDSAX25519_TYPEKEY_PUBLIC);
  ASSERT_NE(publickeya, (XBYTE*)NULL);
  ASSERT_NE(publickeyb, (XBYTE*)NULL);

  EXPECT_TRUE(partya.CreateSharedKey(publickeyb));
  EXPECT_TRUE(partyb.CreateSharedKey(publickeya));

  XBYTE* sharedA = partya.GetKey(CIPHERECDSAX25519_TYPEKEY_SHARED);
  XBYTE* sharedB = partyb.GetKey(CIPHERECDSAX25519_TYPEKEY_SHARED);
  ASSERT_NE(sharedA, (XBYTE*)NULL);
  ASSERT_NE(sharedB, (XBYTE*)NULL);

  EXPECT_EQ(0, memcmp(sharedA, sharedB, CIPHERECDSAX25519_MAXKEY));
}


TEST(UNITTESTS_CIPHERECDSAX25519_CLASSNAME, CleanAllKeysResetsCreatedFlags)
{
  CIPHERECDSAX25519 x25519;

  ASSERT_TRUE(x25519.GenerateRandomPrivateKey());
  ASSERT_TRUE(x25519.CreatePublicKey());
  ASSERT_TRUE(x25519.IsKeyCreated(CIPHERECDSAX25519_TYPEKEY_PRIVATE));
  ASSERT_TRUE(x25519.IsKeyCreated(CIPHERECDSAX25519_TYPEKEY_PUBLIC));

  x25519.CleanAllKeys();

  EXPECT_FALSE(x25519.IsKeyCreated(CIPHERECDSAX25519_TYPEKEY_PRIVATE));
  EXPECT_FALSE(x25519.IsKeyCreated(CIPHERECDSAX25519_TYPEKEY_PUBLIC));
  EXPECT_FALSE(x25519.IsKeyCreated(CIPHERECDSAX25519_TYPEKEY_SHARED));
}


}
#endif
