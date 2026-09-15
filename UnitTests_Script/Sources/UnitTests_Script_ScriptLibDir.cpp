/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibDir.cpp
* @brief      Unit tests for SCRIPT_LIB_DIR
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibDir.h"
#include "UnitTests_Script_TestHelpers.h"
#include "Script_Lib_Dir.h"
#include "GEN_Control.h"

#ifdef GOOGLETEST_ACTIVE
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBDIR, UNITTESTS_SCRIPTLIBDIR_CLASSNAME, SCRIPT_LIB_DIR, SCRIPT_LIB_NAME_DIR, __L("IsItExists"))

namespace TEST_SCRIPTLIBDIR
{
TEST(UNITTESTS_SCRIPTLIBDIR_CLASSNAME, WriteOperationsRespectCapability)
{
  SCRIPT script;
  SCRIPT_LIB_DIR library;
  ASSERT_TRUE(library.AddLibraryFunctions(&script));
  ASSERT_TRUE(script.SetCapabilities(SCRIPT_CAPABILITY_NONE));
  EXPECT_NE(script.GetLibraryFunction(__L("IsItExists")), (SCRIPT_LIB_FUNCTION*)NULL);
  EXPECT_EQ(script.GetLibraryFunction(__L("MakeDir")), (SCRIPT_LIB_FUNCTION*)NULL);
  EXPECT_TRUE(script.EnableCapabilities(SCRIPT_CAPABILITY_FILESYSTEM_WRITE));
  EXPECT_NE(script.GetLibraryFunction(__L("MakeDir")), (SCRIPT_LIB_FUNCTION*)NULL);
}
}
#endif
