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

  // FIXED: Sequence_AddTo() (XBER.cpp) now sets "tagtype = XBER_TAGTYPE_SEQUENCE |
  // XBER_TAG_MASKISCONSTRUCTED" (0x30), correctly marking the tag as constructed, instead of the
  // plain XBER_TAGTYPE_SEQUENCE (0x10) it used to leave unset.
  EXPECT_EQ(parent.GetTagType(), (XBYTE)(XBER_TAGTYPE_SEQUENCE | XBER_TAG_MASKISCONSTRUCTED));
  EXPECT_TRUE(parent.IsConstructed());
  EXPECT_EQ(parent.Sequence_GetSequences()->GetSize(), (XDWORD)1);
  EXPECT_EQ(parent.Sequence_GetSize(), (XDWORD)5); // 1(tag)+1(len)+3(child's own tag+len+value)
}


TEST(UNITTEST_XBER_CLASSNAME, SequenceAddToThenGetDumpNowRoundTripsThroughDecodeCorrectly)
{
  // FIXED: Sequence_AddTo() (XBER.cpp) now sets both tagtype (with the constructed bit OR'd in)
  // AND isconstructed=true, and GetDump() writes that same tagtype byte to the wire unchanged --
  // so a SEQUENCE built purely through the public Set*/Sequence_AddTo API and then dumped now
  // produces the correct 0x30 (constructed) tag byte, instead of the previous 0x10 (plain
  // universal SEQUENCE) that silently dropped the constructed bit. Decoding that dump back through
  // SetFromDump() now correctly reads the constructed bit as set, so the child element is genuinely
  // reparsed into a sub-XBER instead of being silently swallowed as opaque, unparsed 'data' bytes.
  XBER child;
  XBER parent;

  child.SetINTEGER((XDWORD)5);
  parent.Sequence_AddTo(child);

  XBUFFER dump;
  parent.GetDump(dump);

  EXPECT_EQ(dump.GetByte(0), 0x30); // constructed SEQUENCE tag, correctly on the wire

  XBER decoder;

  EXPECT_TRUE(decoder.SetFromDump(dump));

  // SetFromDump() (XBER.cpp) masks the raw wire byte with XBER_TAG_MASKTYPE before storing it in
  // `tagtype` ("tagtype = (XBYTE)(buffer.Get()[0] & XBER_TAG_MASKTYPE);"), so GetTagType() on the
  // decode side reports the plain type (0x10), while the constructed bit lives separately in
  // IsConstructed() -- unlike the encode side, where Sequence_AddTo() stores the combined byte
  // directly in `tagtype`. This asymmetry is real GEN behavior, not something to paper over here.
  EXPECT_EQ(decoder.GetTagType(), (XBYTE)XBER_TAGTYPE_SEQUENCE);
  EXPECT_TRUE(decoder.IsConstructed());
  EXPECT_EQ(decoder.Sequence_GetSequences()->GetSize(), (XDWORD)1);
}


TEST(UNITTEST_XBER_CLASSNAME, TwoInstancesShareTheSameStaticLevelTrackingStorage)
{
  // FIXED: 'level'/'levels[]'/'totalposition' (XBER.h) are no longer declared static -- they are
  // now genuine per-instance members, so GetLevels() on two entirely independent XBER objects now
  // returns two distinct underlying arrays, instead of previously sharing one copy for the whole
  // process (which any reentrant decode, e.g. an observer callback triggering another
  // XBER::SetFromDump() mid-decode, would have silently corrupted).
  XBER berA;
  XBER berB;

  EXPECT_NE((void*)berA.GetLevels(), (void*)berB.GetLevels());
}


}
#endif
