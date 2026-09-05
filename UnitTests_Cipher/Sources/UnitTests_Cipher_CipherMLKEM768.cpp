/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherMLKEM768.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERMLKEM768
* @brief      Cipher unit tests for CIPHERMLKEM768 class
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

#include "UnitTests_Cipher_CipherMLKEM768.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherMLKEM768.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERMLKEM768
{


TEST(UNITTESTS_CIPHERMLKEM768_CLASSNAME, KeyPairCreateProducesNonEmptyKeys)
{
  CIPHERMLKEM768 mlkem;

  XBUFFER publickey;
  XBUFFER privatekey;

  EXPECT_TRUE(mlkem.KeyPair_Create(publickey, privatekey));

  EXPECT_GT(publickey.GetSize(), (XDWORD)0);
  EXPECT_GT(privatekey.GetSize(), (XDWORD)0);
}


TEST(UNITTESTS_CIPHERMLKEM768_CLASSNAME, EncapsulateThenDecapsulateSharedSecretsMatch)
{
  // FIPS 203 KEM contract: Encapsulate() with the public key yields a ciphertext plus a shared
  // secret; Decapsulate() with the matching private key and that ciphertext must recover the
  // exact same shared secret.
  CIPHERMLKEM768 keygen;

  XBUFFER publickey;
  XBUFFER privatekey;
  ASSERT_TRUE(keygen.KeyPair_Create(publickey, privatekey));

  CIPHERMLKEM768 sender;
  XBUFFER ciphertext;
  XBUFFER sharedsecretsender;
  ASSERT_TRUE(sender.Encapsulate(publickey, ciphertext, sharedsecretsender));
  EXPECT_GT(ciphertext.GetSize(), (XDWORD)0);
  EXPECT_GT(sharedsecretsender.GetSize(), (XDWORD)0);

  CIPHERMLKEM768 receiver;
  XBUFFER sharedsecretreceiver;
  ASSERT_TRUE(receiver.Decapsulate(privatekey, ciphertext, sharedsecretreceiver));

  ASSERT_EQ(sharedsecretsender.GetSize(), sharedsecretreceiver.GetSize());
  EXPECT_EQ(0, memcmp(sharedsecretsender.Get(), sharedsecretreceiver.Get(), sharedsecretsender.GetSize()));
}


TEST(UNITTESTS_CIPHERMLKEM768_CLASSNAME, PublicKeyCheckAcceptsGeneratedKeyRejectsGarbage)
{
  CIPHERMLKEM768 mlkem;

  XBUFFER publickey;
  XBUFFER privatekey;
  ASSERT_TRUE(mlkem.KeyPair_Create(publickey, privatekey));

  EXPECT_TRUE(mlkem.PublicKey_Check(publickey));

  XBUFFER garbage;
  for(int c=0; c<32; c++) garbage.Add((XBYTE)0xAB);

  EXPECT_FALSE(mlkem.PublicKey_Check(garbage));
}


TEST(UNITTESTS_CIPHERMLKEM768_CLASSNAME, DecapsulateWithWrongPrivateKeyProducesDifferentSecret)
{
  CIPHERMLKEM768 keygena;
  CIPHERMLKEM768 keygenb;

  XBUFFER publickeya, privatekeya;
  XBUFFER publickeyb, privatekeyb;
  ASSERT_TRUE(keygena.KeyPair_Create(publickeya, privatekeya));
  ASSERT_TRUE(keygenb.KeyPair_Create(publickeyb, privatekeyb));

  CIPHERMLKEM768 sender;
  XBUFFER ciphertext;
  XBUFFER sharedsecretsender;
  ASSERT_TRUE(sender.Encapsulate(publickeya, ciphertext, sharedsecretsender));

  CIPHERMLKEM768 wrongreceiver;
  XBUFFER sharedsecretwrong;

  // ML-KEM is implicit-rejection: Decapsulate() with a mismatched private key still succeeds
  // structurally but must yield a shared secret that does NOT match the sender's.
  bool decapsulated = wrongreceiver.Decapsulate(privatekeyb, ciphertext, sharedsecretwrong);
  if(decapsulated)
    {
      bool identical = (sharedsecretsender.GetSize() == sharedsecretwrong.GetSize()) &&
                        (memcmp(sharedsecretsender.Get(), sharedsecretwrong.Get(), sharedsecretsender.GetSize()) == 0);
      EXPECT_FALSE(identical);
    }
}


}
#endif
