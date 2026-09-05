/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XLanguage_ISO_639_3.cpp
*
* @class      UNITTESTS_XUTILS_XLANGUAGE_ISO_639_3
* @brief      XUtils unit tests for XLanguage_ISO_639_3 class
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

#include "UnitTests_XUtils_XLanguage_ISO_639_3.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XLanguage_ISO_639_3.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XLANGUAGE_ISO_639_3
{


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, Code_GetByCodeAlpha3ResolvesKnownEntry)
{
  XLANGUAGE_ISO_639_3 languages;

  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_ENG, languages.Code_GetByCodeAlpha3(__L("eng")));
  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_SPA, languages.Code_GetByCodeAlpha3(__L("spa")));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, Code_GetByCodeAlpha2ResolvesKnownEntry)
{
  XLANGUAGE_ISO_639_3 languages;

  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_SPA, languages.Code_GetByCodeAlpha2(__L("es")));
  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_FRE, languages.Code_GetByCodeAlpha2(__L("fr")));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, Code_GetByEnglishNameResolvesKnownEntry)
{
  XLANGUAGE_ISO_639_3 languages;

  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_FRE, languages.Code_GetByEnglishName(__L("French")));
  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_DUT, languages.Code_GetByEnglishName(__L("Dutch")));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, Code_GetByAliasResolvesEitherAliasSlot)
{
  XLANGUAGE_ISO_639_3 languages;

  // "dut" entry has alias1name "Flemish" and empty alias2name
  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_DUT, languages.Code_GetByAlias(__L("Flemish")));

  // "chu" entry has alias1name "Old Slavonic" and alias2name "Church Slavonic"
  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_CHU, languages.Code_GetByAlias(__L("Old Slavonic")));
  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_CHU, languages.Code_GetByAlias(__L("Church Slavonic")));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, UnknownCodeAlpha3ReturnsInvalidCode)
{
  XLANGUAGE_ISO_639_3 languages;

  // Header/return-value contract: an unresolved lookup returns XLANGUAGE_ISO_639_3_CODE_INVALID (0),
  // never a null pointer or an exception -- the Code_Get* family always returns a plain XDWORD.
  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_INVALID, languages.Code_GetByCodeAlpha3(__L("xyz")));
  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_INVALID, languages.Code_GetByAlias(__L("Nonexistent")));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, CodeAlpha3LookupIsCaseSensitiveOnStoredData)
{
  // Data quirk, not a header contract violation: the "Armenia" row's alpha-3 code is stored as
  // uppercase "ARM" (XLanguage_ISO_639_3.cpp) while every other row is lowercase, and
  // Code_GetByCodeAlpha3()/XSTRING::Compare() default to a case-SENSITIVE comparison (ignorecase
  // defaults to false in XString.h). So the stored-case spelling resolves, but the natural
  // lowercase spelling used by every other alpha-3 code in this table does not.
  XLANGUAGE_ISO_639_3 languages;

  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_ARM, languages.Code_GetByCodeAlpha3(__L("ARM")));
  EXPECT_EQ((XDWORD)XLANGUAGE_ISO_639_3_CODE_INVALID, languages.Code_GetByCodeAlpha3(__L("arm")));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, CodeAlpha3_GetByCodeReturnsTrueAndFillsString)
{
  XLANGUAGE_ISO_639_3 languages;
  XSTRING codealpha3;

  EXPECT_TRUE(languages.CodeAlpha3_GetByCode(XLANGUAGE_ISO_639_3_CODE_ENG, codealpha3));
  EXPECT_STREQ(codealpha3.Get(), __L("eng"));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, CodeAlpha3_GetByCodeReturnsFalseAndEmptiesStringForUnknownCode)
{
  XLANGUAGE_ISO_639_3 languages;
  XSTRING codealpha3 = __L("previous value");

  EXPECT_FALSE(languages.CodeAlpha3_GetByCode((XDWORD)999999, codealpha3));
  EXPECT_STREQ(codealpha3.Get(), __L(""));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, CodeAlpha3_GetByCodeAlpha2ResolvesKnownEntry)
{
  XLANGUAGE_ISO_639_3 languages;
  XSTRING codealpha3;

  EXPECT_TRUE(languages.CodeAlpha3_GetByCodeAlpha2(__L("en"), codealpha3));
  EXPECT_STREQ(codealpha3.Get(), __L("eng"));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, CodeAlpha3_GetByAliasResolvesKnownAlias)
{
  XLANGUAGE_ISO_639_3 languages;
  XSTRING codealpha3;

  EXPECT_TRUE(languages.CodeAlpha3_GetByAlias(__L("Castilian"), codealpha3));
  EXPECT_STREQ(codealpha3.Get(), __L("spa"));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, EnglishName_GetByCodeResolvesKnownEntry)
{
  XLANGUAGE_ISO_639_3 languages;
  XSTRING englishname;

  EXPECT_TRUE(languages.EnglishName_GetByCode(XLANGUAGE_ISO_639_3_CODE_SPA, englishname));
  EXPECT_STREQ(englishname.Get(), __L("Spanish"));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, EnglishName_GetByCodeAlpha3ResolvesKnownEntry)
{
  XLANGUAGE_ISO_639_3 languages;
  XSTRING englishname;

  EXPECT_TRUE(languages.EnglishName_GetByCodeAlpha3(__L("jpn"), englishname));
  EXPECT_STREQ(englishname.Get(), __L("Japanese"));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, EnglishName_GetByCodeAlpha2ResolvesKnownEntry)
{
  XLANGUAGE_ISO_639_3 languages;
  XSTRING englishname;

  EXPECT_TRUE(languages.EnglishName_GetByCodeAlpha2(__L("de"), englishname));
  EXPECT_STREQ(englishname.Get(), __L("German"));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, EnglishName_GetByAliasResolvesKnownAlias)
{
  XLANGUAGE_ISO_639_3 languages;
  XSTRING englishname;

  EXPECT_TRUE(languages.EnglishName_GetByAlias(__L("Pashto"), englishname));
  EXPECT_STREQ(englishname.Get(), __L("Pushto"));
}


TEST(UNITTESTS_XLANGUAGE_ISO_639_3_CLASSNAME, EnglishName_GetByCodeReturnsFalseAndEmptiesStringForUnknownCode)
{
  XLANGUAGE_ISO_639_3 languages;
  XSTRING englishname = __L("previous value");

  EXPECT_FALSE(languages.EnglishName_GetByCode((XDWORD)999999, englishname));
  EXPECT_STREQ(englishname.Get(), __L(""));
}


}
#endif
