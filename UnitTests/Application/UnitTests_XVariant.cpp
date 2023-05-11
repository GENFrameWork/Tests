/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTest_XVariant.cpp
*
* @class      
* @brief      Unit Tests for XVariant class (GEN FrameWork)
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

#include "string.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XBuffer.h"
#include "XVariant.h"

#include "UnitTests_XVariant.h"

#include "XMemory_Control.h"


#ifdef GOOGLETEST_ACTIVE      
namespace TEST_XVARIANT
{


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

#define UNITTEST_XVARIANT_CONSTRUCTOR(type, value)            { XVARIANT variant((type)value); \
                                                                EXPECT_EQ((type)value, (type)variant); \
                                                              }

#define UNITTEST_XVARIANT_CONSTRUCTOR_STRCMP(type, value)     { XVARIANT variant((type)value); \
                                                                EXPECT_EQ(strcmp((char*)value,(char*)variant), 0);  \
                                                              }

#define UNITTEST_XVARIANT_CONSTRUCTOR_XSTRING(type, value)    { XVARIANT variant(value); \
                                                                XSTRING  string = variant; \
                                                                EXPECT_EQ(string.Compare(value, true), 0); \
                                                              }

/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssign)
* @brief      Unit test of UNITTEST_XVARIANT_CLASSNAME:  ConstructorAssign
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XVARIANT_CLASSNAME, ConstructorAssign) 
{
  UNITTEST_XVARIANT_CONSTRUCTOR(bool, true)

  UNITTEST_XVARIANT_CONSTRUCTOR(short, -12345);

  UNITTEST_XVARIANT_CONSTRUCTOR(XWORD, 12345);

  UNITTEST_XVARIANT_CONSTRUCTOR(int, -1234567890);

  UNITTEST_XVARIANT_CONSTRUCTOR(XDWORD, 1234567890);

  UNITTEST_XVARIANT_CONSTRUCTOR(long long, -1234567890123445);

  UNITTEST_XVARIANT_CONSTRUCTOR(XQWORD, 1234567890123445);

  UNITTEST_XVARIANT_CONSTRUCTOR(float, -123.456f);

  UNITTEST_XVARIANT_CONSTRUCTOR(double, -123456.78787f);

  UNITTEST_XVARIANT_CONSTRUCTOR(XCHAR, __C('A'));

  UNITTEST_XVARIANT_CONSTRUCTOR(XCHAR*, __L("Hello Word!"));

  { XSTRING value = __L("Hello Word!");
    UNITTEST_XVARIANT_CONSTRUCTOR_XSTRING(XSTRING, value);
  }

  UNITTEST_XVARIANT_CONSTRUCTOR_STRCMP(char*, "Hello Word!");

  UNITTEST_XVARIANT_CONSTRUCTOR(char, 'A');    

  { XSTRING datetimestr = __L("01/12/1969 12:30:30");
    XSTRING datetimestr2;
    XDATETIME value;
    value.GetDateTimeFromString(datetimestr, XDATETIME_FORMAT_STANDARD);
    XVARIANT variant(value);
    XDATETIME value2 = variant;
    value2.GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datetimestr2);
    EXPECT_EQ(datetimestr.Compare(datetimestr2, true), 0); 
  }

  { XVARIANT value = (XDWORD)0x1234;
    UNITTEST_XVARIANT_CONSTRUCTOR(XDWORD, value);  
  }      
}


}
#endif
