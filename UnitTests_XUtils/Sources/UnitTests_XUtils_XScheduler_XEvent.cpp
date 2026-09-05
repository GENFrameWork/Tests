/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XScheduler_XEvent.cpp
*
* @class      UNITTESTS_XUTILS_XSCHEDULER_XEVENT
* @brief      XUtils unit tests for XScheduler_XEvent class
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

#include "UnitTests_XUtils_XScheduler_XEvent.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XScheduler_XEvent.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XSCHEDULER_XEVENT
{

// XSCHEDULER/XSCHEDULERTASK/XDATETIME are only forward-declared in XScheduler_XEvent.h; the
// event never dereferences the pointers it stores, so fabricated non-null pointers are enough
// to exercise Get/Set identity.
static XSCHEDULER* const     FAKESCHEDULER = (XSCHEDULER*)0x1;
static XSCHEDULERTASK* const FAKETASK      = (XSCHEDULERTASK*)0x2;
static XDATETIME* const      FAKEDATETIME  = (XDATETIME*)0x3;


TEST(UNITTESTS_XSCHEDULER_XEVENT_CLASSNAME, ConstructorDefaultsTypeAndFamily)
{
  XSCHEDULER_XEVENT event(NULL);

  EXPECT_EQ(event.GetEventType(), (XDWORD)XSCHEDULER_XEVENT_TYPE_UNKNOWN);
  EXPECT_EQ(event.GetEventFamily(), (XDWORD)XEVENT_TYPE_SCHEDULER);
}


TEST(UNITTESTS_XSCHEDULER_XEVENT_CLASSNAME, SchedulerDefaultsToNullAndRoundTrips)
{
  XSCHEDULER_XEVENT event(NULL);

  EXPECT_EQ((void*)NULL, (void*)event.GetScheduler());

  event.SetScheduler(FAKESCHEDULER);
  EXPECT_EQ((void*)FAKESCHEDULER, (void*)event.GetScheduler());
}


TEST(UNITTESTS_XSCHEDULER_XEVENT_CLASSNAME, TaskDefaultsToNullAndRoundTrips)
{
  XSCHEDULER_XEVENT event(NULL);

  EXPECT_EQ((void*)NULL, (void*)event.GetTask());

  event.SetTask(FAKETASK);
  EXPECT_EQ((void*)FAKETASK, (void*)event.GetTask());
}


TEST(UNITTESTS_XSCHEDULER_XEVENT_CLASSNAME, DateTimeDefaultsToNullAndRoundTrips)
{
  XSCHEDULER_XEVENT event(NULL);

  EXPECT_EQ((void*)NULL, (void*)event.GetDateTime());

  event.SetDateTime(FAKEDATETIME);
  EXPECT_EQ((void*)FAKEDATETIME, (void*)event.GetDateTime());
}


}
#endif
