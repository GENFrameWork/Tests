/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_UserInterface_Color.cpp
*
* @brief      UserInterface unit tests for UI_COLOR
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UnitTests_UserInterface_Color.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "UI_Color.h"
#include "UI_Colors.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

#ifdef GOOGLETEST_ACTIVE
namespace TEST_UI_COLOR
{


TEST(UNITTESTS_UI_COLOR_CLASSNAME, DefaultConstructorIsInvalidWithZeroChannels)
{
  UI_COLOR color;

  EXPECT_FALSE(color.IsValid());
  EXPECT_EQ(color.GetRed(), 0);
  EXPECT_EQ(color.GetGreen(), 0);
  EXPECT_EQ(color.GetBlue(), 0);
  EXPECT_EQ(color.GetAlpha(), 0);
}


TEST(UNITTESTS_UI_COLOR_CLASSNAME, ParsesRgbTripleWithOpaqueAlpha)
{
  UI_COLOR color;

  ASSERT_TRUE(color.SetFromString(__L("10,20,30")));
  EXPECT_EQ(color.GetRed(), 10);
  EXPECT_EQ(color.GetGreen(), 20);
  EXPECT_EQ(color.GetBlue(), 30);
  EXPECT_EQ(color.GetAlpha(), 255);
}


TEST(UNITTESTS_UI_COLOR_CLASSNAME, ParsesRgbPlusPercentAlpha)
{
  UI_COLOR color;

  ASSERT_TRUE(color.SetFromString(__L("10,20,30,50")));
  EXPECT_EQ(color.GetRed(), 10);
  EXPECT_EQ(color.GetGreen(), 20);
  EXPECT_EQ(color.GetBlue(), 30);
  EXPECT_EQ(color.GetAlpha(), 127);   // (50 * 255) / 100
}


TEST(UNITTESTS_UI_COLOR_CLASSNAME, ParsesCssHexRgbAndDefaultsAlphaTo255)
{
  UI_COLOR color;

  ASSERT_TRUE(color.SetFromString(__L("#112233")));
  EXPECT_TRUE(color.IsValid());
  EXPECT_EQ(color.GetRed(), 0x11);
  EXPECT_EQ(color.GetGreen(), 0x22);
  EXPECT_EQ(color.GetBlue(), 0x33);
  EXPECT_EQ(color.GetAlpha(), 255);
}


TEST(UNITTESTS_UI_COLOR_CLASSNAME, ParsesCssHexRgba)
{
  UI_COLOR color;

  ASSERT_TRUE(color.SetFromString(__L("#11223344")));
  EXPECT_EQ(color.GetRed(), 0x11);
  EXPECT_EQ(color.GetGreen(), 0x22);
  EXPECT_EQ(color.GetBlue(), 0x33);
  EXPECT_EQ(color.GetAlpha(), 0x44);
}


TEST(UNITTESTS_UI_COLOR_CLASSNAME, RejectsEmptyAndMalformedHex)
{
  UI_COLOR color;

  EXPECT_FALSE(color.SetFromString(__L("")));
  EXPECT_FALSE(color.SetFromString(__L("#123")));
  EXPECT_FALSE(color.SetFromString((XCHAR*)NULL));
}


TEST(UNITTESTS_UI_COLOR_CLASSNAME, CopyFromAndCopyToRoundTrip)
{
  UI_COLOR source;
  UI_COLOR dest;

  ASSERT_TRUE(source.SetFromString(__L("1,2,3,100")));
  ASSERT_TRUE(dest.CopyFrom(&source));

  EXPECT_EQ(dest.GetRed(), source.GetRed());
  EXPECT_EQ(dest.GetGreen(), source.GetGreen());
  EXPECT_EQ(dest.GetBlue(), source.GetBlue());
  EXPECT_EQ(dest.GetAlpha(), source.GetAlpha());

  UI_COLOR again;
  ASSERT_TRUE(source.CopyTo(&again));
  EXPECT_EQ(again.GetRed(), 1);
  EXPECT_EQ(again.GetGreen(), 2);
  EXPECT_EQ(again.GetBlue(), 3);
}


TEST(UNITTESTS_UI_COLOR_CLASSNAME, CopyFromNullFails)
{
  UI_COLOR color;

  EXPECT_FALSE(color.CopyFrom(NULL));
  EXPECT_FALSE(color.CopyTo(NULL));
}


TEST(UNITTESTS_UI_COLOR_CLASSNAME, ResolvesNamedColorThroughUiColorsRegistry)
{
  ASSERT_TRUE(GEN_UI_COLORS.Add(__L("ut_brand"), __L("9,8,7")));

  UI_COLOR color;
  ASSERT_TRUE(color.SetFromString(__L("ut_brand")));
  EXPECT_EQ(color.GetRed(), 9);
  EXPECT_EQ(color.GetGreen(), 8);
  EXPECT_EQ(color.GetBlue(), 7);
  EXPECT_EQ(color.GetAlpha(), 255);

  GEN_UI_COLORS.DeleteAll();
}


} // namespace TEST_UI_COLOR
#endif // GOOGLETEST_ACTIVE
