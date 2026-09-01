/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XSerializationMethod.cpp
*
* @class      XUTILS_UNITTESTS_XSERIALIZATIONMETHOD
* @brief      XUtils unit tests for XSerializationMethod class
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* @cond
* Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
* documentation files(the "Software"), to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense, and/ or sell copies of the Software,
* and to permit persons to whom the Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in all copies or substantial portions of
* the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
* THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
* TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
* @endcond
*
* --------------------------------------------------------------------------------------------------------------------*/
/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XUtils_UnitTests_XSerializationMethod.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XSerializationMethod.h"
#include "XString.h"
#include "XBuffer.h"
#include "XVariant.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XSERIALIZATIONMETHOD
{

// XSERIALIZATIONMETHOD is concrete (not abstract) but every method body in XSerializationMethod.cpp
// is an inert stub: every Add() overload unconditionally returns false, every Extract() overload
// unconditionally returns false WITHOUT touching its output parameter, and AddStruct/AddArray/
// ExtractStruct/ExtractArray/ExtractArrayElement all unconditionally return false too. It exists
// purely as the common interface XSERIALIZATIONMETHODBINARY/XSERIALIZATIONMETHODJSON override --
// these tests confirm that base-class contract (safe no-op defaults) directly, since the real,
// interesting behavior lives in the two concrete subclasses (tested separately).

TEST(UNITTEST_XSERIALIZATIONMETHOD_CLASSNAME, AddScalarOverloadsAllReturnFalse)
{
  XSERIALIZATIONMETHOD method;

  EXPECT_FALSE(method.Add(true,               __L("x")));
  EXPECT_FALSE(method.Add((char)'a',          __L("x")));
  EXPECT_FALSE(method.Add((int)1,             __L("x")));
  EXPECT_FALSE(method.Add((float)1.0f,        __L("x")));
  EXPECT_FALSE(method.Add((double)1.0,        __L("x")));
  EXPECT_FALSE(method.Add((long)1,            __L("x")));
  EXPECT_FALSE(method.Add((long long)1,       __L("x")));
  EXPECT_FALSE(method.Add((XBYTE)1,           __L("x")));
  EXPECT_FALSE(method.Add((XWORD)1,           __L("x")));
  EXPECT_FALSE(method.Add((XDWORD)1,          __L("x")));
  EXPECT_FALSE(method.Add((XQWORD)1,          __L("x")));
}


TEST(UNITTEST_XSERIALIZATIONMETHOD_CLASSNAME, AddPointerOverloadsAllReturnFalse)
{
  XSERIALIZATIONMETHOD method;

  XSTRING  string;
  XBUFFER  buffer;
  XVARIANT variant;

  EXPECT_FALSE(method.Add(&string,  __L("x")));
  EXPECT_FALSE(method.Add(&buffer,  __L("x")));
  EXPECT_FALSE(method.Add(&variant, __L("x")));
}


TEST(UNITTEST_XSERIALIZATIONMETHOD_CLASSNAME, AddStructAndAddArrayReturnFalse)
{
  XSERIALIZATIONMETHOD method;

  EXPECT_FALSE(method.AddStruct(__L("x"), true));
  EXPECT_FALSE(method.AddArray(3, __L("x"), true));
}


TEST(UNITTEST_XSERIALIZATIONMETHOD_CLASSNAME, ExtractScalarOverloadsReturnFalseAndDoNotTouchOutputParameter)
{
  XSERIALIZATIONMETHOD method;

  bool      boolvar   = true;
  char      charvar   = 'z';
  int       intvar    = 12345;
  float     floatvar  = 9.5f;
  double    doublevar = 9.5;
  long      longvar   = 999;
  long long llvar     = 999;
  XBYTE     bytevar   = 7;
  XWORD     wordvar   = 7;
  XDWORD    dwordvar  = 7;
  XQWORD    qwordvar  = 7;

  EXPECT_FALSE(method.Extract(boolvar,   __L("x")));
  EXPECT_FALSE(method.Extract(charvar,   __L("x")));
  EXPECT_FALSE(method.Extract(intvar,    __L("x")));
  EXPECT_FALSE(method.Extract(floatvar,  __L("x")));
  EXPECT_FALSE(method.Extract(doublevar, __L("x")));
  EXPECT_FALSE(method.Extract(longvar,   __L("x")));
  EXPECT_FALSE(method.Extract(llvar,     __L("x")));
  EXPECT_FALSE(method.Extract(bytevar,   __L("x")));
  EXPECT_FALSE(method.Extract(wordvar,   __L("x")));
  EXPECT_FALSE(method.Extract(dwordvar,  __L("x")));
  EXPECT_FALSE(method.Extract(qwordvar,  __L("x")));

  // Every by-reference parameter must be left exactly as it was: the base class must not
  // silently mutate caller state even though it reports failure.
  EXPECT_TRUE(boolvar);
  EXPECT_EQ(charvar,   'z');
  EXPECT_EQ(intvar,    12345);
  EXPECT_FLOAT_EQ(floatvar, 9.5f);
  EXPECT_DOUBLE_EQ(doublevar, 9.5);
  EXPECT_EQ(longvar,   999);
  EXPECT_EQ(llvar,     999);
  EXPECT_EQ(bytevar,   7);
  EXPECT_EQ(wordvar,   7);
  EXPECT_EQ(dwordvar,  7u);
  EXPECT_EQ(qwordvar,  7u);
}


TEST(UNITTEST_XSERIALIZATIONMETHOD_CLASSNAME, ExtractStructAndExtractArrayReturnFalse)
{
  XSERIALIZATIONMETHOD method;

  EXPECT_FALSE(method.ExtractStruct(__L("x")));
  EXPECT_FALSE(method.ExtractArray(3, __L("x")));
}


TEST(UNITTEST_XSERIALIZATIONMETHOD_CLASSNAME, ExtractArrayElementUnconditionallyReturnsTrueUnlikeItsSiblingStubs)
{
  XSERIALIZATIONMETHOD method;

  // Unlike every other stub in this class (which all return false), ExtractArrayElement()'s
  // body is unconditionally "return true;" -- a real, verifiable asymmetry in the base class's
  // own inert defaults.
  EXPECT_TRUE(method.ExtractArrayElement(0, __L("x"), true));
  EXPECT_TRUE(method.ExtractArrayElement(0, __L("x"), false));
}


}
#endif
