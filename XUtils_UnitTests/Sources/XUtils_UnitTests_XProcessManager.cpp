/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XProcessManager.cpp
*
* @class      XUTILS_UNITTESTS_XPROCESSMANAGER
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

#include "XUtils_UnitTests_XProcessManager.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XProcessManager.h"
#include "XConsole.h"
#include "XBuffer.h"
#include "XTimer.h"

// XLINUXPROCESSMANAGER (and the real background-process-spawning tests that exercise it below) is a
// Linux-only class (GEN/Platforms/Linux/XLINUXProcessManager.h/.cpp, only ever compiled into this
// project's own CMakeLists.txt under COMPILE_FOR_LINUX -- see CMake/CMakeLists.txt). It, and the C
// runtime headers only its tests need (stdio.h/string.h for /proc parsing, unistd.h/sys/wait.h/
// signal.h for fork()/waitpid()/SIGTERM), are therefore only included/used on Linux, so this test
// file compiles cleanly on every other platform too.
#ifdef LINUX
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

#include "XLINUXProcessManager.h"
#endif


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         XCONSOLE_SYMBOLSUSED Console_GetSymbolsUsed()
* @brief      Link-time stub for the free function XPROCESSMANAGER::AdjustStringToConsolaSymbolsUsed()/
*             AdjustConsolaSymbolsUsedToString() call (declared in XConsole.h, normally defined in
*             XConsole.cpp). XConsole.cpp itself cannot be compiled into this build: XCONSOLE_FEATURE
*             is off here, so XFACTORY::CreateConsole()/DeleteConsole() (which XConsole.cpp needs) are
*             themselves #ifdef'd out of XFactory.h/.cpp -- a real, unreachable feature gate (see
*             STATUS.md Batch 5), not a fixable build-list oversight like XFString/XBufferBits were.
*             Compiling XProcessManager.cpp for XPROCESSMANAGER testing pulls in this one free-function
*             reference regardless of whether a test calls those two methods (the whole .o is linked),
*             so this file (not GEN) supplies the same answer a real non-console gtest process would
*             get from an implementation: "not a real console".
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
XCONSOLE_SYMBOLSUSED Console_GetSymbolsUsed()
{
  return XCONSOLE_SYMBOLSUSED_NOTCONSOLE;
}


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XPROCESSMANAGER
{


// Everything below that needs a real, concrete XPROCESSMANAGER (the XLINUXPROCESSMANAGER subclass,
// real OS process spawning/termination, /proc parsing) is Linux-only for the same reason the includes
// above are: no other platform's concrete XPROCESSMANAGER subclass is compiled into this project.
// Only the portable, platform-agnostic XPROCESS record tests above run everywhere.
#ifdef LINUX


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void EnsureXProcessManagerInstance()
* @brief      Ensures the XPROCESSMANAGER singleton exists, installing the real XLINUXPROCESSMANAGER
*             subclass (as MainProcLINUX.cpp would, if XPROCESSMANAGER_ACTIVE were defined in this
*             build) so tests exercise real process-spawning behavior, not the unimplemented base stubs.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void EnsureXProcessManagerInstance()
{
  if(!XPROCESSMANAGER::GetIsInstanced())
    {
      XPROCESSMANAGER* instance = GEN_NEW XLINUXPROCESSMANAGER();
      XPROCESSMANAGER::SetInstance(instance);
    }
}


/*---- XPROCESS: plain data record ---------------------------------------------------------------------------------*/


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ProcessDefaultState)
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


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ProcessGetSetID)
{
  XPROCESS process;

  process.SetID(1234);
  EXPECT_EQ(process.GetID(), (XDWORD)1234);
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ProcessGetSetWindowHandle)
{
  XPROCESS process;
  void*    fakehandle = (void*)0x1234;

  process.SetWindowHandle(fakehandle);
  EXPECT_EQ(process.GetWindowHandle(), fakehandle);
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ProcessGetSetWindowTitleHeightAndBorderWidth)
{
  XPROCESS process;

  process.SetWindowTitleHeight(20);
  process.SetWindowBorderWidth(4);

  EXPECT_EQ(process.GetWindowTitleHeight(), 20);
  EXPECT_EQ(process.GetWindowBorderWidth(), 4);
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ProcessCopyToCopiesAllFields)
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


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ProcessCopyFromMirrorsCopyTo)
{
  XPROCESS src, dst;

  src.SetID(99);
  src.GetName()->Set(__L("other"));

  EXPECT_TRUE(dst.CopyFrom(src));

  EXPECT_EQ(dst.GetID(), (XDWORD)99);
  EXPECT_STREQ(dst.GetName()->Get(), __L("other"));
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ProcessCompareTrueForIdenticalCopiesOnlyFixed)
{
  XPROCESS src, dst;

  src.SetID(1);
  src.GetPath()->Set(__L("/bin/x"));
  src.GetName()->Set(__L("x"));
  src.GetWindowTitle()->Set(__L("X"));

  src.CopyTo(dst);

  EXPECT_TRUE(dst.Compare(src, true));
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ProcessCompareNotOnlyFixedRectEqualityCheckIsCorrect)
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


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ProcessCompareNotOnlyFixedDetectsGenuineRectAreaDifference)
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


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ProcessCompareFalseWhenIDDiffers)
{
  XPROCESS src, dst;

  src.SetID(1);
  src.CopyTo(dst);
  dst.SetID(2);

  EXPECT_FALSE(dst.Compare(src, true));
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ProcessCompareOnlyFixedIgnoresRectAndHeights)
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


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, SetInstanceNull)
{
  EXPECT_FALSE(XPROCESSMANAGER::SetInstance(NULL));
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, InstanceLifecycle)
{
  XPROCESSMANAGER* originalinstance = NULL;
  if(XPROCESSMANAGER::GetIsInstanced()) originalinstance = &XPROCESSMANAGER::GetInstance();

  XPROCESSMANAGER* testinstance = GEN_NEW XLINUXPROCESSMANAGER();
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


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, DelInstanceTwice)
{
  XPROCESSMANAGER* originalinstance = NULL;
  if(XPROCESSMANAGER::GetIsInstanced()) originalinstance = &XPROCESSMANAGER::GetInstance();

  XPROCESSMANAGER* testinstance = GEN_NEW XLINUXPROCESSMANAGER();
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


/*---- XPROCESSMANAGER: real (bounded, self-exiting) OS process spawning on Linux --------------------------------------*/


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, MakeSystemCommandRunsRealShellCommand)
{
  EnsureXProcessManagerInstance();

  EXPECT_TRUE(GEN_XPROCESSMANAGER.MakeSystemCommand(__L("true")));
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, MakeSystemCommandDoesNotReportNonZeroExitAsFailure)
{
  // MakeSystemCommand() only ever reports failure when system() itself returns -1 (the shell could
  // not be launched at all) -- it never inspects the child command's own exit status. So a command
  // that legitimately exits non-zero (like the "false" utility) still comes back as true. Captured
  // here as real behavior, not fixed.
  EnsureXProcessManagerInstance();

  EXPECT_TRUE(GEN_XPROCESSMANAGER.MakeSystemCommand(__L("false")));
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, MakeCommandCapturesRealOutputThroughAPopenPipe)
{
  // FIXED (previously a known bug, now confirmed corrected in XLINUXProcessManager.cpp):
  // MakeCommand() used to call popen(cmd, "rt") -- "rt" is an MSVCRT/Windows-style text-mode
  // flag, not a valid POSIX popen() type string. glibc's popen() strictly requires "r" or "w"
  // (optionally "e") and rejected anything else with EINVAL, so pipe was always NULL and
  // MakeCommand() always returned false regardless of the command. It now correctly calls
  // popen(cmd, "r"), so MakeCommand is a real, working API on Linux -- exercised here for the
  // first time.
  EnsureXProcessManagerInstance();

  XBUFFER out;
  int     returncode = -1;

  EXPECT_TRUE(GEN_XPROCESSMANAGER.MakeCommand(__L("echo hello"), &out, &returncode));
  EXPECT_FALSE(out.IsEmpty());
  EXPECT_EQ(returncode, 0);

  out.Add((XBYTE)0);

  XSTRING outstring;
  outstring = out.GetPtrChar();
  EXPECT_NE(outstring.Find(__L("hello"), false), XSTRING_NOTFOUND);
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ApplicationExecuteRunsRealShortLivedProcessSuccessfully)
{
  EnsureXProcessManagerInstance();

  int returncode = -1;

  EXPECT_TRUE(GEN_XPROCESSMANAGER.Application_Execute(__L("/bin/true"), NULL, (XBUFFER*)NULL, (XBUFFER*)NULL, &returncode));
  EXPECT_EQ(returncode, 0);
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ApplicationExecuteReportsNonZeroExitAsFailure)
{
  EnsureXProcessManagerInstance();

  int returncode = -1;

  EXPECT_FALSE(GEN_XPROCESSMANAGER.Application_Execute(__L("/bin/false"), NULL, (XBUFFER*)NULL, (XBUFFER*)NULL, &returncode));
  EXPECT_EQ(returncode, 1);
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ApplicationExecuteCapturesStdoutWithParams)
{
  EnsureXProcessManagerInstance();

  XBUFFER out;
  int     returncode = -1;

  EXPECT_TRUE(GEN_XPROCESSMANAGER.Application_Execute(__L("/bin/echo"), __L("hello_world"), (XBUFFER*)NULL, &out, &returncode));
  EXPECT_EQ(returncode, 0);

  out.Add((XBYTE)0);

  XSTRING outstring;
  outstring = out.GetPtrChar();
  EXPECT_NE(outstring.Find(__L("hello_world"), false), XSTRING_NOTFOUND);
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ApplicationExecuteRejectsMissingApplicationPath)
{
  EnsureXProcessManagerInstance();

  EXPECT_FALSE(GEN_XPROCESSMANAGER.Application_Execute(__L("/this/path/does/not/exist"), NULL, (XBUFFER*)NULL, (XBUFFER*)NULL, (int*)NULL));
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ApplicationGetRunningListViaBaseSingletonNowDispatchesCorrectly)
{
  // PARTIALLY FIXED: XLINUXPROCESSMANAGER::Application_GetRunningList() (XLINUXProcessManager.h)
  // now takes the same signature as the virtual base method,
  // XPROCESSMANAGER::Application_GetRunningList(XVECTOR<XPROCESS*>&, bool
  // onlywithvalidwindow=false) (XProcessManager.h) -- previously the derived override dropped the
  // second parameter, giving it a different signature that *hid* the base method instead of
  // overriding it, so calling it through a base-typed reference/pointer (exactly what
  // GEN_XPROCESSMANAGER / XPROCESSMANAGER::GetInstance() gives you) silently resolved to the base
  // class's own do-nothing stub. Now the vtable dispatch correctly reaches the real Linux
  // /proc-scanning implementation, which does populate applist (confirmed below).
  //
  // STILL OPEN (real bug, reported, not fixed): XLINUXPROCESSMANAGER::Application_GetRunningList()
  // itself (XLINUXProcessManager.cpp) unconditionally "return false;" at the very end of the
  // function, even after successfully scanning /proc and populating applist -- so the return value
  // can never be trusted to reflect success, only the output list can.
  EnsureXProcessManagerInstance();

  XVECTOR<XPROCESS*> applist;

  EXPECT_FALSE(GEN_XPROCESSMANAGER.Application_GetRunningList(applist)); // always false, even on success
  EXPECT_FALSE(applist.IsEmpty());                                       // but the list IS populated now

  XPROCESS* self = XPROCESSMANAGER::Application_GetProcessByID((XDWORD)getpid(), applist);
  EXPECT_NE(self, (XPROCESS*)NULL);

  applist.DeleteContents();
  applist.DeleteAll();
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ApplicationGetRunningListFindsThisTestProcessWhenCalledOnConcreteType)
{
  // Same call, but through a concretely-typed XLINUXPROCESSMANAGER object (not the base-typed
  // singleton reference): here the real /proc-scanning implementation genuinely runs and finds
  // this very test process, proving the underlying logic works -- only the polymorphic dispatch
  // above is broken.
  XLINUXPROCESSMANAGER linuxpm;
  XVECTOR<XPROCESS*>    applist;

  linuxpm.Application_GetRunningList(applist);
  EXPECT_FALSE(applist.IsEmpty());

  XPROCESS* self = XPROCESSMANAGER::Application_GetProcessByID((XDWORD)getpid(), applist);
  EXPECT_NE(self, (XPROCESS*)NULL);

  applist.DeleteContents();
  applist.DeleteAll();
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ApplicationGetProcessByIDReturnsNullWhenNotFound)
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


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ApplicationIsRunningFindsThisTestProcessByItsOwnName)
{
  EnsureXProcessManagerInstance();

  // Read this process's real /proc/self/status "Name:" token, exactly like
  // XLINUXPROCESSMANAGER::Application_IsRunning() itself does for every candidate PID, so the test
  // never has to hardcode the test binary's name.
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
  EXPECT_EQ(foundID, (XDWORD)getpid());
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, AdjustStringToConsolaSymbolsUsedSkipsConversionWhenNotARealConsole)
{
  // XSTRING::ConsoleCodePageToConvertASCII() (XString.cpp) deliberately maps
  // XCONSOLE_SYMBOLSUSED_NOTCONSOLE to XSTRINGASCIICODE_NONE -- i.e. "we are not attached to a real
  // console, so there is no known target code page to convert to". AdjustStringToConsolaSymbolsUsed()
  // then has nothing to do and leaves target_buffer empty, so it correctly returns false here: this
  // gtest binary genuinely is not a real console, so Console_GetSymbolsUsed() (our link-time stub,
  // standing in for XConsole.cpp -- see above) reporting NOTCONSOLE is the accurate answer, and
  // this is intended behavior, not a bug.
  EnsureXProcessManagerInstance();

  XSTRING original;
  original = __L("hello");

  XBUFFER converted;
  EXPECT_FALSE(GEN_XPROCESSMANAGER.AdjustStringToConsolaSymbolsUsed(original, converted));
  EXPECT_TRUE(converted.IsEmpty());
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, AdjustConsolaSymbolsUsedToStringDoesNotSkipUnlikeItsCounterpart)
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


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, AdjustStringToConsolaSymbolsUsedRejectsEmptyString)
{
  EnsureXProcessManagerInstance();

  XSTRING empty;
  XBUFFER converted;

  EXPECT_FALSE(GEN_XPROCESSMANAGER.AdjustStringToConsolaSymbolsUsed(empty, converted));
}


TEST(UNITTEST_XPROCESSMANAGER_CLASSNAME, ApplicationTerminateSendsSIGTERMToRealChildProcess)
{
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
