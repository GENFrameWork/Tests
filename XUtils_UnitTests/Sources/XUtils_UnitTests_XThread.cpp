/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XThread.cpp
*
* @class      XUTILS_UNITTESTS_XTHREAD
* @brief      XUtils unit tests for XThread and XMutex classes
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

#include "XUtils_UnitTests_XThread.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XThread.h"
#include "XTimer.h"
#include "XSleep.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XTHREAD
{

// Shared state handed to XTHREADFUNCTION workers (plain C callback: void(*)(void*)).
struct XTHREADTESTDATA
{
  volatile XDWORD counter;
  volatile bool   sawinfunction;
};


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void EnsureXSleepInstance()
* @brief      Ensures that the XSleep singleton instance exists (GEN's own portable sleep API is used
*             instead of any STL/POSIX sleep function, per project policy).
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
static void EnsureXSleepInstance()
{
  if(!XSLEEP::GetIsInstanced())
    {
      XSLEEP* instance = GEN_NEW XSLEEP();
      XSLEEP::SetInstance(instance);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void IncrementWorker(void* data)
* @brief      Worker used by real-thread tests: increments a shared counter and sleeps briefly so the
*             calling thread's IsInFunction() window is wide enough to be observed deterministically.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void IncrementWorker(void* data)
{
  XTHREADTESTDATA* testdata = (XTHREADTESTDATA*)data;
  if(!testdata) return;

  testdata->counter++;

  EnsureXSleepInstance();
  GEN_XSLEEP.MicroSeconds(10000); // 10 ms in-function window
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static bool WaitForCounterAtLeast(XTHREADTESTDATA* testdata, XDWORD target, int timeoutseconds)
* @brief      Bounded poll (no fixed sleep assumption) used instead of a fixed delay: waits until the
*             worker's counter reaches target, or the timeout elapses.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static bool WaitForCounterAtLeast(XTHREADTESTDATA* testdata, XDWORD target, int timeoutseconds)
{
  EnsureXSleepInstance();

  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  if(!xtimer) return false;

  bool reached = false;

  while(xtimer->GetMeasureSeconds() < (XQWORD)timeoutseconds)
    {
      if(testdata->counter >= target)
        {
          reached = true;
          break;
        }

      GEN_XSLEEP.MicroSeconds(1000);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);

  return reached;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static bool WaitForInFunction(XTHREAD* xthread, int timeoutseconds)
* @brief      Bounded poll that waits until the thread reports IsInFunction()==true, or times out.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static bool WaitForInFunction(XTHREAD* xthread, int timeoutseconds)
{
  EnsureXSleepInstance();

  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  if(!xtimer) return false;

  bool seen = false;

  while(xtimer->GetMeasureSeconds() < (XQWORD)timeoutseconds)
    {
      if(xthread->IsInFunction())
        {
          seen = true;
          break;
        }

      GEN_XSLEEP.MicroSeconds(200);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);

  return seen;
}


TEST(UNITTEST_XTHREAD_CLASSNAME, ConstructorStoresGroupIDAndID)
{
  XTHREAD xthread(XTHREADGROUPID_UNGROUP, __L("MyThread"), NULL, NULL);

  EXPECT_EQ(xthread.GetGroupID(), XTHREADGROUPID_UNGROUP);
  EXPECT_STREQ(xthread.GetID()->Get(), __L("MyThread"));
  EXPECT_EQ(xthread.GetFunction(), (XTHREADFUNCTION)NULL);
  EXPECT_EQ(xthread.GetParam(), (void*)NULL);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, ConstructorStoresFunctionAndParam)
{
  XTHREADTESTDATA testdata; testdata.counter = 0; testdata.sawinfunction = false;

  XTHREAD xthread(XTHREADGROUPID_UNGROUP, __L("Worker"), IncrementWorker, (void*)&testdata);

  EXPECT_EQ(xthread.GetFunction(), &IncrementWorker);
  EXPECT_EQ(xthread.GetParam(), (void*)&testdata);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, DefaultStateBeforeStarting)
{
  XTHREAD xthread(XTHREADGROUPID_UNGROUP, __L("Idle"), NULL, NULL);

  EXPECT_FALSE(xthread.IsRunning());
  EXPECT_FALSE(xthread.IsInFunction());
  EXPECT_EQ(xthread.GetStatusFunc(), XTHREADSTATUS_NONE);
  EXPECT_EQ(xthread.GetWaitYield(), (XDWORD)XTHREAD_DEFAULTWAITYIELD);
  EXPECT_EQ(xthread.GetPriority(), XTHREADPRIORITY_UNKNOWN);
  EXPECT_EQ(xthread.GetStackSize(), (XDWORD)0);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, GetSetGroupID)
{
  XTHREAD xthread(XTHREADGROUPID_UNGROUP, __L("T"), NULL, NULL);

  xthread.SetGroupID(XTHREADGROUPID_SCRIPT);
  EXPECT_EQ(xthread.GetGroupID(), XTHREADGROUPID_SCRIPT);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, GetSetPriority)
{
  XTHREAD xthread(XTHREADGROUPID_UNGROUP, __L("T"), NULL, NULL);

  xthread.SetPriority(XTHREADPRIORITY_HIGH);
  EXPECT_EQ(xthread.GetPriority(), XTHREADPRIORITY_HIGH);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, GetSetStackSize)
{
  XTHREAD xthread(XTHREADGROUPID_UNGROUP, __L("T"), NULL, NULL);

  xthread.SetStackSize(65536);
  EXPECT_EQ(xthread.GetStackSize(), (XDWORD)65536);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, GetSetWaitYield)
{
  XTHREAD xthread(XTHREADGROUPID_UNGROUP, __L("T"), NULL, NULL);

  xthread.SetWaitYield(25);
  EXPECT_EQ(xthread.GetWaitYield(), (XDWORD)25);

  xthread.SetWaitYield();
  EXPECT_EQ(xthread.GetWaitYield(), (XDWORD)XTHREAD_DEFAULTWAITYIELD);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, RunTogglesStatusAndRejectsRedundantCalls)
{
  XTHREAD xthread(XTHREADGROUPID_UNGROUP, __L("T"), NULL, NULL);

  // Not running yet: Run(false) (stop) is rejected.
  EXPECT_FALSE(xthread.Run(false));

  EXPECT_TRUE(xthread.Run(true));
  EXPECT_TRUE(xthread.IsRunning());
  EXPECT_EQ(xthread.GetStatusFunc(), XTHREADSTATUS_RUN);

  // Already running: activating again is rejected.
  EXPECT_FALSE(xthread.Run(true));

  EXPECT_TRUE(xthread.Run(false));
  EXPECT_FALSE(xthread.IsRunning());
  EXPECT_EQ(xthread.GetStatusFunc(), XTHREADSTATUS_STOP);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, ExitSetsExitStatus)
{
  XTHREAD xthread(XTHREADGROUPID_UNGROUP, __L("T"), NULL, NULL);

  EXPECT_TRUE(xthread.Exit());
  EXPECT_EQ(xthread.GetStatusFunc(), XTHREADSTATUS_EXIT);
  EXPECT_FALSE(xthread.IsRunning());
}


TEST(UNITTEST_XTHREAD_CLASSNAME, WaitToEndReturnsTrueImmediatelyWhenNeverStarted)
{
  // gotofunction is only ever set true from inside the real OS thread callback (XLINUXTHREAD::Callback),
  // so a thread object that was never Ini()'d has gotofunction==false and WaitToEnd() takes the
  // immediate "not started" path instead of polling/blocking.
  XTHREAD xthread(XTHREADGROUPID_UNGROUP, __L("T"), NULL, NULL);

  EXPECT_TRUE(xthread.WaitToEnd());
  EXPECT_EQ(xthread.GetStatusFunc(), XTHREADSTATUS_END);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, BaseIniWaitEndAreUnimplementedStubs)
{
  // The portable XTHREAD base class (as opposed to the real XLINUXTHREAD subclass created by the
  // factory) documents Ini/Wait/End as platform-specific and its own .cpp implementation always
  // returns false -- real OS threading only happens through a platform subclass.
  XTHREAD xthread(XTHREADGROUPID_UNGROUP, __L("T"), NULL, NULL);

  EXPECT_FALSE(xthread.Ini(false));
  EXPECT_FALSE(xthread.Wait(0));
  EXPECT_FALSE(xthread.End());
}


TEST(UNITTEST_XTHREAD_CLASSNAME, FactoryCreatesRealThreadStartsRunsAndJoins)
{
  XTHREADTESTDATA testdata; testdata.counter = 0; testdata.sawinfunction = false;

  XTHREAD* xthread = GEN_XFACTORY.CreateThread(XTHREADGROUPID_UNGROUP, __L("RealWorker"), IncrementWorker, (void*)&testdata);
  ASSERT_NE(xthread, (XTHREAD*)NULL);

  xthread->SetWaitYield(1); // fast cadence so the bounded polls below resolve quickly

  EXPECT_TRUE(xthread->Ini(true));
  EXPECT_TRUE(xthread->IsRunning());

  // Bounded poll instead of a fixed sleep: the worker increments repeatedly while RUN is active.
  EXPECT_TRUE(WaitForCounterAtLeast(&testdata, 3, 3));
  EXPECT_GE(testdata.counter, (XDWORD)3);

  EXPECT_TRUE(xthread->End());
  EXPECT_FALSE(xthread->IsRunning());
  EXPECT_EQ(xthread->GetStatusFunc(), XTHREADSTATUS_END);

  GEN_XFACTORY.DeleteThread(XTHREADGROUPID_UNGROUP, xthread);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, IsInFunctionReflectsExecutionWindow)
{
  XTHREADTESTDATA testdata; testdata.counter = 0; testdata.sawinfunction = false;

  XTHREAD* xthread = GEN_XFACTORY.CreateThread(XTHREADGROUPID_UNGROUP, __L("InFuncWorker"), IncrementWorker, (void*)&testdata);
  ASSERT_NE(xthread, (XTHREAD*)NULL);

  xthread->SetWaitYield(1);

  EXPECT_TRUE(xthread->Ini(true));

  // The worker spends most of its cycle asleep inside the callback (10ms sleep vs 1ms yield), so a
  // bounded poll has a wide window to catch IsInFunction()==true deterministically.
  EXPECT_TRUE(WaitForInFunction(xthread, 3));

  EXPECT_TRUE(xthread->End());

  GEN_XFACTORY.DeleteThread(XTHREADGROUPID_UNGROUP, xthread);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, MutexLockUnlockRoundTrip)
{
  XMUTEX* xmutex = GEN_XFACTORY.Create_Mutex();
  ASSERT_NE(xmutex, (XMUTEX*)NULL);

  EXPECT_FALSE(xmutex->IsLock());

  EXPECT_TRUE(xmutex->Lock());
  EXPECT_TRUE(xmutex->IsLock());

  EXPECT_TRUE(xmutex->UnLock());
  EXPECT_FALSE(xmutex->IsLock());

  GEN_XFACTORY.Delete_Mutex(xmutex);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, MutexIsRecursiveOnLinux)
{
  // XLINUXMUTEX is initialized with PTHREAD_MUTEX_RECURSIVE: the same thread can Lock() it more
  // than once without deadlocking.
  XMUTEX* xmutex = GEN_XFACTORY.Create_Mutex();
  ASSERT_NE(xmutex, (XMUTEX*)NULL);

  EXPECT_TRUE(xmutex->Lock());
  EXPECT_TRUE(xmutex->Lock());
  EXPECT_TRUE(xmutex->IsLock());

  EXPECT_TRUE(xmutex->UnLock());

  GEN_XFACTORY.Delete_Mutex(xmutex);
}


TEST(UNITTEST_XTHREAD_CLASSNAME, MutexUsedFromWorkerThreadProtectsCounter)
{
  // End-to-end: a real background thread locks/increments/unlocks a shared counter guarded by a
  // real XMUTEX; verifies XTHREAD + XMUTEX cooperate as intended rather than testing each in isolation.
  struct GUARDEDCOUNTER
  {
    XMUTEX* xmutex;
    volatile XDWORD counter;
  };

  struct LOCALWORKER
  {
    static void Run(void* data)
    {
      GUARDEDCOUNTER* guarded = (GUARDEDCOUNTER*)data;
      if(!guarded) return;

      guarded->xmutex->Lock();
      guarded->counter++;
      guarded->xmutex->UnLock();

      EnsureXSleepInstance();
      GEN_XSLEEP.MicroSeconds(1000);
    }
  };

  EnsureXSleepInstance();

  GUARDEDCOUNTER guarded;
  guarded.xmutex  = GEN_XFACTORY.Create_Mutex();
  guarded.counter = 0;
  ASSERT_NE(guarded.xmutex, (XMUTEX*)NULL);

  XTHREAD* xthread = GEN_XFACTORY.CreateThread(XTHREADGROUPID_UNGROUP, __L("MutexWorker"), LOCALWORKER::Run, (void*)&guarded);
  ASSERT_NE(xthread, (XTHREAD*)NULL);

  xthread->SetWaitYield(1);
  EXPECT_TRUE(xthread->Ini(true));

  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  bool reached = false;
  while(xtimer->GetMeasureSeconds() < 3)
    {
      guarded.xmutex->Lock();
      bool enough = (guarded.counter >= 3);
      guarded.xmutex->UnLock();

      if(enough) { reached = true; break; }

      GEN_XSLEEP.MicroSeconds(1000);
    }
  GEN_XFACTORY.DeleteTimer(xtimer);

  EXPECT_TRUE(reached);

  EXPECT_TRUE(xthread->End());

  GEN_XFACTORY.DeleteThread(XTHREADGROUPID_UNGROUP, xthread);
  GEN_XFACTORY.Delete_Mutex(guarded.xmutex);
}


}
#endif
