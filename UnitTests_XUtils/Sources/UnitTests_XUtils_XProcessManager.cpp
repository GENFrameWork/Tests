/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XProcessManager.cpp
*
* @class      UNITTESTS_XUTILS_XPROCESSMANAGER
* @brief      XUtils unit tests for XProcessManager and XProcess classes
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

#include "UnitTests_XUtils_XProcessManager.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XProcessManager.h"
#include "XConsole.h"
#include "XBuffer.h"
#include "XTimer.h"

// FIXED (architecture): this file used to include "XLINUXProcessManager.h" and construct
// XLINUXPROCESSMANAGER directly, which forced the whole suite behind "#ifdef LINUX" (no other
// platform's concrete XPROCESSMANAGER subclass was ever compiled into this project's test binary).
// Tests must only exercise XPROCESSMANAGER's common/portable interface, through whichever concrete
// instance the application's own bootstrap (Factorys_Ini() in MainProcLINUX.cpp / MainProcWINDOWS.cpp)
// already installed for the current platform -- never a GEN platform module (XLINUXPROCESSMANAGER,
// XWINDOWSPROCESSMANAGER, ...) named directly in test code. That is what lets this file build, link
// and run its tests on every platform instead of only on LINUX.
//
// A small number of tests genuinely verify OS-native mechanisms that have no portable equivalent
// (delivering a real SIGTERM to a real child process via fork()/waitpid(); reading this process'
// own name from /proc/self/status) -- only those individual tests (not the whole file) stay guarded
// by "#ifdef LINUX", and only the C runtime/POSIX headers they need are included conditionally here.
#ifdef LINUX
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#define UNITTESTS_XPROCESSMANAGER_GETPID() ((XDWORD)getpid())

#define UNITTESTS_XPROCESSMANAGER_SHELLCMD_ALWAYSSUCCEEDS    __L("true")
#define UNITTESTS_XPROCESSMANAGER_SHELLCMD_ALWAYSFAILS       __L("false")
#define UNITTESTS_XPROCESSMANAGER_SHELLCMD_ECHO              __L("echo hello")

#define UNITTESTS_XPROCESSMANAGER_APP_PATH_ALWAYSSUCCEEDS    __L("/bin/true")
#define UNITTESTS_XPROCESSMANAGER_APP_PARAMS_ALWAYSSUCCEEDS  (XCHAR*)NULL
#define UNITTESTS_XPROCESSMANAGER_APP_PATH_ALWAYSFAILS       __L("/bin/false")
#define UNITTESTS_XPROCESSMANAGER_APP_PARAMS_ALWAYSFAILS     (XCHAR*)NULL
#define UNITTESTS_XPROCESSMANAGER_APP_PATH_ECHO              __L("/bin/echo")
#define UNITTESTS_XPROCESSMANAGER_APP_PARAMS_ECHO            __L("hello_world")
#define UNITTESTS_XPROCESSMANAGER_APP_PATH_MISSING           __L("/this/path/does/not/exist")

#elif defined(WINDOWS)
#include <process.h>

#define UNITTESTS_XPROCESSMANAGER_GETPID() ((XDWORD)_getpid())

// NOTE: verified against XWINDOWSPROCESSMANAGER's implementation (MakeSystemCommand/MakeCommand run
// the string through cmd.exe via _wsystem()/_wpopen(); Application_Execute() launches
// "applicationpath" directly via CreateProcess() with "params" appended, so it needs a real .exe
// path, not a shell built-in) but not build-verified on an actual Windows machine -- please confirm
// once you build/run this on Windows.
#define UNITTESTS_XPROCESSMANAGER_SHELLCMD_ALWAYSSUCCEEDS    __L("exit 0")
#define UNITTESTS_XPROCESSMANAGER_SHELLCMD_ALWAYSFAILS       __L("exit 1")
#define UNITTESTS_XPROCESSMANAGER_SHELLCMD_ECHO              __L("echo hello")

