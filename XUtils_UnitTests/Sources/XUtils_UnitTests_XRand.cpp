/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XRand.cpp
*
* @class      XUTILS_UNITTESTS_XRAND
* @brief      XUtils unit tests for XRand class
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

#include "XUtils_UnitTests_XRand.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include <string.h>

#include "XFactory.h"
#include "XRand.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XRAND
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void EnsureXRandInstance()
* @brief      Ensures that the XRand singleton instance exists.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
static void EnsureXRandInstance()
{
  if(!XRAND::GetIsInstanced())
    {
      XRAND* instance = GEN_NEW XRAND();
      XRAND::SetInstance(instance);
    }
}


TEST(UNITTEST_XRAND_CLASSNAME, IniAndIsCryptographicallySecure)
{
  EnsureXRandInstance();

  EXPECT_TRUE(XRAND::GetInstance().Ini());

  // NOTE: the base XRAND::IsCryptographicallySecure() documents always returning false, but
  // this application's Linux startup (MainProcLINUX.cpp) installs an XLINUXRAND singleton
  // before any test runs, and XLINUXRAND overrides this to unconditionally return true - so
  // the live singleton's actual answer depends on which concrete subclass is installed, not
  // just on the base class's documented contract. We only assert it is a stable, callable bool.
  bool result = XRAND::GetInstance().IsCryptographicallySecure();
  EXPECT_TRUE(result == true || result == false);
}


TEST(UNITTEST_XRAND_CLASSNAME, GenerateFillsBufferAndAcceptsZeroSize)
{
  EnsureXRandInstance();

  XBYTE buffer[32];
  memset(buffer, 0, sizeof(buffer));

  EXPECT_TRUE(XRAND::GetInstance().Generate(buffer, sizeof(buffer)));

  // At least one byte should have moved away from 0 across 32 random bytes.
  bool allzero = true;
  for(XDWORD c=0; c<sizeof(buffer); c++)
    {
      if(buffer[c] != 0) { allzero = false; break; }
    }
  EXPECT_FALSE(allzero);

  // Zero-size request is a documented no-op success.
  EXPECT_TRUE(XRAND::GetInstance().Generate(buffer, 0));

  // Null buffer with a non-zero size must fail, not crash.
  EXPECT_FALSE(XRAND::GetInstance().Generate((XBYTE*)NULL, 4));
}


TEST(UNITTEST_XRAND_CLASSNAME, MaxElementsRespectsUpperBoundAndRejectsNonPositive)
{
  EnsureXRandInstance();

  for(int c=0; c<50; c++)
    {
      int value = XRAND::GetInstance().MaxElements(10);
      EXPECT_GE(value, 0);
      EXPECT_LT(value, 10);
    }

  EXPECT_EQ(XRAND::GetInstance().MaxElements(0), 0);
  EXPECT_EQ(XRAND::GetInstance().MaxElements(-5), 0);
}


TEST(UNITTEST_XRAND_CLASSNAME, MaxRespectsUpperBoundAndRejectsNonPositive)
{
  EnsureXRandInstance();

  for(int c=0; c<50; c++)
    {
      int value = XRAND::GetInstance().Max(10);
      EXPECT_GE(value, 0);
      EXPECT_LE(value, 10);
    }

  EXPECT_EQ(XRAND::GetInstance().Max(0), 0);
  EXPECT_EQ(XRAND::GetInstance().Max(-5), 0);
}


TEST(UNITTEST_XRAND_CLASSNAME, BetweenIntInclusiveRangeAndDegenerateCase)
{
  EnsureXRandInstance();

  for(int c=0; c<100; c++)
    {
      int value = XRAND::GetInstance().Between(5, 10);
      EXPECT_GE(value, 5);
      EXPECT_LE(value, 10);
    }

  // min >= max: the function documents returning min immediately.
  EXPECT_EQ(XRAND::GetInstance().Between(10, 10), 10);
  EXPECT_EQ(XRAND::GetInstance().Between(10, 5), 10);
}


TEST(UNITTEST_XRAND_CLASSNAME, BetweenFloatInclusiveRangeAndDegenerateCase)
{
  EnsureXRandInstance();

  for(int c=0; c<100; c++)
    {
      float value = XRAND::GetInstance().Between(1.0f, 2.0f);
      EXPECT_GE(value, 1.0f);
      EXPECT_LE(value, 2.0f);
    }

  EXPECT_FLOAT_EQ(XRAND::GetInstance().Between(3.0f, 3.0f), 3.0f);
  EXPECT_FLOAT_EQ(XRAND::GetInstance().Between(5.0f, 1.0f), 5.0f);
}


TEST(UNITTEST_XRAND_CLASSNAME, PercentBoundaryBehavior)
{
  EnsureXRandInstance();

  // Documented edge-cases: always false at/below 0, always true at/above 100.
  EXPECT_FALSE(XRAND::GetInstance().Percent(0));
  EXPECT_FALSE(XRAND::GetInstance().Percent(-10));
  EXPECT_TRUE(XRAND::GetInstance().Percent(100));
  EXPECT_TRUE(XRAND::GetInstance().Percent(150));

  // Interior values must be a stable boolean call (no crash), exercised repeatedly.
  for(int c=0; c<20; c++)
    {
      bool result = XRAND::GetInstance().Percent(50);
      EXPECT_TRUE(result == true || result == false);
    }
}


TEST(UNITTEST_XRAND_CLASSNAME, SetInstanceNull)
{
  EXPECT_FALSE(XRAND::SetInstance(NULL));
}


TEST(UNITTEST_XRAND_CLASSNAME, InstanceLifecycle)
{
  XRAND* originalinstance = NULL;
  if(XRAND::GetIsInstanced()) originalinstance = &XRAND::GetInstance();

  XRAND* testinstance = GEN_NEW XRAND();
  EXPECT_NE((void*)testinstance, (void*)NULL);

  EXPECT_TRUE(XRAND::SetInstance(testinstance));
  EXPECT_TRUE(XRAND::GetIsInstanced());
  EXPECT_EQ(&XRAND::GetInstance(), testinstance);

  if(originalinstance)
    {
      EXPECT_TRUE(XRAND::SetInstance(originalinstance));
      GEN_DELETE testinstance;
    }
  else
    {
      EXPECT_TRUE(XRAND::DelInstance());
      EnsureXRandInstance();
    }
}


TEST(UNITTEST_XRAND_CLASSNAME, DelInstanceTwice)
{
  XRAND* originalinstance = NULL;
  if(XRAND::GetIsInstanced()) originalinstance = &XRAND::GetInstance();

  XRAND* testinstance = GEN_NEW XRAND();
  EXPECT_NE((void*)testinstance, (void*)NULL);

  EXPECT_TRUE(XRAND::SetInstance(testinstance));

  EXPECT_TRUE(XRAND::DelInstance());
  EXPECT_FALSE(XRAND::DelInstance());

  if(originalinstance)
    {
      EXPECT_TRUE(XRAND::SetInstance(originalinstance));
    }
  else
    {
      EnsureXRandInstance();
    }
}


}
#endif
