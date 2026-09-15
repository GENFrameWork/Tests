/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLanguageLua.cpp
* @brief      Unit tests for the Lua interpreter
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLanguageLua.h"
#include "UnitTests_Script_TestHelpers.h"

#ifdef SCRIPT_LUA_ACTIVE
#include "Script_Language_Lua.h"
#endif

#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_LUA_ACTIVE)
namespace TEST_SCRIPTLANGUAGELUA
{

static void UnitTests_ScriptLanguageLua_ReturnFloat(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(returnvalue) (*returnvalue) = 1.25f;
}


static void UnitTests_ScriptLanguageLua_ReturnDouble(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(returnvalue) (*returnvalue) = 2.75;
}


TEST(UNITTESTS_SCRIPTLANGUAGELUA_CLASSNAME, ExecutesNumericResult)
{
  SCRIPT_LNG_LUA script;
  int returnvalue = 0;

  (*script.GetScript()) = __L("return 42");
  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_NONE);
  EXPECT_EQ(returnvalue, 42);
}


TEST(UNITTESTS_SCRIPTLANGUAGELUA_CLASSNAME, ReportsSyntaxError)
{
  SCRIPT_LNG_LUA script;

  (*script.GetScript()) = __L("function main(");
  EXPECT_NE(script.Run(), SCRIPT_ERRORCODE_NONE);
}


TEST(UNITTESTS_SCRIPTLANGUAGELUA_CLASSNAME, ExecutesMainFunctionAfterLoadingChunk)
{
  SCRIPT_LNG_LUA script;
  int returnvalue = 0;

  (*script.GetScript()) = __L("function main()\n return 7\nend");
  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_NONE);
  EXPECT_EQ(returnvalue, 7);
}


TEST(UNITTESTS_SCRIPTLANGUAGELUA_CLASSNAME, DoesNotReuseMainFunctionBetweenRuns)
{
  SCRIPT_LNG_LUA script;
  int returnvalue = 0;

  (*script.GetScript()) = __L("function main()\n return 7\nend");
  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_NONE);
  EXPECT_EQ(returnvalue, 7);

  (*script.GetScript()) = __L("function main()\n return 9\nend");
  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_NONE);
  EXPECT_EQ(returnvalue, 9);

  (*script.GetScript()) = __L("return 3");
  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_NONE);
  EXPECT_EQ(returnvalue, 3);
}


TEST(UNITTESTS_SCRIPTLANGUAGELUA_CLASSNAME, NativeFloatAndDoubleReturnAsNumbers)
{
  SCRIPT_LNG_LUA script;
  SCRIPT_LIB library(__L("UnitTest"));
  int returnvalue = 0;

  ASSERT_TRUE(script.AddLibraryFunction(&library, __L("NativeFloat"), UnitTests_ScriptLanguageLua_ReturnFloat));
  ASSERT_TRUE(script.AddLibraryFunction(&library, __L("NativeDouble"), UnitTests_ScriptLanguageLua_ReturnDouble));

  (*script.GetScript()) = __L("return (NativeFloat() * 10) + (NativeDouble() * 10)");
  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_NONE);
  EXPECT_EQ(returnvalue, 40);
}


TEST(UNITTESTS_SCRIPTLANGUAGELUA_CLASSNAME, DoesNotExposeUnsafeStandardLibraries)
{
  SCRIPT_LNG_LUA script;
  int returnvalue = 0;

  (*script.GetScript()) = __L("if os == nil and io == nil and package == nil and debug == nil and dofile == nil and loadfile == nil and require == nil and module == nil then return 1 else return 0 end");
  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_NONE);
  EXPECT_EQ(returnvalue, 1);
}


TEST(UNITTESTS_SCRIPTLANGUAGELUA_CLASSNAME, DeniesUnsafeNativeLibrariesByDefault)
{
  SCRIPT_LNG_LUA script;
  int returnvalue = 0;

  (*script.GetScript()) = __L("return System_GetType()");
  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_CAPABILITY_DENIED);
}

}
#endif
