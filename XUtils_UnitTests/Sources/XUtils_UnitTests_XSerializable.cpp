/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XSerializable.cpp
*
* @class      XUTILS_UNITTESTS_XSERIALIZABLE
* @brief      XUtils unit tests for XSerializable class
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

#include "XUtils_UnitTests_XSerializable.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XSerializable.h"
#include "XSerializationMethodJSON.h"
#include "XFileJSON.h"
#include "XVector.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XSERIALIZABLE
{

// Minimal test-local XSERIALIZABLE subclasses used to exercise the real Serialize/Deserialize
// contract. The real usage pattern (confirmed against GEN/DataIO/Nodes/DIONodeItemValue.cpp,
// a real "public XSERIALIZABLE" subclass) is: Serialize() calls Primitive_Add<T>(value, name)
// with T taken BY VALUE (a raw pointer for XSTRING*/XBUFFER*/XVARIANT* fields), while
// Deserialize() calls Primitive_Extract<T>(value, name) with T taken BY REFERENCE (a plain
// value type, not a pointer, even for XSTRING/XVARIANT) -- these forward onto the attached
// XSERIALIZATIONMETHOD's own asymmetric Add(T)/Extract(T&) interface.

class TESTSERIALIZABLENESTED : public XSERIALIZABLE
{
  public:
    TESTSERIALIZABLENESTED() : innervalue(0) {}
    virtual ~TESTSERIALIZABLENESTED() {}

    int  GetInnerValue()      { return innervalue; }
    void SetInnerValue(int v) { innervalue = v; }

    virtual bool Serialize()
    {
      Primitive_Add<int>(innervalue, __L("innervalue"));
      return true;
    }

    virtual bool Deserialize()
    {
      Primitive_Extract<int>(innervalue, __L("innervalue"));
      return true;
    }

  private:
    int innervalue;
};


class TESTSERIALIZABLEWIDGET : public XSERIALIZABLE
{
  public:
    TESTSERIALIZABLEWIDGET() : counter(0) {}
    virtual ~TESTSERIALIZABLEWIDGET() {}

    int      GetCounter()        { return counter; }
    void     SetCounter(int c)   { counter = c;     }

    XSTRING& GetLabel()          { return label; }
    void     SetLabel(XCHAR* l)  { label = l;     }

    TESTSERIALIZABLENESTED& GetNested() { return nested; }

    virtual bool Serialize()
    {
      Primitive_Add<int>(counter, __L("counter"));
      Primitive_Add<XSTRING*>(&label, __L("label"));
      Class_Add<TESTSERIALIZABLENESTED>(&nested, __L("nested"));
      return true;
    }

    virtual bool Deserialize()
    {
      Primitive_Extract<int>(counter, __L("counter"));
      Primitive_Extract<XSTRING>(label, __L("label"));
      Class_Extract<TESTSERIALIZABLENESTED>(&nested, __L("nested"));
      return true;
    }

  private:
    int                    counter;
    XSTRING                label;
    TESTSERIALIZABLENESTED nested;
};


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, ConstructorDefaultsToNoMethodAndNotChanged)
{
  TESTSERIALIZABLEWIDGET widget;

  EXPECT_EQ((void*)NULL, (void*)widget.GetSerializationMethod());
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, SetGetSerializationMethodRoundTrips)
{
  TESTSERIALIZABLEWIDGET widget;

  XFILEJSON              filejson;
  XSERIALIZATIONMETHOD*  method = XSERIALIZABLE::CreateInstance(filejson);
  ASSERT_TRUE(method != NULL);

  widget.SetSerializationMethod(method);
  EXPECT_EQ((void*)method, (void*)widget.GetSerializationMethod());

  GEN_DELETE method;
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, DoSerializeWithoutMethodFails)
{
  TESTSERIALIZABLEWIDGET widget;

  EXPECT_FALSE(widget.DoSerialize());
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, DoDeserializeWithoutMethodFails)
{
  TESTSERIALIZABLEWIDGET widget;

  EXPECT_FALSE(widget.DoDeserialize());
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, DoSerializeWithExplicitNullMethodFails)
{
  TESTSERIALIZABLEWIDGET widget;

  EXPECT_FALSE(widget.DoSerialize(NULL));
  EXPECT_FALSE(widget.DoDeserialize(NULL));
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, JSONRoundTripPreservesPrimitiveAndNestedFields)
{
  XFILEJSON              filejson;
  XSERIALIZATIONMETHOD*  method = XSERIALIZABLE::CreateInstance(filejson);
  ASSERT_TRUE(method != NULL);

  TESTSERIALIZABLEWIDGET source;
  source.SetCounter(42);
  source.SetLabel(__L("hello"));
  source.GetNested().SetInnerValue(7);

  EXPECT_TRUE(source.DoSerialize(method));

  TESTSERIALIZABLEWIDGET destination;
  EXPECT_TRUE(destination.DoDeserialize(method));

  EXPECT_EQ(destination.GetCounter(), 42);
  EXPECT_EQ(destination.GetLabel().Compare(__L("hello")), 0);
  EXPECT_EQ(destination.GetNested().GetInnerValue(), 7);

  GEN_DELETE method;
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, HasBeenChangedIsTrueOnFirstCallWithEmptyCache)
{
  TESTSERIALIZABLEWIDGET widget;
  widget.SetCounter(1);
  widget.SetLabel(__L("a"));

  // HasBeenChanged() lazily builds its own internal XFILEJSON-backed serialization method
  // (XSERIALIZABLE::CreateInstance(XFILEJSON&)) and compares the freshly encoded content
  // against a cached buffer that starts empty -- so the first call always reports "changed".
  EXPECT_TRUE(widget.HasBeenChanged());
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, HasBeenChangedIsFalseWhenContentMatchesCacheAfterFlagReset)
{
  TESTSERIALIZABLEWIDGET widget;
  widget.SetCounter(1);
  widget.SetLabel(__L("a"));

  EXPECT_TRUE(widget.HasBeenChanged());   // primes the internal cache
  widget.SetHasBeenChanged(false);        // force HasBeenChanged() to recompute instead of
                                          // short-circuiting on the already-true flag
  EXPECT_FALSE(widget.HasBeenChanged());  // same fields -> same encoded content -> unchanged
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, HasBeenChangedIsTrueAfterFieldMutationAndFlagReset)
{
  TESTSERIALIZABLEWIDGET widget;
  widget.SetCounter(1);

  EXPECT_TRUE(widget.HasBeenChanged());
  widget.SetHasBeenChanged(false);

  widget.SetCounter(2);
  EXPECT_TRUE(widget.HasBeenChanged());
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, HasBeenChangedStaysTrueWithoutExplicitFlagResetEvenIfCalledAgain)
{
  TESTSERIALIZABLEWIDGET widget;
  widget.SetCounter(1);

  EXPECT_TRUE(widget.HasBeenChanged());
  // HasBeenChanged() only recomputes when its internal "hasbeenchanged" flag is currently
  // false (XSerializable.cpp: "if(!hasbeenchanged) {...}"), so a second call without an
  // explicit SetHasBeenChanged(false) in between short-circuits and reports "changed" again,
  // even though nothing was actually modified.
  EXPECT_TRUE(widget.HasBeenChanged());
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, SetHasBeenChangedRoundTripsTheRawFlag)
{
  TESTSERIALIZABLEWIDGET widget;

  widget.SetHasBeenChanged(true);
  EXPECT_TRUE(widget.HasBeenChanged());

  widget.SetHasBeenChanged(false);
  // Recomputes now (cache still empty from never having been primed) -> real content differs
  // from the empty cache -> reports changed.
  EXPECT_TRUE(widget.HasBeenChanged());
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, XVectorAddAcceptsAnEmptyVector)
{
  // FIXED (previously a known bug, now confirmed corrected in XSerializable.h): XVector_Add<T>
  // used to unconditionally call var->Get(0) to type-check the element type via dynamic_cast
  // *before* checking whether the vector was empty. XVECTOR<T*>::Get() on an out-of-range index
  // (including index 0 on an empty vector) safely returns a default-constructed T(), i.e. NULL
  // for a pointer element type, so dynamic_cast<XSERIALIZABLE*>(NULL) was NULL/falsy and
  // XVector_Add unconditionally treated an empty vector as "not serializable", returning false
  // without ever calling AddArray() -- even though serializing zero elements is a perfectly
  // sensible case. The condition is now `var->GetSize() && !dynamic_cast<...>(var->Get(0))`,
  // short-circuiting on GetSize()==0 before Get(0) is ever called, so an empty vector correctly
  // proceeds to AddArray(0, name, ...) and reports success.
  XFILEJSON              filejson;
  XSERIALIZATIONMETHOD*  method = XSERIALIZABLE::CreateInstance(filejson);
  ASSERT_TRUE(method != NULL);

  TESTSERIALIZABLEWIDGET container;
  container.SetSerializationMethod(method);

  XVECTOR<TESTSERIALIZABLENESTED*> emptyvector;

  EXPECT_TRUE(container.XVector_Add<TESTSERIALIZABLENESTED>(&emptyvector, __L("items")));

  GEN_DELETE method;
}


