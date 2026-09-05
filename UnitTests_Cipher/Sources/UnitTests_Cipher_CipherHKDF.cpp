/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherHKDF.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERHKDF
* @brief      Cipher unit tests for CIPHERHKDF class
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

#include "UnitTests_Cipher_CipherHKDF.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherHKDF.h"
#include "HashSHA2.h"
#include "XBuffer.h"
#include "XString.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERHKDF
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_CIPHERHKDF_CLASSNAME, KnownAnswerVector_RFC5869_TestCase1)
* @brief      RFC 5869 appendix A.1 (HKDF-SHA256) test case 1: IKM = 0x0b*22, salt = 13 bytes
*             000102030405060708090a0b0c, info = f0f1f2f3f4f5f6f7f8f9, L=42 -->
*             PRK = 077709362c2e32df0ddc3f0dc47bba6390b6c73bb50f9c3122ec844ad7c2b3e5,
*             OKM = 3cb25f25faacd57a90434f64d0362f2a2d2d0a90cf1a5a4c5db02d56ecc4c5bf34007208d5b887185865.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_CIPHERHKDF_CLASSNAME, KnownAnswerVector_RFC5869_TestCase1)
{
  HASHSHA2 sha256(HASHSHA2TYPE_256);
  CIPHERHKDF hkdf(&sha256);

  XBYTE ikmbytes[22];
  memset(ikmbytes, 0x0b, sizeof(ikmbytes));

  XBYTE saltbytes[13] = { 0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,0x09,0x0a,0x0b,0x0c };
  XBYTE infobytes[10] = { 0xf0,0xf1,0xf2,0xf3,0xf4,0xf5,0xf6,0xf7,0xf8,0xf9 };

  XBUFFER ikm;
  ikm.Add(ikmbytes, sizeof(ikmbytes));

  XBUFFER salt;
  salt.Add(saltbytes, sizeof(saltbytes));

  XBUFFER info;
  info.Add(infobytes, sizeof(infobytes));

  XBUFFER prk;
  EXPECT_TRUE(hkdf.Extract(salt, ikm, prk));

  XBYTE expectedprk[32] = { 0x07,0x77,0x09,0x36,0x2c,0x2e,0x32,0xdf,0x0d,0xdc,0x3f,0x0d,0xc4,0x7b,0xba,0x63,
                             0x90,0xb6,0xc7,0x3b,0xb5,0x0f,0x9c,0x31,0x22,0xec,0x84,0x4a,0xd7,0xc2,0xb3,0xe5 };
  ASSERT_EQ(prk.GetSize(), (XDWORD)32);
  EXPECT_EQ(0, memcmp(prk.Get(), expectedprk, 32));

  XBUFFER okm;
  EXPECT_TRUE(hkdf.Expand(prk, info, 42, okm));

  XBYTE expectedokm[42] = { 0x3c,0xb2,0x5f,0x25,0xfa,0xac,0xd5,0x7a,0x90,0x43,0x4f,0x64,0xd0,0x36,0x2f,0x2a,
                             0x2d,0x2d,0x0a,0x90,0xcf,0x1a,0x5a,0x4c,0x5d,0xb0,0x2d,0x56,0xec,0xc4,0xc5,0xbf,
                             0x34,0x00,0x72,0x08,0xd5,0xb8,0x87,0x18,0x58,0x65 };
  ASSERT_EQ(okm.GetSize(), (XDWORD)42);
  EXPECT_EQ(0, memcmp(okm.Get(), expectedokm, 42));
}


TEST(UNITTESTS_CIPHERHKDF_CLASSNAME, GetHashSizeMatchesSHA256)
{
  HASHSHA2 sha256(HASHSHA2TYPE_256);
  CIPHERHKDF hkdf(&sha256);

  EXPECT_EQ(hkdf.GetHashSize(), (XDWORD)32);
}


TEST(UNITTESTS_CIPHERHKDF_CLASSNAME, GetSetHashRoundtrip)
{
  HASHSHA2 sha256(HASHSHA2TYPE_256);
  CIPHERHKDF hkdf;

  EXPECT_TRUE(hkdf.SetHash(&sha256));
  EXPECT_EQ(hkdf.GetHash(), (HASH*)&sha256);
}


TEST(UNITTESTS_CIPHERHKDF_CLASSNAME, LabelPrefixDefaultsToTLS13)
{
  HASHSHA2 sha256(HASHSHA2TYPE_256);
  CIPHERHKDF hkdf(&sha256);

  XSTRING* labelprefix = hkdf.GetLabelPrefix();
  ASSERT_NE(labelprefix, (XSTRING*)NULL);
  EXPECT_EQ(0, labelprefix->Compare(CIPHERHKDF_LABELPREFIX_TLS13));
}


}
#endif
