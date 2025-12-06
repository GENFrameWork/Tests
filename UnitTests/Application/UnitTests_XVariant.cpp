/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UnitTests_XVariant.cpp
* 
* @class      UNITTESTS_XVARIANT
* @brief      Unit Tests for XVariant class
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

#include "UnitTests_XVariant.h"

#include "string.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XBuffer.h"
#include "XVariant.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

#define UNITTEST_XVARIANT_CONSTRUCTOR(type, value)            { XVARIANT variant((type)value); \
                                                                EXPECT_EQ((type)value, (type)variant); \
                                                              }

#define UNITTEST_XVARIANT_CONVERTSTRING(type, value)          { XVARIANT variant((type)value); \
                                                                XVARIANT variant2; \
                                                                XSTRING  string; \
                                                                type value2; \
                                                                variant.ToString(string); \
                                                                variant2.FromString(string); \
                                                                value2 = (type)variant2; \
                                                                EXPECT_EQ((type)value, (type)value2); \
                                                              }

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS



#ifdef GOOGLETEST_ACTIVE      
namespace TEST_XVARIANT
{


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignBool)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignBool
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignBool) 
{
  UNITTEST_XVARIANT_CONSTRUCTOR(bool, true);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignShort)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignShort
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignShort) 
{
  UNITTEST_XVARIANT_CONSTRUCTOR(short, -12345); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignWord)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignWord) 
{
  UNITTEST_XVARIANT_CONSTRUCTOR(XWORD, 12345); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignInt)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignInt
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignInt) 
{ 
  UNITTEST_XVARIANT_CONSTRUCTOR(int, -1234567890);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignDWord)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignDWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignDWord) 
{
  UNITTEST_XVARIANT_CONSTRUCTOR(XDWORD, 1234567890);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignLongLong)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignLongLong
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignLongLong) 
{
  UNITTEST_XVARIANT_CONSTRUCTOR(long long, -1234567890123445);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignQWord)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignQWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignQWord) 
{
  UNITTEST_XVARIANT_CONSTRUCTOR(XQWORD, 1234567890123445); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignFloat)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignFloat
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignFloat) 
{
  UNITTEST_XVARIANT_CONSTRUCTOR(float, -123.456f); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignDouble)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignDouble
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignDouble) 
{
  UNITTEST_XVARIANT_CONSTRUCTOR(double, -123456.78787f);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignChar)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignChar
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignChar) 
{
  UNITTEST_XVARIANT_CONSTRUCTOR(char, 'A');  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignXChar)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignXChar
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignXChar) 
{  
  UNITTEST_XVARIANT_CONSTRUCTOR(XCHAR, __C('A')); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignCharPtr)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignCharPtr
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignCharPtr) 
{   
  char*       value  = (char*)"Hello Word!";
  XVARIANT    variant(value);
  char*       value2 = value;

  EXPECT_EQ(strcmp(value, value2), 0);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignXCharPtr)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignXCharPtr
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignXCharPtr) 
{   
  XCHAR*    value  = __L("Hello Word!");
  XVARIANT  variant(value);
  XSTRING   value2 = variant;
  
  EXPECT_EQ(value2.Compare(value, true), 0);      
}  
  

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignDateTime)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignDateTime
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignDateTime) 
{   
  XSTRING   datetimestr = __L("01/12/1969 12:30:30");
  XSTRING   datetimestr2;
  XDATETIME value;

  value.GetDateTimeFromString(datetimestr, XDATETIME_FORMAT_STANDARD);

  XVARIANT  variant(value);
  XDATETIME value2 = variant;

  value2.GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datetimestr2);
  EXPECT_EQ(datetimestr.Compare(datetimestr2, true), 0);
}
    

