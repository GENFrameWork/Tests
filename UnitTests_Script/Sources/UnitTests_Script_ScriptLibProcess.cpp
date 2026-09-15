/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibProcess.cpp
* @brief      Unit tests for SCRIPT_LIB_PROCESS
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibProcess.h"
#include "UnitTests_Script_TestHelpers.h"
#ifdef SCRIPT_LIB_PROCESS_ACTIVE
#include "Script_Lib_Process.h"
#endif
#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_LIB_PROCESS_ACTIVE)
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBPROCESS, UNITTESTS_SCRIPTLIBPROCESS_CLASSNAME, SCRIPT_LIB_PROCESS, SCRIPT_LIB_NAME_PROCESS, __L("OpenURL"))
UNITTESTS_SCRIPT_LIBRARY_CAPABILITY_TEST(TEST_SCRIPTLIBPROCESS, UNITTESTS_SCRIPTLIBPROCESS_CLASSNAME, SCRIPT_LIB_PROCESS, __L("OpenURL"), SCRIPT_CAPABILITY_PROCESS)
#endif
