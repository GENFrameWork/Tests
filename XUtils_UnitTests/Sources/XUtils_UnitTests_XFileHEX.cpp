/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XFileHEX.cpp
*
* @class      XUTILS_UNITTESTS_XFILEHEX
* @brief      XUtils unit tests for XFILEHEX class
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

#include "XUtils_UnitTests_XFileHEX.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XFileHEX.h"
#include "XPath.h"
#include "XPathsManager.h"
#include "XFile.h"
#include "XString.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFILEHEX
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


// ----------------------------------------------------------------------------------------------
// Two well-known, hand-verified Intel-HEX records used throughout this file. Both checksums were
// computed by hand against the real algorithm (two's complement of the sum of every byte from the
// length field up to, but not including, the checksum byte itself) and cross-checked against
// XFILEHEX_ENTRY::CalculeCRC() directly:
//
//   ":0300300002337A1E" -- a 3-byte DATA record at address 0x0030, payload {0x02,0x33,0x7A}.
//        bytes (excluding ':' and the final CRC byte) = 03 00 30 00 02 33 7A
//        sum = 0x03+0x00+0x30+0x00+0x02+0x33+0x7A = 0xE2 ; CRC = (~0xE2)+1 = 0x1E
//
//   ":00000001FF"        -- the standard End-Of-File record (0 data bytes, type 0x01).
//        bytes = 00 00 00 01 ; sum = 0x01 ; CRC = (~0x01)+1 = 0xFF
// ----------------------------------------------------------------------------------------------
#define KNOWNGOOD_DATA_LINE   __L(":0300300002337A1E")
#define KNOWNGOOD_EOF_LINE    __L(":00000001FF")


