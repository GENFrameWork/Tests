/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XFileCSV.cpp
*
* @class      XUTILS_UNITTESTS_XFILECSV
* @brief      XUtils unit tests for XFILECSV class
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

#include "XUtils_UnitTests_XFileCSV.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XFileCSV.h"
#include "XPath.h"
#include "XPathsManager.h"
#include "XFile.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFILECSV
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
* @brief      Hand-writes a raw CSV file using plain libc I/O (deliberately not going through
*             XFILECSV's own writer), so parsing tests exercise real, independently-authored
*             content.
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


TEST(UNITTEST_XFILECSV_CLASSNAME, RecordAddElementGetElementAndGetNElements)
{
  XFILECSV_RECORD record;

  EXPECT_EQ(record.GetNElements(), 0);

  EXPECT_TRUE(record.AddElement(__L("first")));
  EXPECT_TRUE(record.AddElement(__L("second")));

  XSTRING third(__L("third"));
  EXPECT_TRUE(record.AddElement(third));

  ASSERT_EQ(record.GetNElements(), 3);

  EXPECT_STREQ(record.GetElement(0), __L("first"));
  EXPECT_STREQ(record.GetElement(1), __L("second"));
  EXPECT_STREQ(record.GetElement(2), __L("third"));

  XSTRING readback;
  EXPECT_TRUE(record.GetElement(1, readback));
  EXPECT_FALSE(readback.Compare(__L("second"), false));

  // Out-of-range access must return NULL/false, never crash.
  EXPECT_EQ(record.GetElement(99), (XCHAR*)NULL);
  EXPECT_FALSE(record.GetElement(99, readback));
}


TEST(UNITTEST_XFILECSV_CLASSNAME, RecordDeleteElementAndDeleteAllElements)
{
  XFILECSV_RECORD record;

  record.AddElement(__L("a"));
  record.AddElement(__L("b"));
  record.AddElement(__L("c"));

  ASSERT_EQ(record.GetNElements(), 3);

  EXPECT_TRUE(record.DeleteElement(1));
  ASSERT_EQ(record.GetNElements(), 2);
  EXPECT_STREQ(record.GetElement(0), __L("a"));
  EXPECT_STREQ(record.GetElement(1), __L("c"));

  EXPECT_TRUE(record.DeleteAllElements());
  EXPECT_EQ(record.GetNElements(), 0);

  // Nothing left to delete -- must fail cleanly.
  EXPECT_FALSE(record.DeleteAllElements());
}


TEST(UNITTEST_XFILECSV_CLASSNAME, RecordCopyNowActuallyPopulatesTheDestination)
{
  // FIXED: XFILECSV_RECORD::Copy() (XFileCSV.cpp) now calls `elements.Add(string)` after copying
  // each source element's text into a freshly allocated XSTRING -- previously that freshly
  // allocated XSTRING was silently discarded (leaked) instead of being appended to this object's
  // own `elements` vector, so the method reported success while leaving the destination empty.
  XFILECSV_RECORD source;
  source.AddElement(__L("colA"));
  source.AddElement(__L("colB"));
  source.AddElement(__L("colC"));

  XFILECSV_RECORD destination;
  ASSERT_EQ(destination.GetNElements(), 0);

  EXPECT_TRUE(destination.Copy(&source));

  // destination now genuinely carries source's elements.
  ASSERT_EQ(destination.GetNElements(), 3);
  EXPECT_STREQ(destination.GetElement(0), __L("colA"));
  EXPECT_STREQ(destination.GetElement(1), __L("colB"));
  EXPECT_STREQ(destination.GetElement(2), __L("colC"));

  // A NULL source, or a source with zero elements, is correctly rejected regardless.
  EXPECT_FALSE(destination.Copy(NULL));

  XFILECSV_RECORD emptysource;
  EXPECT_FALSE(destination.Copy(&emptysource));
}


TEST(UNITTEST_XFILECSV_CLASSNAME, SetSeparatorAcceptsOnlyCommaOrSemicolon)
{
  XFILECSV csv;

  EXPECT_EQ(csv.GetSeparator(), __C(';')); // documented default (XFileCSV.cpp Clean())

  EXPECT_TRUE(csv.SetSeparator(__C(',')));
  EXPECT_EQ(csv.GetSeparator(), __C(','));

  EXPECT_TRUE(csv.SetSeparator(__C(';')));
  EXPECT_EQ(csv.GetSeparator(), __C(';'));

  // Any other character must be rejected, leaving the separator unchanged.
  EXPECT_FALSE(csv.SetSeparator(__C('|')));
  EXPECT_EQ(csv.GetSeparator(), __C(';'));
}


TEST(UNITTEST_XFILECSV_CLASSNAME, AddRecordReadRecordAndGetNRecords)
{
  XFILECSV csv;

  EXPECT_EQ(csv.GetNRecords(), 0);
  EXPECT_EQ(csv.ReadRecord(0), (XFILECSV_RECORD*)NULL);

  XFILECSV_RECORD* record1 = GEN_NEW XFILECSV_RECORD();
  record1->AddElement(__L("r1c1"));
  record1->AddElement(__L("r1c2"));

  XFILECSV_RECORD* record2 = GEN_NEW XFILECSV_RECORD();
  record2->AddElement(__L("r2c1"));
  record2->AddElement(__L("r2c2"));

  EXPECT_TRUE(csv.AddRecord(record1));
  EXPECT_TRUE(csv.AddRecord(record2));

  ASSERT_EQ(csv.GetNRecords(), 2);

  XFILECSV_RECORD* readback0 = csv.ReadRecord(0);
  ASSERT_NE(readback0, (XFILECSV_RECORD*)NULL);
  EXPECT_STREQ(readback0->GetElement(0), __L("r1c1"));

  XFILECSV_RECORD* readback1 = csv.ReadRecord(1);
  ASSERT_NE(readback1, (XFILECSV_RECORD*)NULL);
  EXPECT_STREQ(readback1->GetElement(0), __L("r2c1"));

  // Out-of-range must return NULL, never crash.
  EXPECT_EQ(csv.ReadRecord(99), (XFILECSV_RECORD*)NULL);

  // AddRecord() rejects a NULL record.
  EXPECT_FALSE(csv.AddRecord(NULL));
}


TEST(UNITTEST_XFILECSV_CLASSNAME, WriteRecordReplacesAtIndexAndDeleteRecordRemovesIt)
{
  XFILECSV csv;

  XFILECSV_RECORD* original = GEN_NEW XFILECSV_RECORD();
  original->AddElement(__L("original"));
  csv.AddRecord(original);

  XFILECSV_RECORD* replacement = GEN_NEW XFILECSV_RECORD();
  replacement->AddElement(__L("replacement"));

  EXPECT_TRUE(csv.WriteRecord(0, replacement));
  ASSERT_EQ(csv.GetNRecords(), 1);
  EXPECT_STREQ(csv.ReadRecord(0)->GetElement(0), __L("replacement"));

  // Out-of-range WriteRecord must fail cleanly (and not touch/leak the record it was given).
  XFILECSV_RECORD outofrange;
  EXPECT_FALSE(csv.WriteRecord(99, &outofrange));

  EXPECT_TRUE(csv.DeleteRecord(0));
  EXPECT_EQ(csv.GetNRecords(), 0);

  EXPECT_FALSE(csv.DeleteRecord(0));

  EXPECT_FALSE(csv.DeleteAllRecords()); // nothing left
}


TEST(UNITTEST_XFILECSV_CLASSNAME, OpenParsesHandWrittenCommaSeparatedRows)
{
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfilecsv_comma.csv"));
  RemoveIfExists(xpath);

  WriteRawTextFile(xpath,
    "val1,val2,val3\n"
    "val4,val5,val6\n");

  XFILECSV reader;
  ASSERT_TRUE(reader.Open(xpath, true));

  // No header was pre-declared, so HaveHeader() is false and BOTH lines land as plain records
  // (see OpenWithoutPreDeclaredHeaderTreatsEveryLineAsARecord below for why).
  ASSERT_EQ(reader.GetNRecords(), 2);

  XFILECSV_RECORD* row0 = reader.ReadRecord(0);
  ASSERT_NE(row0, (XFILECSV_RECORD*)NULL);
  ASSERT_EQ(row0->GetNElements(), 3);
  EXPECT_STREQ(row0->GetElement(0), __L("val1"));
  EXPECT_STREQ(row0->GetElement(1), __L("val2"));
  EXPECT_STREQ(row0->GetElement(2), __L("val3"));

  XFILECSV_RECORD* row1 = reader.ReadRecord(1);
  ASSERT_NE(row1, (XFILECSV_RECORD*)NULL);
  EXPECT_STREQ(row1->GetElement(0), __L("val4"));
  EXPECT_STREQ(row1->GetElement(2), __L("val6"));

  // CreateRecordOfLine() (XFileCSV.cpp) auto-detects the separator per parsed line and calls
  // SetSeparator() accordingly -- a comma-only line leaves the separator set to ','.
  EXPECT_EQ(reader.GetSeparator(), __C(','));

  reader.Close();
  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILECSV_CLASSNAME, SemicolonIsPreferredOverCommaWhenBothArePresentOnALine)
{
  // CreateRecordOfLine() (XFileCSV.cpp) always searches for ';' FIRST and only falls back to ','
  // if no ';' is found on the line -- so a line containing both characters is always split on
  // ';', with any ',' left embedded inside whichever field contains it. This is real, existing
  // behavior (not a crash), captured here concretely rather than assumed.
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfilecsv_mixed.csv"));
  RemoveIfExists(xpath);

  WriteRawTextFile(xpath, "first;second,stillsecond;third\n");

  XFILECSV reader;
  ASSERT_TRUE(reader.Open(xpath, true));

  ASSERT_EQ(reader.GetNRecords(), 1);

  XFILECSV_RECORD* row0 = reader.ReadRecord(0);
  ASSERT_NE(row0, (XFILECSV_RECORD*)NULL);
  ASSERT_EQ(row0->GetNElements(), 3);
  EXPECT_STREQ(row0->GetElement(0), __L("first"));
  EXPECT_STREQ(row0->GetElement(1), __L("second,stillsecond")); // the comma stayed embedded
  EXPECT_STREQ(row0->GetElement(2), __L("third"));

  EXPECT_EQ(reader.GetSeparator(), __C(';'));

  reader.Close();
  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILECSV_CLASSNAME, NoQuoteHandlingMeansAFieldContainingTheSeparatorCannotRoundTrip)
{
  // Documents a genuine functional gap flagged by the analysis report: XFILECSV has no
  // quote/escape-character API anywhere (confirmed by reading XFileCSV.h/.cpp in full) -- a field
  // whose real content includes the active separator character is indistinguishable from a field
  // boundary, so it always gets split into two elements instead of round-tripping as one. This is
  // not a crash and not being "fixed" here -- it is a real, load-bearing limitation any caller of
  // this class must know about.
  XFILECSV writer;
  writer.SetSeparator(__C(','));

  XFILECSV_RECORD* record = GEN_NEW XFILECSV_RECORD();
  record->AddElement(__L("value, with an embedded comma"));
  record->AddElement(__L("plain value"));
  writer.AddRecord(record);

  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfilecsv_noquote.csv"));
  RemoveIfExists(xpath);

  ASSERT_TRUE(writer.Create(xpath));
  EXPECT_TRUE(writer.Close());

  XFILECSV reader;
  reader.SetSeparator(__C(','));
  ASSERT_TRUE(reader.Open(xpath, true));

  ASSERT_EQ(reader.GetNRecords(), 1);

  XFILECSV_RECORD* readback = reader.ReadRecord(0);
  ASSERT_NE(readback, (XFILECSV_RECORD*)NULL);

  // The bug/gap in action: what was written as 2 elements comes back as 3, because the embedded
  // comma inside the first field's text was indistinguishable from a real field separator.
  EXPECT_EQ(readback->GetNElements(), 3);
  EXPECT_STREQ(readback->GetElement(0), __L("value"));
  EXPECT_STREQ(readback->GetElement(1), __L(" with an embedded comma"));
  EXPECT_STREQ(readback->GetElement(2), __L("plain value"));

  reader.Close();
  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILECSV_CLASSNAME, WriteThenCloseThenReopenRoundTripWithoutHeader)
{
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfilecsv_roundtrip.csv"));
  RemoveIfExists(xpath);

  {
    XFILECSV writer;
    writer.SetSeparator(__C(','));

    ASSERT_TRUE(writer.Create(xpath));

    XFILECSV_RECORD* record1 = GEN_NEW XFILECSV_RECORD();
    record1->AddElement(__L("Alice"));
    record1->AddElement(__L("30"));
    writer.AddRecord(record1);

    XFILECSV_RECORD* record2 = GEN_NEW XFILECSV_RECORD();
    record2->AddElement(__L("Bob"));
    record2->AddElement(__L("25"));
    writer.AddRecord(record2);

    EXPECT_TRUE(writer.Close());
  }

  {
    XFILECSV reader;
    reader.SetSeparator(__C(','));

    ASSERT_TRUE(reader.Open(xpath, true));
    ASSERT_EQ(reader.GetNRecords(), 2);

    EXPECT_STREQ(reader.ReadRecord(0)->GetElement(0), __L("Alice"));
    EXPECT_STREQ(reader.ReadRecord(0)->GetElement(1), __L("30"));
    EXPECT_STREQ(reader.ReadRecord(1)->GetElement(0), __L("Bob"));
    EXPECT_STREQ(reader.ReadRecord(1)->GetElement(1), __L("25"));

    reader.Close();
  }

  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILECSV_CLASSNAME, OpenWithoutPreDeclaredHeaderTreatsEveryLineAsARecord)
{
  // Real, concrete XUtils behavior worth documenting explicitly (a design quirk, not merely
  // untested): XFILECSV::Open() calls "Serialization(true, HaveHeader())" -- but HaveHeader()
  // is evaluated on a freshly-constructed reader BEFORE any content has been parsed, and
  // XFILECSV's header is never auto-detected from file content; it can only ever become
  // non-empty via an explicit, prior SetHeader()/GetHeader()->AddElement() call. So opening any
  // CSV file that has a real header row, without the caller pre-declaring one first, silently
  // parses that header row as an ordinary data record -- there is no way to ask XFILECSV to
  // "auto-detect" a header purely from the file's own content.
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfilecsv_header_quirk.csv"));
  RemoveIfExists(xpath);

  WriteRawTextFile(xpath,
    "name,age\n"
    "Carol,40\n");

  XFILECSV reader;
  EXPECT_FALSE(reader.HaveHeader());

  ASSERT_TRUE(reader.Open(xpath, true));

  EXPECT_FALSE(reader.HaveHeader());
  ASSERT_EQ(reader.GetNRecords(), 2); // the header row "name,age" became record[0], not the header

  EXPECT_STREQ(reader.ReadRecord(0)->GetElement(0), __L("name"));
  EXPECT_STREQ(reader.ReadRecord(1)->GetElement(0), __L("Carol"));

  reader.Close();
  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILECSV_CLASSNAME, PreDeclaringHeaderViaSetHeaderNowWorksAndMakesOpenSkipTheHeaderRow)
{
  // FIXED: continues the previous test's finding -- since XFILECSV_RECORD::Copy() (XFileCSV.cpp)
  // now genuinely appends the copied elements instead of discarding them, the documented
  // SetHeader(XFILECSV_RECORD*) entry point can now be used to pre-declare a usable, non-empty
  // header, and HaveHeader() correctly reports true right after calling it (previously SetHeader()
  // always left GetHeader()->GetNElements() at 0, and the only working route was to reach into
  // GetHeader()'s live record directly and call AddElement() on it).
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfilecsv_header_predeclared.csv"));
  RemoveIfExists(xpath);

  WriteRawTextFile(xpath,
    "name,age\n"
    "Dave,50\n");

  XFILECSV reader;

  XFILECSV_RECORD placeholderheader;
  placeholderheader.AddElement(__L("placeholder"));
  reader.SetHeader(&placeholderheader);
  EXPECT_TRUE(reader.HaveHeader());
  ASSERT_EQ(reader.GetHeader()->GetNElements(), 1);
  EXPECT_STREQ(reader.GetHeader()->GetElement(0), __L("placeholder"));

  ASSERT_TRUE(reader.Open(xpath, true));

  ASSERT_EQ(reader.GetNRecords(), 1); // only the "Dave,50" data row -- the header line was skipped
  EXPECT_STREQ(reader.ReadRecord(0)->GetElement(0), __L("Dave"));
  EXPECT_STREQ(reader.ReadRecord(0)->GetElement(1), __L("50"));

  // GetHeader() is still NOT reset before parsing -- CreateRecordOfLine() (XFileCSV.cpp) only ever
  // APPENDS elements onto whatever record it is given, it never clears it first (this part of the
  // original behavior is unchanged). So the real header line parsed from the file lands AFTER the
  // pre-declared placeholder, rather than replacing it.
  ASSERT_EQ(reader.GetHeader()->GetNElements(), 3);
  EXPECT_STREQ(reader.GetHeader()->GetElement(0), __L("placeholder"));
  EXPECT_STREQ(reader.GetHeader()->GetElement(1), __L("name"));
  EXPECT_STREQ(reader.GetHeader()->GetElement(2), __L("age"));

  reader.Close();
  RemoveIfExists(xpath);
}


}
#endif
