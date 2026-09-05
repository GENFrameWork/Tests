/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherTrustedRootCertificatesX509.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERTRUSTEDROOTCERTIFICATESX509
* @brief      Cipher unit tests for CIPHERTRUSTEDROOTCERTIFICATESX509 / CIPHERTRUSTPROVIDERX509 classes
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

#include "UnitTests_Cipher_CipherTrustedRootCertificatesX509.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherTrustedRootCertificatesX509.h"
#include "XString.h"
#include "XBuffer.h"
#include "XVector.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

// Same real self-signed certificate PEM used by the other UnitTests_Cipher X509 modules
// (generated with `openssl req -new -x509` for this project), pre-split into lines the way
// CIPHERTRUSTEDROOTCERTIFICATESX509::ReadFromFile() would leave GetLines() populated.
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


static void FillLines(XVECTOR<XSTRING*>* lines, const char** rawlines, XDWORD count)
{
  for(XDWORD c=0; c<count; c++)
    {
      XSTRING* line = new XSTRING();
      line->Set(rawlines[c]);
      lines->Add(line);
    }
}


// Minimal concrete CIPHERTRUSTPROVIDERX509 subclass: the base class is abstract (Load()=0), and
// the real CIPHERTRUSTPROVIDERX509GEN subclass depends on an embedded default root-CA bundle
// this sandbox does not provide -- this local subclass exercises the base class's own
// Root_Add/Root_Remove/GetRoots/SetLimits/GetTotalSize logic directly instead.
class UNITTESTS_CIPHER_TRUSTPROVIDERFAKE : public CIPHERTRUSTPROVIDERX509
{
  public:
    bool Load() { return true; }
};


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERTRUSTEDROOTCERTIFICATESX509
{


TEST(UNITTESTS_CIPHERTRUSTEDROOTCERTIFICATESX509_CLASSNAME, CertificatesDecodeParsesRealSelfSignedCertificate)
{
  CIPHERTRUSTEDROOTCERTIFICATESX509 roots;

  // The constructor pre-populates GetLines() with GEN's own embedded default trusted-root CA
  // bundle (confirmed by reading the constructor) -- drop those first so this test isolates
  // decoding down to just the one certificate it adds itself.
  roots.DeleteAllLines();
  ASSERT_EQ(roots.GetLines()->GetSize(), (XDWORD)0);

  FillLines(roots.GetLines(), UNITTESTS_CIPHER_TESTCERTIFICATE_LINES, (XDWORD)UNITTESTS_CIPHER_TESTCERTIFICATE_LINECOUNT);

  EXPECT_TRUE(roots.Certificates_Decode());

  ASSERT_NE(roots.Certificates_GetAll(), (XVECTOR<XBUFFER*>*)NULL);
  ASSERT_EQ(roots.Certificates_GetAll()->GetSize(), (XDWORD)1);
  EXPECT_GT(roots.Certificates_GetAll()->Get(0)->GetSize(), (XDWORD)0);

  EXPECT_TRUE(roots.Certificates_DeleteAll());
  EXPECT_EQ(roots.Certificates_GetAll()->GetSize(), (XDWORD)0);
}


TEST(UNITTESTS_CIPHERTRUSTEDROOTCERTIFICATESX509_CLASSNAME, CertificatesDecodeRejectsUnterminatedBlock)
{
  static const char* badlines[] =
  {
    "-----BEGIN CERTIFICATE-----",
    "MIIB", // no matching END line
  };

  CIPHERTRUSTEDROOTCERTIFICATESX509 roots;
  FillLines(roots.GetLines(), badlines, 2);

  EXPECT_FALSE(roots.Certificates_Decode());
}


TEST(UNITTESTS_CIPHERTRUSTEDROOTCERTIFICATESX509_CLASSNAME, DeleteAllLinesEmptiesLineList)
{
  CIPHERTRUSTEDROOTCERTIFICATESX509 roots;

  FillLines(roots.GetLines(), UNITTESTS_CIPHER_TESTCERTIFICATE_LINES, (XDWORD)UNITTESTS_CIPHER_TESTCERTIFICATE_LINECOUNT);
  ASSERT_GT(roots.GetLines()->GetSize(), (XDWORD)0);

  EXPECT_TRUE(roots.DeleteAllLines());
  EXPECT_EQ(roots.GetLines()->GetSize(), (XDWORD)0);
}


TEST(UNITTESTS_CIPHERTRUSTEDROOTCERTIFICATESX509_CLASSNAME, TrustProviderRootAddRemoveRoundtrip)
{
  UNITTESTS_CIPHER_TRUSTPROVIDERFAKE provider;

  XBUFFER root;
  for(int c=0; c<32; c++) root.Add((XBYTE)(c+1));

  EXPECT_TRUE(provider.Root_Add(root));
  ASSERT_NE(provider.GetRoots(), (XVECTOR<XBUFFER*>*)NULL);
  EXPECT_EQ(provider.GetRoots()->GetSize(), (XDWORD)1);
  EXPECT_GT(provider.GetTotalSize(), (XDWORD)0);

  EXPECT_TRUE(provider.Root_Remove(root));
  EXPECT_EQ(provider.GetRoots()->GetSize(), (XDWORD)0);
}


TEST(UNITTESTS_CIPHERTRUSTEDROOTCERTIFICATESX509_CLASSNAME, TrustProviderSetLimitsRejectsRootBeyondMaxCount)
{
  UNITTESTS_CIPHER_TRUSTPROVIDERFAKE provider;

  ASSERT_TRUE(provider.SetLimits(1, 1024, 1024*1024));

  XBUFFER root1;
  for(int c=0; c<16; c++) root1.Add((XBYTE)c);
  XBUFFER root2;
  for(int c=0; c<16; c++) root2.Add((XBYTE)(c+100));

  EXPECT_TRUE(provider.Root_Add(root1));
  // Maximum root count is 1 -- a second root must be rejected.
  EXPECT_FALSE(provider.Root_Add(root2));
  EXPECT_EQ(provider.GetRoots()->GetSize(), (XDWORD)1);
}


}
#endif
