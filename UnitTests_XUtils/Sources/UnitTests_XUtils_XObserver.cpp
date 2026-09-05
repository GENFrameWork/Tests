/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XObserver.cpp
*
* @class      UNITTESTS_XUTILS_XOBSERVER
* @brief      XUtils unit tests for XObserver class
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

#include "UnitTests_XUtils_XObserver.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XObserver.h"
#include "XSubject.h"
#include "XPublisher.h"
#include "XEvent.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XOBSERVER
{

// XOBSERVER is abstract (HandleEvent is pure virtual); a minimal concrete test-local subclass
// records how many times / with what event type it was notified.
class TESTOBSERVER : public XOBSERVER
{
  public:
    TESTOBSERVER()  { count = 0; lasttype = 0; }
    ~TESTOBSERVER() { }

    void HandleEvent(XEVENT* event) override
    {
      count++;
      if(event) lasttype = event->GetEventType();
    }

    int    count;
    XDWORD lasttype;
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
  GEN_XPUBLISHER.DeRegisterAllEvents();
  GEN_XPUBLISHER.Active(true);
}


TEST(UNITTESTS_XOBSERVER_CLASSNAME, SubscribeEventWithDefaultObserverUsesThis)
{
  ResetPublisher();

  XSUBJECT     subject;
  TESTOBSERVER observer;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_PING));

  // observer parameter omitted -> XOBSERVER::SubscribeEvent forwards "this" as the observer.
  EXPECT_TRUE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subject));

  XEVENT event(&subject, XEVENT_TYPE_PING);
  EXPECT_TRUE(subject.PostEvent(&event));

  EXPECT_EQ(observer.count, 1);

  ResetPublisher();
}


TEST(UNITTESTS_XOBSERVER_CLASSNAME, SubscribeEventWithExplicitObserverTargetsThatObserver)
{
  ResetPublisher();

  XSUBJECT     subject;
  TESTOBSERVER caller;
  TESTOBSERVER target;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_SOUND));

  // Calling SubscribeEvent on "caller" but naming "target" as the explicit observer argument
  // must register target, not caller, as the one who gets notified.
  EXPECT_TRUE(caller.SubscribeEvent(XEVENT_TYPE_SOUND, &subject, &target));

  XEVENT event(&subject, XEVENT_TYPE_SOUND);
  EXPECT_TRUE(subject.PostEvent(&event));

  EXPECT_EQ(caller.count, 0);
  EXPECT_EQ(target.count, 1);

  ResetPublisher();
}


TEST(UNITTESTS_XOBSERVER_CLASSNAME, UnSubscribeEventStopsFurtherNotifications)
{
  ResetPublisher();

  XSUBJECT     subject;
  TESTOBSERVER observer;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_PING));
  EXPECT_TRUE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subject));

  XEVENT event(&subject, XEVENT_TYPE_PING);
  EXPECT_TRUE(subject.PostEvent(&event));
  EXPECT_EQ(observer.count, 1);

  EXPECT_TRUE(observer.UnSubscribeEvent(XEVENT_TYPE_PING, &subject));

  EXPECT_TRUE(subject.PostEvent(&event));
  EXPECT_EQ(observer.count, 1);  // unchanged: no longer subscribed

  ResetPublisher();
}


TEST(UNITTESTS_XOBSERVER_CLASSNAME, UnSubscribeEventUnknownSubscriptionReturnsFalse)
{
  ResetPublisher();

  XSUBJECT     subject;
  TESTOBSERVER observer;

  EXPECT_FALSE(observer.UnSubscribeEvent(XEVENT_TYPE_PING, &subject));

  ResetPublisher();
}


TEST(UNITTESTS_XOBSERVER_CLASSNAME, MultipleObserversOnSameEventAllGetNotified)
{
  ResetPublisher();

  XSUBJECT     subject;
  TESTOBSERVER observera;
  TESTOBSERVER observerb;
  TESTOBSERVER observerc;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_PING));
  EXPECT_TRUE(observera.SubscribeEvent(XEVENT_TYPE_PING, &subject));
  EXPECT_TRUE(observerb.SubscribeEvent(XEVENT_TYPE_PING, &subject));
  EXPECT_TRUE(observerc.SubscribeEvent(XEVENT_TYPE_PING, &subject));

  XEVENT event(&subject, XEVENT_TYPE_PING);
  EXPECT_TRUE(subject.PostEvent(&event));

  EXPECT_EQ(observera.count, 1);
  EXPECT_EQ(observerb.count, 1);
  EXPECT_EQ(observerc.count, 1);

  ResetPublisher();
}


TEST(UNITTESTS_XOBSERVER_CLASSNAME, SubscribingSameObserverTwiceIsDeduplicated)
{
  ResetPublisher();

  XSUBJECT     subject;
  TESTOBSERVER observer;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_PING));
  EXPECT_TRUE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subject));

  // XPUBLISHER::SubscribeEvent scans eventsvector for an existing (type,subject,observer) entry
  // and only adds a new XPUBLISHERENTRY when none is found -- so re-subscribing the very same
  // (type,subject,observer) triple leaves the internal list unchanged (this call fails: the
  // duplicate is dropped) and the observer is still only notified once per PostEvent.
  EXPECT_FALSE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subject));

  XEVENT event(&subject, XEVENT_TYPE_PING);
  EXPECT_TRUE(subject.PostEvent(&event));

  EXPECT_EQ(observer.count, 1);

  ResetPublisher();
}


TEST(UNITTESTS_XOBSERVER_CLASSNAME, UnsubscribeThenResubscribeWorksAgain)
{
  ResetPublisher();

  XSUBJECT     subject;
  TESTOBSERVER observer;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_PING));
  EXPECT_TRUE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subject));
  EXPECT_TRUE(observer.UnSubscribeEvent(XEVENT_TYPE_PING, &subject));

  // The (type,subject) registration itself (via XSUBJECT::RegisterEvent) is untouched by
  // UnSubscribeEvent, so subscribing again succeeds and notifications resume.
  EXPECT_TRUE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subject));

  XEVENT event(&subject, XEVENT_TYPE_PING);
  EXPECT_TRUE(subject.PostEvent(&event));

  EXPECT_EQ(observer.count, 1);

  ResetPublisher();
}


}
#endif
