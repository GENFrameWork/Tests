/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherPEMCodec.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERPEMCODEC
* @brief      Cipher unit tests for CIPHERPEMCODEC class
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

#include "UnitTests_Cipher_CipherPEMCodec.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherPEMCodec.h"
#include "XBuffer.h"
#include "XString.h"
#include "XMPInteger.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

// Real 2048-bit RSA private key (PKCS1 "RSAPrivateKey" DER, base64-encoded, no PEM
// header/footer) generated via `openssl genrsa`/`openssl rsa -traditional` for this project --
// not a hand-typed/fake fixture.
static const char* UNITTESTS_CIPHER_TESTRSAPKCS1_BASE64 =
  "MIIEoAIBAAKCAQEAyZJuMaP+2ycAox1JbiBrjZb6KWHOgkdEfoImoMdDAyEUIuzkWSzZD+DEMi7g"
  "OM2Kla/rXKTTW175oErAe/8Y9h5NHfmLvRzZyYdPx7++OYr8djDM1BgRVrYKi6AtABorUunzWyqj"
  "OanklJYRmy2wcM2d8AoeMyIgokp4UhgpaJSNvZpRW5y2HHh9i7qzUEFzheGox9lxOk8Fzkn1RhVQ"
  "nUOHdgdGSKTARlk/hppMdHERWfq8/zzxszm3LjhujRSvRnsrjYXKOl5/S5Gd168LRkmz+YQTILJP"
  "PpPIwnd1R+xVWWKpEv1tyy7K1hskp6tBrdyksp1YPDEEOW42TbR3/QIDAQABAoH/d/7tI4LadPy7"
  "GSUB7uF7HIhOXV9z24z7GyfASaeZCDv/YVZxJN92VBvHkOJmrQc6hU+1xWA6dt8q1FbdL91PlB4w"
  "JnV0dhzHjksLbug+bWybLO3iaRir7WHtC1x0VxxcfwCgsJipegVcCHsubgSZMJbmaQvA2nMvz4gg"
  "lCXU0aDWJk0HPyabn4zLi8K9gj9e5qgCM+SX2rcx7zJLLKCNciV1eMOsrXlNAJ5FIWUajK2GLeIO"
  "XfI3CXJhBrQiea2OS/XYWcXFqxeCrwuoZyPl033rc/TRu2hpZTGZeaBpn0pLB5bNDi3/uYKjBPU2"
  "XmFnRRF/4RVFsre+ODI+S62pAoGBAPhFuWdgYD4vJuZNx8sVmTCljNtD/dmROzWpxRhgMD7Q5Yae"
  "e4VjdxpkdlQNHSTo8/XiYGavMNDbHNtFK1MNwRod4CPHzGi/hKzPDtKMmpXXjxOpqo6b/7zSWcY3"
  "G6xLcqSntx/Ijm4FOVPqVTo2GXeQGIXPTClW8xP1RzzT7CglAoGBAM/YlwGJW3cApM/NtrhFQe35"
  "RO4jwGF0Ybrv/IiyocEcjZSyAEiKbRyEgZYaB80oSmuMo3BGoLn/6bymq7ff+q9kjNpLDkqsa3cq"
  "t9dd7SngPe//A9Bw9EFXkzeuytVKvxKYL01MHcqOXrbX8VlBafmeyEmmGBLJlhRazIMMefz5AoGA"
  "ZuHN4O7pMxurDQjyYFAE+UnBQyO70CsE1EoT6PQDSiSa2NqvkSkUtBUpi88bYq4+WoiC1kqG+iWy"
  "oZLaT0KF4OK8fVdQd5/VxR7Qz6OAc9Ot8MIAcbRnl8G7fg5cI1vomB8AHeWoUCNODF4xDzxX9Vn7"
  "L4gl0YO8m2qrKKPRWxkCgYB0zpU20NntTBhTjJm2f32o3uDFMKRqYHyYEU0MCc/r9j7/JPYRznG5"
  "iCJHmANwYcdJH/WuIJMtVMwoMEbrBF4e+dRKzcmPX8zZYNGGoIurcBF+8gNTvlcW7b+XmIz3R5WQ"
  "PqS+vRs0/cPu3/cMIT4MghavhT+cN1w3vjuXHojkCQKBgFLrqvBuw11/iGUzr5ltBSBAE0C+95ar"
  "Yr7jpA81ahwUYYPoy8AH4V03negYdLHHKRLFg9OmcMeGjTevmgsg75aJrtN+c+66sjgNt8e1bDYL"
  "pcOWUTLMwalbrSScvzhR49SG6zig3HnU9HneJWjgsPDdAz74qG5v7aOBRAwiRN4y";


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERPEMCODEC
{


TEST(UNITTESTS_CIPHERPEMCODEC_CLASSNAME, IsPEMRecognisesPEMHeaderRejectsRawDER)
{
  XBUFFER pemtext;
  const char* pem = "-----BEGIN CERTIFICATE-----\nMIIB\n-----END CERTIFICATE-----\n";
  pemtext.Add((XBYTE*)pem, (XDWORD)strlen(pem));

  EXPECT_TRUE(CIPHERPEMCODEC::IsPEM(pemtext));

  XBUFFER rawder;
  for(int c=0; c<16; c++) rawder.Add((XBYTE)(c*7));

  EXPECT_FALSE(CIPHERPEMCODEC::IsPEM(rawder));
}


TEST(UNITTESTS_CIPHERPEMCODEC_CLASSNAME, RSAPrivateKeyDecodeRecoversRealPKCS1Key)
{
  // Real 2048-bit RSA key material (see UNITTESTS_CIPHER_TESTRSAPKCS1_BASE64 above): decode its
  // base64 body into DER, then decode the PKCS1 RSAPrivateKey DER structure itself.
  XSTRING base64;
  base64.Set(UNITTESTS_CIPHER_TESTRSAPKCS1_BASE64);

  XBUFFER der;
  ASSERT_TRUE(der.ConvertFromBase64(base64));
  EXPECT_GT(der.GetSize(), (XDWORD)0);

  XMPINTEGER prime1;
  XMPINTEGER prime2;
  XMPINTEGER exponent;

  EXPECT_TRUE(CIPHERPEMCODEC::RSAPrivateKey_Decode(der, prime1, prime2, exponent));

  // A 2048-bit RSA modulus factors into two ~1024-bit (~128 byte) primes.
  EXPECT_GT(prime1.GetSize(), (XDWORD)120);
  EXPECT_GT(prime2.GetSize(), (XDWORD)120);
}


TEST(UNITTESTS_CIPHERPEMCODEC_CLASSNAME, RSAPrivateKeyDecodeRejectsGarbageDER)
{
  XBUFFER garbage;
  for(int c=0; c<64; c++) garbage.Add((XBYTE)0xAB);

  XMPINTEGER prime1;
  XMPINTEGER prime2;
  XMPINTEGER exponent;

  EXPECT_FALSE(CIPHERPEMCODEC::RSAPrivateKey_Decode(garbage, prime1, prime2, exponent));
}


}
#endif
