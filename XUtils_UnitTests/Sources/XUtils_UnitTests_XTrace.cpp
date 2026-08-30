/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XTrace.cpp
*
* @class      XUTILS_UNITTESTS_XTRACE
* @brief      XUtils unit tests for XTrace class
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

#include "XUtils_UnitTests_XTrace.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XTrace.h"
#include "XFactory.h"
#include "XDateTime.h"
#include "XBuffer.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


// XTRACE is this codebase's THIRD distinct singleton-access convention (XTrace.h line 470): a bare
// public "static XTRACE* instance;" pointer, with no GetInstance()/SetInstance()/GetIsInstanced()/
// DelInstance() API whatsoever - every XTRACE_* macro dereferences XTRACE::instance directly. This
// process's real instance was already constructed and populated for real by AppProc_Ini
// (XTRACE_SETAPPLICATIONNAME, two real net targets added via XTRACE_ADDTARGET, etc.) before any
// TEST body below runs. Because the pointer is a bare public static, we can temporarily swap it to
// point at a throwaway local XTRACE object for tests that need a clean slate (target management,
// size limit, application metadata), and always restore the original pointer before the test
// returns - never leaving the shared, real instance's pointer replaced for any other test in this
// binary. XTRACE_ACTIVE is defined for this desktop build (confirmed in build.ninja's DEFINES), so
// the real, non-stub XTRACE class methods below are exactly what the XTRACE_* macros used
// throughout AppProc_Ini ultimately call.
#ifdef GOOGLETEST_ACTIVE
namespace TEST_XTRACE
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static XTRACE* SwapInFreshXTrace(XTRACE** originalinstance)
* @brief      Temporarily swaps XTRACE::instance for a fresh, heap-allocated, clean-slate XTRACE
*             object, returning it and handing back the real original pointer via out-parameter so
*             the caller can restore it explicitly with RestoreXTrace() below.
* @note       Deliberately NOT a stack-scoped RAII guard: XTRACE::Clean() (see the bug documented in
*             ConstructingAnXTRACEObjectUnconditionallyNullsTheSharedStaticInstancePointer below)
*             unconditionally nulls the shared static XTRACE::instance from ANY XTRACE destructor,
*             including a plain stack-local test object's. With RAII, C++ destroys objects in
*             REVERSE declaration order, so a guard restoring the pointer in ITS destructor would
*             run BEFORE the local XTRACE object's own destructor re-nulls it moments later -
*             leaving XTRACE::instance permanently NULL after the test returns and crashing later,
*             unrelated tests the next time anything dereferences it. Managing both the test
*             object's lifetime and the pointer restore explicitly, in one fixed order, avoids that.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static XTRACE* SwapInFreshXTrace(XTRACE** originalinstance)
{
  *originalinstance = XTRACE::instance;

  XTRACE* testinstance = GEN_NEW XTRACE();
  XTRACE::instance     = testinstance;

  return testinstance;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void RestoreXTrace(XTRACE* testinstance, XTRACE* originalinstance)
* @brief      Deletes the test instance and restores the real original XTRACE::instance pointer,
*             in that fixed order - see SwapInFreshXTrace() above for why the order matters.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void RestoreXTrace(XTRACE* testinstance, XTRACE* originalinstance)
{
  GEN_DELETE testinstance;
  XTRACE::instance = originalinstance;
}


TEST(UNITTEST_XTRACE_CLASSNAME, ConstructingAnXTRACEObjectUnconditionallyNullsTheSharedStaticInstancePointer)
{
  // Source concern (real bug, not fixed): XTRACE::Clean() (XTrace.cpp line 2368) unconditionally
  // executes "instance = NULL;" even though Clean() is an ordinary (non-static) member function
  // called from the constructor. Since "instance" is the class's single STATIC pointer, merely
  // constructing ANY XTRACE object - even one never intended to become the shared singleton -
  // clobbers whatever XTRACE::instance currently points to. We capture the observable side effect
  // here and restore the real pointer immediately afterwards, before any other test runs.
  XTRACE* original = XTRACE::instance;
  ASSERT_NE(original, nullptr);

  { XTRACE second;
    EXPECT_EQ(XTRACE::instance, nullptr);
  }

  XTRACE::instance = original;
  EXPECT_EQ(XTRACE::instance, original);
}


TEST(UNITTEST_XTRACE_CLASSNAME, TargetDefaultConstructionIsTypeNoneWithEmptyAimAndNoSendings)
{
  XTRACE_TARGET target;

  EXPECT_EQ(target.GetType(), XTRACE_TYPE_NONE);
  EXPECT_STREQ(target.GetAim(), __L(""));
  EXPECT_EQ(target.GetNSendings(), (XDWORD)0);
}


TEST(UNITTEST_XTRACE_CLASSNAME, TargetSetTypeAndSetAimFromCharPointer)
{
  XTRACE_TARGET target;

  target.SetType(XTRACE_TYPE_FILE);
  EXPECT_EQ(target.GetType(), XTRACE_TYPE_FILE);

  target.SetAim(__L("/tmp/mytrace.log"));
  EXPECT_STREQ(target.GetAim(), __L("/tmp/mytrace.log"));

  XSTRING aimstring;
  EXPECT_TRUE(target.GetAim(aimstring));
  EXPECT_STREQ(aimstring.Get(), __L("/tmp/mytrace.log"));
}


TEST(UNITTEST_XTRACE_CLASSNAME, TargetSetAimFromXStringReference)
{
  XTRACE_TARGET target;
  XSTRING       aim = __L("special-aim");

  target.SetAim(aim);
  EXPECT_STREQ(target.GetAim(), __L("special-aim"));
}


TEST(UNITTEST_XTRACE_CLASSNAME, TargetGetAimOnAnEmptyTargetReportsFalse)
{
  XTRACE_TARGET target;
  XSTRING       aimstring;

  EXPECT_FALSE(target.GetAim(aimstring));
}


TEST(UNITTEST_XTRACE_CLASSNAME, TargetAddNSendingsIncrementsCounter)
{
  XTRACE_TARGET target;

  EXPECT_EQ(target.GetNSendings(), (XDWORD)0);
  target.AddNSendings();
  target.AddNSendings();
  EXPECT_EQ(target.GetNSendings(), (XDWORD)2);
}


TEST(UNITTEST_XTRACE_CLASSNAME, TargetCleanResetsTypeAimAndSendingsToDefaults)
{
  XTRACE_TARGET target;

  target.SetType(XTRACE_TYPE_SPECIAL);
  target.SetAim(__L("something"));
  target.AddNSendings();

  target.Clean();

  EXPECT_EQ(target.GetType(), XTRACE_TYPE_NONE);
  EXPECT_STREQ(target.GetAim(), __L(""));
  EXPECT_EQ(target.GetNSendings(), (XDWORD)0);
}


TEST(UNITTEST_XTRACE_CLASSNAME, StatusMsgDefaultConstructionIsZeroedAndOwnsARealTimer)
{
  XTRACE_STATUS_MSG statusmsg;

  EXPECT_EQ(statusmsg.GetType(), XTRACE_TYPE_STATUS_MSG_UNKNOWN);
  EXPECT_FALSE(statusmsg.Value_GetBoolean());
  EXPECT_EQ(statusmsg.Value_GetInteger(), 0);
  EXPECT_STREQ(statusmsg.Value_GetString()->Get(), __L(""));
  EXPECT_EQ(statusmsg.Value_GetDword(), (XDWORD)0);
  EXPECT_FLOAT_EQ(statusmsg.Value_GetFloat(), 0.0f);

  // Constructed for real via GEN_XFACTORY.CreateTimer() (XTrace.cpp line 392) and released via
  // GEN_XFACTORY.DeleteTimer() in the destructor - a real, working XTIMER, not a stub.
  EXPECT_NE(statusmsg.GetXTimerLastUpdate(), nullptr);
}


TEST(UNITTEST_XTRACE_CLASSNAME, StatusMsgBooleanIntegerDwordFloatValueRoundTrip)
{
  XTRACE_STATUS_MSG statusmsg;

  statusmsg.SetType(XTRACE_TYPE_STATUS_MSG_BOOLEAN);
  statusmsg.Value_SetBoolean(true);
  EXPECT_EQ(statusmsg.GetType(), XTRACE_TYPE_STATUS_MSG_BOOLEAN);
  EXPECT_TRUE(statusmsg.Value_GetBoolean());

  statusmsg.Value_SetInteger(-42);
  EXPECT_EQ(statusmsg.Value_GetInteger(), -42);

  statusmsg.Value_SetDword(123456);
  EXPECT_EQ(statusmsg.Value_GetDword(), (XDWORD)123456);

  statusmsg.Value_SetFloat(3.5f);
  EXPECT_FLOAT_EQ(statusmsg.Value_GetFloat(), 3.5f);
}


TEST(UNITTEST_XTRACE_CLASSNAME, StatusMsgColorValueRoundTrip)
{
  XTRACE_STATUS_MSG statusmsg;
  XBYTE             color[3] = { 10, 20, 30 };

  statusmsg.Value_SetColor(color);

  XBYTE* readback = statusmsg.Value_GetColor();
  ASSERT_NE(readback, nullptr);
  EXPECT_EQ(readback[0], 10);
  EXPECT_EQ(readback[1], 20);
  EXPECT_EQ(readback[2], 30);
}


TEST(UNITTEST_XTRACE_CLASSNAME, StatusMsgGetNameReturnsAMutableEmptyStringByDefault)
{
  XTRACE_STATUS_MSG statusmsg;

  ASSERT_NE(statusmsg.GetName(), nullptr);
  EXPECT_STREQ(statusmsg.GetName()->Get(), __L(""));

  statusmsg.GetName()->Set(__L("counter1"));
  EXPECT_STREQ(statusmsg.GetName()->Get(), __L("counter1"));
}


TEST(UNITTEST_XTRACE_CLASSNAME, StatusMsgsAddParsesABooleanEncodedLine)
{
  XTRACE_STATUS_MSGS statusmsgs;
  XSTRING            line;

  line.Format(__L("%s,%s,%c,%s"), XTRACE_IDMSGSTATUS, __L("flag1"), XTRACE_IDMSGSTATUS_BOOLEAN, __L("true"));

  XTRACE_STATUS_MSG* msg = statusmsgs.StatusMsg_Add(&line);
  ASSERT_NE(msg, nullptr);
  EXPECT_EQ(msg->GetType(), XTRACE_TYPE_STATUS_MSG_BOOLEAN);
  EXPECT_TRUE(msg->Value_GetBoolean());
  EXPECT_STREQ(msg->GetName()->Get(), __L("flag1"));

  statusmsgs.StatusMsg_DeleteAll();
}


TEST(UNITTEST_XTRACE_CLASSNAME, StatusMsgsAddParsesIntegerDwordFloatAndStringEncodedLines)
{
  XTRACE_STATUS_MSGS statusmsgs;

  XSTRING lineinteger;
  lineinteger.Format(__L("%s,%s,%c,%d"), XTRACE_IDMSGSTATUS, __L("counter"), XTRACE_IDMSGSTATUS_INTEGER, -7);
  XTRACE_STATUS_MSG* msginteger = statusmsgs.StatusMsg_Add(&lineinteger);
  ASSERT_NE(msginteger, nullptr);
  EXPECT_EQ(msginteger->GetType(), XTRACE_TYPE_STATUS_MSG_INTEGER);
  EXPECT_EQ(msginteger->Value_GetInteger(), -7);

  XSTRING linedword;
  linedword.Format(__L("%s,%s,%c,%d"), XTRACE_IDMSGSTATUS, __L("dwordval"), XTRACE_IDMSGSTATUS_DWORD, 999);
  XTRACE_STATUS_MSG* msgdword = statusmsgs.StatusMsg_Add(&linedword);
  ASSERT_NE(msgdword, nullptr);
  EXPECT_EQ(msgdword->GetType(), XTRACE_TYPE_STATUS_MSG_XDWORD);
  EXPECT_EQ(msgdword->Value_GetDword(), (XDWORD)999);

  XSTRING linestring;
  linestring.Format(__L("%s,%s,%c,%s"), XTRACE_IDMSGSTATUS, __L("textval"), XTRACE_IDMSGSTATUS_STRING, __L("hello"));
  XTRACE_STATUS_MSG* msgstring = statusmsgs.StatusMsg_Add(&linestring);
  ASSERT_NE(msgstring, nullptr);
  EXPECT_EQ(msgstring->GetType(), XTRACE_TYPE_STATUS_MSG_STRING);
  EXPECT_STREQ(msgstring->Value_GetString()->Get(), __L("hello"));

  EXPECT_EQ(statusmsgs.StatusMsg_GetAll()->GetSize(), (XDWORD)3);

  statusmsgs.StatusMsg_DeleteAll();
}


TEST(UNITTEST_XTRACE_CLASSNAME, StatusMsgsAddParsesAColorEncodedLine)
{
  XTRACE_STATUS_MSGS statusmsgs;
  XSTRING            line;

  line.Format(__L("%s,%s,%c,%02X,%02X,%02X"), XTRACE_IDMSGSTATUS, __L("led1"), XTRACE_IDMSGSTATUS_COLOR, 0xAA, 0xBB, 0xCC);

  XTRACE_STATUS_MSG* msg = statusmsgs.StatusMsg_Add(&line);
  ASSERT_NE(msg, nullptr);
  EXPECT_EQ(msg->GetType(), XTRACE_TYPE_STATUS_MSG_RGBCOLOR);
  EXPECT_EQ(msg->Value_GetColor()[0], 0xAA);
  EXPECT_EQ(msg->Value_GetColor()[1], 0xBB);
  EXPECT_EQ(msg->Value_GetColor()[2], 0xCC);

  statusmsgs.StatusMsg_DeleteAll();
}


TEST(UNITTEST_XTRACE_CLASSNAME, StatusMsgsAddOnRepeatedNameUpdatesInPlaceInsteadOfDuplicating)
{
  XTRACE_STATUS_MSGS statusmsgs;

  XSTRING line1;
  line1.Format(__L("%s,%s,%c,%d"), XTRACE_IDMSGSTATUS, __L("samename"), XTRACE_IDMSGSTATUS_INTEGER, 1);
  statusmsgs.StatusMsg_Add(&line1);

  XSTRING line2;
  line2.Format(__L("%s,%s,%c,%d"), XTRACE_IDMSGSTATUS, __L("samename"), XTRACE_IDMSGSTATUS_INTEGER, 2);
  statusmsgs.StatusMsg_Add(&line2);

  EXPECT_EQ(statusmsgs.StatusMsg_GetAll()->GetSize(), (XDWORD)1);
  EXPECT_EQ(statusmsgs.StatusMsg_Get(__L("samename"))->Value_GetInteger(), 2);

  statusmsgs.StatusMsg_DeleteAll();
}


TEST(UNITTEST_XTRACE_CLASSNAME, StatusMsgsAddReturnsNullForALineWithoutTheStatusMarker)
{
  XTRACE_STATUS_MSGS statusmsgs;
  XSTRING            line = __L("this line has no status marker at all");

  EXPECT_EQ(statusmsgs.StatusMsg_Add(&line), nullptr);
  EXPECT_EQ(statusmsgs.StatusMsg_Add(NULL), nullptr);
}


TEST(UNITTEST_XTRACE_CLASSNAME, StatusMsgsAddOnAClearMarkerLineDeletesEverythingAndReturnsNull)
{
  XTRACE_STATUS_MSGS statusmsgs;

  XSTRING line;
  line.Format(__L("%s,%s,%c,%d"), XTRACE_IDMSGSTATUS, __L("toclear"), XTRACE_IDMSGSTATUS_INTEGER, 5);
  statusmsgs.StatusMsg_Add(&line);
  EXPECT_EQ(statusmsgs.StatusMsg_GetAll()->GetSize(), (XDWORD)1);

  XSTRING clearline = XTRACE_IDMSGSTATUSCLEAR;
  EXPECT_EQ(statusmsgs.StatusMsg_Add(&clearline), nullptr);
  EXPECT_TRUE(statusmsgs.StatusMsg_GetAll()->IsEmpty());
}


TEST(UNITTEST_XTRACE_CLASSNAME, StatusMsgsGetByIndexAndDeleteAllOnEmptyReturnsFalse)
{
  XTRACE_STATUS_MSGS statusmsgs;

  EXPECT_EQ(statusmsgs.StatusMsg_Get(0), nullptr);
  EXPECT_FALSE(statusmsgs.StatusMsg_DeleteAll());

  XSTRING line;
  line.Format(__L("%s,%s,%c,%d"), XTRACE_IDMSGSTATUS, __L("byindex"), XTRACE_IDMSGSTATUS_INTEGER, 9);
  statusmsgs.StatusMsg_Add(&line);

  ASSERT_NE(statusmsgs.StatusMsg_Get(0), nullptr);
  EXPECT_STREQ(statusmsgs.StatusMsg_Get(0)->GetName()->Get(), __L("byindex"));

  EXPECT_TRUE(statusmsgs.StatusMsg_DeleteAll());
}


TEST(UNITTEST_XTRACE_CLASSNAME, SizeLimitDefaultsAndSetSizeLimitRejectsZero)
{
  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  EXPECT_EQ(localtrace->GetSizeLimit(), (XDWORD)XTRACE_SIZELIMITDEFAULT);

  EXPECT_FALSE(localtrace->SetSizeLimit(0));
  EXPECT_EQ(localtrace->GetSizeLimit(), (XDWORD)XTRACE_SIZELIMITDEFAULT);

  EXPECT_TRUE(localtrace->SetSizeLimit(2048));
  EXPECT_EQ(localtrace->GetSizeLimit(), (XDWORD)2048);

  RestoreXTrace(localtrace, originalinstance);
}


TEST(UNITTEST_XTRACE_CLASSNAME, ApplicationNameSetAndGetAllThreeOverloads)
{
  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  localtrace->Application_SetName(__L("App1"));
  EXPECT_STREQ(localtrace->Application_GetName(), __L("App1"));

  // Source concern (not a crash, but a real quirk worth documenting): the (XCHAR*,XDWORD size)
  // overload (XTrace.cpp lines 1128-1132) does "memcpy(this->applicationname, applicationname,
  // (size+1)*sizeof(XCHAR))" -- it copies size+1 characters straight from the source rather than
  // truncating to `size` characters and appending its own NUL terminator. It only produces a
  // clean, size-character result when the source string's own NUL happens to sit at index `size`
  // (i.e. size == real string length); passing a smaller size, as here, copies one extra live
  // character from the source instead of truncating it away.
  localtrace->Application_SetName(__L("App2Extra"), 4);
  EXPECT_STREQ(localtrace->Application_GetName(), __L("App2E"));

  XSTRING name3 = __L("App3");
  localtrace->Application_SetName(name3);
  EXPECT_STREQ(localtrace->Application_GetName(), __L("App3"));

  RestoreXTrace(localtrace, originalinstance);
}


TEST(UNITTEST_XTRACE_CLASSNAME, ApplicationVersionSetAndGetRoundTrip)
{
  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  localtrace->Application_SetVersion(1, 2, 3);

  int version = 0, subversion = 0, subversionerr = 0;
  localtrace->Application_GetVersion(version, subversion, subversionerr);

  EXPECT_EQ(version, 1);
  EXPECT_EQ(subversion, 2);
  EXPECT_EQ(subversionerr, 3);

  RestoreXTrace(localtrace, originalinstance);
}


TEST(UNITTEST_XTRACE_CLASSNAME, ApplicationIDSetAndGetBothOverloads)
{
  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  XSTRING id = __L("ID-1234");
  localtrace->Application_SetID(id);
  EXPECT_STREQ(localtrace->Application_GetID(), __L("ID-1234"));

  localtrace->Application_SetID(__L("ID-5678"), 7);
  EXPECT_STREQ(localtrace->Application_GetID(), __L("ID-5678"));

  RestoreXTrace(localtrace, originalinstance);
}


TEST(UNITTEST_XTRACE_CLASSNAME, AddTargetFillsSlotsInOrderAndFailsOnceAllSlotsAreFull)
{
  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  int filled = 0;
  while(localtrace->AddTarget(XTRACE_TYPE_SPECIAL, __L("aim")))
    {
      filled++;
      ASSERT_LE(filled, XTRACE_MAXNTARGETS);
    }

  EXPECT_EQ(filled, XTRACE_MAXNTARGETS);

  // Every slot is now full: one more AddTarget() call must fail.
  EXPECT_FALSE(localtrace->AddTarget(XTRACE_TYPE_SPECIAL, __L("overflow")));

  RestoreXTrace(localtrace, originalinstance);
}


TEST(UNITTEST_XTRACE_CLASSNAME, SetTargetOutOfRangeIndexOrNullAimIsRejected)
{
  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  EXPECT_FALSE(localtrace->SetTarget(XTRACE_MAXNTARGETS, XTRACE_TYPE_SPECIAL, __L("aim")));
  EXPECT_FALSE(localtrace->SetTarget(0, XTRACE_TYPE_SPECIAL, NULL));

  EXPECT_TRUE(localtrace->SetTarget(0, XTRACE_TYPE_SPECIAL, __L("validaim")));

  RestoreXTrace(localtrace, originalinstance);
}


TEST(UNITTEST_XTRACE_CLASSNAME, DeactivateAllTargetsResetsEverySlotToTypeNone)
{
  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  EXPECT_TRUE(localtrace->AddTarget(XTRACE_TYPE_SPECIAL, __L("aim1")));
  EXPECT_TRUE(localtrace->AddTarget(XTRACE_TYPE_FILE, __L("aim2")));

  EXPECT_TRUE(localtrace->DeactivateAllTargets());

  // With every slot back to XTRACE_TYPE_NONE, AddTarget() must be able to fill slot 0 again.
  EXPECT_TRUE(localtrace->SetTarget(0, XTRACE_TYPE_SPECIAL, __L("aimagain")));

  RestoreXTrace(localtrace, originalinstance);
}


TEST(UNITTEST_XTRACE_CLASSNAME, PrintPrintHeaderClearScreenAndClearMsgsStatusAreSafeWithNoTargetsConfigured)
{
  // With no targets configured, PrintSpecial/PrintFile/PrintNet are never invoked (Print() only
  // dispatches to a target whose slot type is not XTRACE_TYPE_NONE), so these calls are entirely
  // side-effect free and safe to assert on just their return values.
  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  EXPECT_TRUE(localtrace->Print(0, __L("plain message %d"), 42));
  EXPECT_TRUE(localtrace->ClearScreen(0));
  EXPECT_TRUE(localtrace->ClearMsgsStatus(0));

  localtrace->PrintHeader(0, __L("A Header"));  // void: only checking it does not crash.

  XBYTE data[4] = { 0x01, 0x02, 0x03, 0x04 };
  EXPECT_TRUE(localtrace->PrintDataBlock(0, data, 4));

  XBUFFER xbuffer;
  xbuffer.Add(data, 4);
  EXPECT_TRUE(localtrace->PrintDataBlock(0, xbuffer));

  RestoreXTrace(localtrace, originalinstance);
}


TEST(UNITTEST_XTRACE_CLASSNAME, PrintMsgStatusOverloadsAllReturnTrueWithNoTargetsConfigured)
{
  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  XBYTE color[3] = { 1, 2, 3 };

  EXPECT_TRUE(localtrace->PrintMsgStatus(0, __L("b"), true));
  EXPECT_TRUE(localtrace->PrintMsgStatus(0, __L("i"), (int)-5));
  EXPECT_TRUE(localtrace->PrintMsgStatus(0, __L("s"), __L("text")));
  EXPECT_TRUE(localtrace->PrintMsgStatus(0, __L("d"), (XDWORD)7));
  EXPECT_TRUE(localtrace->PrintMsgStatus(0, __L("f"), 1.5f));
  EXPECT_TRUE(localtrace->PrintMsgStatus(0, __L("c"), color));

  RestoreXTrace(localtrace, originalinstance);
}


TEST(UNITTEST_XTRACE_CLASSNAME, SetTraceTextToXBufferAndGetTraceFromXBufferRoundTrip)
{
  XDATETIME* xtimewrite = GEN_XFACTORY.CreateDateTime();
  ASSERT_NE(xtimewrite, nullptr);

  xtimewrite->SetYear(2024);
  xtimewrite->SetMonth(6);
  xtimewrite->SetDay(15);
  xtimewrite->SetHours(10);
  xtimewrite->SetMinutes(30);
  xtimewrite->SetSeconds(45);
  xtimewrite->SetMilliSeconds(500);

  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  XBUFFER xbufferpacket;
  EXPECT_TRUE(localtrace->SetTraceTextToXBuffer((XDWORD)0x0A0B0C0D, (XDWORD)0x01020304, (XBYTE)5, (XDWORD)7, xtimewrite, __L("hello trace"), xbufferpacket));

  XDWORD    publicIPread = 0;
  XDWORD    localIPread  = 0;
  XBYTE     levelread    = 0;
  XDWORD    sequenceread = 0;
  XBUFFER   dataread;
  XDATETIME* xtimeread = GEN_XFACTORY.CreateDateTime();
  ASSERT_NE(xtimeread, nullptr);

  EXPECT_EQ(localtrace->GetTraceFromXBuffer(xbufferpacket, publicIPread, localIPread, levelread, sequenceread, xtimeread, dataread), (XDWORD)0);

  EXPECT_EQ(publicIPread, (XDWORD)0x0A0B0C0D);
  EXPECT_EQ(localIPread,  (XDWORD)0x01020304);
  EXPECT_EQ(levelread,    (XBYTE)5);
  EXPECT_EQ(sequenceread, (XDWORD)7);

  EXPECT_EQ(xtimeread->GetYear(),         2024);
  EXPECT_EQ(xtimeread->GetMonth(),        6);
  EXPECT_EQ(xtimeread->GetDay(),          15);
  EXPECT_EQ(xtimeread->GetHours(),        10);
  EXPECT_EQ(xtimeread->GetMinutes(),      30);
  EXPECT_EQ(xtimeread->GetSeconds(),      45);
  EXPECT_EQ(xtimeread->GetMilliSeconds(), 500);

  XSTRING textread;
  EXPECT_TRUE(localtrace->SetTraceDataToText(dataread, textread));
  EXPECT_STREQ(textread.Get(), __L("hello trace"));

  GEN_XFACTORY.DeleteDateTime(xtimewrite);
  GEN_XFACTORY.DeleteDateTime(xtimeread);
  RestoreXTrace(localtrace, originalinstance);
}


TEST(UNITTEST_XTRACE_CLASSNAME, GetTraceFromXBufferRejectsAnEmptyOrUndersizedBuffer)
{
  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  XDATETIME* xtime = GEN_XFACTORY.CreateDateTime();
  ASSERT_NE(xtime, nullptr);

  XDWORD  publicIPread = 0, localIPread = 0, sequenceread = 0;
  XBYTE   levelread = 0;
  XBUFFER dataread;
  XBUFFER emptybuffer;

  EXPECT_EQ(localtrace->GetTraceFromXBuffer(emptybuffer, publicIPread, localIPread, levelread, sequenceread, xtime, dataread), (XDWORD)1);

  // A NULL xtime pointer is also explicitly rejected before touching the buffer at all.
  XBUFFER somebuffer;
  somebuffer.Add((XBYTE)0);
  EXPECT_EQ(localtrace->GetTraceFromXBuffer(somebuffer, publicIPread, localIPread, levelread, sequenceread, NULL, dataread), (XDWORD)1);

  GEN_XFACTORY.DeleteDateTime(xtime);
  RestoreXTrace(localtrace, originalinstance);
}


TEST(UNITTEST_XTRACE_CLASSNAME, GetTraceFromXBufferDetectsACorruptedCRC)
{
  XDATETIME* xtimewrite = GEN_XFACTORY.CreateDateTime();
  ASSERT_NE(xtimewrite, nullptr);

  XTRACE* originalinstance = NULL;
  XTRACE* localtrace = SwapInFreshXTrace(&originalinstance);

  XBUFFER xbufferpacket;
  EXPECT_TRUE(localtrace->SetTraceTextToXBuffer((XDWORD)1, (XDWORD)2, (XBYTE)3, (XDWORD)4, xtimewrite, __L("crc check"), xbufferpacket));

  // Flip the very last byte (part of the trailing CRC16) so the packet's own CRC no longer matches.
  XBYTE* rawdata = xbufferpacket.Get();
  rawdata[xbufferpacket.GetSize()-1] ^= 0xFF;

  XDWORD    publicIPread = 0, localIPread = 0, sequenceread = 0;
  XBYTE     levelread = 0;
  XBUFFER   dataread;
  XDATETIME* xtimeread = GEN_XFACTORY.CreateDateTime();
  ASSERT_NE(xtimeread, nullptr);

  EXPECT_EQ(localtrace->GetTraceFromXBuffer(xbufferpacket, publicIPread, localIPread, levelread, sequenceread, xtimeread, dataread), (XDWORD)2);

  GEN_XFACTORY.DeleteDateTime(xtimewrite);
  GEN_XFACTORY.DeleteDateTime(xtimeread);
  RestoreXTrace(localtrace, originalinstance);
}


}
#endif

