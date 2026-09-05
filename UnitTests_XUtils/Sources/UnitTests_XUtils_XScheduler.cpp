/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XScheduler.cpp
*
* @class      UNITTESTS_XUTILS_XSCHEDULER
* @brief      XUtils unit tests for XScheduler and XSchedulerTask classes
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

#include "UnitTests_XUtils_XScheduler.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XScheduler.h"
#include "XScheduler_XEvent.h"
#include "XObserver.h"
#include "XDateTime.h"
#include "XTimer.h"
#include "XSleep.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XSCHEDULER
{

class SCHEDULEROBSERVER : public XOBSERVER
{
  public:
    SCHEDULEROBSERVER() { count = 0; lasttask = NULL; lastscheduler = NULL; }
    ~SCHEDULEROBSERVER() { }

    void HandleEvent(XEVENT* event) override
    {
      count++;

      XSCHEDULER_XEVENT* schedulerevent = (XSCHEDULER_XEVENT*)event;
      lasttask      = schedulerevent->GetTask();
      lastscheduler = schedulerevent->GetScheduler();
    }

    int             count;
    XSCHEDULERTASK* lasttask;
    XSCHEDULER*     lastscheduler;
};


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static XBYTE DayOfWeekMaskFor(XDATETIME* xdatetime)
* @brief      Maps a real XDATETIME's actual GetDayOfWeek() to the matching XSCHEDULER_DAYWEEK_IS*
*             bitmask value, so day-of-week tests never have to hardcode "today" is some fixed day.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static XBYTE DayOfWeekMaskFor(XDATETIME* xdatetime)
{
  switch(xdatetime->GetDayOfWeek())
    {
      case XDATETIME_DAYWEEK_SUNDAY     : return XSCHEDULER_DAYWEEK_ISSUNDAY;
      case XDATETIME_DAYWEEK_MONDAY     : return XSCHEDULER_DAYWEEK_ISMONDAY;
      case XDATETIME_DAYWEEK_TUESDAY    : return XSCHEDULER_DAYWEEK_ISTUESDAY;
      case XDATETIME_DAYWEEK_WEDNESDAY  : return XSCHEDULER_DAYWEEK_ISWEDNESDAY;
      case XDATETIME_DAYWEEK_THURSDAY   : return XSCHEDULER_DAYWEEK_ISTHURSDAY;
      case XDATETIME_DAYWEEK_FRIDAY     : return XSCHEDULER_DAYWEEK_ISFRIDAY;
      case XDATETIME_DAYWEEK_SATURDAY   : return XSCHEDULER_DAYWEEK_ISSATURDAY;
    }

  return XSCHEDULER_DAYWEEK_NONE;
}


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


/*---- XSCHEDULERTASK: pure condition-evaluation logic, no threading involved -----------------------------------------*/


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskConstructorInitializesDefaults)
{
  XSCHEDULERTASK task(NULL);

  EXPECT_NE(task.GetXTimer(), (XTIMER*)NULL);
  EXPECT_FALSE(task.IsActive());
  EXPECT_EQ(task.GetID(), (XDWORD)0);
  EXPECT_EQ(task.GetNCyclesTodo(), 0);
  EXPECT_FALSE(task.IsCyclic());
  EXPECT_FALSE(task.IsStartImmediatelyCycles());
  EXPECT_FALSE(task.IsInValidTimeLimit());
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskSetIsActiveTrue)
{
  XSCHEDULERTASK task(NULL);

  EXPECT_TRUE(task.SetIsActive(true));
  EXPECT_TRUE(task.IsActive());

  EXPECT_TRUE(task.SetIsActive(false));
  EXPECT_FALSE(task.IsActive());
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskGetSetID)
{
  XSCHEDULERTASK task(NULL);

  task.SetID(42);
  EXPECT_EQ(task.GetID(), (XDWORD)42);
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskSetNCyclesPointerOverloadDefaultsToCycleForever)
{
  XSCHEDULERTASK task(NULL);

  EXPECT_TRUE(task.SetNCycles());
  EXPECT_EQ(task.GetNCyclesTodo(), XSCHEDULER_CYCLEFOREVER);
  EXPECT_TRUE(task.IsCyclic()); // -1 != 0, so this counts as "cyclic"
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskSetNCyclesClampsNegativeToCycleForever)
{
  XSCHEDULERTASK task(NULL);

  EXPECT_TRUE(task.SetNCycles(-99));
  EXPECT_EQ(task.GetNCyclesTodo(), XSCHEDULER_CYCLEFOREVER);
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskSetNCyclesZeroIsNotCyclic)
{
  XSCHEDULERTASK task(NULL);

  EXPECT_TRUE(task.SetNCycles(0));
  EXPECT_EQ(task.GetNCyclesTodo(), 0);
  EXPECT_FALSE(task.IsCyclic());
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskThreeSetNCyclesOverloadsAgreeOnCycleCount)
{
  // Same requested cycle count via all 3 overloads (XDATETIME* cadence / XQWORD seconds / int
  // seconds) must all land on the same GetNCyclesTodo(), confirming the int/XQWORD overloads
  // forward correctly into the XDATETIME* overload rather than diverging.
  XSCHEDULERTASK taskPointer(NULL);
  XSCHEDULERTASK taskQWord(NULL);
  XSCHEDULERTASK taskInt(NULL);

  EXPECT_TRUE(taskPointer.SetNCycles(7, (XDATETIME*)NULL));
  EXPECT_TRUE(taskQWord.SetNCycles(7, (XQWORD)5));
  EXPECT_TRUE(taskInt.SetNCycles(7, (int)5));

  EXPECT_EQ(taskPointer.GetNCyclesTodo(), 7);
  EXPECT_EQ(taskQWord.GetNCyclesTodo(), 7);
  EXPECT_EQ(taskInt.GetNCyclesTodo(), 7);
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskCheckConditionFalseWhenDateTimeIsNull)
{
  XSCHEDULERTASK task(NULL);
  XTIMER*        xtimer = GEN_XFACTORY.CreateTimer();

  EXPECT_FALSE(task.CheckCondition(NULL, xtimer));

  GEN_XFACTORY.DeleteTimer(xtimer);
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskCheckConditionBlockedWhenNoCyclesRequested)
{
  // Default-constructed task has ncyclestodo==0 -> ncyclesactual==0, which CheckCondition() gates
  // on unconditionally ("if(!ncyclesactual) return false;"), even with no time limits/day mask set.
  XSCHEDULERTASK task(NULL);
  XDATETIME      now;
  now.Read();

  EXPECT_FALSE(task.CheckCondition(&now, task.GetXTimer()));
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskSetTimeLimitsAlwaysReturnsFalseEvenOnSuccess)
{
  // XSCHEDULERTASK::SetTimeLimits() (XScheduler.cpp) unconditionally "return false;" at the end,
  // regardless of whether the copy actually happened -- captured here as real (if surprising)
  // behavior rather than fixed, since the copy itself does take effect (proven via
  // IsInValidTimeLimit()/CheckCondition below).
  XSCHEDULERTASK task(NULL);
  XDATETIME      now, start, end;

  now.Read();
  start.CopyFrom(now); start.SubtractDays(1);
  end.CopyFrom(now);   end.AddDays(1);

  EXPECT_FALSE(task.SetTimeLimits(&start, &end));

  EXPECT_TRUE(task.SetNCycles(1));

  // The limits were, in fact, applied despite the false return value above.
  EXPECT_TRUE(task.CheckCondition(&now, task.GetXTimer()));
  EXPECT_TRUE(task.IsInValidTimeLimit());
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskCheckConditionBlockedByFutureTimeLimitStart)
{
  XSCHEDULERTASK task(NULL);
  XDATETIME      now, start;

  now.Read();
  start.CopyFrom(now);
  start.AddDays(1); // starts tomorrow: "now" is still before the valid window

  task.SetTimeLimits(&start, NULL);
  task.SetNCycles(1);

  EXPECT_FALSE(task.CheckCondition(&now, task.GetXTimer()));
  EXPECT_FALSE(task.IsInValidTimeLimit());
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskCheckConditionBlockedByPastTimeLimitEnd)
{
  XSCHEDULERTASK task(NULL);
  XDATETIME      now, end;

  now.Read();
  end.CopyFrom(now);
  end.SubtractDays(1); // ended yesterday: "now" is already past the valid window

  task.SetTimeLimits(NULL, &end);
  task.SetNCycles(1);

  EXPECT_FALSE(task.CheckCondition(&now, task.GetXTimer()));
  EXPECT_FALSE(task.IsInValidTimeLimit());
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskCheckConditionPassesWithinTimeLimitWindow)
{
  XSCHEDULERTASK task(NULL);
  XDATETIME      now, start, end;

  now.Read();
  start.CopyFrom(now); start.SubtractDays(1);
  end.CopyFrom(now);   end.AddDays(1);

  task.SetTimeLimits(&start, &end);
  task.SetNCycles(1);

  EXPECT_TRUE(task.CheckCondition(&now, task.GetXTimer()));
  EXPECT_TRUE(task.IsInValidTimeLimit());
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskCheckConditionDayOfWeekMaskMatchesToday)
{
  XSCHEDULERTASK task(NULL);
  XDATETIME      now;
  now.Read();

  task.SetConditionDayWeek(DayOfWeekMaskFor(&now));
  task.SetNCycles(1);

  EXPECT_TRUE(task.CheckCondition(&now, task.GetXTimer()));
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskCheckConditionDayOfWeekMaskMismatchBlocks)
{
  XSCHEDULERTASK task(NULL);
  XDATETIME      now;
  now.Read();

  XBYTE todaybit  = DayOfWeekMaskFor(&now);
  XBYTE otherdays = (~todaybit) & 0x7F; // every day-of-week bit except today's

  task.SetConditionDayWeek(otherdays);
  task.SetNCycles(1);

  EXPECT_FALSE(task.CheckCondition(&now, task.GetXTimer()));
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskCheckConditionCadenceGateBlocksImmediateRecheck)
{
  // SetNCycles(n, cadenceinseconds) builds a real cadence date under the hood: CheckCondition()
  // only fires once GetXTimer()'s elapsed seconds reach that cadence.
  XSCHEDULERTASK task(NULL);
  XDATETIME      now;
  now.Read();

  EXPECT_TRUE(task.SetNCycles(1, (XQWORD)9999));
  task.ResetCondition(); // resets the internal XTIMER used as "time since last fire"

  EXPECT_FALSE(task.CheckCondition(&now, task.GetXTimer()));
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskCheckConditionZeroCadenceDoesNotBlock)
{
  XSCHEDULERTASK task(NULL);
  XDATETIME      now;
  now.Read();

  EXPECT_TRUE(task.SetNCycles(1, (XQWORD)0));
  task.ResetCondition();

  EXPECT_TRUE(task.CheckCondition(&now, task.GetXTimer()));
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskStartConditionImmediatelyForcesNextCheckToPass)
{
  XSCHEDULERTASK task(NULL);
  XDATETIME      now;
  now.Read();

  EXPECT_TRUE(task.SetNCycles(1, (XQWORD)9999)); // large cadence: would normally block
  task.ResetCondition();

  EXPECT_TRUE(task.StartConditionImmediately());

  EXPECT_TRUE(task.CheckCondition(&now, task.GetXTimer()));
}


