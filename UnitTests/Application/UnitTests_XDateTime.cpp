/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UnitTests_XDateTime.cpp
* 
* @class      UNITTESTS_XDATETIME
* @brief      Unit Tests for XDateTime class
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

#include "UnitTests_XDateTime.h"

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


}
#endif


#pragma endregion