TEST(UNITTEST_XSERIALIZABLE_CLASSNAME, XVectorAddBoxesElementsSoXVectorExtractReadsThemBack)
{
  XFILEJSON              filejson;
  XSERIALIZATIONMETHOD*  method = XSERIALIZABLE::CreateInstance(filejson);
  ASSERT_TRUE(method != NULL);

  TESTSERIALIZABLEWIDGET container;
  container.SetSerializationMethod(method);

  XVECTOR<TESTSERIALIZABLENESTED*> sourcevector;

  TESTSERIALIZABLENESTED* item0 = GEN_NEW TESTSERIALIZABLENESTED();
  TESTSERIALIZABLENESTED* item1 = GEN_NEW TESTSERIALIZABLENESTED();
  ASSERT_TRUE(item0 != NULL);
  ASSERT_TRUE(item1 != NULL);
  item0->SetInnerValue(10);
  item1->SetInnerValue(20);
  sourcevector.Add(item0);
  sourcevector.Add(item1);

  // FIXED (previously a known bug, now confirmed corrected in XSerializable.h): XVector_Add<T>
  // used to call AddArray(...,true) once and then call element->Serialize() directly for every
  // element -- unlike XVectorClass_Add, it never wrapped each element in its own AddStruct(...)
  // boundary. With the JSON backend this meant every element's fields landed as FLAT, repeated,
  // same-named primitive values directly under the single shared array node, not as separate
  // per-element JSON objects, so the later ExtractArrayElement(...,true) calls (which require
  // each array element to be a JSON object) always failed and the round trip silently did
  // nothing. XVector_Add now wraps each element's Serialize() call in its own
  // AddStruct(NULL, true)/AddStruct(NULL, false) pair, exactly like XVectorClass_Add, so each
  // element becomes its own JSON object and the round trip genuinely works.
  EXPECT_TRUE(container.XVector_Add<TESTSERIALIZABLENESTED>(&sourcevector, __L("items")));

  XVECTOR<TESTSERIALIZABLENESTED*> destvector;

  TESTSERIALIZABLENESTED* dest0 = GEN_NEW TESTSERIALIZABLENESTED();
  TESTSERIALIZABLENESTED* dest1 = GEN_NEW TESTSERIALIZABLENESTED();
  ASSERT_TRUE(dest0 != NULL);
  ASSERT_TRUE(dest1 != NULL);
  dest0->SetInnerValue(-1);
  dest1->SetInnerValue(-1);
  destvector.Add(dest0);
  destvector.Add(dest1);

  // With XVector_Add now producing one real JSON object per element, ExtractArrayElement(index,
  // name, true) (which requires XFILEJSONVALUETYPE_OBJECT) finds what it expects, so
  // Deserialize() genuinely runs for each destination element and the round trip now works.
  EXPECT_TRUE(container.XVector_Extract<TESTSERIALIZABLENESTED>(&destvector, __L("items")));

  EXPECT_EQ(dest0->GetInnerValue(), 10);
  EXPECT_EQ(dest1->GetInnerValue(), 20);

  GEN_DELETE item0;
  GEN_DELETE item1;
  GEN_DELETE dest0;
  GEN_DELETE dest1;
  GEN_DELETE method;
}


}
#endif
