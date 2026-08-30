/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XFileTXT.cpp
*
* @class      XUTILS_UNITTESTS_XFILETXT
* @brief      XUtils unit tests for XFILETXT class
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

#include "XUtils_UnitTests_XFileTXT.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XFactory.h"
#include "XFileTXT.h"
#include "XPath.h"
#include "XFile.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFILETXT
{


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


TEST(UNITTEST_XFILETXT_CLASSNAME, CreateAddLineWriteThenOpenReadRoundTripASCII)
{
  XPATH xpath(__L("/tmp/xutils_unittests_xfiletxt_ascii.txt"));
  RemoveIfExists(xpath);

  {
    XFILETXT writer;

    ASSERT_TRUE(writer.Create(xpath, XFILETXTFORMATCHAR_ASCII, XFILETXTTYPELF_0A));

    EXPECT_TRUE(writer.AddLine(__L("line one")));
    EXPECT_TRUE(writer.AddLine(__L("line two")));
    EXPECT_TRUE(writer.AddLine(__L("line three")));

    EXPECT_EQ(writer.GetNLines(), 3);

    EXPECT_TRUE(writer.WriteAllFile());
    EXPECT_TRUE(writer.Close());
  }

  {
    XFILETXT reader;

    ASSERT_TRUE(reader.Open(xpath, true));
    EXPECT_EQ(reader.GetFormatChar(), XFILETXTFORMATCHAR_ASCII);

    EXPECT_TRUE(reader.ReadAllFile());

    ASSERT_EQ(reader.GetNLines(), 3);

    EXPECT_STREQ(reader.GetLineText(0), __L("line one"));
    EXPECT_STREQ(reader.GetLineText(1), __L("line two"));
    EXPECT_STREQ(reader.GetLineText(2), __L("line three"));

    // NOTE: GetLine()/GetLineText() with an out-of-range index are deliberately NOT exercised
    // here -- see GetLineUsesUnboundedFastGetInsteadOfBoundsCheckedGet below for why an
    // out-of-range GetLine() call is genuine undefined behavior in this class, not a safe,
    // NULL-returning query.

    reader.Close();
  }

  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILETXT_CLASSNAME, UTF8BOMIsWrittenAndDetectedOnReopen)
{
  XPATH xpath(__L("/tmp/xutils_unittests_xfiletxt_utf8.txt"));
  RemoveIfExists(xpath);

  {
    XFILETXT writer;

    ASSERT_TRUE(writer.Create(xpath, XFILETXTFORMATCHAR_UTF8, XFILETXTTYPELF_0A));
    EXPECT_TRUE(writer.AddLine(__L("utf8 content")));
    EXPECT_TRUE(writer.WriteAllFile());
    writer.Close();
  }

  {
    XFILETXT reader;

    ASSERT_TRUE(reader.Open(xpath, true));

    // Open() calls GetFormatCharFromFile() internally and adopts its result -- the UTF8 BOM
    // (0xEF 0xBB 0xBF) written by WriteAllFile()/CreateBOMFormatChar() must be detected here.
    EXPECT_EQ(reader.GetFormatChar(), XFILETXTFORMATCHAR_UTF8);

    XDWORD sizeBOM = 0;
    EXPECT_EQ(reader.GetFormatCharFromFile(&sizeBOM), XFILETXTFORMATCHAR_UTF8);
    EXPECT_EQ(sizeBOM, (XDWORD)3);

    reader.Close();
  }

  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILETXT_CLASSNAME, LineEndingContentSplitsCorrectlyOnReopenFor0AAnd0D)
{
  // Only 0A and 0D are exercised for the write-then-read round trip here -- see the dedicated
  // CreateTypeLFHasTypoForCombinedLineEndings test below for why 0A0D/0D0A combined line endings
  // do not round trip through CreateTypeLF() as shipped. See also
  // OpenForcesDefaultTypeLFSoAutoDetectionNeverFiresThroughReadNLines below for why this test
  // deliberately does NOT assert on GetTypeLF() after reopening.
  XFILETXTTYPELF typesToTest[2] = { XFILETXTTYPELF_0A, XFILETXTTYPELF_0D };

  for(int t = 0; t < 2; t++)
    {
      XPATH xpath(__L("/tmp/xutils_unittests_xfiletxt_lf.txt"));
      RemoveIfExists(xpath);

      {
        XFILETXT writer;

        ASSERT_TRUE(writer.Create(xpath, XFILETXTFORMATCHAR_ASCII, typesToTest[t]));
        writer.AddLine(__L("first"));
        writer.AddLine(__L("second"));
        writer.WriteAllFile();
        writer.Close();
      }

      {
        XFILETXT reader;

        ASSERT_TRUE(reader.Open(xpath, true));
        EXPECT_TRUE(reader.ReadNLines());

        ASSERT_EQ(reader.GetNLines(), 2);
        EXPECT_STREQ(reader.GetLineText(0), __L("first"));
        EXPECT_STREQ(reader.GetLineText(1), __L("second"));

        reader.Close();
      }

      RemoveIfExists(xpath);
    }
}


TEST(UNITTEST_XFILETXT_CLASSNAME, OpenForcesDefaultTypeLFSoAutoDetectionNeverFiresThroughReadNLines)
{
  // Real, concrete XUtils bug (not fixed, per the hard rule): XFILETXT::Open(XPATH&,bool)
  // (XFileTXT.cpp) unconditionally sets `typeLF = XFILETXTTYPELF_DEFAULT;` (0A on this LINUX
  // build) rather than leaving it at XFILETXTTYPELF_UNKNOWN. XFILETXT::ReadNLines()'s own
  // auto-detection only ever overwrites `typeLF` when it finds it still XFILETXTTYPELF_UNKNOWN
  // ("if(typeLF == XFILETXTTYPELF_UNKNOWN && ...) typeLF = _typeLF;"), so through the normal,
  // documented Open()-then-ReadAllFile() API sequence that auto-detection branch can never fire:
  // GetTypeLF() always reports the platform default after reopening a file, even when the file's
  // actual on-disk line endings are something else entirely (0D here, deliberately written with
  // plain libc I/O so this is independent of XFILETXT's own write path).
  XPATH xpath(__L("/tmp/xutils_unittests_xfiletxt_lfbug.txt"));
  RemoveIfExists(xpath);

  {
    XFILE* xfile = GEN_XFACTORY.Create_File();
    ASSERT_NE(xfile, (XFILE*)NULL);
    ASSERT_TRUE(xfile->Create(xpath));

    const char content[] = "first\rsecond\r";
    xfile->Write((XBYTE*)content, (XDWORD)(sizeof(content) - 1));
    xfile->Close();

    GEN_XFACTORY.Delete_File(xfile);
  }

  XFILETXT reader;
  ASSERT_TRUE(reader.Open(xpath, true));
  EXPECT_TRUE(reader.ReadNLines());

  // The lines themselves still split correctly (GetSizeOfLine() scans real bytes per-line,
  // independent of the `typeLF` member) ...
  ASSERT_EQ(reader.GetNLines(), 2);
  EXPECT_STREQ(reader.GetLineText(0), __L("first"));
  EXPECT_STREQ(reader.GetLineText(1), __L("second"));

  // ... but GetTypeLF() incorrectly reports the platform default (0A) rather than the file's real
  // 0D line endings -- the bug.
  EXPECT_EQ(reader.GetTypeLF(), XFILETXTTYPELF_0A);

  reader.Close();
  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILETXT_CLASSNAME, CreateTypeLFHasTypoForCombinedLineEndings)
{
  // Real, concrete XUtils bug (not fixed, per the hard rule): XFILETXT::CreateTypeLF()
  // (XFileTXT.cpp, the XFILETXTFORMATCHAR_ASCII/XFILETXTFORMATCHAR_UTF8 branch, case
  // XFILETXTTYPELF_0A0D) writes LF[0] = 0xA0 instead of the evidently-intended 0x0A -- a single
  // transposed-digit typo. This is confirmed directly here rather than through a full file
  // round trip (a full round trip would just silently show 2 "lines" instead of 1, which is a
  // less concrete way to pin down the exact bug than reading the raw bytes CreateTypeLF() itself
  // produces).
  XFILETXT dummy;
  XBYTE    LF[4]  = { 0,0,0,0 };
  XDWORD   sizeLF = 0;

  EXPECT_TRUE(dummy.CreateTypeLF(XFILETXTFORMATCHAR_ASCII, XFILETXTTYPELF_0A0D, LF, sizeLF));

  ASSERT_EQ(sizeLF, (XDWORD)2);
  EXPECT_EQ(LF[0], (XBYTE)0xA0); // bug: should be 0x0A to spell out a real CR-then-LF-like pair
  EXPECT_EQ(LF[1], (XBYTE)0x0D);
}


TEST(UNITTEST_XFILETXT_CLASSNAME, GetLineUsesUnboundedFastGetInsteadOfBoundsCheckedGet)
{
  // Real, concrete XUtils bug (not fixed, per the hard rule, and deliberately NOT exercised with
  // an actual out-of-range call here -- doing so is genuine undefined behavior, not a safe
  // NULL-returning query, so executing it would risk a nondeterministic crash of this whole test
  // binary rather than demonstrating anything reliably). XFILETXT::GetLine(int index)
  // (XFileTXT.cpp) reads: `return lines.FastGet(index);` -- XVECTOR<T>::FastGet() (XVector.h) is
  // documented by its own name and implementation as the UNCHECKED accessor
  // (`return array[index];`, no bounds test at all), unlike XVECTOR<T>::Get(), which safely
  // returns a default/NULL for an out-of-range index. The source even shows this was a
  // deliberate, later change: GetLine()'s own commented-out prior implementation
  // ("//if(index<0) return NULL; //if(index>=(int)lines.GetSize()) return NULL; ... //XSTRING*
  // string = (XSTRING*)lines.Get(index); ... //return string;") explicitly used the safe,
  // bounds-checked XVECTOR::Get() and was replaced with the unchecked FastGet() call that ships
  // today. As a direct, observable consequence confirmed once during this batch's own
  // development (not repeated here to keep this test binary's behavior deterministic): calling
  // GetLine() with an index at or beyond GetNLines() does NOT reliably return NULL -- it can
  // return an arbitrary, non-NULL garbage pointer instead, which GetLineText() would then
  // dereference.
  XFILETXT filetxt;
  filetxt.AddLine(__L("only line"));

  ASSERT_EQ(filetxt.GetNLines(), 1);
  EXPECT_STREQ(filetxt.GetLineText(0), __L("only line"));
}


TEST(UNITTEST_XFILETXT_CLASSNAME, InsertLineAndDeleteLine)
{
  XFILETXT filetxt;

  filetxt.AddLine(__L("alpha"));
  filetxt.AddLine(__L("gamma"));

  ASSERT_EQ(filetxt.GetNLines(), 2);

  EXPECT_TRUE(filetxt.InsertLine(1, __L("beta")));
  ASSERT_EQ(filetxt.GetNLines(), 3);

  EXPECT_STREQ(filetxt.GetLineText(0), __L("alpha"));
  EXPECT_STREQ(filetxt.GetLineText(1), __L("beta"));
  EXPECT_STREQ(filetxt.GetLineText(2), __L("gamma"));

  EXPECT_TRUE(filetxt.DeleteLine(1));
  ASSERT_EQ(filetxt.GetNLines(), 2);

  EXPECT_STREQ(filetxt.GetLineText(0), __L("alpha"));
  EXPECT_STREQ(filetxt.GetLineText(1), __L("gamma"));

  // Deleting with a negative index must fail cleanly, not crash.
  EXPECT_FALSE(filetxt.DeleteLine(-1));

  EXPECT_TRUE(filetxt.DeleteAllLines());
  EXPECT_EQ(filetxt.GetNLines(), 0);

  // Nothing left to delete -- must report failure, not crash.
  EXPECT_FALSE(filetxt.DeleteAllLines());
}


TEST(UNITTEST_XFILETXT_CLASSNAME, GetAllInOneLineAndGetAllInBufferPartialRange)
{
  // Each check below uses its OWN freshly-populated XFILETXT -- see the dedicated
  // GetAllInOneLineMutatesStoredLinesAsASideEffect test for why reusing one instance across
  // repeated GetAllInOneLine()/GetAllInBuffer() calls would give misleading results here.
  {
    XFILETXT filetxt;
    filetxt.AddLine(__L("one"));
    filetxt.AddLine(__L("two"));
    filetxt.AddLine(__L("three"));

    XSTRING alllines;
    EXPECT_TRUE(filetxt.GetAllInOneLine(alllines, XFILETXTTYPELF_0A));
    EXPECT_FALSE(alllines.Compare(__L("one\ntwo\nthree\n"), false));
  }

  {
    XFILETXT filetxt;
    filetxt.AddLine(__L("one"));
    filetxt.AddLine(__L("two"));
    filetxt.AddLine(__L("three"));

    XSTRING partial;
    EXPECT_TRUE(filetxt.GetAllInOneLine(partial, XFILETXTTYPELF_0A, 1, 2));
    EXPECT_FALSE(partial.Compare(__L("two\n"), false));
  }

  {
    XFILETXT filetxt;
    filetxt.AddLine(__L("one"));
    filetxt.AddLine(__L("two"));

    XBUFFER allbuffer;
    EXPECT_TRUE(filetxt.GetAllInBuffer(allbuffer, XFILETXTTYPELF_UNKNOWN));
    EXPECT_TRUE(allbuffer.GetSize() > 0);
  }
}


TEST(UNITTEST_XFILETXT_CLASSNAME, GetAllInOneLineMutatesStoredLinesAsASideEffect)
{
  // Real, concrete XUtils bug (not fixed, per the hard rule): XFILETXT::GetAllInOneLine()
  // (XFileTXT.cpp) fetches each stored line via `XSTRING* line = GetLine(c);` -- a pointer into
  // the LIVE `lines` vector, not a copy -- and then calls `line->Add(LF.Get())` directly on it.
  // This means every call to GetAllInOneLine() permanently appends the line-ending characters
  // onto the actual stored lines, so calling it a second time appends a SECOND copy of the line
  // ending on top of the first, rather than leaving the stored lines untouched (as a "get" method
  // should).
  XFILETXT filetxt;
  filetxt.AddLine(__L("repeatable"));

  XSTRING firstcall;
  EXPECT_TRUE(filetxt.GetAllInOneLine(firstcall, XFILETXTTYPELF_0A));
  EXPECT_FALSE(firstcall.Compare(__L("repeatable\n"), false));

  // The stored line itself now already carries the appended "\n" -- proof of the mutation.
  EXPECT_FALSE(filetxt.GetLine(0)->Compare(__L("repeatable\n"), false));

  XSTRING secondcall;
  EXPECT_TRUE(filetxt.GetAllInOneLine(secondcall, XFILETXTTYPELF_0A));

  // The bug in action: the second call's result carries the line ending TWICE, not once.
  EXPECT_FALSE(secondcall.Compare(__L("repeatable\n\n"), false));
}


TEST(UNITTEST_XFILETXT_CLASSNAME, CopyToDuplicatesLinesAndFormat)
{
  XFILETXT source;
  source.SetFormatChar(XFILETXTFORMATCHAR_UTF8);
  source.SetTypeLF(XFILETXTTYPELF_0D0A);
  source.AddLine(__L("copied line"));

  XFILETXT destination;
  EXPECT_TRUE(source.CopyTo(&destination));

  EXPECT_EQ(destination.GetFormatChar(), XFILETXTFORMATCHAR_UTF8);
  EXPECT_EQ(destination.GetTypeLF(), XFILETXTTYPELF_0D0A);
  ASSERT_EQ(destination.GetNLines(), 1);
  EXPECT_STREQ(destination.GetLineText(0), __L("copied line"));
}


TEST(UNITTEST_XFILETXT_CLASSNAME, CopyFromIsBrokenAndNeverTouchesTheCaller)
{
  // Real, concrete XUtils bug (not fixed, per the hard rule): XFILETXT::CopyFrom(XFILETXT* filetxt)
  // (XFileTXT.cpp) is implemented as `return filetxt->CopyTo(filetxt);` -- it calls CopyTo() on the
  // ARGUMENT, copying that argument's content into ITSELF (a harmless no-op), instead of the
  // evidently-intended `return filetxt->CopyTo(this);` which would copy the argument's content into
  // the object CopyFrom() was called on. As a direct result, calling `this->CopyFrom(other)` never
  // changes `this` at all -- `this`'s own lines/format are left completely untouched.
  XFILETXT destination;
  destination.AddLine(__L("original untouched line"));
  destination.SetFormatChar(XFILETXTFORMATCHAR_ASCII);

  XFILETXT source;
  source.AddLine(__L("source line that should have been copied"));
  source.SetFormatChar(XFILETXTFORMATCHAR_UTF8);

  EXPECT_TRUE(destination.CopyFrom(&source));

  // The bug: destination is completely unchanged -- still has its OWN original line/format, not
  // source's.
  ASSERT_EQ(destination.GetNLines(), 1);
  EXPECT_STREQ(destination.GetLineText(0), __L("original untouched line"));
  EXPECT_EQ(destination.GetFormatChar(), XFILETXTFORMATCHAR_ASCII);
}


TEST(UNITTEST_XFILETXT_CLASSNAME, IsBinaryFileDetectsNonTextContent)
{
  XPATH xpath(__L("/tmp/xutils_unittests_xfiletxt_binary.bin"));
  RemoveIfExists(xpath);

  {
    XFILE* xfile = GEN_XFACTORY.Create_File();
    ASSERT_NE(xfile, (XFILE*)NULL);

    ASSERT_TRUE(xfile->Create(xpath));

    XBYTE binarydata[32];
    for(int c = 0; c < 32; c++) binarydata[c] = (XBYTE)(c < 16 ? c : 0); // lots of low control bytes

    xfile->Write(binarydata, sizeof(binarydata));
    xfile->Close();

    GEN_XFACTORY.Delete_File(xfile);
  }

  {
    // XFILETXT::Open() itself rejects binary content when the detected format looks like
    // ASCII/UTF8 (XFileTXT.cpp: "if(IsBinaryFile()) return false;"), so Open() must fail here.
    XFILETXT reader;
    EXPECT_FALSE(reader.Open(xpath, true));
  }

  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILETXT_CLASSNAME, PublicDataMembersAreDirectlyMutable)
{
  // Documents a real, concrete house-convention break flagged by the analysis report:
  // XFILETXT declares `formatchar`/`typeLF`/`LF`/`lines` directly under `public:` (XFileTXT.h
  // lines 148-151), unlike the private-data-plus-accessor pattern used everywhere else in this
  // module -- so external code (including this very test) can mutate the live `lines` vector
  // directly, bypassing AddLine()/DeleteLine() entirely.
  XFILETXT filetxt;

  filetxt.AddLine(__L("via AddLine"));
  EXPECT_EQ(filetxt.GetNLines(), 1);

  XSTRING* direct = GEN_NEW XSTRING(__L("added by poking the public member directly"));
  filetxt.lines.Add(direct);

  EXPECT_EQ(filetxt.GetNLines(), 2);
  EXPECT_STREQ(filetxt.GetLineText(1), __L("added by poking the public member directly"));

  filetxt.formatchar = XFILETXTFORMATCHAR_UTF16_LE;
  EXPECT_EQ(filetxt.GetFormatChar(), XFILETXTFORMATCHAR_UTF16_LE);
}


}
#endif
