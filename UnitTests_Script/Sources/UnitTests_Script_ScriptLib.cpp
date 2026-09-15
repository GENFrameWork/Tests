/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptLib.cpp
* @brief      Unit tests for SCRIPT_LIB
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptLib.h"
#include "UnitTests_Script_TestHelpers.h"
#include "GEN_Control.h"

#ifdef GOOGLETEST_ACTIVE
namespace TEST_SCRIPTLIB
{

TEST(UNITTESTS_SCRIPTLIB_CLASSNAME, ConvertsSupportedVariantTypes)
{
  SCRIPT_LIB library(__L("Test"));
  XVARIANT integer(25);
  XVARIANT real(2.5f);
  XVARIANT text(__L("value"));
  int convertedinteger = 0;
  float convertedreal = 0.0f;
  XSTRING convertedtext;

  EXPECT_TRUE(library.GetParamConverted(&integer, convertedinteger));
  EXPECT_EQ(convertedinteger, 25);
  EXPECT_TRUE(library.GetParamConverted(&real, convertedreal));
  EXPECT_FLOAT_EQ(convertedreal, 2.5f);
  EXPECT_TRUE(library.GetParamConverted(&text, convertedtext));
  EXPECT_EQ(convertedtext.Compare(__L("value")), 0);
  EXPECT_FALSE(library.GetParamConverted(NULL, convertedinteger));
}


TEST(UNITTESTS_SCRIPTLIB_CLASSNAME, FormatsParametersOnceAndBoundsErrors)
{
  SCRIPT_LIB library(__L("Test"));
  XVARIANT integer(7);
  XVARIANT text(__L("100% ready"));
  XVECTOR<XVARIANT*> params;
  XSTRING output;

  params.Add(&integer);
  params.Add(&text);

  EXPECT_EQ(library.FormatParams(&params, 0, __L("%d %s"), output), SCRIPT_LIB_FORMATSTATUS_OK);
  EXPECT_EQ(output.Compare(__L("7 100% ready")), 0);
  EXPECT_EQ(library.FormatParams(&params, 0, __L("%0"), output), SCRIPT_LIB_FORMATSTATUS_INVALID_FORMAT);
  EXPECT_EQ(library.FormatParams(&params, 0, __L("%d %s %d"), output), SCRIPT_LIB_FORMATSTATUS_INSUFFICIENT_PARAMS);
}


TEST(UNITTESTS_SCRIPTLIB_CLASSNAME, ValidatesRequiredParameterCountAndPointers)
{
  SCRIPT_LIB                     library(__L("Test"));
  UNITTESTS_SCRIPT_ERRORCAPTURE  script;
  XVECTOR<XVARIANT*>             params;
  XVARIANT                       value(7);

  EXPECT_FALSE(library.CheckParams(&script, &params, 1));
  EXPECT_EQ(script.GetLastError(), SCRIPT_ERRORCODE_INSUF_PARAMS);

  params.Add(NULL);
  script.ResetLastError();

  EXPECT_FALSE(library.CheckParams(&script, &params, 1));
  EXPECT_EQ(script.GetLastError(), SCRIPT_ERRORCODE_INSUF_PARAMS);

  params.DeleteAll();
  params.Add(&value);
  script.ResetLastError();

  EXPECT_TRUE(library.CheckParams(&script, &params, 1));
  EXPECT_EQ(script.GetLastError(), SCRIPT_ERRORCODE_NONE);
  EXPECT_FALSE(library.CheckParams(NULL, &params, 1));
  EXPECT_FALSE(library.CheckParams(&script, NULL, 1));

  params.DeleteAll();
}

}
#endif
