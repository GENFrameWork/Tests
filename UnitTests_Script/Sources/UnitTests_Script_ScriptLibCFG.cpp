/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibCFG.cpp
* @brief      Unit tests for SCRIPT_LIB_CFG
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibCFG.h"
#include "UnitTests_Script_TestHelpers.h"
#ifdef SCRIPT_LIB_CFG_ACTIVE
#include "Script_Lib_CFG.h"
#endif
#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_LIB_CFG_ACTIVE)
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBCFG, UNITTESTS_SCRIPTLIBCFG_CLASSNAME, SCRIPT_LIB_CFG, SCRIPT_LIB_NAME_CFG, __L("GetFileCFGValue"))

namespace TEST_SCRIPTLIBCFG
{
TEST(UNITTESTS_SCRIPTLIBCFG_CLASSNAME, StoresExternalConfiguration)
{
  SCRIPT_LIB_CFG library;
  EXPECT_EQ(library.GetXFileCFG(), (XFILECFG*)NULL);
  library.SetXFileCFG((XFILECFG*)0x1);
  EXPECT_EQ(library.GetXFileCFG(), (XFILECFG*)0x1);
}
}
#endif
