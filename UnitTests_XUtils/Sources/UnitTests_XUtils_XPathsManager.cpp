/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XPathsManager.cpp
*
* @class      UNITTESTS_XUTILS_XPATHSMANAGER
* @brief      XUtils unit tests for XPathsManager class
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

#include "UnitTests_XUtils_XPathsManager.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XPathsManager.h"
#include "XPath.h"
#include "XDir.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XPATHSMANAGER
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void EnsureXPathsManagerInstance()
* @brief      Ensures that the XPathsManager singleton instance exists.
* @note       Unlike XRAND/XSLEEP/XSYSTEM, XPATHSMANAGER has no public constructor and no
*             SetInstance() (private ctor/copy-ctor, GetInstance() lazily GEN_NEW's the single
*             instance) - so the only way to "ensure" it is to call GetInstance() itself. The
*             application's own AppProc_Ini() already does this for real (AdjustRootPathDefault
*             + CreateAllPathSectionOnDisk), so by the time any TEST() body runs, the instance -
*             and its ROOT section - already exist.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
static void EnsureXPathsManagerInstance()
{
  XPATHSMANAGER::GetInstance();
}


TEST(UNITTESTS_XPATHSMANAGER_CLASSNAME, InstancedAfterApplicationInit)
{
  EnsureXPathsManagerInstance();

  EXPECT_TRUE(XPATHSMANAGER::GetIsInstanced());
}


TEST(UNITTESTS_XPATHSMANAGER_CLASSNAME, RootSectionAlreadyConfiguredByAppInit)
{
  EnsureXPathsManagerInstance();

  XPATHSMANAGERSECTION* rootsection = GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT);

  ASSERT_NE(rootsection, (XPATHSMANAGERSECTION*)NULL);
  EXPECT_EQ(rootsection->type, XPATHSMANAGERSECTIONTYPE_ROOT);
  ASSERT_NE(rootsection->xpath, (XPATH*)NULL);
  EXPECT_FALSE(rootsection->xpath->IsEmpty());
  EXPECT_TRUE(rootsection->xpath->Slash_HaveAtLast());
}


TEST(UNITTESTS_XPATHSMANAGER_CLASSNAME, GetPathSectionReturnsNullForNeverAddedSection)
{
  EnsureXPathsManagerInstance();

  // GENERIC6 is never added by this test file nor by the application's own AppProc_Ini(),
  // so it must report as absent from GetPathSection() (a direct, unprefixed lookup).
  EXPECT_EQ(GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_GENERIC6), (XPATHSMANAGERSECTION*)NULL);

  // FIXED: GetPathOfSection() (XPathsManager.cpp) now tracks a separate `found` flag for the
  // requested-section search, instead of using the output `xpath`'s emptiness as the success
  // indicator. Previously, with addroot=true (the default), the ROOT section's path was written
  // into `xpath` unconditionally *before* searching for the requested section, so an unregistered
  // section still left `xpath` non-empty (just the ROOT path) and the old `xpath.IsEmpty()?
  // false:true` check reported true -- conflating "ROOT exists" with "this section exists". Now
  // the return value correctly reflects only whether the requested section itself was found,
  // regardless of the addroot prefix still being written into `xpath` as a side effect.
  XPATH withrootprefix;
  EXPECT_FALSE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GENERIC6, withrootprefix, true));

  XPATH rootonly;
  ASSERT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, rootonly));
  // The ROOT prefix is still written into `xpath` even though the section itself wasn't found.
  EXPECT_STREQ(withrootprefix.Get(), rootonly.Get());

  XPATH missing;
  EXPECT_FALSE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GENERIC6, missing, false));
}


TEST(UNITTESTS_XPATHSMANAGER_CLASSNAME, AddPathSectionRegistersNewSectionNormalizedWithTrailingSlash)
{
  EnsureXPathsManagerInstance();

  XSTRING rawvalue(__L("some/generic/value"));

  EXPECT_TRUE(GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GENERIC1, rawvalue));

  XPATHSMANAGERSECTION* section = GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_GENERIC1);

  ASSERT_NE(section, (XPATHSMANAGERSECTION*)NULL);
  EXPECT_STREQ(section->xpath->Get(), __L("some/generic/value/"));
}


TEST(UNITTESTS_XPATHSMANAGER_CLASSNAME, AddPathSectionOnExistingTypeUpdatesInPlace)
{
  EnsureXPathsManagerInstance();

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GENERIC2, __L("first/value"));

  XPATHSMANAGERSECTION* firstadd = GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_GENERIC2);
  ASSERT_NE(firstadd, (XPATHSMANAGERSECTION*)NULL);
  EXPECT_STREQ(firstadd->xpath->Get(), __L("first/value/"));

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GENERIC2, __L("second/value"));

  XPATHSMANAGERSECTION* secondadd = GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_GENERIC2);
  ASSERT_NE(secondadd, (XPATHSMANAGERSECTION*)NULL);
  EXPECT_STREQ(secondadd->xpath->Get(), __L("second/value/"));

  // Updating in place: still the same section object, not a duplicate entry.
  EXPECT_EQ(firstadd, secondadd);
}


