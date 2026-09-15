/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibString.cpp
* @brief      Unit tests for SCRIPT_LIB_STRING
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibString.h"
#include "UnitTests_Script_TestHelpers.h"
#include "Script_Lib_String.h"
#include "GEN_Control.h"

#ifdef GOOGLETEST_ACTIVE
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBSTRING, UNITTESTS_SCRIPTLIBSTRING_CLASSNAME, SCRIPT_LIB_STRING, SCRIPT_LIB_NAME_STRING, __L("SPrintf"))

namespace TEST_SCRIPTLIBSTRING
{
TEST(UNITTESTS_SCRIPTLIBSTRING_CLASSNAME, SPrintfPreservesPercentInData)
{
  SCRIPT script;
  SCRIPT_LIB_STRING library;
  XVARIANT destination(__L(""));
  XVARIANT mask(__L("%s"));
  XVARIANT data(__L("100% ready"));
  XVARIANT result;
  XVECTOR<XVARIANT*> params;
  XSTRING text;

  params.Add(&destination);
  params.Add(&mask);
  params.Add(&data);
  Call_SPrintf(&library, &script, &params, &result);
  EXPECT_TRUE(result.ToString(text));
  EXPECT_EQ(text.Compare(__L("100% ready")), 0);
}
}
#endif
