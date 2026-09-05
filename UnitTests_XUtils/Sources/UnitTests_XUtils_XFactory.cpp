/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XFactory.cpp
*
* @class      UNITTESTS_XUTILS_XFACTORY
* @brief      XUtils unit tests for XFactory class
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

#include "UnitTests_XUtils_XFactory.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XTimer.h"
#include "XDateTime.h"
#include "XRand.h"
#include "FormatFiles/XFile.h"
#include "XDir.h"
#include "XThread.h"

// The concrete XFACTORY subclass is platform-specific (exactly as MainProcLINUX.cpp /
// MainProcWINDOWS.cpp themselves install a different one per platform at real app bootstrap:
// XLINUXFACTORY on Linux, XWINDOWSFACTORY on Windows) -- isolate that choice here the same way,
// instead of hardcoding one platform's concrete class, so this file builds and links everywhere.
#if defined(LINUX)
#include "XLINUXFactory.h"
#define UNITTESTS_XFACTORY_CONCRETECLASS XLINUXFACTORY
#elif defined(WINDOWS)
#include "XWINDOWSFactory.h"
#define UNITTESTS_XFACTORY_CONCRETECLASS XWINDOWSFACTORY
#endif


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFACTORY
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void EnsureXFactoryInstance()
* @brief      Ensures that the XFactory singleton instance exists, installing a real, fully
*             functional XLINUXFACTORY if none is installed - never a base-class stub, since every
*             other test in this shared binary (this file's own Create/Delete tests included, and
*             every earlier batch's XSleep/XDateTime/XTimer/XUUID tests) needs GEN_XFACTORY to
*             really work, not just exist.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
static void EnsureXFactoryInstance()
{
  if(!XFACTORY::GetIsInstanced())
    {
      XFACTORY::SetInstance(GEN_NEW UNITTESTS_XFACTORY_CONCRETECLASS());
    }
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, SetInstanceNull)
{
  EXPECT_FALSE(XFACTORY::SetInstance(NULL));
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, InstanceLifecycle)
{
  // Source concern (a real, concrete divergence from XSLEEP's otherwise-identical Set/Get/Del/
  // IsInstanced quartet - worth checking per-class rather than assuming, exactly as flagged for
  // this batch): XFACTORY::SetInstance() (XFactory.cpp lines 142-151) calls DelInstance() BEFORE
  // installing the new pointer - unlike XSLEEP::SetInstance(), which just overwrites the pointer
  // without deleting the previous instance. That means swapping the real, load-bearing
  // XLINUXFACTORY singleton out for a test double genuinely destroys the real object as a side
  // effect of the very first SetInstance() call below - there is no live "original" pointer left to
  // hand back to SetInstance() afterward (copying XSLEEP's "SetInstance(originalinstance)" restore
  // pattern verbatim here would install a dangling pointer). The safe way to leave every other test
  // in this shared binary with working GEN_XFACTORY.CreateXxx() functionality afterward is to
  // finish by installing a FRESH, real XLINUXFACTORY - exactly what this project's own
  // MainProcLINUX.cpp does at bootstrap.
  XFACTORY* testinstance = GEN_NEW XFACTORY();
  EXPECT_NE(testinstance, nullptr);

  EXPECT_TRUE(XFACTORY::SetInstance(testinstance));
  EXPECT_TRUE(XFACTORY::GetIsInstanced());
  EXPECT_EQ(&XFACTORY::GetInstance(), testinstance);

  EXPECT_TRUE(XFACTORY::SetInstance(GEN_NEW UNITTESTS_XFACTORY_CONCRETECLASS()));
  EXPECT_TRUE(XFACTORY::GetIsInstanced());
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, DelInstanceTwice)
{
  // As above: whichever instance is installed when this test starts is unavoidably destroyed by
  // DelInstance(), so this always finishes by installing a fresh, real XLINUXFACTORY.
  EXPECT_TRUE(XFACTORY::GetIsInstanced());

  EXPECT_TRUE(XFACTORY::DelInstance());
  EXPECT_FALSE(XFACTORY::GetIsInstanced());
  EXPECT_FALSE(XFACTORY::DelInstance());

  EXPECT_TRUE(XFACTORY::SetInstance(GEN_NEW UNITTESTS_XFACTORY_CONCRETECLASS()));
  EXPECT_TRUE(XFACTORY::GetIsInstanced());
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, BaseClassCreateMethodsAreInertStubsReturningNullOrFalse)
{
  // The base XFACTORY (not swapped into the global slot: a throwaway local object) is meant to be
  // overridden per platform; every one of its own Create/Delete methods is documented here as an
  // inert stub, confirmed directly against the base class rather than through the real singleton.
  XFACTORY basefactory;

  EXPECT_EQ(basefactory.CreateTimer(), nullptr);
  EXPECT_FALSE(basefactory.DeleteTimer(NULL));

  EXPECT_EQ(basefactory.CreateDateTime(), nullptr);
  EXPECT_FALSE(basefactory.DeleteDateTime(NULL));

  EXPECT_EQ(basefactory.CreateRand(), nullptr);
  EXPECT_FALSE(basefactory.DeleteRand(NULL));

  EXPECT_EQ(basefactory.Create_File(), nullptr);
  EXPECT_FALSE(basefactory.Delete_File(NULL));

  EXPECT_EQ(basefactory.Create_Dir(), nullptr);
  EXPECT_FALSE(basefactory.Delete_Dir(NULL));

  EXPECT_EQ(basefactory.Create_Mutex(), nullptr);
  EXPECT_FALSE(basefactory.Delete_Mutex(NULL));

  EXPECT_EQ(basefactory.CreateThread(XTHREADGROUPID_UNGROUP, __L("test"), NULL, NULL), nullptr);
  EXPECT_FALSE(basefactory.DeleteThread(XTHREADGROUPID_UNGROUP, NULL));
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, CreateTimerAndDeleteTimerViaRealInstance)
{
  EnsureXFactoryInstance();

  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_NE(xtimer, nullptr);

  EXPECT_TRUE(GEN_XFACTORY.DeleteTimer(xtimer));
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, CreateDateTimeAndDeleteDateTimeViaRealInstance)
{
  EnsureXFactoryInstance();

  XDATETIME* xdatetime = GEN_XFACTORY.CreateDateTime();
  EXPECT_NE(xdatetime, nullptr);

  EXPECT_TRUE(GEN_XFACTORY.DeleteDateTime(xdatetime));
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, CreateRandAndDeleteRandViaRealInstance)
{
  EnsureXFactoryInstance();

  XRAND* xrand = GEN_XFACTORY.CreateRand();
  EXPECT_NE(xrand, nullptr);

  EXPECT_TRUE(GEN_XFACTORY.DeleteRand(xrand));
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, CreateDirAndDeleteDirViaRealInstance)
{
  EnsureXFactoryInstance();

  XDIR* xdir = GEN_XFACTORY.Create_Dir();
  EXPECT_NE(xdir, nullptr);

  EXPECT_TRUE(GEN_XFACTORY.Delete_Dir(xdir));
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, CreateMutexAndDeleteMutexViaRealInstance)
{
  EnsureXFactoryInstance();

  XMUTEX* xmutex = GEN_XFACTORY.Create_Mutex();
  EXPECT_NE(xmutex, nullptr);

  EXPECT_TRUE(GEN_XFACTORY.Delete_Mutex(xmutex));
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, CreateThreadAndDeleteThreadViaRealInstance)
{
  EnsureXFactoryInstance();

  XTHREAD* xthread = GEN_XFACTORY.CreateThread(XTHREADGROUPID_UNGROUP, __L("UnitTests_XUtils_XFactory_Thread"));
  EXPECT_NE(xthread, nullptr);

  EXPECT_TRUE(GEN_XFACTORY.DeleteThread(XTHREADGROUPID_UNGROUP, xthread));
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, CreateFileAndDeleteFileViaRealInstance)
{
  // Create_File/Delete_File is the one Create/Delete pair not already exercised incidentally by
  // earlier batches (Timer/DateTime/Rand/Dir/Mutex/Thread are all used for real elsewhere in this
  // suite). We never call Open()/Create() on the returned object, so nothing touches disk and
  // there is nothing to clean up afterwards.
  EnsureXFactoryInstance();

  XFILE* xfile = GEN_XFACTORY.Create_File();
  EXPECT_NE(xfile, nullptr);

  EXPECT_FALSE(xfile->IsOpen());

  EXPECT_TRUE(GEN_XFACTORY.Delete_File(xfile));
}


TEST(UNITTESTS_XFACTORY_CLASSNAME, DeleteWithNullPointerReturnsFalseInsteadOfCrashing)
{
  // A genuine double-Delete of the *same*, already-freed pointer is undefined behavior (use after
  // free) and unsafe to exercise here without risking corrupting this shared test binary's heap.
  // The one double-delete scenario the real DELETEFUNC/virtual-stub implementation actually
  // documents and guards against is a NULL pointer, which is what we verify instead: a caller that
  // has already deleted an object (and, following normal C++ hygiene, nulled out its own pointer)
  // gets a clean "false" back from a second Delete call rather than a crash.
  EnsureXFactoryInstance();

  EXPECT_FALSE(GEN_XFACTORY.DeleteTimer(NULL));
  EXPECT_FALSE(GEN_XFACTORY.Delete_File(NULL));
  EXPECT_FALSE(GEN_XFACTORY.DeleteRand(NULL));
}


}
#endif

