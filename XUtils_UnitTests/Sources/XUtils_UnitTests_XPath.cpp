/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XPath.cpp
*
* @class      XUTILS_UNITTESTS_XPATH
* @brief      XUtils unit tests for XPath class
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

#include "XUtils_UnitTests_XPath.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XPath.h"
#include "XPathsManager.h"
#include "XVector.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XPATH
{


TEST(UNITTEST_XPATH_CLASSNAME, ConstructorsBuildExpectedContent)
{
  XPATH xpathchar("hello/world");
  EXPECT_STREQ(xpathchar.Get(), __L("hello/world"));

  XPATH xpathwide(__L("wide/path"));
  EXPECT_STREQ(xpathwide.Get(), __L("wide/path"));

  XPATH xpathcopy(xpathwide);
  EXPECT_STREQ(xpathcopy.Get(), __L("wide/path"));

  XSTRING sourcestring(__L("from/string"));
  XPATH   xpathfromstring(sourcestring);
  EXPECT_STREQ(xpathfromstring.Get(), __L("from/string"));

  XPATH xpathempty;
  EXPECT_TRUE(xpathempty.IsEmpty());
}


TEST(UNITTEST_XPATH_CLASSNAME, AssignmentOperatorsOverwriteContent)
{
  XPATH xpath;

  xpath = "assigned/char";
  EXPECT_STREQ(xpath.Get(), __L("assigned/char"));

  xpath = __L("assigned/wide");
  EXPECT_STREQ(xpath.Get(), __L("assigned/wide"));

  XPATH other(__L("other/value"));
  xpath = other;
  EXPECT_STREQ(xpath.Get(), __L("other/value"));

  XSTRING stringvalue(__L("string/value"));
  xpath = stringvalue;
  EXPECT_STREQ(xpath.Get(), __L("string/value"));
}


TEST(UNITTEST_XPATH_CLASSNAME, PlusEqualsOperatorsAppendContent)
{
  XPATH xpath(__L("base"));

  xpath += "/char";
  EXPECT_STREQ(xpath.Get(), __L("base/char"));

  xpath += __L("/wide");
  EXPECT_STREQ(xpath.Get(), __L("base/char/wide"));

  XPATH appended(__L("/more"));
  xpath += appended;
  EXPECT_STREQ(xpath.Get(), __L("base/char/wide/more"));

  XSTRING stringappend(__L("/tail"));
  xpath += stringappend;
  EXPECT_STREQ(xpath.Get(), __L("base/char/wide/more/tail"));

  xpath += __C('!');
  EXPECT_STREQ(xpath.Get(), __L("base/char/wide/more/tail!"));
}


TEST(UNITTEST_XPATH_CLASSNAME, ComparisonOperatorsAgainstXPath)
{
  XPATH lower(__L("aaa"));
  XPATH higher(__L("bbb"));
  XPATH same(__L("aaa"));

  EXPECT_TRUE(lower  < higher);
  EXPECT_TRUE(higher > lower);
  EXPECT_TRUE(lower  <= same);
  EXPECT_TRUE(lower  >= same);
  EXPECT_TRUE(lower  == same);
  EXPECT_TRUE(lower  != higher);
  EXPECT_FALSE(lower == higher);
}


TEST(UNITTEST_XPATH_CLASSNAME, ComparisonOperatorsAgainstXString)
{
  XPATH   xpath(__L("aaa"));
  XSTRING higher(__L("bbb"));
  XSTRING same(__L("aaa"));

  EXPECT_TRUE(xpath <  higher);
  EXPECT_TRUE(xpath <= same);
  EXPECT_TRUE(xpath >= same);
  EXPECT_TRUE(xpath == same);
  EXPECT_TRUE(xpath != higher);
  EXPECT_FALSE(xpath > higher);
}


TEST(UNITTEST_XPATH_CLASSNAME, IndexOperatorClampsOutOfRangePositions)
{
  XPATH xpath(__L("abc"));

  EXPECT_EQ(xpath[0], __C('a'));
  EXPECT_EQ(xpath[1], __C('b'));
  EXPECT_EQ(xpath[2], __C('c'));

  // Negative position clamps to the first character (per source, not a documented contract).
  EXPECT_EQ(xpath[-1], __C('a'));

  // Out-of-range clamps to the last character.
  EXPECT_EQ(xpath[100], __C('c'));

  XPATH xpathempty;
  EXPECT_EQ(xpathempty[0], (XCHAR)0);
}


TEST(UNITTEST_XPATH_CLASSNAME, SplitExtractsDriveXpathNameAndExt)
{
  XPATH   xpath(__L("C:\\folder\\sub\\file.txt"));
  XSTRING drive;
  XPATH   xpathpart;
  XSTRING name;
  XSTRING ext;

  EXPECT_TRUE(xpath.Split(&drive, &xpathpart, &name, &ext));

  EXPECT_STREQ(drive.Get(),     __L("C:"));
  EXPECT_STREQ(xpathpart.Get(), __L("\\folder\\sub\\"));
  EXPECT_STREQ(name.Get(),      __L("file"));
  EXPECT_STREQ(ext.Get(),       __L(".txt"));
}


TEST(UNITTEST_XPATH_CLASSNAME, SplitOnEmptyPathReturnsFalse)
{
  XPATH xpath;

  EXPECT_FALSE(xpath.Split(NULL, NULL, NULL, NULL));
}


TEST(UNITTEST_XPATH_CLASSNAME, GetDriveGetPathAndGetDriveAndPath)
{
  XPATH   xpath(__L("C:\\folder\\sub\\file.txt"));
  XSTRING drive;
  XSTRING path;
  XSTRING drivepath;

  EXPECT_TRUE(xpath.GetDrive(drive));
  EXPECT_STREQ(drive.Get(), __L("C:"));

  EXPECT_TRUE(xpath.GetPath(path));
  EXPECT_STREQ(path.Get(), __L("\\folder\\sub\\"));

  EXPECT_TRUE(xpath.GetDriveAndPath(drivepath));
  EXPECT_STREQ(drivepath.Get(), __L("C:\\folder\\sub\\"));
}


TEST(UNITTEST_XPATH_CLASSNAME, GetNamefileVariantsAndExt)
{
  XPATH   xpath(__L("C:\\folder\\sub\\file.txt"));
  XSTRING pathnamefile;
  XSTRING pathnamefileext;
  XSTRING namefile;
  XSTRING namefileext;
  XSTRING ext;

  EXPECT_TRUE(xpath.GetPathAndNamefile(pathnamefile));
  EXPECT_STREQ(pathnamefile.Get(), __L("\\folder\\sub\\file"));

  EXPECT_TRUE(xpath.GetPathAndNamefileExt(pathnamefileext));
  EXPECT_STREQ(pathnamefileext.Get(), __L("\\folder\\sub\\file.txt"));

  EXPECT_TRUE(xpath.GetNamefile(namefile));
  EXPECT_STREQ(namefile.Get(), __L("file"));

  EXPECT_TRUE(xpath.GetNamefileExt(namefileext));
  EXPECT_STREQ(namefileext.Get(), __L("file.txt"));

  EXPECT_TRUE(xpath.GetExt(ext));
  EXPECT_STREQ(ext.Get(), __L(".txt"));
}


TEST(UNITTEST_XPATH_CLASSNAME, GetPathInSequenceReturnsEachSlashDelimitedSegment)
{
  XPATH   xpath(__L("/tmp/alpha/beta"));
  XSTRING part;

  EXPECT_TRUE(xpath.GetPathInSequence(0, part));
  EXPECT_STREQ(part.Get(), __L(""));

  EXPECT_TRUE(xpath.GetPathInSequence(1, part));
  EXPECT_STREQ(part.Get(), __L("tmp"));

  EXPECT_TRUE(xpath.GetPathInSequence(2, part));
  EXPECT_STREQ(part.Get(), __L("alpha"));

  // NOTE (source behavior, not a bug we fix): the final segment ("beta") is only ever
  // yielded when it is followed by a slash. Since this path has no trailing slash, requesting
  // the index past the last slash falls through the loop, empties pathpart and returns false -
  // "beta" itself is never reported as a found segment. Callers relying on this (e.g.
  // XLINUXDIR::Make's recursive directory creation) must account for this off-by-one.
  EXPECT_FALSE(xpath.GetPathInSequence(3, part));
  EXPECT_TRUE(part.IsEmpty());
}


TEST(UNITTEST_XPATH_CLASSNAME, SetOnlyVariantsMutateInPlace)
{
  // BUG (XPath.cpp, every SetOnlyXXX() method, e.g. SetOnlyDrive() around line 840-851):
  // each of these methods builds its result in a *local* XSTRING, calls Set(string) to update
  // `this` (which deep-copies - so the XPATH object itself ends up correct), and then does
  // `return string.Get();` - returning a pointer into that local's buffer. The local is
  // destroyed (freeing its buffer) during stack unwind before the caller ever reads through
  // that pointer, so the returned `const XCHAR*` is a dangling/use-after-free pointer, not a
  // usable string - confirmed empirically (it prints as garbage bytes here). We do NOT read
  // the return value for that reason; we only assert the well-defined side effect, which is
  // that `this` (the XPATH object) itself ends up holding the correct value.
  XPATH xpath(__L("C:\\folder\\sub\\file.txt"));
  XPATH original(xpath);

  xpath = original; xpath.SetOnlyDrive();             EXPECT_STREQ(xpath.Get(), __L("C:"));
  xpath = original; xpath.SetOnlyPath();               EXPECT_STREQ(xpath.Get(), __L("\\folder\\sub\\"));
  xpath = original; xpath.SetOnlyDriveAndPath();       EXPECT_STREQ(xpath.Get(), __L("C:\\folder\\sub\\"));
  xpath = original; xpath.SetOnlyPathAndNamefile();    EXPECT_STREQ(xpath.Get(), __L("\\folder\\sub\\file"));
  xpath = original; xpath.SetOnlyPathAndNamefileExt(); EXPECT_STREQ(xpath.Get(), __L("\\folder\\sub\\file.txt"));
  xpath = original; xpath.SetOnlyNamefile();           EXPECT_STREQ(xpath.Get(), __L("file"));
  xpath = original; xpath.SetOnlyNamefileExt();        EXPECT_STREQ(xpath.Get(), __L("file.txt"));
  xpath = original; xpath.SetOnlyExt();                EXPECT_STREQ(xpath.Get(), __L(".txt"));
}


TEST(UNITTEST_XPATH_CLASSNAME, DeleteDriveRemovesLeadingDriveLetter)
{
  XPATH xpath(__L("C:\\folder\\file.txt"));

  EXPECT_TRUE(xpath.DeleteDrive());
  EXPECT_STREQ(xpath.Get(), __L("\\folder\\file.txt"));

  // No drive present: GetSize() <= 2 short path rejected.
  XPATH shortpath(__L("ab"));
  EXPECT_FALSE(shortpath.DeleteDrive());

  // No ':' at position 1.
  XPATH nodrive(__L("folder/file.txt"));
  EXPECT_FALSE(nodrive.DeleteDrive());
}


TEST(UNITTEST_XPATH_CLASSNAME, DeleteExtStripsExtensionKeepingPathAndName)
{
  XPATH xpath(__L("C:\\folder\\file.txt"));

  EXPECT_TRUE(xpath.DeleteExt());
  EXPECT_STREQ(xpath.Get(), __L("\\folder\\file"));
}


TEST(UNITTEST_XPATH_CLASSNAME, SlashHaveAtLast)
{
  XPATH withslash(__L("folder/"));
  XPATH withoutslash(__L("folder"));

  EXPECT_TRUE(withslash.Slash_HaveAtLast());
  EXPECT_FALSE(withoutslash.Slash_HaveAtLast());
}


TEST(UNITTEST_XPATH_CLASSNAME, SlashAddAppendsSlashMatchingMajorityStyle)
{
  XPATH forwardstyle(__L("folder/sub"));
  EXPECT_TRUE(forwardstyle.Slash_Add());
  EXPECT_STREQ(forwardstyle.Get(), __L("folder/sub/"));

  // Calling again on an already-terminated path is a documented no-op (returns false).
  EXPECT_FALSE(forwardstyle.Slash_Add());
  EXPECT_STREQ(forwardstyle.Get(), __L("folder/sub/"));

  XPATH backslashstyle(__L("folder\\sub"));
  EXPECT_TRUE(backslashstyle.Slash_Add());
  // Slash_Add() normalizes after adding, so the trailing separator becomes '/' even though the
  // majority-style vote chose '\' (Slash_Normalize() runs unconditionally after the Add()).
  EXPECT_STREQ(backslashstyle.Get(), __L("folder/sub/"));
}


TEST(UNITTEST_XPATH_CLASSNAME, SlashNormalizeConvertsBackslashesToForwardByDefault)
{
  XPATH mixed(__L("folder\\sub\\file"));

  EXPECT_TRUE(mixed.Slash_Normalize());
  EXPECT_STREQ(mixed.Get(), __L("folder/sub/file"));

  EXPECT_TRUE(mixed.Slash_Normalize(true));
  EXPECT_STREQ(mixed.Get(), __L("folder\\sub\\file"));
}


TEST(UNITTEST_XPATH_CLASSNAME, SlashDeleteRemovesTrailingSeparator)
{
  XPATH withslash(__L("folder/sub/"));

  EXPECT_TRUE(withslash.Slash_Delete());
  EXPECT_STREQ(withslash.Get(), __L("folder/sub"));
  EXPECT_FALSE(withslash.Slash_HaveAtLast());

  // No trailing separator: documented no-op (returns false).
  EXPECT_FALSE(withslash.Slash_Delete());
}


TEST(UNITTEST_XPATH_CLASSNAME, AddToNameFilePrefixAndSuffix)
{
  XPATH prefixed(__L("folder/sub/file.txt"));
  EXPECT_TRUE(prefixed.AddToNameFile(true, (XCHAR*)__L("pre_")));
  EXPECT_STREQ(prefixed.Get(), __L("folder/sub/pre_file.txt"));

  XPATH suffixed(__L("folder/sub/file.txt"));
  EXPECT_TRUE(suffixed.AddToNameFile(false, (XCHAR*)__L("_v2")));
  EXPECT_STREQ(suffixed.Get(), __L("folder/sub/file_v2.txt"));
}


TEST(UNITTEST_XPATH_CLASSNAME, CreateJoinsSegmentsWithNormalizedSlash)
{
  XPATH xpath;

  EXPECT_TRUE(xpath.Create(3, __L("folder"), __L("sub"), __L("file.txt")));
  EXPECT_STREQ(xpath.Get(), __L("folder/sub/file.txt"));

  // A segment starting with '.' (e.g. a bare extension continuation) does not get a separator
  // forced in front of it.
  XPATH xpathwithdot;
  EXPECT_TRUE(xpathwithdot.Create(2, __L("file"), __L(".txt")));
  EXPECT_STREQ(xpathwithdot.Get(), __L("file.txt"));

  // Empty elements among the varargs are skipped entirely.
  XPATH xpathskipsempty;
  EXPECT_TRUE(xpathskipsempty.Create(3, __L("folder"), __L(""), __L("file.txt")));
  EXPECT_STREQ(xpathskipsempty.Get(), __L("folder/file.txt"));
}


TEST(UNITTEST_XPATH_CLASSNAME, CreateWithSectionPrependsRootSection)
{
  // Relies on the ROOT path section already being configured by the application's own
  // AppProc_Ini() (AdjustRootPathDefault), exactly as XUtils_UnitTests.cpp does for real.
  ASSERT_TRUE(XPATHSMANAGER::GetIsInstanced());

  XPATH xpathroot;
  ASSERT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathroot));

  XPATH xpath;
  EXPECT_TRUE(xpath.Create(XPATHSMANAGERSECTIONTYPE_ROOT, 2, __L("subdir"), __L("file.dat")));

  XSTRING expected;
  expected  = xpathroot.Get();
  expected += __L("subdir/file.dat");

  EXPECT_STREQ(xpath.Get(), expected.Get());
}


