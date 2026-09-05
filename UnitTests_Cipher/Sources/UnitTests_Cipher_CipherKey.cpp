/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherKey.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERKEY
* @brief      Cipher unit tests for CIPHERKEY class
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

#include "UnitTests_Cipher_CipherKey.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherKey.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERKEY
{


TEST(UNITTESTS_CIPHERKEY_CLASSNAME, DefaultTypeIsUnknown)
{
  CIPHERKEY key;

  EXPECT_EQ(key.GetType(), CIPHERKEYTYPE_UNKNOWN);
}


TEST(UNITTESTS_CIPHERKEY_CLASSNAME, SetTypeGetTypeRoundtrip)
{
  CIPHERKEY key;

  key.SetType(CIPHERKEYTYPE_RSA_PUBLIC);
  EXPECT_EQ(key.GetType(), CIPHERKEYTYPE_RSA_PUBLIC);

  key.SetType(CIPHERKEYTYPE_ED25519_PRIVATE);
  EXPECT_EQ(key.GetType(), CIPHERKEYTYPE_ED25519_PRIVATE);
}


TEST(UNITTESTS_CIPHERKEY_CLASSNAME, GetTypeStrIsNotNull)
{
  CIPHERKEY key;

  key.SetType(CIPHERKEYTYPE_SYMMETRICAL);
  EXPECT_NE(key.GetTypeStr(), (XCHAR*)NULL);
}


TEST(UNITTESTS_CIPHERKEY_CLASSNAME, DefaultSizeInBytesIsZero)
{
  CIPHERKEY key;

  EXPECT_EQ(key.GetSizeInBytes(), 0);
  EXPECT_EQ(key.GetSizeInBits(), 0);
}


TEST(UNITTESTS_CIPHERKEY_CLASSNAME, CopyFromCopiesType)
{
  CIPHERKEY key1;
  CIPHERKEY key2;

  key1.SetType(CIPHERKEYTYPE_RSA_PRIVATE);

  EXPECT_TRUE(key2.CopyFrom(&key1));
  EXPECT_EQ(key2.GetType(), CIPHERKEYTYPE_RSA_PRIVATE);
}


TEST(UNITTESTS_CIPHERKEY_CLASSNAME, CopyFromNullFails)
{
  CIPHERKEY key;

  EXPECT_FALSE(key.CopyFrom(NULL));
}


}
#endif
