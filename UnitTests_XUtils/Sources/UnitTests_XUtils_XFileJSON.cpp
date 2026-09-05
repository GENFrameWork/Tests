/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XFileJSON.cpp
*
* @class      UNITTESTS_XUTILS_XFILEJSON
* @brief      XUtils unit tests for XFILEJSON class
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

#include "UnitTests_XUtils_XFileJSON.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XFileJSON.h"
#include "XString.h"
#include "XVariant.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFILEJSON
{


TEST(UNITTESTS_XFILEJSON_CLASSNAME, ValueSetGetScalarTypesRoundTrip)
{
  XFILEJSONVALUE value;

  value.Set(true);
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_BOOLEAN);
  EXPECT_TRUE(value.GetValueBoolean());

  value.Set((short)-7);
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_SHORT);
  EXPECT_EQ(value.GetValueShort(), -7);

  value.Set((XWORD)12345);
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_WORD);
  EXPECT_EQ(value.GetValueWord(), (XWORD)12345);

  value.Set((int)-123456);
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_INTEGER);
  EXPECT_EQ(value.GetValueInteger(), -123456);

  value.Set((XDWORD)0xCAFEBABE);
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_DWORD);
  EXPECT_EQ(value.GetValueDWord(), (XDWORD)0xCAFEBABE);

  value.Set((long long)-9000000000LL);
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_DOUBLEINTEGER);
  EXPECT_EQ(value.GetValueDoubleInteger(), -9000000000LL);

  value.Set((XQWORD)18000000000ULL);
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_QWORD);
  EXPECT_EQ(value.GetValueQWord(), (XQWORD)18000000000ULL);

  value.Set((float)3.5f);
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_FLOAT);
  EXPECT_FLOAT_EQ(value.GetValueFloating(), 3.5f);

  value.Set((double)12.25);
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_DOUBLEFLOAT);
  EXPECT_DOUBLE_EQ(value.GetValueDoubleFloat(), 12.25);

  value.Set(__L("hello"));
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_STRING);
  XSTRING str = value.GetValueString();
  EXPECT_FALSE(str.Compare(__L("hello"), false));

  // FIXED: XFILEJSONVALUE::Set(void) (XFileJSON.cpp) now does "type = XFILEJSONVALUETYPE_NULL;"
  // alongside setting the internal XVARIANT to XVARIANT_TYPE_NULL -- previously it never updated
  // `type`, so GetType() kept reporting whatever type was set last (STRING here) even though the
  // stored value itself had been cleared to NULL underneath.
  value.Set();
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_NULL);
}


TEST(UNITTESTS_XFILEJSON_CLASSNAME, ValueSetObjectAndArrayPointerRoundTrip)
{
  XFILEJSONVALUE     value;
  XFILEJSONOBJECT*   object = GEN_NEW XFILEJSONOBJECT();
  XFILEJSONARRAY*    array  = GEN_NEW XFILEJSONARRAY();

  ASSERT_TRUE(value.Set(object));
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_OBJECT);
  EXPECT_EQ(value.GetValueObject(), object);

  ASSERT_TRUE(value.Set(array));
  EXPECT_EQ(value.GetType(), XFILEJSONVALUETYPE_ARRAY);
  EXPECT_EQ(value.GetValueArray(), array);

  // Set(NULL object/array) must fail gracefully rather than crash.
  EXPECT_FALSE(value.Set((XFILEJSONOBJECT*)NULL));
  EXPECT_FALSE(value.Set((XFILEJSONARRAY*)NULL));

  // value now owns "array" (last successful Set()); its destructor will delete it. "object" was
  // never adopted by the final state, so it must be freed here to avoid a leak.
  GEN_DELETE object;
}


TEST(UNITTESTS_XFILEJSON_CLASSNAME, ObjectAddGetValuesAndDeleteAllValues)
{
  XFILEJSONOBJECT object;

  EXPECT_FALSE(object.IsArray());
  EXPECT_FALSE(object.DeleteAllValues()); // nothing to delete yet

  XFILEJSONVALUE* v1 = GEN_NEW XFILEJSONVALUE();
  v1->SetName(__L("one"));
  v1->Set((int)1);

  XFILEJSONVALUE* v2 = GEN_NEW XFILEJSONVALUE();
  v2->SetName(__L("two"));
  v2->Set((int)2);

  ASSERT_TRUE(object.Add(v1));
  ASSERT_TRUE(object.Add(v2));
  EXPECT_FALSE(object.Add(NULL));

  ASSERT_TRUE(object.GetValues() != NULL);
  ASSERT_EQ(object.GetValues()->GetSize(), (XDWORD)2);
  EXPECT_EQ(object.GetValues()->Get(0), v1);
  EXPECT_EQ(object.GetValues()->Get(1), v2);

  EXPECT_TRUE(object.DeleteAllValues());
  EXPECT_EQ(object.GetValues()->GetSize(), (XDWORD)0);
}


