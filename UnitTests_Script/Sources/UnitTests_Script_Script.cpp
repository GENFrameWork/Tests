/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_Script.cpp
* @brief      Unit tests for SCRIPT
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_Script.h"
#include "UnitTests_Script_TestHelpers.h"
#include "Script_Language_G.h"
#include "XDir.h"
#include "XFactory.h"
#include "XFileTXT.h"
#include "GEN_Control.h"

#if defined(WINDOWS) || defined(_WINDOWS)
#include <windows.h>
#endif

#ifdef GOOGLETEST_ACTIVE
namespace TEST_SCRIPT
{

static bool UnitTests_Script_ConfigureScriptsRoot()
{
  XPATH scriptspath;
  #if !defined(WINDOWS) && !defined(_WINDOWS)
  XDIR* dir = NULL;
  #endif
  bool  status = false;

  if(!GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, scriptspath)) return false;

  #if defined(WINDOWS) || defined(_WINDOWS)
  if(!CreateDirectory(scriptspath.Get(), NULL))
    {
      DWORD error = GetLastError();
      if(error != ERROR_ALREADY_EXISTS) return false;
    }

  DWORD attributes = GetFileAttributes(scriptspath.Get());
  status = ((attributes != INVALID_FILE_ATTRIBUTES) && ((attributes & FILE_ATTRIBUTE_DIRECTORY) == FILE_ATTRIBUTE_DIRECTORY));
  #else
  dir = GEN_XFACTORY.Create_Dir();
  if(!dir) return false;

  status = dir->Exist(scriptspath);
  if(!status) status = dir->Make(scriptspath, true);

  if(status) status = GEN_XPATHSMANAGER.AddPathSection(XPATHSMANAGERSECTIONTYPE_SCRIPTS, scriptspath);

  GEN_XFACTORY.Delete_Dir(dir);
  #endif

  return status;
}


static bool UnitTests_Script_WriteTextFile(XPATH& path, XCHAR* text)
{
  XFILETXT filetxt;
  XSTRING  line;

  if(!text) return false;
  if(!filetxt.Create(path)) return false;

  line = text;
  filetxt.AddLine(line);

  bool status = filetxt.WriteAllFile();
  filetxt.Close();

  return status;
}


TEST(UNITTESTS_SCRIPT_CLASSNAME, DetectsEnabledExtensions)
{
  EXPECT_EQ(SCRIPT::GetTypeByExtension(__L("sample.g")), SCRIPT_TYPE_G);
  EXPECT_EQ(SCRIPT::GetTypeByExtension(__L("sample.G")), SCRIPT_TYPE_G);
  EXPECT_EQ(SCRIPT::GetTypeByExtension(__L("sample.unknown")), SCRIPT_TYPE_UNKNOWN);
  EXPECT_EQ(SCRIPT::GetTypeByExtension(NULL), SCRIPT_TYPE_UNKNOWN);
}


TEST(UNITTESTS_SCRIPT_CLASSNAME, CapabilitiesCanBeRestrictedAndRestored)
{
  SCRIPT script;

  EXPECT_EQ(script.GetCapabilities(), (XDWORD)SCRIPT_CAPABILITY_NONE);
  EXPECT_FALSE(script.IsCapabilityEnabled(SCRIPT_CAPABILITY_PROCESS));
  EXPECT_TRUE(script.SetCapabilities(SCRIPT_CAPABILITY_NONE));
  EXPECT_FALSE(script.IsCapabilityEnabled(SCRIPT_CAPABILITY_PROCESS));
  EXPECT_TRUE(script.EnableCapabilities(SCRIPT_CAPABILITY_PROCESS));
  EXPECT_TRUE(script.IsCapabilityEnabled(SCRIPT_CAPABILITY_PROCESS));
  EXPECT_TRUE(script.DisableCapabilities(SCRIPT_CAPABILITY_PROCESS));
  EXPECT_FALSE(script.SetCapabilities(0x80000000));
}


TEST(UNITTESTS_SCRIPT_CLASSNAME, RejectsUnconfinedScriptNames)
{
  XPATH path;

  EXPECT_FALSE(SCRIPT::ResolvePathInScriptsRoot(__L("../outside.g"), path));
  EXPECT_FALSE(SCRIPT::ResolvePathInScriptsRoot(__L("C:/outside.g"), path));
  EXPECT_FALSE(SCRIPT::ResolvePathInScriptsRoot(__L("folder//test.g"), path));
  EXPECT_TRUE(SCRIPT::ResolvePathInScriptsRoot(__L("folder/test.g"), path));
}


TEST(UNITTESTS_SCRIPT_CLASSNAME, SaveAndLoadRoundTrip)
{
  XPATH path;
  SCRIPT writer;
  SCRIPT reader;

  ASSERT_TRUE(UnitTests_Script_ConfigureScriptsRoot());
  ASSERT_TRUE(SCRIPT::ResolvePathInScriptsRoot(__L("UnitTests_Script_SaveRoundTrip.g"), path));

  (*writer.GetScript()) = __L("return 42");
  ASSERT_TRUE(writer.Save(path));

  ASSERT_TRUE(reader.Load(path));
  EXPECT_NE(reader.GetScript()->Find(__L("return 42"), false), XSTRING_NOTFOUND);
  EXPECT_EQ(reader.GetNameScript()->Compare(__L("UnitTests_Script_SaveRoundTrip.g")), 0);
}


TEST(UNITTESTS_SCRIPT_CLASSNAME, LoadInvalidatesCacheWhenFileContentChanges)
{
  XPATH path;
  SCRIPT firstload;
  SCRIPT secondload;

  ASSERT_TRUE(UnitTests_Script_ConfigureScriptsRoot());
  ASSERT_TRUE(SCRIPT::ResolvePathInScriptsRoot(__L("UnitTests_Script_CacheInvalidation.g"), path));

  ASSERT_TRUE(UnitTests_Script_WriteTextFile(path, __L("return 1")));
  ASSERT_TRUE(firstload.Load(path));
  EXPECT_NE(firstload.GetScript()->Find(__L("return 1"), false), XSTRING_NOTFOUND);

  ASSERT_TRUE(UnitTests_Script_WriteTextFile(path, __L("return 2")));
  ASSERT_TRUE(secondload.Load(path));
  EXPECT_NE(secondload.GetScript()->Find(__L("return 2"), false), XSTRING_NOTFOUND);
  EXPECT_EQ(secondload.GetScript()->Find(__L("return 1"), false), XSTRING_NOTFOUND);
  EXPECT_EQ(secondload.GetNameScript()->Compare(__L("UnitTests_Script_CacheInvalidation.g")), 0);
}


TEST(UNITTESTS_SCRIPT_CLASSNAME, TrimsConfiguredNames)
{
  XSTRING name(__L("  test.g\t"));

  EXPECT_TRUE(SCRIPT::EliminateExtraChars(&name));
  EXPECT_EQ(name.Compare(__L("test.g")), 0);
  EXPECT_FALSE(SCRIPT::EliminateExtraChars(NULL));
}

}
#endif
