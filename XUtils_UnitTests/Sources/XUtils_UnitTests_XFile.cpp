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
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFILE
{


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

  XPATH missing(__L("/tmp/xutils_unittests_xfile_definitely_does_not_exist.bin"));

  EXPECT_FALSE(xfile->Exist(missing));
  EXPECT_FALSE(xfile->Exist(missing.Get()));

  GEN_XFACTORY.Delete_File(xfile);
}


TEST(UNITTEST_XFILE_CLASSNAME, CreateWriteCloseThenOpenReadRoundTrip)
{
  XPATH xpath(__L("/tmp/xutils_unittests_xfile_roundtrip.bin"));

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
    // (IsReadOnly() happens to read false here too, but only because it is ALWAYS false --
    // see IsReadOnlyNeverReflectsTheOpenModeItWasGivenBug below.)

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

    // NOT `EXPECT_TRUE` -- see IsReadOnlyNeverReflectsTheOpenModeItWasGivenBug below: this is a
    // real, confirmed XUtils bug, not the documented behavior.
    EXPECT_FALSE(reader->IsReadOnly());

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
  XPATH xpath(__L("/tmp/xutils_unittests_xfile_writebuffer.bin"));

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
  XPATH xpath(__L("/tmp/xutils_unittests_xfile_seek.bin"));

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
  XPATH original(__L("/tmp/xutils_unittests_xfile_renameorig.bin"));
  XPATH renamed(__L("/tmp/xutils_unittests_xfile_renamednew.bin"));

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
  XPATH xpath(__L("/tmp/xutils_unittests_xfile_pathname.bin"));

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


TEST(UNITTEST_XFILE_CLASSNAME, IsReadOnlyNeverReflectsTheOpenModeItWasGivenBug)
{
  // Real, concrete XUtils bug (not fixed, per the hard rule): XLINUXFILE::Open(XCHAR* xpath, bool
  // isreadonly) (XLINUXFile.cpp) receives its `isreadonly` argument as a plain local parameter
  // and only ever reads it to pick an fopen() mode string ("rb" vs "r+b") -- it never assigns
  // that value to `this->isreadonly` (the protected XFILE member IsReadOnly() actually returns).
  // That member is set to `false` exactly once, in XFILE::Clean() (XFile.cpp), and never touched
  // again anywhere in XFile.cpp/XLINUXFile.cpp/XLINUXFile.h -- confirmed by grep. As a result,
  // IsReadOnly() unconditionally reports false for every XLINUXFILE, regardless of whether the
  // file was actually opened read-only (Open(path, true)) or read-write (Open(path, false)).
  XPATH xpath(__L("/tmp/xutils_unittests_xfile_isreadonlybug.bin"));

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
  // ... yet IsReadOnly() reports false -- the bug.
  EXPECT_FALSE(xfile->IsReadOnly());
  xfile->Close();

  xfile->Erase(xpath);
  GEN_XFACTORY.Delete_File(xfile);
}


TEST(UNITTEST_XFILE_CLASSNAME, GetFileSizeMacroNeverSetsItsOwnOutputParameter)
{
  // Confirms the analysis report's flagged bug concretely: XFILE_GETFILESIZE (XFile.h lines 56-67)
  // is declared as a macro whose own parameter is named `size` -- callers naturally expect that
  // parameter to receive the real file size -- but line 62 of the macro body assigns the result of
  // xfile->GetSize() to a completely different, UNDECLARED identifier literally spelled `sizefile`
  // instead of to `size` (the macro's own parameter). Because C macro expansion is pure textual
  // substitution (not scoped, and not "closest spelling" matching), the parameter `size` only ever
  // gets its initial sentinel `-1` assignment (the macro's very first statement); `sizefile` is
  // never touched by that first line and is only not a hard compile error here because we have
  // deliberately declared a variable with that exact name in scope, purely to demonstrate the bug
  // without hiding it: the macro is invoked completely unmodified.
  XPATH xpath(__L("/tmp/xutils_unittests_xfile_macrobug.bin"));

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

  XQWORD reportedsize = 12345;  // the macro's actual output parameter -- expected (buggy) to stay untouched
  XQWORD sizefile     = 0;      // only in scope because the macro's body erroneously targets this literal name

  XFILE_GETFILESIZE(xpath, reportedsize);

  // The macro's own output parameter is left at its internal sentinel value (-1), NOT the real
  // file size (5) -- this is the bug: the caller-visible `reportedsize` never reflects the file.
  EXPECT_EQ(reportedsize, (XQWORD)-1);

  // Meanwhile the real size silently landed in the unrelated same-scope `sizefile` variable instead.
  EXPECT_EQ(sizefile, (XQWORD)5);

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
