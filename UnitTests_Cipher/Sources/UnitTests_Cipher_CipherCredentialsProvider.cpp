/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Cipher_CipherCredentialsProvider.cpp
*
* @class      UNITTESTS_CIPHER_CIPHERCREDENTIALSPROVIDER
* @brief      Cipher unit tests for CIPHERCREDENTIALSPROVIDER class
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

#include "UnitTests_Cipher_CipherCredentialsProvider.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CipherCredentialsProvider.h"
#include "CipherCredentialsLoader.h"
#include "CipherKeyPrivateRSA.h"
#include "XBuffer.h"
#include "XString.h"

#include <string.h>


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_CIPHERCREDENTIALSPROVIDER
{


TEST(UNITTESTS_CIPHERCREDENTIALSPROVIDER_CLASSNAME, SecretProviderStringReturnsConfiguredSource)
{
  XSTRING source;
  source.Set(__L("s3cr3t-password"));

  CIPHERSECRETPROVIDERSTRING provider;
  provider.SetSource(&source);

  XSTRING secret;
  EXPECT_TRUE(provider.Secret_Get(secret));
  EXPECT_TRUE(secret.Compare(source) == 0);
}


TEST(UNITTESTS_CIPHERCREDENTIALSPROVIDER_CLASSNAME, SecretProviderStringWithoutSourceReturnsEmptySecret)
{
  // No source XSTRING* was ever set (still NULL): Secret_Get() treats "no source" as "no
  // password" rather than as an error -- it returns true with an empty secret, not false.
  CIPHERSECRETPROVIDERSTRING provider;

  XSTRING secret;
  EXPECT_TRUE(provider.Secret_Get(secret));
  EXPECT_TRUE(secret.IsEmpty());
}


TEST(UNITTESTS_CIPHERCREDENTIALSPROVIDER_CLASSNAME, CredentialsProviderBufferRequiresBothCertificateAndKey)
{
  CIPHERCREDENTIALSPROVIDERBUFFER provider;

  XVECTOR<XBUFFER*> chain;
  CIPHERKEY* privatekey = NULL;

  // Neither certificate nor private-key buffers have been set yet.
  EXPECT_FALSE(provider.Credentials_Load(chain, privatekey));
}


TEST(UNITTESTS_CIPHERCREDENTIALSPROVIDER_CLASSNAME, CredentialsProviderBufferLoadsRealCertificateAndKey)
{
  const char* certpem =
    "-----BEGIN CERTIFICATE-----\n"
    "MIIDazCCAlOgAwIBAgIUGRvtpad1LBSkRUkjlv5inJpU7swwDQYJKoZIhvcNAQEL\n"
    "BQAwRTEhMB8GA1UEAwwYQ2lwaGVyIFVuaXRUZXN0cyBUZXN0IENBMRMwEQYDVQQK\n"
    "DApFbmRvcmFTb2Z0MQswCQYDVQQGEwJFUzAeFw0yNjA5MDQwNzIyMjJaFw0zNjA5\n"
    "MDEwNzIyMjJaMEUxITAfBgNVBAMMGENpcGhlciBVbml0VGVzdHMgVGVzdCBDQTET\n"
    "MBEGA1UECgwKRW5kb3JhU29mdDELMAkGA1UEBhMCRVMwggEiMA0GCSqGSIb3DQEB\n"
    "AQUAA4IBDwAwggEKAoIBAQDJkm4xo/7bJwCjHUluIGuNlvopYc6CR0R+giagx0MD\n"
    "IRQi7ORZLNkP4MQyLuA4zYqVr+tcpNNbXvmgSsB7/xj2Hk0d+Yu9HNnJh0/Hv745\n"
    "ivx2MMzUGBFWtgqLoC0AGitS6fNbKqM5qeSUlhGbLbBwzZ3wCh4zIiCiSnhSGClo\n"
    "lI29mlFbnLYceH2LurNQQXOF4ajH2XE6TwXOSfVGFVCdQ4d2B0ZIpMBGWT+Gmkx0\n"
    "cRFZ+rz/PPGzObcuOG6NFK9GeyuNhco6Xn9LkZ3XrwtGSbP5hBMgsk8+k8jCd3VH\n"
    "7FVZYqkS/W3LLsrWGySnq0Gt3KSynVg8MQQ5bjZNtHf9AgMBAAGjUzBRMB0GA1Ud\n"
    "DgQWBBQc7VNcagn2eyEdx5MmEtMNvjuzOzAfBgNVHSMEGDAWgBQc7VNcagn2eyEd\n"
    "x5MmEtMNvjuzOzAPBgNVHRMBAf8EBTADAQH/MA0GCSqGSIb3DQEBCwUAA4IBAQBo\n"
    "eq+oYsIV54wz5TmMLOe0Ptx16a1w6nT1GJJLCNG6E7sV0EQeZz243f1rpcimF57b\n"
    "4HDCOiCYPh1YVOqo+Yx1clgMqoRTjIixH4Nm8dpQFXH+rUvi6ZNQMdd9AqBnPQIQ\n"
    "YPZMjScXP9PGKwADrVtZDEZ3jBkAcZXyTSoSsVOVho6XBddgWdrmIwlyZscPsRS9\n"
    "gNL682yvHsHLcS33GKYmsv24NDT8Hb6BlmRLSrmWYcMnJdBFoXB40iKawQ8FrkBf\n"
    "08Orn1YAcykAawMdBd9kNcI3W+7d9b6ejuwgjBDpb7X4Mo6RbjV5hZjLBOWdQ6tg\n"
    "wJ5O25pVKsR6qT4Bolyu\n"
    "-----END CERTIFICATE-----\n";

  XBUFFER certdata;
  certdata.Add((XBYTE*)certpem, (XDWORD)strlen(certpem));

  const char* keypem =
    "-----BEGIN PRIVATE KEY-----\n"
    "MIIEugIBADANBgkqhkiG9w0BAQEFAASCBKQwggSgAgEAAoIBAQDJkm4xo/7bJwCj\n"
    "HUluIGuNlvopYc6CR0R+giagx0MDIRQi7ORZLNkP4MQyLuA4zYqVr+tcpNNbXvmg\n"
    "SsB7/xj2Hk0d+Yu9HNnJh0/Hv745ivx2MMzUGBFWtgqLoC0AGitS6fNbKqM5qeSU\n"
    "lhGbLbBwzZ3wCh4zIiCiSnhSGClolI29mlFbnLYceH2LurNQQXOF4ajH2XE6TwXO\n"
    "SfVGFVCdQ4d2B0ZIpMBGWT+Gmkx0cRFZ+rz/PPGzObcuOG6NFK9GeyuNhco6Xn9L\n"
    "kZ3XrwtGSbP5hBMgsk8+k8jCd3VH7FVZYqkS/W3LLsrWGySnq0Gt3KSynVg8MQQ5\n"
    "bjZNtHf9AgMBAAECgf93/u0jgtp0/LsZJQHu4XsciE5dX3PbjPsbJ8BJp5kIO/9h\n"
    "VnEk33ZUG8eQ4matBzqFT7XFYDp23yrUVt0v3U+UHjAmdXR2HMeOSwtu6D5tbJss\n"
    "7eJpGKvtYe0LXHRXHFx/AKCwmKl6BVwIey5uBJkwluZpC8Dacy/PiCCUJdTRoNYm\n"
    "TQc/JpufjMuLwr2CP17mqAIz5JfatzHvMkssoI1yJXV4w6yteU0AnkUhZRqMrYYt\n"
    "4g5d8jcJcmEGtCJ5rY5L9dhZxcWrF4KvC6hnI+XTfetz9NG7aGllMZl5oGmfSksH\n"
    "ls0OLf+5gqME9TZeYWdFEX/hFUWyt744Mj5LrakCgYEA+EW5Z2BgPi8m5k3HyxWZ\n"
    "MKWM20P92ZE7NanFGGAwPtDlhpp7hWN3GmR2VA0dJOjz9eJgZq8w0Nsc20UrUw3B\n"
    "Gh3gI8fMaL+ErM8O0oyaldePE6mqjpv/vNJZxjcbrEtypKe3H8iObgU5U+pVOjYZ\n"
    "d5AYhc9MKVbzE/VHPNPsKCUCgYEAz9iXAYlbdwCkz822uEVB7flE7iPAYXRhuu/8\n"
    "iLKhwRyNlLIASIptHISBlhoHzShKa4yjcEaguf/pvKart9/6r2SM2ksOSqxrdyq3\n"
    "113tKeA97/8D0HD0QVeTN67K1Uq/EpgvTUwdyo5ettfxWUFp+Z7ISaYYEsmWFFrM\n"
    "gwx5/PkCgYBm4c3g7ukzG6sNCPJgUAT5ScFDI7vQKwTUShPo9ANKJJrY2q+RKRS0\n"
    "FSmLzxtirj5aiILWSob6JbKhktpPQoXg4rx9V1B3n9XFHtDPo4Bz063wwgBxtGeX\n"
    "wbt+DlwjW+iYHwAd5ahQI04MXjEPPFf1WfsviCXRg7ybaqsoo9FbGQKBgHTOlTbQ\n"
    "2e1MGFOMmbZ/faje4MUwpGpgfJgRTQwJz+v2Pv8k9hHOcbmIIkeYA3Bhx0kf9a4g\n"
    "ky1UzCgwRusEXh751ErNyY9fzNlg0Yagi6twEX7yA1O+Vxbtv5eYjPdHlZA+pL69\n"
    "GzT9w+7f9wwhPgyCFq+FP5w3XDe+O5ceiOQJAoGAUuuq8G7DXX+IZTOvmW0FIEAT\n"
    "QL73lqtivuOkDzVqHBRhg+jLwAfhXTed6Bh0sccpEsWD06Zwx4aNN6+aCyDvlomu\n"
    "035z7rqyOA23x7VsNgulw5ZRMszBqVutJJy/OFHj1IbrOKDcedT0ed4laOCw8N0D\n"
    "Pviobm/to4FEDCJE3jI=\n"
    "-----END PRIVATE KEY-----\n";

  XBUFFER keydata;
  keydata.Add((XBYTE*)keypem, (XDWORD)strlen(keypem));

  CIPHERCREDENTIALSPROVIDERBUFFER provider;
  provider.SetCertificateData(&certdata);
  provider.SetPrivateKeyData(&keydata);

  XVECTOR<XBUFFER*> chain;
  CIPHERKEY* privatekey = NULL;

  EXPECT_TRUE(provider.Credentials_Load(chain, privatekey));

  ASSERT_EQ(chain.GetSize(), (XDWORD)1);
  ASSERT_NE(privatekey, (CIPHERKEY*)NULL);
  EXPECT_EQ(privatekey->GetType(), CIPHERKEYTYPE_RSA_PRIVATE);

  CIPHERCREDENTIALSLOADER::PrivateKey_Delete(privatekey);
  CIPHERCREDENTIALSLOADER::Certificates_Delete(chain);
}


}
#endif
