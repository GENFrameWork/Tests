/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XSerializationMethodJSON.cpp
*
* @class      XUTILS_UNITTESTS_XSERIALIZATIONMETHODJSON
* @brief      XUtils unit tests for XSerializationMethodJSON class
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

#include "XUtils_UnitTests_XSerializationMethodJSON.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XSerializationMethodJSON.h"
#include "XSerializable.h"
#include "XFileJSON.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XSERIALIZATIONMETHODJSON
{

// Test-local XSERIALIZABLE subclass used to exercise the real, polymorphic Add/Extract path
// exactly as XSERIALIZABLE-derived production classes use it (see
// GEN/DataIO/Nodes/DIONodeItemValue.cpp for the real pattern this mirrors).
class TESTJSONWIDGET : public XSERIALIZABLE
{
  public:
    TESTJSONWIDGET() : counter(0) {}
    virtual ~TESTJSONWIDGET() {}

    int      GetCounter()          { return counter; }
    void     SetCounter(int c)     { counter = c;     }

    XSTRING& GetLabel()            { return label; }
    void     SetLabel(XCHAR* l)    { label = l;     }

    virtual bool Serialize()
    {
      Primitive_Add<int>(counter, __L("counter"));
      Primitive_Add<XSTRING*>(&label, __L("label"));
      return true;
    }

    virtual bool Deserialize()
    {
      Primitive_Extract<int>(counter, __L("counter"));
      Primitive_Extract<XSTRING>(label, __L("label"));
      return true;
    }

  private:
    int     counter;
    XSTRING label;
};


TEST(UNITTEST_XSERIALIZATIONMETHODJSON_CLASSNAME, ConstructorDefaultsFileJSONAndActualObjectToNull)
{
  XSERIALIZATIONMETHODJSON method;

  EXPECT_EQ((void*)NULL, (void*)method.GetFileJSON());
  EXPECT_EQ((void*)NULL, (void*)method.GetActualObject());
}


TEST(UNITTEST_XSERIALIZATIONMETHODJSON_CLASSNAME, SetGetFileJSONAndActualObjectRoundTrip)
{
  XSERIALIZATIONMETHODJSON method;
  XFILEJSON                filejson;
  XFILEJSONOBJECT          object;

  method.SetFileJSON(&filejson);
  method.SetActualObject(&object);

  EXPECT_EQ((void*)&filejson, (void*)method.GetFileJSON());
  EXPECT_EQ((void*)&object,   (void*)method.GetActualObject());
}


TEST(UNITTEST_XSERIALIZATIONMETHODJSON_CLASSNAME, AddScalarsFailWithoutFileJSONOrActualObjectSet)
{
  XSERIALIZATIONMETHODJSON method;

  EXPECT_FALSE(method.Add((int)1, __L("x")));
  EXPECT_FALSE(method.Add(true,   __L("x")));
}


TEST(UNITTEST_XSERIALIZATIONMETHODJSON_CLASSNAME, CreateInstanceBuildsARootObjectAndAddIntStoresARealJSONValue)
{
  XFILEJSON              filejson;
  XSERIALIZATIONMETHOD*  basemethod = XSERIALIZABLE::CreateInstance(filejson);
  ASSERT_TRUE(basemethod != NULL);

  ASSERT_TRUE(filejson.GetRoot() != NULL);

  EXPECT_TRUE(basemethod->Add((int)42, __L("counter")));

  XFILEJSONVALUE* stored = filejson.GetValue(__L("counter"));
  ASSERT_TRUE(stored != NULL);
  EXPECT_EQ(stored->GetValueInteger(), 42);

  GEN_DELETE basemethod;
}


TEST(UNITTEST_XSERIALIZATIONMETHODJSON_CLASSNAME, AddStringAndAddBoolStoreRealJSONValues)
{
  XFILEJSON              filejson;
  XSERIALIZATIONMETHOD*  basemethod = XSERIALIZABLE::CreateInstance(filejson);
  ASSERT_TRUE(basemethod != NULL);

  XSTRING text;
  text = __L("hello");

  EXPECT_TRUE(basemethod->Add(&text, __L("label")));
  EXPECT_TRUE(basemethod->Add(true,  __L("flag")));

  XFILEJSONVALUE* storedlabel = filejson.GetValue(__L("label"));
  ASSERT_TRUE(storedlabel != NULL);
  XSTRING storedstring = storedlabel->GetValueString();
  EXPECT_EQ(storedstring.Compare(__L("hello")), 0);

  XFILEJSONVALUE* storedflag = filejson.GetValue(__L("flag"));
  ASSERT_TRUE(storedflag != NULL);
  EXPECT_TRUE(storedflag->GetValueBoolean());

  GEN_DELETE basemethod;
}


TEST(UNITTEST_XSERIALIZATIONMETHODJSON_CLASSNAME, AddBufferIsANoOpThatWritesNoJSONValue)
{
  XFILEJSON              filejson;
  XSERIALIZATIONMETHOD*  basemethod = XSERIALIZABLE::CreateInstance(filejson);
  ASSERT_TRUE(basemethod != NULL);

  XBUFFER payload;
  payload.Add((XBYTE)0xAA);

  // XSerializationMethodJSON.cpp's Add(XBUFFER*, ...) has its one line of real work commented
  // out ("//XFILEJSON_ADDVALUE(...)") and its body is otherwise just "return true;" -- so a
  // XBUFFER field serialized through this backend is silently dropped, same class of gap as
  // XSERIALIZATIONMETHODBINARY's own Add(XBUFFER*, ...). Documented, not fixed.
  EXPECT_TRUE(basemethod->Add(&payload, __L("payload")));
  EXPECT_EQ((void*)NULL, (void*)filejson.GetValue(__L("payload")));

  GEN_DELETE basemethod;
}


TEST(UNITTEST_XSERIALIZATIONMETHODJSON_CLASSNAME, MissingAddLongOverloadSilentlyFallsBackToInertBaseStubThroughPolymorphicDispatch)
{
  XFILEJSON              filejson;
  XSERIALIZATIONMETHOD*  basemethod = XSERIALIZABLE::CreateInstance(filejson);
  ASSERT_TRUE(basemethod != NULL);

  long longvalue = 123;

  // XSerializationMethodJSON.h declares Add(long long,...) but, unlike the base class and
  // XSERIALIZATIONMETHODBINARY (both of which declare BOTH Add(long,...) and
  // Add(long long,...)), it has no Add(long,...) override at all. Calling Add(long,...)
  // directly on a concretely-typed XSERIALIZATIONMETHODJSON* is not merely "falls back to a
  // different overload" -- on this platform (64-bit Linux, sizeof(long)==sizeof(long long)) it
  // is genuinely AMBIGUOUS at compile time between int/float/double/long long/XBYTE/XWORD/
  // XDWORD/XQWORD, confirmed with a standalone probe. Through the polymorphic
  // XSERIALIZATIONMETHOD* interface XSERIALIZABLE actually drives (Primitive_Add<T>() calls
  // serializationmethod->Add(var, name) where serializationmethod is statically typed as
  // XSERIALIZATIONMETHOD*), the call resolves at compile time against the BASE class's own
  // Add(long,...) declaration -- and since XSERIALIZATIONMETHODJSON never overrides that
  // particular vtable slot, virtual dispatch silently invokes the inert BASE STUB (always
  // returns false, never touches fileJSON) instead of any JSON-specific behavior. A long-typed
  // field serialized through XSERIALIZABLE with the JSON backend is therefore silently dropped.
  EXPECT_FALSE(basemethod->Add(longvalue, __L("longfield")));
  EXPECT_EQ((void*)NULL, (void*)filejson.GetValue(__L("longfield")));

  GEN_DELETE basemethod;
}


TEST(UNITTEST_XSERIALIZATIONMETHODJSON_CLASSNAME, AddStructDefaultsToOpenTrueUnlikeBaseAndBinaryBackends)
{
  XFILEJSON                 filejson;
  XSERIALIZATIONMETHOD*     basemethod = XSERIALIZABLE::CreateInstance(filejson);
  ASSERT_TRUE(basemethod != NULL);

  XSERIALIZATIONMETHODJSON* method = (XSERIALIZATIONMETHODJSON*)basemethod;

  XFILEJSONOBJECT* before = method->GetActualObject();
  ASSERT_TRUE(before != NULL);

  // Calling AddStruct with only the `name` argument relies on XSERIALIZATIONMETHODJSON's own
  // default open=true (XSerializationMethodJSON.h: AddStruct(XCHAR* name=NULL, bool open=true))
  // -- unlike the base class and XSERIALIZATIONMETHODBINARY, which both default `open` to false
  // for the very same method signature. Code that omits `open` gets a silently different result
  // depending on which concrete backend it is actually talking to.
  EXPECT_TRUE(method->AddStruct(__L("nested")));

  XFILEJSONOBJECT* after = method->GetActualObject();
  EXPECT_NE((void*)before, (void*)after);   // a brand-new struct node was opened, not closed

  GEN_DELETE basemethod;
}


TEST(UNITTEST_XSERIALIZATIONMETHODJSON_CLASSNAME, PolymorphicRoundTripThroughXSerializableReconstructsTheOriginalValues)
{
  XFILEJSON              filejson;
  XSERIALIZATIONMETHOD*  method = XSERIALIZABLE::CreateInstance(filejson);
  ASSERT_TRUE(method != NULL);

  TESTJSONWIDGET source;
  source.SetCounter(42);
  source.SetLabel(__L("hello"));

  // Unlike XSERIALIZATIONMETHODBINARY, XSERIALIZATIONMETHODJSON's Extract() overloads are
  // correctly declared BY REFERENCE (matching the base class exactly), so this really does
  // override the base's virtual slot -- the round trip through the intended, polymorphic
  // XSERIALIZABLE API actually works for the JSON backend.
  EXPECT_TRUE(source.DoSerialize(method));

  TESTJSONWIDGET destination;
  EXPECT_TRUE(destination.DoDeserialize(method));

  EXPECT_EQ(destination.GetCounter(), 42);
  EXPECT_EQ(destination.GetLabel().Compare(__L("hello")), 0);

  GEN_DELETE method;
}


TEST(UNITTEST_XSERIALIZATIONMETHODJSON_CLASSNAME, EncodedJSONTextContainsTheSerializedFieldNamesAndValues)
{
  XFILEJSON              filejson;
  XSERIALIZATIONMETHOD*  method = XSERIALIZABLE::CreateInstance(filejson);
  ASSERT_TRUE(method != NULL);

  TESTJSONWIDGET source;
  source.SetCounter(42);
  source.SetLabel(__L("hello"));

  EXPECT_TRUE(source.DoSerialize(method));

  ASSERT_TRUE(filejson.EncodeAllLines());

  XSTRING alltext;
  ASSERT_TRUE(filejson.GetAllInOneLine(alltext));

  // A sane-looking JSON encoding: quoted field names, the quoted string value, and the plain
  // (unquoted) integer value all present in the produced text.
  EXPECT_GE(alltext.Find(__L("\"counter\""), false), 0);
  EXPECT_GE(alltext.Find(__L("\"label\""),   false), 0);
  EXPECT_GE(alltext.Find(__L("\"hello\""),   false), 0);
  EXPECT_GE(alltext.Find(__L("42"),          false), 0);

  GEN_DELETE method;
}


}
#endif
