/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_HashHMAC.cpp
*
* @class      UNITTESTS_CIPHER_HASHHMAC
* @brief      Cipher unit tests for HASHHMAC class
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

#include "UnitTests_Cipher_HashHMAC.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "HashHMAC.h"
#include "HashMD5.h"
#include "HashSHA1.h"
#include "XBuffer.h"
#include "XString.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_HASHHMAC
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHHMAC_CLASSNAME, KnownAnswerVector_HMAC_MD5_RFC2202)
* @brief      RFC 2202 test vector #1: HMAC-MD5 with key = 0x0b repeated 16 times and data "Hi There"
*             produces 9294727a3638bb1c13f48ef8158bfc9d.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHHMAC_CLASSNAME, KnownAnswerVector_HMAC_MD5_RFC2202)
{
  HASHMD5 md5;
  HASHHMAC hmac(&md5);

  XBYTE key[16];
  memset(key, 0x0b, sizeof(key));
  EXPECT_TRUE(hmac.SetKey(key, sizeof(key)));

  const char* data = "Hi There";
  EXPECT_TRUE(hmac.Do((XBYTE*)data, (XQWORD)strlen(data)));

  XSTRING stringhex;
  EXPECT_TRUE(hmac.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("9294727a3638bb1c13f48ef8158bfc9d"), true));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_HASHHMAC_CLASSNAME, KnownAnswerVector_HMAC_SHA1_RFC2202)
* @brief      RFC 2202 test vector #1: HMAC-SHA1 with key = 0x0b repeated 20 times and data "Hi There"
*             produces b617318655057264e28bc0b6fb378c8ef146be00.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_HASHHMAC_CLASSNAME, KnownAnswerVector_HMAC_SHA1_RFC2202)
{
  HASHSHA1 sha1;
  HASHHMAC hmac(&sha1);

  XBYTE key[20];
  memset(key, 0x0b, sizeof(key));
  EXPECT_TRUE(hmac.SetKey(key, sizeof(key)));

  const char* data = "Hi There";
  EXPECT_TRUE(hmac.Do((XBYTE*)data, (XQWORD)strlen(data)));

  XSTRING stringhex;
  EXPECT_TRUE(hmac.GetResultString(stringhex));
  EXPECT_EQ(0, stringhex.Compare(__L("b617318655057264e28bc0b6fb378c8ef146be00"), true));
}


TEST(UNITTESTS_HASHHMAC_CLASSNAME, GetSetHashRoundtrip)
{
  HASHMD5 md5;
  HASHHMAC hmac;

  EXPECT_EQ(hmac.GetHash(), (HASH*)NULL);
  EXPECT_TRUE(hmac.SetHash(&md5));
  EXPECT_EQ(hmac.GetHash(), (HASH*)&md5);
}


TEST(UNITTESTS_HASHHMAC_CLASSNAME, DifferentKeysProduceDifferentMAC)
{
  HASHMD5 md5a;
  HASHMD5 md5b;
  HASHHMAC hmaca(&md5a);
  HASHHMAC hmacb(&md5b);

  XBYTE keya[16];
  XBYTE keyb[16];
  memset(keya, 0x01, sizeof(keya));
  memset(keyb, 0x02, sizeof(keyb));

  EXPECT_TRUE(hmaca.SetKey(keya, sizeof(keya)));
  EXPECT_TRUE(hmacb.SetKey(keyb, sizeof(keyb)));

  const char* data = "same message";
  EXPECT_TRUE(hmaca.Do((XBYTE*)data, (XQWORD)strlen(data)));
  EXPECT_TRUE(hmacb.Do((XBYTE*)data, (XQWORD)strlen(data)));

  XSTRING stringhexa;
  XSTRING stringhexb;
  EXPECT_TRUE(hmaca.GetResultString(stringhexa));
  EXPECT_TRUE(hmacb.GetResultString(stringhexb));

  EXPECT_NE(0, stringhexa.Compare(stringhexb, true));
}


}
#endif
