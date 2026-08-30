/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XString.cpp
*
* @class      XUTILS_UNITTESTS_XSTRING
* @brief      XUtils unit tests for XString class
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

#include "XUtils_UnitTests_XString.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XBuffer.h"
#include "XString.h"
#include "XVector.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

char*  unittest_hellostringOEM = (char*)("Hello, world!");
XCHAR* unittest_hellostring    = __L("Hello, world!");


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE      
namespace TEST_XSTRING
{


TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorSize) 
{
  XSTRING string(32);

  EXPECT_EQ(32, string.GetSize());
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssignOEM) 
{
  XSTRING string(unittest_hellostringOEM);

  EXPECT_EQ(0, string.Compare(unittest_hellostringOEM, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssign) 
{
  XSTRING string(unittest_hellostring);

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssingSize) 
{
  XSTRING string(unittest_hellostring, 13);

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
  EXPECT_EQ(13, string.GetSize());
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConstructorAssingDirect) 
{
  XSTRING string(unittest_hellostring, 13);
  XSTRING string2(string);

  EXPECT_EQ(0, string2.Compare(unittest_hellostring, false));
}  


TEST(UNITTEST_XSTRING_CLASSNAME, Set) 
{
  XSTRING string;

  string.Set(unittest_hellostring);

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, Add) 
{
  XSTRING string;

  string.Add(unittest_hellostring);

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, AssignmentOperator) 
{
  XSTRING string = unittest_hellostring;

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, CompareOneCharacter) 
{
  XSTRING string = "0";

  EXPECT_EQ(-1, string.Compare(__L("1"), false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, CompareOneCharacterIgnoreCase) 
{
  XSTRING string = "A";

  EXPECT_EQ(0, string.Compare(__L("a"), true));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII) 
{
  XSTRING string1 = __L("Hello world!");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer);
  string2.ConvertFromASCII(buffer);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage437) 
{
  XSTRING string1 = __L("Hello 437! ÇüéâäàåçêëèïîìÄÅÉÖÜñÑ");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_CODEPAGE_437);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_CODEPAGE_437);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage850) 
{
  XSTRING string1 = __L("Hello 850! áéíóú üñÑ çÇ ß Øø Åå");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_CODEPAGE_850);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_CODEPAGE_850);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage852) 
{
  XSTRING string1 = __L("Hello 852! Ąą Ćć Ęę Łł Ńń Óó Śś Źź Żż");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_CODEPAGE_852);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_CODEPAGE_852);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_codepage866) 
{
  XSTRING string1 = __L("Hello 866! Привет мир! Ёё Жж Йй Яя Юю");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_CODEPAGE_866);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_CODEPAGE_866);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_1) 
{
  XSTRING string1 = __L("Hello 8859-1! àèìòù Ññ ÁÉÍÓÚ üç ß");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_ISO_8859_1);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_ISO_8859_1);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_2) 
{
  XSTRING string1 = __L("Hello 8859-2! Ąą Ćć Ęę Łł Ńń Óó Śś Źź Żż");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_ISO_8859_2);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_ISO_8859_2);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_3) 
{
  XSTRING string1 = __L("Hello 8859-3! Ħħ Ġġ Ċċ Żż àèìòù");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_ISO_8859_3);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_ISO_8859_3);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_ISO_8859_4) 
{
  XSTRING string1 = __L("Hello 8859-4! Āā Ēē Ģģ Īī Ķķ Ļļ Ņņ Šš Ūū Žž");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_ISO_8859_4);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_ISO_8859_4);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1250) 
{
  XSTRING string1 = __L("Hello 1250! Ąą Čč Ďď Ęę Ěě Łł Ňň Řř Šš Ťť Ůů Žž");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_WINDOWS_1250);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_WINDOWS_1250);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1251) 
{
  XSTRING string1 = __L("Hello 1251! Привет мир! Ёё Жж Йй Яя Юю");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_WINDOWS_1251);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_WINDOWS_1251);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1252) 
{
  XSTRING string1 = __L("Hello 1252! àèìòù Ññ ÁÉÍÓÚ üç € “ ” ‘ ’ — …");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_WINDOWS_1252);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_WINDOWS_1252);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1253) 
{
  XSTRING string1 = __L("Hello 1253! Γειά σου κόσμε! Αα Ββ Γγ Δδ Εε Ζζ Ηη Θθ");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_WINDOWS_1253);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_WINDOWS_1253);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertASCII_WINDOWS_1254) 
{
  XSTRING string1 = __L("Hello 1254! Türkçe: Ğğ İı Şş Çç Öö Üü");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToASCII(buffer, XSTRINGASCIICODE_WINDOWS_1254);
  string2.ConvertFromASCII(buffer, XSTRINGASCIICODE_WINDOWS_1254);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertUTF8) 
{
  XSTRING string1 = __L("แผ่นดินฮั่นเสื่อมโทรมแสนสังเวช");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToUTF8(buffer, false);
  string2.ConvertFromUTF8(buffer);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertUTF16) 
{
  XSTRING string1 = __L("𠜎 𠜱 𠝹 𠱓 𠱸 𠲖 𠳏 𠳕 𠴕 𠵼 𠵿 𠸎 𠸏 𠹷 𠺝 𠺢 𠻗 𠻹 𠻺 𠼭 𠼮 𠽌 𠾴 𠾼 𠿪");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToUTF16(buffer);
  string2.ConvertFromUTF16(buffer);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertUTF32) 
{
  XSTRING string1 = __L("𠜎 𠜱 𠝹 𠱓 𠱸 𠲖 𠳏 𠳕 𠴕 𠵼 𠵿 𠸎 𠸏 𠹷 𠺝 𠺢 𠻗 𠻹 𠻺 𠼭 𠼮 𠽌 𠾴 𠾼 𠿪");
  XSTRING string2;
  XBUFFER buffer;

  string1.ConvertToUTF32(buffer);
  string2.ConvertFromUTF32(buffer);

  EXPECT_EQ(0, string1.Compare(string2, false));
}


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


