/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XUtils_UnitTests_XDateTime.cpp
* 
* @class      XUTILS_UNITTESTS_XDATETIME
* @brief      XUtils Unit Tests for XDateTime class
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

#include "XUtils_UnitTests_XDateTime.h"

#include "string.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
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


#ifdef GOOGLETEST_ACTIVE      
namespace TEST_XDATETIME
{


/*---- AUXILIARY FUNCTIONS -------------------------------------------------------------------------------------------*/
#pragma region AUXILIARY_FUNCTIONS

static void SetKnownDateTime(XDATETIME* datetime, int day, int month, int year, int hours, int minutes, int seconds, int milliseconds)
{
  if(!datetime) return;

  datetime->SetToZero();
  datetime->SetDay(day);
  datetime->SetMonth(month);
  datetime->SetYear(year);
  datetime->SetHours(hours);
  datetime->SetMinutes(minutes);
  datetime->SetSeconds(seconds);
  datetime->SetMilliSeconds(milliseconds);
}

#pragma endregion


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, Constructor)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  Constructor
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, Constructor) 
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  EXPECT_NE((void*)datetime, (void*)NULL);  
       
  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, Assing1)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  Assing1
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, Assing1) 
{
  XDATETIME*        datetime = GEN_XFACTORY.CreateDateTime();
  XDATETIME_DAYWEEK dayweek; 

  EXPECT_NE((void*)datetime, (void*)NULL);       

  datetime->SetToZero();

  datetime->SetDay(31);
  datetime->SetMonth(12);
  datetime->SetYear(2000);
  datetime->SetHours(11);
  datetime->SetMinutes(59);
  datetime->SetSeconds(59);
  datetime->SetMilliSeconds(100);

  dayweek = datetime->GetDayOfWeek();
  EXPECT_EQ(dayweek, XDATETIME_DAYWEEK_SUNDAY);    
  EXPECT_EQ(datetime->GetDayOfYear(), 366);    
  EXPECT_EQ(datetime->GetWeekOfYear(), 53);  

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, Assing2)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  Assing2
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, Assing2) 
{
  XDATETIME*        datetime = GEN_XFACTORY.CreateDateTime();
  XDATETIME_DAYWEEK dayweek; 

  EXPECT_NE((void*)datetime, (void*)NULL);       

  datetime->SetToZero();

  datetime->SetDay(31);
  datetime->SetMonth(12);
  datetime->SetYear(2000);
  datetime->SetHours(11);
  datetime->SetMinutes(59);
  datetime->SetSeconds(59);
  datetime->SetMilliSeconds(100); 

  datetime->AddDays(1);

  dayweek = datetime->GetDayOfWeek();
  EXPECT_EQ(dayweek, XDATETIME_DAYWEEK_MONDAY);    
  EXPECT_EQ(datetime->GetDayOfYear(), 1);    
  EXPECT_EQ(datetime->GetWeekOfYear(), 1);  

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringStandard)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeToStringStandard
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringStandard)

