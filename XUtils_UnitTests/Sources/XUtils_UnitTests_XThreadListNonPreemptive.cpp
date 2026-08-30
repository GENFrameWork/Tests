/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XThreadListNonPreemptive.cpp
*
* @class      XUTILS_UNITTESTS_XTHREADLISTNONPREEMPTIVE
* @brief      XUtils unit tests for XThreadListNonPreemptive class
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

#include "XUtils_UnitTests_XThreadListNonPreemptive.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XThreadListNonPreemptive.h"
#include "XThread.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XTHREADLISTNONPREEMPTIVE
{

// XTHREADLISTNONPREEMPTIVE::ExecuteFunctions() runs each registered XTHREAD's function
// synchronously, on the calling thread -- no real OS thread is ever started by these tests, which
// is exactly what makes the cooperative dispatch deterministic to test.
static void BumpCounter(void* data)
{
  XDWORD* counter = (XDWORD*)data;
  if(counter) (*counter)++;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void ResetList()
* @brief      Leaves the GEN singleton in a clean, empty state before a test (DeleteAll() also
*             deletes any XTHREAD objects still registered from a previous test).
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void ResetList()
{
  XTHREADLISTNONPREEMPTIVE::GetInstance().DeleteAll();
}


TEST(UNITTEST_XTHREADLISTNONPREEMPTIVE_CLASSNAME, GetInstanceReturnsSameReference)
{
  ResetList();

  XTHREADLISTNONPREEMPTIVE& instance1 = XTHREADLISTNONPREEMPTIVE::GetInstance();
  XTHREADLISTNONPREEMPTIVE& instance2 = XTHREADLISTNONPREEMPTIVE::GetInstance();

  EXPECT_EQ(&instance1, &instance2);
}


TEST(UNITTEST_XTHREADLISTNONPREEMPTIVE_CLASSNAME, DelInstanceThenGetInstanceRecreatesEmptyList)
{
  ResetList();

  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::DelInstance());

  // Lazily recreate: GetInstance() after DelInstance() builds a brand new, empty instance.
  XTHREADLISTNONPREEMPTIVE& fresh = XTHREADLISTNONPREEMPTIVE::GetInstance();
  EXPECT_FALSE(fresh.ExecuteFunctions()); // empty list

  ResetList();
}


TEST(UNITTEST_XTHREADLISTNONPREEMPTIVE_CLASSNAME, AddThreadRejectsNull)
{
  ResetList();

  EXPECT_FALSE(XTHREADLISTNONPREEMPTIVE::GetInstance().AddThread(NULL));

  ResetList();
}


TEST(UNITTEST_XTHREADLISTNONPREEMPTIVE_CLASSNAME, DeleteThreadRejectsNullAndUnknownPointer)
{
  ResetList();

  EXPECT_FALSE(XTHREADLISTNONPREEMPTIVE::GetInstance().DeleteThread(NULL));

  XTHREAD notregistered(XTHREADGROUPID_UNGROUP, __L("NotRegistered"), NULL, NULL);
  EXPECT_FALSE(XTHREADLISTNONPREEMPTIVE::GetInstance().DeleteThread(&notregistered));

  ResetList();
}


TEST(UNITTEST_XTHREADLISTNONPREEMPTIVE_CLASSNAME, AddThreadThenDeleteThreadRoundTrip)
{
  ResetList();

  XTHREAD* xthread = GEN_NEW XTHREAD(XTHREADGROUPID_UNGROUP, __L("Coop"), NULL, NULL);
  ASSERT_NE(xthread, (XTHREAD*)NULL);

  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().AddThread(xthread));

  // DeleteThread() only unregisters -- it does not delete the XTHREAD object, so the caller (this
  // test) remains the owner and must free it itself.
  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().DeleteThread(xthread));
  EXPECT_FALSE(XTHREADLISTNONPREEMPTIVE::GetInstance().DeleteThread(xthread)); // already removed

  GEN_DELETE xthread;

  ResetList();
}


TEST(UNITTEST_XTHREADLISTNONPREEMPTIVE_CLASSNAME, ExecuteFunctionsOnEmptyListReturnsFalse)
{
  ResetList();

  EXPECT_FALSE(XTHREADLISTNONPREEMPTIVE::GetInstance().ExecuteFunctions());
}


