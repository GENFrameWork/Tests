/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XSystem.cpp
*
* @class      XUTILS_UNITTESTS_XSYSTEM
* @brief      XUtils unit tests for XSystem class
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

#include "XUtils_UnitTests_XSystem.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XSystem.h"
#include "XPath.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XSYSTEM
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void EnsureXSystemInstance()
* @brief      Ensures that the XSystem singleton instance exists.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
static void EnsureXSystemInstance()
{
  if(!XSYSTEM::GetIsInstanced())
    {
      XSYSTEM* instance = GEN_NEW XSYSTEM();
      XSYSTEM::SetInstance(instance);
    }
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, GetOperativeSystemID)
{
  EnsureXSystemInstance();

  // NOTE: the base XSYSTEM::GetOperativeSystemID() documents Empty()+true, but this
  // application's Linux startup (MainProcLINUX.cpp) installs an XLINUXSYSTEM singleton before
  // any test runs, and XLINUXSYSTEM overrides this to fill the string with uname() details
  // ("Linux <release> <version> <machine> ") - so the live singleton's actual answer depends
  // on which concrete subclass is installed, not just on the base class's documented contract.
  XSTRING SOid;

  EXPECT_TRUE(XSYSTEM::GetInstance().GetOperativeSystemID(SOid));
  EXPECT_FALSE(SOid.IsEmpty());
  EXPECT_NE(SOid.Find(__L("Linux"), false), XSTRING_NOTFOUND);
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, GetPlatformBaseContractFillsUnknownNameString)
{
  // The base implementation is not overridden for GetPlatform() by XLINUXSYSTEM in this
  // build's platform layer used here indirectly - exercised through a throwaway local instance
  // so the test is independent of whichever concrete subclass is currently installed globally.
  XSYSTEM localsystem;
  XSTRING namestring;

  XSYSTEM_PLATFORM platform = localsystem.GetPlatform(&namestring);

  EXPECT_EQ(platform, XSYSTEM_PLATFORM_UNKNOWN);
  EXPECT_STREQ(namestring.Get(), __L("Unknown"));

  // Passing NULL must not crash.
  platform = localsystem.GetPlatform(NULL);
  EXPECT_EQ(platform, XSYSTEM_PLATFORM_UNKNOWN);
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, GetTypeHardwareBaseContractIsUnknown)
{
  XSYSTEM localsystem;

  EXPECT_EQ(localsystem.GetTypeHardware(), XSYSTEM_HARDWARETYPE_UNKNOWN);

  int revision = 0;
  EXPECT_EQ(localsystem.GetTypeHardware(&revision), XSYSTEM_HARDWARETYPE_UNKNOWN);
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, HardwareUseLittleEndianIsStableBoolean)
{
  XSYSTEM localsystem;

  // Base GetTypeHardware() always answers UNKNOWN, which HardwareUseLittleEndian() documents
  // as true - assert the documented mapping directly against a throwaway local instance.
  EXPECT_TRUE(localsystem.HardwareUseLittleEndian());
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, GetMemoryInfoBaseContractReturnsZeroedFailure)
{
  XSYSTEM localsystem;
  XDWORD  total = 123;
  XDWORD  free  = 456;

  EXPECT_FALSE(localsystem.GetMemoryInfo(total, free));
  EXPECT_EQ(total, (XDWORD)0);
  EXPECT_EQ(free,  (XDWORD)0);
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, GetFreeMemoryPercentBaseContractIsZero)
{
  XSYSTEM localsystem;

  // GetMemoryInfo() base contract always fails, so GetFreeMemoryPercent() falls through
  // its "if(!GetMemoryInfo(...)) return false" branch - note the real signature returns int,
  // so that boolean false becomes integer 0, not a documented percentage.
  EXPECT_EQ(localsystem.GetFreeMemoryPercent(), 0);
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, CPUUsageQueriesBaseContractReturnError)
{
  XSYSTEM localsystem;

  EXPECT_EQ(localsystem.GetCPUUsageTotal(), XSYSTEM_CPUUSAGE_ERROR);
  EXPECT_EQ(localsystem.GetCPUUsageForProcessName((XCHAR*)__L("anyprocess")), XSYSTEM_CPUUSAGE_ERROR);
  EXPECT_EQ(localsystem.GetCPUUsageForProcessID(1), XSYSTEM_CPUUSAGE_ERROR);
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, GetPathExecApplicationBaseContractEmptiesPathAndFails)
{
  XSYSTEM localsystem;
  XPATH   apppath;

  apppath = __L("some/previous/value");

  EXPECT_FALSE(localsystem.GetPathExecApplication((XCHAR*)__L("myapp"), apppath));
  EXPECT_TRUE(apppath.IsEmpty());

  // XSTRING* overload forwards to the XCHAR* overload and must reject a NULL pointer.
  EXPECT_FALSE(localsystem.GetPathExecApplication((XSTRING*)NULL, apppath));
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, EnviromentVariableBaseContractIsInertButSafe)
{
  XSYSTEM localsystem;

  // The base contract never touches the real environment: Get returns an empty string,
  // Set/Del always report failure. We only assert the documented, side-effect-free contract.
  EXPECT_STREQ(localsystem.GetEnviromentVariable((XCHAR*)__L("PATH")), __L(""));
  EXPECT_FALSE(localsystem.SetEnviromentVariable((XCHAR*)__L("XUNITTEST_VAR"), (XCHAR*)__L("1")));
  EXPECT_FALSE(localsystem.DelEnviromentVariable((XCHAR*)__L("XUNITTEST_VAR")));

  XSTRING name;
  XSTRING value;

  name  = __L("XUNITTEST_VAR");
  value = __L("1");

  EXPECT_STREQ(localsystem.GetEnviromentVariable(name), __L(""));
  EXPECT_FALSE(localsystem.SetEnviromentVariable(name, value));
  EXPECT_FALSE(localsystem.DelEnviromentVariable(name));
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, GetUserAndDomainBaseContractFails)
{
  XSYSTEM localsystem;
  XSTRING user;
  XSTRING domain;

  EXPECT_FALSE(localsystem.GetUserAndDomain(user, domain));
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, ShutDownBaseContractFails)
{
  XSYSTEM localsystem;

  EXPECT_FALSE(localsystem.ShutDown(XSYSTEM_CHANGESTATUSTYPE_NONE));
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, SoundControlsBaseContract)
{
  XSYSTEM localsystem;

  EXPECT_EQ(localsystem.Sound_GetLevel(), 0);
  EXPECT_FALSE(localsystem.Sound_SetLevel(50));
  EXPECT_FALSE(localsystem.Sound_SetMutex(true));
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, GetBatteryAndWifiBaseContract)
{
  XSYSTEM localsystem;
  bool    isincharge   = true;
  XBYTE   levelpercent = 99;

  EXPECT_FALSE(localsystem.GetBatteryLevel(isincharge, levelpercent));
  EXPECT_EQ(localsystem.GetWifiRSSILevel(), -1);
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, SetInstanceNull)
{
  EXPECT_FALSE(XSYSTEM::SetInstance(NULL));
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, InstanceLifecycle)
{
  XSYSTEM* originalinstance = NULL;
  if(XSYSTEM::GetIsInstanced()) originalinstance = &XSYSTEM::GetInstance();

  XSYSTEM* testinstance = GEN_NEW XSYSTEM();
  EXPECT_NE(testinstance, nullptr);

  EXPECT_TRUE(XSYSTEM::SetInstance(testinstance));
  EXPECT_TRUE(XSYSTEM::GetIsInstanced());
  EXPECT_EQ(&XSYSTEM::GetInstance(), testinstance);

  if(originalinstance)
    {
      EXPECT_TRUE(XSYSTEM::SetInstance(originalinstance));
      GEN_DELETE testinstance;
    }
   else
    {
      EXPECT_TRUE(XSYSTEM::DelInstance());
      EnsureXSystemInstance();
    }
}


TEST(UNITTEST_XSYSTEM_CLASSNAME, DelInstanceTwice)
{
  XSYSTEM* originalinstance = NULL;
  if(XSYSTEM::GetIsInstanced()) originalinstance = &XSYSTEM::GetInstance();

  XSYSTEM* testinstance = GEN_NEW XSYSTEM();
  EXPECT_NE(testinstance, nullptr);

  EXPECT_TRUE(XSYSTEM::SetInstance(testinstance));

  EXPECT_TRUE(XSYSTEM::DelInstance());
  EXPECT_FALSE(XSYSTEM::DelInstance());

  if(originalinstance)
    {
      EXPECT_TRUE(XSYSTEM::SetInstance(originalinstance));
    }
   else
    {
      EnsureXSystemInstance();
    }
}


}
#endif
