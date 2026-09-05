/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XFileRIFF.cpp
*
* @class      UNITTESTS_XUTILS_XFILERIFF
* @brief      XUtils unit tests for XFILERIFF class
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

#include "UnitTests_XUtils_XFileRIFF.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XFileRIFF.h"
#include "XPath.h"
#include "XPathsManager.h"
#include "XFile.h"
#include "XBuffer.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFILERIFF
{

// Test files are written under this GEN application's own portable ROOT path (via
// GEN_XPATHSMANAGER, exactly as UnitTests_XUtils.cpp's own bootstrap resolves it) instead of a
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
* @fn         static void WriteFourCC(XBUFFER& buffer, const char* fourcc)
* @brief      Appends a 4-byte little-endian FOURCC (exactly how XFILERIFF::ReadNodeLists() reads
*             its "type" XDWORD off disk -- as raw bytes, no byte-swapping) to a buffer.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void WriteFourCC(XBUFFER& buffer, const char* fourcc)
{
  buffer.Add((XBYTE)fourcc[0]);
  buffer.Add((XBYTE)fourcc[1]);
  buffer.Add((XBYTE)fourcc[2]);
  buffer.Add((XBYTE)fourcc[3]);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void WriteRawSizeDWORD(XBUFFER& buffer, XDWORD value)
* @brief      Appends a 4-byte size field in the local host's *native* byte order -- deliberately
*             NOT via XBUFFER::Add(XDWORD), which always byte-swaps to network (big-endian) order
*             on a little-endian host. XFILERIFF::ReadAllLists()/ReadNodeLists() read their size
*             XDWORDs straight off disk with XFILE::Read() into a plain XDWORD variable, with no
*             un-swap -- so on this (little-endian) host the on-disk bytes must already be in
*             native/little-endian order for those reads to reconstruct the intended value.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void WriteRawSizeDWORD(XBUFFER& buffer, XDWORD value)
{
  buffer.Add((XBYTE*)&value, sizeof(XDWORD));
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void BuildNestedRIFFFile(XBUFFER& buffer)
* @brief      Hand-builds a small, well-formed RIFF binary: "RIFF" root (typelist "TEST") holding
*             one plain chunk ("AAAA", 4 bytes of data) and one nested LIST ("SUBT") holding one
*             more plain chunk ("BBBB", 4 bytes of data) -- verified size fields hand-computed
*             exactly the way XFILERIFF::ReadAllLists()/ReadNodeLists() expect them.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void BuildNestedRIFFFile(XBUFFER& buffer)
{
  buffer.Empty();

  WriteFourCC(buffer, "RIFF");
  WriteRawSizeDWORD(buffer, 40);      // size: "TEST"(4) + Child1(12) + Child2(24) = 40
  WriteFourCC(buffer, "TEST");       // typelist

  // Child1: plain chunk "AAAA", 4 bytes of data.
  WriteFourCC(buffer, "AAAA");
  WriteRawSizeDWORD(buffer, 4);
  buffer.Add((XBYTE)'D'); buffer.Add((XBYTE)'A'); buffer.Add((XBYTE)'T'); buffer.Add((XBYTE)'1');

  // Child2: nested LIST "SUBT" containing one plain chunk "BBBB", 4 bytes of data.
  WriteFourCC(buffer, "LIST");
  WriteRawSizeDWORD(buffer, 16);      // size: "SUBT"(4) + Child2a(12) = 16
  WriteFourCC(buffer, "SUBT");
  WriteFourCC(buffer, "BBBB");
  WriteRawSizeDWORD(buffer, 4);
  buffer.Add((XBYTE)'D'); buffer.Add((XBYTE)'A'); buffer.Add((XBYTE)'T'); buffer.Add((XBYTE)'2');
}


TEST(UNITTESTS_XFILERIFF_CLASSNAME, GetTypeFromStringMatchesTheWellKnownRIFFAndLISTConstants)
{
  XFILERIFF riff;

  EXPECT_EQ(riff.GetTypeFromString(__L("RIFF")), (XDWORD)XFILERIFF_TYPE_RIFF);
  EXPECT_EQ(riff.GetTypeFromString(__L("LIST")), (XDWORD)XFILERIFF_TYPE_LIST);
  EXPECT_EQ(riff.GetTypeFromString(__L("INFO")), (XDWORD)XFILERIFF_TYPE_INFO);
  EXPECT_EQ(riff.GetTypeFromString(NULL), (XDWORD)0);
}


TEST(UNITTESTS_XFILERIFF_CLASSNAME, ListAccessorsGetSetRoundTripAndIsTypeList)
{
  XFILERIFF_LIST list;

  list.SetType(XFILERIFF_TYPE_RIFF);
  EXPECT_EQ(list.GetType(), (XDWORD)XFILERIFF_TYPE_RIFF);
  EXPECT_TRUE(list.IsTypeList());

  list.SetType(0x41414141); // an arbitrary plain fourcc, not RIFF/LIST
  EXPECT_FALSE(list.IsTypeList());

  list.SetSize(123);
  EXPECT_EQ(list.GetSize(), (XDWORD)123);

  list.SetTypeList(XFILERIFF_TYPE_INFO);
  EXPECT_EQ(list.GetTypeList(), (XDWORD)XFILERIFF_TYPE_INFO);

  list.SetPositionFileData(999);
  EXPECT_EQ(list.GetPositionFileData(), (XQWORD)999);
}


TEST(UNITTESTS_XFILERIFF_CLASSNAME, ReadAllListsParsesNestedListsAndChunksFromARealFile)
{
  XPATH xpath;
  BuildTestFilePath(xpath, __L("unittests_xutils_riff_good.riff"));
  RemoveIfExists(xpath);

  XBUFFER filedata;
  BuildNestedRIFFFile(filedata);

  XFILE* rawfile = GEN_XFACTORY.Create_File();
  ASSERT_TRUE(rawfile != NULL);
  ASSERT_TRUE(rawfile->Create(xpath));
  ASSERT_TRUE(rawfile->Write(filedata.Get(), filedata.GetSize()));
  rawfile->Close();
  GEN_XFACTORY.Delete_File(rawfile);

  XFILERIFF riff;
  ASSERT_TRUE(riff.Open(xpath.Get(), true));
  ASSERT_TRUE(riff.ReadAllLists());

  // Plain chunk "AAAA", a direct child of the "TEST" root.
  XFILERIFF_LIST* chunkA = riff.GetChunk(__L("AAAA"));
  ASSERT_TRUE(chunkA != NULL);
  EXPECT_EQ(chunkA->GetSize(), (XDWORD)4);

  XBUFFER dataA;
  ASSERT_TRUE(riff.GetChunkData(chunkA, dataA));
  ASSERT_EQ(dataA.GetSize(), (XDWORD)4);
  EXPECT_EQ(memcmp(dataA.Get(), "DAT1", 4), 0);

  // Nested LIST "SUBT" and its own chunk "BBBB", found both by DWORD type and by string.
  XFILERIFF_LIST* listSUBT = riff.GetList(__L("SUBT"));
  ASSERT_TRUE(listSUBT != NULL);
  EXPECT_TRUE(listSUBT->IsTypeList());
  EXPECT_EQ(listSUBT->GetTypeList(), (XDWORD)riff.GetTypeFromString(__L("SUBT")));

  XFILERIFF_LIST* chunkB = riff.GetChunk(__L("BBBB"));
  ASSERT_TRUE(chunkB != NULL);

  XBYTE readbuf[4] = { 0,0,0,0 };
  XDWORD readsize = 0;
  ASSERT_TRUE(riff.GetChunkData(chunkB, readbuf, readsize));
  EXPECT_EQ(readsize, (XDWORD)4);
  EXPECT_EQ(memcmp(readbuf, "DAT2", 4), 0);

  // A chunk scoped to the wrong father must not be found.
  XFILERIFF_LIST* wrongfather = riff.GetChunk(riff.GetTypeFromString(__L("BBBB")), riff.GetTypeFromString(__L("TEST")));
  EXPECT_TRUE(wrongfather == (XFILERIFF_LIST*)NULL);

  // Looking up a chunk name as if it were a list (and vice-versa) must fail.
  EXPECT_TRUE(riff.GetList(__L("AAAA")) == (XFILERIFF_LIST*)NULL);
  EXPECT_TRUE(riff.GetChunk(__L("SUBT")) == (XFILERIFF_LIST*)NULL);

  riff.Close();
  RemoveIfExists(xpath);
}


TEST(UNITTESTS_XFILERIFF_CLASSNAME, ReadAllListsRejectsWrongMagicZeroSizeAndTruncatedFiles)
{
  // Wrong magic (neither "RIFF" nor "LIST").
  {
    XPATH xpath;
    BuildTestFilePath(xpath, __L("unittests_xutils_riff_badmagic.riff"));
    RemoveIfExists(xpath);

    XBUFFER filedata;
    WriteFourCC(filedata, "JUNK");
    WriteRawSizeDWORD(filedata, 8);
    WriteFourCC(filedata, "TEST");

    XFILE* rawfile = GEN_XFACTORY.Create_File();
    ASSERT_TRUE(rawfile->Create(xpath));
    ASSERT_TRUE(rawfile->Write(filedata.Get(), filedata.GetSize()));
    rawfile->Close();
    GEN_XFACTORY.Delete_File(rawfile);

    XFILERIFF riff;
    ASSERT_TRUE(riff.Open(xpath.Get(), true));
    EXPECT_FALSE(riff.ReadAllLists());
    riff.Close();
    RemoveIfExists(xpath);
  }

  // size == 0 must be rejected outright.
  {
    XPATH xpath;
    BuildTestFilePath(xpath, __L("unittests_xutils_riff_zerosize.riff"));
    RemoveIfExists(xpath);

    XBUFFER filedata;
    WriteFourCC(filedata, "RIFF");
    WriteRawSizeDWORD(filedata, 0);

    XFILE* rawfile = GEN_XFACTORY.Create_File();
    ASSERT_TRUE(rawfile->Create(xpath));
    ASSERT_TRUE(rawfile->Write(filedata.Get(), filedata.GetSize()));
    rawfile->Close();
    GEN_XFACTORY.Delete_File(rawfile);

    XFILERIFF riff;
    ASSERT_TRUE(riff.Open(xpath.Get(), true));
    EXPECT_FALSE(riff.ReadAllLists());
    riff.Close();
    RemoveIfExists(xpath);
  }

  // Truncated right after the declared size (missing the typelist FOURCC entirely).
  {
    XPATH xpath;
    BuildTestFilePath(xpath, __L("unittests_xutils_riff_truncated.riff"));
    RemoveIfExists(xpath);

    XBUFFER filedata;
    WriteFourCC(filedata, "RIFF");
    WriteRawSizeDWORD(filedata, 40);

    XFILE* rawfile = GEN_XFACTORY.Create_File();
    ASSERT_TRUE(rawfile->Create(xpath));
    ASSERT_TRUE(rawfile->Write(filedata.Get(), filedata.GetSize()));
    rawfile->Close();
    GEN_XFACTORY.Delete_File(rawfile);

    XFILERIFF riff;
    ASSERT_TRUE(riff.Open(xpath.Get(), true));
    EXPECT_FALSE(riff.ReadAllLists());
    riff.Close();
    RemoveIfExists(xpath);
  }
}


TEST(UNITTESTS_XFILERIFF_CLASSNAME, CreateListNodeAndCreateChunkNodeBuildCorrectlyPopulatedNodes)
{
  XFILERIFF riff;

  XFILERIFF_LIST_NODE* listnode = riff.CreateListNode(__L("LIST"), __L("INFO"));
  ASSERT_TRUE(listnode != NULL);
  ASSERT_TRUE(listnode->GetData() != NULL);
  EXPECT_EQ(listnode->GetData()->GetType(), (XDWORD)XFILERIFF_TYPE_LIST);
  EXPECT_EQ(listnode->GetData()->GetTypeList(), (XDWORD)XFILERIFF_TYPE_INFO);
  EXPECT_TRUE(listnode->GetData()->IsTypeList());

  XFILERIFF_LIST_NODE* chunknode = riff.CreateChunkNode(__L("DATA"), 128);
  ASSERT_TRUE(chunknode != NULL);
  ASSERT_TRUE(chunknode->GetData() != NULL);
  EXPECT_EQ(chunknode->GetData()->GetSize(), (XDWORD)128);
  EXPECT_FALSE(chunknode->GetData()->IsTypeList());

  // XTREE_NODE's destructor unconditionally deletes its own "data" pointer (DeleteContents()),
  // so deleting the node alone is enough -- deleting GetData() separately as well would be a
  // double free.
  GEN_DELETE listnode;
  GEN_DELETE chunknode;
}


TEST(UNITTESTS_XFILERIFF_CLASSNAME, WriteListToFileWritesAPlainChunkHeaderAndDataAtItsPosition)
{
  XPATH xpath;
  BuildTestFilePath(xpath, __L("unittests_xutils_riff_write.riff"));
  RemoveIfExists(xpath);

  XFILERIFF riff;
  ASSERT_TRUE(riff.Create(xpath.Get()));

  XFILERIFF_LIST chunk;
  chunk.SetType(riff.GetTypeFromString(__L("DATA")));
  chunk.SetPositionFileData(0);

  XBYTE payload[4] = { 'W', 'X', 'Y', 'Z' };
  ASSERT_TRUE(riff.WriteListToFile(&chunk, payload, 4));

  riff.Close();

  // Verify the raw bytes on disk directly, independent of XFILERIFF's own read path.
  XFILE* rawfile = GEN_XFACTORY.Create_File();
  ASSERT_TRUE(rawfile->Open(xpath, true));

  XDWORD type = 0, size = 0;
  XBYTE  data[4] = {0,0,0,0};

  ASSERT_TRUE(rawfile->Read((XBYTE*)&type, sizeof(XDWORD)));
  ASSERT_TRUE(rawfile->Read((XBYTE*)&size, sizeof(XDWORD)));
  ASSERT_TRUE(rawfile->Read(data, 4));

  EXPECT_EQ(type, (XDWORD)riff.GetTypeFromString(__L("DATA")));
  EXPECT_EQ(size, (XDWORD)4); // WriteListToFile() overrides the stored size with the real datasize
  EXPECT_EQ(memcmp(data, payload, 4), 0);

  rawfile->Close();
  GEN_XFACTORY.Delete_File(rawfile);

  RemoveIfExists(xpath);
}


TEST(UNITTESTS_XFILERIFF_CLASSNAME, AdjustSizeOfListsComputesTotalSizeOfAOneLevelChunkList)
{
  XPATH xpath;
  BuildTestFilePath(xpath, __L("unittests_xutils_riff_adjust.riff"));
  RemoveIfExists(xpath);

  XFILERIFF riff;
  ASSERT_TRUE(riff.Create(xpath.Get()));

  XFILERIFF_LIST_NODE* root = riff.CreateListNode(__L("LIST"), __L("INFO"));
  ASSERT_TRUE(root != NULL);
  root->GetData()->SetPositionFileData(0);
  riff.GetXTreeList()->SetRoot(root);

  XFILERIFF_LIST_NODE* child = riff.CreateChunkNode(__L("ICMT"), 6);
  ASSERT_TRUE(child != NULL);
  root->AddChild(child);

  XDWORD computed = riff.AdjustSizeOfLists(root);

  // One plain chunk child: its own header (type+size, 8 bytes) + its declared data size (6).
  EXPECT_EQ(computed, (XDWORD)(8 + 6));
  EXPECT_EQ(root->GetData()->GetSize(), (XDWORD)(computed + sizeof(XDWORD)));

  riff.Close();
  RemoveIfExists(xpath);
}


} // namespace TEST_XFILERIFF
#endif
