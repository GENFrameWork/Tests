/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherKeysFilePEM.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERKEYSFILEPEM
* @brief      Cipher unit tests for CIPHERKEYSFILEPEM class
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

#include "UnitTests_Cipher_CipherKeysFilePEM.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherKeysFilePEM.h"
#include "CipherKeySymmetrical.h"
#include "XString.h"
#include "XVector.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

// Same real self-signed certificate PEM used by UnitTests_Cipher_CipherCertificateX509.cpp /
// UnitTests_Cipher_CipherCredentialsLoader.cpp (generated with `openssl req -new -x509` for
// this project), split line-by-line here since DecodeCertificates() takes an XVECTOR<XSTRING*>
// of already-split lines (the shape a line-oriented file reader would hand it).
static const char* UNITTESTS_CIPHER_TESTCERTIFICATE_LINES[] =
{
  "-----BEGIN CERTIFICATE-----",
  "MIIDazCCAlOgAwIBAgIUGRvtpad1LBSkRUkjlv5inJpU7swwDQYJKoZIhvcNAQEL",
  "BQAwRTEhMB8GA1UEAwwYQ2lwaGVyIFVuaXRUZXN0cyBUZXN0IENBMRMwEQYDVQQK",
  "DApFbmRvcmFTb2Z0MQswCQYDVQQGEwJFUzAeFw0yNjA5MDQwNzIyMjJaFw0zNjA5",
  "MDEwNzIyMjJaMEUxITAfBgNVBAMMGENpcGhlciBVbml0VGVzdHMgVGVzdCBDQTET",
  "MBEGA1UECgwKRW5kb3JhU29mdDELMAkGA1UEBhMCRVMwggEiMA0GCSqGSIb3DQEB",
  "AQUAA4IBDwAwggEKAoIBAQDJkm4xo/7bJwCjHUluIGuNlvopYc6CR0R+giagx0MD",
  "IRQi7ORZLNkP4MQyLuA4zYqVr+tcpNNbXvmgSsB7/xj2Hk0d+Yu9HNnJh0/Hv745",
  "ivx2MMzUGBFWtgqLoC0AGitS6fNbKqM5qeSUlhGbLbBwzZ3wCh4zIiCiSnhSGClo",
  "lI29mlFbnLYceH2LurNQQXOF4ajH2XE6TwXOSfVGFVCdQ4d2B0ZIpMBGWT+Gmkx0",
  "cRFZ+rz/PPGzObcuOG6NFK9GeyuNhco6Xn9LkZ3XrwtGSbP5hBMgsk8+k8jCd3VH",
  "7FVZYqkS/W3LLsrWGySnq0Gt3KSynVg8MQQ5bjZNtHf9AgMBAAGjUzBRMB0GA1Ud",
  "DgQWBBQc7VNcagn2eyEdx5MmEtMNvjuzOzAfBgNVHSMEGDAWgBQc7VNcagn2eyEd",
  "x5MmEtMNvjuzOzAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQBo",
  "eq+oYsIV54wz5TmMLOe0Ptx16a1w6nT1GJJLCNG6E7sV0EQeZz243f1rpcimF57b",
  "4HDCOiCYPh1YVOqo+Yx1clgMqoRTjIixH4Nm8dpQFXH+rUvi6ZNQMdd9AqBnPQIQ",
  "YPZMjScXP9PGKwADrVtZDEZ3jBkAcZXyTSoSsVOVho6XBddgWdrmIwlyZscPsRS9",
  "gNL682yvHsHLcS33GKYmsv24NDT8Hb6BlmRLSrmWYcMnJdBFoXB40iKawQ8FrkBf",
  "08Orn1YAcykAawMdBd9kNcI3W+7d9b6ejuwgjBDpb7X4Mo6RbjV5hZjLBOWdQ6tg",
  "wJ5O25pVKsR6qT4Bolyu",
  "-----END CERTIFICATE-----"
};

