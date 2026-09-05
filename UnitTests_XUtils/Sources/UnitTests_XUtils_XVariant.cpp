/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XVariant.cpp
*
* @class      UNITTESTS_XUTILS_XVARIANT
* @brief      XUtils unit tests for XVariant class
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

#include "UnitTests_XUtils_XVariant.h"

#include "string.h"

#ifdef GOOGLETEST_ACTIVE      
#include "gtest/gtest.h"
#endif

#include "XBuffer.h"
#include "XVariant.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

#define UNITTESTS_XVARIANT_CONSTRUCTOR(type, value)            { XVARIANT variant((type)value); \
                                                                EXPECT_EQ((type)value, (type)variant); \
                                                              }

#define UNITTESTS_XVARIANT_CONVERTSTRING(type, value)          { XVARIANT variant((type)value); \
                                                                XVARIANT variant2; \
                                                                XSTRING  string; \
                                                                type value2; \
                                                                variant.ToString(string); \
                                                                variant2.FromString(string); \
                                                                value2 = (type)variant2; \
                                                                EXPECT_EQ((type)value, (type)value2); \
                                                              }


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE      
namespace TEST_XVARIANT
{


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignBool) 
{
  UNITTESTS_XVARIANT_CONSTRUCTOR(bool, true);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignShort) 
{
  UNITTESTS_XVARIANT_CONSTRUCTOR(short, -12345); 
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignWord) 
{
  UNITTESTS_XVARIANT_CONSTRUCTOR(XWORD, 12345); 
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignInt) 
{ 
  UNITTESTS_XVARIANT_CONSTRUCTOR(int, -1234567890);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignDWord) 
{
  UNITTESTS_XVARIANT_CONSTRUCTOR(XDWORD, 1234567890);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignLongLong) 
{
  UNITTESTS_XVARIANT_CONSTRUCTOR(long long, -1234567890123445);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignQWord) 
{
  UNITTESTS_XVARIANT_CONSTRUCTOR(XQWORD, 1234567890123445); 
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignFloat) 
{
  UNITTESTS_XVARIANT_CONSTRUCTOR(float, -123.456f); 
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignDouble) 
{
  UNITTESTS_XVARIANT_CONSTRUCTOR(double, -123456.78787f);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignChar) 
{
  UNITTESTS_XVARIANT_CONSTRUCTOR(char, 'A');  
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignXChar) 
{  
  UNITTESTS_XVARIANT_CONSTRUCTOR(XCHAR, __C('A')); 
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignCharPtr) 
{   
  const char* value  = (const char*)"Hello Word!";
  XVARIANT    variant((char*)value);
  XSTRING     value2 = variant;

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_STRING);
  EXPECT_EQ(value2.Compare(value, true), 0);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignXCharPtr) 
{   
  XCHAR*    value  = __L("Hello Word!");
  XVARIANT  variant(value);
  XSTRING   value2 = variant;
  
  EXPECT_EQ(value2.Compare(value, true), 0);      
}  
  


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignDateTime) 
{   
  XSTRING   datetimestr = __L("01/12/1969 12:30:30");
  XSTRING   datetimestr2;
  XDATETIME value;

  value.GetDateTimeFromString(datetimestr, XDATETIME_FORMAT_STANDARD);

  XVARIANT  variant(value);
  XDATETIME value2 = variant;

  value2.GetDateTimeToString(XDATETIME_FORMAT_STANDARD, datetimestr2);
  EXPECT_EQ(datetimestr.Compare(datetimestr2, true), 0);
}
    


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignDWord2)    
{ 
  XVARIANT value = (XDWORD)0x1234;

  UNITTESTS_XVARIANT_CONSTRUCTOR(XDWORD, value);  
}  


