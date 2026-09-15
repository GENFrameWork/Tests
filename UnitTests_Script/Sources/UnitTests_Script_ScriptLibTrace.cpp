/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibTrace.cpp
* @brief      Unit tests for SCRIPT_LIB_TRACE
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibTrace.h"
#include "UnitTests_Script_TestHelpers.h"
#include "Script_Lib_Trace.h"
#include "GEN_Control.h"

#ifdef GOOGLETEST_ACTIVE
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBTRACE, UNITTESTS_SCRIPTLIBTRACE_CLASSNAME, SCRIPT_LIB_TRACE, SCRIPT_LIB_NAME_TRACE, __L("TracePrintColor"))

TEST(UNITTESTS_SCRIPTLIBTRACE_CLASSNAME, PrintColorRejectsMissingMask)
{
  SCRIPT_LIB_TRACE               library;
  UNITTESTS_SCRIPT_ERRORCAPTURE  script;
  XVECTOR<XVARIANT*>             params;
  XVARIANT                       color(1);
  XVARIANT                       result;

  params.Add(&color);
  Call_TracePrintColor(&library, &script, &params, &result);

  EXPECT_EQ(script.GetLastError(), SCRIPT_ERRORCODE_INSUF_PARAMS);

  params.DeleteAll();
}


TEST(UNITTESTS_SCRIPTLIBTRACE_CLASSNAME, ClearScreenAcceptsItsSingleArgument)
{
  SCRIPT_LIB_TRACE               library;
  UNITTESTS_SCRIPT_ERRORCAPTURE  script;
  XVECTOR<XVARIANT*>             params;
  XVARIANT                       recursive(false);
  XVARIANT                       result;

  params.Add(&recursive);
  Call_TraceClearScreen(&library, &script, &params, &result);

  EXPECT_EQ(script.GetLastError(), SCRIPT_ERRORCODE_NONE);

  params.DeleteAll();
}
#endif
