/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XVectorSTL.cpp
*
* @class      XUTILS_UNITTESTS_XVECTORSTL
* @brief      XUtils unit tests for XVECTORSTL class
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

#include "XUtils_UnitTests_XVectorSTL.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XVectorSTL.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


// IMPORTANT (verified directly against XVectorSTL.h, not just inferred):
// Two methods are outright compile errors the moment they are instantiated
// (i.e. actually called):
//   - Resize(XDWORD) (line 88): `return this->resize(newsize);` returns
//     std::vector<T>::resize()'s void result from a function declared to
//     return bool -- ill-formed. This also means the SIZED CONSTRUCTOR
//     (line 62-66, which calls Resize() directly) is unusable, so this
//     file never constructs XVECTORSTL via the sized ctor.
//   - DeleteLast() (line 156): `this->getsize()` calls a method std::vector
//     does not have (the real member is size()); calling DeleteLast() at
//     all fails to build. Neither is exercised below for that reason.
// Both were confirmed with a standalone -fsyntax-only compile of this exact
// header before writing these tests.


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XVECTORSTL
{


TEST(UNITTEST_XVECTORSTL_CLASSNAME, ConstructorIsEmpty)
{
  XVECTORSTL<int> vector;

  EXPECT_TRUE(vector.IsEmpty());
  EXPECT_EQ(vector.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XVECTORSTL_CLASSNAME, AddAndGetElement)
{
  XVECTORSTL<int> vector;

  EXPECT_TRUE(vector.Add(10));
  EXPECT_TRUE(vector.Add(20));
  EXPECT_TRUE(vector.Add(30));

  EXPECT_FALSE(vector.IsEmpty());
  EXPECT_EQ(vector.GetSize(), (XDWORD)3);
  EXPECT_EQ(vector.Get(0), 10);
  EXPECT_EQ(vector.Get(1), 20);
  EXPECT_EQ(vector.GetLast(), 30);
}


// NOTE: a third confirmed compile-error-level bug, found while writing these
// tests (not previously called out in the analysis report): XVECTORSTL
// declares BOTH `Add(T element)` and `Add(T& element)` (XVectorSTL.h lines
// 92 and 99). Calling Add() with a plain lvalue argument (e.g. `int value=42;
// vector.Add(value);`) is ambiguous -- overload resolution ranks a by-value
// and a by-reference parameter as equally good exact matches for an lvalue,
// so Clang rejects the call outright ("call to member function 'Add' is
// ambiguous"). Only Add() called with an rvalue/temporary (as in the tests
// above) is unambiguous, since only the `T&` overload cannot bind a
// non-const rvalue. Verified directly; not exercised further here since the
// point is already made by the compile error itself.


TEST(UNITTEST_XVECTORSTL_CLASSNAME, DeleteIndexRemovesElement)
{
  // DeleteIndex is one of the genuinely-implemented methods (thin wrapper
  // over std::vector::erase).
  XVECTORSTL<int> vector;
  vector.Add(1);
  vector.Add(2);
  vector.Add(3);

  EXPECT_TRUE(vector.DeleteIndex(1));
  EXPECT_EQ(vector.GetSize(), (XDWORD)2);
  EXPECT_EQ(vector.Get(0), 1);
  EXPECT_EQ(vector.Get(1), 3);

  EXPECT_FALSE(vector.DeleteIndex(50));
}


TEST(UNITTEST_XVECTORSTL_CLASSNAME, FindAlwaysReportsNotFoundStub)
{
  // Find() is an unconditional no-op stub: `return NOTFOUND;` regardless of
  // whether the value is present (XVectorSTL.h lines 107-111). This
  // documents the actual (broken) behavior rather than real search semantics.
  XVECTORSTL<int> vector;
  vector.Add(5);

  EXPECT_EQ(vector.Find(5), NOTFOUND);
  EXPECT_EQ(vector.Find(999), NOTFOUND);
}


TEST(UNITTEST_XVECTORSTL_CLASSNAME, SetIsANoOpStubThatReportsSuccess)
{
  // Set() body is only `return true;` -- it never actually writes to the
  // vector (XVectorSTL.h lines 126-129).
  XVECTORSTL<int> vector;
  vector.Add(1);

  EXPECT_TRUE(vector.Set(0, 999));
  EXPECT_EQ(vector.Get(0), 1);   // unchanged despite Set() reporting success
}


TEST(UNITTEST_XVECTORSTL_CLASSNAME, InsertIsANoOpStubThatReportsSuccess)
{
  // Insert() body is only `return true;` -- nothing is inserted
  // (XVectorSTL.h lines 132-135).
  XVECTORSTL<int> vector;
  vector.Add(1);

  EXPECT_TRUE(vector.Insert(0, 999));
  EXPECT_EQ(vector.GetSize(), (XDWORD)1);   // size unchanged
}


TEST(UNITTEST_XVECTORSTL_CLASSNAME, DeleteNowRemovesTheMatchingElement)
{
  // FIXED: Delete(T) (XVectorSTL.h) now searches for the matching element and calls
  // DeleteIndex() on it, actually removing it, instead of unconditionally returning false.
  XVECTORSTL<int> vector;
  vector.Add(1);

  EXPECT_TRUE(vector.Delete(1));
  EXPECT_EQ(vector.GetSize(), (XDWORD)0);

  // A value not present is still correctly reported as not found.
  EXPECT_FALSE(vector.Delete(999));
}


TEST(UNITTEST_XVECTORSTL_CLASSNAME, DeleteContentsNowFreesEachElementAndClears)
{
  // FIXED: DeleteContents() (XVectorSTL.h) now deletes each stored pointer and clears the vector,
  // instead of doing nothing and reporting failure.
  XVECTORSTL<int*> vector;
  vector.Add(GEN_NEW int(1));

  EXPECT_TRUE(vector.DeleteContents());
  EXPECT_EQ(vector.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XVECTORSTL_CLASSNAME, DeleteAllNowActuallyClearsTheVector)
{
  // FIXED: DeleteAll() (XVectorSTL.h) now calls this->clear(), instead of doing nothing while
  // still reporting success.
  XVECTORSTL<int> vector;
  vector.Add(1);
  vector.Add(2);

  EXPECT_TRUE(vector.DeleteAll());
  EXPECT_EQ(vector.GetSize(), (XDWORD)0);
  EXPECT_TRUE(vector.IsEmpty());
}


TEST(UNITTEST_XVECTORSTL_CLASSNAME, SwapIsANoOpStubThatReportsSuccess)
{
  // Swap() body is only `return true;` -- nothing is swapped (XVectorSTL.h
  // lines 186-190).
  XVECTORSTL<int> vector;
  vector.Add(1);
  vector.Add(2);

  EXPECT_TRUE(vector.Swap(0, 1));
  EXPECT_EQ(vector.Get(0), 1);   // unchanged despite Swap() reporting success
  EXPECT_EQ(vector.Get(1), 2);
}


TEST(UNITTEST_XVECTORSTL_CLASSNAME, CopyIsANoOpStubThatReportsSuccess)
{
  // Copy() body is only `return true;` -- origin's contents are never
  // copied into *this (XVectorSTL.h lines 193-197).
  XVECTORSTL<int> origin;
  origin.Add(1);
  origin.Add(2);

  XVECTORSTL<int> destination;

  EXPECT_TRUE(destination.Copy(&origin));
  EXPECT_TRUE(destination.IsEmpty());   // nothing was actually copied
}


}
#endif

