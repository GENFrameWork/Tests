/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XDir.cpp
*
* @class      UNITTESTS_XUTILS_XDIR
* @brief      XUtils unit tests for XDir class
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

#include "UnitTests_XUtils_XDir.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XDir.h"
#include "XPath.h"
#include "XPathsManager.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XDIR
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
* @fn         static XDIR* CreateConcreteDir()
* @brief      XDIR is an abstract class (Exist/Make/ChangeTo/Delete/GetActual/FirstSearch/
*             NextSearch taking XCHAR* are pure virtual) - it can only be exercised through the
*             platform-concrete subclass the application's own factory creates (XLINUXDIR on
*             this build), exactly like XPATHSMANAGER::CreateAllPathSectionOnDisk() and
*             XPATHSMANAGER::AdjustRootPathDefault() already do for real.
* @ingroup    UNIT TEST
*
* @return     XDIR* : Pointer to the requested object; NULL if it is not available.
*
* --------------------------------------------------------------------------------------------------------------------*/
static XDIR* CreateConcreteDir()
{
  return GEN_XFACTORY.Create_Dir();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void WriteSmallFile(XPATH& path, const char* content)
* @brief      Writes a tiny plain-text file using plain libc I/O (deliberately not XFILE, which
*             is outside this batch's scope) so XDIR's search/copy tests have real files to
*             enumerate/copy without depending on another untested module.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void WriteSmallFile(XPATH& path, const char* content)
{
  XBUFFER ascii;
  path.ConvertToASCII(ascii);

  FILE* file = fopen(ascii.GetPtrChar(), "wb");
  if(file)
    {
      fwrite(content, 1, strlen(content), file);
      fclose(file);
    }
}


TEST(UNITTESTS_XDIR_CLASSNAME, FactoryCreatesConcreteInstance)
{
  XDIR* xdir = CreateConcreteDir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  GEN_XFACTORY.Delete_Dir(xdir);
}


TEST(UNITTESTS_XDIR_CLASSNAME, ExistReturnsFalseForMissingDirectory)
{
  XDIR* xdir = CreateConcreteDir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  XPATH missing; BuildTestFilePath(missing, __L("unittests_xutils_xdir_definitely_does_not_exist"));

  EXPECT_FALSE(xdir->Exist(missing));
  EXPECT_FALSE(xdir->Exist(missing.Get()));

  GEN_XFACTORY.Delete_Dir(xdir);
}


TEST(UNITTESTS_XDIR_CLASSNAME, MakeNonRecursiveCreatesSingleLevelDirectoryAndExistReportsTrue)
{
  XDIR* xdir = CreateConcreteDir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  XPATH testdir; BuildTestFilePath(testdir, __L("unittests_xutils_xdir_singlelevel"));

  // Defensive cleanup from any previous interrupted run.
  if(xdir->Exist(testdir)) xdir->Delete(testdir, true);
  ASSERT_FALSE(xdir->Exist(testdir));

  EXPECT_TRUE(xdir->Make(testdir, false));
  EXPECT_TRUE(xdir->Exist(testdir));

  // Make() on an already-existing directory is documented to succeed (short-circuits on
  // Exist() before ever calling mkdir()).
  EXPECT_TRUE(xdir->Make(testdir, false));

  EXPECT_TRUE(xdir->Delete(testdir, false));
  EXPECT_FALSE(xdir->Exist(testdir));

  GEN_XFACTORY.Delete_Dir(xdir);
}


TEST(UNITTESTS_XDIR_CLASSNAME, MakeNonRecursiveFailsWhenParentDirectoryIsMissing)
{
  XDIR* xdir = CreateConcreteDir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  XPATH missingparent; BuildTestFilePath(missingparent, __L("unittests_xutils_xdir_missingparent"));
  XPATH nested; BuildTestFilePath(nested, __L("unittests_xutils_xdir_missingparent/child"));

  if(xdir->Exist(missingparent)) xdir->Delete(missingparent, true);
  ASSERT_FALSE(xdir->Exist(missingparent));

  // Non-recursive Make() is a single mkdir() call: with the parent absent, it must fail.
  EXPECT_FALSE(xdir->Make(nested, false));
  EXPECT_FALSE(xdir->Exist(nested));

  GEN_XFACTORY.Delete_Dir(xdir);
}


TEST(UNITTESTS_XDIR_CLASSNAME, MakeRecursiveCreatesIntermediateLevels)
{
  XDIR* xdir = CreateConcreteDir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  XPATH base; BuildTestFilePath(base, __L("unittests_xutils_xdir_recursive"));
  XPATH nested; BuildTestFilePath(nested, __L("unittests_xutils_xdir_recursive/sub1/sub2"));

  if(xdir->Exist(base)) xdir->Delete(base, true);
  ASSERT_FALSE(xdir->Exist(base));

  bool makeresult = xdir->Make(nested, true);

  // FIXED: XLINUXDIR::Make()'s recursive branch (XLINUXDir.cpp) now calls xpath.Slash_Add() to
  // append a trailing separator *before* walking XPATH::GetPathInSequence() segments, exactly
  // like XWINDOWSDIR::Make() already did - so the final path component ("sub2") is now handed to
  // mkdir() on Linux too, instead of being silently dropped by the segment walk (which only
  // reports a segment as "found" when it is followed by a separator). Both platforms now
  // consistently create every intermediate level, including the final one.
  EXPECT_TRUE(makeresult);
  EXPECT_TRUE(xdir->Exist(base));
  XPATH sub1; BuildTestFilePath(sub1, __L("unittests_xutils_xdir_recursive/sub1"));
  EXPECT_TRUE(xdir->Exist(sub1));
  EXPECT_TRUE(xdir->Exist(nested));

  EXPECT_TRUE(xdir->Delete(base, true));
  EXPECT_FALSE(xdir->Exist(base));

  GEN_XFACTORY.Delete_Dir(xdir);
}


TEST(UNITTESTS_XDIR_CLASSNAME, DeleteRecursiveRemovesNonEmptyDirectoryTree)
{
  XDIR* xdir = CreateConcreteDir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  XPATH base; BuildTestFilePath(base, __L("unittests_xutils_xdir_deletetree"));
  XPATH subdir; BuildTestFilePath(subdir, __L("unittests_xutils_xdir_deletetree/subdir"));
  XPATH filea; BuildTestFilePath(filea, __L("unittests_xutils_xdir_deletetree/a.txt"));
  XPATH fileb; BuildTestFilePath(fileb, __L("unittests_xutils_xdir_deletetree/subdir/b.txt"));

  if(xdir->Exist(base)) xdir->Delete(base, true);
  ASSERT_FALSE(xdir->Exist(base));

  ASSERT_TRUE(xdir->Make(base, false));
  ASSERT_TRUE(xdir->Make(subdir, false));

  WriteSmallFile(filea, "alpha content");
  WriteSmallFile(fileb, "beta content");

  ASSERT_TRUE(xdir->Exist(subdir));

  // A non-recursive delete of a non-empty directory must fail (rmdir() on a populated dir).
  EXPECT_FALSE(xdir->Delete(base, false));
  EXPECT_TRUE(xdir->Exist(base));

  // Recursive delete tears down files and subdirectories, then the directory itself.
  EXPECT_TRUE(xdir->Delete(base, true));
  EXPECT_FALSE(xdir->Exist(base));

  GEN_XFACTORY.Delete_Dir(xdir);
}


TEST(UNITTESTS_XDIR_CLASSNAME, FirstSearchAndNextSearchEnumerateDirectoryEntries)
{
  XDIR* xdir = CreateConcreteDir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  XPATH base; BuildTestFilePath(base, __L("unittests_xutils_xdir_search"));
  XPATH subdir; BuildTestFilePath(subdir, __L("unittests_xutils_xdir_search/childdir"));
  XPATH filea; BuildTestFilePath(filea, __L("unittests_xutils_xdir_search/one.dat"));

  if(xdir->Exist(base)) xdir->Delete(base, true);
  ASSERT_FALSE(xdir->Exist(base));

  ASSERT_TRUE(xdir->Make(base, false));
  ASSERT_TRUE(xdir->Make(subdir, false));
  WriteSmallFile(filea, "content");

  XDIRELEMENT   element;
  XSTRING       pattern(__L("*"));
  int           nfiles     = 0;
  int           ndirs      = 0;
  bool          foundfile  = false;
  bool          founddir   = false;

  bool found = xdir->FirstSearch(base, pattern, &element);
  while(found)
    {
      XSTRING name(element.GetNameFile()->Get());

      if(element.GetType() == XDIRELEMENTTYPE_FILE)
        {
          nfiles++;
          if(!name.Compare(__L("one.dat"))) foundfile = true;
        }
       else if(element.GetType() == XDIRELEMENTTYPE_DIR)
        {
          ndirs++;
          if(!name.Compare(__L("childdir"))) founddir = true;
        }

      found = xdir->NextSearch(&element);
    }

  EXPECT_EQ(nfiles, 1);
  EXPECT_EQ(ndirs, 1);
  EXPECT_TRUE(foundfile);
  EXPECT_TRUE(founddir);

  EXPECT_TRUE(xdir->Delete(base, true));
  EXPECT_FALSE(xdir->Exist(base));

  GEN_XFACTORY.Delete_Dir(xdir);
}


TEST(UNITTESTS_XDIR_CLASSNAME, FirstSearchOnMissingDirectoryReturnsFalse)
{
  XDIR* xdir = CreateConcreteDir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  XDIRELEMENT element;
  XPATH missing; BuildTestFilePath(missing, __L("unittests_xutils_xdir_search_missing"));

  EXPECT_FALSE(xdir->FirstSearch(missing.Get(), (XCHAR*)__L("*"), &element));

  GEN_XFACTORY.Delete_Dir(xdir);
}


TEST(UNITTESTS_XDIR_CLASSNAME, GetActualReturnsNonEmptyCurrentDirectory)
{
  XDIR* xdir = CreateConcreteDir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  XPATH current;
  EXPECT_TRUE(xdir->GetActual(current));
  EXPECT_FALSE(current.IsEmpty());

  GEN_XFACTORY.Delete_Dir(xdir);
}


TEST(UNITTESTS_XDIR_CLASSNAME, ChangeToSwitchesWorkingDirectoryAndIsRestored)
{
  XDIR* xdir = CreateConcreteDir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  XPATH original;
  ASSERT_TRUE(xdir->GetActual(original));

  XPATH target; GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, target);

  ASSERT_TRUE(xdir->ChangeTo(target));

  // ChangeTo()/GetActual() round-trips through the OS's own working-directory API, which
  // normalizes away any trailing path separator -- so the expected value here is the ROOT path
  // with its own trailing slash removed, not a hardcoded "/tmp" (portable across platforms).
  XPATH expected(target);
  expected.Slash_Delete();
  expected.Slash_Normalize();  // GEN_XPATHSMANAGER stores '/'-separated paths on every platform.

  // On Windows, GetActual() returns the native '\'-separated working directory (the OS's own
  // GetCurrentDirectory() convention), while "expected" is built from XPATHSMANAGER's own
  // always-forward-slash convention. Normalize before comparing so the two sides use the same
  // separator; this is purely a test-side comparison detail, not a change to XDIR's behavior.
  XPATH afterchange;
  ASSERT_TRUE(xdir->GetActual(afterchange));
  afterchange.Slash_Normalize();
  EXPECT_STREQ(afterchange.Get(), expected.Get());

  // Restore the working directory exactly, so later tests/relative paths in this same
  // process (e.g. the "assets" ROOT resolved by XPATHSMANAGER) are unaffected.
  ASSERT_TRUE(xdir->ChangeTo(original));

  XPATH restored;
  ASSERT_TRUE(xdir->GetActual(restored));
  EXPECT_STREQ(restored.Get(), original.Get());

  GEN_XFACTORY.Delete_Dir(xdir);
}


TEST(UNITTESTS_XDIR_CLASSNAME, CopyDuplicatesFileContentByteForByte)
{
  XDIR* xdir = CreateConcreteDir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  XPATH base; BuildTestFilePath(base, __L("unittests_xutils_xdir_copy"));

  if(xdir->Exist(base)) xdir->Delete(base, true);
  ASSERT_TRUE(xdir->Make(base, false));

  XPATH source; BuildTestFilePath(source, __L("unittests_xutils_xdir_copy/source.txt"));
  XPATH target; BuildTestFilePath(target, __L("unittests_xutils_xdir_copy/target.txt"));

  WriteSmallFile(source, "hello xdir copy");

  EXPECT_TRUE(xdir->Copy(source, target));

  XBUFFER targetascii;
  target.ConvertToASCII(targetascii);

  FILE* readback = fopen(targetascii.GetPtrChar(), "rb");
  ASSERT_NE(readback, (FILE*)NULL);

  char buffer[64];
  memset(buffer, 0, sizeof(buffer));
  size_t nread = fread(buffer, 1, sizeof(buffer)-1, readback);
  fclose(readback);

  EXPECT_GT(nread, (size_t)0);
  EXPECT_STREQ(buffer, "hello xdir copy");

  EXPECT_TRUE(xdir->Delete(base, true));

  GEN_XFACTORY.Delete_Dir(xdir);
}


}
#endif