TEST(UNITTEST_XTHREADLISTNONPREEMPTIVE_CLASSNAME, ExecuteFunctionsInvokesRunningThreadFunctionSynchronously)
{
  ResetList();

  XDWORD counter = 0;

  // A plain XTHREAD (not created via the OS-thread factory) is enough: ExecuteFunctions() only
  // ever reads GetStatusFunc()/GetFunction()/GetParam(), it never spawns anything.
  XTHREAD* xthread = GEN_NEW XTHREAD(XTHREADGROUPID_UNGROUP, __L("Coop"), BumpCounter, (void*)&counter);
  ASSERT_NE(xthread, (XTHREAD*)NULL);

  EXPECT_TRUE(xthread->Run(true)); // status -> XTHREADSTATUS_RUN, the only status ExecuteFunctions() dispatches

  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().AddThread(xthread));

  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().ExecuteFunctions());
  EXPECT_EQ(counter, (XDWORD)1);

  // A second pass invokes it again: this is a repeated cooperative dispatch, not a one-shot call.
  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().ExecuteFunctions());
  EXPECT_EQ(counter, (XDWORD)2);

  ResetList(); // deletes xthread for us
}


TEST(UNITTEST_XTHREADLISTNONPREEMPTIVE_CLASSNAME, ExecuteFunctionsSkipsExitStatusThread)
{
  ResetList();

  XDWORD counter = 0;

  XTHREAD* xthread = GEN_NEW XTHREAD(XTHREADGROUPID_UNGROUP, __L("Coop"), BumpCounter, (void*)&counter);
  ASSERT_NE(xthread, (XTHREAD*)NULL);

  EXPECT_TRUE(xthread->Exit()); // status -> XTHREADSTATUS_EXIT

  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().AddThread(xthread));
  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().ExecuteFunctions()); // list not empty -> true

  EXPECT_EQ(counter, (XDWORD)0); // EXIT status is explicitly not dispatched

  ResetList();
}


TEST(UNITTEST_XTHREADLISTNONPREEMPTIVE_CLASSNAME, ExecuteFunctionsSkipsDefaultNoneStatusThread)
{
  ResetList();

  XDWORD counter = 0;

  // Freshly constructed thread: GetStatusFunc() is XTHREADSTATUS_NONE (falls into the switch's
  // default case), so ExecuteFunctions() never touches its function pointer.
  XTHREAD* xthread = GEN_NEW XTHREAD(XTHREADGROUPID_UNGROUP, __L("Coop"), BumpCounter, (void*)&counter);
  ASSERT_NE(xthread, (XTHREAD*)NULL);

  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().AddThread(xthread));
  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().ExecuteFunctions());

  EXPECT_EQ(counter, (XDWORD)0);

  ResetList();
}


TEST(UNITTEST_XTHREADLISTNONPREEMPTIVE_CLASSNAME, ExecuteFunctionsDispatchesEveryRegisteredThreadPerPass)
{
  ResetList();

  XDWORD counterA = 0, counterB = 0, counterC = 0;

  XTHREAD* threadA = GEN_NEW XTHREAD(XTHREADGROUPID_UNGROUP, __L("A"), BumpCounter, (void*)&counterA);
  XTHREAD* threadB = GEN_NEW XTHREAD(XTHREADGROUPID_UNGROUP, __L("B"), BumpCounter, (void*)&counterB);
  XTHREAD* threadC = GEN_NEW XTHREAD(XTHREADGROUPID_UNGROUP, __L("C"), BumpCounter, (void*)&counterC);
  ASSERT_NE(threadA, (XTHREAD*)NULL);
  ASSERT_NE(threadB, (XTHREAD*)NULL);
  ASSERT_NE(threadC, (XTHREAD*)NULL);

  threadA->Run(true);
  threadB->Run(true);
  threadC->Run(true);

  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().AddThread(threadA));
  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().AddThread(threadB));
  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().AddThread(threadC));

  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().ExecuteFunctions());

  EXPECT_EQ(counterA, (XDWORD)1);
  EXPECT_EQ(counterB, (XDWORD)1);
  EXPECT_EQ(counterC, (XDWORD)1);

  ResetList(); // deletes threadA/B/C for us
}


TEST(UNITTEST_XTHREADLISTNONPREEMPTIVE_CLASSNAME, DeleteAllEmptiesListAndFreesOwnedThreads)
{
  ResetList();

  XTHREAD* xthread = GEN_NEW XTHREAD(XTHREADGROUPID_UNGROUP, __L("Owned"), NULL, NULL);
  ASSERT_NE(xthread, (XTHREAD*)NULL);

  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().AddThread(xthread));

  EXPECT_TRUE(XTHREADLISTNONPREEMPTIVE::GetInstance().DeleteAll());

  // The list is empty again: ExecuteFunctions() has nothing to dispatch (xthread itself was freed
  // by DeleteAll()'s DeleteContents(), so it must not be touched again from here).
  EXPECT_FALSE(XTHREADLISTNONPREEMPTIVE::GetInstance().ExecuteFunctions());
}


}
#endif
