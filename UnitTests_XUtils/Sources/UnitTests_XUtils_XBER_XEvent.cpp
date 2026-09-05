/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XBER_XEvent.cpp
*
* @class      UNITTESTS_XUTILS_XBER_XEVENT
* @brief      XUtils unit tests for XBER_XEvent class
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

#include "UnitTests_XUtils_XBER_XEvent.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XBER_XEvent.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XBER_XEVENT
{

// XASN1_OID_PROPERTY is fully defined via XASN1.h (included by XBER_XEvent.h), but the event
// never dereferences the pointer it stores -- only Get/Set copy it -- so a fabricated non-null
// pointer is enough to exercise identity.
static XASN1_OID_PROPERTY* const FAKEPROPERTY = (XASN1_OID_PROPERTY*)0x1;


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, DefaultConstructorLeavesTypeAndFamilyAtZero)
{
  XBER_XEVENT event;

  EXPECT_EQ(event.GetEventType(), (XDWORD)0);
  EXPECT_EQ(event.GetEventFamily(), (XDWORD)0);
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, SubjectConstructorDefaultsTypeAndFamilyToBERFamily)
{
  XBER_XEVENT event(NULL);

  EXPECT_EQ(event.GetEventType(), (XDWORD)XBERXEVENT_TYPE_UNKNOWN);
  EXPECT_EQ(event.GetEventFamily(), (XDWORD)XEVENT_TYPE_XBER);
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, LevelDefaultsToZeroAndRoundTrips)
{
  XBER_XEVENT event(NULL);

  EXPECT_EQ(0, event.GetLevel());

  event.SetLevel(5);
  EXPECT_EQ(5, event.GetLevel());
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, GetLevelsReturnsZeroedArrayByDefault)
{
  XBER_XEVENT event(NULL);

  XDWORD* levels = event.GetLevels();

  ASSERT_NE((void*)NULL, (void*)levels);
  EXPECT_EQ((XDWORD)0, levels[0]);
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, GetLevelsStringReturnsUsableEmptyString)
{
  XBER_XEVENT event(NULL);

  XSTRING* levelsstr = event.GetLevelsString();

  ASSERT_NE((void*)NULL, (void*)levelsstr);
  EXPECT_STREQ(levelsstr->Get(), __L(""));

  *levelsstr = __L("1.2.3");
  EXPECT_STREQ(event.GetLevelsString()->Get(), __L("1.2.3"));
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, GetLineReturnsWritableString)
{
  XBER_XEVENT event(NULL);

  XSTRING* line = event.GetLine();

  ASSERT_NE((void*)NULL, (void*)line);

  *line = __L("SEQUENCE (constructed)");
  EXPECT_STREQ(event.GetLine()->Get(), __L("SEQUENCE (constructed)"));
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, GetDataReturnsWritableEmptyBuffer)
{
  XBER_XEVENT event(NULL);

  XBUFFER* data = event.GetData();

  ASSERT_NE((void*)NULL, (void*)data);
  EXPECT_EQ((XDWORD)0, data->GetSize());
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, TagTypeDefaultsToReservedAndRoundTrips)
{
  XBER_XEVENT event(NULL);

  EXPECT_EQ((XBYTE)XBER_TAGTYPE_RESERVEDBER, event.GetTagType());

  event.SetTagType(0x10);
  EXPECT_EQ((XBYTE)0x10, event.GetTagType());
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, GetTagTypeNameReturnsUsableEmptyString)
{
  XBER_XEVENT event(NULL);

  XSTRING* tagtypename = event.GetTagTypeName();

  ASSERT_NE((void*)NULL, (void*)tagtypename);
  EXPECT_STREQ(tagtypename->Get(), __L(""));
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, TagClassDefaultsToUnknownAndRoundTrips)
{
  XBER_XEVENT event(NULL);

  EXPECT_EQ(XBER_TAGCLASS_UNKNOWN, event.GetTagClass());

  event.SetTagClass(XBER_TAGCLASS_APPLICATION);
  EXPECT_EQ(XBER_TAGCLASS_APPLICATION, event.GetTagClass());
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, PropertyDefaultsToNullAndRoundTrips)
{
  XBER_XEVENT event(NULL);

  EXPECT_EQ((void*)NULL, (void*)event.GetProperty());

  event.SetProperty(FAKEPROPERTY);
  EXPECT_EQ((void*)FAKEPROPERTY, (void*)event.GetProperty());
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, GetValueReturnsUsableVariant)
{
  XBER_XEVENT event(NULL);

  XVARIANT* value = event.GetValue();

  ASSERT_NE((void*)NULL, (void*)value);

  *value = (XDWORD)77;
  EXPECT_EQ((XDWORD)77, (XDWORD)(*event.GetValue()));
}


TEST(UNITTESTS_XBER_XEVENT_CLASSNAME, StatusDefaultsToFalseAndRoundTrips)
{
  XBER_XEVENT event(NULL);

  EXPECT_FALSE(event.GetStatus());

  event.SetStatus(true);
  EXPECT_TRUE(event.GetStatus());
}


}
#endif
