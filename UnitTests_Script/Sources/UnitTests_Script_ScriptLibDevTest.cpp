/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibDevTest.cpp
* @brief      Unit tests for SCRIPT_LIB_DEVTEST
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibDevTest.h"
#include "UnitTests_Script_TestHelpers.h"
#ifdef SCRIPT_LIB_DEVTEST_ACTIVE
#include "Script_Lib_DevTest.h"
#endif
#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_LIB_DEVTEST_ACTIVE)
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBDEVTEST, UNITTESTS_SCRIPTLIBDEVTEST_CLASSNAME, SCRIPT_LIB_DEVTEST, SCRIPT_LIB_NAME_DEVTEST, __L("DevTest_Func1"))

namespace TEST_SCRIPTLIBDEVTEST
{
TEST(UNITTESTS_SCRIPTLIBDEVTEST_CLASSNAME, ReturnsDevelopmentPayload)
{
  SCRIPT script;
  SCRIPT_LIB_DEVTEST library;
  XVECTOR<XVARIANT*> params;
  XVARIANT result;
  XSTRING text;

  Call_DevTest_Func1(&library, &script, &params, &result);
  EXPECT_TRUE(result.ToString(text));
  EXPECT_NE(text.Find(__L("Pepe"), false), XSTRING_NOTFOUND);
}
}
#endif
