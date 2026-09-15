/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptXEvent.cpp
* @brief      Unit tests for SCRIPT_XEVENT
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptXEvent.h"
#include "UnitTests_Script_TestHelpers.h"
#include "Script_XEvent.h"
#include "GEN_Control.h"

#ifdef GOOGLETEST_ACTIVE
namespace TEST_SCRIPTXEVENT
{

TEST(UNITTESTS_SCRIPTXEVENT_CLASSNAME, InitializesAndStoresDiagnosticData)
{
  SCRIPT subject;
  SCRIPT_XEVENT event(&subject, SCRIPT_XEVENT_TYPE_ERROR);

  EXPECT_EQ(event.GetScript(), (SCRIPT*)NULL);
  EXPECT_EQ(event.GetError(), 0);
  EXPECT_EQ(event.GetNLine(), 0);

  event.SetScript(&subject);
  event.SetError(SCRIPT_ERRORCODE_INTERNALERROR);
  event.SetNLine(12);
  event.GetNameScript()->Set(__L("test.g"));
  event.GetErrorText()->Set(__L("error"));
  event.GetCurrentToken()->Set(__L("token"));

  EXPECT_EQ(event.GetScript(), &subject);
  EXPECT_EQ(event.GetError(), SCRIPT_ERRORCODE_INTERNALERROR);
  EXPECT_EQ(event.GetNLine(), 12);
  EXPECT_EQ(event.GetNameScript()->Compare(__L("test.g")), 0);
}

}
#endif
