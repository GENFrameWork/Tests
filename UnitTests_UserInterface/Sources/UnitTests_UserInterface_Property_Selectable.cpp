/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_UserInterface_Property_Selectable.cpp
*
* @brief      UserInterface unit tests for UI_PROPERTY_SELECTABLE
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UnitTests_UserInterface_Property_Selectable.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "UI_Property_Selectable.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

#ifdef GOOGLETEST_ACTIVE
namespace TEST_UI_PROPERTY_SELECTABLE
{


TEST(UNITTESTS_UI_PROPERTY_SELECTABLE_CLASSNAME, DefaultsToDeactiveWithDefaultSelectionTimeAndTimer)
{
  UI_PROPERTY_SELECTABLE property;

  EXPECT_EQ(property.GetSelectableState(), UI_PROPERTY_SELECTABLE_STATE_DEACTIVE);
  EXPECT_EQ(property.GetTimeSelected(), UI_PROPERTY_SELECTABLE_DEFAULT_TIMESELECTED);
  EXPECT_NE(property.GetXTimerSelected(), (XTIMER*)NULL);
}


TEST(UNITTESTS_UI_PROPERTY_SELECTABLE_CLASSNAME, SetSelectableStateRoundTrips)
{
  UI_PROPERTY_SELECTABLE property;

  ASSERT_TRUE(property.SetSelectableState(UI_PROPERTY_SELECTABLE_STATE_SELECTED));
  EXPECT_EQ(property.GetSelectableState(), UI_PROPERTY_SELECTABLE_STATE_SELECTED);
}


TEST(UNITTESTS_UI_PROPERTY_SELECTABLE_CLASSNAME, SetSelectableStateFromStringMapsKnownTokens)
{
  UI_PROPERTY_SELECTABLE property;

  EXPECT_EQ(property.SetSelectableStateFromString(__L("active")), UI_PROPERTY_SELECTABLE_STATE_ACTIVE);
  EXPECT_EQ(property.GetSelectableState(), UI_PROPERTY_SELECTABLE_STATE_ACTIVE);

  EXPECT_EQ(property.SetSelectableStateFromString(__L("preselect")), UI_PROPERTY_SELECTABLE_STATE_PRESELECT);
  EXPECT_EQ(property.SetSelectableStateFromString(__L("selected")), UI_PROPERTY_SELECTABLE_STATE_SELECTED);
  EXPECT_EQ(property.SetSelectableStateFromString(__L("deactive")), UI_PROPERTY_SELECTABLE_STATE_DEACTIVE);
}


TEST(UNITTESTS_UI_PROPERTY_SELECTABLE_CLASSNAME, SetSelectableStateFromStringFallsBackToDeactive)
{
  UI_PROPERTY_SELECTABLE property;

  EXPECT_EQ(property.SetSelectableStateFromString((XCHAR*)NULL), UI_PROPERTY_SELECTABLE_STATE_DEACTIVE);
  EXPECT_EQ(property.SetSelectableStateFromString(__L("not-a-state")), UI_PROPERTY_SELECTABLE_STATE_DEACTIVE);
}


TEST(UNITTESTS_UI_PROPERTY_SELECTABLE_CLASSNAME, TimeSelectedRoundTrips)
{
  UI_PROPERTY_SELECTABLE property;

  property.SetTimeSelected(250);
  EXPECT_EQ(property.GetTimeSelected(), 250);
}


} // namespace TEST_UI_PROPERTY_SELECTABLE
#endif // GOOGLETEST_ACTIVE
