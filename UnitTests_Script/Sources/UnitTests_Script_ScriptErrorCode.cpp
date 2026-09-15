/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptErrorCode.cpp
* @brief      Unit tests for Script error codes
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptErrorCode.h"
#include "gtest/gtest.h"
#include "Script_ErrorCode.h"
#include "GEN_Control.h"

#ifdef GOOGLETEST_ACTIVE
namespace TEST_SCRIPTERRORCODE
{

TEST(UNITTESTS_SCRIPTERRORCODE_CLASSNAME, CommonValuesRemainStable)
{
  EXPECT_EQ(SCRIPT_ERRORCODE_NONE, 0);
  EXPECT_EQ(SCRIPT_ERRORCODE_INTERNALERROR, 1);
  EXPECT_EQ(SCRIPT_ERRORCODE_INSUF_PARAMS, 2);
  EXPECT_EQ(SCRIPT_ERRORCODE_CAPABILITY_DENIED, 3);
  EXPECT_EQ(SCRIPT_ERRORCODE_OWN, 4);
}

}
#endif