{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;  

  EXPECT_NE((void*)datetime, (void*)NULL);       

  datetime->SetToZero();

  datetime->SetDay(31);
  datetime->SetMonth(12);
  datetime->SetYear(2000);
  datetime->SetHours(11);
  datetime->SetMinutes(59);
  datetime->SetSeconds(59);
  datetime->SetMilliSeconds(100);

  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, string);
  EXPECT_EQ(string.Compare(__L("31/12/2000 11:59:59")), 0);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringStandardMilliSeconds)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeToStringStandardMilliSeconds
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringStandardMilliSeconds)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;  

  EXPECT_NE((void*)datetime, (void*)NULL);       

  datetime->SetToZero();

  datetime->SetDay(31);
  datetime->SetMonth(12);
  datetime->SetYear(2000);
  datetime->SetHours(11);
  datetime->SetMinutes(59);
  datetime->SetSeconds(59);
  datetime->SetMilliSeconds(100);

  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS, string);
  EXPECT_EQ(string.Compare(__L("31/12/2000 11:59:59.100")), 0);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringISO8601Standard)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeToStringISO8601Standard
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringISO8601Standard)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;  

  EXPECT_NE((void*)datetime, (void*)NULL);       

  datetime->SetToZero();

  datetime->SetDay(31);
  datetime->SetMonth(12);
  datetime->SetYear(2000);
  datetime->SetHours(11);
  datetime->SetMinutes(59);
  datetime->SetSeconds(59);
  datetime->SetMilliSeconds(100);

  datetime->GetDateTimeToStringISO8601(XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS, string);
  EXPECT_EQ(string.Compare(__L("2000-12-31T11:59:59.100Z")), 0);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringStandardAddDay)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeToStringStandardAddDay
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringStandardAddDay)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;  

  EXPECT_NE((void*)datetime, (void*)NULL);       

  datetime->SetToZero();

  datetime->SetDay(31);
  datetime->SetMonth(12);
  datetime->SetYear(2000);
  datetime->SetHours(11);
  datetime->SetMinutes(59);
  datetime->SetSeconds(59);
  datetime->SetMilliSeconds(100);

  datetime->AddDays(1);

  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, string);
  EXPECT_EQ(string.Compare(__L("01/01/2001 11:59:59")), 0);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringStandardMilliSecondsAddDay)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeToStringStandardMilliSecondsAddDay
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringStandardMilliSecondsAddDay)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;  

  EXPECT_NE((void*)datetime, (void*)NULL);       

  datetime->SetToZero();

  datetime->SetDay(31);
  datetime->SetMonth(12);
  datetime->SetYear(2000);
  datetime->SetHours(11);
  datetime->SetMinutes(59);
  datetime->SetSeconds(59);
  datetime->SetMilliSeconds(100);

  datetime->AddDays(1);

  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS, string);
  EXPECT_EQ(string.Compare(__L("01/01/2001 11:59:59.100")), 0);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringISO8601StandardAddDay)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeToStringISO8601StandardAddDay
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringISO8601StandardAddDay)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;  

  EXPECT_NE((void*)datetime, (void*)NULL);       

  datetime->SetToZero();

  datetime->SetDay(31);
  datetime->SetMonth(12);
  datetime->SetYear(2000);
  datetime->SetHours(11);
  datetime->SetMinutes(59);
  datetime->SetSeconds(59);
  datetime->SetMilliSeconds(100);

  datetime->AddDays(1);

  datetime->GetDateTimeToStringISO8601(XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS, string);
  EXPECT_EQ(string.Compare(__L("2001-01-01T11:59:59.100Z")), 0);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringStandard)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeFromStringStandard
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringStandard) 
{  
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;  

  EXPECT_NE((void*)datetime, (void*)NULL);   
    
  string = __L("31/12/2000 11:59:59");
  datetime->SetToZero();
  datetime->GetDateTimeFromString(string, XDATETIME_FORMAT_STANDARD);
  EXPECT_EQ(datetime->GetDay(), 31);
  EXPECT_EQ(datetime->GetMonth(), 12);
  EXPECT_EQ(datetime->GetYear(), 2000);
  EXPECT_EQ(datetime->GetHours(), 11);
  EXPECT_EQ(datetime->GetMinutes(), 59);
  EXPECT_EQ(datetime->GetSeconds(), 59);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringStandarMilliSeconds)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeFromStringStandarMilliSeconds
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringStandarMilliSeconds) 
{  
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;  
  
  EXPECT_NE((void*)datetime, (void*)NULL);   
      
  string = __L("31/12/2000 11:59:59.100");
  datetime->SetToZero();
  datetime->GetDateTimeFromString(string, XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS);
  EXPECT_EQ(datetime->GetDay(), 31);
  EXPECT_EQ(datetime->GetMonth(), 12);
  EXPECT_EQ(datetime->GetYear(), 2000);
  EXPECT_EQ(datetime->GetHours(), 11);
  EXPECT_EQ(datetime->GetMinutes(), 59);
  EXPECT_EQ(datetime->GetSeconds(), 59);
  EXPECT_EQ(datetime->GetMilliSeconds(), 100);
  
  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringISO8601Standard)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeFromStringISO8601Standard
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringISO8601Standard) 
{  
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;  
  
  EXPECT_NE((void*)datetime, (void*)NULL);   
      
  string = __L("2000-12-31T11:59:59.100");
  datetime->SetToZero();
  datetime->GetDateTimeFromStringISO8601(string, XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS);
  EXPECT_EQ(datetime->GetDay(), 31);
  EXPECT_EQ(datetime->GetMonth(), 12);
  EXPECT_EQ(datetime->GetYear(), 2000);
  EXPECT_EQ(datetime->GetHours(), 11);
  EXPECT_EQ(datetime->GetMinutes(), 59);
  EXPECT_EQ(datetime->GetSeconds(), 59);
  EXPECT_EQ(datetime->GetMilliSeconds(), 100);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringStandard2)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeFromStringStandard2
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringStandard2) 
{  
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string; 
 
  EXPECT_NE((void*)datetime, (void*)NULL);   
    
  string = __L("01/01/2001 11:59:59");
  datetime->SetToZero();
  datetime->GetDateTimeFromString(string, XDATETIME_FORMAT_STANDARD);
  EXPECT_EQ(datetime->GetDay(), 1);
  EXPECT_EQ(datetime->GetMonth(), 1);
  EXPECT_EQ(datetime->GetYear(), 2001);
  EXPECT_EQ(datetime->GetHours(), 11);
  EXPECT_EQ(datetime->GetMinutes(), 59);
  EXPECT_EQ(datetime->GetSeconds(), 59);
 
  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringStandardMilliSeconds2)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeFromStringStandardMilliSeconds2
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringStandardMilliSeconds2) 