TEST(UNITTESTS_XFILEJSON_CLASSNAME, DecodeAllLinesParsesFlatObjectWithEveryScalarType)
{
  XFILEJSON filejson;

  filejson.AddLine(__L("{\"nullv\":null,\"boolv\":true,\"intv\":42,\"negv\":-7,"));
  filejson.AddLine(__L("\"floatv\":3.5,\"strv\":\"hello\"}"));

  ASSERT_TRUE(filejson.DecodeAllLines());

  XFILEJSONOBJECT* root = filejson.GetRoot();
  ASSERT_TRUE(root != NULL);
  ASSERT_FALSE(root->IsArray());

  XFILEJSONVALUE* nullv = filejson.GetValue(__L("nullv"));
  ASSERT_TRUE(nullv != NULL);
  EXPECT_EQ(nullv->GetType(), XFILEJSONVALUETYPE_NULL);

  XFILEJSONVALUE* boolv = filejson.GetValue(__L("boolv"));
  ASSERT_TRUE(boolv != NULL);
  EXPECT_EQ(boolv->GetType(), XFILEJSONVALUETYPE_BOOLEAN);
  EXPECT_TRUE(boolv->GetValueBoolean());

  XFILEJSONVALUE* intv = filejson.GetValue(__L("intv"));
  ASSERT_TRUE(intv != NULL);
  EXPECT_EQ(intv->GetValueInteger(), 42);

  XFILEJSONVALUE* negv = filejson.GetValue(__L("negv"));
  ASSERT_TRUE(negv != NULL);
  EXPECT_EQ(negv->GetValueInteger(), -7);

  XFILEJSONVALUE* floatv = filejson.GetValue(__L("floatv"));
  ASSERT_TRUE(floatv != NULL);
  EXPECT_EQ(floatv->GetType(), XFILEJSONVALUETYPE_DOUBLEFLOAT);
  EXPECT_DOUBLE_EQ(floatv->GetValueDoubleFloat(), 3.5);

  XFILEJSONVALUE* strv = filejson.GetValue(__L("strv"));
  ASSERT_TRUE(strv != NULL);
  XSTRING strvalue = strv->GetValueString();
  EXPECT_FALSE(strvalue.Compare(__L("hello"), false));

  filejson.DeleteAllObjects();
  filejson.DeleteAllLines();
}


TEST(UNITTESTS_XFILEJSON_CLASSNAME, DecodeAllLinesParsesNestedObjectAndArray)
{
  XFILEJSON filejson;

  filejson.AddLine(__L("{\"outer\":{\"inner\":5},\"arr\":[1,2,3]}"));

  ASSERT_TRUE(filejson.DecodeAllLines());

  XFILEJSONOBJECT* outerobj = filejson.GetObj(__L("outer"));
  ASSERT_TRUE(outerobj != NULL);

  XFILEJSONVALUE* innerval = filejson.GetValue(__L("inner"), outerobj);
  ASSERT_TRUE(innerval != NULL);
  EXPECT_EQ(innerval->GetValueInteger(), 5);

  // NOTE (real XUtils behavior): XFILEJSON::GetValue(name) can only ever find a *scalar*-typed
  // named value -- when it walks into an OBJECT/ARRAY-typed value it recurses looking for `name`
  // among that sub-container's own children, without ever comparing `name` against the
  // OBJECT/ARRAY value's own name first. So an OBJECT/ARRAY-typed value can never be retrieved
  // through GetValue(), only through GetObj() (whose GetObjSubValue() helper does check the
  // value's own name before recursing). Fetch the array that way instead.
  XFILEJSONOBJECT* arrobj = filejson.GetObj(__L("arr"));
  ASSERT_TRUE(arrobj != NULL);
  ASSERT_TRUE(arrobj->IsArray());

  XFILEJSONARRAY* array = (XFILEJSONARRAY*)arrobj;
  ASSERT_TRUE(array != NULL);
  ASSERT_TRUE(array->GetValues() != NULL);
  ASSERT_EQ(array->GetValues()->GetSize(), (XDWORD)3);
  EXPECT_EQ(array->GetValues()->Get(0)->GetValueInteger(), 1);
  EXPECT_EQ(array->GetValues()->Get(1)->GetValueInteger(), 2);
  EXPECT_EQ(array->GetValues()->Get(2)->GetValueInteger(), 3);

  filejson.DeleteAllObjects();
  filejson.DeleteAllLines();
}


