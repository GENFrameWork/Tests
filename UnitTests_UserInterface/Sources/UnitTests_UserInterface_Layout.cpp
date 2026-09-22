/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_UserInterface_Layout.cpp
*
* @brief      UserInterface unit tests for UI_LAYOUT
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UnitTests_UserInterface_Layout.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "UI_Layout.h"
#include "UI_Element.h"
#include "UI_StyleSheet.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

#ifdef GOOGLETEST_ACTIVE
namespace TEST_UI_LAYOUT
{


TEST(UNITTESTS_UI_LAYOUT_CLASSNAME, ConstructsWithNullSkinWhenOwnershipDisabled)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  EXPECT_EQ(layout.GetSkin(), (UI_SKIN*)NULL);
  ASSERT_NE(layout.GetNameID(), (XSTRING*)NULL);
  EXPECT_EQ(layout.GetStyleSheet(), (UI_STYLESHEET*)NULL);
  ASSERT_NE(layout.Elements_Get(), (XVECTOR<UI_ELEMENT*>*)NULL);
  EXPECT_TRUE(layout.Elements_Get()->IsEmpty());
}


TEST(UNITTESTS_UI_LAYOUT_CLASSNAME, ElementsAddRejectsNullAndStoresLookupByName)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  EXPECT_FALSE(layout.Elements_Add(NULL));

  UI_ELEMENT* button = new UI_ELEMENT();
  button->SetType(UI_ELEMENT_TYPE_BUTTON);
  button->GetName()->Set(__L("save"));

  ASSERT_TRUE(layout.Elements_Add(button));
  ASSERT_EQ(layout.Elements_Get()->GetSize(), 1);

  UI_ELEMENT* found = layout.Elements_Get(__L("save"));
  ASSERT_NE(found, (UI_ELEMENT*)NULL);
  EXPECT_EQ(found, button);

  UI_ELEMENT* typed = layout.Elements_Get(__L("save"), UI_ELEMENT_TYPE_BUTTON);
  EXPECT_EQ(typed, button);

  EXPECT_EQ(layout.Elements_Get(__L("save"), UI_ELEMENT_TYPE_TEXT), (UI_ELEMENT*)NULL);
  EXPECT_EQ(layout.Elements_Get(__L("missing")), (UI_ELEMENT*)NULL);

  // Destructor / Elements_DeleteAll owns the element pointers.
}


TEST(UNITTESTS_UI_LAYOUT_CLASSNAME, StyleSheetReplaceDeletesPreviousOwnedInstance)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  UI_STYLESHEET* first = new UI_STYLESHEET();
  layout.SetStyleSheet(first);
  EXPECT_EQ(layout.GetStyleSheet(), first);

  UI_STYLESHEET* second = new UI_STYLESHEET();
  layout.SetStyleSheet(second);
  EXPECT_EQ(layout.GetStyleSheet(), second);
}


TEST(UNITTESTS_UI_LAYOUT_CLASSNAME, NameIdRoundTrips)
{
  UI_LAYOUT layout(NULL);
  layout.SetOwnsSkin(false);

  layout.GetNameID()->Set(__L("dashboard"));
  EXPECT_EQ(layout.GetNameID()->Compare(__L("dashboard"), true), 0);
}


} // namespace TEST_UI_LAYOUT
#endif // GOOGLETEST_ACTIVE