TEST(UNITTESTS_XVARIANT_CLASSNAME, ConstructorAssignPointer)  
{ 
  void*     value = (void*)0x12345678;
  XVARIANT  variant(value);
  void*     value2; 

  value2 = variant; 

  EXPECT_EQ(value, value2); 
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionBool) 
{
  UNITTESTS_XVARIANT_CONVERTSTRING(bool, true);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionShort) 
{
  UNITTESTS_XVARIANT_CONVERTSTRING(short, -12345);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionWord) 
{
  UNITTESTS_XVARIANT_CONVERTSTRING(XWORD, 12345);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionInt) 
{
  UNITTESTS_XVARIANT_CONVERTSTRING(int, -1234567890);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionDWord) 
{
  UNITTESTS_XVARIANT_CONVERTSTRING(XDWORD, 1234567890);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionLongLong) 
{
  UNITTESTS_XVARIANT_CONVERTSTRING(long long, -1234567890123445);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionQWord) 
{
  UNITTESTS_XVARIANT_CONVERTSTRING(XQWORD, 1234567890123445);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionFloat) 
{
  float       value = AdjustFloat(-12.1234f, 4);
  XVARIANT    variant(value); 
  XVARIANT    variant2; 
  XSTRING     string; 
  float       value2; 

  variant.ToString(string); 
  variant2.FromString(string); 
  value2 = AdjustFloat((float)variant2, 4);

  EXPECT_EQ((float)value, (float)value2); 
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionDouble) 
{ 
  double      value = AdjustDouble(-12.12345678f, 6);
  XVARIANT    variant(value); 
  XVARIANT    variant2; 
  XSTRING     string; 
  double      value2; 

  variant.ToString(string); 
  variant2.FromString(string); 
  value2 = AdjustDouble((double)variant2, 6);

  EXPECT_EQ((double)value, (double)value2); 
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionChar) 
{ 
  char        value = 'A';
  XVARIANT    variant(value); 
  XVARIANT    variant2; 
  XSTRING     string; 
  char        value2; 

  variant.ToString(string); 
  variant2.FromString(string, XVARIANT_TYPE_CHAR); 
  value2 = (char)variant2;

  EXPECT_EQ((char)value, (char)value2); 
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionCharPtr) 
{   
  const char* value = (char*)"Hello Word!";
  XVARIANT    variant(value);
  XVARIANT    variant2; 
  XSTRING     string;
  XSTRING     value2;

  variant.ToString(string);
  variant2.FromString(string); 
  
  value2 = (const XSTRING&)variant2;
  
  EXPECT_EQ(value2.Compare(value, true), 0);    
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionXChar) 
{ 
  XCHAR       value = __C('A');
  XVARIANT    variant(value); 
  XVARIANT    variant2; 
  XSTRING     string; 
  XCHAR       value2; 

  variant.ToString(string); 
  variant2.FromString(string, XVARIANT_TYPE_XCHAR); 
  value2 = (XCHAR)variant2;

  EXPECT_EQ((XCHAR)value, (XCHAR)value2); 
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionXCharPtr) 
{  
  XSTRING     value;

  value.Add(__L("Hello Word!"));

  XVARIANT    variant(value);
  XVARIANT    variant2; 
  XSTRING     string;
  XSTRING     value2;

  variant.ToString(string);
  variant2.FromString(string, XVARIANT_TYPE_STRING); 
  
  value2 = (const XSTRING&)variant2;

  EXPECT_EQ(value2.Compare(value, true), 0);    
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionDateTime)   
{   
  XSTRING     datetimestr = __L("01/12/1969 12:30:30");
  XDATETIME   value;

  value.GetDateTimeFromString(datetimestr, XDATETIME_FORMAT_STANDARD);

  XVARIANT    variant(value);
  XVARIANT    variant2; 
  XSTRING     string;    
  XDATETIME   value2;

  variant.ToString(string);
  variant2.FromString(string, XVARIANT_TYPE_DATETIME); 

  value2 = variant2;

  EXPECT_EQ(value2.Compare(value), 0);              
}

  