TEST(UNITTESTS_XFILEJSON_CLASSNAME, GetObjFindsNestedObjectByNameAndReturnsNullWhenMissing)
{
  XFILEJSON filejson;

  filejson.AddLine(__L("{\"a\":{\"b\":{\"c\":9}}}"));
  ASSERT_TRUE(filejson.DecodeAllLines());

  XFILEJSONOBJECT* cobj = filejson.GetObj(__L("c"));
  // "c" is a scalar value, not an OBJECT/ARRAY -- GetObj() only ever returns OBJECT/ARRAY typed
  // sub-values, so searching for a plain-scalar name must come back NULL.
  EXPECT_TRUE(cobj == (XFILEJSONOBJECT*)NULL);

  XFILEJSONOBJECT* bobj = filejson.GetObj(__L("b"));
  ASSERT_TRUE(bobj != NULL);

  XFILEJSONVALUE* cval = filejson.GetValue(__L("c"), bobj);
  ASSERT_TRUE(cval != NULL);
  EXPECT_EQ(cval->GetValueInteger(), 9);

  EXPECT_TRUE(filejson.GetObj(__L("nosuch")) == (XFILEJSONOBJECT*)NULL);
  EXPECT_TRUE(filejson.GetValue(__L("nosuch")) == (XFILEJSONVALUE*)NULL);

  filejson.DeleteAllObjects();
  filejson.DeleteAllLines();
}


TEST(UNITTESTS_XFILEJSON_CLASSNAME, DecodeRejectsUnterminatedValueStringButAcceptsBadTrailingComma)
{
  // Unterminated name string: GetString() runs off the end of the buffer and returns false, and
  // DecodeObject() DOES check that return value for the name-string case, so this is correctly
  // rejected.
  {
    XFILEJSON filejson;
    filejson.AddLine(__L("{\"unterminated : 1}"));
    EXPECT_FALSE(filejson.DecodeAllLines());
    filejson.DeleteAllLines();
  }

  // Mismatched braces/brackets ('{' opened, ']' used to close it) are correctly rejected: once the
  // decoder is back at the isobject-scoped closing check it finds neither the expected CLOSEBRACE
  // nor a plain comma, so it fails.
  {
    XFILEJSON filejson;
    filejson.AddLine(__L("{\"a\":[1,2}"));
    EXPECT_FALSE(filejson.DecodeAllLines());
    filejson.DeleteAllLines();
  }

  // A trailing comma before the closing brace is, per the shipped decoder's own inline comment
  // ("COMMA is ADD to end (BAD JSON format)"), explicitly TOLERATED rather than rejected -- this
  // is a real, deliberate leniency (not spec-correct JSON), captured here so it isn't mistaken for
  // a regression later.
  {
    XFILEJSON filejson;
    filejson.AddLine(__L("{\"a\":1,}"));
    EXPECT_TRUE(filejson.DecodeAllLines());

    XFILEJSONVALUE* a = filejson.GetValue(__L("a"));
    ASSERT_TRUE(a != NULL);
    EXPECT_EQ(a->GetValueInteger(), 1);

    filejson.DeleteAllObjects();
    filejson.DeleteAllLines();
  }
}


TEST(UNITTESTS_XFILEJSON_CLASSNAME, TopLevelArrayIsDecodedAsAnAnonymousArrayValueUnderAnObjectRoot)
{
  // Real, surprising quirk (not a crash, so it is safe to exercise directly): XFILEJSON::
  // DecodeAllLines() ALWAYS calls DecodeObject(position, /*isobject=*/true, root) for the document
  // root, regardless of whether the very first non-space character is '{' or '['. For a top-level
  // JSON array, this means GetRoot() does NOT come back as an XFILEJSONARRAY with the elements
  // directly inside it -- it comes back as a plain XFILEJSONOBJECT holding exactly one, unnamed
  // (empty-name) value of type ARRAY, and the real elements are one level deeper, inside that.
  XFILEJSON filejson;

  filejson.AddLine(__L("[10,20,30]"));
  ASSERT_TRUE(filejson.DecodeAllLines());

  XFILEJSONOBJECT* root = filejson.GetRoot();
  ASSERT_TRUE(root != NULL);
  EXPECT_FALSE(root->IsArray()); // NOT an array object, despite the document being a top-level array

  ASSERT_TRUE(root->GetValues() != NULL);
  ASSERT_EQ(root->GetValues()->GetSize(), (XDWORD)1);

  XFILEJSONVALUE* wrapped = root->GetValues()->Get(0);
  ASSERT_TRUE(wrapped != NULL);
  ASSERT_EQ(wrapped->GetType(), XFILEJSONVALUETYPE_ARRAY);

  XFILEJSONARRAY* array = wrapped->GetValueArray();
  ASSERT_TRUE(array != NULL);
  ASSERT_EQ(array->GetValues()->GetSize(), (XDWORD)3);
  EXPECT_EQ(array->GetValues()->Get(0)->GetValueInteger(), 10);
  EXPECT_EQ(array->GetValues()->Get(1)->GetValueInteger(), 20);
  EXPECT_EQ(array->GetValues()->Get(2)->GetValueInteger(), 30);

  filejson.DeleteAllObjects();
  filejson.DeleteAllLines();
}


