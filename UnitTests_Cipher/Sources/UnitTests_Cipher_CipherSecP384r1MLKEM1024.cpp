/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherSecP384r1MLKEM1024.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERSECP384R1MLKEM1024
* @brief      Cipher unit tests for CIPHERSECP384R1MLKEM1024 class
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

#include "UnitTests_Cipher_CipherSecP384r1MLKEM1024.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherSecP384r1MLKEM1024.h"
#include "XBuffer.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERSECP384R1MLKEM1024
{


TEST(UNITTESTS_CIPHERSECP384R1MLKEM1024_CLASSNAME, ClientKeyShareCreateProducesExpectedSize)
{
  CIPHERSECP384R1MLKEM1024 client;

  XBUFFER clientshare;
  EXPECT_TRUE(client.ClientKeyShare_Create(clientshare));
  EXPECT_EQ(clientshare.GetSize(), (XDWORD)CIPHERSECP384R1MLKEM1024_CLIENTSHARESIZE);
}


TEST(UNITTESTS_CIPHERSECP384R1MLKEM1024_CLASSNAME, ClientServerHandshakeSharedSecretsMatch)
{
  // Hybrid TLS 1.3-style handshake: client sends its share, server derives its own share plus
  // the shared secret from it, client then derives the same shared secret from the server's
  // share -- both sides must agree.
  CIPHERSECP384R1MLKEM1024 client;
  XBUFFER clientshare;
  ASSERT_TRUE(client.ClientKeyShare_Create(clientshare));

  CIPHERSECP384R1MLKEM1024 server;
  XBUFFER servershare;
  XBUFFER serversecret;
  bool serverinvalid = false;
  ASSERT_TRUE(server.ServerKeyShare_Create(clientshare, servershare, serversecret, &serverinvalid));
  EXPECT_FALSE(serverinvalid);
  EXPECT_EQ(servershare.GetSize(), (XDWORD)CIPHERSECP384R1MLKEM1024_SERVERSHARESIZE);
  EXPECT_EQ(serversecret.GetSize(), (XDWORD)CIPHERSECP384R1MLKEM1024_SHAREDSECRETSIZE);

  XBUFFER clientsecret;
  bool clientinvalid = false;
  ASSERT_TRUE(client.ClientSharedSecret_Create(servershare, clientsecret, &clientinvalid));
  EXPECT_FALSE(clientinvalid);

  ASSERT_EQ(clientsecret.GetSize(), serversecret.GetSize());
  EXPECT_EQ(0, memcmp(clientsecret.Get(), serversecret.Get(), clientsecret.GetSize()));
}


TEST(UNITTESTS_CIPHERSECP384R1MLKEM1024_CLASSNAME, ClientSharedSecretRejectsGarbageServerShare)
{
  CIPHERSECP384R1MLKEM1024 client;
  XBUFFER clientshare;
  ASSERT_TRUE(client.ClientKeyShare_Create(clientshare));

  XBUFFER garbage;
  for(XDWORD c=0; c<CIPHERSECP384R1MLKEM1024_SERVERSHARESIZE; c++) garbage.Add((XBYTE)0xAB);

  XBUFFER clientsecret;
  bool invalid = false;
  client.ClientSharedSecret_Create(garbage, clientsecret, &invalid);
  EXPECT_TRUE(invalid);
}


}
#endif