#define UNITTESTS_CIPHER_TESTCERTIFICATE_LINECOUNT \
  (sizeof(UNITTESTS_CIPHER_TESTCERTIFICATE_LINES) / sizeof(UNITTESTS_CIPHER_TESTCERTIFICATE_LINES[0]))


static void BuildLinesVector(XVECTOR<XSTRING*>& lines, const char** rawlines, XDWORD count)
{
  for(XDWORD c=0; c<count; c++)
    {
      XSTRING* line = new XSTRING();
      line->Set(rawlines[c]);
      lines.Add(line);
    }
}


static void DeleteLinesVector(XVECTOR<XSTRING*>& lines)
{
  for(XDWORD c=0; c<lines.GetSize(); c++) delete lines.Get(c);
  lines.DeleteAll();
}


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERKEYSFILEPEM
{


TEST(UNITTESTS_CIPHERKEYSFILEPEM_CLASSNAME, KeyAddDelRoundtrip)
{
  // Key_Del() takes ownership and deletes the key itself (GEN_DELETE key;) -- confirmed by
  // reading CipherKeysFilePEM.cpp -- so the key must NOT also be deleted by the caller here.
  CIPHERKEYSFILEPEM pemfile;

  CIPHERKEYSYMMETRICAL* key = new CIPHERKEYSYMMETRICAL();
  key->SetType(CIPHERKEYTYPE_SYMMETRICAL);

  EXPECT_TRUE(pemfile.Key_Add(key));
  EXPECT_TRUE(pemfile.Key_Del(key));
}


TEST(UNITTESTS_CIPHERKEYSFILEPEM_CLASSNAME, KeyDelAllOwnsAndFreesAddedKeys)
{
  CIPHERKEYSFILEPEM pemfile;

  CIPHERKEYSYMMETRICAL* key = new CIPHERKEYSYMMETRICAL();
  key->SetType(CIPHERKEYTYPE_SYMMETRICAL);

  ASSERT_TRUE(pemfile.Key_Add(key));

  // Key_DelAll() (and the destructor, which calls it) deletes the CIPHERKEY objects it owns --
  // this only proves it runs without crashing; the key pointer itself is now dangling.
  EXPECT_TRUE(pemfile.Key_DelAll());
}


TEST(UNITTESTS_CIPHERKEYSFILEPEM_CLASSNAME, DecodeCertificatesParsesRealSelfSignedCertificate)
{
  // Real certificate content (see UNITTESTS_CIPHER_TESTCERTIFICATE_LINES above), pre-split into
  // lines the way a line-oriented PEM file reader would hand them to DecodeCertificates().
  XVECTOR<XSTRING*> lines;
  BuildLinesVector(lines, UNITTESTS_CIPHER_TESTCERTIFICATE_LINES, (XDWORD)UNITTESTS_CIPHER_TESTCERTIFICATE_LINECOUNT);

  CIPHERKEYSFILEPEM pemfile;
  EXPECT_TRUE(pemfile.DecodeCertificates(&lines));

  DeleteLinesVector(lines);
}


TEST(UNITTESTS_CIPHERKEYSFILEPEM_CLASSNAME, DecodeCertificatesWithNoMarkersIsANoOp)
{
  // No "-----BEGIN .../-----END ..." markers at all -- no PEM entry is ever opened, so the
  // scan finds nothing to decode and simply returns true having done nothing (confirmed by
  // reading CIPHERKEYSFILEPEM::DecodeCertificates(): the loop is a no-op and the function
  // always returns true once no partially-open entry remains).
  static const char* plainlines[] =
  {
    "just some unrelated text",
    "with no PEM markers at all"
  };

  XVECTOR<XSTRING*> lines;
  BuildLinesVector(lines, plainlines, 2);

  CIPHERKEYSFILEPEM pemfile;
  EXPECT_TRUE(pemfile.DecodeCertificates(&lines));

  DeleteLinesVector(lines);
}


}
#endif
