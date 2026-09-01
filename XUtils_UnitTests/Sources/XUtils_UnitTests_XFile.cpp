/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XFile.cpp
*
* @class      XUTILS_UNITTESTS_XFILE
* @brief      XUtils unit tests for XFILE / XFILECONTAINER class
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

#include "XUtils_UnitTests_XFile.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XFile.h"
#include "XPath.h"
#include "XPathsManager.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFILE
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
* @fn         static XFILE* CreateConcreteFile()
* @brief      XFILE is an abstract class (Exist/Open/Create/SetSize/GetPosition/SetPosition/Read/
*             Write/Flush/Erase/Rename/CreateStructHandle/DeleteStructHandle/ActualizeSize are all
*             pure virtual) -- it can only be exercised through the platform-concrete subclass the
*             application's own factory creates (XLINUXFILE on this build), exactly like XDIR's own
*             GEN_XFACTORY.Create_Dir() pattern (XUtils_UnitTests_XDir.cpp).
* @ingroup    UNIT TEST
*
* @return     XFILE* : Pointer to the requested object; NULL if it is not available.
*
* --------------------------------------------------------------------------------------------------------------------*/
static XFILE* CreateConcreteFile()
{
  return GEN_XFACTORY.Create_File();
}


TEST(UNITTEST_XFILE_CLASSNAME, FactoryCreatesConcreteInstance)
{
  XFILE* xfile = CreateConcreteFile();
  ASSERT_NE(xfile, (XFILE*)NULL);

  EXPECT_FALSE(xfile->IsOpen());

  GEN_XFACTORY.Delete_File(xfile);
}


TEST(UNITTEST_XFILE_CLASSNAME, ExistReturnsFalseForMissingFile)
{
  XFILE* xfile = CreateConcreteFile();
  ASSERT_NE(xfile, (XFILE*)NULL);

  XPATH missing; BuildTestFilePath(missing, __L("xutils_unittests_xfile_definitely_does_not_exist.bin"));

  EXPECT_FALSE(xfile->Exist(missing));
  EXPECT_FALSE(xfile->Exist(missing.Get()));

  GEN_XFACTORY.Delete_File(xfile);
}


TEST(UNITTEST_XFILE_CLASSNAME, CreateWriteCloseThenOpenReadRoundTrip)
{
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfile_roundtrip.bin"));

  // Defensive cleanup from any previous interrupted run.
  {
    XFILE* cleanup = CreateConcreteFile();
    if(cleanup)
      {
        if(cleanup->Exist(xpath)) cleanup->Erase(xpath);
        GEN_XFACTORY.Delete_File(cleanup);
      }
  }

  XBYTE payload[16] = { 'X','U','T','I','L','S',' ','X','F','I','L','E',' ','1','2','3' };

  {
    XFILE* writer = CreateConcreteFile();
    ASSERT_NE(writer, (XFILE*)NULL);

    ASSERT_TRUE(writer->Create(xpath));
    EXPECT_TRUE(writer->IsOpen());
    // (IsReadOnly() reads false here on both platforms -- Create() is inherently read-write.
    // See IsReadOnlyNeverReflectsTheOpenModeItWasGivenBug below for the platform difference
    // that shows up once a file is opened read-only instead.)

    EXPECT_TRUE(writer->Write(payload, sizeof(payload)));
    EXPECT_TRUE(writer->Flush());

    EXPECT_EQ(writer->GetSize(), (XQWORD)sizeof(payload));

    EXPECT_TRUE(writer->Close());

    GEN_XFACTORY.Delete_File(writer);
  }

  {
    XFILE* existchecker = CreateConcreteFile();
    EXPECT_TRUE(existchecker->Exist(xpath));
    GEN_XFACTORY.Delete_File(existchecker);
  }

  {
    XFILE* reader = CreateConcreteFile();
    ASSERT_NE(reader, (XFILE*)NULL);

    ASSERT_TRUE(reader->Open(xpath, true));
    EXPECT_TRUE(reader->IsOpen());

    // FIXED: see IsReadOnlyNeverReflectsTheOpenModeItWasGivenBug below -- XLINUXFILE::Open() now
    // assigns its `isreadonly` argument to the member IsReadOnly() reads, exactly like
    // XWINDOWSFILE::Open() already did, so IsReadOnly() now genuinely reflects the true
    // (read-only) open mode used just above on both platforms.
    EXPECT_TRUE(reader->IsReadOnly());

    EXPECT_EQ(reader->GetSize(), (XQWORD)sizeof(payload));

    XBYTE readback[16];
    memset(readback, 0, sizeof(readback));

    EXPECT_TRUE(reader->Read(readback, (XDWORD)sizeof(readback)));
    EXPECT_EQ(memcmp(payload, readback, sizeof(payload)), 0);

    EXPECT_TRUE(reader->Close());

    GEN_XFACTORY.Delete_File(reader);
  }

  {
    XFILE* eraser = CreateConcreteFile();
    ASSERT_NE(eraser, (XFILE*)NULL);

    EXPECT_TRUE(eraser->Erase(xpath));
    EXPECT_FALSE(eraser->Exist(xpath));

    GEN_XFACTORY.Delete_File(eraser);
  }
}


