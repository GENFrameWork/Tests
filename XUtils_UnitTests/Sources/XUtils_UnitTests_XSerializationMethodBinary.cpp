/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XSerializationMethodBinary.cpp
*
* @class      XUTILS_UNITTESTS_XSERIALIZATIONMETHODBINARY
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

#include "XUtils_UnitTests_XSerializationMethodBinary.h"

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


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, ConstructorDefaultsBufferDataToNull)
{
  XSERIALIZATIONMETHODBINARY method;

  EXPECT_EQ((void*)NULL, (void*)method.GetBufferData());
}


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, SetGetBufferDataRoundTrips)
{
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;

  method.SetBufferData(&buffer);
  EXPECT_EQ((void*)&buffer, (void*)method.GetBufferData());
}


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddScalarsFailWithoutBufferDataSet)
{
  XSERIALIZATIONMETHODBINARY method;

  EXPECT_FALSE(method.Add(true,        __L("x")));
  EXPECT_FALSE(method.Add((int)1,      __L("x")));
  EXPECT_FALSE(method.Add((XDWORD)1,   __L("x")));
}


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddIntWritesTypeTagByteThenFourValueBytes)
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


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddBoolWritesTypeTagByteThenOneValueByte)
{
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  EXPECT_TRUE(method.Add(true, __L("flag")));

  ASSERT_EQ(buffer.GetSize(), 1u + 1u);
  EXPECT_EQ(buffer.GetByte(0), (XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_BOOLEAN);
  EXPECT_NE(buffer.GetByte(1), (XBYTE)0);
}


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddStringWritesTypeTagAndUTF8Payload)
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


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddStructAndAddArrayWriteExpectedMarkerBytes)
{
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  EXPECT_TRUE(method.AddStruct(__L("s"), true));
  ASSERT_EQ(buffer.GetSize(), 2u);   // STRUCT_ID written as an XWORD (2 bytes)
  XWORD structid = 0;
  ASSERT_TRUE(buffer.Get(structid, 0));
  EXPECT_EQ(structid, (XWORD)XSERIALIZATIONMETHOD_STRUCT_ID);

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


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddVariantIsANoOpThatWritesNothingToTheBuffer)
{
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  XVARIANT variant;
  variant = (int)123;

  // XSerializationMethodBinary.cpp's Add(XVARIANT*, ...) body is literally "return true;" --
  // it never writes a type tag, never writes the variant's value, and does not even check
  // bufferdata/var for NULL. Any XVARIANT field serialized through this backend is silently
  // dropped. Documented, not fixed.
  EXPECT_TRUE(method.Add(&variant, __L("v")));
  EXPECT_EQ(buffer.GetSize(), 0u);
}


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, AddBufferOnlyWritesATypeTagAndLosesTheActualContent)
{
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  XBYTE  payloadbytes[4] = { 0xAA, 0xBB, 0xCC, 0xDD };
  XBUFFER payload;
  payload.Add(payloadbytes, 4);

  // XSerializationMethodBinary.cpp's Add(XBUFFER*, ...) writes only the XBYTE type-tag and
  // never touches var's actual bytes -- the payload's content is silently lost. (Note also:
  // unlike every other Add() overload here, this one does not NULL-check its own `bufferdata`
  // member before dereferencing it -- calling this without a prior SetBufferData() would
  // crash; not exercised here to avoid crashing the whole test binary.)
  EXPECT_TRUE(method.Add(&payload, __L("payload")));

  ASSERT_EQ(buffer.GetSize(), 1u);
  EXPECT_EQ(buffer.GetByte(0), (XBYTE)XSERIALIZATIONMETHODBINARY_TYPEELEMENT_XBUFFER);
}


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, DirectExtractCallsAlwaysReturnTrueWithoutTouchingTheOutputArgument)
{
  XSERIALIZATIONMETHODBINARY method;
  XBUFFER                    buffer;
  method.SetBufferData(&buffer);

  method.Add((int)999, __L("value"));   // real bytes really are in the buffer now

  // XSERIALIZATIONMETHODBINARY::Extract() takes its scalar argument BY VALUE (a real, verifiable
  // signature bug vs. the base class's by-reference Extract(int&,...) -- see
  // XSerializationMethodBinary.h lines 98-113), and Extract(int,...)'s own .cpp body is simply
  // "return true;" -- it never even reads bufferdata. So calling it directly (bypassing the
  // by-value/by-reference hiding problem entirely, since we're calling it on the concrete type)
  // still cannot possibly write back to the caller: only a local copy is ever modified.
  int readback = 12345;
  EXPECT_TRUE(method.Extract(readback, __L("value")));
  EXPECT_EQ(readback, 12345);   // unchanged -- 999 was never read back
}


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, ExtractStructAndExtractArrayAlwaysReturnTrueRegardlessOfBufferContent)
{
  XSERIALIZATIONMETHODBINARY method;

  // No buffer set at all, yet these still report success -- ExtractStruct()/ExtractArray()'s
  // bodies are unconditional "return true;" stubs with no cursor/position tracking of any kind.
  EXPECT_TRUE(method.ExtractStruct(__L("s")));
  EXPECT_TRUE(method.ExtractArray(3, __L("a")));
}


TEST(UNITTEST_XSERIALIZATIONMETHODBINARY_CLASSNAME, PolymorphicRoundTripThroughXSerializableNeverReconstructsTheOriginalValues)
{
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

  // XSERIALIZABLE::Primitive_Extract<T>(T& var, name) calls
  // serializationmethod->Extract(var, name) where `serializationmethod` is statically typed as
  // XSERIALIZATIONMETHOD* (XSerializable.h line 79) -- so this resolves to the BASE class's
  // Extract(T&, XCHAR*) overload (an inert stub, see XUtils_UnitTests_XSerializationMethod.cpp),
  // never XSERIALIZATIONMETHODBINARY's own Extract(T, XCHAR*) overload at all, because a `T&`
  // parameter and a `T` parameter are different signatures and the derived class's version
  // HIDES rather than OVERRIDES the base virtual. Combined with the by-value-only bug confirmed
  // above (which would prevent a write-back even if it *were* reached), the net effect is that
  // binary deserialization through the intended, polymorphic XSERIALIZABLE API is completely
  // non-functional: the destination object keeps its untouched default field values even though
  // the buffer genuinely contains the correct serialized bytes. This is the single highest-impact
  // finding for this module -- captured here as real, current behavior, not fixed.
  EXPECT_TRUE(destination.DoDeserialize(&method));
  EXPECT_EQ(destination.GetValue(), 0);
  EXPECT_TRUE(destination.GetLabel().IsEmpty());
}


}
#endif