#define UNITTESTS_XPROCESSMANAGER_APP_PATH_ALWAYSSUCCEEDS    __L("C:\\Windows\\System32\\cmd.exe")
#define UNITTESTS_XPROCESSMANAGER_APP_PARAMS_ALWAYSSUCCEEDS  __L("/c exit 0")
#define UNITTESTS_XPROCESSMANAGER_APP_PATH_ALWAYSFAILS       __L("C:\\Windows\\System32\\cmd.exe")
#define UNITTESTS_XPROCESSMANAGER_APP_PARAMS_ALWAYSFAILS     __L("/c exit 1")
#define UNITTESTS_XPROCESSMANAGER_APP_PATH_ECHO              __L("C:\\Windows\\System32\\cmd.exe")
#define UNITTESTS_XPROCESSMANAGER_APP_PARAMS_ECHO            __L("/c echo hello_world")
#define UNITTESTS_XPROCESSMANAGER_APP_PATH_MISSING           __L("C:\\this\\path\\does\\not\\exist.exe")
#endif


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XPROCESSMANAGER
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void EnsureXProcessManagerInstance()
* @brief      Asserts the XPROCESSMANAGER singleton is already installed.
* @note       FIXED (architecture): this used to construct XLINUXPROCESSMANAGER directly as a
*             fallback. XPROCESSMANAGER_ACTIVE is defined for this build (see
*             UnitTests_XUtils/CMake/CMakeLists.txt), so the application's own portable bootstrap
*             (Factorys_Ini() in MainProcLINUX.cpp / MainProcWINDOWS.cpp) already installs the real,
*             concrete, platform-specific XPROCESSMANAGER before any test runs -- exactly like it does
*             for XFACTORY/XSYSTEM/XRAND/XSLEEP. Tests must never construct a platform module
*             (XLINUXPROCESSMANAGER, XWINDOWSPROCESSMANAGER, ...) themselves: they only exercise the
*             common XPROCESSMANAGER interface through whichever concrete instance the application
*             already installed. This helper is now just a defensive check for that precondition.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void EnsureXProcessManagerInstance()
{
  ASSERT_TRUE(XPROCESSMANAGER::GetIsInstanced()) << "XPROCESSMANAGER must already be installed by "
                                                      "this application's own bootstrap before any "
                                                      "test runs (XPROCESSMANAGER_ACTIVE is defined "
                                                      "for this build) -- tests must not construct a "
                                                      "platform-specific XPROCESSMANAGER subclass "
                                                      "directly.";
}