/*---- XSCHEDULER: real background-thread engine (bounded polling, no fixed sleeps) ------------------------------------*/


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, IniCreatesMutexThreadAndActivates)
{
  XSCHEDULER scheduler;

  EXPECT_TRUE(scheduler.Ini());
  EXPECT_TRUE(scheduler.IsActive());
  EXPECT_NE(scheduler.GetMutexScheduler(), (XMUTEX*)NULL);
  EXPECT_NE(scheduler.GetDateTimeActual(), (XDATETIME*)NULL);

  EXPECT_TRUE(scheduler.End());
  EXPECT_FALSE(scheduler.IsActive());
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, ActivateTogglesIsActive)
{
  XSCHEDULER scheduler;
  ASSERT_TRUE(scheduler.Ini());

  scheduler.Activate(false);
  EXPECT_FALSE(scheduler.IsActive());

  scheduler.Activate(true);
  EXPECT_TRUE(scheduler.IsActive());

  scheduler.End();
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskAddGetAndGetForID)
{
  XSCHEDULER scheduler;
  ASSERT_TRUE(scheduler.Ini());

  XSCHEDULERTASK* task = GEN_NEW XSCHEDULERTASK(&scheduler);
  task->SetID(5);

  EXPECT_TRUE(scheduler.Task_Add(task));
  EXPECT_EQ(scheduler.Task_Get(0), task);
  EXPECT_EQ(scheduler.Task_GetForID(5), task);
  EXPECT_EQ(scheduler.Task_GetForID(999), (XSCHEDULERTASK*)NULL);

  scheduler.Task_DelAll(); // also deletes the task object for us
  scheduler.End();
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskDelForIDRemovesAndDeletesTask)
{
  XSCHEDULER scheduler;
  ASSERT_TRUE(scheduler.Ini());

  XSCHEDULERTASK* task = GEN_NEW XSCHEDULERTASK(&scheduler);
  task->SetID(9);
  scheduler.Task_Add(task);

  EXPECT_TRUE(scheduler.Task_DelForID(9));
  EXPECT_EQ(scheduler.Task_GetForID(9), (XSCHEDULERTASK*)NULL);
  EXPECT_FALSE(scheduler.Task_DelForID(9)); // already gone

  scheduler.End();
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskDelByIndexRemovesAndDeletesTask)
{
  XSCHEDULER scheduler;
  ASSERT_TRUE(scheduler.Ini());

  XSCHEDULERTASK* task = GEN_NEW XSCHEDULERTASK(&scheduler);
  scheduler.Task_Add(task);

  EXPECT_TRUE(scheduler.Task_Del(0));
  EXPECT_EQ(scheduler.Task_Get(0), (XSCHEDULERTASK*)NULL);

  scheduler.End();
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, TaskDelAllClearsEveryTask)
{
  XSCHEDULER scheduler;
  ASSERT_TRUE(scheduler.Ini());

  scheduler.Task_Add(GEN_NEW XSCHEDULERTASK(&scheduler));
  scheduler.Task_Add(GEN_NEW XSCHEDULERTASK(&scheduler));
  scheduler.Task_Add(GEN_NEW XSCHEDULERTASK(&scheduler));

  EXPECT_TRUE(scheduler.Task_DelAll());
  EXPECT_EQ(scheduler.Task_Get(0), (XSCHEDULERTASK*)NULL);

  scheduler.End();
}


