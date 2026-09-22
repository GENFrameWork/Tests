/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_UserInterface_Element.cpp
*
* @brief      UserInterface unit tests for UI_ELEMENT (core identity / visibility / tree)
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "UnitTests_UserInterface_Element.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "UI_Element.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/

#ifdef GOOGLETEST_ACTIVE
namespace TEST_UI_ELEMENT
{


TEST(UNITTESTS_UI_ELEMENT_CLASSNAME, DefaultTypeIsUnknownAndVisibleByDefault)
{
  UI_ELEMENT element;

  EXPECT_EQ(element.GetType(), UI_ELEMENT_TYPE_UNKNOWN);
  EXPECT_TRUE(element.IsVisible());
  EXPECT_EQ(element.GetFather(), (UI_ELEMENT*)NULL);
  ASSERT_NE(element.GetName(), (XSTRING*)NULL);
  EXPECT_TRUE(element.GetName()->IsEmpty());
}


TEST(UNITTESTS_UI_ELEMENT_CLASSNAME, SetTypeAndNameRoundTrip)
{
  UI_ELEMENT element;

  element.SetType(UI_ELEMENT_TYPE_BUTTON);
  element.GetName()->Set(__L("ok_button"));

  EXPECT_EQ(element.GetType(), UI_ELEMENT_TYPE_BUTTON);
  EXPECT_EQ(element.GetName()->Compare(__L("ok_button"), true), 0);
}


TEST(UNITTESTS_UI_ELEMENT_CLASSNAME, VisibilityToggleRoundTrips)
{
  UI_ELEMENT element;

  element.SetVisible(false);
  EXPECT_FALSE(element.IsVisible());
  element.SetVisible(true);
  EXPECT_TRUE(element.IsVisible());
}


TEST(UNITTESTS_UI_ELEMENT_CLASSNAME, ClassNamesParseAndHasClassMatchesTokens)
{
  UI_ELEMENT element;

  element.SetClassNames(__L("card flex-row primary"));
  EXPECT_TRUE(element.HasClass(__L("card")));
  EXPECT_TRUE(element.HasClass(__L("flex-row")));
  EXPECT_TRUE(element.HasClass(__L("primary")));
  EXPECT_FALSE(element.HasClass(__L("missing")));
}


TEST(UNITTESTS_UI_ELEMENT_CLASSNAME, FatherAndComposeTreeLinkWithoutOwningDuplicatesOnDeleteAll)
{
  UI_ELEMENT* parent = new UI_ELEMENT();
  UI_ELEMENT* child  = new UI_ELEMENT();

  parent->GetName()->Set(__L("parent"));
  child->GetName()->Set(__L("child"));

  child->SetFather(parent);
  parent->GetComposeElements()->Add(child);

  EXPECT_EQ(child->GetFather(), parent);
  ASSERT_EQ(parent->GetComposeElements()->GetSize(), 1);
  EXPECT_EQ(parent->GetComposeElements()->Get(0), child);

  // DeleteAllComposeElements owns and deletes the children.
  ASSERT_TRUE(parent->DeleteAllComposeElements());
  EXPECT_TRUE(parent->GetComposeElements()->IsEmpty());

  delete parent;
}


} // namespace TEST_UI_ELEMENT
#endif // GOOGLETEST_ACTIVE