/*---- XPROCESS: plain data record ---------------------------------------------------------------------------------*/


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ProcessDefaultState)
{
  XPROCESS process;

  EXPECT_EQ(process.GetID(), (XDWORD)0xFFFFFFFF);
  EXPECT_EQ(process.GetWindowHandle(), (void*)NULL);
  EXPECT_EQ(process.GetWindowTitleHeight(), 0);
  EXPECT_EQ(process.GetWindowBorderWidth(), 0);
  EXPECT_NE(process.GetPath(), (XPATH*)NULL);
  EXPECT_NE(process.GetName(), (XSTRING*)NULL);
  EXPECT_NE(process.GetWindowTitle(), (XSTRING*)NULL);
  EXPECT_NE(process.GetWindowRect(), (GRPRECTINT*)NULL);
  EXPECT_NE(process.GetProcessIDs(), (XVECTOR<XDWORD>*)NULL);
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ProcessGetSetID)
{
  XPROCESS process;

  process.SetID(1234);
  EXPECT_EQ(process.GetID(), (XDWORD)1234);
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ProcessGetSetWindowHandle)
{
  XPROCESS process;
  void*    fakehandle = (void*)0x1234;

  process.SetWindowHandle(fakehandle);
  EXPECT_EQ(process.GetWindowHandle(), fakehandle);
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ProcessGetSetWindowTitleHeightAndBorderWidth)
{
  XPROCESS process;

  process.SetWindowTitleHeight(20);
  process.SetWindowBorderWidth(4);

  EXPECT_EQ(process.GetWindowTitleHeight(), 20);
  EXPECT_EQ(process.GetWindowBorderWidth(), 4);
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ProcessCopyToCopiesAllFields)
{
  XPROCESS src, dst;

  src.SetID(77);
  src.GetPath()->Set(__L("/tmp/app"));
  src.GetName()->Set(__L("app"));
  src.GetWindowTitle()->Set(__L("My Window"));
  src.GetWindowRect()->Set(1, 2, 3, 4);
  src.SetWindowTitleHeight(15);
  src.SetWindowBorderWidth(2);

  EXPECT_TRUE(src.CopyTo(dst));

  EXPECT_EQ(dst.GetID(), (XDWORD)77);
  EXPECT_STREQ(dst.GetPath()->Get(), __L("/tmp/app"));
  EXPECT_STREQ(dst.GetName()->Get(), __L("app"));
  EXPECT_STREQ(dst.GetWindowTitle()->Get(), __L("My Window"));
  // GRPRECTBASE::IsEqual() is a tri-state comparator (ISLESS/ISEQUAL/ISGREATER, from XBase.h) that
  // compares rectangle *area*, not a plain bool -- ISEQUAL is 0, so it must be compared against
  // ISEQUAL rather than used directly as a condition.
  EXPECT_EQ(dst.GetWindowRect()->IsEqual(src.GetWindowRect()), ISEQUAL);
  EXPECT_EQ(dst.GetWindowTitleHeight(), 15);
  EXPECT_EQ(dst.GetWindowBorderWidth(), 2);
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ProcessCopyFromMirrorsCopyTo)
{
  XPROCESS src, dst;

  src.SetID(99);
  src.GetName()->Set(__L("other"));

  EXPECT_TRUE(dst.CopyFrom(src));

  EXPECT_EQ(dst.GetID(), (XDWORD)99);
  EXPECT_STREQ(dst.GetName()->Get(), __L("other"));
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ProcessCompareTrueForIdenticalCopiesOnlyFixed)
{
  XPROCESS src, dst;

  src.SetID(1);
  src.GetPath()->Set(__L("/bin/x"));
  src.GetName()->Set(__L("x"));
  src.GetWindowTitle()->Set(__L("X"));

  src.CopyTo(dst);

  EXPECT_TRUE(dst.Compare(src, true));
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ProcessCompareNotOnlyFixedRectEqualityCheckIsCorrect)
{
  // FIXED (XProcessManager.cpp): XPROCESS::Compare(..., onlyfixed=false) now does
  // "if(GetWindowRect()->IsEqual(...) != ISEQUAL) return false;", correctly using
  // GRPRECTBASE::IsEqual()'s tri-state result (ISLESS=-1/ISEQUAL=0/ISGREATER=1) instead of treating
  // it as a bool. Two otherwise-identical XPROCESS objects with the same rect now correctly compare
  // as equal.
  XPROCESS src, dst;

  src.SetID(1);
  src.GetWindowRect()->Set(0, 0, 10, 10);
  src.CopyTo(dst);

  EXPECT_TRUE(dst.Compare(src, false));
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ProcessCompareNotOnlyFixedDetectsGenuineRectAreaDifference)
{
  // FIXED: the flip side of the same corrected comparison -- when the rect areas genuinely DO
  // differ, IsEqual() returns non-zero (ISGREATER/ISLESS), so "!= ISEQUAL" now correctly triggers
  // and Compare() reports the difference via the rect field.
  XPROCESS src, dst;

  src.SetID(1);
  src.GetWindowRect()->Set(0, 0, 10, 10);  // area 100
  src.CopyTo(dst);
  dst.GetWindowRect()->Set(0, 0, 20, 20);  // area 400 -- genuinely different from src's

  EXPECT_FALSE(dst.Compare(src, false));
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ProcessCompareFalseWhenIDDiffers)
{
  XPROCESS src, dst;

  src.SetID(1);
  src.CopyTo(dst);
  dst.SetID(2);

  EXPECT_FALSE(dst.Compare(src, true));
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ProcessCompareOnlyFixedIgnoresRectAndHeights)
{
  XPROCESS src, dst;

  src.SetID(1);
  src.GetName()->Set(__L("same"));
  src.CopyTo(dst);

  // Diverge only the "not fixed" fields (rect/heights) -- onlyfixed=true must not notice.
  // Note: dst's rect (9,9,9,9) has zero area, same as src's default (0,0,0,0), so it does not
  // exercise the IsEqual() inversion bug documented above -- the "false" result below is driven
  // purely by the (correctly implemented) windowtitleheight mismatch.
  dst.GetWindowRect()->Set(9, 9, 9, 9);
  dst.SetWindowTitleHeight(999);

  EXPECT_TRUE(dst.Compare(src, true));
  EXPECT_FALSE(dst.Compare(src, false));
}


