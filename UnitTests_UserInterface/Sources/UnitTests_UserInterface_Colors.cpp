/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_UserInterface_Colors.cpp
*
* @brief      UserInterface unit tests for UI_COLORS
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UnitTests_UserInterface_Colors.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "UI_Colors.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

#ifdef GOOGLETEST_ACTIVE
namespace TEST_UI_COLORS
{


TEST(UNITTESTS_UI_COLORS_CLASSNAME, AddThenGetReturnsTheRegisteredString)
{
  GEN_UI_COLORS.DeleteAll();

  ASSERT_TRUE(GEN_UI_COLORS.Add(__L("ut_red"), __L("255,0,0")));

  XSTRING* value = GEN_UI_COLORS.Get(__L("ut_red"));
  ASSERT_NE(value, (XSTRING*)NULL);
  EXPECT_EQ(value->Compare(__L("255,0,0"), true), 0);

  GEN_UI_COLORS.DeleteAll();
}


TEST(UNITTESTS_UI_COLORS_CLASSNAME, GetUnknownNameReturnsNull)
{
  GEN_UI_COLORS.DeleteAll();

  EXPECT_EQ(GEN_UI_COLORS.Get(__L("does_not_exist")), (XSTRING*)NULL);
}


TEST(UNITTESTS_UI_COLORS_CLASSNAME, DeleteAllClearsPreviousEntries)
{
  ASSERT_TRUE(GEN_UI_COLORS.Add(__L("ut_tmp"), __L("1,2,3")));
  ASSERT_NE(GEN_UI_COLORS.Get(__L("ut_tmp")), (XSTRING*)NULL);

  ASSERT_TRUE(GEN_UI_COLORS.DeleteAll());
  EXPECT_EQ(GEN_UI_COLORS.Get(__L("ut_tmp")), (XSTRING*)NULL);
}


} // namespace TEST_UI_COLORS
#endif // GOOGLETEST_ACTIVE