TEST(UNITTESTS_XPATHSMANAGER_CLASSNAME, GetPathOfSectionWithAddRootPrependsRootPath)
{
  EnsureXPathsManagerInstance();

  XPATH rootonly;
  ASSERT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, rootonly));

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GENERIC3, __L("nested/section"));

  XPATH withroot;
  EXPECT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GENERIC3, withroot, true));

  XSTRING expectedwithroot;
  expectedwithroot  = rootonly.Get();
  expectedwithroot += __L("nested/section/");

  EXPECT_STREQ(withroot.Get(), expectedwithroot.Get());

  XPATH withoutroot;
  EXPECT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GENERIC3, withoutroot, false));
  EXPECT_STREQ(withoutroot.Get(), __L("nested/section/"));
}


TEST(UNITTESTS_XPATHSMANAGER_CLASSNAME, GetPathOfSectionForRootItselfNeverDoublesRootPrefix)
{
  EnsureXPathsManagerInstance();

  XPATH direct;
  ASSERT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, direct, false));

  XPATH withaddrootflag;
  ASSERT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, withaddrootflag, true));

  // addroot only ever prepends the ROOT section's own path when querying a *different*
  // section (see source: "if(addroot && (sectiontype!=ROOT))") - requesting ROOT itself is
  // unaffected by the flag.
  EXPECT_STREQ(direct.Get(), withaddrootflag.Get());
}


TEST(UNITTESTS_XPATHSMANAGER_CLASSNAME, CreateAllPathSectionOnDiskCreatesRegisteredDirectory)
{
  EnsureXPathsManagerInstance();

  const XCHAR* relativedirname = __L("unittests_xpathsmanager_createdisk");

  GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_GENERIC4, relativedirname);

  XPATH fulldirpath;
  ASSERT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_GENERIC4, fulldirpath, true));

  XDIR* xdir = GEN_XFACTORY.Create_Dir();
  ASSERT_NE(xdir, (XDIR*)NULL);

  // Defensive cleanup in case a previous interrupted run left this directory behind.
  if(xdir->Exist(fulldirpath))
    {
      xdir->Delete(fulldirpath, true);
    }
  ASSERT_FALSE(xdir->Exist(fulldirpath));

  // NOTE: CreateAllPathSectionOnDisk() creates a directory for *every currently registered
  // section*, not just the one added above - so this call also materializes real directories
  // on disk for whatever GENERIC1/GENERIC2/GENERIC3 sections earlier tests in this file
  // registered (their values are plain relative strings like "some/generic/value", never
  // intended to be real directories). We clean up all of those here too, so the on-disk state
  // stays pristine/idempotent across repeated full-suite runs.
  EXPECT_TRUE(GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk());
  EXPECT_TRUE(xdir->Exist(fulldirpath));

  // Calling it again with the directory already present is a documented no-op success path.
  EXPECT_TRUE(GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk());

  // Clean up so re-running the full suite finds a pristine starting state (idempotency).
  EXPECT_TRUE(xdir->Delete(fulldirpath, true));
  EXPECT_FALSE(xdir->Exist(fulldirpath));

  XPATH rootonly;
  ASSERT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, rootonly));

  const XPATHSMANAGERSECTIONTYPE sidesectiontypes[] = { XPATHSMANAGERSECTIONTYPE_GENERIC1,
                                                         XPATHSMANAGERSECTIONTYPE_GENERIC2,
                                                         XPATHSMANAGERSECTIONTYPE_GENERIC3 };
  for(int c=0; c<3; c++)
    {
      // IMPORTANT (root cause of a real order/repeat-dependent flake, fixed here): under
      // --gtest_shuffle (and across --gtest_repeat iterations, since the XPATHSMANAGER
      // singleton's registered sections persist across the whole process) this test can run
      // *before* one or more of AddPathSectionRegistersNewSectionNormalizedWithTrailingSlash /
      // AddPathSectionOnExistingTypeUpdatesInPlace / GetPathOfSectionWithAddRootPrependsRootPath
      // have (re-)registered GENERIC1/GENERIC2/GENERIC3 in that same iteration - so any of these
      // sidesectiontypes may genuinely be UNREGISTERED at this point. GetPathSection() is the
      // correct, direct "is it registered" check; GetPathOfSection(...,addroot=true) is NOT -
      // per the documented quirk exercised in GetPathSectionReturnsNullForNeverAddedSection
      // above, it unconditionally writes the ROOT path into its output *before* searching for
      // the requested section, so it returns true (and a non-empty path equal to rootonly)
      // even when the section was never added. Trusting that return value here used to compute
      // remainder="" (sidepath==rootonly), which made topleveldir collapse to rootonly ITSELF -
      // i.e. the real ROOT/assets directory - and delete it wholesale (wiping
      // assets/unittests_xutils.lng along with it), corrupting the on-disk state for every test
      // that runs afterward. Checking GetPathSection() first makes this cleanup depend only on
      // this file's own bookkeeping of "did I actually register this section", not on
      // GetPathOfSection's addroot=true fallback semantics - safe under any run order/repeat.
      if(GEN_XPATHSMANAGER.GetPathSection(sidesectiontypes[c]) == (XPATHSMANAGERSECTION*)NULL) continue;

      XPATH sidepath;
      if(GEN_XPATHSMANAGER.GetPathOfSection(sidesectiontypes[c], sidepath, true))
        {
          // sidepath == rootonly + "<toplevelname>/...rest". Delete only the top-level
          // directory directly under ROOT (not just the deepest leaf), so no empty
          // intermediate directories are left behind either.
          XSTRING remainder;
          sidepath.Copy((int)rootonly.GetSize(), (int)sidepath.GetSize(), remainder);

          int slashindex = remainder.FindCharacter(__C('/'));

          // Extra safety net: even with the registration check above, never let topleveldir
          // collapse to rootonly itself (an empty remainder can only mean "not really a
          // side section under root" - deleting ROOT/assets is never a correct outcome here).
          if(remainder.IsEmpty()) continue;

          XPATH topleveldir(rootonly);
          if(slashindex != XSTRING_NOTFOUND)
            {
              XSTRING topname;
              remainder.Copy(0, slashindex, topname);
              topleveldir += topname;
            }
           else
            {
              topleveldir += remainder;
            }

          if(xdir->Exist(topleveldir)) xdir->Delete(topleveldir, true);
        }
    }

  GEN_XFACTORY.Delete_Dir(xdir);
}


