/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XEvent.cpp
*
* @class      XUTILS_UNITTESTS_XEVENT
* @brief      XUtils unit tests for XEvent class
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

#include "XUtils_UnitTests_XEvent.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XEvent.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XEVENT
{

// XSUBJECT is only forward-declared in XEvent.h; XEVENT never dereferences
// the pointer it stores, so a fabricated non-null pointer value is enough
// to exercise Get/SetSubject identity without needing a real XSUBJECT.
static XSUBJECT* const FAKESUBJECT = (XSUBJECT*)0x1;


TEST(UNITTEST_XEVENT_CLASSNAME, ConstructorWithFamilyAndType)
{
  XEVENT event(FAKESUBJECT, XEVENT_TYPE_LICENSE, XEVENT_TYPE_SCHEDULER);

  EXPECT_EQ((void*)event.GetSubject(), (void*)FAKESUBJECT);
  EXPECT_EQ(event.GetEventType(), (XDWORD)XEVENT_TYPE_LICENSE);
  EXPECT_EQ(event.GetEventFamily(), (XDWORD)XEVENT_TYPE_SCHEDULER);
}


TEST(UNITTEST_XEVENT_CLASSNAME, ConstructorWithoutFamilyLeavesFamilyNone)
{
  // The 2-argument constructor sets subject/type but never assigns
  // `family`, so it keeps whatever Clean() set it to (XEVENT_TYPE_NONE).
  XEVENT event(FAKESUBJECT, XEVENT_TYPE_PING);

  EXPECT_EQ((void*)event.GetSubject(), (void*)FAKESUBJECT);
  EXPECT_EQ(event.GetEventType(), (XDWORD)XEVENT_TYPE_PING);
  EXPECT_EQ(event.GetEventFamily(), (XDWORD)XEVENT_TYPE_NONE);
}


TEST(UNITTEST_XEVENT_CLASSNAME, ConstructorWithNullSubject)
{
  XEVENT event(NULL, XEVENT_TYPE_NONE);

  EXPECT_EQ((void*)event.GetSubject(), (void*)NULL);
}


TEST(UNITTEST_XEVENT_CLASSNAME, SetAndGetSubject)
{
  XEVENT event(NULL, XEVENT_TYPE_NONE);

  EXPECT_EQ((void*)event.GetSubject(), (void*)NULL);

  event.SetSubject(FAKESUBJECT);

  EXPECT_EQ((void*)event.GetSubject(), (void*)FAKESUBJECT);
}


TEST(UNITTEST_XEVENT_CLASSNAME, SetAndGetEventFamilyAndType)
{
  XEVENT event(FAKESUBJECT, XEVENT_TYPE_NONE, XEVENT_TYPE_NONE);

  event.SetEventFamily(XEVENT_TYPE_GRAPHICS);
  EXPECT_EQ(event.GetEventFamily(), (XDWORD)XEVENT_TYPE_GRAPHICS);

  event.SetEventType(XEVENT_TYPE_SOUND);
  EXPECT_EQ(event.GetEventType(), (XDWORD)XEVENT_TYPE_SOUND);
}


}
#endif

