/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherCertificateX509.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERCERTIFICATEX509
* @brief      Cipher unit tests for CIPHERCERTIFICATEX509 class
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

#include "UnitTests_Cipher_CipherCertificateX509.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherCertificateX509.h"
#include "CipherKeyPublicRSA.h"
#include "XBuffer.h"
#include "XString.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

// Base64 body (no PEM header/footer) of a real, self-signed X509 certificate generated with
// `openssl req -new -x509` for this project (CN=Cipher UnitTests Test CA, RSA-2048/SHA-256,
// 10 year validity). Not a hand-typed/fake fixture.
static const char* UNITTESTS_CIPHER_TESTCERTIFICATE_BASE64 =
  "MIIDazCCAlOgAwIBAgIUGRvtpad1LBSkRUkjlv5inJpU7swwDQYJKoZIhvcNAQEL"
  "BQAwRTEhMB8GA1UEAwwYQ2lwaGVyIFVuaXRUZXN0cyBUZXN0IENBMRMwEQYDVQQK"
  "DApFbmRvcmFTb2Z0MQswCQYDVQQGEwJFUzAeFw0yNjA5MDQwNzIyMjJaFw0zNjA5"
  "MDEwNzIyMjJaMEUxITAfBgNVBAMMGENpcGhlciBVbml0VGVzdHMgVGVzdCBDQTET"
  "MBEGA1UECgwKRW5kb3JhU29mdDELMAkGA1UEBhMCRVMwggEiMA0GCSqGSIb3DQEB"
  "AQUAA4IBDwAwggEKAoIBAQDJkm4xo/7bJwCjHUluIGuNlvopYc6CR0R+giagx0MD"
  "IRQi7ORZLNkP4MQyLuA4zYqVr+tcpNNbXvmgSsB7/xj2Hk0d+Yu9HNnJh0/Hv745"
  "ivx2MMzUGBFWtgqLoC0AGitS6fNbKqM5qeSUlhGbLbBwzZ3wCh4zIiCiSnhSGClo"
  "lI29mlFbnLYceH2LurNQQXOF4ajH2XE6TwXOSfVGFVCdQ4d2B0ZIpMBGWT+Gmkx0"
  "cRFZ+rz/PPGzObcuOG6NFK9GeyuNhco6Xn9LkZ3XrwtGSbP5hBMgsk8+k8jCd3VH"
  "7FVZYqkS/W3LLsrWGySnq0Gt3KSynVg8MQQ5bjZNtHf9AgMBAAGjUzBRMB0GA1Ud"
  "DgQWBBQc7VNcagn2eyEdx5MmEtMNvjuzOzAfBgNVHSMEGDAWgBQc7VNcagn2eyEd"
  "x5MmEtMNvjuzOzAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQBo"
  "eq+oYsIV54wz5TmMLOe0Ptx16a1w6nT1GJJLCNG6E7sV0EQeZz243f1rpcimF57b"
  "4HDCOiCYPh1YVOqo+Yx1clgMqoRTjIixH4Nm8dpQFXH+rUvi6ZNQMdd9AqBnPQIQ"
  "YPZMjScXP9PGKwADrVtZDEZ3jBkAcZXyTSoSsVOVho6XBddgWdrmIwlyZscPsRS9"
  "gNL682yvHsHLcS33GKYmsv24NDT8Hb6BlmRLSrmWYcMnJdBFoXB40iKawQ8FrkBf"
  "08Orn1YAcykAawMdBd9kNcI3W+7d9b6ejuwgjBDpb7X4Mo6RbjV5hZjLBOWdQ6tg"
  "wJ5O25pVKsR6qT4Bolyu";


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


static bool DecodeTestCertificate(XBUFFER& der)
{
  XSTRING base64;
  base64.Set(UNITTESTS_CIPHER_TESTCERTIFICATE_BASE64);
  return der.ConvertFromBase64(base64);
}


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERCERTIFICATEX509
{


TEST(UNITTESTS_CIPHERCERTIFICATEX509_CLASSNAME, DecodeRealSelfSignedCertificateSucceeds)
{
  XBUFFER der;
  ASSERT_TRUE(DecodeTestCertificate(der));
  EXPECT_GT(der.GetSize(), (XDWORD)0);

  CIPHERCERTIFICATEX509 certificate;
  EXPECT_TRUE(certificate.Decode(der));

  // GetVersion() returns the human "vN" number (3), not the raw ASN.1-encoded INTEGER value
  // (2, since X509 versions are zero-indexed: v1=0, v2=1, v3=2) -- confirmed directly against
  // this real `openssl req -x509` certificate, which is a default X509v3 certificate.
  EXPECT_EQ(certificate.GetVersion(), (XWORD)3);
}


TEST(UNITTESTS_CIPHERCERTIFICATEX509_CLASSNAME, DecodedCertificateIsSelfSignedAndDateValid)
{
  XBUFFER der;
  ASSERT_TRUE(DecodeTestCertificate(der));

  CIPHERCERTIFICATEX509 certificate;
  ASSERT_TRUE(certificate.Decode(der));

  // Issuer == Subject, so this certificate is expected to be self-signed.
  EXPECT_TRUE(certificate.IsSelfSigned());

  // Generated with a 10-year (3650 day) validity period starting now, so "now" must fall inside
  // [notBefore, notAfter].
  EXPECT_TRUE(certificate.IsValidDates());
}


TEST(UNITTESTS_CIPHERCERTIFICATEX509_CLASSNAME, DecodedCertificateHasBasicConstraintsAsCA)
{
  XBUFFER der;
  ASSERT_TRUE(DecodeTestCertificate(der));

  CIPHERCERTIFICATEX509 certificate;
  ASSERT_TRUE(certificate.Decode(der));

  // Generated with `openssl req -x509`'s default v3 basic constraints (CA:TRUE) for a
  // self-signed certificate.
  EXPECT_TRUE(certificate.HasBasicConstraints());
  EXPECT_TRUE(certificate.IsCertificateAuthority());
}


TEST(UNITTESTS_CIPHERCERTIFICATEX509_CLASSNAME, DecodedCertificateSignatureVerifiesWithOwnPublicKey)
{
  // Self-signed: the certificate's own embedded public key must verify its own signature.
  XBUFFER der;
  ASSERT_TRUE(DecodeTestCertificate(der));

  CIPHERCERTIFICATEX509 certificate;
  ASSERT_TRUE(certificate.Decode(der));

  CIPHERKEY* publickey = certificate.GetPublicCipherKey();
  ASSERT_NE(publickey, (CIPHERKEY*)NULL);

  EXPECT_TRUE(certificate.VerifySignature(publickey));
}


TEST(UNITTESTS_CIPHERCERTIFICATEX509_CLASSNAME, DecodeRejectsGarbageDER)
{
  XBUFFER garbage;
  for(int c=0; c<64; c++) garbage.Add((XBYTE)0xAB);

  CIPHERCERTIFICATEX509 certificate;
  EXPECT_FALSE(certificate.Decode(garbage));
}


}
#endif