TEST(UNITTESTS_XFILEJSON_CLASSNAME, EncodeThenDecodeRoundTripReproducesAnEquivalentTree)
{
  XFILEJSON filejson;

  XFILEJSONOBJECT* root = GEN_NEW XFILEJSONOBJECT();
  ASSERT_TRUE(filejson.SetRoot(root));

  XFILEJSON_ADDVALUE(root, __L("name"), __L("acme"));
  XFILEJSON_ADDVALUE(root, __L("count"), (int)7);
  XFILEJSON_ADDVALUE_NULL(root, __L("extra"));

  ASSERT_TRUE(filejson.EncodeAllLines(true));
  ASSERT_TRUE(filejson.GetNLines() > 0);

  XFILEJSON filejson2;
  for(int c=0; c<filejson.GetNLines(); c++)
    {
      filejson2.AddLine(*filejson.GetLine(c));
    }

  ASSERT_TRUE(filejson2.DecodeAllLines());

  XFILEJSONVALUE* name = filejson2.GetValue(__L("name"));
  ASSERT_TRUE(name != NULL);
  XSTRING namestr = name->GetValueString();
  EXPECT_FALSE(namestr.Compare(__L("acme"), false));

  XFILEJSONVALUE* count = filejson2.GetValue(__L("count"));
  ASSERT_TRUE(count != NULL);
  EXPECT_EQ(count->GetValueInteger(), 7);

  XFILEJSONVALUE* extra = filejson2.GetValue(__L("extra"));
  ASSERT_TRUE(extra != NULL);
  EXPECT_EQ(extra->GetType(), XFILEJSONVALUETYPE_NULL);

  filejson.DeleteAllObjects();
  filejson.DeleteAllLines();
  filejson2.DeleteAllObjects();
  filejson2.DeleteAllLines();
}


TEST(UNITTESTS_XFILEJSON_CLASSNAME, ObjectCloneDeepCopiesNamedValuesIndependentlyOfOriginal)
{
  // Clone() is only exercised here with NAMED values (every value added carries a SetName()),
  // which is the safe path. See the comment on the skipped case below for why an unnamed value
  // is deliberately NOT run through Clone() in this test binary.
  XFILEJSONOBJECT original;

  XFILEJSONVALUE* v1 = GEN_NEW XFILEJSONVALUE();
  v1->SetName(__L("a"));
  v1->Set((int)1);
  original.Add(v1);

  XFILEJSONVALUE* v2 = GEN_NEW XFILEJSONVALUE();
  v2->SetName(__L("b"));
  v2->Set(__L("original"));
  original.Add(v2);

  XFILEJSONOBJECT* clone = original.Clone();
  ASSERT_TRUE(clone != NULL);
  ASSERT_EQ(clone->GetValues()->GetSize(), (XDWORD)2);

  // Modify the clone's string value and confirm the original's own value is unaffected -- proves
  // Clone() is a real, independent deep copy and not a shallow/shared-pointer alias.
  XFILEJSONVALUE* clonedb = clone->GetValues()->Get(1);
  ASSERT_TRUE(clonedb != NULL);
  clonedb->Set(__L("changed"));

  XSTRING originalvalue = original.GetValues()->Get(1)->GetValueString();
  EXPECT_FALSE(originalvalue.Compare(__L("original"), false));

  XSTRING clonedvalue = clone->GetValues()->Get(1)->GetValueString();
  EXPECT_FALSE(clonedvalue.Compare(__L("changed"), false));

  GEN_DELETE clone;

  // NOTE (real XUtils bug, not fixed, documented rather than exercised to avoid crashing this
  // whole test binary): XFILEJSONVALUE::Clone() (XFileJSON.cpp) unconditionally dereferences its
  // own "name" member -- "newvalue->SetName(name->Get());" -- with no NULL check. Any value that
  // was never given a name (which is exactly what happens for every ARRAY ELEMENT produced by
  // DecodeObject(), since XFILEJSONVALUE::SetName() is only ever called when isobject==true) has
  // "name" left at its Clean()-initialized NULL, so calling Clone() on it -- e.g. via
  // XFILEJSONOBJECT::Clone() walking an array's own values -- is a guaranteed NULL-pointer crash.
}


} // namespace TEST_XFILEJSON
#endif
