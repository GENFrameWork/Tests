/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XFString.cpp
*
* @class      XUTILS_UNITTESTS_XFSTRING
* @brief      XUtils unit tests for XFString class
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

#include "XUtils_UnitTests_XFString.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XFString.h"
#include "XVector.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFSTRING
{

// These tests focus on what XFSTRING actually ADDS over XSTRING (which is already covered by
// XUtils_UnitTests_XString.cpp): the Fast_* accessors/mutators, Scan(), and Explode(). The
// assignment/relational operators XFSTRING re-declares just forward to XSTRING::Set/Add/Compare,
// so only a couple of sanity checks are included for those.


TEST(UNITTEST_XFSTRING_CLASSNAME, FastConvertToIntParsesLeadingInteger)
{
  XFSTRING string(__L("123abc"));

  EXPECT_EQ(string.Fast_ConvertToInt(), 123);
}


TEST(UNITTEST_XFSTRING_CLASSNAME, FastConvertToIntHonoursStartIndex)
{
  XFSTRING string(__L("ab42"));

  EXPECT_EQ(string.Fast_ConvertToInt(2), 42);
}


TEST(UNITTEST_XFSTRING_CLASSNAME, FastConvertToDWordParsesUnsigned)
{
  XFSTRING string(__L("4000000000"));

  EXPECT_EQ(string.Fast_ConvertToDWord(), (XDWORD)4000000000UL);
}


TEST(UNITTEST_XFSTRING_CLASSNAME, FastConvertToQWordParsesLargeValue)
{
  XFSTRING string(__L("123456789012"));

  EXPECT_EQ(string.Fast_ConvertToQWord(), (XQWORD)123456789012ULL);
}


TEST(UNITTEST_XFSTRING_CLASSNAME, FastConvertToSQWordParsesSignedValue)
{
  XFSTRING string(__L("-987654321"));

  EXPECT_EQ(string.Fast_ConvertToSQWord(), (XQWORDSIG)(-987654321LL));
}


TEST(UNITTEST_XFSTRING_CLASSNAME, FastConvertToFloatParsesDecimal)
{
  XFSTRING string(__L("3.5"));

  EXPECT_FLOAT_EQ(string.Fast_ConvertToFloat(), 3.5f);
}


TEST(UNITTEST_XFSTRING_CLASSNAME, FastConvertToDoubleParsesDecimal)
{
  XFSTRING string(__L("2.25"));

  EXPECT_DOUBLE_EQ(string.Fast_ConvertToDouble(), 2.25);
}


TEST(UNITTEST_XFSTRING_CLASSNAME, FastConvertOnNonNumericTextReturnsZero)
{
  XFSTRING string(__L("abc"));

  EXPECT_EQ(string.Fast_ConvertToInt(), 0);
}


TEST(UNITTEST_XFSTRING_CLASSNAME, FastAddCharacterOnEmptyStringGrowsToOneCharacter)
{
  XFSTRING string;

  EXPECT_TRUE(string.IsEmpty());
  EXPECT_TRUE(string.Fast_AddCharacter(L'A'));

  EXPECT_EQ(string.GetSize(), (XDWORD)1);
  EXPECT_EQ(string.Get()[0], L'A');
}


TEST(UNITTEST_XFSTRING_CLASSNAME, FastAddCharacterAppendsToExistingString)
{
  XFSTRING string(__L("ab"));

  EXPECT_TRUE(string.Fast_AddCharacter(L'c'));

  EXPECT_EQ(string.GetSize(), (XDWORD)3);
  EXPECT_EQ(0, string.Compare(__L("abc"), false));
}


TEST(UNITTEST_XFSTRING_CLASSNAME, FastEmptyClearsSizeButKeepsObjectUsable)
{
  XFSTRING string(__L("hello"));

  EXPECT_EQ(string.GetSize(), (XDWORD)5);
  EXPECT_TRUE(string.Fast_Empty());

  EXPECT_EQ(string.GetSize(), (XDWORD)0);
  EXPECT_TRUE(string.IsEmpty());
}


TEST(UNITTEST_XFSTRING_CLASSNAME, FastEmptyOnAlreadyEmptyStringSucceeds)
{
  XFSTRING string;

  EXPECT_TRUE(string.Fast_Empty());
  EXPECT_EQ(string.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XFSTRING_CLASSNAME, ScanParsesIntegerFromInternalBuffer)
{
  XFSTRING string(__L("77 rest"));

  int value = 0;
  EXPECT_EQ(string.Scan(__L("%d"), &value), 1);
  EXPECT_EQ(value, 77);
}


TEST(UNITTEST_XFSTRING_CLASSNAME, ScanReturnsZeroWhenMaskDoesNotMatch)
{
  XFSTRING string(__L("notanumber"));

  int value = 0;
  EXPECT_EQ(string.Scan(__L("%d"), &value), 0);
}


TEST(UNITTEST_XFSTRING_CLASSNAME, ExplodeSplitsOnTokenIntoOwnedFragments)
{
  XFSTRING string(__L("aa,bb,ccc"));
  XVECTOR<XFSTRING*> parts;

  EXPECT_TRUE(string.Explode(L',', &parts));

  ASSERT_EQ(parts.GetSize(), (XDWORD)3);
  EXPECT_EQ(0, parts.Get(0)->Compare(__L("aa"), false));
  EXPECT_EQ(0, parts.Get(1)->Compare(__L("bb"), false));
  EXPECT_EQ(0, parts.Get(2)->Compare(__L("ccc"), false));

  for(XDWORD c = 0; c < parts.GetSize(); c++) { GEN_DELETE parts.Get(c); }
  parts.DeleteAll();
}


TEST(UNITTEST_XFSTRING_CLASSNAME, ExplodeSkipsEmptyFieldsBetweenConsecutiveTokens)
{
  // Explode only Add()s a fragment when (end-start)>0, so back-to-back tokens ("a,,b")
  // produce just the non-empty fragments, not an empty string in between.
  XFSTRING string(__L("a,,b"));
  XVECTOR<XFSTRING*> parts;

  EXPECT_TRUE(string.Explode(L',', &parts));

  ASSERT_EQ(parts.GetSize(), (XDWORD)2);
  EXPECT_EQ(0, parts.Get(0)->Compare(__L("a"), false));
  EXPECT_EQ(0, parts.Get(1)->Compare(__L("b"), false));

  for(XDWORD c = 0; c < parts.GetSize(); c++) { GEN_DELETE parts.Get(c); }
  parts.DeleteAll();
}


TEST(UNITTEST_XFSTRING_CLASSNAME, ExplodeWithNoTokenPresentReturnsWholeStringAsOneFragment)
{
  XFSTRING string(__L("noseparatorhere"));
  XVECTOR<XFSTRING*> parts;

  EXPECT_TRUE(string.Explode(L',', &parts));

  ASSERT_EQ(parts.GetSize(), (XDWORD)1);
  EXPECT_EQ(0, parts.Get(0)->Compare(__L("noseparatorhere"), false));

  for(XDWORD c = 0; c < parts.GetSize(); c++) { GEN_DELETE parts.Get(c); }
  parts.DeleteAll();
}


TEST(UNITTEST_XFSTRING_CLASSNAME, AssignmentOperatorFromCharSetsContent)
{
  XFSTRING string;

  string = "hello";

  EXPECT_EQ(0, string.Compare(__L("hello"), false));
}


TEST(UNITTEST_XFSTRING_CLASSNAME, AppendOperatorFromXCharAppendsCharacter)
{
  XFSTRING string(__L("ab"));

  string += L'c';

  EXPECT_EQ(0, string.Compare(__L("abc"), false));
}


TEST(UNITTEST_XFSTRING_CLASSNAME, RelationalOperatorsMatchCompareResult)
{
  XFSTRING lower(__L("apple"));
  XFSTRING upper(__L("banana"));

  EXPECT_TRUE(lower < upper);
  EXPECT_TRUE(upper > lower);
  EXPECT_TRUE(lower <= upper);
  EXPECT_FALSE(lower == upper);
  EXPECT_TRUE(lower != upper);
}


TEST(UNITTEST_XFSTRING_CLASSNAME, IndexOperatorReturnsCharacterAtPosition)
{
  XFSTRING string(__L("xyz"));

  EXPECT_EQ(string[0], L'x');
  EXPECT_EQ(string[2], L'z');
}


}
#endif
