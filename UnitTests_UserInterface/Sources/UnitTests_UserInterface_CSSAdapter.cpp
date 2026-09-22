/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_UserInterface_CSSAdapter.cpp
*
* @brief      UserInterface unit tests for UI_CSSAdapter helpers
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UnitTests_UserInterface_CSSAdapter.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "UI_CSSAdapter.h"
#include "UI_Element.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

#ifdef GOOGLETEST_ACTIVE
namespace TEST_UI_CSSADAPTER
{


TEST(UNITTESTS_UI_CSSADAPTER_CLASSNAME, GetOnNullElementReturnsZeroBox)
{
  UI_CSSBOX box = UI_CSSBox_Get(NULL);

  EXPECT_EQ(box.left, 0.0);
  EXPECT_EQ(box.top, 0.0);
  EXPECT_EQ(box.width, 0.0);
  EXPECT_EQ(box.height, 0.0);
}


TEST(UNITTESTS_UI_CSSADAPTER_CLASSNAME, SetThenGetRoundTripsCssTopLeftBox)
{
  UI_ELEMENT element;

  UI_CSSBOX input;
  input.left = 100.0;
  input.top = 50.0;
  input.width = 200.0;
  input.height = 80.0;

  UI_CSSBox_Set(&element, input);

  // Internal Y stores the BOTTOM edge (top + height).
  EXPECT_EQ(element.GetBoundaryLine()->width, 200.0);
  EXPECT_EQ(element.GetBoundaryLine()->height, 80.0);
  EXPECT_EQ(element.GetLeftX(), 100.0);
  EXPECT_EQ(element.GetTopY(), 50.0);

  UI_CSSBOX output = UI_CSSBox_Get(&element);
  EXPECT_EQ(output.left, 100.0);
  EXPECT_EQ(output.top, 50.0);
  EXPECT_EQ(output.width, 200.0);
  EXPECT_EQ(output.height, 80.0);
}


TEST(UNITTESTS_UI_CSSADAPTER_CLASSNAME, SetOnNullElementIsNoOp)
{
  UI_CSSBOX box = { 1.0, 2.0, 3.0, 4.0 };
  UI_CSSBox_Set(NULL, box);   // must not crash
}


} // namespace TEST_UI_CSSADAPTER
#endif // GOOGLETEST_ACTIVE