{  
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;  

  EXPECT_NE((void*)datetime, (void*)NULL);   

  string = __L("01/01/2001 11:59:59.100");
  datetime->SetToZero();
  datetime->GetDateTimeFromString(string, XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS);
  EXPECT_EQ(datetime->GetDay(), 1);
  EXPECT_EQ(datetime->GetMonth(), 1);
  EXPECT_EQ(datetime->GetYear(), 2001);
  EXPECT_EQ(datetime->GetHours(), 11);
  EXPECT_EQ(datetime->GetMinutes(), 59);
  EXPECT_EQ(datetime->GetSeconds(), 59);
  EXPECT_EQ(datetime->GetMilliSeconds(), 100);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringISO8601StandardMilliSeconds2)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeFromStringISO8601StandardMilliSeconds2
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringISO8601StandardMilliSeconds2) 
{  
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;  

  EXPECT_NE((void*)datetime, (void*)NULL);   
   
  string = __L("2001-01-01T11:59:59.100");
  datetime->SetToZero();
  datetime->GetDateTimeFromStringISO8601(string, XDATETIME_FORMAT_ISO8601_STANDARD | XDATETIME_FORMAT_TIMEWITHMILLISECONDS);
  EXPECT_EQ(datetime->GetDay(), 1);
  EXPECT_EQ(datetime->GetMonth(), 1);
  EXPECT_EQ(datetime->GetYear(), 2001);
  EXPECT_EQ(datetime->GetHours(), 11);
  EXPECT_EQ(datetime->GetMinutes(), 59);
  EXPECT_EQ(datetime->GetSeconds(), 59);
  EXPECT_EQ(datetime->GetMilliSeconds(), 100);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringStandardDateWithDash)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeToStringStandardDateWithDash
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeToStringStandardDateWithDash)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;

  EXPECT_NE((void*)datetime, (void*)NULL);

  SetKnownDateTime(datetime, 31, 12, 2000, 11, 59, 59, 0);

  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_DATEWITHDASH, string);
  EXPECT_EQ(string.Compare(__L("31-12-2000 11:59:59")), 0);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringStandardDateWithDash)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetDateTimeFromStringStandardDateWithDash
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetDateTimeFromStringStandardDateWithDash)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;

  EXPECT_NE((void*)datetime, (void*)NULL);

  string = __L("31-12-2000 11:59:59");
  datetime->SetToZero();
  datetime->GetDateTimeFromString(string, XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_DATEWITHDASH);
  EXPECT_EQ(datetime->GetDay(), 31);
  EXPECT_EQ(datetime->GetMonth(), 12);
  EXPECT_EQ(datetime->GetYear(), 2000);
  EXPECT_EQ(datetime->GetHours(), 11);
  EXPECT_EQ(datetime->GetMinutes(), 59);
  EXPECT_EQ(datetime->GetSeconds(), 59);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, IsValidDateAndLeapYear)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  IsValidDateAndLeapYear
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, IsValidDateAndLeapYear)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();

  EXPECT_NE((void*)datetime, (void*)NULL);

  SetKnownDateTime(datetime, 29, 2, 2000, 0, 0, 0, 0);
  EXPECT_TRUE(datetime->IsLeapYear());
  EXPECT_TRUE(datetime->IsValidDate());

  SetKnownDateTime(datetime, 29, 2, 2001, 0, 0, 0, 0);
  EXPECT_FALSE(datetime->IsLeapYear());
  EXPECT_FALSE(datetime->IsValidDate());

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, AddSecondsAcrossMidnight)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  AddSecondsAcrossMidnight
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, AddSecondsAcrossMidnight)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;

  EXPECT_NE((void*)datetime, (void*)NULL);

  SetKnownDateTime(datetime, 31, 12, 2000, 23, 59, 59, 0);
  datetime->AddSeconds(1);

  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, string);
  EXPECT_EQ(string.Compare(__L("01/01/2001 00:00:00")), 0);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, SubtractDaysAcrossYear)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  SubtractDaysAcrossYear
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, SubtractDaysAcrossYear)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;

  EXPECT_NE((void*)datetime, (void*)NULL);

  SetKnownDateTime(datetime, 1, 1, 2001, 11, 59, 59, 0);
  datetime->SubtractDays(1);

  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, string);
  EXPECT_EQ(string.Compare(__L("31/12/2000 11:59:59")), 0);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, CopyCompareOperators)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  CopyCompareOperators
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, CopyCompareOperators)
{
  XDATETIME* datetimeA = GEN_XFACTORY.CreateDateTime();
  XDATETIME* datetimeB = GEN_XFACTORY.CreateDateTime();

  EXPECT_NE((void*)datetimeA, (void*)NULL);
  EXPECT_NE((void*)datetimeB, (void*)NULL);

  SetKnownDateTime(datetimeA, 31, 12, 2000, 11, 59, 59, 100);
  datetimeB->SetToZero();

  EXPECT_TRUE(datetimeA->CopyTo(datetimeB));
  EXPECT_TRUE(datetimeB->CopyFrom(datetimeA));

  EXPECT_TRUE((*datetimeA) == (*datetimeB));
  EXPECT_FALSE((*datetimeA) != (*datetimeB));
  EXPECT_EQ(datetimeA->Compare(*datetimeB), 0);

  datetimeB->AddDays(1);

  EXPECT_TRUE((*datetimeA) < (*datetimeB));
  EXPECT_TRUE((*datetimeB) > (*datetimeA));
  EXPECT_TRUE((*datetimeA) <= (*datetimeB));
  EXPECT_TRUE((*datetimeB) >= (*datetimeA));
  EXPECT_NE(datetimeA->Compare(*datetimeB), 0);

  GEN_XFACTORY.DeleteDateTime(datetimeA);
  GEN_XFACTORY.DeleteDateTime(datetimeB);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, IsBetweenInclusive)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  IsBetweenInclusive
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, IsBetweenInclusive)
{
  XDATETIME* start   = GEN_XFACTORY.CreateDateTime();
  XDATETIME* middle  = GEN_XFACTORY.CreateDateTime();
  XDATETIME* end     = GEN_XFACTORY.CreateDateTime();

  EXPECT_NE((void*)start,  (void*)NULL);
  EXPECT_NE((void*)middle, (void*)NULL);
  EXPECT_NE((void*)end,    (void*)NULL);

  SetKnownDateTime(start,  1,  1, 2001, 0, 0, 0, 0);
  SetKnownDateTime(middle, 2,  1, 2001, 0, 0, 0, 0);
  SetKnownDateTime(end,    3,  1, 2001, 0, 0, 0, 0);

  EXPECT_TRUE(middle->IsBetween(*start, *end));
  EXPECT_TRUE(start->IsBetween(*start, *end));
  EXPECT_TRUE(end->IsBetween(*start, *end));

  middle->AddDays(2);
  EXPECT_FALSE(middle->IsBetween(*start, *end));

  GEN_XFACTORY.DeleteDateTime(start);
  GEN_XFACTORY.DeleteDateTime(middle);
  GEN_XFACTORY.DeleteDateTime(end);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, AddMonthsAndAddYears)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  AddMonthsAndAddYears
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, AddMonthsAndAddYears)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;

  EXPECT_NE((void*)datetime, (void*)NULL);

  SetKnownDateTime(datetime, 31, 12, 2000, 11, 59, 59, 0);
  datetime->AddMonths(12);

  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, string);
  EXPECT_EQ(string.Compare(__L("31/12/2001 11:59:59")), 0);

  datetime->AddYears(1);
  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, string);
  EXPECT_EQ(string.Compare(__L("31/12/2002 11:59:59")), 0);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, IsZeroAndZeroSetters)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  IsZeroAndZeroSetters
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, IsZeroAndZeroSetters)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();

  EXPECT_NE((void*)datetime, (void*)NULL);

  datetime->SetToZero();
  EXPECT_TRUE(datetime->IsZero());

  // Milliseconds are not considered by IsZero()
  datetime->SetMilliSeconds(123);
  EXPECT_TRUE(datetime->IsZero());

  datetime->SetSeconds(1);
  EXPECT_FALSE(datetime->IsZero());

  datetime->SetToZero();
  SetKnownDateTime(datetime, 31, 12, 2000, 11, 59, 59, 100);

  datetime->SetDateToZero();
  EXPECT_EQ(datetime->GetYear(), 0);
  EXPECT_EQ(datetime->GetMonth(), 0);
  EXPECT_EQ(datetime->GetDay(), 0);
  EXPECT_FALSE(datetime->IsZero());

  datetime->SetHourToZero();
  EXPECT_EQ(datetime->GetHours(), 0);
  EXPECT_EQ(datetime->GetMinutes(), 0);
  EXPECT_EQ(datetime->GetSeconds(), 0);
  EXPECT_EQ(datetime->GetMilliSeconds(), 0);
  EXPECT_TRUE(datetime->IsZero());

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, IsLocalFlag)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  IsLocalFlag
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, IsLocalFlag)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();

  EXPECT_NE((void*)datetime, (void*)NULL);

  // Default value comes from internal Clean() implementation.
  EXPECT_FALSE(datetime->IsLocal());

  datetime->SetIsLocal(true);
  EXPECT_TRUE(datetime->IsLocal());

  datetime->SetIsLocal(false);
  EXPECT_FALSE(datetime->IsLocal());

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, DaysOfYearAndDayOfYearRelation)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  DaysOfYearAndDayOfYearRelation
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, DaysOfYearAndDayOfYearRelation)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();

  EXPECT_NE((void*)datetime, (void*)NULL);

  SetKnownDateTime(datetime,  1,  1, 2001, 0, 0, 0, 0);
  EXPECT_EQ(datetime->GetDaysOfYear(), 0);
  EXPECT_EQ(datetime->GetDayOfYear(),  1);
  EXPECT_EQ(datetime->GetDaysOfYear(), (datetime->GetDayOfYear() - 1));

  // Leap year check (year 2000 is leap): Dec 31 is day 366, but "days of year" is 0-based.
  SetKnownDateTime(datetime, 31, 12, 2000, 0, 0, 0, 0);
  EXPECT_EQ(datetime->GetDayOfYear(),  366);
  EXPECT_EQ(datetime->GetDaysOfYear(), 365);
  EXPECT_EQ(datetime->GetDaysOfYear(), (datetime->GetDayOfYear() - 1));

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, GetSecondsFromADay)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  GetSecondsFromADay
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, GetSecondsFromADay)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();

  EXPECT_NE((void*)datetime, (void*)NULL);

  datetime->SetToZero();
  datetime->SetHours(1);
  datetime->SetMinutes(2);
  datetime->SetSeconds(3);

  EXPECT_EQ(datetime->GetSecondsFromADay(), (XDWORD)(1*3600 + 2*60 + 3));

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, NDdaysRoundTripGregorianAndJulian)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  NDdaysRoundTripGregorianAndJulian
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, NDdaysRoundTripGregorianAndJulian)
{
  XDATETIME* datetimeA = GEN_XFACTORY.CreateDateTime();
  XDATETIME* datetimeB = GEN_XFACTORY.CreateDateTime();

  EXPECT_NE((void*)datetimeA, (void*)NULL);
  EXPECT_NE((void*)datetimeB, (void*)NULL);

  SetKnownDateTime(datetimeA, 15, 6, 2020, 0, 0, 0, 0);

  // Gregorian round-trip
  datetimeB->SetToZero();
  datetimeB->GetDateFromNDays(datetimeA->GetNDaysInGregorian(), false);
  EXPECT_EQ(datetimeB->GetDay(),   datetimeA->GetDay());
  EXPECT_EQ(datetimeB->GetMonth(), datetimeA->GetMonth());
  EXPECT_EQ(datetimeB->GetYear(),  datetimeA->GetYear());

  // Julian round-trip
  datetimeB->SetToZero();
  datetimeB->GetDateFromNDays(datetimeA->GetNDaysInJulian(), true);
  EXPECT_EQ(datetimeB->GetDay(),   datetimeA->GetDay());
  EXPECT_EQ(datetimeB->GetMonth(), datetimeA->GetMonth());
  EXPECT_EQ(datetimeB->GetYear(),  datetimeA->GetYear());

  GEN_XFACTORY.DeleteDateTime(datetimeA);
  GEN_XFACTORY.DeleteDateTime(datetimeB);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, SecondsRoundTripGregorian)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  SecondsRoundTripGregorian
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, SecondsRoundTripGregorian)
{
  XDATETIME* datetimeA = GEN_XFACTORY.CreateDateTime();
  XDATETIME* datetimeB = GEN_XFACTORY.CreateDateTime();

  EXPECT_NE((void*)datetimeA, (void*)NULL);
  EXPECT_NE((void*)datetimeB, (void*)NULL);

  SetKnownDateTime(datetimeA, 31, 12, 2000, 11, 59, 59, 0);

  XQWORD allseconds = datetimeA->GetSeconsFromDate(false);

  datetimeB->SetToZero();
  datetimeB->SetDateFromSeconds(allseconds, false);

  EXPECT_EQ(datetimeB->GetDay(),     datetimeA->GetDay());
  EXPECT_EQ(datetimeB->GetMonth(),   datetimeA->GetMonth());
  EXPECT_EQ(datetimeB->GetYear(),    datetimeA->GetYear());
  EXPECT_EQ(datetimeB->GetHours(),   datetimeA->GetHours());
  EXPECT_EQ(datetimeB->GetMinutes(), datetimeA->GetMinutes());
  EXPECT_EQ(datetimeB->GetSeconds(), datetimeA->GetSeconds());

  GEN_XFACTORY.DeleteDateTime(datetimeA);
  GEN_XFACTORY.DeleteDateTime(datetimeB);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, IsTheSameDay)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  IsTheSameDay
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, IsTheSameDay)
{
  XDATETIME* datetimeA = GEN_XFACTORY.CreateDateTime();
  XDATETIME* datetimeB = GEN_XFACTORY.CreateDateTime();

  EXPECT_NE((void*)datetimeA, (void*)NULL);
  EXPECT_NE((void*)datetimeB, (void*)NULL);

  SetKnownDateTime(datetimeA, 31, 12, 2000, 11,  0,  0, 0);
  SetKnownDateTime(datetimeB, 31, 12, 2000, 23, 59, 59, 0);

  EXPECT_TRUE(datetimeA->IsTheSameDay(datetimeB));
  EXPECT_TRUE(datetimeB->IsTheSameDay(datetimeA));

  datetimeB->AddDays(1);
  EXPECT_FALSE(datetimeA->IsTheSameDay(datetimeB));

  GEN_XFACTORY.DeleteDateTime(datetimeA);
  GEN_XFACTORY.DeleteDateTime(datetimeB);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, SubtractSecondsAcrossMidnight)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  SubtractSecondsAcrossMidnight
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, SubtractSecondsAcrossMidnight)
{
  XDATETIME* datetime = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;

  EXPECT_NE((void*)datetime, (void*)NULL);

  SetKnownDateTime(datetime, 1, 1, 2001, 0, 0, 0, 0);
  datetime->SubtractSeconds(1);

  datetime->GetDateTimeToString(XDATETIME_FORMAT_STANDARD, string);
  EXPECT_EQ(string.Compare(__L("31/12/2000 23:59:59")), 0);

  GEN_XFACTORY.DeleteDateTime(datetime);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XDATETIME_CLASSNAME, StringFormatsPostgreSQLAndFirstTime)
