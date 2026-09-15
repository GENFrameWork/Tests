/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLanguageJavascript.cpp
* @brief      Unit tests for the JavaScript interpreter
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLanguageJavascript.h"
#include "UnitTests_Script_TestHelpers.h"

#ifdef SCRIPT_JAVASCRIPT_ACTIVE
#include "Script_Language_Javascript.h"
#endif

#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_JAVASCRIPT_ACTIVE)
namespace TEST_SCRIPTLANGUAGEJAVASCRIPT
{

static void UnitTests_ScriptLanguageJavascript_ReturnFloat(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(returnvalue) (*returnvalue) = 1.25f;
}


static void UnitTests_ScriptLanguageJavascript_ReturnDouble(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(returnvalue) (*returnvalue) = 2.75;
}


TEST(UNITTESTS_SCRIPTLANGUAGEJAVASCRIPT_CLASSNAME, ExecutesNumericResult)
{
  SCRIPT_LNG_JAVASCRIPT script;
  int returnvalue = 0;

  (*script.GetScript()) = __L("42");
  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_NONE);
  EXPECT_EQ(returnvalue, 42);
}


TEST(UNITTESTS_SCRIPTLANGUAGEJAVASCRIPT_CLASSNAME, RejectsNonNumericResult)
{
  SCRIPT_LNG_JAVASCRIPT script;
  int returnvalue = 0;

  (*script.GetScript()) = __L("'not numeric'");
  EXPECT_NE(script.Run(&returnvalue), SCRIPT_ERRORCODE_NONE);
}


TEST(UNITTESTS_SCRIPTLANGUAGEJAVASCRIPT_CLASSNAME, NativeFloatAndDoubleReturnAsNumbers)
{
  SCRIPT_LNG_JAVASCRIPT script;
  SCRIPT_LIB library(__L("UnitTest"));
  int returnvalue = 0;

  ASSERT_TRUE(script.AddLibraryFunction(&library, __L("NativeFloat"), UnitTests_ScriptLanguageJavascript_ReturnFloat));
  ASSERT_TRUE(script.AddLibraryFunction(&library, __L("NativeDouble"), UnitTests_ScriptLanguageJavascript_ReturnDouble));

  (*script.GetScript()) = __L("(NativeFloat() * 10) + (NativeDouble() * 10)");
  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_NONE);
  EXPECT_EQ(returnvalue, 40);
}


TEST(UNITTESTS_SCRIPTLANGUAGEJAVASCRIPT_CLASSNAME, DeniesUnsafeNativeLibrariesByDefault)
{
  SCRIPT_LNG_JAVASCRIPT script;
  int returnvalue = 0;

  (*script.GetScript()) = __L("System_GetType()");
  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_CAPABILITY_DENIED);
}

}
#endif