TEST(UNITTESTS_XSCHEDULER_CLASSNAME, EndToEndActiveTaskFiresSchedulerXEvent)
{
  // Full loop: a real background XTHREAD (via XSCHEDULER::Ini()) repeatedly evaluates the task's
  // CheckCondition() and, once due, posts an XSCHEDULER_XEVENT through the inherited XSUBJECT/
  // XPUBLISHER mechanism -- observed here via a real XOBSERVER subscription, with a bounded poll
  // (never a fixed sleep) standing in for "wait for the event to arrive".
  XSCHEDULER scheduler;
  ASSERT_TRUE(scheduler.Ini());

  SCHEDULEROBSERVER observer;
  ASSERT_TRUE(observer.SubscribeEvent(XEVENT_TYPE_SCHEDULER, &scheduler));

  XSCHEDULERTASK* task = GEN_NEW XSCHEDULERTASK(&scheduler);
  task->SetID(77);
  task->SetIsActive(true);   // ThreadScheduler() only ever checks active tasks
  task->SetNCycles(1);       // no cadence limit (NULL XDATETIME*), fires as soon as it is checked

  EXPECT_TRUE(scheduler.Task_Add(task));

  EnsureXSleepInstance();

  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  bool    fired  = false;

  while(xtimer->GetMeasureSeconds() < 3)
    {
      if(observer.count >= 1) { fired = true; break; }
      GEN_XSLEEP.MicroSeconds(2000);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);

  EXPECT_TRUE(fired);
  EXPECT_GE(observer.count, 1);
  EXPECT_EQ(observer.lasttask, task);
  EXPECT_EQ(observer.lastscheduler, &scheduler);

  scheduler.Task_DelAll();
  scheduler.End();
}


}
#endif
