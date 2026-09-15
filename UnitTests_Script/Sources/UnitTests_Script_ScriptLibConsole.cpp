/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibConsole.cpp
* @brief      Unit tests for SCRIPT_LIB_CONSOLE
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibConsole.h"
#include "UnitTests_Script_TestHelpers.h"
#ifdef SCRIPT_LIB_CONSOLE_ACTIVE
#include "Script_Lib_Console.h"
#endif
#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_LIB_CONSOLE_ACTIVE)
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBCONSOLE, UNITTESTS_SCRIPTLIBCONSOLE_CLASSNAME, SCRIPT_LIB_CONSOLE, SCRIPT_LIB_NAME_CONSOLE, __L("Console_Printf"))
#endif
