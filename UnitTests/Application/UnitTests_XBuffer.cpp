/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTest_XBuffer.cpp
*
* @class      
* @brief      Unit Tests for XBuffer class (GEN FrameWork)
* @ingroup    TESTS
*
* @copyright  GEN Group. All right reserved.
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
*---------------------------------------------------------------------------------------------------------------------*/


/*---- PRECOMPILATION CONTROL ----------------------------------------------------------------------------------------*/

#include "GEN_Defines.h"


/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XString.h"
#include "XBuffer.h"
#include "XVariant.h"

#include "UnitTests_XBuffer.h"

#include "XMemory_Control.h"


#ifdef GOOGLETEST_ACTIVE      
namespace test_XBuffer
{

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


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
* @fn         TEST(UNITTEST_XBuffer_CLASSNAME, Add)
* @brief      Unit test of UNITTEST_XBuffer_CLASSNAME:  Add
* @ingroup    UNIT TEST
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, Add)
{
  XBUFFER buffer;

  buffer.Add((bool)true);
  EXPECT_EQ(1,buffer.GetSize());
  buffer.Empty();

  buffer.Add((XBYTE)1);
  EXPECT_EQ(1, buffer.GetSize());
  buffer.Empty();

  buffer.Add((XWORD)16);
  EXPECT_EQ(2, buffer.GetSize());
  buffer.Empty();

  buffer.Add((float)1.3);
  EXPECT_EQ(4, buffer.GetSize());
  buffer.Empty();

  buffer.Add((XDWORD)32);
  EXPECT_EQ(4, buffer.GetSize());
  buffer.Empty();

  buffer.Add((XQWORD)64);
  EXPECT_EQ(8, buffer.GetSize());
  buffer.Empty();  
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTEST_XBuffer_CLASSNAME, Get)
* @brief      Unit test of UNITTEST_XBuffer_CLASSNAME:  Get
* @ingroup    UNIT TEST
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, Get)
{
  XBUFFER buffer;
  XBYTE   byte = 0;
  XWORD   xword = 0;
  XDWORD  xdword = 0;
  XQWORD  xqword= 0;
  float   i;
 
  buffer.Add((bool)true);
  buffer.Get((XBYTE&)byte, 0);

  EXPECT_EQ(byte, true);
  EXPECT_EQ(1, buffer.GetSize());
  buffer.Empty();

  buffer.Add((XBYTE)50);
  buffer.Get((XBYTE&)byte, 0);
  
  EXPECT_EQ(byte, 50);
  EXPECT_EQ(1, buffer.GetSize());
  buffer.Empty();
 
  buffer.Add((XWORD)16);
  buffer.Get((XWORD&)xword, 0);

  EXPECT_EQ(xword, 16);
  EXPECT_EQ(2, buffer.GetSize());
  buffer.Empty();


  buffer.Add((float)1.6);
  buffer.Get((float&)i, 0);

  EXPECT_EQ(4, buffer.GetSize());
  buffer.Empty();


  buffer.Add((XDWORD)32);
  buffer.Get((XDWORD&)xdword, 0);

  EXPECT_EQ(xdword, 32);
  EXPECT_EQ(4, buffer.GetSize());
  buffer.Empty();


  buffer.Add((XQWORD)64);
  buffer.Get((XQWORD&)xqword, 0);

  EXPECT_EQ(xqword, 64);
  EXPECT_EQ(8, buffer.GetSize());
  buffer.Empty();   
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTEST_XBuffer_CLASSNAME, Extract)
* @brief      Unit test of UNITTEST_XBuffer_CLASSNAME:  Extract
* @ingroup    UNIT TEST
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XBUFFER_CLASSNAME, Extract)
{
  XBUFFER buffer;
  XBYTE byte;
  XWORD   xword = 0;
  XDWORD  xdword = 0;
  XQWORD  xqword = 0;
  float   i;


  buffer.Add((bool)1);
  buffer.Extract((XBYTE&)byte, 0);

  EXPECT_EQ(byte, 1);
  EXPECT_EQ(0, buffer.GetSize());


  buffer.Add((XBYTE)30);
  buffer.Extract((XBYTE&)byte, 0);

  EXPECT_EQ(byte, 30);
  EXPECT_EQ(0, buffer.GetSize());


  buffer.Add((XWORD)16);
  buffer.Extract((XWORD&)xword,0);

  EXPECT_EQ(xword, 16);
  EXPECT_EQ(0, buffer.GetSize());


  buffer.Add((XDWORD)32);
  buffer.Extract((XDWORD&)xdword, 0);

  EXPECT_EQ(xdword, 32);
  EXPECT_EQ(0, buffer.GetSize());


  buffer.Add((float)1.6);
  buffer.Extract((float&)i, 0);

  EXPECT_EQ(0, buffer.GetSize());


  buffer.Add((XQWORD)64);
  buffer.Extract((XQWORD&)xqword, 0);

  EXPECT_EQ(xqword, 64);
  EXPECT_EQ(0, buffer.GetSize());
  
}

}
#endif