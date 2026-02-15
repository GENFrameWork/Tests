/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XUtils_UnitTests_XUUID.cpp
* 
* @class      XUTILS_UNITTESTS_XUUID
* @brief      XUtils Unit Tests for XUUID class
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

#include "GEN_Defines.h"



/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "XUtils_UnitTests_XUUID.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XRand.h"
#include "XString.h"
#include "XUUID.h"



/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"




/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/




/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         static XDWORD GenerateDWord(XRAND* xrand)
* @brief      DWORd  generate Dword
* @ingroup    
* 
* @param[in]  xrand : 
* 
* @return     static : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
static XDWORD GenerateDWord(XRAND* xrand)
{
  XDWORD high = (XDWORD)xrand->Max(0xFFFF);
  XDWORD low  = (XDWORD)xrand->Max(0xFFFF);
  return (XDWORD)((high << 16) | low);
}


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
  ASSERT_NE((XRAND*)NULL, xrand);

  xrand->Ini();

  XUUID ID[2]; 
  XBYTE data[XUUIDMAXDATA4] = { (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255) };

  ID[0].SetData1((XDWORD)GenerateDWord(xrand));
  ID[0].SetData2((XWORD)xrand->Max(0xFFFF));
  ID[0].SetData3((XWORD)xrand->Max(0xFFFF));
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
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, SetByNumber2)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  SetByNumber2
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, SetByNumber2) 
{
  XRAND* xrand = GEN_XFACTORY.CreateRand();
  ASSERT_NE((XRAND*)NULL, xrand);

  xrand->Ini();

  XUUID ID[2]; 
  XBYTE data[XUUIDMAXDATA4] = { (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255) };

  ID[0].Set((XDWORD)GenerateDWord(xrand), (XWORD)xrand->Max(0xFFFF), (XWORD)xrand->Max(0xFFFF), (XBYTE)xrand->Max(255), (XBYTE)xrand->Max(255), data);
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


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, ConstructorIsEmpty)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  ConstructorIsEmpty
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, ConstructorIsEmpty) 
{
  XUUID ID;

  EXPECT_EQ(true, ID.IsEmpty());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, EmptyResetValues)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  EmptyResetValues
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, EmptyResetValues) 
{
  XUUID   ID;
  XBYTE   data[XUUIDMAXDATA4] = { 1, 2, 3, 4, 5, 6 };

  ID.Set(0x12345678, 0x1234, 0x5678, 0x9A, 0xBC, data);
  EXPECT_EQ(false, ID.IsEmpty());

  ID.Empty();

  EXPECT_EQ(true, ID.IsEmpty());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, CompareDetectsDifferences)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  CompareDetectsDifferences
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, CompareDetectsDifferences) 
{
  XUUID   ID[2];
  XBYTE   data[XUUIDMAXDATA4] = { 10, 11, 12, 13, 14, 15 };

  ID[0].Set(0x12345678, 0x1234, 0x5678, 0x9A, 0xBC, data);
  ID[1].CopyFrom(ID[0]);

  EXPECT_EQ(true, ID[0].Compare(ID[1]));

  ID[1].SetData5((XBYTE)0xBD);
  EXPECT_EQ(false, ID[0].Compare(ID[1]));

  ID[1].CopyFrom(ID[0]);
  ID[1].GetData6()[0] = (XBYTE)0xFF;
  EXPECT_EQ(false, ID[0].Compare(ID[1]));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, SetData6CopiesValues)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  SetData6CopiesValues
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, SetData6CopiesValues) 
{
  XUUID   ID;
  XBYTE   data[XUUIDMAXDATA4] = { 1, 2, 3, 4, 5, 6 };

  ID.SetData6(data);

  data[0] = 0;

  EXPECT_EQ((XBYTE)1, ID.GetData6()[0]);
  EXPECT_EQ((XBYTE)6, ID.GetData6()[5]);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, StringFormatLength)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  StringFormatLength
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, StringFormatLength) 
{
  XUUID     ID;
  XSTRING   IDstr;

  ID.GenerateRandom();
  ID.GetToString(IDstr);

  EXPECT_EQ((XDWORD)36, IDstr.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, SetFromStringEmptyFails)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  SetFromStringEmptyFails
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, SetFromStringEmptyFails) 
{
  XUUID     ID;
  XSTRING   str;

  str.Empty();

  EXPECT_EQ(false, ID.SetFromString(str));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, GenerateRandomProducesDifferentValues)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  GenerateRandomProducesDifferentValues
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, GenerateRandomProducesDifferentValues) 
{
  XUUID ID[2];
  bool  isdifferent = false;

  EXPECT_EQ(true, ID[0].GenerateRandom());
  EXPECT_EQ(false, ID[0].IsEmpty());

  for(int c=0; c<100; c++)
    {
      EXPECT_EQ(true, ID[1].GenerateRandom());

      if(!ID[0].Compare(ID[1]))
        {
          isdifferent = true;
          break;
        }
    }

  EXPECT_EQ(true, isdifferent);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XUUID_CLASSNAME, SetAndCopyReturnTrue)
* @brief      Unit test of UNITTEST_XUUID_CLASSNAME:  SetAndCopyReturnTrue
* @ingroup    UNIT TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XUUID_CLASSNAME, SetAndCopyReturnTrue) 
{
  XUUID   ID[3];
  XBYTE   data[XUUIDMAXDATA4] = { 10, 20, 30, 40, 50, 60 };

  EXPECT_EQ(true, ID[0].Set(0x01020304, 0x0506, 0x0708, 0x09, 0x0A, data));
  EXPECT_EQ(true, ID[1].Set(ID[0]));
  EXPECT_EQ(true, ID[0].CopyTo(ID[2]));
  EXPECT_EQ(true, ID[2].CopyFrom(ID[1]));

  EXPECT_EQ(true, ID[0].Compare(ID[1]));
  EXPECT_EQ(true, ID[0].Compare(ID[2]));
}


}
#endif