TEST(UNITTEST_XFILEHEX_CLASSNAME, EntryGetSetSizeDataAddressEntryTypeAndData)
{
  XFILEHEX_ENTRY entry;

  EXPECT_EQ(entry.GetSizeData(), 0);
  EXPECT_EQ(entry.GetAddress(), 0);
  EXPECT_EQ(entry.GetEntryType(), XFILEHEX_ENTRYTYPE_NODEFINED);

  entry.SetSizeData(3);
  entry.SetAddress(0x0030);
  entry.SetEntryType(XFILEHEX_ENTRYTYPE_DATA);

  EXPECT_EQ(entry.GetSizeData(), 3);
  EXPECT_EQ(entry.GetAddress(), 0x0030);
  EXPECT_EQ(entry.GetEntryType(), XFILEHEX_ENTRYTYPE_DATA);

  ASSERT_TRUE(entry.GetData() != NULL);
  entry.GetData()->Add((XBYTE)0x02);
  entry.GetData()->Add((XBYTE)0x33);
  entry.GetData()->Add((XBYTE)0x7A);

  ASSERT_EQ(entry.GetData()->GetSize(), (XDWORD)3);
  EXPECT_EQ(entry.GetData()->Get()[0], 0x02);
  EXPECT_EQ(entry.GetData()->Get()[1], 0x33);
  EXPECT_EQ(entry.GetData()->Get()[2], 0x7A);
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, CalculeCRCMatchesKnownGoodDataRecordChecksum)
{
  XFILEHEX_ENTRY entry;

  XBUFFER dataCRC;
  dataCRC.Add((XBYTE)0x03);
  dataCRC.Add((XBYTE)0x00);
  dataCRC.Add((XBYTE)0x30);
  dataCRC.Add((XBYTE)0x00);
  dataCRC.Add((XBYTE)0x02);
  dataCRC.Add((XBYTE)0x33);
  dataCRC.Add((XBYTE)0x7A);

  EXPECT_EQ(entry.CalculeCRC(dataCRC), (XBYTE)0x1E);
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, CalculeCRCMatchesKnownGoodEOFRecordChecksum)
{
  XFILEHEX_ENTRY entry;

  XBUFFER dataCRC;
  dataCRC.Add((XBYTE)0x00);
  dataCRC.Add((XBYTE)0x00);
  dataCRC.Add((XBYTE)0x00);
  dataCRC.Add((XBYTE)0x01);

  EXPECT_EQ(entry.CalculeCRC(dataCRC), (XBYTE)0xFF);
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, DecodeLineDecodesKnownGoodDataRecord)
{
  XFILEHEX     filehex;
  XFILEHEX_ENTRY entry;
  XSTRING      line(KNOWNGOOD_DATA_LINE);

  ASSERT_TRUE(filehex.DecodeLine(&line, entry));

  EXPECT_EQ(entry.GetSizeData(), 3);
  EXPECT_EQ(entry.GetAddress(), 0x0030);
  EXPECT_EQ(entry.GetEntryType(), XFILEHEX_ENTRYTYPE_DATA);

  ASSERT_EQ(entry.GetData()->GetSize(), (XDWORD)3);
  EXPECT_EQ(entry.GetData()->Get()[0], 0x02);
  EXPECT_EQ(entry.GetData()->Get()[1], 0x33);
  EXPECT_EQ(entry.GetData()->Get()[2], 0x7A);
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, DecodeLineDecodesKnownGoodEOFRecord)
{
  XFILEHEX     filehex;
  XFILEHEX_ENTRY entry;
  XSTRING      line(KNOWNGOOD_EOF_LINE);

  ASSERT_TRUE(filehex.DecodeLine(&line, entry));

  EXPECT_EQ(entry.GetSizeData(), 0);
  EXPECT_EQ(entry.GetAddress(), 0x0000);
  EXPECT_EQ(entry.GetEntryType(), XFILEHEX_ENTRYTYPE_EOF);
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, DecodeLineRejectsCorruptChecksum)
{
  // Same record as the known-good data line above, but with the last checksum digit flipped
  // (0x1E -> 0x1F), so the recomputed CRC no longer matches the CRC stored in the line.
  XFILEHEX     filehex;
  XFILEHEX_ENTRY entry;
  XSTRING      line(__L(":0300300002337A1F"));

  EXPECT_FALSE(filehex.DecodeLine(&line, entry));
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, DecodeLineRejectsLineNotStartingWithColon)
{
  XFILEHEX     filehex;
  XFILEHEX_ENTRY entry;
  XSTRING      line(__L("0300300002337A1E"));

  EXPECT_FALSE(filehex.DecodeLine(&line, entry));
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, DecodeLineRejectsEmptyLine)
{
  XFILEHEX     filehex;
  XFILEHEX_ENTRY entry;
  XSTRING      line;

  EXPECT_FALSE(filehex.DecodeLine(&line, entry));
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, DecodeLineRejectsNullLinePointer)
{
  XFILEHEX     filehex;
  XFILEHEX_ENTRY entry;

  EXPECT_FALSE(filehex.DecodeLine(NULL, entry));
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, EncodeLineProducesKnownGoodDataRecordVerbatim)
{
  XFILEHEX filehex;

  XFILEHEX_ENTRY entry;
  entry.SetSizeData(3);
  entry.SetAddress(0x0030);
  entry.SetEntryType(XFILEHEX_ENTRYTYPE_DATA);
  entry.GetData()->Add((XBYTE)0x02);
  entry.GetData()->Add((XBYTE)0x33);
  entry.GetData()->Add((XBYTE)0x7A);

  XSTRING line;
  ASSERT_TRUE(filehex.EncodeLine(&entry, line));

  EXPECT_FALSE(line.Compare(KNOWNGOOD_DATA_LINE, false));
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, EncodeLineProducesKnownGoodEOFRecordVerbatim)
{
  XFILEHEX filehex;

  XFILEHEX_ENTRY entry;
  entry.SetSizeData(0);
  entry.SetAddress(0x0000);
  entry.SetEntryType(XFILEHEX_ENTRYTYPE_EOF);

  XSTRING line;
  ASSERT_TRUE(filehex.EncodeLine(&entry, line));

  EXPECT_FALSE(line.Compare(KNOWNGOOD_EOF_LINE, false));
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, EncodeThenDecodeRoundTripPreservesAllFields)
{
  XFILEHEX filehex;

  XFILEHEX_ENTRY original;
  original.SetSizeData(4);
  original.SetAddress(0x1234);
  original.SetEntryType(XFILEHEX_ENTRYTYPE_DATA);
  original.GetData()->Add((XBYTE)0xDE);
  original.GetData()->Add((XBYTE)0xAD);
  original.GetData()->Add((XBYTE)0xBE);
  original.GetData()->Add((XBYTE)0xEF);

  XSTRING line;
  ASSERT_TRUE(filehex.EncodeLine(&original, line));

  XFILEHEX_ENTRY decoded;
  ASSERT_TRUE(filehex.DecodeLine(&line, decoded));

  EXPECT_EQ(decoded.GetSizeData(), original.GetSizeData());
  EXPECT_EQ(decoded.GetAddress(), original.GetAddress());
  EXPECT_EQ(decoded.GetEntryType(), original.GetEntryType());

  ASSERT_EQ(decoded.GetData()->GetSize(), original.GetData()->GetSize());
  for(XDWORD c=0; c<original.GetData()->GetSize(); c++)
    {
      EXPECT_EQ(decoded.GetData()->Get()[c], original.GetData()->Get()[c]);
    }
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, GetNEntrysStartsAtZero)
{
  XFILEHEX filehex;
  EXPECT_EQ(filehex.GetNEntrys(), (XDWORD)0);
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, EntryAddParsesAKnownGoodLineAndIncrementsCount)
{
  XFILEHEX filehex;

  XSTRING line(KNOWNGOOD_DATA_LINE);
  EXPECT_TRUE(filehex.Entry_Add(&line));

  ASSERT_EQ(filehex.GetNEntrys(), (XDWORD)1);

  XFILEHEX_ENTRY* entry = filehex.Entry_Get(0);
  ASSERT_TRUE(entry != NULL);
  EXPECT_EQ(entry->GetAddress(), 0x0030);
  EXPECT_EQ(entry->GetEntryType(), XFILEHEX_ENTRYTYPE_DATA);
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, EntryAddRejectsCorruptChecksumLineAndCountStaysZero)
{
  XFILEHEX filehex;

  XSTRING line(__L(":0300300002337A1F")); // corrupted checksum, see DecodeLineRejectsCorruptChecksum
  EXPECT_FALSE(filehex.Entry_Add(&line));

  EXPECT_EQ(filehex.GetNEntrys(), (XDWORD)0);
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, EntryGetByAddressAndTypeFindsTheRightEntryAmongSeveral)
{
  XFILEHEX filehex;

  XSTRING line1(KNOWNGOOD_DATA_LINE);       // address 0x0030, DATA
  XSTRING line2(KNOWNGOOD_EOF_LINE);        // address 0x0000, EOF

  ASSERT_TRUE(filehex.Entry_Add(&line1));
  ASSERT_TRUE(filehex.Entry_Add(&line2));

  ASSERT_EQ(filehex.GetNEntrys(), (XDWORD)2);

  XFILEHEX_ENTRY* dataentry = filehex.Entry_Get((XWORD)0x0030, XFILEHEX_ENTRYTYPE_DATA);
  ASSERT_TRUE(dataentry != NULL);
  EXPECT_EQ(dataentry->GetSizeData(), 3);

  XFILEHEX_ENTRY* eofentry = filehex.Entry_Get((XWORD)0x0000, XFILEHEX_ENTRYTYPE_EOF);
  ASSERT_TRUE(eofentry != NULL);
  EXPECT_EQ(eofentry->GetEntryType(), XFILEHEX_ENTRYTYPE_EOF);

  // A real address that only exists under a different type must not match.
  EXPECT_TRUE(filehex.Entry_Get((XWORD)0x0030, XFILEHEX_ENTRYTYPE_EOF) == NULL);
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, EntryGetByIndexReturnsEntriesInInsertionOrder)
{
  XFILEHEX filehex;

  XSTRING line1(KNOWNGOOD_DATA_LINE);
  XSTRING line2(KNOWNGOOD_EOF_LINE);

  ASSERT_TRUE(filehex.Entry_Add(&line1));
  ASSERT_TRUE(filehex.Entry_Add(&line2));

  ASSERT_TRUE(filehex.Entry_Get(0) != NULL);
  ASSERT_TRUE(filehex.Entry_Get(1) != NULL);

  EXPECT_EQ(filehex.Entry_Get(0)->GetEntryType(), XFILEHEX_ENTRYTYPE_DATA);
  EXPECT_EQ(filehex.Entry_Get(1)->GetEntryType(), XFILEHEX_ENTRYTYPE_EOF);
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, EntryDeleteByAddressAndTypeRemovesOnlyThatEntry)
{
  XFILEHEX filehex;

  XSTRING line1(KNOWNGOOD_DATA_LINE);
  XSTRING line2(KNOWNGOOD_EOF_LINE);

  ASSERT_TRUE(filehex.Entry_Add(&line1));
  ASSERT_TRUE(filehex.Entry_Add(&line2));
  ASSERT_EQ(filehex.GetNEntrys(), (XDWORD)2);

  EXPECT_TRUE(filehex.Entry_Delete((XWORD)0x0030, XFILEHEX_ENTRYTYPE_DATA));
  EXPECT_EQ(filehex.GetNEntrys(), (XDWORD)1);

  // The remaining entry must be the EOF one, not the deleted DATA one.
  EXPECT_TRUE(filehex.Entry_Get((XWORD)0x0030, XFILEHEX_ENTRYTYPE_DATA) == NULL);
  EXPECT_TRUE(filehex.Entry_Get((XWORD)0x0000, XFILEHEX_ENTRYTYPE_EOF)  != NULL);

  // Deleting an address/type pair that no longer exists must fail cleanly.
  EXPECT_FALSE(filehex.Entry_Delete((XWORD)0x0030, XFILEHEX_ENTRYTYPE_DATA));
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, EntryDeleteByIndexRemovesTheRightEntry)
{
  XFILEHEX filehex;

  XSTRING line1(KNOWNGOOD_DATA_LINE);
  XSTRING line2(KNOWNGOOD_EOF_LINE);

  ASSERT_TRUE(filehex.Entry_Add(&line1));
  ASSERT_TRUE(filehex.Entry_Add(&line2));

  EXPECT_TRUE(filehex.Entry_Delete(0));
  ASSERT_EQ(filehex.GetNEntrys(), (XDWORD)1);

  // What used to be index 1 (the EOF entry) is now index 0.
  EXPECT_EQ(filehex.Entry_Get(0)->GetEntryType(), XFILEHEX_ENTRYTYPE_EOF);
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, EntryDeleteAllRemovesEveryEntryAndFailsWhenAlreadyEmpty)
{
  XFILEHEX filehex;

  XSTRING line1(KNOWNGOOD_DATA_LINE);
  XSTRING line2(KNOWNGOOD_EOF_LINE);

  ASSERT_TRUE(filehex.Entry_Add(&line1));
  ASSERT_TRUE(filehex.Entry_Add(&line2));

  EXPECT_TRUE(filehex.Entry_DeleteAll());
  EXPECT_EQ(filehex.GetNEntrys(), (XDWORD)0);

  EXPECT_FALSE(filehex.Entry_DeleteAll()); // nothing left
}


