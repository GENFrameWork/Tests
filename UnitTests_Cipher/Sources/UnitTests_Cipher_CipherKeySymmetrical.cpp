/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherKeySymmetrical.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERKEYSYMMETRICAL
* @brief      Cipher unit tests for CIPHERKEYSYMMETRICAL class
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

#include "UnitTests_Cipher_CipherKeySymmetrical.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherKeySymmetrical.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERKEYSYMMETRICAL
{


TEST(UNITTESTS_CIPHERKEYSYMMETRICAL_CLASSNAME, SetGetRoundtrip)
{
  CIPHERKEYSYMMETRICAL key;

  XBYTE rawkey[16];
  for(int c=0; c<16; c++) rawkey[c] = (XBYTE)c;

  EXPECT_TRUE(key.Set(rawkey, sizeof(rawkey)));

  int size = 0;
  XBYTE* result = key.Get(size);
  ASSERT_NE(result, (XBYTE*)NULL);
  EXPECT_EQ(size, 16);
  EXPECT_EQ(0, memcmp(result, rawkey, 16));
}


TEST(UNITTESTS_CIPHERKEYSYMMETRICAL_CLASSNAME, GetSizeInBytesMatchesSetSize)
{
  CIPHERKEYSYMMETRICAL key;

  XBYTE rawkey[32];
  memset(rawkey, 0xAA, sizeof(rawkey));

  EXPECT_TRUE(key.Set(rawkey, sizeof(rawkey)));
  EXPECT_EQ(key.GetSizeInBytes(), 32);
}


TEST(UNITTESTS_CIPHERKEYSYMMETRICAL_CLASSNAME, SetFromXBufferRoundtrip)
{
  CIPHERKEYSYMMETRICAL key;

  XBUFFER xbuffer;
  xbuffer.Add((XBYTE)0x01);
  xbuffer.Add((XBYTE)0x02);
  xbuffer.Add((XBYTE)0x03);
  xbuffer.Add((XBYTE)0x04);

  EXPECT_TRUE(key.Set(xbuffer));

  XBUFFER* result = key.Get();
  ASSERT_NE(result, (XBUFFER*)NULL);
  EXPECT_EQ(result->GetSize(), (XDWORD)4);
}


TEST(UNITTESTS_CIPHERKEYSYMMETRICAL_CLASSNAME, CopyFromCopiesKeyBytes)
{
  CIPHERKEYSYMMETRICAL key1;
  CIPHERKEYSYMMETRICAL key2;

  XBYTE rawkey[8] = { 1,2,3,4,5,6,7,8 };
  EXPECT_TRUE(key1.Set(rawkey, sizeof(rawkey)));

  EXPECT_TRUE(key2.CopyFrom(&key1));

  int size = 0;
  XBYTE* result = key2.Get(size);
  ASSERT_NE(result, (XBYTE*)NULL);
  EXPECT_EQ(size, 8);
  EXPECT_EQ(0, memcmp(result, rawkey, 8));
}


}
#endif
