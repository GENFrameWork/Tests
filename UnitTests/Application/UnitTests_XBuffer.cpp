/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UnitTests_XBuffer.cpp
* 
* @class      UNITTESTS_XBUFFER
* @brief      Unit Tests for XBuffer class
* @ingroup    TESTS
* 
* @copyright  GEN Group. All rights reserved.
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

#include "UnitTests_XBuffer.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XString.h"
#include "XBuffer.h"
#include "XVariant.h"

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
namespace TEST_XBUFFER
{


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBuffer_CLASSNAME, ConstructorSize)
* @brief      Unit test of UNITTEST_XBuffer_CLASSNAME:  ConstructorSize
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, ConstructorSize) 
{
  XBUFFER buffer((XDWORD)32);

  EXPECT_EQ(32, buffer.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTEST_XBuffer_CLASSNAME, AddAll)
* @brief      Unit test of UNITTEST_XBuffer_CLASSNAME:  AddAll
* @ingroup    UNIT TEST
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, AddAll)
{
  XBUFFER buffer;

  buffer.Add((bool)true)  ;
  buffer.Add((XBYTE)  1)  ;
  buffer.Add((XWORD) 16)  ;
  buffer.Add((XDWORD)32)  ;
  buffer.Add((XQWORD)64)  ;
  buffer.Add((float)1.3)  ; 

  EXPECT_EQ(20, buffer.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, AddBool)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  AddBool
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, AddBool)
{
  XBUFFER buffer;

  buffer.Add((bool)true);
  EXPECT_EQ(1,buffer.GetSize());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, AddByte)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  AddByte
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, AddByte)
{
  XBUFFER buffer;
 
  buffer.Add((XBYTE)1);
  EXPECT_EQ(1, buffer.GetSize()); 
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, AddWord)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  AddWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, AddWord)
{
  XBUFFER buffer;

  buffer.Add((XWORD)16);
  EXPECT_EQ(2, buffer.GetSize());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, AddDWord)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  AddDWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, AddDWord)
{
  XBUFFER buffer;

  buffer.Add((XDWORD)32);
  EXPECT_EQ(4, buffer.GetSize());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, AddQWord)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  AddQWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, AddQWord)
{
  XBUFFER buffer;

  buffer.Add((XQWORD)64);
  EXPECT_EQ(8, buffer.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, AddFloat)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  AddFloat
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, AddFloat)
{
  XBUFFER buffer;
  
  buffer.Add((float)1.3);
  EXPECT_EQ(4, buffer.GetSize()); 
}  


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, GetByte)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  GetByte
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, GetByte)
{
  XBUFFER buffer;
  XBYTE   byte = 0;
 
  buffer.Add((bool)true);
  buffer.Get((XBYTE&)byte, 0);

  EXPECT_EQ(byte, true);
  EXPECT_EQ(1, buffer.GetSize());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, GetArrayByte)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  GetArrayByte
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, GetArrayByte)
{
  XBUFFER buffer;
  XBYTE   byte = 0;
 
  buffer.Add((XBYTE)50);
  buffer.Get((XBYTE&)byte, 0);
  
  EXPECT_EQ(byte, 50);
  EXPECT_EQ(1, buffer.GetSize());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, GetWord)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  GetWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, GetWord)
{
  XBUFFER buffer;
  XWORD   xword = 0;
 
  buffer.Add((XWORD)16);
  buffer.Get((XWORD&)xword, 0);

  EXPECT_EQ(xword, 16);
  EXPECT_EQ(2, buffer.GetSize());
  buffer.Empty();
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, GetDWord)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  GetDWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, GetDWord)
{
  XBUFFER buffer;
  XDWORD  xdword = 0;
 
  buffer.Add((XDWORD)32);
  buffer.Get((XDWORD&)xdword, 0);

  EXPECT_EQ(xdword, 32);
  EXPECT_EQ(4, buffer.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, GetQWord)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  GetQWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, GetQWord)
{
  XBUFFER buffer;
  XQWORD  xqword= 0;
    
  buffer.Add((XQWORD)64);
  buffer.Get((XQWORD&)xqword, 0);

  EXPECT_EQ(xqword, 64);
  EXPECT_EQ(8, buffer.GetSize());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, GetFloat)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  GetFloat
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, GetFloat)
{
  XBUFFER buffer; 
  float   i;
 
  buffer.Add((float)1.6);
  buffer.Get((float&)i, 0);

  EXPECT_EQ(4, buffer.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractByte)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  ExtractByte
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractByte)
{
  XBUFFER buffer;
  XBYTE   byte;
  
  buffer.Add((bool)1);
  buffer.Extract((XBYTE&)byte, 0);

  EXPECT_EQ(byte, 1);
  EXPECT_EQ(0, buffer.GetSize());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractArrayByte)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  ExtractArrayByte
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractArrayByte)
{
  XBUFFER buffer;
  XBYTE   byte;

  buffer.Add((XBYTE)30);
  buffer.Extract((XBYTE&)byte, 0);

  EXPECT_EQ(byte, 30);
  EXPECT_EQ(0, buffer.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractWord)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  ExtractWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractWord)
{
  XBUFFER buffer;
  XWORD   xword = 0;

  buffer.Add((XWORD)16);
  buffer.Extract((XWORD&)xword,0);

  EXPECT_EQ(xword, 16);
  EXPECT_EQ(0, buffer.GetSize());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractDWord)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  ExtractDWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractDWord)
{
  XBUFFER buffer;
  XDWORD  xdword = 0;

  buffer.Add((XDWORD)32);
  buffer.Extract((XDWORD&)xdword, 0);

  EXPECT_EQ(xdword, 32);
  EXPECT_EQ(0, buffer.GetSize());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractQWord)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  ExtractQWord
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractQWord)
{
  XBUFFER buffer;
  XQWORD  xqword = 0;
 
  buffer.Add((XQWORD)64);
  buffer.Extract((XQWORD&)xqword, 0);

  EXPECT_EQ(xqword, 64);
  EXPECT_EQ(0, buffer.GetSize());  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractFloat)
* @brief      Unit test of UNITTEST_XBUFFER_CLASSNAME:  ExtractFloat
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, ExtractFloat)
{
  XBUFFER buffer;
  float   i;

  buffer.Add((float)1.6);
  buffer.Extract((float&)i, 0);

  EXPECT_EQ(0, buffer.GetSize());
}


}


#endif


#pragma endregion

