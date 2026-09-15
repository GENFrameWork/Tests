/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibMath.cpp
* @brief      Unit tests for SCRIPT_LIB_MATH
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibMath.h"
#include "UnitTests_Script_TestHelpers.h"
#include "Script_Lib_Math.h"
#include "GEN_Control.h"

#ifdef GOOGLETEST_ACTIVE
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBMATH, UNITTESTS_SCRIPTLIBMATH_CLASSNAME, SCRIPT_LIB_MATH, SCRIPT_LIB_MATH_NAME, __L("Abs"))

namespace TEST_SCRIPTLIBMATH
{
TEST(UNITTESTS_SCRIPTLIBMATH_CLASSNAME, AbsoluteValue)
{
  SCRIPT script;
  SCRIPT_LIB_MATH library;
  XVARIANT value(-17);
  XVARIANT result;
  XVECTOR<XVARIANT*> params;
  params.Add(&value);
  Call_Abs(&library, &script, &params, &result);
  EXPECT_EQ((int)result, 17);
}
}
#endif