/*---- XPROCESSMANAGER: singleton lifecycle ---------------------------------------------------------------------------*/


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, SetInstanceNull)
{
  EXPECT_FALSE(XPROCESSMANAGER::SetInstance(NULL));
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, InstanceLifecycle)
{
  // FIXED (architecture): the temporary test instance used to be a platform module
  // (XLINUXPROCESSMANAGER). XPROCESSMANAGER itself has no pure virtual methods (its header even
  // notes "ITS NOT A SINGLETON [by construction]"), so it is directly instantiable and enough to
  // exercise Set/Get/Del/IsInstanced mechanics through the common interface alone -- no platform
  // module needed here at all.
  XPROCESSMANAGER* originalinstance = NULL;
  if(XPROCESSMANAGER::GetIsInstanced()) originalinstance = &XPROCESSMANAGER::GetInstance();

  XPROCESSMANAGER* testinstance = GEN_NEW XPROCESSMANAGER();
  EXPECT_NE(testinstance, (XPROCESSMANAGER*)NULL);

  EXPECT_TRUE(XPROCESSMANAGER::SetInstance(testinstance));
  EXPECT_TRUE(XPROCESSMANAGER::GetIsInstanced());
  EXPECT_EQ(&XPROCESSMANAGER::GetInstance(), testinstance);

  if(originalinstance)
    {
      EXPECT_TRUE(XPROCESSMANAGER::SetInstance(originalinstance));
      GEN_DELETE testinstance;
    }
   else
    {
      EXPECT_TRUE(XPROCESSMANAGER::DelInstance());
      EnsureXProcessManagerInstance();
    }
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, DelInstanceTwice)
{
  // Same reasoning as InstanceLifecycle above: a plain XPROCESSMANAGER is enough here, no platform
  // module needed.
  XPROCESSMANAGER* originalinstance = NULL;
  if(XPROCESSMANAGER::GetIsInstanced()) originalinstance = &XPROCESSMANAGER::GetInstance();

  XPROCESSMANAGER* testinstance = GEN_NEW XPROCESSMANAGER();
  EXPECT_NE(testinstance, (XPROCESSMANAGER*)NULL);

  EXPECT_TRUE(XPROCESSMANAGER::SetInstance(testinstance));

  EXPECT_TRUE(XPROCESSMANAGER::DelInstance());
  EXPECT_FALSE(XPROCESSMANAGER::DelInstance());

  if(originalinstance)
    {
      EXPECT_TRUE(XPROCESSMANAGER::SetInstance(originalinstance));
    }
   else
    {
      EnsureXProcessManagerInstance();
    }
}