TEST(UNITTESTS_XVARIANT_CLASSNAME, StringConversionBuffer) 
{ 
  XBUFFER     value;

  value.Add((XBYTE)0xAA);
  value.Add((XBYTE)0x55);
  value.Add((XBYTE)0xCA);
  value.Add((XBYTE)0xFE);
  value.Add((XBYTE)0x02);
  value.Add((XBYTE)0x9A);

  XVARIANT    variant(value);
  XVARIANT    variant2; 
  XSTRING     string;  
  XBUFFER     value2;  
  
  variant.ToString(string);
  variant2.FromString(string, XVARIANT_TYPE_BUFFER); 

  value2 = variant2;
 
  EXPECT_EQ(value2.Compare(value), true);            
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, DefaultConstructor) 
{ 
  XVARIANT  variant;

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_NULL);
  EXPECT_EQ(variant.IsNull(), true);
  EXPECT_EQ(variant.GetSize(), (XDWORD)0);
  EXPECT_EQ(variant.GetData(), (void*)NULL);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, GetTypeStringSupported) 
{
  XVARIANT  variant((int)1);
  XSTRING   typestr;

  EXPECT_EQ(variant.GetType(typestr), true);
  EXPECT_EQ(typestr.Compare(__L("integer"), true), 0);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, GetTypeStringUnsupported) 
{
  void*     ptr = (void*)0x1234;
  XVARIANT  variant(ptr);
  XSTRING   typestr;

  EXPECT_EQ(variant.GetType(typestr), false);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, CopyConstructorNumeric) 
{
  XVARIANT  variant((int)123);
  XVARIANT  variant2(variant);

  variant = (int)5;

  EXPECT_EQ(variant2.GetType(), XVARIANT_TYPE_INTEGER);
  EXPECT_EQ((int)variant2, 123);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, DeepCopyStringFromXString) 
{
  XSTRING   value  = __L("Hello Word!");
  XVARIANT  variant(value);

  value = __L("Bye!");

  XSTRING value2 = variant;

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_STRING);
  EXPECT_EQ(value2.Compare(__L("Hello Word!"), true), 0);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, DeepCopyBufferFromXBuffer) 
{
  XBUFFER value;
  value.Add((XBYTE)0xAA);
  value.Add((XBYTE)0x55);
  value.Add((XBYTE)0xCA);

  XVARIANT variant(value);

  value.Add((XBYTE)0xFE);

  XBUFFER value2 = variant;
  XBUFFER value3;

  value3.Add((XBYTE)0xAA);
  value3.Add((XBYTE)0x55);
  value3.Add((XBYTE)0xCA);

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_BUFFER);
  EXPECT_EQ(value2.Compare(value3), true);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, OperatorAssignSelf) 
{
  XVARIANT variant((int)123);

  variant = variant;

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_INTEGER);
  EXPECT_EQ((int)variant, 123);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, DestroySetsNullState) 
{
  XVARIANT variant((int)123);

  variant.Destroy();

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_NULL);
  EXPECT_EQ(variant.IsNull(), true);
  EXPECT_EQ(variant.GetSize(), (XDWORD)0);
  EXPECT_EQ(variant.GetData(), (void*)NULL);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, ToStringNull) 
{
  XVARIANT  variant;
  XSTRING   string;

  variant.ToString(string);

  EXPECT_EQ(string.Compare(__L("NULL"), true), 0);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, FromStringEmptyDoesNotModify) 
{
  XVARIANT  variant((int)123);
  XSTRING   string;

  variant.FromString(string, XVARIANT_TYPE_INTEGER);

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_INTEGER);
  EXPECT_EQ((int)variant, 123);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, SetTypeChangesTypeTagOnly)
{
  XVARIANT variant((int)123);

  // SetType() is documented as only changing the type tag, independent of Set() -- it does
  // not reallocate/convert the underlying data, so GetType() reflects the new tag right away.
  variant.SetType(XVARIANT_TYPE_FLOAT);

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_FLOAT);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, GetDataFromStringCharPtr)
{
  XVARIANT variant;
  char     text[] = "Hello ASCII";

  EXPECT_TRUE(variant.GetDataFromString(text));

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_STRING);

  XSTRING value = variant;
  EXPECT_EQ(value.Compare(__L("Hello ASCII"), true), 0);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, GetDataFromStringXCharPtr)
{
  XVARIANT variant;
  XCHAR*   text = __L("Hello Unicode");

  EXPECT_TRUE(variant.GetDataFromString(text));

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_STRING);

  XSTRING value = variant;
  EXPECT_EQ(value.Compare(__L("Hello Unicode"), true), 0);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, GetDataVariantCopiesFromAnotherVariant)
{
  XVARIANT source((int)456);
  XVARIANT target;

  EXPECT_EQ(true, target.GetDataVariant(source));

  EXPECT_EQ(target.GetType(), XVARIANT_TYPE_INTEGER);
  EXPECT_EQ((int)target, 456);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, GetDataVariantRejectsSelf)
{
  XVARIANT variant((int)789);

  // &value == this -> documented early-out, returns false and leaves the variant untouched.
  EXPECT_EQ(false, variant.GetDataVariant(variant));

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_INTEGER);
  EXPECT_EQ((int)variant, 789);
}


TEST(UNITTESTS_XVARIANT_CLASSNAME, OperatorVoidPointerReadBack)
{
  void*    ptr = (void*)0xDEADBEEF;
  XVARIANT variant(ptr);

  EXPECT_EQ(variant.GetType(), XVARIANT_TYPE_POINTER);

  void* readback = variant;
  EXPECT_EQ(readback, ptr);
}


}


#endif


