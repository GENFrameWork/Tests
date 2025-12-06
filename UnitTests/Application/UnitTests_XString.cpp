/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       UnitTests_XString.cpp
* 
* @class      UNITTESTS_XSTRING
* @brief      Unit Tests for XString class
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

#include "UnitTests_XString.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XBuffer.h"
#include "XString.h"

#pragma endregion


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/
#pragma region PRECOMPILATION_CONTROL_INCLUDE

#include "GEN_Control.h"

#pragma endregion



/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/
#pragma region GENERAL_VARIABLE

char*  unittest_hellostringOEM = (char*)("Hello, world!");
XCHAR* unittest_hellostring    = __L("Hello, world!");

#pragma endregion


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/
#pragma region CLASS_MEMBERS


#ifdef GOOGLETEST_ACTIVE      
namespace TEST_XSTRING
{


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


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, CompareOneCharacter)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME: CompareOneCharacter
* @ingroup    UNIT_TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, CompareOneCharacter) 
{
  XSTRING string = "0";

  EXPECT_EQ(-1, string.Compare(__L("1"), false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, CompareOneCharacterIgnoreCase)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME: CompareOneCharacterIgnoreCase
* @ingroup    UNIT_TEST
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, CompareOneCharacterIgnoreCase) 
{
  XSTRING string = "A";

  EXPECT_EQ(0, string.Compare(__L("a"), true));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ConvertASCII
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII) 

{
  XSTRING string1 = __L("Hello world!");
  XSTRING string2;
  XBUFFER buffer;
      
  string1.ConvertToASCII(buffer);
  string2.ConvertFromASCII(buffer);
    
  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertUTF8)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ConvertUTF8
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertUTF8) 
{
  XSTRING string1 = __L("แผ่นดินฮั่นเสื่อมโทรมแสนสังเวช");
  XSTRING string2;
  XBUFFER buffer;
      
  string1.ConvertToUTF8(buffer, false);
  string2.ConvertFromUTF8(buffer);
    
  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertUTF16)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ConvertUTF16
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertUTF16) 
{
  XSTRING string1 = __L("𠜎 𠜱 𠝹 𠱓 𠱸 𠲖 𠳏 𠳕 𠴕 𠵼 𠵿 𠸎 𠸏 𠹷 𠺝 𠺢 𠻗 𠻹 𠻺 𠼭 𠼮 𠽌 𠾴 𠾼 𠿪");
  XSTRING string2;
  XBUFFER buffer;
      
  string1.ConvertToUTF16(buffer);
  string2.ConvertFromUTF16(buffer);
  
  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertUTF32)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ConvertUTF32
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertUTF32) 
{
  XSTRING string1 = __L("ᚻᛖ ᚳᚹᚫᚦ ᚦᚫᛏ ᚻᛖ ᛒᚢᛞᛖ ᚩᚾ ᚦᚫᛗ ᛚᚪᚾᛞᛖ ᚾᚩᚱᚦᚹᛖᚪᚱᛞᚢᛗ ᚹᛁᚦ ᚦᚪ ᚹᛖᛥᚫ");
  XSTRING string2;
  XBUFFER buffer;
      
  string1.ConvertToUTF16(buffer);
  string2.ConvertFromUTF16(buffer);
    
  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, Base64)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  Base64
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, Base64) 
{
  XSTRING string;
  XSTRING string2;
  XBUFFER buffer;

  string = __L("MIIDdTCCAl2gAwIBAgILBAAAAAABFUtaw5QwDQYJKoZIhvcNAQEFBQAwVzELMAkGA1UEBhMCQkUxGTAXBgNVBAoTEEdsb2JhbFNpZ24gbnYtc2ExEDAOBgNVBAsTB1Jvb3QgQ0ExGzAZBgNVBAMTEkdsb2JhbFNpZ24gUm9vdCBDQTAeFw05ODA5MDExMjAwMDBaFw0yODAxMjgxMjAwMDBaMFcxCzAJBgNVBAYTAkJFMRkwFwYDVQQKExBHbG9iYWxTaWduIG52LXNhMRAwDgYDVQQLEwdSb290IENBMRswGQYDVQQDExJHbG9iYWxTaWduIFJvb3QgQ0EwggEiMA0GCSqGSIb3DQEBAQUAA4IBDwAwggEKAoIBAQDaDuaZjc6j40+Kfvvxi4Mla+pIH/EqsLmVEQS98GPR4mdmzxzdzxtIK+6NiY6arymAZavpxy0Sy6scTHAHoT0KMM0VjU/43dSMUBUc71DuxC73/OlS8pF94G3VNTCOXkNz8kHp1Wrjsok6Vjk4bwY8iGlbKk3Fp1S4bInMm/k8yuX9ifUSPJJ4ltbcdG6TRGHRjcdGsnUOhugZitVtbNV4FpWi6cgKOOvyJBNPc1STE4U6G7weNLWLBYy5d4ux2x8gkasJU26Qzns3dLlwR5EiUWMWea6xrkEmCMgZK9FGqkjWZCrXgzT/LCrBbBlDSgeF59N89iFo7+ryUp9/k5DPAgMBAAGjQjBAMA4GA1UdDwEB/wQEAwIBBjAPBgNVHRMBAf8EBTADAQH/MB0GA1UdDgQWBBRge2YaRQ2XyolQL30EzTSo//z9SzANBgkqhkiG9w0BAQUFAAOCAQEA1nPnfE920I2/7LqivjTFKDK1fPxsnCwrvQmeU79rXqoRSLblCKOzyj1hTdNGCbM+w6DjY1Ub8rrvrTnhQ7k4o+YviiY776BQVvnGCv04zcQLcFGUl5gE38NflNUVyRRBnMRddWQVDf9VMOyGj/8N7yy5Y0b2qvzfvGn9LhJIZJrglfCm7ymPAbEVtQwdpf5pLGkkeB6zpxxxYu7KyJesF12KwvhHhm4qxFYxldBniYUr+WymXUadDKqC5JlR3XC321Y9YeRq4VzW9v493kHMB65jUr9TU/Qr6cf9tveCX4XSQRjbgbMEHMUfpIBvFSDJ3gyICh3WZlXi/EjJKSZp4A==");
  
  string.ConvertBase64ToBinary(buffer);    
  string2.ConvertBinaryToBase64(buffer);

  EXPECT_EQ(0, string.Compare(string2, false));
}


}


#endif


#pragma endregion

