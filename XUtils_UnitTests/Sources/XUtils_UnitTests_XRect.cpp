/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XRect.cpp
*
* @class      XUTILS_UNITTESTS_XRECT
* @brief      XUtils unit tests for XRect class
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

#include "XUtils_UnitTests_XRect.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XRect.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XRECT
{


TEST(UNITTEST_XRECT_CLASSNAME, ConstructorDefault)
{
  XRECT rect;

  // Note: the constructor calls Clean() (which zeroes all 4 fields) and then
  // immediately overwrites them, so the real post-construction default is
  // (0,0,1,1), NOT the degenerate (0,0,0,0) that Clean() alone would suggest.
  EXPECT_DOUBLE_EQ(rect.x1, 0.0);
  EXPECT_DOUBLE_EQ(rect.y1, 0.0);
  EXPECT_DOUBLE_EQ(rect.x2, 1.0);
  EXPECT_DOUBLE_EQ(rect.y2, 1.0);
}


TEST(UNITTEST_XRECT_CLASSNAME, SetAndGetFields)
{
  XRECT rect;

  rect.x1 = -10.5;
  rect.y1 = 2.25;
  rect.x2 = 100.0;
  rect.y2 = 0.0;

  EXPECT_DOUBLE_EQ(rect.x1, -10.5);
  EXPECT_DOUBLE_EQ(rect.y1, 2.25);
  EXPECT_DOUBLE_EQ(rect.x2, 100.0);
  EXPECT_DOUBLE_EQ(rect.y2, 0.0);
}


TEST(UNITTEST_XRECT_CLASSNAME, CopyToAndCopyFrom)
{
  XRECT source;
  source.x1 = 1.0;
  source.y1 = 2.0;
  source.x2 = 3.0;
  source.y2 = 4.0;

  XRECT destination;
  source.CopyTo(destination);

  EXPECT_DOUBLE_EQ(destination.x1, 1.0);
  EXPECT_DOUBLE_EQ(destination.y1, 2.0);
  EXPECT_DOUBLE_EQ(destination.x2, 3.0);
  EXPECT_DOUBLE_EQ(destination.y2, 4.0);

  XRECT copy;
  copy.CopyFrom(source);

  EXPECT_DOUBLE_EQ(copy.x1, 1.0);
  EXPECT_DOUBLE_EQ(copy.y1, 2.0);
  EXPECT_DOUBLE_EQ(copy.x2, 3.0);
  EXPECT_DOUBLE_EQ(copy.y2, 4.0);
}


TEST(UNITTEST_XRECT_CLASSNAME, CopyRoundTripIndependence)
{
  XRECT rectA;
  rectA.x1 = 5.0;
  rectA.y1 = 6.0;
  rectA.x2 = 7.0;
  rectA.y2 = 8.0;

  XRECT rectB;
  rectB.CopyFrom(rectA);

  // Mutating the source afterwards must not affect the already-copied target.
  rectA.x1 = 999.0;

  EXPECT_DOUBLE_EQ(rectB.x1, 5.0);
  EXPECT_DOUBLE_EQ(rectA.x1, 999.0);
}


}
#endif

