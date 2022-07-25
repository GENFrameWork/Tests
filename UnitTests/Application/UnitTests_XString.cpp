/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTest_XString.cpp
*
* @class      
* @brief      Unit Tests for XString class (GEN FrameWork)
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

#include "UnitTests_XString.h"

#include "XMemory_Control.h"


#ifdef GOOGLETEST_ACTIVE      
namespace test_xstring
{

/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

char*  unittest_hellostringOEM = (char*)("Hello, world!");
XCHAR* unittest_hellostring    = __L("Hello, world!");

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorSize)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ConstructorSize
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorSize) 
{
  XSTRING string(32);

  EXPECT_EQ(32, string.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssignOEM)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ConstructorAssignOEM
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssignOEM) 
{
  XSTRING string(unittest_hellostringOEM);

  EXPECT_EQ(0, string.Compare(unittest_hellostringOEM, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssign)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ConstructorAssign
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssign) 
{
  XSTRING string(unittest_hellostring);

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssingSize)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ConstructorAssingSize
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssingSize) 
{
  XSTRING string(unittest_hellostring, 13);

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
  EXPECT_EQ(13, string.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssingDirect)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ConstructorAssingDirect
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssingDirect) 
{
  XSTRING string(unittest_hellostring, 13);
  XSTRING string2(string);

  EXPECT_EQ(0, string2.Compare(unittest_hellostring, false));
}  


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, Set)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  Set
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, Set) 
{
  XSTRING string;

  string.Set(unittest_hellostring);

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, Add)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  Add
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, Add) 
{
  XSTRING string;

  string.Add(unittest_hellostring);

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, AssignmentOperator)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  AssignmentOperator
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, AssignmentOperator) 
{
  XSTRING string = unittest_hellostring;

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
}



}
#endif