TEST(UNITTEST_XFILE_CLASSNAME, WriteXBufferConvenienceOverloadMatchesRawWrite)
{
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfile_writebuffer.bin"));

  {
    XFILE* cleanup = CreateConcreteFile();
    if(cleanup->Exist(xpath)) cleanup->Erase(xpath);
    GEN_XFACTORY.Delete_File(cleanup);
  }

  XFILE* xfile = CreateConcreteFile();
  ASSERT_NE(xfile, (XFILE*)NULL);

  ASSERT_TRUE(xfile->Create(xpath));

  XBUFFER xbuffer;
  xbuffer.Add((XBYTE)'A');
  xbuffer.Add((XBYTE)'B');
  xbuffer.Add((XBYTE)'C');

  EXPECT_TRUE(xfile->Write(xbuffer));
  EXPECT_EQ(xfile->GetSize(), (XQWORD)3);

  xfile->Close();
  GEN_XFACTORY.Delete_File(xfile);

  XFILE* eraser = CreateConcreteFile();
  eraser->Erase(xpath);
  GEN_XFACTORY.Delete_File(eraser);
}


TEST(UNITTEST_XFILE_CLASSNAME, SetPositionAndGetPositionSeek)
{
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfile_seek.bin"));

  {
    XFILE* cleanup = CreateConcreteFile();
    if(cleanup->Exist(xpath)) cleanup->Erase(xpath);
    GEN_XFACTORY.Delete_File(cleanup);
  }

  XFILE* xfile = CreateConcreteFile();
  ASSERT_NE(xfile, (XFILE*)NULL);

  ASSERT_TRUE(xfile->Create(xpath));

  XBYTE tenbytes[10] = { 0,1,2,3,4,5,6,7,8,9 };
  ASSERT_TRUE(xfile->Write(tenbytes, sizeof(tenbytes)));

  XQWORD position = 999;
  EXPECT_TRUE(xfile->GetPosition(position));
  EXPECT_EQ(position, (XQWORD)sizeof(tenbytes));

  EXPECT_TRUE(xfile->SetPosition(3));
  EXPECT_TRUE(xfile->GetPosition(position));
  EXPECT_EQ(position, (XQWORD)3);

  XBYTE onebyte = 0xFF;
  EXPECT_TRUE(xfile->Read(&onebyte, (XDWORD)1));
  EXPECT_EQ(onebyte, 3); // byte at offset 3 was written as value 3

  // Seeking past the end of the file must fail (XLINUXFILE::SetPosition rejects positions beyond
  // the cached size), leaving the position unmoved.
  EXPECT_FALSE(xfile->SetPosition(9999));

  xfile->Close();
  GEN_XFACTORY.Delete_File(xfile);

  XFILE* eraser = CreateConcreteFile();
  eraser->Erase(xpath);
  GEN_XFACTORY.Delete_File(eraser);
}


TEST(UNITTEST_XFILE_CLASSNAME, RenameMovesFileToNewPath)
{
  XPATH original; BuildTestFilePath(original, __L("xutils_unittests_xfile_renameorig.bin"));
  XPATH renamed; BuildTestFilePath(renamed, __L("xutils_unittests_xfile_renamednew.bin"));

  {
    XFILE* cleanup = CreateConcreteFile();
    if(cleanup->Exist(original)) cleanup->Erase(original);
    if(cleanup->Exist(renamed))  cleanup->Erase(renamed);
    GEN_XFACTORY.Delete_File(cleanup);
  }

  XFILE* xfile = CreateConcreteFile();
  ASSERT_NE(xfile, (XFILE*)NULL);

  ASSERT_TRUE(xfile->Create(original));
  XBYTE onebyte = 'Z';
  xfile->Write(&onebyte, (XDWORD)1);
  xfile->Close();

  EXPECT_TRUE(xfile->Rename(original, renamed));
  EXPECT_FALSE(xfile->Exist(original));
  EXPECT_TRUE(xfile->Exist(renamed));

  xfile->Erase(renamed);

  GEN_XFACTORY.Delete_File(xfile);
}


