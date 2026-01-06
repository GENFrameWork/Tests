/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UnitTests_XSleep.cpp
* 
* @class      XUTILS_UNITTESTS_XSLEEP
* @brief      Unit Tests for XSleep class
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
#pragma region PRECOMPILATION_DEFINES_INCLUDE

#include "GEN_Defines.h"

#pragma endregion


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/
#pragma region INCLUDES

#include "XUtils_UnitTests_XSleep.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XSleep.h"
#include "XTimer.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#ifdef GOOGLETEST_ACTIVE      
namespace TEST_XSLEEP
{

       
/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void EnsureXSleepInstance()
* @brief      Ensure XSleep instance
* @ingroup    UNIT TEST
*
* @return     Does not return anything. 
*
* --------------------------------------------------------------------------------------------------------------------*/
static void EnsureXSleepInstance()
{
  if(!XSLEEP::GetIsInstanced())
    {
      XSLEEP* instance = new XSLEEP();
      XSLEEP::SetInstance(instance);
    }
}

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn  
* @brief      Unit test of UNITTEST_XSLEEP_CLASSNAME:  Seconds
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSLEEP_CLASSNAME, Seconds)
{
  EnsureXSleepInstance();
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_NE(xtimer, nullptr);
  
  GEN_XSLEEP.Seconds(2);                                

  EXPECT_GE(xtimer->GetMeasureSeconds(), 2);

  GEN_XFACTORY.DeleteTimer(xtimer);
 }


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSLEEP_CLASSNAME, Miliseconds)
* @brief      Unit test of UNITTEST_XSLEEP_CLASSNAME:  Miliseconds
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSLEEP_CLASSNAME, Miliseconds)
{
  EnsureXSleepInstance();
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_NE(xtimer, nullptr);

  GEN_XSLEEP.MilliSeconds(2000);

  EXPECT_GE(xtimer->GetMeasureMilliSeconds(),2000);

  GEN_XFACTORY.DeleteTimer(xtimer);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSLEEP_CLASSNAME, Microseconds)
* @brief      Unit test of UNITTEST_XSLEEP_CLASSNAME:  Microseconds
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSLEEP_CLASSNAME, Microseconds)
{
  EnsureXSleepInstance();
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_NE(xtimer, nullptr);

  GEN_XSLEEP.MicroSeconds(100000);  // 100 ms

  EXPECT_GE(xtimer->GetMeasureMilliSeconds(),100);

  GEN_XFACTORY.DeleteTimer(xtimer);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSLEEP_CLASSNAME, Nanoseconds)
* @brief      Unit test of UNITTEST_XSLEEP_CLASSNAME:  Nanoseconds
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
/*
TEST(UNITTEST_XSLEEP_CLASSNAME, Nanoseconds)
{
  EnsureXSleepInstance();
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_NE(xtimer, nullptr);

  GEN_XSLEEP.NanoSeconds(100000000);  // 100 ms

  EXPECT_GE(xtimer->GetMeasureMilliSeconds(),100);

  GEN_XFACTORY.DeleteTimer(xtimer);
}
*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSLEEP_CLASSNAME, SetInstanceNull)
* @brief      Unit test of UNITTEST_XSLEEP_CLASSNAME:  SetInstanceNull
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSLEEP_CLASSNAME, SetInstanceNull)
{
  EXPECT_FALSE(XSLEEP::SetInstance(NULL));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSLEEP_CLASSNAME, InstanceLifecycle)
* @brief      Unit test of UNITTEST_XSLEEP_CLASSNAME:  InstanceLifecycle
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSLEEP_CLASSNAME, InstanceLifecycle)
{
  XSLEEP* originalinstance = NULL;
  if(XSLEEP::GetIsInstanced()) originalinstance = &XSLEEP::GetInstance();

  XSLEEP* testinstance = new XSLEEP();
  EXPECT_NE(testinstance, nullptr);

  EXPECT_TRUE(XSLEEP::SetInstance(testinstance));
  EXPECT_TRUE(XSLEEP::GetIsInstanced());
  EXPECT_EQ(&XSLEEP::GetInstance(), testinstance);

  if(originalinstance)
    {
      EXPECT_TRUE(XSLEEP::SetInstance(originalinstance));
      delete testinstance;
    }
  else
    {
      EXPECT_TRUE(XSLEEP::DelInstance());
      EnsureXSleepInstance();
    }
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSLEEP_CLASSNAME, SleepAPIAcceptsZero)
* @brief      Unit test of UNITTEST_XSLEEP_CLASSNAME:  SleepAPIAcceptsZero
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSLEEP_CLASSNAME, SleepAPIAcceptsZero)
{
  EnsureXSleepInstance();

  // The API should be robust to edge-case values.
  // We only validate that the calls are safe.
  GEN_XSLEEP.Seconds(0);
  GEN_XSLEEP.MilliSeconds(0);
  GEN_XSLEEP.MicroSeconds(0);
  GEN_XSLEEP.NanoSeconds(0);

  SUCCEED();
}



/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSLEEP_CLASSNAME, DelInstanceTwice)
* @brief      Unit test of UNITTEST_XSLEEP_CLASSNAME:  DelInstanceTwice
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSLEEP_CLASSNAME, DelInstanceTwice)
{
  XSLEEP* originalinstance = NULL;
  if(XSLEEP::GetIsInstanced()) originalinstance = &XSLEEP::GetInstance();

  XSLEEP* testinstance = new XSLEEP();
  EXPECT_NE(testinstance, nullptr);

  EXPECT_TRUE(XSLEEP::SetInstance(testinstance));

  EXPECT_TRUE(XSLEEP::DelInstance());
  EXPECT_FALSE(XSLEEP::DelInstance());

  if(originalinstance)
    {
      EXPECT_TRUE(XSLEEP::SetInstance(originalinstance));
    }
  else
    {
      EnsureXSleepInstance();
    }

}


}
#endif


#pragma endregion
