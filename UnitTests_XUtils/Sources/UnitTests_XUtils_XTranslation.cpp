/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XTranslation.cpp
*
* @class      UNITTESTS_XUTILS_XTRANSLATION
* @brief      XUtils unit tests for XTranslation class
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

#include "UnitTests_XUtils_XTranslation.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XTranslation.h"
#include "XLanguage_ISO_639_3.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


// This application's own AppProc_Ini (UnitTests_XUtils.cpp) already calls GEN_XTRANSLATION.Ini(xpath)
// against assets/unittests_xutils.lng and GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_ENG)
// once, at process start-up, before any TEST body below ever runs. By the time these tests run,
// GEN_XTRANSLATION is therefore already a real, fully working, populated singleton - Pattern B
// (GetIsInstanced/GetInstance/DelInstance, no SetInstance - Meyer's singleton with a private ctor).
// Deliberately NOT exercised here: Ini()/End()/DelInstance(). Re-Ini()-ing would need to reconstruct
// the exact XPATH AppProc_Ini used and re-parses the real .lng file a second time, and End()/DelInstance()
// would wipe every sentence (including the ones XTRANSLATION_GEN pushed in) for the rest of this
// shared test binary - none of that is worth the risk when the already-initialized real state is
// exactly what this class is meant to be used as. This was confirmed safe by running the FULL suite
// (not just this file's filter) twice in a row after writing these tests - see Batch 10 notes.
#ifdef GOOGLETEST_ACTIVE
namespace TEST_XTRANSLATION
{


TEST(UNITTESTS_XTRANSLATION_CLASSNAME, GetInstanceCreatesAndReturnsSameReference)
{
  EXPECT_TRUE(XTRANSLATION::GetIsInstanced());

  XTRANSLATION& instance1 = XTRANSLATION::GetInstance();
  XTRANSLATION& instance2 = XTRANSLATION::GetInstance();
  EXPECT_EQ(&instance1, &instance2);
}


TEST(UNITTESTS_XTRANSLATION_CLASSNAME, GetActualReflectsTheLanguageAppProcIniAlreadySelected)
{
  EXPECT_EQ(GEN_XTRANSLATION.GetActual(), (XDWORD)XLANGUAGE_ISO_639_3_CODE_ENG);
}


TEST(UNITTESTS_XTRANSLATION_CLASSNAME, SetActualWithTheSameCurrentCodeIsRejected)
{
  // SetActual's very first check is "if(this->code == code) return false;" - re-selecting the
  // language that is already active is a no-op reported as failure, not success.
  EXPECT_EQ(GEN_XTRANSLATION.GetActual(), (XDWORD)XLANGUAGE_ISO_639_3_CODE_ENG);
  EXPECT_FALSE(GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_ENG));
  EXPECT_EQ(GEN_XTRANSLATION.GetActual(), (XDWORD)XLANGUAGE_ISO_639_3_CODE_ENG);
}


TEST(UNITTESTS_XTRANSLATION_CLASSNAME, SetActualWithAnUnavailableCodeIsRejectedAndLeavesActualUnchanged)
{
  // Neither this .lng file's "languages" array nor XTRANSLATION_GEN's built-in catalogue ever
  // registers this arbitrary made-up code, so SetActual must refuse it and leave the current
  // language untouched.
  EXPECT_FALSE(GEN_XTRANSLATION.SetActual((XDWORD)0xEFEFEFEF));
  EXPECT_EQ(GEN_XTRANSLATION.GetActual(), (XDWORD)XLANGUAGE_ISO_639_3_CODE_ENG);
}


TEST(UNITTESTS_XTRANSLATION_CLASSNAME, TranslateGetSentenceReturnsTheRealEnglishTextLoadedFromTheLNGFile)
{
  // assets/unittests_xutils.lng registers languages ["Spanish","English","French"] (indices 0,1,2)
  // and translation ID "00100" as [0, "hola radiola", "hi radiola", "jau radiola"] - with the
  // active language English (languageindex 1), Translate_Load() picks array slot languageindex+1=2.
  EXPECT_STREQ(GEN_XTRANSLATION.Translate_GetSentence(100), __L("hi radiola"));

  // ID "00101" is [70, "mas mensage", "more message", "jau radiola"] - same slot 2 -> English text.
  EXPECT_STREQ(GEN_XTRANSLATION.Translate_GetSentence(101), __L("more message"));
}


