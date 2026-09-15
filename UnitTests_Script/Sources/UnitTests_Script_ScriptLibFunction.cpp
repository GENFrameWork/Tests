/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLibFunction.cpp
* @brief      Unit tests for SCRIPT_LIB_FUNCTION
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLibFunction.h"
#include "UnitTests_Script_TestHelpers.h"
#include "GEN_Control.h"

#ifdef GOOGLETEST_ACTIVE
namespace TEST_SCRIPTLIBFUNCTION
{

TEST(UNITTESTS_SCRIPTLIBFUNCTION_CLASSNAME, StoresAndUpdatesDescriptor)
{
  SCRIPT_LIB first(__L("First"));
  SCRIPT_LIB second(__L("Second"));
  SCRIPT_LIB_FUNCTION function(&first, __L("Function"), UnitTests_Script_DummyFunction);

  EXPECT_EQ(function.GetLibrary(), &first);
  EXPECT_EQ(function.GetName()->Compare(__L("Function")), 0);
  SCRFUNCIONLIBRARY expectedfunction = UnitTests_Script_DummyFunction;

  EXPECT_EQ(function.GetFunctionLibrary(), expectedfunction);
  EXPECT_FALSE(function.SetLibrary(NULL));
  EXPECT_TRUE(function.SetLibrary(&second));
  EXPECT_EQ(function.GetLibrary(), &second);
  EXPECT_TRUE(function.SetFunctionLibrary(NULL));
  EXPECT_EQ(function.GetFunctionLibrary(), (SCRFUNCIONLIBRARY)NULL);
}

}
#endif