TEST(UNITTEST_XFILE_CLASSNAME, GetPathNameFileReturnsLastOpenedOrCreatedPath)
{
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfile_pathname.bin"));

  {
    XFILE* cleanup = CreateConcreteFile();
    if(cleanup->Exist(xpath)) cleanup->Erase(xpath);
    GEN_XFACTORY.Delete_File(cleanup);
  }

  XFILE* xfile = CreateConcreteFile();
  ASSERT_NE(xfile, (XFILE*)NULL);

  ASSERT_TRUE(xfile->Create(xpath));

  XCHAR* namestored = xfile->GetPathNameFile();
  ASSERT_NE(namestored, (XCHAR*)NULL);

  XSTRING storedasstring(namestored);
  EXPECT_FALSE(storedasstring.Compare(xpath.Get(), false));

  xfile->Close();
  xfile->Erase(xpath);

  GEN_XFACTORY.Delete_File(xfile);
}


TEST(UNITTEST_XFILE_CLASSNAME, IsReadOnlyNowReflectsTheOpenModeItWasGiven)
{
  // FIXED: XLINUXFILE::Open(XCHAR* xpath, bool isreadonly) (XLINUXFile.cpp) now does
  // "this->isreadonly = isreadonly;" up front, exactly like XWINDOWSFILE::Open() already did --
  // previously it only ever read its `isreadonly` argument to pick an fopen() mode string ("rb" vs
  // "r+b"), never assigning that value to `this->isreadonly` (the protected XFILE member
  // IsReadOnly() actually returns), so IsReadOnly() unconditionally reported false for every
  // XLINUXFILE regardless of how it was opened. Now both platforms consistently report the true
  // open mode.
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfile_isreadonlybug.bin"));

  {
    XFILE* cleanup = CreateConcreteFile();
    if(cleanup->Exist(xpath)) cleanup->Erase(xpath);
    GEN_XFACTORY.Delete_File(cleanup);
  }

  XFILE* xfile = CreateConcreteFile();
  ASSERT_NE(xfile, (XFILE*)NULL);

  ASSERT_TRUE(xfile->Create(xpath));
  xfile->Write((XBYTE*)"x", (XDWORD)1);
  xfile->Close();

  // Genuinely opened read-only ...
  ASSERT_TRUE(xfile->Open(xpath, true));
  // ... and IsReadOnly() now correctly reports true, on both platforms.
  EXPECT_TRUE(xfile->IsReadOnly());
  xfile->Close();

  xfile->Erase(xpath);
  GEN_XFACTORY.Delete_File(xfile);
}


TEST(UNITTEST_XFILE_CLASSNAME, GetFileSizeMacroNowSetsItsOwnOutputParameter)
{
  // FIXED: XFILE_GETFILESIZE (XFile.h) now assigns the result of xfile->GetSize() to `size` (the
  // macro's own parameter), instead of to a completely different, unrelated identifier literally
  // spelled `sizefile`. The `sizefile` variable declared below is kept only to prove the fix: it
  // stays untouched by the macro now, while the caller-visible `reportedsize` genuinely receives
  // the real file size.
  XPATH xpath; BuildTestFilePath(xpath, __L("xutils_unittests_xfile_macrobug.bin"));

  {
    XFILE* cleanup = GEN_XFACTORY.Create_File();
    if(cleanup->Exist(xpath)) cleanup->Erase(xpath);
    GEN_XFACTORY.Delete_File(cleanup);
  }

  {
    XFILE* writer = GEN_XFACTORY.Create_File();
    ASSERT_NE(writer, (XFILE*)NULL);
    ASSERT_TRUE(writer->Create(xpath));

    XBYTE fivebytes[5] = { 1,2,3,4,5 };
    writer->Write(fivebytes, sizeof(fivebytes));
    writer->Close();

    GEN_XFACTORY.Delete_File(writer);
  }

  XQWORD reportedsize = 12345;  // the macro's actual output parameter
  XQWORD sizefile     = 0;      // an unrelated, incidentally-same-named local -- must stay untouched now

  XFILE_GETFILESIZE(xpath, reportedsize);

  // The macro's own output parameter now genuinely reflects the real file size (5).
  EXPECT_EQ(reportedsize, (XQWORD)5);

  // The unrelated `sizefile` local is untouched by the macro now.
  EXPECT_EQ(sizefile, (XQWORD)0);

  XFILE* eraser = GEN_XFACTORY.Create_File();
  eraser->Erase(xpath);
  GEN_XFACTORY.Delete_File(eraser);
}


TEST(UNITTEST_XFILECONTAINER_CLASSNAME, CreateGetAndDeletePrimaryFileLifecycle)
{
  XFILECONTAINER container;

  EXPECT_EQ(container.GetPrimaryFile(), (XFILE*)NULL);

  EXPECT_TRUE(container.CreatePrimaryFile());

  XFILE* primary = container.GetPrimaryFile();
  ASSERT_NE(primary, (XFILE*)NULL);

  EXPECT_TRUE(container.DeletePrimaryFile());
  EXPECT_EQ(container.GetPrimaryFile(), (XFILE*)NULL);

  // A second delete with nothing left to delete must report failure, not crash.
  EXPECT_FALSE(container.DeletePrimaryFile());
}


}
#endif
