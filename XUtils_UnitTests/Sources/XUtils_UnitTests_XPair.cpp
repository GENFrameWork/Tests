/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XPair.cpp
*
* @class      XUTILS_UNITTESTS_XPAIR
* @brief      XUtils unit tests for XPair class
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

#include "XUtils_UnitTests_XPair.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XPair.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XPAIR
{


TEST(UNITTEST_XPAIR_CLASSNAME, ConstructorDefault)
{
  XPAIR<int, int> pair;

  // Clean() value-initializes both fields via L()/R(), which for int is 0.
  EXPECT_EQ(pair.left, 0);
  EXPECT_EQ(pair.right, 0);
}


TEST(UNITTEST_XPAIR_CLASSNAME, ConstructorWithValues)
{
  XPAIR<int, int> pair(10, 20);

  EXPECT_EQ(pair.left, 10);
  EXPECT_EQ(pair.right, 20);
}


TEST(UNITTEST_XPAIR_CLASSNAME, ConstructorCopy)
{
  XPAIR<int, int> original(5, 7);
  XPAIR<int, int> copy(original);

  EXPECT_EQ(copy.left, 5);
  EXPECT_EQ(copy.right, 7);

  // Mutating the original afterwards must not affect the already-made copy.
  original.left = 999;
  EXPECT_EQ(copy.left, 5);
}


TEST(UNITTEST_XPAIR_CLASSNAME, OperatorAssign)
{
  XPAIR<int, int> pairA(1, 2);
  XPAIR<int, int> pairB;

  pairB = pairA;

  EXPECT_EQ(pairB.left, 1);
  EXPECT_EQ(pairB.right, 2);
}


TEST(UNITTEST_XPAIR_CLASSNAME, OperatorEquals)
{
  XPAIR<int, int> pairA(3, 4);
  XPAIR<int, int> pairB(3, 4);
  XPAIR<int, int> pairC(3, 5);

  EXPECT_TRUE(pairA == pairB);
  EXPECT_FALSE(pairA == pairC);
}


TEST(UNITTEST_XPAIR_CLASSNAME, OperatorLessThanComparesOnlyLeft)
{
  XPAIR<int, int> pairA(1, 100);
  XPAIR<int, int> pairB(2, 0);

  // operator< only compares .left, per XPair.h ("not much sense comparing
  // the right element", matching SGI STL behavior) -- pairB.right (0) is
  // smaller than pairA.right (100), yet pairA < pairB must still hold
  // because only .left (1 < 2) is considered.
  EXPECT_TRUE(pairA < pairB);
  EXPECT_FALSE(pairB < pairA);

  XPAIR<int, int> pairEqualLeft(1, 999);
  EXPECT_FALSE(pairA < pairEqualLeft);
  EXPECT_FALSE(pairEqualLeft < pairA);
}


TEST(UNITTEST_XPAIR_CLASSNAME, DifferentTypePair)
{
  // Instantiate with two different concrete types to exercise the
  // independent L/R template parameters.
  XPAIR<int, double> pair(42, 3.5);

  EXPECT_EQ(pair.left, 42);
  EXPECT_DOUBLE_EQ(pair.right, 3.5);
}


}
#endif