TEST(UNITTESTS_XTRANSLATION_CLASSNAME, TranslateGetSentenceOnAnUnregisteredIDFallsBackToTheEmptySentence)
{
  EXPECT_STREQ(GEN_XTRANSLATION.Translate_GetSentence(55555), __L("--"));
}


TEST(UNITTESTS_XTRANSLATION_CLASSNAME, TranslateGetSentenceAtOrBeyondTheArrayBoundFallsBackToTheEmptySentence)
{
  // Translate_GetSentence bounds-checks ID against XTRANSLATION_MAXSENTENCES before ever touching
  // the sentences[] array, so this is a safe, non-corrupting way to probe the boundary.
  EXPECT_STREQ(GEN_XTRANSLATION.Translate_GetSentence(XTRANSLATION_MAXSENTENCES), __L("--"));
  EXPECT_STREQ(GEN_XTRANSLATION.Translate_GetSentence(XTRANSLATION_MAXSENTENCES + 1000), __L("--"));
}


TEST(UNITTESTS_XTRANSLATION_CLASSNAME, TranslateAddAndGetSentenceRoundTripOnAFreshUnusedID)
{
  // A high, otherwise-unused ID: it does not collide with the .lng file's IDs (100/101) nor with
  // any of XTRANSLATION_GEN's small enum-valued IDs, so this cannot disturb any other test's
  // expectations about the real, shared GEN_XTRANSLATION content.
  //
  // Deliberately NOT asserted here: that Translate_GetSentence(freshID) starts out as "--". Under a
  // single plain run of this suite that precondition holds (nothing else ever registers this ID),
  // but GEN_XTRANSLATION is a persistent process-global singleton with no reset between gtest
  // iterations - under --gtest_repeat this same TEST body runs more than once against the SAME
  // singleton, so by the second iteration this ID is already registered by the first. Asserting only
  // the add+get round trip (not the "was never registered before" precondition) keeps this test
  // correct and idempotent regardless of how many times it runs.
  const XDWORD freshID = 9500;

  EXPECT_TRUE(GEN_XTRANSLATION.Translate_Add(freshID, __L("Fresh unit test sentence"), 0));
  EXPECT_STREQ(GEN_XTRANSLATION.Translate_GetSentence(freshID), __L("Fresh unit test sentence"));
}


TEST(UNITTESTS_XTRANSLATION_CLASSNAME, TranslateAddTruncatesToTheFixedLengthWhenGiven)
{
  const XDWORD freshID = 9501;

  EXPECT_TRUE(GEN_XTRANSLATION.Translate_Add(freshID, __L("HelloWorldThisIsLong"), 5));
  EXPECT_STREQ(GEN_XTRANSLATION.Translate_GetSentence(freshID), __L("Hello"));
}


TEST(UNITTESTS_XTRANSLATION_CLASSNAME, TranslateAddRejectsZeroIDOrNullSentence)
{
  EXPECT_FALSE(GEN_XTRANSLATION.Translate_Add(0, __L("text"), 0));
  EXPECT_FALSE(GEN_XTRANSLATION.Translate_Add(9502, NULL, 0));
}


// Source concern (not fixed, not exercised): Translate_Add(XDWORD ID, XCHAR* sentence, XDWORD fixed)
// (XTranslation.cpp lines 213-234) writes "sentences[ID] = newsentence;" with NO upper-bound check
// of ID against XTRANSLATION_MAXSENTENCES (unlike Translate_GetSentence, which does check before
// reading). Calling Translate_Add with an ID >= XTRANSLATION_MAXSENTENCES (10000 on this desktop
// build) would write past the end of the fixed-size "XCHAR* sentences[XTRANSLATION_MAXSENTENCES]"
// array - a real out-of-bounds write. This is deliberately NOT exercised by any test here: doing so
// would corrupt this shared test binary's heap/adjacent members rather than fail cleanly, which is
// exactly the kind of unsafe repro the task brief asks us to avoid triggering.


}
#endif

