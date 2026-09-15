/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLanguageG.cpp
* @brief      Unit tests for the G interpreter
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLanguageG.h"
#include "UnitTests_Script_TestHelpers.h"
#include "Script_Language_G.h"
#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_G_ACTIVE)
namespace TEST_SCRIPTLANGUAGEG
{

TEST(UNITTESTS_SCRIPTLANGUAGEG_CLASSNAME, CommandStoresTextAndToken)
{
  SCRIPT_LNG_G_COMMAND command;

  ASSERT_TRUE(command.Set(__L("return"), SCRIPT_LNG_G_TOKENIREPS_RETURN));
  EXPECT_EQ(command.GetCommand()->Compare(__L("return")), 0);
  EXPECT_EQ(command.GetToken(), SCRIPT_LNG_G_TOKENIREPS_RETURN);
}


TEST(UNITTESTS_SCRIPTLANGUAGEG_CLASSNAME, FloatVariableRoundTripsThroughVariant)
{
  SCRIPT_LNG_G_VAR source;
  SCRIPT_LNG_G_VAR destination;
  XVARIANT variant;

  EXPECT_TRUE(source.SetType(SCRIPT_LNG_G_TOKENIREPS_FLOAT));
  EXPECT_TRUE(source.SetValueFloat(3.75f));
  EXPECT_TRUE(source.ConvertToXVariant(variant));
  EXPECT_TRUE(destination.ConvertFromXVariant(variant));
  EXPECT_EQ(destination.GetType(), SCRIPT_LNG_G_TOKENIREPS_FLOAT);
  EXPECT_FLOAT_EQ(destination.GetValueFloat(), 3.75f);
}


TEST(UNITTESTS_SCRIPTLANGUAGEG_CLASSNAME, FunctionNameSetterReportsSuccess)
{
  SCRIPT_LNG_G_FUNCTIONTYPE function;

  EXPECT_TRUE(function.SetName(__L("main")));
  EXPECT_EQ(function.GetName()->Compare(__L("main")), 0);
}


TEST(UNITTESTS_SCRIPTLANGUAGEG_CLASSNAME, ExecutesIntegerAndFloatExpressions)
{
  SCRIPT_LNG_G script;
  int returnvalue = 0;

  (*script.GetScript()) = __L("int main(){ float value; value = 1.5 + 2.25; if(value == 3.75){ return 42; } return 0; }");

  EXPECT_EQ(script.Run(&returnvalue), SCRIPT_ERRORCODE_NONE);
  EXPECT_EQ(returnvalue, 42);
}


TEST(UNITTESTS_SCRIPTLANGUAGEG_CLASSNAME, ReportsUnexpectedEndOfInput)
{
  SCRIPT_LNG_G script;

  (*script.GetScript()) = __L("int main(){ string value; value = \"unterminated; }");

  EXPECT_NE(script.Run(), SCRIPT_ERRORCODE_NONE);
}


TEST(UNITTESTS_SCRIPTLANGUAGEG_CLASSNAME, RejectsModuloByZero)
{
  SCRIPT_LNG_G script;

  (*script.GetScript()) = __L("int main(){ return 10 % 0; }");

  EXPECT_EQ(script.Run(), SCRIPT_LNG_G_ERRORCODE_DIV_BY_ZERO);
}

}
#endif
