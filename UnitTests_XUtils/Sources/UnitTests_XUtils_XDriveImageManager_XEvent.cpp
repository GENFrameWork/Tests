/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XDriveImageManager_XEvent.cpp
*
* @class      UNITTESTS_XUTILS_XDRIVEIMAGEMANAGER_XEVENT
* @brief      XUtils unit tests for XDriveImageManager_XEvent class
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

#include "UnitTests_XUtils_XDriveImageManager_XEvent.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XDriveImageManager_XEvent.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XDRIVEIMAGEMANAGER_XEVENT
{

// XDRIVEIMAGEMANAGER_DRIVE is only forward-declared via XDriveImageManager.h's own forward
// declarations; the event never dereferences the pointer it stores, so a fabricated non-null
// pointer is enough to exercise Get/Set identity.
static XDRIVEIMAGEMANAGER_DRIVE* const FAKEDRIVE = (XDRIVEIMAGEMANAGER_DRIVE*)0x1;


TEST(UNITTESTS_XDRIVEIMAGEMANAGER_XEVENT_CLASSNAME, ConstructorDefaultsTypeAndFamily)
{
  XDRIVEIMAGEMANAGER_XEVENT event(NULL);

  EXPECT_EQ(event.GetEventType(), (XDWORD)XDRIVEIMAGEMANAGER_XEVENT_TYPE_UNKNOWN);
  EXPECT_EQ(event.GetEventFamily(), (XDWORD)XEVENT_TYPE_DRIVEIMAGEMANAGER);
}


TEST(UNITTESTS_XDRIVEIMAGEMANAGER_XEVENT_CLASSNAME, ConstructorWithExplicitType)
{
  XDRIVEIMAGEMANAGER_XEVENT event(NULL, XDRIVEIMAGEMANAGER_XEVENT_TYPE_READSECTORS);

  EXPECT_EQ(event.GetEventType(), (XDWORD)XDRIVEIMAGEMANAGER_XEVENT_TYPE_READSECTORS);
}


TEST(UNITTESTS_XDRIVEIMAGEMANAGER_XEVENT_CLASSNAME, GetDriveReturnsNullByDefault)
{
  XDRIVEIMAGEMANAGER_XEVENT event(NULL);

  EXPECT_EQ((void*)event.GetDrive(), (void*)NULL);
}


TEST(UNITTESTS_XDRIVEIMAGEMANAGER_XEVENT_CLASSNAME, SetAndGetDriveRoundTrips)
{
  XDRIVEIMAGEMANAGER_XEVENT event(NULL);

  event.SetDrive(FAKEDRIVE);

  EXPECT_EQ((void*)event.GetDrive(), (void*)FAKEDRIVE);
}


TEST(UNITTESTS_XDRIVEIMAGEMANAGER_XEVENT_CLASSNAME, IndexSectorDefaultsToZeroAndRoundTrips)
{
  XDRIVEIMAGEMANAGER_XEVENT event(NULL);

  EXPECT_EQ((XQWORD)0, event.GetIndexSector());

  event.SetIndexSector((XQWORD)123456789);
  EXPECT_EQ((XQWORD)123456789, event.GetIndexSector());
}


TEST(UNITTESTS_XDRIVEIMAGEMANAGER_XEVENT_CLASSNAME, NumberSectorsInOperationRoundTrips)
{
  XDRIVEIMAGEMANAGER_XEVENT event(NULL);

  event.SetNumberSectorsInOperation((XQWORD)4096);
  EXPECT_EQ((XQWORD)4096, event.GetNumberSectorsInOperation());
}


TEST(UNITTESTS_XDRIVEIMAGEMANAGER_XEVENT_CLASSNAME, OperationPercentRoundTrips)
{
  XDRIVEIMAGEMANAGER_XEVENT event(NULL);

  event.SetOperationPercent(42.5f);
  EXPECT_FLOAT_EQ(42.5f, event.GetOperationPercent());
}


TEST(UNITTESTS_XDRIVEIMAGEMANAGER_XEVENT_CLASSNAME, ErrorDefaultsToNoneAndRoundTrips)
{
  XDRIVEIMAGEMANAGER_XEVENT event(NULL);

  EXPECT_EQ(XDRIVEIMAGEMANAGER_ERROR_NONE, event.GetError());

  event.SetError(XDRIVEIMAGEMANAGER_ERROR_WRITESECTORS);
  EXPECT_EQ(XDRIVEIMAGEMANAGER_ERROR_WRITESECTORS, event.GetError());
}


}
#endif