* @brief      Unit test of UNITTEST_XDATETIME_CLASSNAME:  StringFormatsPostgreSQLAndFirstTime
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XDATETIME_CLASSNAME, StringFormatsPostgreSQLAndFirstTime)
{
  XDATETIME* datetimeA = GEN_XFACTORY.CreateDateTime();
  XDATETIME* datetimeB = GEN_XFACTORY.CreateDateTime();
  XSTRING    string;

  EXPECT_NE((void*)datetimeA, (void*)NULL);
  EXPECT_NE((void*)datetimeB, (void*)NULL);

  SetKnownDateTime(datetimeA, 31, 12, 2000, 11, 59, 59, 0);

  // PostgreSQL format (Y/M/D)
  datetimeA->GetDateTimeToString(XDATETIME_FORMAT_POSTGRESQL, string);
  EXPECT_EQ(string.Compare(__L("2000/12/31 11:59:59")), 0);

  datetimeB->SetToZero();
  EXPECT_TRUE(datetimeB->GetDateTimeFromString(string, XDATETIME_FORMAT_POSTGRESQL));
  EXPECT_TRUE((*datetimeA) == (*datetimeB));

  // Date only (DMY)
  datetimeA->GetDateTimeToString(XDATETIME_FORMAT_DMY, string);
  EXPECT_EQ(string.Compare(__L("31/12/2000")), 0);

  datetimeB->SetToZero();
  EXPECT_TRUE(datetimeB->GetDateTimeFromString(string, XDATETIME_FORMAT_DMY));
  EXPECT_EQ(datetimeB->GetDay(),   31);
  EXPECT_EQ(datetimeB->GetMonth(), 12);
  EXPECT_EQ(datetimeB->GetYear(),  2000);

  // First time (time + date)
  datetimeA->GetDateTimeToString(XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_FIRSTTIME, string);
  EXPECT_EQ(string.Compare(__L("11:59:59 31/12/2000")), 0);

  datetimeB->SetToZero();
  EXPECT_TRUE(datetimeB->GetDateTimeFromString(string, XDATETIME_FORMAT_STANDARD | XDATETIME_FORMAT_FIRSTTIME));
  EXPECT_TRUE((*datetimeA) == (*datetimeB));

  GEN_XFACTORY.DeleteDateTime(datetimeA);
  GEN_XFACTORY.DeleteDateTime(datetimeB);
}


}
#endif


#pragma endregion
