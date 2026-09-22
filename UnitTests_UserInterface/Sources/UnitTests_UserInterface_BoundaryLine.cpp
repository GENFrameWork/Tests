/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_UserInterface_BoundaryLine.cpp
*
* @brief      UserInterface unit tests for UI_BOUNDARYLINE
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UnitTests_UserInterface_BoundaryLine.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "UI_BoundaryLine.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

#ifdef GOOGLETEST_ACTIVE
namespace TEST_UI_BOUNDARYLINE
{


TEST(UNITTESTS_UI_BOUNDARYLINE_CLASSNAME, DefaultConstructorIsEmpty)
{
  UI_BOUNDARYLINE box;

  EXPECT_TRUE(box.IsEmpty());
  EXPECT_EQ(box.x, 0.0);
  EXPECT_EQ(box.y, 0.0);
  EXPECT_EQ(box.width, 0.0);
  EXPECT_EQ(box.height, 0.0);
}


TEST(UNITTESTS_UI_BOUNDARYLINE_CLASSNAME, EdgeHelpersUseBottomAnchoredYConvention)
{
  // Stored y is the BOTTOM edge; the box occupies [y-height, y].
  EXPECT_EQ(UI_BOUNDARYLINE_EdgeTop(100.0, 40.0), 60.0);
  EXPECT_EQ(UI_BOUNDARYLINE_EdgeBottom(100.0, 40.0), 100.0);
  EXPECT_EQ(UI_BOUNDARYLINE_EdgeLeft(10.0, 50.0), 10.0);
  EXPECT_EQ(UI_BOUNDARYLINE_EdgeRight(10.0, 50.0), 60.0);
}


TEST(UNITTESTS_UI_BOUNDARYLINE_CLASSNAME, AccessorsMatchEdgeHelpers)
{
  UI_BOUNDARYLINE box;
  box.x = 10.0;
  box.y = 100.0;
  box.width = 50.0;
  box.height = 40.0;

  EXPECT_EQ(box.GetLeft(), 10.0);
  EXPECT_EQ(box.GetRight(), 60.0);
  EXPECT_EQ(box.GetTop(), 60.0);
  EXPECT_EQ(box.GetBottom(), 100.0);
}


TEST(UNITTESTS_UI_BOUNDARYLINE_CLASSNAME, IsWithinAcceptsInteriorPointsAndRejectsEdgesOutsideHalfOpenRules)
{
  UI_BOUNDARYLINE box;
  box.x = 10.0;
  box.y = 100.0;      // bottom
  box.width = 50.0;
  box.height = 40.0;  // top = 60

  EXPECT_TRUE(box.IsWithin(10, 99));     // left inclusive, below bottom exclusive of bottom? ypos <= bottom && ypos > top
  EXPECT_TRUE(box.IsWithin(59, 61));
  EXPECT_FALSE(box.IsWithin(60, 80));    // right edge exclusive (xpos < GetRight())
  EXPECT_FALSE(box.IsWithin(30, 60));    // top edge exclusive (ypos > GetTop())
  EXPECT_FALSE(box.IsWithin(5, 80));
}


TEST(UNITTESTS_UI_BOUNDARYLINE_CLASSNAME, CopyFromAndCopyToRoundTrip)
{
  UI_BOUNDARYLINE source;
  source.x = 1.0;
  source.y = 2.0;
  source.width = 3.0;
  source.height = 4.0;

  UI_BOUNDARYLINE dest;
  dest.CopyFrom(source);

  EXPECT_EQ(dest.x, 1.0);
  EXPECT_EQ(dest.y, 2.0);
  EXPECT_EQ(dest.width, 3.0);
  EXPECT_EQ(dest.height, 4.0);

  UI_BOUNDARYLINE again;
  source.CopyTo(again);
  EXPECT_EQ(again.width, 3.0);
  EXPECT_EQ(again.height, 4.0);
}


TEST(UNITTESTS_UI_BOUNDARYLINE_CLASSNAME, SetAroundExpandsToUnionOfBothBoxes)
{
  UI_BOUNDARYLINE host;
  host.x = 50.0;
  host.y = 200.0;
  host.width = 20.0;
  host.height = 20.0;

  UI_BOUNDARYLINE other;
  other.x = 10.0;
  other.y = 220.0;
  other.width = 30.0;
  other.height = 40.0;

  ASSERT_TRUE(host.SetAround(other));

  EXPECT_EQ(host.GetLeft(), 10.0);
  EXPECT_EQ(host.GetBottom(), 220.0);
  EXPECT_GE(host.GetRight(), other.GetRight());
  EXPECT_LE(host.GetTop(), other.GetTop());
}


} // namespace TEST_UI_BOUNDARYLINE
#endif // GOOGLETEST_ACTIVE
