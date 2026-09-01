/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XPublisher.cpp
*
* @class      XUTILS_UNITTESTS_XPUBLISHER
* @brief      XUtils unit tests for XPublisher class
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

#include "XUtils_UnitTests_XPublisher.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XPublisher.h"
#include "XSubject.h"
#include "XObserver.h"
#include "XEvent.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XPUBLISHER
{

class TESTPUBLISHEROBSERVER : public XOBSERVER
{
  public:
    TESTPUBLISHEROBSERVER() { count = 0; }
    ~TESTPUBLISHEROBSERVER() { }

    void HandleEvent(XEVENT* event) override { count++; }

    int count;
};


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void ResetPublisher()
* @brief      Leaves the GEN_XPUBLISHER singleton in a clean, active, empty state before a test.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void ResetPublisher()
{
  XPUBLISHER::GetInstance().DeRegisterAllEvents();
  XPUBLISHER::GetInstance().Active(true);
}


TEST(UNITTEST_XPUBLISHER_CLASSNAME, GetInstanceCreatesAndReturnsSameReference)
{
  XPUBLISHER& instance1 = XPUBLISHER::GetInstance();
  EXPECT_TRUE(XPUBLISHER::GetIsInstanced());

  XPUBLISHER& instance2 = XPUBLISHER::GetInstance();
  EXPECT_EQ(&instance1, &instance2);

  ResetPublisher();
}


TEST(UNITTEST_XPUBLISHER_CLASSNAME, DelInstanceTwice)
{
  XPUBLISHER::GetInstance();  // ensure instanced
  EXPECT_TRUE(XPUBLISHER::GetIsInstanced());

  EXPECT_TRUE(XPUBLISHER::DelInstance());
  EXPECT_FALSE(XPUBLISHER::GetIsInstanced());
  EXPECT_FALSE(XPUBLISHER::DelInstance());

  // Lazily recreate for subsequent tests / other suites relying on GEN_XPUBLISHER.
  XPUBLISHER::GetInstance();
  ResetPublisher();
}


TEST(UNITTEST_XPUBLISHER_CLASSNAME, DelInstanceThenGetInstanceCreatesFreshDefaultState)
{
  XSUBJECT              subject;
  TESTPUBLISHEROBSERVER observer;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_PING));
  EXPECT_TRUE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subject));

  EXPECT_TRUE(XPUBLISHER::DelInstance());
  EXPECT_FALSE(XPUBLISHER::GetIsInstanced());

  // A fresh instance starts with no registrations at all: posting to the same (now stale)
  // subject/type pair reaches nobody because the previous registration was destroyed with the
  // old instance.
  XEVENT event(&subject, XEVENT_TYPE_PING);
  EXPECT_TRUE(XPUBLISHER::GetInstance().PostEvent(&event, &subject));
  EXPECT_EQ(observer.count, 0);

  ResetPublisher();
}


TEST(UNITTEST_XPUBLISHER_CLASSNAME, ActiveFalseBlocksPostEvent)
{
  ResetPublisher();

  XSUBJECT              subject;
  TESTPUBLISHEROBSERVER observer;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_PING));
  EXPECT_TRUE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subject));

  XPUBLISHER::GetInstance().Active(false);

  XEVENT event(&subject, XEVENT_TYPE_PING);
  EXPECT_FALSE(subject.PostEvent(&event));
  EXPECT_EQ(observer.count, 0);

  XPUBLISHER::GetInstance().Active(true);
  EXPECT_TRUE(subject.PostEvent(&event));
  EXPECT_EQ(observer.count, 1);

  ResetPublisher();
}


TEST(UNITTEST_XPUBLISHER_CLASSNAME, IsInEventIsFalseOutsideOfPostEvent)
{
  ResetPublisher();

  EXPECT_FALSE(XPUBLISHER::GetInstance().IsInEvent());
}


TEST(UNITTEST_XPUBLISHER_CLASSNAME, RegisterAndDeRegisterEventDirectly)
{
  ResetPublisher();

  XSUBJECT subject;

  EXPECT_TRUE(XPUBLISHER::GetInstance().RegisterEvent(XEVENT_TYPE_PING, &subject));
  EXPECT_TRUE(XPUBLISHER::GetInstance().DeRegisterEvent(XEVENT_TYPE_PING, &subject));

  // Once removed, de-registering the same pair again finds nothing to remove.
  EXPECT_FALSE(XPUBLISHER::GetInstance().DeRegisterEvent(XEVENT_TYPE_PING, &subject));

  ResetPublisher();
}


TEST(UNITTEST_XPUBLISHER_CLASSNAME, SubscribeEventRejectsNullSubjectOrObserver)
{
  ResetPublisher();

  XSUBJECT              subject;
  TESTPUBLISHEROBSERVER observer;

  EXPECT_FALSE(XPUBLISHER::GetInstance().SubscribeEvent(XEVENT_TYPE_PING, NULL, &observer));
  EXPECT_FALSE(XPUBLISHER::GetInstance().SubscribeEvent(XEVENT_TYPE_PING, &subject, NULL));

  ResetPublisher();
}


TEST(UNITTEST_XPUBLISHER_CLASSNAME, SubscribeEventWithoutPriorRegisterEventFails)
{
  ResetPublisher();

  XSUBJECT              subject;
  TESTPUBLISHEROBSERVER observer;

  // SubscribeEvent requires the (type,subject) pair to already be present in subjectsmap
  // (added by RegisterEvent); skipping RegisterEvent makes it fail even with valid pointers.
  EXPECT_FALSE(XPUBLISHER::GetInstance().SubscribeEvent(XEVENT_TYPE_PING, &subject, &observer));

  ResetPublisher();
}


TEST(UNITTEST_XPUBLISHER_CLASSNAME, PublisherEntryDefaultConstructionIsZeroed)
{
  XPUBLISHERENTRY entry;

  EXPECT_EQ(entry.type, (XDWORD)0);
  EXPECT_EQ(entry.subject, (XSUBJECT*)NULL);
  EXPECT_EQ(entry.observer, (XOBSERVER*)NULL);
}


}
#endif