TEST(UNITTEST_XFILEHEX_CLASSNAME, WriteThenReopenWholeFileRoundTrip)
{
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfilehex_roundtrip.hex"));
  RemoveIfExists(xpath);

  {
    XFILEHEX writer;
    ASSERT_TRUE(writer.Create(xpath, XFILETXTFORMATCHAR_ASCII, XFILETXTTYPELF_0A));

    XSTRING line1(KNOWNGOOD_DATA_LINE);
    XSTRING line2(KNOWNGOOD_EOF_LINE);

    ASSERT_TRUE(writer.Entry_Add(&line1));
    ASSERT_TRUE(writer.Entry_Add(&line2));

    ASSERT_TRUE(writer.EncodeAllLines());
    EXPECT_TRUE(writer.WriteAllFile());
    EXPECT_TRUE(writer.Close());
  }

  {
    XFILEHEX reader;
    ASSERT_TRUE(reader.Open(xpath, true));
    ASSERT_TRUE(reader.DecodeAllLines());

    ASSERT_EQ(reader.GetNEntrys(), (XDWORD)2);

    XFILEHEX_ENTRY* dataentry = reader.Entry_Get((XWORD)0x0030, XFILEHEX_ENTRYTYPE_DATA);
    ASSERT_TRUE(dataentry != NULL);
    EXPECT_EQ(dataentry->GetSizeData(), 3);
    ASSERT_EQ(dataentry->GetData()->GetSize(), (XDWORD)3);
    EXPECT_EQ(dataentry->GetData()->Get()[0], 0x02);
    EXPECT_EQ(dataentry->GetData()->Get()[1], 0x33);
    EXPECT_EQ(dataentry->GetData()->Get()[2], 0x7A);

    XFILEHEX_ENTRY* eofentry = reader.Entry_Get((XWORD)0x0000, XFILEHEX_ENTRYTYPE_EOF);
    ASSERT_TRUE(eofentry != NULL);

    reader.Close();
  }

  RemoveIfExists(xpath);
}


} // namespace TEST_XFILEHEX
#endif
