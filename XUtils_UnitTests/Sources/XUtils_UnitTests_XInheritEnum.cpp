/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XInheritEnum.cpp
*
* @class      XUTILS_UNITTESTS_XINHERITENUM
* @brief      XUtils unit tests for XInheritEnum class
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

#include "XUtils_UnitTests_XInheritEnum.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XInheritEnum.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XINHERITENUM
{

// Two independent, plain (int-underlying) enums used to instantiate the
// XINHERITENUM<derived, base> template, mirroring the "module-specific
// enum extends a common base enum" usage this class is designed for.
enum DERIVED_ENUM
{
  DERIVED_ENUM_A = 1 ,
  DERIVED_ENUM_B = 2 ,
  DERIVED_ENUM_C = 3
};

enum BASE_ENUM
{
  BASE_ENUM_X = 1 ,
  BASE_ENUM_Y = 2 ,
  BASE_ENUM_Z = 3
};


TEST(UNITTEST_XINHERITENUM_CLASSNAME, ConstructFromDerivedEnum)
{
  XINHERITENUM<DERIVED_ENUM, BASE_ENUM> value(DERIVED_ENUM_B);

  EXPECT_EQ((DERIVED_ENUM)value, DERIVED_ENUM_B);
}


TEST(UNITTEST_XINHERITENUM_CLASSNAME, ConstructFromExplicitInt)
{
  XINHERITENUM<DERIVED_ENUM, BASE_ENUM> value(3);

  EXPECT_EQ((DERIVED_ENUM)value, DERIVED_ENUM_C);
}


TEST(UNITTEST_XINHERITENUM_CLASSNAME, ConstructFromBaseEnumReadThroughUnion)
{
  // NOTE: the class stores enumT/baseenumT in a union; writing baseEnum_ via
  // this constructor and reading it back through operator enumT() (which
  // reads the enum_ member) is technically undefined behavior in C++ unless
  // the two enum types are layout-compatible. Both enums here default to an
  // `int` underlying type, so in practice (on this compiler/build) the value
  // round-trips numerically. This test documents that actual, current
  // behavior -- it is not a guarantee the language makes.
  XINHERITENUM<DERIVED_ENUM, BASE_ENUM> value(BASE_ENUM_Y);

  EXPECT_EQ((int)(DERIVED_ENUM)value, (int)BASE_ENUM_Y);
}


TEST(UNITTEST_XINHERITENUM_CLASSNAME, TakeAsBaseRoundTrip)
{
  XINHERITENUM<DERIVED_ENUM, BASE_ENUM> value(DERIVED_ENUM_C);

  // TakeAsBase() converts through int and back (see XInheritEnum.h): since
  // DERIVED_ENUM_C and BASE_ENUM_Z share the same underlying numeric value
  // (3), the round trip lands on BASE_ENUM_Z.
  BASE_ENUM asBase = value.TakeAsBase();

  EXPECT_EQ(asBase, BASE_ENUM_Z);
}


TEST(UNITTEST_XINHERITENUM_CLASSNAME, DefaultConstructThenAssign)
{
  // The default constructor leaves the union completely uninitialized, so
  // this test never reads the value before assigning one of the enum
  // constructors to it (per XInheritEnum.h's documented risk).
  XINHERITENUM<DERIVED_ENUM, BASE_ENUM> value;

  value = XINHERITENUM<DERIVED_ENUM, BASE_ENUM>(DERIVED_ENUM_A);

  EXPECT_EQ((DERIVED_ENUM)value, DERIVED_ENUM_A);
}


}
#endif

