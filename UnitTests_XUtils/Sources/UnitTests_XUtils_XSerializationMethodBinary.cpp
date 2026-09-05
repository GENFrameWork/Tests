/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XSerializationMethodBinary.cpp
*
* @class      UNITTESTS_XUTILS_XSERIALIZATIONMETHODBINARY
* @brief      XUtils unit tests for XSerializationMethodBinary class
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

#include "UnitTests_XUtils_XSerializationMethodBinary.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XSerializationMethodBinary.h"
#include "XSerializable.h"
#include "XBuffer.h"
#include "XString.h"
#include "XVariant.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XSERIALIZATIONMETHODBINARY
{

// Test-local XSERIALIZABLE subclass used to exercise the real, polymorphic Add/Extract path
// exactly as XSERIALIZABLE-derived production classes use it (see
// GEN/DataIO/Nodes/DIONodeItemValue.cpp for the real pattern this mirrors).
class TESTBINARYWIDGET : public XSERIALIZABLE
{
  public:
    TESTBINARYWIDGET() : value(0) {}
    virtual ~TESTBINARYWIDGET() {}

    int      GetValue()          { return value; }
    void     SetValue(int v)     { value = v;    }

    XSTRING& GetLabel()          { return label; }
    void     SetLabel(XCHAR* l)  { label = l;    }

    virtual bool Serialize()
    {
      Primitive_Add<int>(value, __L("value"));
      Primitive_Add<XSTRING*>(&label, __L("label"));
      return true;
    }

    virtual bool Deserialize()
    {
      Primitive_Extract<int>(value, __L("value"));
      Primitive_Extract<XSTRING>(label, __L("label"));
      return true;
    }

  private:
    int     value;
    XSTRING label;
};


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, ConstructorDefaultsBufferDataToNull)
{
  XSERIALIZATIONMETHODBINARY method;

  EXPECT_EQ((void*)NULL, (void*)method.GetBufferData());
}


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, SetGetBufferDataRoundTrips)
{
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;

  method.SetBufferData(&buffer);
  EXPECT_EQ((void*)&buffer, (void*)method.GetBufferData());
}


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddScalarsFailWithoutBufferDataSet)
{
  XSERIALIZATIONMETHODBINARY method;

  EXPECT_FALSE(method.Add(true,        __L("x")));
  EXPECT_FALSE(method.Add((int)1,      __L("x")));
  EXPECT_FALSE(method.Add((XDWORD)1,   __L("x")));
}


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddIntWritesTypeTagByteThenFourValueBytes)
{
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  EXPECT_TRUE(method.Add((int)0x11223344, __L("value")));

  ASSERT_EQ(buffer.GetSize(), 1u + 4u);
  EXPECT_EQ(buffer.GetByte(0), (XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_INTEGER);

  XDWORD decoded = 0;
  ASSERT_TRUE(buffer.Get(decoded, 1));
  EXPECT_EQ(decoded, (XDWORD)0x11223344);
}


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddBoolWritesTypeTagByteThenOneValueByte)
{
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  EXPECT_TRUE(method.Add(true, __L("flag")));

  ASSERT_EQ(buffer.GetSize(), 1u + 1u);
  EXPECT_EQ(buffer.GetByte(0), (XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_BOOLEAN);
  EXPECT_NE(buffer.GetByte(1), (XBYTE)0);
}


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddStringWritesTypeTagAndUTF8Payload)
{
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  XSTRING text;
  text = __L("hi");

  EXPECT_TRUE(method.Add(&text, __L("label")));

  ASSERT_GT(buffer.GetSize(), 1u);
  EXPECT_EQ(buffer.GetByte(0), (XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_XSTRING);
}


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddStructIsAValidityCheckOnlyAndAddArrayWritesExpectedMarkerBytes)
{
  // CHANGED (confirmed in the current XSerializationMethodBinary.cpp): AddStruct() no longer
  // writes a STRUCT_ID marker to the buffer at all -- it is now purely a "do we have somewhere
  // to write to" validity check (`if(!bufferdata) return false; return true;`), writing zero
  // bytes either way. This is consistent with the format's actual needs: every field written
  // inside a struct already carries its own type tag via Add(...), so no separate struct
  // boundary marker is required for a binary reader to know where one ends -- only AddArray()
  // still needs to record an explicit element count up front, which it continues to do.
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  EXPECT_TRUE(method.AddStruct(__L("s"), true));
  EXPECT_EQ(buffer.GetSize(), 0u);

  buffer.Empty();

  EXPECT_TRUE(method.AddArray(5, __L("a"), true));
  ASSERT_EQ(buffer.GetSize(), 2u + 4u);   // ARRAY_ID (XWORD) + nelements (XDWORD)
  XWORD arrayid = 0;
  ASSERT_TRUE(buffer.Get(arrayid, 0));
  EXPECT_EQ(arrayid, (XWORD)XSERIALIZATIONMETHOD_ARRAY_ID);

  XDWORD nelements = 0;
  ASSERT_TRUE(buffer.Get(nelements, 2));
  EXPECT_EQ(nelements, (XDWORD)5);
}


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddThenExtractVariantRoundTripsTypeAndValue)
{
  // FIXED (previously a known bug, now confirmed corrected): Add(XVARIANT*, ...) used to have a
  // body that was literally "return true;" -- it never wrote a type tag, never wrote the
  // variant's value, and did not even check bufferdata/var for NULL, so any XVARIANT field was
  // silently dropped. It now writes a real type tag, the XVARIANT_TYPE, a UTF-8-encoded string
  // payload size and the payload itself, and the paired Extract(XVARIANT&, ...) reads all of
  // that back and reconstructs the value via FromString() -- a real, working round trip.
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  XVARIANT variant;
  variant = (int)123;

  EXPECT_TRUE(method.Add(&variant, __L("v")));
  EXPECT_GT(buffer.GetSize(), 0u);
  EXPECT_EQ(buffer.GetByte(0), (XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_XVARIANT);

  XVARIANT readback;
  EXPECT_TRUE(method.Extract(readback, __L("v")));
  EXPECT_EQ(readback.GetType(), XVARIANT_TYPE_INTEGER);
  EXPECT_EQ((int)readback, 123);
}


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddThenExtractBufferRoundTripsTheActualContent)
{
  // FIXED (previously a known bug, now confirmed corrected): Add(XBUFFER*, ...) used to write
  // only the XBYTE type-tag and never touch var's actual bytes, silently losing the payload's
  // content (and it did not NULL-check its own `bufferdata` member either). It now writes a
  // type tag, the payload's size, and the payload bytes themselves via the shared
  // XSERIALIZATIONMETHODBINARY_AddData() helper, and the paired Extract(XBUFFER&, ...) reads
  // all of it back byte-for-byte.
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  XBYTE  payloadbytes[4] = { 0xAA, 0xBB, 0xCC, 0xDD };
  XBUFFER payload;
  payload.Add(payloadbytes, 4);

  EXPECT_TRUE(method.Add(&payload, __L("payload")));

  ASSERT_GT(buffer.GetSize(), 1u);
  EXPECT_EQ(buffer.GetByte(0), (XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_XBUFFER);

  XBUFFER readback;
  EXPECT_TRUE(method.Extract(readback, __L("payload")));
  ASSERT_EQ(readback.GetSize(), (XDWORD)4);
  EXPECT_EQ(readback.GetByte(0), (XBYTE)0xAA);
  EXPECT_EQ(readback.GetByte(1), (XBYTE)0xBB);
  EXPECT_EQ(readback.GetByte(2), (XBYTE)0xCC);
  EXPECT_EQ(readback.GetByte(3), (XBYTE)0xDD);
}


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, DirectExtractGenuinelyReadsBackThePreviouslyWrittenValue)
{
  // FIXED (previously a known bug, now confirmed corrected): XSERIALIZATIONMETHODBINARY::Extract()
  // used to take its scalar argument BY VALUE -- a real signature mismatch vs. the base class's
  // by-reference Extract(int&, ...) -- and its own .cpp body was simply "return true;", never
  // even reading bufferdata, so a write-back to the caller was categorically impossible. The
  // header now declares every Extract() overload by reference (matching the base class exactly,
  // a real override rather than a hiding declaration), and the .cpp body genuinely reads the
  // type tag and value bytes back from the buffer at the tracked read cursor.
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  method.Add((int)999, __L("value"));

  int readback = 12345;
  EXPECT_TRUE(method.Extract(readback, __L("value")));
  EXPECT_EQ(readback, 999);
}


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, ExtractArrayNowValidatesAgainstRealBufferContentButExtractStructRemainsANoOp)
{
  // CHANGED (confirmed in the current XSerializationMethodBinary.cpp): ExtractArray() is no
  // longer an unconditional "return true;" stub -- it now genuinely reads back the ARRAY_ID
  // marker and stored element count that AddArray() writes, and fails if either the marker is
  // missing/wrong or the stored count does not match the count the caller asked for (including
  // when there is no buffer at all to read from). ExtractStruct() remains an unconditional
  // "return true;" -- but that is now consistent, not buggy, since the paired AddStruct() also
  // writes nothing for a reader to skip over.
  XSERIALIZATIONMETHODBINARY method;

  // No buffer set at all: ExtractStruct() still trivially succeeds (nothing to read)...
  EXPECT_TRUE(method.ExtractStruct(__L("s")));
  // ... but ExtractArray() now correctly fails, since there is no ARRAY_ID marker to read.
  EXPECT_FALSE(method.ExtractArray(3, __L("a")));

  XBUFFER buffer;
  method.SetBufferData(&buffer);

  EXPECT_TRUE(method.AddArray(3, __L("a"), true));
  EXPECT_TRUE(method.ExtractArray(3, __L("a")));   // real marker + matching count: succeeds

  buffer.Empty();
  EXPECT_TRUE(method.AddArray(3, __L("a"), true));
  EXPECT_FALSE(method.ExtractArray(5, __L("a")));  // real marker but a mismatched count: fails
}


