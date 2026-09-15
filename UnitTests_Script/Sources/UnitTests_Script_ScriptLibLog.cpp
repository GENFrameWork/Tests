/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibLog.cpp
* @brief      Unit tests for SCRIPT_LIB_LOG
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibLog.h"
#include "UnitTests_Script_TestHelpers.h"
#ifdef SCRIPT_LIB_LOG_ACTIVE
#include "Script_Lib_Log.h"
#endif
#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_LIB_LOG_ACTIVE)
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBLOG, UNITTESTS_SCRIPTLIBLOG_CLASSNAME, SCRIPT_LIB_LOG, SCRIPT_LIB_NAME_LOG, __L("Log_AddEntry"))
#endif