/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignDWord2)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignDWord2
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignDWord2)    
{ 
  XVARIANT value = (XDWORD)0x1234;

  UNITTEST_XVARIANT_CONSTRUCTOR(XDWORD, value);  
}  


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignPointer)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssignPointer
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssignPointer)  
{ 
  void*     value = (void*)0x12345678;
  XVARIANT  variant(value);
  void*     value2; 

  value2 = variant; 

  EXPECT_EQ(value, value2); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionBool)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionBool
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionBool) 
{
  UNITTEST_XVARIANT_CONVERTSTRING(bool, true);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionShort)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionShort
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionShort) 
{
  UNITTEST_XVARIANT_CONVERTSTRING(short, -12345);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionWord)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionWord) 
{
  UNITTEST_XVARIANT_CONVERTSTRING(XWORD, 12345);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionInt)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionInt
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionInt) 
{
  UNITTEST_XVARIANT_CONVERTSTRING(int, -1234567890);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionDWord)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionDWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionDWord) 
{
  UNITTEST_XVARIANT_CONVERTSTRING(XDWORD, 1234567890);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionLongLong)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionLongLong
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionLongLong) 
{
  UNITTEST_XVARIANT_CONVERTSTRING(long long, -1234567890123445);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionQWord)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionQWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionQWord) 
{
  UNITTEST_XVARIANT_CONVERTSTRING(XQWORD, 1234567890123445);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionFloat)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionFloat
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionFloat) 
{
  float       value = AdjustFloat(-12.1234f, 4);
  XVARIANT    variant(value); 
  XVARIANT    variant2; 
  XSTRING     string; 
  float       value2; 

  variant.ToString(string); 
  variant2.FromString(string); 
  value2 = AdjustFloat((float)variant2, 4);

  EXPECT_EQ((float)value, (float)value2); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionDouble)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionDouble
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionDouble) 
{ 
  double      value = AdjustDouble(-12.12345678f, 6);
  XVARIANT    variant(value); 
  XVARIANT    variant2; 
  XSTRING     string; 
  double      value2; 

  variant.ToString(string); 
  variant2.FromString(string); 
  value2 = AdjustDouble((double)variant2, 6);

  EXPECT_EQ((double)value, (double)value2); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionChar)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionChar
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionChar) 
{ 
  char        value = 'A';
  XVARIANT    variant(value); 
  XVARIANT    variant2; 
  XSTRING     string; 
  char        value2; 

  variant.ToString(string); 
  variant2.FromString(string, XVARIANT_TYPE_CHAR); 
  value2 = (char)variant2;

  EXPECT_EQ((char)value, (char)value2); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionCharPtr)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionCharPtr
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionCharPtr) 
{   
  const char* value = (char*)"Hello Word!";
  XVARIANT    variant(value);
  XVARIANT    variant2; 
  XSTRING     string;
  XSTRING     value2;

  variant.ToString(string);
  variant2.FromString(string); 
  
  value2 = (const XSTRING&)variant2;
  
  EXPECT_EQ(value2.Compare(value, true), 0);    
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionXChar)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionXChar
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionXChar) 
{ 
  XCHAR       value = __C('A');
  XVARIANT    variant(value); 
  XVARIANT    variant2; 
  XSTRING     string; 
  XCHAR       value2; 

  variant.ToString(string); 
  variant2.FromString(string, XVARIANT_TYPE_XCHAR); 
  value2 = (XCHAR)variant2;

  EXPECT_EQ((XCHAR)value, (XCHAR)value2); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionXCharPtr)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionXCharPtr
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionXCharPtr) 
{  
  XSTRING     value;

  value.Add(__L("Hello Word!"));

  XVARIANT    variant(value);
  XVARIANT    variant2; 
  XSTRING     string;
  XSTRING     value2;

  variant.ToString(string);
  variant2.FromString(string, XVARIANT_TYPE_STRING); 
  
  value2 = (const XSTRING&)variant2;

  EXPECT_EQ(value2.Compare(value, true), 0);    
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionDateTime)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionDateTime
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionDateTime)   
{   
  XSTRING     datetimestr = __L("01/12/1969 12:30:30");
  XDATETIME   value;

  value.GetDateTimeFromString(datetimestr, XDATETIME_FORMAT_STANDARD);

  XVARIANT    variant(value);
  XVARIANT    variant2; 
  XSTRING     string;    
  XDATETIME   value2;

  variant.ToString(string);
  variant2.FromString(string, XVARIANT_TYPE_DATETIME); 

  value2 = variant2;

  EXPECT_EQ(value2.Compare(value), 0);              
}

  
/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionBuffer)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  StringConversionBuffer
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, StringConversionBuffer) 
{ 
  XBUFFER     value;

  value.Add((XBYTE)0xAA);
  value.Add((XBYTE)0x55);
  value.Add((XBYTE)0xCA);
  value.Add((XBYTE)0xFE);
  value.Add((XBYTE)0x02);
  value.Add((XBYTE)0x9A);

  XVARIANT    variant(value);
  XVARIANT    variant2; 
  XSTRING     string;  
  XBUFFER     value2;  
  
  variant.ToString(string);
  variant2.FromString(string, XVARIANT_TYPE_BUFFER); 

  value2 = variant2;
 
  EXPECT_EQ(value2.Compare(value), true);            
}

}


#endif


#pragma endregion

