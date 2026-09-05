/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XLicense_XEvent.cpp
*
* @class      UNITTESTS_XUTILS_XLICENSE_XEVENT
* @brief      XUtils unit tests for XLicense_XEvent class
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

#include "UnitTests_XUtils_XLicense_XEvent.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XLicense_XEvent.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XLICENSE_XEVENT
{

// XLICENSE is only forward-declared in XLicense_XEvent.h; the event never dereferences the
// pointer it stores, so a fabricated non-null pointer is enough to exercise Get/Set identity.
static XLICENSE* const FAKELICENSE = (XLICENSE*)0x1;


TEST(UNITTESTS_XLICENSE_XEVENT_CLASSNAME, ConstructorDefaultsTypeAndFamilyToLicenseFamily)
{
  XLICENSE_XEVENT event(NULL);

  EXPECT_EQ(event.GetEventType(), (XDWORD)XLICENSEXEVENT_TYPE_UNKNOWN);
  EXPECT_EQ(event.GetEventFamily(), (XDWORD)XEVENT_TYPE_LICENSE);
}


TEST(UNITTESTS_XLICENSE_XEVENT_CLASSNAME, ConstructorWithExplicitTypeAndFamily)
{
  XLICENSE_XEVENT event(NULL, XLICENSEXEVENT_TYPE_EXPIRED, XEVENT_TYPE_LICENSE);

  EXPECT_EQ(event.GetEventType(), (XDWORD)XLICENSEXEVENT_TYPE_EXPIRED);
  EXPECT_EQ(event.GetEventFamily(), (XDWORD)XEVENT_TYPE_LICENSE);
}


TEST(UNITTESTS_XLICENSE_XEVENT_CLASSNAME, GetReturnsNullByDefault)
{
  XLICENSE_XEVENT event(NULL);

  EXPECT_EQ((void*)event.Get(), (void*)NULL);
}


TEST(UNITTESTS_XLICENSE_XEVENT_CLASSNAME, SetAndGetLicenseRoundTrips)
{
  XLICENSE_XEVENT event(NULL);

  event.Set(FAKELICENSE);

  EXPECT_EQ((void*)event.Get(), (void*)FAKELICENSE);
}


}
#endif
