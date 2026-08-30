/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XBER.cpp
*
* @class      XUTILS_UNITTESTS_XBER
* @brief      XUtils unit tests for XBER class
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

#include "XUtils_UnitTests_XBER.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XBER.h"
#include "XBuffer.h"
#include "XString.h"
#include "XVariant.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XBER
{

TEST(UNITTEST_XBER_CLASSNAME, SetIntegerAndGetDumpProducesKnownWireBytes)
{
  // Reference encoding: ASN.1/BER INTEGER 5 is the well-known byte sequence 02 01 05
  // (tag=INTEGER, length=1, value=5) -- a wire-format regression check, not just self-consistency.
  XBER    ber;
  XBUFFER dump;

  EXPECT_TRUE(ber.SetINTEGER((XDWORD)5));
  EXPECT_TRUE(ber.GetDump(dump));

  ASSERT_EQ(dump.GetSize(), (XDWORD)3);
  EXPECT_EQ(dump.GetByte(0), 0x02);
  EXPECT_EQ(dump.GetByte(1), 0x01);
  EXPECT_EQ(dump.GetByte(2), 0x05);
}


TEST(UNITTEST_XBER_CLASSNAME, SetIntegerZeroProducesKnownWireBytes)
{
  XBER    ber;
  XBUFFER dump;

  EXPECT_TRUE(ber.SetINTEGER((XDWORD)0));
  EXPECT_TRUE(ber.GetDump(dump));

  ASSERT_EQ(dump.GetSize(), (XDWORD)3);
  EXPECT_EQ(dump.GetByte(0), 0x02);
  EXPECT_EQ(dump.GetByte(1), 0x01);
  EXPECT_EQ(dump.GetByte(2), 0x00);
}


TEST(UNITTEST_XBER_CLASSNAME, SetOctetStringAndGetDumpProducesKnownWireBytes)
{
  // OCTET STRING "AB" -> tag=04, length=2, ASCII bytes 0x41 0x42.
  XBER    ber;
  XBUFFER dump;

  EXPECT_TRUE(ber.SetOCTETSTRING((XCHAR*)__L("AB")));
  EXPECT_TRUE(ber.GetDump(dump));

  ASSERT_EQ(dump.GetSize(), (XDWORD)4);
  EXPECT_EQ(dump.GetByte(0), 0x04);
  EXPECT_EQ(dump.GetByte(1), 0x02);
  EXPECT_EQ(dump.GetByte(2), 0x41);
  EXPECT_EQ(dump.GetByte(3), 0x42);
}


TEST(UNITTEST_XBER_CLASSNAME, SetNullProducesKnownWireBytes)
{
  XBER    ber;
  XBUFFER dump;

  EXPECT_TRUE(ber.SetNULL());
  EXPECT_TRUE(ber.GetDump(dump));

  ASSERT_EQ(dump.GetSize(), (XDWORD)2);
  EXPECT_EQ(dump.GetByte(0), 0x05);
  EXPECT_EQ(dump.GetByte(1), 0x00);
}


TEST(UNITTEST_XBER_CLASSNAME, GetTagTypeNameKnownTypes)
{
  XBER    ber;
  XSTRING name;

  ber.SetINTEGER((XDWORD)1);
  EXPECT_TRUE(ber.GetTagTypeName(name));
  EXPECT_STREQ(name.Get(), __L("INTEGER"));

  ber.SetOCTETSTRING((XCHAR*)__L("X"));
  EXPECT_TRUE(ber.GetTagTypeName(name));
  EXPECT_STREQ(name.Get(), __L("OCTET STRING"));
}


TEST(UNITTEST_XBER_CLASSNAME, IsConstructedDefaultsToFalse)
{
  XBER ber;

  EXPECT_FALSE(ber.IsConstructed());
}


TEST(UNITTEST_XBER_CLASSNAME, RoundTripIntegerEncodeThenDecode)
{
  XBER    encoder;
  XBUFFER dump;

  encoder.SetINTEGER((XDWORD)42);
  encoder.GetDump(dump);

  XBER decoder;

  EXPECT_TRUE(decoder.SetFromDump(dump));

  EXPECT_EQ(decoder.GetTagType(), (XBYTE)XBER_TAGTYPE_INTEGER);
  EXPECT_EQ(decoder.GetSize(), (XDWORD)1);

  XSTRING valuestring;

  decoder.GetValue()->ToString(valuestring);
  EXPECT_STREQ(valuestring.Get(), __L("42"));
}


TEST(UNITTEST_XBER_CLASSNAME, RoundTripOctetStringDecodesToHexEncodedValue)
{
  // Source note: XBER::ConvertToOctetString() (XBER.cpp) always stringifies the OCTET STRING
  // payload as its hex representation, not as readable text -- so decoding OCTET STRING "AB"
  // yields the XVARIANT string "4142" (hex of 0x41,0x42), not "AB". Documented behaviour, not a
  // bug, but easy to assume otherwise.
  XBER    encoder;
  XBUFFER dump;

  encoder.SetOCTETSTRING((XCHAR*)__L("AB"));
  encoder.GetDump(dump);

  XBER decoder;

  EXPECT_TRUE(decoder.SetFromDump(dump));

  EXPECT_EQ(decoder.GetTagType(), (XBYTE)XBER_TAGTYPE_OCTET_STRING);

  XSTRING valuestring;

  decoder.GetValue()->ToString(valuestring);
  EXPECT_STREQ(valuestring.Get(), __L("4142"));
}


TEST(UNITTEST_XBER_CLASSNAME, WellFormedConstructedSequenceDecodesIntoOneChild)
{
  // Hand-built, spec-correct BER: SEQUENCE (tag 0x30 = universal | constructed) containing one
  // INTEGER 5 (02 01 05) -- confirms SetFromDump() really does recurse into children when the
  // constructed bit is set on the wire.
  XBUFFER dump;

  dump.Add((XBYTE)0x30); // SEQUENCE, constructed
  dump.Add((XBYTE)0x03); // length = 3
  dump.Add((XBYTE)0x02); // INTEGER
  dump.Add((XBYTE)0x01); // length = 1
  dump.Add((XBYTE)0x05); // value = 5

  XBER decoder;

  EXPECT_TRUE(decoder.SetFromDump(dump));

  EXPECT_EQ(decoder.GetTagType(), (XBYTE)XBER_TAGTYPE_SEQUENCE);
  EXPECT_TRUE(decoder.IsConstructed());

  ASSERT_NE((void*)decoder.Sequence_GetSequences(), (void*)NULL);
  EXPECT_EQ(decoder.Sequence_GetSequences()->GetSize(), (XDWORD)1);

  XBER* child = decoder.Sequence_GetSequences()->Get(0);

  ASSERT_NE((void*)child, (void*)NULL);
  EXPECT_EQ(child->GetTagType(), (XBYTE)XBER_TAGTYPE_INTEGER);
}


TEST(UNITTEST_XBER_CLASSNAME, SequenceAddToBuildsSequenceWithCorrectSize)
{
  XBER child;
  XBER parent;

  child.SetINTEGER((XDWORD)5);

  EXPECT_TRUE(parent.Sequence_AddTo(child));

  EXPECT_EQ(parent.GetTagType(), (XBYTE)XBER_TAGTYPE_SEQUENCE);
  EXPECT_EQ(parent.Sequence_GetSequences()->GetSize(), (XDWORD)1);
  EXPECT_EQ(parent.Sequence_GetSize(), (XDWORD)5); // 1(tag)+1(len)+3(child's own tag+len+value)
}


TEST(UNITTEST_XBER_CLASSNAME, SequenceAddToThenGetDumpLosesConstructedBitOnDecodeRoundTrip)
{
  // Real, not-fixed XUtils gap: XBER::Sequence_AddTo() (XBER.cpp) sets tagtype=SEQUENCE but never
  // sets the 'isconstructed' member, and XBER::GetDump() writes the raw 'tagtype' byte with no
  // class/constructed bits OR'd in (XBER.cpp) -- so a SEQUENCE built purely through the public
  // Set*/Sequence_AddTo API and then dumped produces a tag byte of 0x10 (plain universal SEQUENCE)
  // instead of the correct 0x30 (constructed). Decoding that dump back through SetFromDump() then
  // reads the constructed bit as unset, so the child element is never reparsed into a sub-XBER --
  // it is silently swallowed as opaque, unparsed 'data' bytes on the decoded object, and
  // Sequence_GetSequences() comes back EMPTY even though the original had one child.
  XBER child;
  XBER parent;

  child.SetINTEGER((XDWORD)5);
  parent.Sequence_AddTo(child);

  XBUFFER dump;
  parent.GetDump(dump);

  EXPECT_EQ(dump.GetByte(0), 0x10); // NOT 0x30 -- the constructed bit is missing on the wire

  XBER decoder;

  EXPECT_TRUE(decoder.SetFromDump(dump));

  EXPECT_EQ(decoder.GetTagType(), (XBYTE)XBER_TAGTYPE_SEQUENCE);
  EXPECT_FALSE(decoder.IsConstructed());
  EXPECT_EQ(decoder.Sequence_GetSequences()->GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XBER_CLASSNAME, TwoInstancesShareTheSameStaticLevelTrackingStorage)
{
  // Source concern (analysis report): 'level'/'levels[]'/'totalposition' (XBER.h) are declared
  // static, i.e. per-CLASS, not per-instance -- GetLevels() on two entirely independent XBER
  // objects returns the exact same underlying array. SetFromDump() does reset this shared state
  // at the start of every top-level call, which covers the common case, but any reentrant decode
  // (e.g. an observer callback that itself triggers another XBER::SetFromDump() while the first
  // decode is still in progress) would silently corrupt the outer decode's bookkeeping, since
  // there is only one shared copy of this state for the whole process.
  XBER berA;
  XBER berB;

  EXPECT_EQ((void*)berA.GetLevels(), (void*)berB.GetLevels());
}


}
#endif
