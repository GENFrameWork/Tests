/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_UserInterface_Property_Editable.cpp
*
* @brief      UserInterface unit tests for UI_PROPERTY_EDITABLE
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UnitTests_UserInterface_Property_Editable.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "UI_Property_Editable.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

#ifdef GOOGLETEST_ACTIVE
namespace TEST_UI_PROPERTY_EDITABLE
{


TEST(UNITTESTS_UI_PROPERTY_EDITABLE_CLASSNAME, DefaultsCursorAndMaxSizeToZero)
{
  UI_PROPERTY_EDITABLE property;

  EXPECT_EQ(property.Cursor_GetPosition(), 0);
  EXPECT_EQ(property.GetMaxSize(), 0);
}


TEST(UNITTESTS_UI_PROPERTY_EDITABLE_CLASSNAME, CursorAndMaxSizeRoundTrip)
{
  UI_PROPERTY_EDITABLE property;

  property.Cursor_SetPosition(7);
  property.SetMaxSize(128);

  EXPECT_EQ(property.Cursor_GetPosition(), 7);
  EXPECT_EQ(property.GetMaxSize(), 128);
}


} // namespace TEST_UI_PROPERTY_EDITABLE
#endif // GOOGLETEST_ACTIVE
