/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XLicense.cpp
*
* @class      XUTILS_UNITTESTS_XLICENSE
* @brief      XUtils unit tests for XLicense class
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

#include "XUtils_UnitTests_XLicense.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

// NOTE on the confirmed XLicense.h macro-arity bug (analysis report, independently reconfirmed
// while writing this batch): CHECKLICENSEFULLLOCAL/CHECKLICENSEFULLLOCALEXPIRE are declared with
// 4/5 parameters under "#ifdef XLICENSE_ACTIVE" (XLicense.h lines 69/81) but with only 3 parameters
// under the "#else" branch (lines 112/113) -- this project does not define XLICENSE_ACTIVE, so the
// 3-parameter macros are the ones in scope here; calling either macro with the 4/5-argument form
// that its own #ifdef sibling uses would not compile. Per the task's instructions, neither macro is
// invoked anywhere in this file -- every test below drives XLICENSE's real methods directly.

#include "XLicense.h"
#include "XFileINI.h"
#include "XPath.h"
#include "XBuffer.h"
#include "XString.h"
#include "XUUID.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XLICENSE
{

TEST(UNITTEST_XLICENSE_CLASSNAME, GetReturnsEmptyBufferInitially)
{
  XLICENSE xlicense;
  XSTRING  licensestring;

  ASSERT_NE((void*)xlicense.Get(), (void*)NULL);
  EXPECT_EQ(xlicense.Get()->GetSize(), (XDWORD)0);

  EXPECT_FALSE(xlicense.Get(licensestring));
}


TEST(UNITTEST_XLICENSE_CLASSNAME, GenerateMachineIDIsDeterministicAcrossCalls)
{
  XLICENSE   xlicense;
  XLICENSEID idA;
  XLICENSEID idB;

  EXPECT_TRUE(xlicense.GenerateMachineID(idA));
  EXPECT_TRUE(xlicense.GenerateMachineID(idB));

  EXPECT_TRUE(idA.GetID()->Compare((*idB.GetID())));
}


TEST(UNITTEST_XLICENSE_CLASSNAME, GetBufferKeyFromMachineIDProducesSixteenByteDeterministicKey)
{
  XLICENSE xlicense;
  XSTRING  appID;
  XBUFFER  keyA;
  XBUFFER  keyB;

  appID = __L("com.endorasoft.unittest");

  EXPECT_TRUE(xlicense.GetBufferKeyFromMachineID(appID, keyA));
  EXPECT_TRUE(xlicense.GetBufferKeyFromMachineID(appID, keyB));

  EXPECT_EQ(keyA.GetSize(), (XDWORD)16);

  for(XDWORD c = 0; c < keyA.GetSize(); c++)
    {
      EXPECT_EQ(keyA.GetByte(c), keyB.GetByte(c));
    }
}


TEST(UNITTEST_XLICENSE_CLASSNAME, GetBufferKeyFromMachineIDDiffersByApplicationID)
{
  XLICENSE xlicense;
  XSTRING  appIDone;
  XSTRING  appIDtwo;
  XBUFFER  keyone;
  XBUFFER  keytwo;

  appIDone = __L("app.one");
  appIDtwo = __L("app.two");

  EXPECT_TRUE(xlicense.GetBufferKeyFromMachineID(appIDone, keyone));
  EXPECT_TRUE(xlicense.GetBufferKeyFromMachineID(appIDtwo, keytwo));

  bool identical = true;

  for(XDWORD c = 0; c < keyone.GetSize(); c++)
    {
      if(keyone.GetByte(c) != keytwo.GetByte(c)) identical = false;
    }

  EXPECT_FALSE(identical);
}


TEST(UNITTEST_XLICENSE_CLASSNAME, CipherExpirationDateRoundTrip)
{
  XLICENSE xlicense;
  XSTRING  appID;
  XSTRING  date;

  appID = __L("com.endorasoft.unittest");
  date  = __L("2030/01/01 00:00:00");

  EXPECT_TRUE(xlicense.CipherExpirationDate(true, appID, date));

  // Ciphered form must no longer be the plain-text date.
  EXPECT_STRNE(date.Get(), __L("2030/01/01 00:00:00"));

  EXPECT_TRUE(xlicense.CipherExpirationDate(false, appID, date));

  EXPECT_STREQ(date.Get(), __L("2030/01/01 00:00:00"));
}


TEST(UNITTEST_XLICENSE_CLASSNAME, GenerateProducesNonEmptyCipheredLicenseBuffer)
{
  XLICENSE   xlicense;
  XLICENSEID xlicenseID;
  XSTRING    appID;
  XBUFFER    license;

  appID = __L("com.endorasoft.unittest");

  EXPECT_TRUE(xlicense.GenerateMachineID(xlicenseID));
  EXPECT_TRUE(xlicense.Generate(xlicenseID, &appID, &license));

  EXPECT_GT(license.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XLICENSE_CLASSNAME, GenerateIsDeterministicForSameLicenseIDAndApplicationID)
{
  XLICENSE   xlicense;
  XLICENSEID xlicenseID;
  XSTRING    appID;
  XBUFFER    licenseA;
  XBUFFER    licenseB;

  appID = __L("com.endorasoft.unittest");

  EXPECT_TRUE(xlicense.GenerateMachineID(xlicenseID));

  EXPECT_TRUE(xlicense.Generate(xlicenseID, &appID, &licenseA));
  EXPECT_TRUE(xlicense.Generate(xlicenseID, &appID, &licenseB));

  ASSERT_EQ(licenseA.GetSize(), licenseB.GetSize());

  for(XDWORD c = 0; c < licenseA.GetSize(); c++)
    {
      EXPECT_EQ(licenseA.GetByte(c), licenseB.GetByte(c));
    }
}


TEST(UNITTEST_XLICENSE_CLASSNAME, GenerateWithDefaultArgumentsUsesInternalMembers)
{
  // No explicit applicationID/license pointers: Generate() falls back to its own internal
  // 'applicationID' (empty by default) and 'license' members.
  XLICENSE   xlicense;
  XLICENSEID xlicenseID;

  EXPECT_TRUE(xlicense.GenerateMachineID(xlicenseID));
  EXPECT_TRUE(xlicense.Generate(xlicenseID));

  EXPECT_GT(xlicense.Get()->GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XLICENSE_CLASSNAME, ApplicationGetIDAndGetExpirationDateTimeReturnValidPointers)
{
  XLICENSE xlicense;

  ASSERT_NE((void*)xlicense.Application_GetID(), (void*)NULL);
  ASSERT_NE((void*)xlicense.GetExpirationDateTime(), (void*)NULL);
}


TEST(UNITTEST_XLICENSE_CLASSNAME, SetEventDoesNotCrashWithNoSubscribers)
{
  XLICENSE xlicense;

  EXPECT_TRUE(xlicense.SetEvent(XLICENSEXEVENT_TYPE_INVALID));
  EXPECT_TRUE(xlicense.SetEvent(XLICENSEXEVENT_TYPE_EXPIRED));
}


TEST(UNITTEST_XLICENSE_CLASSNAME, GenerateThenLoadFromFileFullRoundTrip)
{
  // Builds the on-disk .ini exactly the way XLICENSE::CheckMasterCreation() does (same XFILEINI
  // section/keys), then reads it back through LoadFromFile() -- exercising GenerateMachineID's
  // determinism, Generate()'s AES cipher, and LoadFromBuffer()'s machine-ID verification gate
  // together, all without touching the buggy CHECKLICENSEFULLLOCAL macro.
  XPATH      xpath(__L("/tmp/xutils_unittests_xlicense_roundtrip.ini"));
  XLICENSE   xlicense;
  XLICENSEID xlicenseID;
  XSTRING    appID;
  XBUFFER    license;
  XSTRING    licenseIDstring;
  XSTRING    licensehexstring;

  appID = __L("com.endorasoft.unittest");

  EXPECT_TRUE(xlicense.GenerateMachineID(xlicenseID));
  EXPECT_TRUE(xlicense.Generate(xlicenseID, &appID, &license));

  xlicenseID.GetID()->GetToString(licenseIDstring);
  licensehexstring.ConvertHexStringFromBuffer(license);

  {
    XFILEINI fileini;

    ASSERT_TRUE(fileini.Create(xpath));

    fileini.CreateSection(__L("LICENSE"));
    fileini.WriteValue(__L("LICENSE"), __L("licenseID"), licenseIDstring);
    fileini.WriteValue(__L("LICENSE"), __L("license"),   licensehexstring);

    fileini.Close();
  }

  XLICENSE xlicensereader;
  XBUFFER  readlicense;

  EXPECT_TRUE(xlicensereader.LoadFromFile(xpath, appID, &readlicense));

  ASSERT_EQ(readlicense.GetSize(), license.GetSize());

  for(XDWORD c = 0; c < license.GetSize(); c++)
    {
      EXPECT_EQ(readlicense.GetByte(c), license.GetByte(c));
    }

  remove("/tmp/xutils_unittests_xlicense_roundtrip.ini");
}


TEST(UNITTEST_XLICENSE_CLASSNAME, LoadFromFileWithMismatchedMachineIDFails)
{
  // LoadFromBuffer() recomputes this machine's real ID and rejects the file if the stored
  // 'licenseID' does not match -- a fabricated, clearly-wrong UUID string must be rejected.
  XPATH   xpath(__L("/tmp/xutils_unittests_xlicense_mismatch.ini"));
  XSTRING appID;
  XSTRING wronglicenseIDstring;
  XSTRING licensehexstring;

  appID                = __L("com.endorasoft.unittest");
  wronglicenseIDstring = __L("00000000-0000-0000-0000-000000000000");
  licensehexstring     = __L("AABBCCDD");

  {
    XFILEINI fileini;

    ASSERT_TRUE(fileini.Create(xpath));

    fileini.CreateSection(__L("LICENSE"));
    fileini.WriteValue(__L("LICENSE"), __L("licenseID"), wronglicenseIDstring);
    fileini.WriteValue(__L("LICENSE"), __L("license"),   licensehexstring);

    fileini.Close();
  }

  XLICENSE xlicensereader;
  XBUFFER  readlicense;

  EXPECT_FALSE(xlicensereader.LoadFromFile(xpath, appID, &readlicense));

  remove("/tmp/xutils_unittests_xlicense_mismatch.ini");
}


}
#endif
