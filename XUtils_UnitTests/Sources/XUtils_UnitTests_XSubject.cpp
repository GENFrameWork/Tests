/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XSubject.cpp
*
* @class      XUTILS_UNITTESTS_XSUBJECT
* @brief      XUtils unit tests for XSubject class
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

#include "XUtils_UnitTests_XSubject.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XSubject.h"
#include "XObserver.h"
#include "XPublisher.h"
#include "XEvent.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XSUBJECT
{

// XSUBJECT itself has no observable state: RegisterEvent / DeRegisterEvent / DeRegisterAllEvents /
// PostEvent are thin forwarders onto the GEN_XPUBLISHER singleton (see XSubject.cpp). To exercise
// them meaningfully we drive the real singleton end-to-end through a minimal concrete XOBSERVER,
// counting how many times / with what event it gets notified.
class TESTSUBJECTOBSERVER : public XOBSERVER
{
  public:
    TESTSUBJECTOBSERVER()  { count = 0; lasttype = 0; }
    ~TESTSUBJECTOBSERVER() { }

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


TEST(UNITTEST_XSUBJECT_CLASSNAME, RegisterEventThenPostEventReachesSubscribedObserver)
{
  ResetPublisher();

  XSUBJECT             subject;
  TESTSUBJECTOBSERVER  observer;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_PING));
  EXPECT_TRUE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subject));

  XEVENT event(&subject, XEVENT_TYPE_PING);
  EXPECT_TRUE(subject.PostEvent(&event));

  EXPECT_EQ(observer.count, 1);
  EXPECT_EQ(observer.lasttype, (XDWORD)XEVENT_TYPE_PING);

  ResetPublisher();
}


TEST(UNITTEST_XSUBJECT_CLASSNAME, RegisterEventSameTypeAndSubjectTwiceReturnsFalse)
{
  ResetPublisher();

  XSUBJECT subject;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_PING));
  // XPUBLISHER::RegisterEvent scans for an existing (type,subject) pair first and only Adds
  // when none is found, so a second identical registration is rejected.
  EXPECT_FALSE(subject.RegisterEvent(XEVENT_TYPE_PING));

  ResetPublisher();
}


TEST(UNITTEST_XSUBJECT_CLASSNAME, PostEventWithoutSubscribersStillReturnsTrue)
{
  ResetPublisher();

  XSUBJECT subject;
  XEVENT   event(&subject, XEVENT_TYPE_PING);

  // PostEvent only checks the publisher's "on" flag before returning true/false: it does not
  // require the subject to be registered nor any observer to be subscribed.
  EXPECT_TRUE(subject.PostEvent(&event));

  ResetPublisher();
}


TEST(UNITTEST_XSUBJECT_CLASSNAME, DeRegisterEventRemovesSubscriptionSoNewSubscribeFails)
{
  ResetPublisher();

  XSUBJECT             subject;
  TESTSUBJECTOBSERVER  observer;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_PING));
  EXPECT_TRUE(subject.DeRegisterEvent(XEVENT_TYPE_PING));

  // SubscribeEvent requires the (type,subject) pair to already be registered; after
  // DeRegisterEvent it is gone, so subscribing now fails.
  EXPECT_FALSE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subject));

  ResetPublisher();
}


TEST(UNITTEST_XSUBJECT_CLASSNAME, DeRegisterAllEventsClearsExistingSubscriptions)
{
  ResetPublisher();

  XSUBJECT             subject;
  TESTSUBJECTOBSERVER  observer;

  EXPECT_TRUE(subject.RegisterEvent(XEVENT_TYPE_PING));
  EXPECT_TRUE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subject));

  EXPECT_TRUE(subject.DeRegisterAllEvents());

  XEVENT event(&subject, XEVENT_TYPE_PING);
  EXPECT_TRUE(subject.PostEvent(&event));

  EXPECT_EQ(observer.count, 0);

  ResetPublisher();
}


TEST(UNITTEST_XSUBJECT_CLASSNAME, PostEventTwoArgOverloadTargetsGivenSubject)
{
  ResetPublisher();

  XSUBJECT             subjecta;
  XSUBJECT             subjectb;
  TESTSUBJECTOBSERVER  observer;

  EXPECT_TRUE(subjecta.RegisterEvent(XEVENT_TYPE_PING));
  EXPECT_TRUE(observer.SubscribeEvent(XEVENT_TYPE_PING, &subjecta));

  XEVENT event(&subjectb, XEVENT_TYPE_PING);

  // Posting through subjectb (the 2-arg overload lets the caller name a different XSUBJECT than
  // "this") must not reach an observer that only subscribed against subjecta.
  EXPECT_TRUE(subjectb.PostEvent(&event, &subjectb));
  EXPECT_EQ(observer.count, 0);

  // Posting explicitly naming subjecta as the target does reach it.
  EXPECT_TRUE(subjectb.PostEvent(&event, &subjecta));
  EXPECT_EQ(observer.count, 1);

  ResetPublisher();
}


TEST(UNITTEST_XSUBJECT_CLASSNAME, MultipleSubjectsKeepIndependentEventTypeRegistrations)
{
  ResetPublisher();

  XSUBJECT             subjecta;
  XSUBJECT             subjectb;
  TESTSUBJECTOBSERVER  observera;
  TESTSUBJECTOBSERVER  observerb;

  EXPECT_TRUE(subjecta.RegisterEvent(XEVENT_TYPE_PING));
  EXPECT_TRUE(subjectb.RegisterEvent(XEVENT_TYPE_SOUND));

  EXPECT_TRUE(observera.SubscribeEvent(XEVENT_TYPE_PING, &subjecta));
  EXPECT_TRUE(observerb.SubscribeEvent(XEVENT_TYPE_SOUND, &subjectb));

  XEVENT eventping(&subjecta, XEVENT_TYPE_PING);
  EXPECT_TRUE(subjecta.PostEvent(&eventping));

  EXPECT_EQ(observera.count, 1);
  EXPECT_EQ(observerb.count, 0);

  ResetPublisher();
}


}
#endif
