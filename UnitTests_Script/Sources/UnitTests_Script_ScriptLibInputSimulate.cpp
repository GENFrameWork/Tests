/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibInputSimulate.cpp
* @brief      Unit tests for SCRIPT_LIB_INPUTSIMULATE
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibInputSimulate.h"
#include "UnitTests_Script_TestHelpers.h"
#ifdef SCRIPT_LIB_INPUTSIMULATE_ACTIVE
#include "Script_Lib_InputSimulate.h"
#endif
#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_LIB_INPUTSIMULATE_ACTIVE)
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBINPUTSIMULATE, UNITTESTS_SCRIPTLIBINPUTSIMULATE_CLASSNAME, SCRIPT_LIB_INPUTSIMULATE, SCRIPT_LIB_NAME_INPUTSIMULATE, __L("InpSim_Key_Press"))
UNITTESTS_SCRIPT_LIBRARY_CAPABILITY_TEST(TEST_SCRIPTLIBINPUTSIMULATE, UNITTESTS_SCRIPTLIBINPUTSIMULATE_CLASSNAME, SCRIPT_LIB_INPUTSIMULATE, __L("InpSim_Key_Press"), SCRIPT_CAPABILITY_INPUT_SIMULATE)

TEST(UNITTESTS_SCRIPTLIBINPUTSIMULATE_CLASSNAME, TwoArgumentFunctionsRejectOneArgument)
{
  SCRIPT_LIB_INPUTSIMULATE       library;
  UNITTESTS_SCRIPT_ERRORCAPTURE  script;
  XVECTOR<XVARIANT*>             params;
  XVARIANT                       value(1);
  XVARIANT                       result;

  params.Add(&value);

  Call_Key_Click(&library, &script, &params, &result);
  EXPECT_EQ(script.GetLastError(), SCRIPT_ERRORCODE_INSUF_PARAMS);

  script.ResetLastError();
  Call_Key_ClickByLiteral(&library, &script, &params, &result);
  EXPECT_EQ(script.GetLastError(), SCRIPT_ERRORCODE_INSUF_PARAMS);

  script.ResetLastError();
  Call_Key_ClickByText(&library, &script, &params, &result);
  EXPECT_EQ(script.GetLastError(), SCRIPT_ERRORCODE_INSUF_PARAMS);

  params.DeleteAll();
}
#endif
