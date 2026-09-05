/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XTimer.cpp
*
* @class      UNITTESTS_XUTILS_XTIMER
* @brief      XUtils unit tests for XTimer class
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

#include "UnitTests_XUtils_XTimer.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XString.h"
#include "XTimer.h"
#include "XSleep.h"
#include "XDateTime.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE      
namespace TEST_XTIMER
{


TEST(UNITTESTS_XTIMER_CLASSNAME, ConstructorSize) 
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);
  
  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);
}


TEST(UNITTESTS_XTIMER_CLASSNAME, Reset)
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


TEST(UNITTESTS_XTIMER_CLASSNAME, GetMeasureMilliSeconds)
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


TEST(UNITTESTS_XTIMER_CLASSNAME, GetMeasureSeconds)

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


TEST(UNITTESTS_XTIMER_CLASSNAME, GetMeasureToDate)
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


TEST(UNITTESTS_XTIMER_CLASSNAME, GetMeasureString)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);

  XSTRING measure;

  xtimer->AddSeconds(100000L);
  xtimer->AddSeconds(750000L);

  if(xtimer)
    {   
      xtimer->GetMeasureString(measure, true);
      EXPECT_STREQ(measure.Get(), __L("9 days, 20 hours, 6 minutes, 40 seconds"));
    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);  
}


TEST(UNITTESTS_XTIMER_CLASSNAME, GetMicroSecondsTickCounter)
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


TEST(UNITTESTS_XTIMER_CLASSNAME, AddMilliSecondsDirectly)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);

  if(xtimer)
    {
      xtimer->Reset();
      xtimer->AddMilliSeconds(5000);
      EXPECT_NEAR(5000, (double)xtimer->GetMeasureMilliSeconds(), 65);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);
}


TEST(UNITTESTS_XTIMER_CLASSNAME, SetMilliSecondsResetsBaseline)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);

  if(xtimer)
    {
      // Push the timer far ahead first, then confirm SetMilliSeconds discards that offset
      // (it Reset()s internally before adding), rather than accumulating on top of it.
      xtimer->AddSeconds(100000L);
      xtimer->SetMilliSeconds(3000);
      EXPECT_NEAR(3000, (double)xtimer->GetMeasureMilliSeconds(), 65);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);
}


TEST(UNITTESTS_XTIMER_CLASSNAME, GetMeasureHoursMinutesMicroSeconds)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);

  if(xtimer)
    {
      xtimer->Reset();
      xtimer->AddSeconds(3661L);  // 1h 1m 1s

      EXPECT_EQ(1,  xtimer->GetMeasureHours());
      EXPECT_EQ(61, xtimer->GetMeasureMinutes());  // total elapsed minutes, not modulo
      // Multiply as XQWORD (64-bit) from the start: on platforms where "long" is 32 bits (e.g. LLP64
      // targets such as Windows/clang-cl), 3661L*1000000L overflows a 32-bit long before the result is
      // ever cast to XQWORD, tripping -Winteger-overflow -- casting each operand up-front avoids that.
      EXPECT_GE(xtimer->GetMeasureMicroSeconds(), (XQWORD)3661*(XQWORD)1000000);
    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);
}


TEST(UNITTESTS_XTIMER_CLASSNAME, GetMeasureStringShortForm)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_TRUE(xtimer != NULL);

  XSTRING measure;

  xtimer->AddSeconds(3661L);  // 1h 1m 1s, no days/months/years component

  if(xtimer)
    {
      xtimer->GetMeasureString(measure, false);
      EXPECT_STREQ(measure.Get(), __L("01:01:01"));
    }

  GEN_XFACTORY.DeleteTimer(xtimer);
  xtimer = NULL;
  EXPECT_TRUE(xtimer == NULL);
}


}


#endif


