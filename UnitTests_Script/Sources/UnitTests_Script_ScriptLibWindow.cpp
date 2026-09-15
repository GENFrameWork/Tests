/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibWindow.cpp
* @brief      Unit tests for SCRIPT_LIB_WINDOW
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibWindow.h"
#include "UnitTests_Script_TestHelpers.h"
#ifdef SCRIPT_LIB_WINDOW_ACTIVE
#include "Script_Lib_Window.h"
#endif
#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_LIB_WINDOW_ACTIVE)
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBWINDOW, UNITTESTS_SCRIPTLIBWINDOW_CLASSNAME, SCRIPT_LIB_WINDOW, SCRIPT_LIB_NAME_WINDOW, __L("Window_GetPosX"))
UNITTESTS_SCRIPT_LIBRARY_CAPABILITY_TEST(TEST_SCRIPTLIBWINDOW, UNITTESTS_SCRIPTLIBWINDOW_CLASSNAME, SCRIPT_LIB_WINDOW, __L("Window_GetPosX"), SCRIPT_CAPABILITY_WINDOW)

namespace TEST_SCRIPTLIBWINDOW
{
TEST(UNITTESTS_SCRIPTLIBWINDOW_CLASSNAME, StoresBitmapSearchConfiguration)
{
  SCRIPT_LIB_WINDOW library;
  library.BmpFindCFG_SetDiffLimitPercent(9);
  library.BmpFindCFG_SetPixelMargin(4);
  EXPECT_EQ(library.BmpFindCFG_GetDiffLimitPercent(), (XBYTE)9);
  EXPECT_EQ(library.BmpFindCFG_GetPixelMargin(), (XBYTE)4);
}
}
#endif