TEST(UNITTEST_XPATH_CLASSNAME, SplitWithSubpathsVectorPopulatesEachComponent)
{
  XPATH             xpath(__L("/alpha/beta/gamma.txt"));
  XVECTOR<XSTRING*> subpaths;
  XSTRING           name;
  XSTRING           ext;

  EXPECT_TRUE(xpath.Split(NULL, subpaths, &name, &ext));

  // NOTE (source behavior): the intermediate xpath ("/alpha/beta/") ends in a separator, and
  // the tokenizer loop treats the position exactly at GetSize() as a delimiter too (it reads
  // one past the last real character, which XSTRING::operator[] clamps back to that last
  // character - the separator itself - so the trailing-separator branch fires twice), so a
  // trailing empty XSTRING* is appended in addition to the two real segments.
  ASSERT_EQ(subpaths.GetSize(), (XDWORD)3);
  EXPECT_STREQ(subpaths.Get(0)->Get(), __L("alpha"));
  EXPECT_STREQ(subpaths.Get(1)->Get(), __L("beta"));
  EXPECT_STREQ(subpaths.Get(2)->Get(), __L(""));

  // BUG (XPath.cpp, XPATH::Split(XSTRING*, XVECTOR<XSTRING*>&, XSTRING*, XSTRING*), around
  // line 1417-1470): this overload extracts the name/ext into *local* `_name`/`_ext` variables
  // (via the 4-pointer Split() it calls internally) but never copies them into the caller's
  // `name`/`ext` out-parameters - the `name`/`ext` pointers passed in are only ever consulted
  // for a null-check (deciding whether to fold the name into the path), never written to. So
  // both out-parameters are always left exactly as the caller passed them in (empty here),
  // confirmed empirically - not the "gamma"/".txt" a caller would reasonably expect.
  EXPECT_STREQ(name.Get(), __L(""));
  EXPECT_STREQ(ext.Get(),  __L(""));

  // The vector owns heap-allocated XSTRING* elements (GEN_NEW'd inside Split) - the caller is
  // responsible for freeing them; clean up here to avoid leaking in the test itself.
  subpaths.DeleteContents();
  subpaths.DeleteAll();
}


}
#endif
