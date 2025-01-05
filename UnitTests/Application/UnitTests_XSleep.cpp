/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UnitTests_XSleep.cpp
* 
* @class      UNITTESTS_XSLEEP
* @brief      Unit Tests for XSleep class
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

#include "UnitTests_XSleep.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XSleep.h"
#include "XTimer.h"

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
namespace TEST_XSLEEP
{


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSLEEP_CLASSNAME, Seconds)
* @brief      Unit test of UNITTEST_XSLEEP_CLASSNAME:  Seconds
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSLEEP_CLASSNAME, Seconds)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_NE(xtimer, nullptr);
  
  GEN_XSLEEP.Seconds(2);                                

  EXPECT_GE(xtimer->GetMeasureSeconds(), 2);

  GEN_XFACTORY.DeleteTimer(xtimer);
 }


/**-------------------------------------------------------------------------------------------------------------------

@fn         TEST(UNITTEST_XSLEEP_CLASSNAME, Miliseconds)
@brief      Unit test of UNITTEST_XSLEEP_CLASSNAME:  Miliseconds
@ingroup    UNIT TEST

@return     Does not return anything. 

--------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSLEEP_CLASSNAME, Miliseconds)
{
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  EXPECT_NE(xtimer, nullptr);

  GEN_XSLEEP.MilliSeconds(2000);

  EXPECT_GE(xtimer->GetMeasureMilliSeconds(),2000);

  GEN_XFACTORY.DeleteTimer(xtimer);
}

}
#endif


#pragma endregion

