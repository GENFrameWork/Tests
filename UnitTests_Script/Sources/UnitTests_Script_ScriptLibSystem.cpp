/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibSystem.cpp
* @brief      Unit tests for SCRIPT_LIB_SYSTEM
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibSystem.h"
#include "UnitTests_Script_TestHelpers.h"
#ifdef SCRIPT_LIB_SYSTEM_ACTIVE
#include "Script_Lib_System.h"
#endif
#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_LIB_SYSTEM_ACTIVE)
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBSYSTEM, UNITTESTS_SCRIPTLIBSYSTEM_CLASSNAME, SCRIPT_LIB_SYSTEM, SCRIPT_LIB_SYSTEM_NAME, __L("System_GetType"))
UNITTESTS_SCRIPT_LIBRARY_CAPABILITY_TEST(TEST_SCRIPTLIBSYSTEM, UNITTESTS_SCRIPTLIBSYSTEM_CLASSNAME, SCRIPT_LIB_SYSTEM, __L("System_GetType"), SCRIPT_CAPABILITY_SYSTEM)
#endif
