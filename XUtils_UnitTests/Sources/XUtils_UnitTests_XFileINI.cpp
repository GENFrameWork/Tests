/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XFileINI.cpp
*
* @class      XUTILS_UNITTESTS_XFILEINI
* @brief      XUtils unit tests for XFILEINI class
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

#include "XUtils_UnitTests_XFileINI.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XFileINI.h"
#include "XPath.h"
#include "XPathsManager.h"
#include "XFile.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFILEINI
{

// Test files are written under this GEN application's own portable ROOT path (via
// GEN_XPATHSMANAGER, exactly as XUtils_UnitTests.cpp's own bootstrap resolves it) instead of a
// hardcoded Unix path like "/tmp/..." -- "/tmp" does not exist on Windows, which silently made
// every Create()/Open() call in this file fail there (confirmed against a real Windows/clang-cl
// run: every disk-touching test here failed with "Create(xpath) == false").
static void BuildTestFilePath(XPATH& xpath, const XCHAR* relativename)
{
  GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpath);
  xpath += relativename;
}



/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void RemoveIfExists(XPATH& xpath)
* @brief      Best-effort scratch-file cleanup via the real XFILE factory.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void RemoveIfExists(XPATH& xpath)
{
  XFILE* xfile = GEN_XFACTORY.Create_File();
  if(xfile)
    {
      if(xfile->Exist(xpath)) xfile->Erase(xpath);
      GEN_XFACTORY.Delete_File(xfile);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void WriteRawTextFile(XPATH& xpath, const char* content)
* @brief      Hand-writes a raw ini file using plain libc I/O (deliberately not going through
*             XFILEINI's own writer), so parsing tests exercise ConvertFromLines() against content
*             this batch fully controls, independent of anything XFILEINI's own write path does.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void WriteRawTextFile(XPATH& xpath, const char* content)
{
  XBUFFER ascii;
  xpath.ConvertToASCII(ascii);

  FILE* file = fopen(ascii.GetPtrChar(), "wb");
  if(file)
    {
      fwrite(content, 1, strlen(content), file);
      fclose(file);
    }
}


TEST(UNITTEST_XFILEINI_CLASSNAME, CreateSectionWriteValueReadValueInMemory)
{
  XFILEINI fileini;

  EXPECT_TRUE(fileini.CreateSection(__L("SECTION")));

  XSTRING key(__L("key1"));
  XSTRING value(__L("value1"));

  EXPECT_TRUE(fileini.WriteValue(__L("SECTION"), key, value));

  XSTRING readback;
  EXPECT_TRUE(fileini.ReadValue(__L("SECTION"), key, readback));
  EXPECT_FALSE(readback.Compare(__L("value1"), false));

  // WriteValue() auto-creates the section if it does not already exist yet.
  XSTRING key2(__L("autokey"));
  XSTRING value2(__L("autovalue"));
  EXPECT_TRUE(fileini.WriteValue(__L("NEWSECTION"), key2, value2));

  XSTRING readback2;
  EXPECT_TRUE(fileini.ReadValue(__L("NEWSECTION"), key2, readback2));
  EXPECT_FALSE(readback2.Compare(__L("autovalue"), false));
}


TEST(UNITTEST_XFILEINI_CLASSNAME, CreateSectionFailsWhenSectionAlreadyExists)
{
  XFILEINI fileini;

  EXPECT_TRUE(fileini.CreateSection(__L("DUP")));
  EXPECT_FALSE(fileini.CreateSection(__L("DUP")));

  // Case-insensitive: a differently-cased spelling of the same section must also be rejected.
  EXPECT_FALSE(fileini.CreateSection(__L("dup")));
}


TEST(UNITTEST_XFILEINI_CLASSNAME, GetSectionAndSelectSectionAreCaseInsensitive)
{
  XFILEINI fileini;

  fileini.CreateSection(__L("MixedCase"));

  EXPECT_NE(fileini.GetSection(__L("MixedCase")), (XFILEINISECTION*)NULL);
  EXPECT_NE(fileini.GetSection(__L("MIXEDCASE")), (XFILEINISECTION*)NULL);
  EXPECT_NE(fileini.GetSection(__L("mixedcase")), (XFILEINISECTION*)NULL);

  EXPECT_EQ(fileini.GetSection(__L("DOES_NOT_EXIST")), (XFILEINISECTION*)NULL);

  EXPECT_TRUE(fileini.SelectSection(__L("mixedcase")));
  EXPECT_FALSE(fileini.SelectSection(__L("still_missing")));
}


TEST(UNITTEST_XFILEINI_CLASSNAME, DeleteKeyAndDeleteSection)
{
  XFILEINI fileini;

  XSTRING key(__L("removeme"));
  XSTRING value(__L("value"));
  fileini.WriteValue(__L("SEC"), key, value);

  XSTRING readback;
  EXPECT_TRUE(fileini.ReadValue(__L("SEC"), key, readback));

  EXPECT_TRUE(fileini.DeleteKey(__L("SEC"), key));
  EXPECT_FALSE(fileini.ReadValue(__L("SEC"), key, readback));

  // Deleting an already-deleted key must fail cleanly.
  EXPECT_FALSE(fileini.DeleteKey(__L("SEC"), key));

  EXPECT_TRUE(fileini.DeleteSection(__L("SEC")));
  EXPECT_EQ(fileini.GetSection(__L("SEC")), (XFILEINISECTION*)NULL);

  // A section that no longer exists cannot be deleted again.
  EXPECT_FALSE(fileini.DeleteSection(__L("SEC")));
}


TEST(UNITTEST_XFILEINI_CLASSNAME, GetNextKeyIterationAndResetSelectionKey)
{
  XFILEINISECTION section;

  XSTRING sectionname(__L("ITERSECTION"));
  section.SetName(sectionname);

  XSTRING k1(__L("k1")), v1(__L("v1"));
  XSTRING k2(__L("k2")), v2(__L("v2"));
  XSTRING k3(__L("k3")), v3(__L("v3"));

  section.SetKey(k1, v1);
  section.SetKey(k2, v2);
  section.SetKey(k3, v3);

  XSTRING key, value;
  int count = 0;

  while(section.GetNextKey(key, value)) count++;

  EXPECT_EQ(count, 3);

  // Exhausted: one more call must fail.
  EXPECT_FALSE(section.GetNextKey(key, value));

  EXPECT_TRUE(section.ResetSelectionKey());

  count = 0;
  while(section.GetNextKey(key, value)) count++;
  EXPECT_EQ(count, 3);
}


TEST(UNITTEST_XFILEINI_CLASSNAME, OpenParsesHandWrittenINIWithMultipleSectionsAndKeys)
{
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfileini_parse.ini"));
  RemoveIfExists(xpath);

  WriteRawTextFile(xpath,
    "[SECTION1]\n"
    "key1=value1\n"
    "key2=value2\n"
    "[SECTION2]\n"
    "keyA=valueA\n");

  XFILEINI reader;
  ASSERT_TRUE(reader.Open(xpath, true));

  XSTRING value;

  EXPECT_TRUE(reader.ReadValue(__L("SECTION1"), __L("key1"), value));
  EXPECT_FALSE(value.Compare(__L("value1"), false));

  EXPECT_TRUE(reader.ReadValue(__L("SECTION1"), __L("key2"), value));
  EXPECT_FALSE(value.Compare(__L("value2"), false));

  // Case-insensitive section/key lookup on the parsed content too.
  EXPECT_TRUE(reader.ReadValue(__L("section2"), __L("keyA"), value));
  EXPECT_FALSE(value.Compare(__L("valueA"), false));

  EXPECT_FALSE(reader.ReadValue(__L("SECTION1"), __L("nosuchkey"), value));
  EXPECT_FALSE(reader.ReadValue(__L("NOSUCHSECTION"), __L("key1"), value));

  reader.Close();
  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILEINI_CLASSNAME, RemarksAreRecognizedAndTextIsCaptured)
{
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfileini_remarks.ini"));
  RemoveIfExists(xpath);

  WriteRawTextFile(xpath,
    "; a whole line remark\n"
    "[REMARKSECTION]\n"
    "onlykey=onlyvalue ; trailing remark\n");

  XFILEINI reader;
  ASSERT_TRUE(reader.Open(xpath, true));

  // The key's value must be correctly separated from its trailing remark.
  XSTRING value;
  EXPECT_TRUE(reader.ReadValue(__L("REMARKSECTION"), __L("onlykey"), value));
  EXPECT_FALSE(value.Compare(__L("onlyvalue"), false));

  XVECTOR<XFILEINIREMARK*>* remarks = reader.GetRemarks();
  ASSERT_NE(remarks, (XVECTOR<XFILEINIREMARK*>*)NULL);
  EXPECT_EQ(remarks->GetSize(), (XDWORD)2);

  bool foundwholeline = false;
  bool foundinkey      = false;

  for(XDWORD c = 0; c < remarks->GetSize(); c++)
    {
      XFILEINIREMARK* remark = remarks->Get(c);
      ASSERT_NE(remark, (XFILEINIREMARK*)NULL);

      if(remark->GetType() == XFILEINI_TYPEREMARK_ALL_LINE)
        {
          foundwholeline = true;
          EXPECT_NE(remark->GetTextRemark()->Find(__L("a whole line remark"), false, 0), XSTRING_NOTFOUND);
        }

      if(remark->GetType() == XFILEINI_TYPEREMARK_IN_KEY)
        {
          foundinkey = true;
          EXPECT_NE(remark->GetTextRemark()->Find(__L("trailing remark"), false, 0), XSTRING_NOTFOUND);
        }
    }

  EXPECT_TRUE(foundwholeline);
  EXPECT_TRUE(foundinkey);

  reader.Close();
  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILEINI_CLASSNAME, WriteThenCloseThenReopenRoundTrip)
{
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfileini_roundtrip.ini"));
  RemoveIfExists(xpath);

  {
    XFILEINI writer;

    ASSERT_TRUE(writer.Create(xpath));

    writer.CreateSection(__L("License"));

    XSTRING k1(__L("Key1")), v1(__L("Value1"));
    XSTRING k2(__L("Key2")), v2(__L("Value2"));

    writer.WriteValue(__L("License"), k1, v1);
    writer.WriteValue(__L("License"), k2, v2);

    EXPECT_TRUE(writer.Close());
  }

  {
    XFILEINI reader;
    ASSERT_TRUE(reader.Open(xpath, true));

    XSTRING value;

    // ConvertFromLines() upper-cases every parsed section name (Line_IsSection ->
    // ToUpperCase()), so the section written as "License" is expected back as "LICENSE" --
    // but GetSection()/SelectSection()'s own case-insensitive Compare() means looking it up
    // with the original mixed-case spelling still works either way.
    EXPECT_TRUE(reader.ReadValue(__L("License"), __L("Key1"), value));
    EXPECT_FALSE(value.Compare(__L("Value1"), false));

    EXPECT_TRUE(reader.ReadValue(__L("LICENSE"), __L("Key2"), value));
    EXPECT_FALSE(value.Compare(__L("Value2"), false));

    XFILEINISECTION* section = reader.GetSection(__L("license"));
    ASSERT_NE(section, (XFILEINISECTION*)NULL);
    EXPECT_FALSE(section->GetName()->Compare(__L("LICENSE"), false));

    reader.Close();
  }

  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILEINI_CLASSNAME, ReadKeyMapBulkReadsMultipleKeysAtOnce)
{
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfileini_keymap.ini"));
  RemoveIfExists(xpath);

  WriteRawTextFile(xpath,
    "[BULK]\n"
    "first=1\n"
    "second=2\n"
    "third=3\n");

  XFILEINI reader;
  ASSERT_TRUE(reader.Open(xpath, true));

  // XFILEININKEYMAP(map) must be invoked in the SAME scope as the array declaration -- passing a
  // decayed pointer into a helper function would silently produce a too-small count (a real,
  // well-known C-array-decay hazard baked into this macro-driven API, per the analysis report).
  XFILEINIKEYMAP map[3];
  map[0].key = __L("first");
  map[1].key = __L("second");
  map[2].key = __L("third");

  ASSERT_EQ(XFILEININKEYMAP(map), (XDWORD)3);

  EXPECT_TRUE(reader.ReadKeyMap(__L("BULK"), map, XFILEININKEYMAP(map)));

  EXPECT_FALSE(map[0].value.Compare(__L("1"), false));
  EXPECT_FALSE(map[1].value.Compare(__L("2"), false));
  EXPECT_FALSE(map[2].value.Compare(__L("3"), false));

  reader.Close();
  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILEINI_CLASSNAME, WriteValueSingleArgOverloadNowActuallyWrites)
{
  // FIXED: XFILEINI::WriteValue(XCHAR* key, XSTRING& value) (XFileINI.cpp, near the bottom of the
  // WriteValue overload family) now does `XSTRING _key(key); return WriteValue(_key,value);` --
  // previously it called ReadValue() instead of WriteValue() (an evident copy-paste mistake), so
  // this exact overload never wrote anything at all -- it silently performed a READ into `value`
  // instead, against whatever section was currently selected.
  XFILEINI fileini;

  fileini.CreateSection(__L("ONLYSECTION"));

  XSTRING existingkey(__L("existingkey"));
  XSTRING existingvalue(__L("existingvalue"));
  fileini.WriteValue(__L("ONLYSECTION"), existingkey, existingvalue); // via the 3-arg overload

  XSTRING newvalue(__L("this is now genuinely written"));

  // Calling the single-key-arg overload with the pre-existing key name now genuinely overwrites
  // the stored value with `newvalue`, instead of silently reading the old value back into it.
  EXPECT_TRUE(fileini.WriteValue(__L("existingkey"), newvalue));
  EXPECT_FALSE(newvalue.Compare(__L("this is now genuinely written"), false)); // untouched by the call

  // Proof the store was genuinely updated: re-reading "existingkey" the normal way now shows the
  // NEW value, not the original "existingvalue".
  XSTRING readback;
  EXPECT_TRUE(fileini.ReadValue(__L("ONLYSECTION"), existingkey, readback));
  EXPECT_FALSE(readback.Compare(__L("this is now genuinely written"), false));
}


TEST(UNITTEST_XFILEINI_CLASSNAME, DeleteAllSectionsAndDeleteAllRemarks)
{
  XFILEINI fileini;

  fileini.CreateSection(__L("A"));
  fileini.CreateSection(__L("B"));

  EXPECT_TRUE(fileini.DeleteAllSections());
  EXPECT_EQ(fileini.GetSection(__L("A")), (XFILEINISECTION*)NULL);
  EXPECT_EQ(fileini.GetSection(__L("B")), (XFILEINISECTION*)NULL);

  // Nothing left -- must fail cleanly rather than crash.
  EXPECT_FALSE(fileini.DeleteAllSections());

  // No remarks were ever parsed into this in-memory-only instance.
  EXPECT_FALSE(fileini.DeleteAllRemarks());
}


}
#endif