/*---- XPROCESSMANAGER: real (bounded, self-exiting) OS process spawning, through the common interface -----------------*/


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, MakeSystemCommandRunsRealShellCommand)
{
  EnsureXProcessManagerInstance();

  EXPECT_TRUE(GEN_XPROCESSMANAGER.MakeSystemCommand(UNITTESTS_XPROCESSMANAGER_SHELLCMD_ALWAYSSUCCEEDS));
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, MakeSystemCommandDoesNotReportNonZeroExitAsFailure)
{
  // MakeSystemCommand() only ever reports failure when the underlying system()/_wsystem() call
  // itself returns -1 (the shell could not be launched at all) -- it never inspects the child
  // command's own exit status. So a command that legitimately exits non-zero still comes back as
  // true. Captured here as real behavior, not fixed -- true on every platform's implementation.
  EnsureXProcessManagerInstance();

  EXPECT_TRUE(GEN_XPROCESSMANAGER.MakeSystemCommand(UNITTESTS_XPROCESSMANAGER_SHELLCMD_ALWAYSFAILS));
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, MakeCommandCapturesRealOutputThroughAPopenPipe)
{
  // FIXED on LINUX (historical, XLINUXProcessManager.cpp): MakeCommand() used to call
  // popen(cmd, "rt") -- "rt" is an MSVCRT/Windows-style text-mode flag, not a valid POSIX popen()
  // type string, so glibc rejected it with EINVAL and MakeCommand() always returned false. It now
  // correctly calls popen(cmd, "r"). (XWINDOWSPROCESSMANAGER's own _wpopen(cmd, "rt") never had this
  // problem -- "rt" is a valid MSVCRT mode there.) MakeCommand is a real, working API on both
  // platforms, exercised here through the common interface.
  EnsureXProcessManagerInstance();

  XBUFFER out;
  int     returncode = -1;

  EXPECT_TRUE(GEN_XPROCESSMANAGER.MakeCommand(UNITTESTS_XPROCESSMANAGER_SHELLCMD_ECHO, &out, &returncode));
  EXPECT_FALSE(out.IsEmpty());
  EXPECT_EQ(returncode, 0);

  out.Add((XBYTE)0);

  XSTRING outstring;
  outstring = out.GetPtrChar();
  EXPECT_NE(outstring.Find(__L("hello"), false), XSTRING_NOTFOUND);
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ApplicationExecuteRunsRealShortLivedProcessSuccessfully)
{
  EnsureXProcessManagerInstance();

  int returncode = -1;

  EXPECT_TRUE(GEN_XPROCESSMANAGER.Application_Execute(UNITTESTS_XPROCESSMANAGER_APP_PATH_ALWAYSSUCCEEDS, UNITTESTS_XPROCESSMANAGER_APP_PARAMS_ALWAYSSUCCEEDS, (XBUFFER*)NULL, (XBUFFER*)NULL, &returncode));
  EXPECT_EQ(returncode, 0);
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ApplicationExecuteReportsNonZeroExitAsFailure)
{
  EnsureXProcessManagerInstance();

  int returncode = -1;

  EXPECT_FALSE(GEN_XPROCESSMANAGER.Application_Execute(UNITTESTS_XPROCESSMANAGER_APP_PATH_ALWAYSFAILS, UNITTESTS_XPROCESSMANAGER_APP_PARAMS_ALWAYSFAILS, (XBUFFER*)NULL, (XBUFFER*)NULL, &returncode));
  EXPECT_EQ(returncode, 1);
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ApplicationExecuteCapturesStdoutWithParams)
{
  EnsureXProcessManagerInstance();

  XBUFFER out;
  int     returncode = -1;

  EXPECT_TRUE(GEN_XPROCESSMANAGER.Application_Execute(UNITTESTS_XPROCESSMANAGER_APP_PATH_ECHO, UNITTESTS_XPROCESSMANAGER_APP_PARAMS_ECHO, (XBUFFER*)NULL, &out, &returncode));
  EXPECT_EQ(returncode, 0);

  out.Add((XBYTE)0);

  XSTRING outstring;
  outstring = out.GetPtrChar();
  EXPECT_NE(outstring.Find(__L("hello_world"), false), XSTRING_NOTFOUND);
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ApplicationExecuteRejectsMissingApplicationPath)
{
  EnsureXProcessManagerInstance();

  EXPECT_FALSE(GEN_XPROCESSMANAGER.Application_Execute(UNITTESTS_XPROCESSMANAGER_APP_PATH_MISSING, NULL, (XBUFFER*)NULL, (XBUFFER*)NULL, (int*)NULL));
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ApplicationGetRunningListDispatchesThroughTheCommonInterface)
{
  // FIXED (dispatch bug, previously platform-specific): XLINUXPROCESSMANAGER::Application_GetRunningList()
  // (XLINUXProcessManager.h) used to take a different signature than the virtual base method
  // XPROCESSMANAGER::Application_GetRunningList(XVECTOR<XPROCESS*>&, bool onlywithvalidwindow=false)
  // (XProcessManager.h), which *hid* the base method instead of overriding it -- so calling it through
  // a base-typed reference/pointer (exactly what GEN_XPROCESSMANAGER / XPROCESSMANAGER::GetInstance()
  // gives you) silently resolved to the base class' own do-nothing stub. Both signatures now match, so
  // the vtable dispatch correctly reaches the real per-platform implementation, exercised here purely
  // through the common interface (no platform module named in this test).
  //
  // STILL OPEN on LINUX (real bug, reported, not fixed): XLINUXPROCESSMANAGER::Application_GetRunningList()
  // itself (XLINUXProcessManager.cpp) unconditionally "return false;" at the very end of the function,
  // even after successfully scanning /proc and populating applist -- so on LINUX the return value can
  // never be trusted to reflect success, only the output list can. XWINDOWSPROCESSMANAGER's own
  // implementation does not have this bug and genuinely returns true on success.
  EnsureXProcessManagerInstance();

  XVECTOR<XPROCESS*> applist;

  #if defined(LINUX)
  EXPECT_FALSE(GEN_XPROCESSMANAGER.Application_GetRunningList(applist)); // documented LINUX bug: always false, even on success
  #else
  EXPECT_TRUE(GEN_XPROCESSMANAGER.Application_GetRunningList(applist));
  #endif

  EXPECT_FALSE(applist.IsEmpty()); // the list IS populated on every platform

  XPROCESS* self = XPROCESSMANAGER::Application_GetProcessByID(UNITTESTS_XPROCESSMANAGER_GETPID(), applist);
  EXPECT_NE(self, (XPROCESS*)NULL);

  applist.DeleteContents();
  applist.DeleteAll();
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ApplicationGetProcessByIDReturnsNullWhenNotFound)
{
  XVECTOR<XPROCESS*> applist;

  XPROCESS* fake = GEN_NEW XPROCESS();
  fake->SetID(123);
  applist.Add(fake);

  EXPECT_EQ(XPROCESSMANAGER::Application_GetProcessByID(456, applist), (XPROCESS*)NULL);
  EXPECT_EQ(XPROCESSMANAGER::Application_GetProcessByID(123, applist), fake);

  applist.DeleteContents();
  applist.DeleteAll();
}


