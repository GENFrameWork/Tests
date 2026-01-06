/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XUtils_UnitTests_XBase.cpp
* 
* @class      XUTILS_UNITTESTS_XBASE
* @brief      Unit Tests for XBase functions and defines
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

#include "XUtils_UnitTests_XBase.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XBase.h"

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
namespace TEST_XBASE
{


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBASE_CLASSNAME, DecimalNumbers)
* @brief      Unit test of UNITTEST_XBASE_CLASSNAME:  DecimalNumbers
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBASE_CLASSNAME, DecimalNumbers) 
{
  float  float1  = 0.0f;
  float  float2  = 0.0f;
  double double1 = 0.0f;
  double double2 = 0.0f;

  double1 = Truncate(1.03f);  
  EXPECT_EQ(1.0f, double1);

  double1 = Fraction(1.123f);  
  double1 = AdjustDouble(double1, 3);
  double2 = AdjustDouble(0.123f, 3);
  EXPECT_EQ(double1, double2);
 
  float1 = (float)RoundOff(1.123f, 1);
  float1 = AdjustFloat(float1, 3);
  float2 = AdjustFloat(1.1f, 3);
  EXPECT_EQ(float1, float2);
  
  double1 = (double)RoundOff(1.123f, 1);
  double1 = AdjustDouble(double1, 3);
  double2 = AdjustDouble(1.1f, 3);
  EXPECT_EQ(double1, double2);

  float1 = (float)RoundFloat(1.123f);
  float1 = AdjustFloat(float1, 3);
  float2 = AdjustFloat(1.0f, 3);
  EXPECT_EQ(float1, float2);  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBASE_CLASSNAME, BitPart)
* @brief      Unit test of UNITTEST_XBASE_CLASSNAME:  BitPart
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBASE_CLASSNAME, BitPart) 
{
  XBYTE    byte  = 0;
  XWORD    word  = 0;
  XDWORD   dword = 0;
  
  byte = HighWORD(0x1234);
  EXPECT_EQ(0x12, byte); 

  word = HighDWORD(0x12345678);
  EXPECT_EQ(0x1234, word); 

  dword = HighQWORD(0x123456789ABCDEF0);
  EXPECT_EQ(0x12345678, dword); 

  byte = LowWORD(0x1234);
  EXPECT_EQ(0x34, byte); 

  word = LowDWORD(0x12345678);
  EXPECT_EQ(0x5678, word); 

  dword = LowQWORD(0x123456789ABCDEF0);
  EXPECT_EQ(0x9ABCDEF0, dword); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBASE_CLASSNAME, BitPart)
* @brief      Unit test of UNITTEST_XBASE_CLASSNAME:  BitPart
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBASE_CLASSNAME, BitSwap) 
{
  XWORD    word  = 0;
  XDWORD   dword = 0;
  XQWORD   qword = 0;

  word  = SwapWORD(0x1234);
  EXPECT_EQ(0x3412, word); 

  dword = SwapDWORD(0x12345678);
  EXPECT_EQ(0x78563412, dword); 

  qword = SwapQWORD(0x1234567890ABCDF0);
  EXPECT_EQ(0xF0CDAB9078563412, qword); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBASE_CLASSNAME, InvertSign)
* @brief      Unit test of UNITTEST_XBASE_CLASSNAME:  InvertSign
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBASE_CLASSNAME, InvertSign) 
{
  int number = InvertSign(-12345);
  EXPECT_EQ(12345, number); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBASE_CLASSNAME, NumberBCD)
* @brief      Unit test of UNITTEST_XBASE_CLASSNAME:  NumberBCD
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBASE_CLASSNAME, NumberBCD) 
{
  XQWORD number1 = DWORDToBCD(12345678);
  EXPECT_EQ(305419896, number1); 

  XDWORD number2 = BCDToDWORD(number1);
  EXPECT_EQ(12345678, number2); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBASE_CLASSNAME, RotateBits)
* @brief      Unit test of UNITTEST_XBASE_CLASSNAME:  RotateBits
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBASE_CLASSNAME, RotateBits) 
{
  XBYTE byte1 = RotateBitLeft(0xAA);
  EXPECT_EQ(0x55, byte1); 

  XBYTE byte2 = RotateBitRight(0x55);
  EXPECT_EQ(0xAA, byte2); 

  XBYTE byte3 = RotateBitReverse(0x11);
  EXPECT_EQ(0x88, byte3);   
}


}


#pragma endregion

#endif



