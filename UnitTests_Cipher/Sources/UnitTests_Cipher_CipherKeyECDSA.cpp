/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherKeyECDSA.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERKEYECDSA
* @brief      Cipher unit tests for CIPHERKEYECDSA class
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

#include "UnitTests_Cipher_CipherKeyECDSA.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherKeyECDSA.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERKEYECDSA
{


TEST(UNITTESTS_CIPHERKEYECDSA_CLASSNAME, SetTypeGetTypeRoundtrip)
{
  CIPHERKEYECDSA key;

  key.SetType(CIPHERKEYTYPE_ECDSA_SECP256R1_PUBLIC);
  EXPECT_EQ(key.GetType(), CIPHERKEYTYPE_ECDSA_SECP256R1_PUBLIC);
}


TEST(UNITTESTS_CIPHERKEYECDSA_CLASSNAME, SetGetRawBytesRoundtrip)
{
  CIPHERKEYECDSA key;
  key.SetType(CIPHERKEYTYPE_ECDSA_SECP256R1_PRIVATE);

  XBYTE rawkey[32];
  for(int c=0; c<32; c++) rawkey[c] = (XBYTE)c;

  EXPECT_TRUE(key.Set(rawkey, sizeof(rawkey)));

  int size = 0;
  XBYTE* result = key.Get(size);
  ASSERT_NE(result, (XBYTE*)NULL);
  EXPECT_EQ(size, 32);
  EXPECT_EQ(0, memcmp(result, rawkey, 32));
}


}
#endif
