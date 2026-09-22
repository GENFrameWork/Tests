/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_UserInterface_Text.cpp
*
* @brief      UserInterface unit tests for UI_TEXT
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UnitTests_UserInterface_Text.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "UI_Text.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

#ifdef GOOGLETEST_ACTIVE
namespace TEST_UI_TEXT
{


TEST(UNITTESTS_UI_TEXT_CLASSNAME, DefaultNameAndTextAreEmpty)
{
  UI_TEXT text;

  ASSERT_NE(text.GetName(), (XSTRING*)NULL);
  ASSERT_NE(text.GetText(), (XSTRING*)NULL);
  EXPECT_TRUE(text.GetName()->IsEmpty());
  EXPECT_TRUE(text.GetText()->IsEmpty());
}


TEST(UNITTESTS_UI_TEXT_CLASSNAME, NameAndTextRoundTripThroughSetters)
{
  UI_TEXT text;

  text.GetName()->Set(__L("caption"));
  text.GetText()->Set(__L("Hello UI"));

  EXPECT_EQ(text.GetName()->Compare(__L("caption"), true), 0);
  EXPECT_EQ(text.GetText()->Compare(__L("Hello UI"), true), 0);
}


} // namespace TEST_UI_TEXT
#endif // GOOGLETEST_ACTIVE
