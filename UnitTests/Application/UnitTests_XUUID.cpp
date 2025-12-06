/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UnitTests_XUUID.cpp
* 
* @class      UNITTESTS_XUUID
* @brief      Unit Tests for XUUID class
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

#include "UnitTests_XUUID.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XRand.h"
#include "XString.h"
#include "XUUID.h"

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
namespace TEST_XUUID
{


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, SetByNumber1)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  SetByNumber1
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, SetByNumber1) 
{
  XRAND* xrand = GEN_XFACTORY.CreateRand();
  if(!xrand)
    {
      EXPECT_EQ(true, false);
    }

  xrand->Ini();

  XUUID ID[2]; 
  XBYTE data[XUUIDMAXDATA4] = { (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255) };

  ID[0].SetData1((XDWORD)xrand->Max(900000));
  ID[0].SetData2((XDWORD)xrand->Max(900000));
  ID[0].SetData3((XWORD)xrand->Max(10000));
  ID[0].SetData4((XBYTE)xrand->Max(255));
  ID[0].SetData5((XBYTE)xrand->Max(255));
  ID[0].SetData6(data);

  ID[1].SetData1(ID[0].GetData1());
  ID[1].SetData2(ID[0].GetData2());
  ID[1].SetData3(ID[0].GetData3());
  ID[1].SetData4(ID[0].GetData4());
  ID[1].SetData5(ID[0].GetData5());
  ID[1].SetData6(ID[0].GetData6());

  GEN_XFACTORY.DeleteRand(xrand);

  EXPECT_EQ(true, ID[0].Compare(ID[1]));  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, SetByNumber)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  SetByNumber
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, SetByNumber2) 
{
  XRAND* xrand = GEN_XFACTORY.CreateRand();
  if(!xrand)
    {
      EXPECT_EQ(true, false);
    }

  xrand->Ini();

  XUUID ID[2]; 
  XBYTE data[XUUIDMAXDATA4] = { (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255) };

  ID[0].Set((XDWORD)xrand->Max(900000), (XDWORD)xrand->Max(900000), (XWORD)xrand->Max(10000), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), data);
  ID[1].CopyFrom(ID[0]);

  GEN_XFACTORY.DeleteRand(xrand);

  EXPECT_EQ(true, ID[0].Compare(ID[1]));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, AssignByBuffer)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  AssignByBuffer
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, AssignByBuffer) 
{
  XUUID     ID[2]; 
  XBUFFER   IDbuffer[2];

  for(XDWORD c=0; c<UNITTEST_XUUID_NTESTS; c++)
    {
      ID[0].GenerateRandom();
      ID[0].GetToBuffer(IDbuffer[0]);

      ID[1].SetFromBuffer(IDbuffer[0]);
      ID[1].GetToBuffer(IDbuffer[1]);

      EXPECT_EQ(true, IDbuffer[0].Compare(IDbuffer[1]));
    }  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, AssignByString)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  AssignByString
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, AssignByString) 
{
  XUUID     ID[2]; 
  XSTRING   IDstr[2];

  for(XDWORD c=0; c<UNITTEST_XUUID_NTESTS; c++)
    {
      ID[0].GenerateRandom();
      ID[0].GetToString(IDstr[0]);

      ID[1].SetFromString(IDstr[0]);
      ID[1].GetToString(IDstr[1]);

      EXPECT_EQ(0, IDstr[0].Compare(IDstr[1], false));
    }  
}




/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, AssignByCopyTo)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  AssignByCopyTo
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, AssignByCopyTo) 
{
  XUUID     ID[2]; 
  XSTRING   IDstr[2];
  
  for(XDWORD c=0; c<UNITTEST_XUUID_NTESTS; c++)
    {
      ID[0].GenerateRandom();
      ID[0].CopyTo(ID[1]);

      ID[0].GetToString(IDstr[0]);
      ID[1].GetToString(IDstr[1]);

      EXPECT_EQ(0, IDstr[0].Compare(IDstr[1], false));
    }  
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, AssignByCopyFrom)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  AssignByCopyFrom
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, AssignByCopyFrom) 
{
  XUUID     ID[2]; 
  XSTRING   IDstr[2];
  
  for(XDWORD c=0; c<UNITTEST_XUUID_NTESTS; c++)
    {
      ID[0].GenerateRandom();
      ID[1].CopyFrom(ID[0]);

      ID[0].GetToString(IDstr[0]);
      ID[1].GetToString(IDstr[1]);

      EXPECT_EQ(0, IDstr[0].Compare(IDstr[1], false));
    }  
}


}
#endif


#pragma endregion