TEST(UNITTESTS_XPATHSMANAGER_CLASSNAME, AdjustRootPathDefaultReaffirmsRootWhenAssetsDirAlreadyPresent)
{
  EnsureXPathsManagerInstance();

  XPATH beforeroot;
  ASSERT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, beforeroot));

  // This is exactly the call UnitTests_XUtils.cpp's own AppProc_Ini() makes at real startup
  // (APPLICATION_DIRECTORYMAIN == "assets"). Since that "assets" directory already exists on
  // disk (found by walking up from the current ROOT), calling it again is expected to
  // re-resolve to the same ROOT path rather than disturb it.
  EXPECT_TRUE(GEN_XPATHSMANAGER.AdjustRootPathDefault((XCHAR*)__L("assets")));

  XPATH afterroot;
  ASSERT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, afterroot));

  EXPECT_STREQ(beforeroot.Get(), afterroot.Get());
}


TEST(UNITTESTS_XPATHSMANAGER_CLASSNAME, DeleteAllPathSectionsClearsEverySectionThenRestoresRoot)
{
  EnsureXPathsManagerInstance();

  // This test intentionally drives the one destructive whole-manager operation
  // (DeleteAllPathSections wipes every section, ROOT included, since XPATHSMANAGER has no
  // per-section removal API) and then restores real application state afterward so later
  // code in this same test binary keeps working.
  //
  // IMPORTANT: restoring via AdjustRootPathDefault() here (instead of directly re-adding the
  // captured ROOT value) would be genuinely destructive to the machine running the test, not
  // just to in-process state - confirmed empirically. With ROOT emptied, AdjustRootPathDefault
  // walks the (now-empty, then Slash_Add()-ed-to-"/") xpathroot looking for a slash: its very
  // first candidate is built via Copy(0,0,...), which XSTRING::Copy() treats as a no-op
  // (startindex>=endindex) that leaves the destination untouched - i.e. still empty - so the
  // first directory it probes is unconditionally "/assets" (filesystem root + assetsdirname),
  // never a path under the real application directory. When that probe's Exist() is false, the
  // function's fallback then calls Make("/assets", false) - which, running as root in this
  // container, actually CREATES a real "/assets" directory at the machine's filesystem root
  // and adopts it as ROOT. We avoid that landmine entirely by restoring the exact captured
  // XPATH value directly through AddPathSection() instead.
  XPATH originalroot;
  ASSERT_TRUE(GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, originalroot, false));
  ASSERT_TRUE(GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT) != (XPATHSMANAGERSECTION*)NULL);

  EXPECT_TRUE(GEN_XPATHSMANAGER.DeleteAllPathSections());

  EXPECT_EQ(GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT), (XPATHSMANAGERSECTION*)NULL);

  // A second call with nothing left to delete is a documented failure return.
  EXPECT_FALSE(GEN_XPATHSMANAGER.DeleteAllPathSections());

  // Restore: re-register the exact ROOT value captured before deletion (see the safety note
  // above for why this - not AdjustRootPathDefault() - is the correct way to restore it here).
  EXPECT_TRUE(GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_ROOT, originalroot.Get()));

  XPATHSMANAGERSECTION* restoredsection = GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT);
  ASSERT_NE(restoredsection, (XPATHSMANAGERSECTION*)NULL);
  EXPECT_STREQ(restoredsection->xpath->Get(), originalroot.Get());
}


}
#endif