TEST(UNITTESTS_XSERIALIZATIONMETHODBINARY_CLASSNAME, PolymorphicRoundTripThroughXSerializableNowReconstructsTheOriginalValues)
{
  // FIXED (previously a known bug, now confirmed corrected): XSERIALIZABLE::Primitive_Extract<T>
  // (T& var, name) calls serializationmethod->Extract(var, name) where `serializationmethod` is
  // statically typed as XSERIALIZATIONMETHOD* -- this used to resolve to the BASE class's inert
  // Extract(T&, XCHAR*) stub, because XSERIALIZATIONMETHODBINARY's own Extract(T, XCHAR*)
  // overload took its argument by value (a different signature that HID rather than overrode
  // the base virtual). Now that every XSERIALIZATIONMETHODBINARY::Extract() overload takes its
  // argument by reference -- a real override -- virtual dispatch correctly reaches the derived
  // class's genuine, working implementation, and binary deserialization through the intended,
  // polymorphic XSERIALIZABLE API is fully functional.
  XBUFFER                     databuffer;
  XSERIALIZATIONMETHODBINARY  method;
  method.SetBufferData(&databuffer);

  TESTBINARYWIDGET source;
  source.SetValue(42);
  source.SetLabel(__L("hello"));

  EXPECT_TRUE(source.DoSerialize(&method));
  // Real bytes were actually produced: a working, well-formed write path.
  EXPECT_GT(databuffer.GetSize(), 0u);

  TESTBINARYWIDGET destination;
  EXPECT_EQ(destination.GetValue(), 0);   // fresh/default state before deserializing

  EXPECT_TRUE(destination.DoDeserialize(&method));
  EXPECT_EQ(destination.GetValue(), 42);
  EXPECT_STREQ(destination.GetLabel().Get(), __L("hello"));
}


}
#endif
