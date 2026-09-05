/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XFileDFU.cpp
*
* @class      UNITTESTS_XUTILS_XFILEDFU
* @brief      XUtils unit tests for XFILEDFU class
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

#include "UnitTests_XUtils_XFileDFU.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XFileDFU.h"
#include "XPath.h"
#include "XPathsManager.h"
#include "XFile.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFILEDFU
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
* @fn         static XDWORD ComputeDFUCRC(XBYTE* data, XDWORD size)
* @brief      Bitwise reimplementation of the exact reflected CRC-32 (IEEE 802.3 / zlib polynomial
*             0xEDB88320) that XFILEDFU::CheckCRC() computes against its own 256-entry CRCtable --
*             produces byte-identical results without needing to hand-copy that table here, and
*             (matching XFILEDFU::CheckCRC() exactly) does NOT apply the final ^0xFFFFFFFF
*             complement that a "standard" crc32() call normally would.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void AddRawDWORD(XBUFFER& buffer, XDWORD value)
{
  buffer.Add((XBYTE*)&value, sizeof(XDWORD));
}


static void AddRawWORD(XBUFFER& buffer, XWORD value)
{
  buffer.Add((XBYTE*)&value, sizeof(XWORD));
}


static XDWORD ComputeDFUCRC(XBYTE* data, XDWORD size)
{
  XDWORD crc = 0xFFFFFFFF;

  for(XDWORD c=0; c<size; c++)
    {
      crc ^= data[c];

      for(int bit=0; bit<8; bit++)
        {
          if(crc & 1) crc = (crc >> 1) ^ 0xEDB88320;
          else        crc = (crc >> 1);
        }
    }

  return crc;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void BuildMinimalDFUImage(XBUFFER& buffer, XBYTE lastdatabyte)
* @brief      Hand-builds one minimal, well-formed DFU (DfuSe) binary image: a prefix, one target
*             image with one data element, and a suffix with a correct trailing CRC-32 -- entirely
*             in memory, matching XFILEDFU::ReadAll()'s exact expected byte layout field-by-field.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void BuildMinimalDFUImage(XBUFFER& buffer, XBYTE lastdatabyte)
{
  buffer.Empty();

  // ---- Prefix (11 bytes) ----
  buffer.Add((XBYTE)'D'); buffer.Add((XBYTE)'f'); buffer.Add((XBYTE)'u'); buffer.Add((XBYTE)'S'); buffer.Add((XBYTE)'e');
  buffer.Add((XBYTE)1);              // version
  AddRawDWORD(buffer, 0);            // imagesize (not cross-checked by ReadAll(), stored as-is)
  buffer.Add((XBYTE)1);              // ntargets

  // ---- Image (6 + 1 + 4 + 255 + 4 + 4 = 274 bytes) ----
  buffer.Add((XBYTE)'T'); buffer.Add((XBYTE)'a'); buffer.Add((XBYTE)'r'); buffer.Add((XBYTE)'g'); buffer.Add((XBYTE)'e'); buffer.Add((XBYTE)'t');
  buffer.Add((XBYTE)0);              // alternatesetting
  AddRawDWORD(buffer, 0);            // targetnameexist
  for(int c=0; c<255; c++) buffer.Add((XBYTE)0); // targetname[255]
  AddRawDWORD(buffer, 13);           // targetsize (address+size+data of the one element below)
  AddRawDWORD(buffer, 1);            // nelements

  // ---- Element (4 + 4 + 5 = 13 bytes) ----
  AddRawDWORD(buffer, 0x08000000);   // address
  AddRawDWORD(buffer, 5);            // size
  buffer.Add((XBYTE)'H'); buffer.Add((XBYTE)'E'); buffer.Add((XBYTE)'L'); buffer.Add((XBYTE)'L');
  buffer.Add(lastdatabyte);          // last data byte -- deliberately parameterized so the CRC-mismatch
                                      // test can corrupt exactly this one byte after computing a CRC
                                      // against the well-formed value ('O').

  // ---- Suffix, minus its own CRC field (2+2+2+2+3+1 = 12 bytes) ----
  AddRawWORD(buffer, 0x0100);        // BCDdevice
  AddRawWORD(buffer, 0x1234);        // IDproduct
  AddRawWORD(buffer, 0x5678);        // IDvendor
  AddRawWORD(buffer, 0x011A);        // BCDDFU
  buffer.Add((XBYTE)'U'); buffer.Add((XBYTE)'F'); buffer.Add((XBYTE)'D'); // "UFD" signature
  buffer.Add((XBYTE)16);             // length

  // NOTE: sizes/fields above are written via AddRawDWORD/AddRawWORD (raw native-endian bytes),
  // deliberately bypassing XBUFFER::Add(XDWORD)/Add(XWORD), which always byte-swap to network
  // (big-endian) order on this little-endian host. XFILEDFU::ReadAll()/Read_Image()/Read_Element()
  // read these fields straight off disk with XFILE::Read() into plain XDWORD/XWORD variables, with
  // no un-swap -- so the on-disk bytes must already be in native/little-endian order.
  XDWORD crc = ComputeDFUCRC(buffer.Get(), buffer.GetSize());
  AddRawDWORD(buffer, crc);
}


TEST(UNITTESTS_XFILEDFU_CLASSNAME, ReadAllParsesAWellFormedPrefixImageElementAndSuffix)
{
  XPATH xpath;
  BuildTestFilePath(xpath, __L("unittests_xutils_dfu_good.dfu"));
  RemoveIfExists(xpath);

  XBUFFER filedata;
  BuildMinimalDFUImage(filedata, (XBYTE)'O'); // "HELLO"

  XFILE* rawfile = GEN_XFACTORY.Create_File();
  ASSERT_TRUE(rawfile != NULL);
  ASSERT_TRUE(rawfile->Create(xpath));
  ASSERT_TRUE(rawfile->Write(filedata.Get(), filedata.GetSize()));
  rawfile->Close();
  GEN_XFACTORY.Delete_File(rawfile);

  XFILEDFU dfu;
  ASSERT_TRUE(dfu.Open(xpath.Get(), true));
  ASSERT_TRUE(dfu.ReadAll());

  XFILEDFU_PREFIX* prefix = dfu.GetPrefix();
  ASSERT_TRUE(prefix != NULL);
  EXPECT_EQ(memcmp(prefix->signature, "DfuSe", 5), 0);
  EXPECT_EQ(prefix->version, (XBYTE)1);
  EXPECT_EQ(prefix->ntargets, (XBYTE)1);

  XVECTOR<XFILEDFU_IMAGE*>* images = dfu.GetImages();
  ASSERT_TRUE(images != NULL);
  ASSERT_EQ(images->GetSize(), (XDWORD)1);

  XFILEDFU_IMAGE* image = images->Get(0);
  ASSERT_TRUE(image != NULL);
  EXPECT_EQ(memcmp(image->signature, "Target", 6), 0);
  EXPECT_EQ(image->nelements, (XDWORD)1);
  ASSERT_EQ(image->elements.GetSize(), (XDWORD)1);

  XFILEDFU_ELEMENT* element = image->elements.Get(0);
  ASSERT_TRUE(element != NULL);
  EXPECT_EQ(element->address, (XDWORD)0x08000000);
  EXPECT_EQ(element->size, (XDWORD)5);
  ASSERT_EQ(element->data.GetSize(), (XDWORD)5);
  EXPECT_EQ(memcmp(element->data.Get(), "HELLO", 5), 0);

  XFILEDFU_SUFFIX* suffix = dfu.GetSuffix();
  ASSERT_TRUE(suffix != NULL);
  EXPECT_EQ(suffix->BCDdevice, (XWORD)0x0100);
  EXPECT_EQ(suffix->IDproduct, (XWORD)0x1234);
  EXPECT_EQ(suffix->IDvendor, (XWORD)0x5678);
  EXPECT_EQ(memcmp(suffix->signature, "UFD", 3), 0);

  dfu.Close();
  RemoveIfExists(xpath);
}


TEST(UNITTESTS_XFILEDFU_CLASSNAME, ReadAllRejectsAFileWhoseContentWasCorruptedAfterTheCRCWasComputed)
{
  XPATH xpath;
  BuildTestFilePath(xpath, __L("unittests_xutils_dfu_badcrc.dfu"));
  RemoveIfExists(xpath);

  XBUFFER filedata;
  BuildMinimalDFUImage(filedata, (XBYTE)'O'); // CRC computed for "HELLO"

  // Corrupt the last data byte AFTER the CRC was already computed and appended -- the file on
  // disk no longer matches its own trailing CRC-32.
  filedata.Get()[11 /* prefix */ + 274 /* image header */ + 8 /* element address+size */ + 4] = (XBYTE)'X';

  XFILE* rawfile = GEN_XFACTORY.Create_File();
  ASSERT_TRUE(rawfile != NULL);
  ASSERT_TRUE(rawfile->Create(xpath));
  ASSERT_TRUE(rawfile->Write(filedata.Get(), filedata.GetSize()));
  rawfile->Close();
  GEN_XFACTORY.Delete_File(rawfile);

  XFILEDFU dfu;
  ASSERT_TRUE(dfu.Open(xpath.Get(), true));
  EXPECT_FALSE(dfu.ReadAll()); // CheckCRC() must reject the corrupted content

  dfu.Close();
  RemoveIfExists(xpath);
}


TEST(UNITTESTS_XFILEDFU_CLASSNAME, OpenOfANonexistentFileFailsGracefully)
{
  XPATH xpath;
  BuildTestFilePath(xpath, __L("unittests_xutils_dfu_does_not_exist.dfu"));
  RemoveIfExists(xpath);

  XFILEDFU dfu;
  EXPECT_FALSE(dfu.Open(xpath.Get(), true));
}


} // namespace TEST_XFILEDFU
#endif
