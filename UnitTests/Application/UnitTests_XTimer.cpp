/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UnitTests_XTimer.cpp
* 
* @class      UNITTESTS_XTIMER
* @brief      Unit Tests for XTimer class
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

#include "UnitTests_XTimer.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XString.h"
#include "XTimer.h"
#include "XSleep.h"
#include "XDateTime.h"

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


#pragma endregion


#ifdef GOOGLETEST_ACTIVE      
namespace TEST_XTIMER
{


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XTimer_CLASSNAME, ConstructorSize)
* @brief      Unit test of UNITTEST_XTimer_CLASSNAME:  ConstructorSize
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XTIMER_CLASSNAME, ConstructorSize) 
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);
  
  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XTIMER_CLASSNAME, Reset)
* @brief      Unit test of UNITTEST_XTIMER_CLASSNAME:  Reset
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XTIMER_CLASSNAME, Reset)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);

  if(xtimer)
    {
      xtimer->Reset();
      EXPECT_NEAR(0, (double)xtimer->GetMeasureMilliSeconds(), 50);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XTIMER_CLASSNAME, GetMeasureMilliSeconds)
* @brief      Unit test of UNITTEST_XTIMER_CLASSNAME:  GetMeasureMilliSeconds
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XTIMER_CLASSNAME, GetMeasureMilliSeconds)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);

  if(xtimer)
    {
      xtimer->Reset();  
      GEN_XSLEEP.MilliSeconds(50);
      EXPECT_NEAR(0, (double)xtimer->GetMeasureMilliSeconds(), 65);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XTIMER_CLASSNAME, GetMeasureSeconds)
* @brief      Unit test of UNITTEST_XTIMER_CLASSNAME:  GetMeasureSeconds
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XTIMER_CLASSNAME, GetMeasureSeconds)

{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);

  if(xtimer)
    {
      xtimer->Reset();  
      GEN_XSLEEP.Seconds(1);
      EXPECT_NEAR(0, (double)xtimer->GetMeasureSeconds(), 2);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XTIMER_CLASSNAME, GetMeasureToDate)
* @brief      Unit test of UNITTEST_XTIMER_CLASSNAME:  GetMeasureToDate
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XTIMER_CLASSNAME, GetMeasureToDate)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);

  XDATETIME datetime;

  xtimer->AddSeconds(1000000000000L);
  
  if(xtimer)
    {   
      xtimer->GetMeasureToDate(&datetime);
      EXPECT_EQ(datetime.GetYear()        , 26976);
      EXPECT_EQ(datetime.GetMonth()       , 2);
      EXPECT_EQ(datetime.GetDay()         , 2);
      EXPECT_EQ(datetime.GetHours()       , 1);
      EXPECT_EQ(datetime.GetMinutes()     , 46);
      EXPECT_EQ(datetime.GetSeconds()     , 40);
      EXPECT_EQ(datetime.GetMilliSeconds(), 0);

    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XTIMER_CLASSNAME, GetMeasureString)
* @brief      Unit test of UNITTEST_XTIMER_CLASSNAME:  GetMeasureString
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XTIMER_CLASSNAME, GetMeasureString)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);

  XSTRING measure;

  xtimer->AddSeconds(100000L);
  xtimer->AddSeconds(750000L);

  if(xtimer)
    {   
      xtimer->GetMeasureString(measure, true);
      EXPECT_STREQ(measure.Get(), __L("9 dias, 20 horas, 6 minutos, 40 segundos"));
    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XTIMER_CLASSNAME, GetMicroSecondsTickCounter)
* @brief      Unit test of UNITTEST_XTIMER_CLASSNAME:  GetMicroSecondsTickCounter
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XTIMER_CLASSNAME, GetMicroSecondsTickCounter)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);

  if(xtimer)
    {        
      EXPECT_TRUE(xtimer->GetMicroSecondsTickCounter());
    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);  
}


}


#endif


#pragma endregion