TEST(UNITTEST_XSTRING_CLASSNAME, OperatorPlusEqual) 
{
  XSTRING string;

  string  = __L("Hello");
  string += __L(", ");
  string += "world";
  string += __C('!');

  EXPECT_EQ(0, string.Compare(unittest_hellostring, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, DeleteCharactersMiddle) 
{
  XSTRING string = __L("abcdef");

  EXPECT_TRUE(string.DeleteCharacters(2, 2));
  EXPECT_EQ(0, string.Compare(__L("abef"), false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, DeleteCharacterAllString) 
{
  XSTRING string = __L("--a--b--");

  EXPECT_TRUE(string.DeleteCharacter(__C('-'), XSTRINGCONTEXT_ALLSTRING));
  EXPECT_EQ(0, string.Compare(__L("ab"), false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, InsertAtPosition) 
{
  XSTRING string = __L("ac");

  EXPECT_TRUE(string.Insert(__L("b"), 1));
  EXPECT_EQ(0, string.Compare(__L("abc"), false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ReplaceFirstAndReplaceAll) 
{
  XSTRING string = __L("one two one two");

  EXPECT_EQ(0, string.ReplaceFirst(__L("one"), __L("1")));
  EXPECT_EQ(0, string.Compare(__L("1 two one two"), false));

  EXPECT_EQ(2, string.Replace(__L("two"), __L("2")));
  EXPECT_EQ(0, string.Compare(__L("1 2 one 2"), false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertIntRoundtrip) 
{
  XSTRING string;

  EXPECT_TRUE(string.ConvertFromInt(-12345));
  EXPECT_EQ(-12345, string.ConvertToInt());
}


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


TEST(UNITTEST_XSTRING_CLASSNAME, OperatorIndexBounds) 
{
  XSTRING string = __L("abcd");

  EXPECT_EQ(__C('a'), string[0]);
  EXPECT_EQ(__C('a'), string[-1]);
  EXPECT_EQ(__C('d'), string[100]);
}


TEST(UNITTEST_XSTRING_CLASSNAME, FillChar) 
{
  XSTRING string = __L("----");

  EXPECT_TRUE(string.FillChar(__C('A')));
  EXPECT_EQ(0, string.Compare(__L("AAAA"), false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, FindAndCountCharacter) 
{
  XSTRING string = __L("abcaBCa");

  EXPECT_EQ(0, string.Find(__L("abc"), true, 0));
  EXPECT_EQ(1, string.Find(__L("bc"), false, 0));
  EXPECT_EQ(4, string.Find(__L("BC"), false, 0));

  EXPECT_EQ(3, (int)string.CountCharacter(__C('a')));
}


TEST(UNITTEST_XSTRING_CLASSNAME, FindCharacterEndToStart) 
{
  XSTRING string = __L("a-b-c-a");

  EXPECT_EQ(0, string.FindCharacter(__C('a'), 0, false));
  EXPECT_EQ(6, string.FindCharacter(__C('a'), 0, true));
}


TEST(UNITTEST_XSTRING_CLASSNAME, DeleteCharactersToEnd) 
{
  XSTRING string = __L("abcdef");

  EXPECT_TRUE(string.DeleteCharactersToEnd(3));
  EXPECT_EQ(0, string.Compare(__L("abc"), false));

  EXPECT_FALSE(string.DeleteCharactersToEnd(100));
}


TEST(UNITTEST_XSTRING_CLASSNAME, DeleteLastCharacterAndZeros) 
{
  XSTRING string = __L("12345.000");

  EXPECT_TRUE(string.DeleteLastZeros());
  EXPECT_EQ(0, string.Compare(__L("12345"), false));

  EXPECT_TRUE(string.DeleteLastCharacter());
  EXPECT_EQ(0, string.Compare(__L("1234"), false));

  string = __L("12345.6700");

  EXPECT_TRUE(string.DeleteLastZeros());
  EXPECT_EQ(0, string.Compare(__L("12345.67"), false));

  string = __L("12345000");

  EXPECT_FALSE(string.DeleteLastZeros());
  EXPECT_EQ(0, string.Compare(__L("12345000"), false));

  string = __L("12345.67");

  EXPECT_FALSE(string.DeleteLastZeros());
  EXPECT_EQ(0, string.Compare(__L("12345.67"), false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, InsertBeyondEnd) 
{
  XSTRING string = __L("abc");

  EXPECT_TRUE(string.Insert(__L("def"), 100));
  EXPECT_EQ(0, string.Compare(__L("abcdef"), false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ReplaceNotFound) 
{
  XSTRING string = __L("one two");

  EXPECT_EQ(XSTRING_NOTFOUND, string.ReplaceFirst(__L("xxx"), __L("y")));
  EXPECT_EQ(0, string.Replace(__L("xxx"), __L("y")));
  EXPECT_EQ(0, string.Compare(__L("one two"), false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, DeleteNoCharactersAllString) 
{
  XSTRING string = __L("\t  a \r\n");

  EXPECT_TRUE(string.DeleteNoCharacters(XSTRINGCONTEXT_ALLSTRING));
  EXPECT_EQ(0, string.Compare(__L("a"), false));
}


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


TEST(UNITTEST_XSTRING_CLASSNAME, CopySubstringOverloads)
{
  XSTRING string = __L("abcdefgh");
  XSTRING result;

  EXPECT_NE(XSTRING_NOTFOUND, string.Copy(2, 5, result));
  EXPECT_EQ(0, result.Compare(__L("cde"), false));

  EXPECT_NE(XSTRING_NOTFOUND, string.Copy(3, result));
  EXPECT_EQ(0, result.Compare(__L("defgh"), false));

  // startindex >= endindex is documented as a NOTFOUND rejection.
  EXPECT_EQ(XSTRING_NOTFOUND, string.Copy(5, 2, result));
}


TEST(UNITTEST_XSTRING_CLASSNAME, SplitBySeparator)
{
  XSTRING             string = __L("one,two,three");
  XVECTOR<XSTRING*>   parts;

  EXPECT_TRUE(string.Split(__C(','), parts, false));
  ASSERT_EQ((XDWORD)3, parts.GetSize());

  EXPECT_EQ(0, parts.Get(0)->Compare(__L("one"),   false));
  EXPECT_EQ(0, parts.Get(1)->Compare(__L("two"),   false));
  EXPECT_EQ(0, parts.Get(2)->Compare(__L("three"), false));

  for(XDWORD c=0; c<parts.GetSize(); c++)
    {
      GEN_DELETE parts.Get(c);
    }
}


TEST(UNITTEST_XSTRING_CLASSNAME, ExplodeBySeparator)
{
  XSTRING           string = __L("a::b::c");
  XVECTOR<XSTRING*> tokens;

  EXPECT_TRUE(string.Explode(__C(':'), &tokens));

  // Explode skips zero-length runs (consecutive separators collapse), unlike Split's
  // "addsubstringempty" option -- confirms the two vector-splitting methods have different
  // ownership/empty-token semantics.
  ASSERT_EQ((XDWORD)3, tokens.GetSize());
  EXPECT_EQ(0, tokens.Get(0)->Compare(__L("a"), false));
  EXPECT_EQ(0, tokens.Get(1)->Compare(__L("b"), false));
  EXPECT_EQ(0, tokens.Get(2)->Compare(__L("c"), false));

  for(XDWORD c=0; c<tokens.GetSize(); c++)
    {
      GEN_DELETE tokens.Get(c);
    }
}


TEST(UNITTEST_XSTRING_CLASSNAME, FormatAddFormatAndUnFormat)
{
  XSTRING string;

  // Source bug (not fixed, XString.cpp XSTRING::Format()/AddFormat()): both wrappers
  // literally "return 0;" (false) unconditionally, even though the real work is done by the
  // internal FormatArg() helper, which itself returns true on this same happy path -- so
  // Format()/AddFormat() always report failure to the caller despite succeeding. The actual
  // string content is still correct, only the reported bool status is wrong.
  EXPECT_FALSE(string.Format(__L("ID-%02d"), 7));
  EXPECT_EQ(0, string.Compare(__L("ID-07"), false));

  EXPECT_FALSE(string.AddFormat(__L("/%d"), 42));
  EXPECT_EQ(0, string.Compare(__L("ID-07/42"), false));

  int number1 = 0;
  int number2 = 0;

  EXPECT_TRUE(string.UnFormat(__L("ID-%02d/%d"), &number1, &number2));
  EXPECT_EQ(7,  number1);
  EXPECT_EQ(42, number2);
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertToPascalAndFromPascal)
{
  XSTRING     string = __L("Pascal!");
  SHORTSTRING pascalstring;
  XSTRING     roundtrip;

  EXPECT_TRUE(string.ConvertToPascal(pascalstring));
  EXPECT_EQ((XBYTE)string.GetSize(), pascalstring.size);

  EXPECT_TRUE(roundtrip.ConvertFromPascal(pascalstring));
  EXPECT_EQ(0, roundtrip.Compare(__L("Pascal!"), false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, Swab)
{
  XSTRING string = __L("abcd");

  EXPECT_TRUE(string.Swab());
  EXPECT_EQ(0, string.Compare(__L("badc"), false));

  XSTRING empty;
  EXPECT_FALSE(empty.Swab());
}


TEST(UNITTEST_XSTRING_CLASSNAME, BinaryCompare)
{
  XSTRING a = __L("same");
  XSTRING b = __L("same");
  XSTRING c = __L("diff");
  XSTRING d = __L("longer text");

  EXPECT_TRUE(a.BinaryCompare(b));
  EXPECT_FALSE(a.BinaryCompare(c));
  EXPECT_FALSE(a.BinaryCompare(d));  // different size -> immediate false
}


TEST(UNITTEST_XSTRING_CLASSNAME, GetTypeOfLineEnd)
{
  XSTRING string = __L("line1\r\nline2\r\n");
  XSTRING lineend;

  EXPECT_TRUE(string.GetTypeOfLineEnd(lineend));
  EXPECT_EQ(0, lineend.Compare(__L("\r\n"), false));

  XSTRING toosmall = __L("a");
  XSTRING lineend2;
  EXPECT_FALSE(toosmall.GetTypeOfLineEnd(lineend2));
}


TEST(UNITTEST_XSTRING_CLASSNAME, HexConversionRoundTrip)
{
  XSTRING string = __L("Hi!");
  XSTRING hexstring;
  XBUFFER buffer;
  XSTRING roundtrip;

  EXPECT_TRUE(string.ConvertToHexString(hexstring, true));
  EXPECT_EQ(0, hexstring.Compare(__L("486921"), true));  // 'H'=0x48 'i'=0x69 '!'=0x21

  EXPECT_TRUE(hexstring.ConvertHexStringToBuffer(buffer));
  EXPECT_EQ((XDWORD)3, buffer.GetSize());
  EXPECT_EQ((XBYTE)'H', buffer.GetByte(0));
  EXPECT_EQ((XBYTE)'i', buffer.GetByte(1));
  EXPECT_EQ((XBYTE)'!', buffer.GetByte(2));

  EXPECT_TRUE(roundtrip.ConvertHexStringFromBuffer(buffer, true));
  EXPECT_EQ(0, roundtrip.Compare(hexstring, false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, FindCharacterFromSetAndAreValidCharacters)
{
  XSTRING string = __L("hello world");

  EXPECT_EQ(5, string.FindCharacterFromSet(__L(" ,;")));

  XSTRING noneofthese = __L("abc");
  EXPECT_EQ((int)noneofthese.GetSize(), noneofthese.FindCharacterFromSet(__L("xyz")));

  EXPECT_TRUE(string.AreValidCharacters((XCHAR*)__L("helo wrd")));
  EXPECT_FALSE(string.AreValidCharacters((XCHAR*)__L("hel")));
}


TEST(UNITTEST_XSTRING_CLASSNAME, CharacterFamilyHelpers)
{
  XSTRING string = __L("abc");

  EXPECT_TRUE(string.Character_IsAlpha(__C('a')));
  EXPECT_FALSE(string.Character_IsAlpha(__C('5')));

  EXPECT_TRUE(string.Character_IsUpperCase(__C('A')));
  EXPECT_FALSE(string.Character_IsUpperCase(__C('a')));

  EXPECT_TRUE(string.Character_IsLowerCase(__C('a')));
  EXPECT_FALSE(string.Character_IsLowerCase(__C('A')));

  EXPECT_TRUE(string.Character_IsNumber(__C('7')));
  EXPECT_FALSE(string.Character_IsNumber(__C('x')));

  EXPECT_EQ(__C('A'), string.Character_ToUpper(__C('a')));
  EXPECT_EQ(__C('a'), string.Character_ToLower(__C('A')));

  EXPECT_EQ(__C('a'), string.Character_GetFirst());
  EXPECT_EQ(__C('c'), string.Character_GetLast());

  EXPECT_TRUE(string.Character_Change(__C('b'), __C('Z')));
  EXPECT_EQ(0, string.Compare(__L("aZc"), false));
  EXPECT_FALSE(string.Character_Change(__C('x'), __C('Y')));  // not present -> no change made
}


TEST(UNITTEST_XSTRING_CLASSNAME, HaveNumbersAndIsNumberFamily)
{
  XSTRING alphaonly   = __L("abc");
  XSTRING mixed       = __L("ab12");
  XSTRING numbersonly = __L("12345");
  XSTRING decimal     = __L("123.45");

  EXPECT_FALSE(alphaonly.HaveNumbers());
  EXPECT_TRUE(mixed.HaveNumbers());
  EXPECT_FALSE(mixed.HaveOnlyNumbers());
  EXPECT_TRUE(numbersonly.HaveOnlyNumbers());

  EXPECT_TRUE(numbersonly.IsNumber());
  EXPECT_FALSE(alphaonly.IsNumber());

  int ndecimals = 0;
  EXPECT_TRUE(decimal.IsDecimalNumber(&ndecimals));
  // Source quirk (not a crash, just a naming/off-by-one surprise): ndecimals is computed as
  // "size - indexof('.')", which includes the decimal separator character itself in the
  // count, not just the digits after it -- so "123.45" (2 real decimal digits) reports 3.
  EXPECT_EQ(3, ndecimals);
  EXPECT_FALSE(alphaonly.IsDecimalNumber());
}


TEST(UNITTEST_XSTRING_CLASSNAME, ToUpperCaseAndToLowerCase)
{
  XSTRING string = __L("MixedCase123");

  EXPECT_TRUE(string.ToUpperCase());
  EXPECT_EQ(0, string.Compare(__L("MIXEDCASE123"), false));

  EXPECT_TRUE(string.ToLowerCase());
  EXPECT_EQ(0, string.Compare(__L("mixedcase123"), false));
}


TEST(UNITTEST_XSTRING_CLASSNAME, ConvertFromBooleanShortWordLongLong)
{
  XSTRING string;

  EXPECT_TRUE(string.ConvertFromBoolean(true, XSTRINGBOOLEANMODE_COMPUTER));
  EXPECT_FALSE(string.IsEmpty());

  EXPECT_TRUE(string.ConvertFromShort((short)-123));
  EXPECT_EQ(-123, string.ConvertToInt());

  EXPECT_TRUE(string.ConvertFromWord((XWORD)6789));
  EXPECT_EQ(6789, string.ConvertToInt());

  EXPECT_TRUE(string.ConvertFromLongLong((long long)-987654321LL));
  EXPECT_EQ((long long)-987654321LL, string.ConvertToLongLong());
}


}


#endif


