/**-------------------------------------------------------------------------------------------------------------------
* 
* @file       XUtils UnitTests_XString.cpp
* 
* @class      XUTILS_UNITTESTS_XSTRING
* @brief      XUtils Unit Tests for XString class
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

#include "XUtils_UnitTests_XString.h"

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
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage437)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ConvertASCII_codepage437
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage437) 
{
  XSTRING string1 = __L("Hello 437! ÇüéâäàåçêëèïîìÄÅÉÖÜñÑ");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_CODEPAGE_437);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_CODEPAGE_437);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage850)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_codepage850 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage850) 
{
  XSTRING string1 = __L("Hello 850! áéíóú üñÑ çÇ ß Øø Åå");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_CODEPAGE_850);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_CODEPAGE_850);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage852)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_codepage852 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage852) 
{
  XSTRING string1 = __L("Hello 852! Ąą Ćć Ęę Łł Ńń Óó Śś Źź Żż");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_CODEPAGE_852);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_CODEPAGE_852);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage866)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_codepage866 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage866) 
{
  XSTRING string1 = __L("Hello 866! Привет мир! Ёё Жж Йй Яя Юю");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_CODEPAGE_866);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_CODEPAGE_866);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_1)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_ISO_8859_1 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_1) 
{
  XSTRING string1 = __L("Hello 8859-1! àèìòù Ññ ÁÉÍÓÚ üç ß");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_ISO_8859_1);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_ISO_8859_1);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_2)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_ISO_8859_2 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_2) 
{
  XSTRING string1 = __L("Hello 8859-2! Ąą Ćć Ęę Łł Ńń Óó Śś Źź Żż");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_ISO_8859_2);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_ISO_8859_2);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_3)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_ISO_8859_3 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_3) 
{
  XSTRING string1 = __L("Hello 8859-3! Ħħ Ġġ Ċċ Żż àèìòù");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_ISO_8859_3);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_ISO_8859_3);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_4)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_ISO_8859_4 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_4) 
{
  XSTRING string1 = __L("Hello 8859-4! Āā Ēē Ģģ Īī Ķķ Ļļ Ņņ Šš Ūū Žž");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_ISO_8859_4);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_ISO_8859_4);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1250)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_WINDOWS_1250 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1250) 
{
  XSTRING string1 = __L("Hello 1250! Ąą Čč Ďď Ęę Ěě Łł Ňň Řř Šš Ťť Ůů Žž");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_WINDOWS_1250);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_WINDOWS_1250);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1251)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_WINDOWS_1251 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1251) 
{
  XSTRING string1 = __L("Hello 1251! Привет мир! Ёё Жж Йй Яя Юю");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_WINDOWS_1251);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_WINDOWS_1251);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1252)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_WINDOWS_1252 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1252) 
{
  XSTRING string1 = __L("Hello 1252! àèìòù Ññ ÁÉÍÓÚ üç € “ ” ‘ ’ — …");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_WINDOWS_1252);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_WINDOWS_1252);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1253)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_WINDOWS_1253 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1253) 
{
  XSTRING string1 = __L("Hello 1253! Γειά σου κόσμε! Αα Ββ Γγ Δδ Εε Ζζ Ηη Θθ");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_WINDOWS_1253);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_WINDOWS_1253);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1254)
* @brief      Constructor of class
* @ingroup    
* 
* @param[in]  UNITTEST_XSTRING_CLASSNAME : 
* @param[in]  ConvertASCII_WINDOWS_1254 : 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1254) 
{
  XSTRING string1 = __L("Hello 1254! Türkçe: Ğğ İı Şş Çç Öö Üü");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_WINDOWS_1254);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_WINDOWS_1254);

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
  XSTRING string1 = __L("𠜎 𠜱 𠝹 𠱓 𠱸 𠲖 𠳏 𠳕 𠴕 𠵼 𠵿 𠸎 𠸏 𠹷 𠺝 𠺢 𠻗 𠻹 𠻺 𠼭 𠼮 𠽌 𠾴 𠾼 𠿪");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToUTF32(buffer);
  string2.ConvertFromUTF32(buffer);

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


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, EmptyAndIsEmpty)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  EmptyAndIsEmpty
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, EmptyAndIsEmpty) 
{
  XSTRING string;

  EXPECT_TRUE(string.IsEmpty());

  string.Set(unittest_hellostring);

  EXPECT_FALSE(string.IsEmpty());
  EXPECT_TRUE(string.HaveCharacters());

  EXPECT_TRUE(string.Empty());
  EXPECT_TRUE(string.IsEmpty());

  EXPECT_FALSE(string.Empty());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, OperatorPlusEqual)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  OperatorPlusEqual
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, OperatorPlusEqual) 
{
  XSTRING string;

  string  = __L("Hello");
  string += __L(", ");
  string += "world";
  string += __C('!');

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, DeleteCharactersMiddle)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  DeleteCharactersMiddle
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, DeleteCharactersMiddle) 
{
  XSTRING string = __L("abcdef");

  EXPECT_TRUE(string.DeleteCharacters(2, 2));
  EXPECT_EQ(0, string.Compare(__L("abef"), false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, DeleteCharacterAllString)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  DeleteCharacterAllString
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, DeleteCharacterAllString) 
{
  XSTRING string = __L("--a--b--");

  EXPECT_TRUE(string.DeleteCharacter(__C('-'), XSTRINGCONTEXT_ALLSTRING));
  EXPECT_EQ(0, string.Compare(__L("ab"), false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, InsertAtPosition)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  InsertAtPosition
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, InsertAtPosition) 
{
  XSTRING string = __L("ac");

  EXPECT_TRUE(string.Insert(__L("b"), 1));
  EXPECT_EQ(0, string.Compare(__L("abc"), false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ReplaceFirstAndReplaceAll)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ReplaceFirstAndReplaceAll
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ReplaceFirstAndReplaceAll) 
{
  XSTRING string = __L("one two one two");

  EXPECT_EQ(0, string.ReplaceFirst(__L("one"), __L("1")));
  EXPECT_EQ(0, string.Compare(__L("1 two one two"), false));

  EXPECT_EQ(2, string.Replace(__L("two"), __L("2")));
  EXPECT_EQ(0, string.Compare(__L("1 2 one 2"), false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ConvertIntRoundtrip)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ConvertIntRoundtrip
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ConvertIntRoundtrip) 
{
  XSTRING string;

  EXPECT_TRUE(string.ConvertFromInt(-12345));
  EXPECT_EQ(-12345, string.ConvertToInt());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, OperatorsCompareAndEquality)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  OperatorsCompareAndEquality
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, OperatorsCompareAndEquality) 
{
  XSTRING a = __L("abc");
  XSTRING b = __L("abd");
  XSTRING c = __L("abc");

  EXPECT_TRUE(a < b);
  EXPECT_FALSE(b < a);

  EXPECT_TRUE(a == c);
  EXPECT_FALSE(a != c);

  EXPECT_TRUE(a <= c);
  EXPECT_TRUE(a >= c);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, OperatorIndexBounds)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  OperatorIndexBounds
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, OperatorIndexBounds) 
{
  XSTRING string = __L("abcd");

  EXPECT_EQ(__C('a'), string[0]);
  EXPECT_EQ(__C('a'), string[-1]);
  EXPECT_EQ(__C('d'), string[100]);
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, FillChar)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  FillChar
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, FillChar) 
{
  XSTRING string = __L("----");

  EXPECT_TRUE(string.FillChar(__C('A')));
  EXPECT_EQ(0, string.Compare(__L("AAAA"), false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, FindAndCountCharacter)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  FindAndCountCharacter
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, FindAndCountCharacter) 
{
  XSTRING string = __L("abcaBCa");

  EXPECT_EQ(0, string.Find(__L("abc"), true, 0));
  EXPECT_EQ(1, string.Find(__L("bc"), false, 0));
  EXPECT_EQ(4, string.Find(__L("BC"), false, 0));

  EXPECT_EQ(3, (int)string.CountCharacter(__C('a')));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, FindCharacterEndToStart)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  FindCharacterEndToStart
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, FindCharacterEndToStart) 
{
  XSTRING string = __L("a-b-c-a");

  EXPECT_EQ(0, string.FindCharacter(__C('a'), 0, false));
  EXPECT_EQ(6, string.FindCharacter(__C('a'), 0, true));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, DeleteCharactersToEnd)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  DeleteCharactersToEnd
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, DeleteCharactersToEnd) 
{
  XSTRING string = __L("abcdef");

  EXPECT_TRUE(string.DeleteCharactersToEnd(3));
  EXPECT_EQ(0, string.Compare(__L("abc"), false));

  EXPECT_FALSE(string.DeleteCharactersToEnd(100));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, DeleteLastCharacterAndZeros)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  DeleteLastCharacterAndZeros
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, DeleteLastCharacterAndZeros) 
{
  XSTRING string = __L("12345000");

  EXPECT_TRUE(string.DeleteLastZeros());
  EXPECT_EQ(0, string.Compare(__L("12345"), false));

  EXPECT_TRUE(string.DeleteLastCharacter());
  EXPECT_EQ(0, string.Compare(__L("1234"), false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, InsertBeyondEnd)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  InsertBeyondEnd
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, InsertBeyondEnd) 
{
  XSTRING string = __L("abc");

  EXPECT_TRUE(string.Insert(__L("def"), 100));
  EXPECT_EQ(0, string.Compare(__L("abcdef"), false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, ReplaceNotFound)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  ReplaceNotFound
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, ReplaceNotFound) 
{
  XSTRING string = __L("one two");

  EXPECT_EQ(XSTRING_NOTFOUND, string.ReplaceFirst(__L("xxx"), __L("y")));
  EXPECT_EQ(0, string.Replace(__L("xxx"), __L("y")));
  EXPECT_EQ(0, string.Compare(__L("one two"), false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, DeleteNoCharactersAllString)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  DeleteNoCharactersAllString
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, DeleteNoCharactersAllString) 
{
  XSTRING string = __L("\t  a \r\n");

  EXPECT_TRUE(string.DeleteNoCharacters(XSTRINGCONTEXT_ALLSTRING));
  EXPECT_EQ(0, string.Compare(__L("a"), false));
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, AdjustSizeGrowAndShrink)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  AdjustSizeGrowAndShrink
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, AdjustSizeGrowAndShrink) 
{
  XSTRING string = __L("abc");

  EXPECT_TRUE(string.AdjustSize(5, false, __L("0"), false));
  EXPECT_EQ(0, string.Compare(__L("abc00"), false));
  EXPECT_EQ(5, string.GetSize());

  EXPECT_TRUE(string.AdjustSize(4, false, __L(" "), false));
  EXPECT_EQ(0, string.Compare(__L("abc0"), false));
  EXPECT_EQ(4, string.GetSize());

  EXPECT_TRUE(string.AdjustSize(6, true, __L("-"), false));
  EXPECT_EQ(0, string.Compare(__L("--abc0"), false));
  EXPECT_EQ(6, string.GetSize());
}


/**-------------------------------------------------------------------------------------------------------------------
* 
* @fn         TEST(UNITTEST_XSTRING_CLASSNAME, AdjustSizeAutoTrim)
* @brief      Unit test of UNITTEST_XSTRING_CLASSNAME:  AdjustSizeAutoTrim
* @ingroup    UNIT TEST
* 
* @return     Does not return anything. 
* 
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTEST_XSTRING_CLASSNAME, AdjustSizeAutoTrim) 
{
  XSTRING string;

  EXPECT_TRUE(string.Set((XDWORD)10));

  XCHAR* text = string.Get();
  ASSERT_TRUE(text != NULL);

  text[0] = __C('a');
  text[1] = __C('b');
  text[2] = __C('c');
  text[3] = __C('\0');

  EXPECT_TRUE(string.AdjustSize());
  EXPECT_EQ(3, string.GetSize());
  EXPECT_EQ(0, string.Compare(__L("abc"), false));
}


}


#endif


#pragma endregion
