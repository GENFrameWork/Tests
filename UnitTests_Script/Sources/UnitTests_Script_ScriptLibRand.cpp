/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibRand.cpp
* @brief      Unit tests for SCRIPT_LIB_RAND
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibRand.h"
#include "UnitTests_Script_TestHelpers.h"
#include "Script_Lib_Rand.h"
#include "GEN_Control.h"

#ifdef GOOGLETEST_ACTIVE
UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(TEST_SCRIPTLIBRAND, UNITTESTS_SCRIPTLIBRAND_CLASSNAME, SCRIPT_LIB_RAND, SCRIPT_LIB_NAME_RANDOM, __L("RandBetween"))

namespace TEST_SCRIPTLIBRAND
{
TEST(UNITTESTS_SCRIPTLIBRAND_CLASSNAME, OwnsRandomGenerator)
{
  SCRIPT_LIB_RAND library;
  EXPECT_NE(library.GetXRand(), (XRAND*)NULL);
}
}
#endif