#ifdef LINUX
TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ApplicationIsRunningFindsThisTestProcessByItsOwnName)
{
  // This test genuinely needs an OS-native, independent way to learn "this process' own name" (so it
  // never has to hardcode the test binary's name), which on LINUX means reading /proc/self/status --
  // the same source XLINUXPROCESSMANAGER::Application_IsRunning() itself uses for every candidate PID.
  // There is no equally simple portable equivalent (Windows would need GetCurrentProcessId() +
  // GetModuleBaseName()/QueryFullProcessImageName() from psapi.h), so this one test -- not the whole
  // file -- stays LINUX-only; Application_IsRunning() itself is still exercised through the common
  // interface (GEN_XPROCESSMANAGER).
  EnsureXProcessManagerInstance();

  FILE* fp = fopen("/proc/self/status", "r");
  ASSERT_NE(fp, (FILE*)NULL);

  char line[512] = { 0 };
  ASSERT_NE(fgets(line, sizeof(line), fp), (char*)NULL);
  fclose(fp);

  char* first = strtok(line, " \t\n");
  ASSERT_NE(first, (char*)NULL);
  first = strtok(NULL, " \t\n"); // skip the "Name:" label itself, keep the value

  XSTRING selfname;
  selfname = first; // strtok's result is already NUL-terminated

  XDWORD foundID = 0;
  EXPECT_TRUE(GEN_XPROCESSMANAGER.Application_IsRunning(selfname.Get(), &foundID));
  EXPECT_EQ(foundID, UNITTESTS_XPROCESSMANAGER_GETPID());
}
#endif // LINUX


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, AdjustStringToConsolaSymbolsUsedSkipsConversionWhenNotARealConsole)
{
  // XSTRING::ConsoleCodePageToConvertASCII() (XString.cpp) deliberately maps
  // XCONSOLE_SYMBOLSUSED_NOTCONSOLE to XSTRINGASCIICODE_NONE -- i.e. "we are not attached to a real
  // console, so there is no known target code page to convert to". AdjustStringToConsolaSymbolsUsed()
  // then has nothing to do and leaves target_buffer empty, so it correctly returns false in that case.
  //
  // FIXED (test, portable): guessing whether this binary happens to be attached to a real console
  // per platform (isatty() on LINUX, GetConsoleCP() on WINDOWS) depends entirely on how/where the
  // test binary is launched, and a wrong guess for one platform (assuming WINDOWS never has a real
  // console, which broke this test under an interactive/console CI run) is exactly what happened
  // here. Instead of guessing, the test asks a real XCONSOLE the same question the production code
  // itself asks (GetSymbolsUsed()) and runs it through the exact same decision
  // AdjustStringToConsolaSymbolsUsed() uses (the UTF-8 special case, then
  // XSTRING::ConsoleCodePageToConvertASCII()) to predict the outcome -- correct on every platform and
  // immune to how/where the binary happens to be launched.
  EnsureXProcessManagerInstance();

  XCONSOLE* consoleforprediction = GEN_XFACTORY.CreateConsole();
  ASSERT_NE(consoleforprediction, (XCONSOLE*)NULL);

  XCONSOLE_SYMBOLSUSED symbolused = consoleforprediction->GetSymbolsUsed();
  GEN_XFACTORY.DeleteConsole(consoleforprediction);

  XSTRING          probe;
  XSTRINGASCIICODE asciicode = probe.ConsoleCodePageToConvertASCII(symbolused);

  bool expectconversion = (symbolused == XCONSOLE_SYMBOLSUSED_UNICODE_UTF8) || (asciicode != XSTRINGASCIICODE_NONE);

  XSTRING original;
  original = __L("hello");

  XBUFFER converted;
  bool    status = GEN_XPROCESSMANAGER.AdjustStringToConsolaSymbolsUsed(original, converted);

  if(!expectconversion)
    {
      EXPECT_FALSE(status);
      EXPECT_TRUE(converted.IsEmpty());
    }
   else
    {
      // A real target charset was detected, so the conversion legitimately runs and produces
      // non-empty output.
      EXPECT_TRUE(status);
      EXPECT_FALSE(converted.IsEmpty());
    }
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, AdjustConsolaSymbolsUsedToStringDoesNotSkipUnlikeItsCounterpart)
{
  // Asymmetry (XProcessManager.cpp ~819): AdjustStringToConsolaSymbolsUsed() guards its ASCII
  // conversion with "if(stringasccicode != XSTRINGASCIICODE_NONE)", so it correctly skips (and
  // returns false) when there's no known target code page (see the sibling test above). Its
  // reverse-direction counterpart AdjustConsolaSymbolsUsedToString() has the exact same guard
  // present in the source but commented out ("//if(stringasccicode != XSTRINGASCIICODE_NONE)"),
  // so it always calls ConvertFromASCII(..., XSTRINGASCIICODE_NONE) regardless -- which in practice
  // still produces a non-empty string. The two methods are not actually symmetric despite the
  // matching names/intent. Captured as real (if inconsistent) behavior, not fixed.
  EnsureXProcessManagerInstance();

  XBUFFER origin;
  origin.Add((XBYTE*)"hello", 5);

  XSTRING converted;
  EXPECT_TRUE(GEN_XPROCESSMANAGER.AdjustConsolaSymbolsUsedToString(origin, converted));
  EXPECT_FALSE(converted.IsEmpty());
}


TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, AdjustStringToConsolaSymbolsUsedRejectsEmptyString)
{
  EnsureXProcessManagerInstance();

  XSTRING empty;
  XBUFFER converted;

  EXPECT_FALSE(GEN_XPROCESSMANAGER.AdjustStringToConsolaSymbolsUsed(empty, converted));
}


#ifdef LINUX
TEST(UNITTESTS_XPROCESSMANAGER_CLASSNAME, ApplicationTerminateSendsSIGTERMToRealChildProcess)
{
  // Verifies that Application_Terminate() (exercised here through the common GEN_XPROCESSMANAGER
  // interface) delivers a real SIGTERM to a real child process. Spawning that disposable child via
  // fork() and inspecting its death via waitpid()/WIFSIGNALED()/WTERMSIG() are POSIX-only concepts
  // with no equivalent shape on Windows (which would terminate via TerminateProcess() and inspect the
  // result via GetExitCodeProcess()), so this one test -- not the whole file -- stays LINUX-only.
  EnsureXProcessManagerInstance();

  pid_t child = fork();
  if(child == 0)
    {
      // Child: this test binary's own GEN framework startup (MainProcLINUX.cpp) installs a SIGTERM
      // handler for graceful app shutdown, and fork() inherits that handler into the child -- so a
      // real SIGTERM would just interrupt sleep() early rather than terminate the process, which
      // would defeat the point of this test. Reset SIGTERM to its default disposition first so the
      // child behaves like a normal, unrelated external process would.
      signal(SIGTERM, SIG_DFL);

      // Sleep far longer than this test needs -- it is expected to be killed by SIGTERM below,
      // never to exit on its own, so the parent's waitpid() never actually waits 30s.
      sleep(30);
      _exit(0);
    }

  ASSERT_GT(child, 0);

  // Bounded wait for the child to actually reach sleep() before signalling it.
  XTIMER* xtimer = GEN_XFACTORY.CreateTimer();
  while(xtimer->GetMeasureMilliSeconds() < 50) { }
  GEN_XFACTORY.DeleteTimer(xtimer);

  EXPECT_TRUE(GEN_XPROCESSMANAGER.Application_Terminate((XDWORD)child));

  int status = 0;
  ASSERT_EQ(waitpid(child, &status, 0), child);
  EXPECT_TRUE(WIFSIGNALED(status));
  EXPECT_EQ(WTERMSIG(status), SIGTERM);
}
#endif // LINUX


}
#endif
