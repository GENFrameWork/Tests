/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XVector.cpp
*
* @class      UNITTESTS_XUTILS_XVECTOR
* @brief      XUtils unit tests for XVECTOR class
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

#include "UnitTests_XUtils_XVector.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XVector.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XVECTOR
{


TEST(UNITTESTS_XVECTOR_CLASSNAME, ConstructorIsEmpty)
{
  XVECTOR<int> vector;

  EXPECT_TRUE(vector.IsEmpty());
  EXPECT_EQ(vector.GetSize(), (XDWORD)0);
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, SizedConstructorGrowsAndZeroFillsViaAddZero)
{
  // The sized ctor calls Resize(), whose growing branch appends via Add(0)
  // (XVector.h line 99), not via T() default-construction -- for T=int this
  // coincidentally yields zero-valued elements.
  XVECTOR<int> vector(5);

  EXPECT_EQ(vector.GetSize(), (XDWORD)5);
  EXPECT_EQ(vector.Get(0), 0);
  EXPECT_EQ(vector.Get(4), 0);
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, AddAndGetElement)
{
  XVECTOR<int> vector;

  EXPECT_TRUE(vector.Add(10));
  EXPECT_TRUE(vector.Add(20));
  EXPECT_TRUE(vector.Add(30));

  EXPECT_EQ(vector.GetSize(), (XDWORD)3);
  EXPECT_EQ(vector.Get(0), 10);
  EXPECT_EQ(vector.Get(1), 20);
  EXPECT_EQ(vector.Get(2), 30);
  EXPECT_EQ(vector.GetLast(), 30);
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, GetOutOfRangeReturnsDefaultValue)
{
  XVECTOR<int> vector;
  vector.Add(1);

  EXPECT_EQ(vector.Get(5), 0);
  EXPECT_EQ(vector.GetPointer(5), (int*)NULL);
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, FastGetAndGetPointerValidIndex)
{
  // FastGet/GetPointer perform no bounds checking by contract -- only valid
  // indexes are exercised here.
  XVECTOR<int> vector;
  vector.Add(42);
  vector.Add(43);

  EXPECT_EQ(vector.FastGet(1), 43);

  int* pointer = vector.GetPointer(0);
  ASSERT_NE((void*)pointer, (void*)NULL);
  EXPECT_EQ(*pointer, 42);
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, SetOverwritesExistingElement)
{
  XVECTOR<int> vector;
  vector.Add(1);
  vector.Add(2);

  EXPECT_TRUE(vector.Set(1, 99));
  EXPECT_EQ(vector.Get(1), 99);

  EXPECT_FALSE(vector.Set(10, 0));
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, InsertAtMiddleShiftsFollowingElements)
{
  XVECTOR<int> vector;
  vector.Add(1);
  vector.Add(2);
  vector.Add(4);

  EXPECT_TRUE(vector.Insert(2, 3));

  EXPECT_EQ(vector.GetSize(), (XDWORD)4);
  EXPECT_EQ(vector.Get(0), 1);
  EXPECT_EQ(vector.Get(1), 2);
  EXPECT_EQ(vector.Get(2), 3);
  EXPECT_EQ(vector.Get(3), 4);
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, InsertBeyondSizeClampsToAppend)
{
  // Unlike XLIST::Insert (which rejects index >= nelements), XVECTOR::Insert
  // clamps any out-of-range index down to "append at end" (XVector.h line 216).
  XVECTOR<int> vector;
  vector.Add(1);
  vector.Add(2);

  EXPECT_TRUE(vector.Insert(100, 3));
  EXPECT_EQ(vector.GetSize(), (XDWORD)3);
  EXPECT_EQ(vector.GetLast(), 3);
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, FindExistingAndMissingElement)
{
  XVECTOR<int> vector;
  vector.Add(10);
  vector.Add(20);
  vector.Add(30);

  EXPECT_EQ(vector.Find(20), 1);
  EXPECT_EQ(vector.Find(999), NOTFOUND);
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, AddRejectsDuplicatesWhenNotMulti)
{
  XVECTOR<int> vector;
  vector.SetIsMulti(false);

  EXPECT_TRUE(vector.Add(5));
  EXPECT_FALSE(vector.Add(5));
  EXPECT_EQ(vector.GetSize(), (XDWORD)1);
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, AddAllowsDuplicatesByDefault)
{
  // ismulti defaults to true (see Clean() in XVector.h), so duplicates are
  // allowed unless SetIsMulti(false) is called explicitly.
  XVECTOR<int> vector;

  EXPECT_TRUE(vector.Add(5));
  EXPECT_TRUE(vector.Add(5));
  EXPECT_EQ(vector.GetSize(), (XDWORD)2);
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, DeleteRemovesFirstMatchingValue)
{
  // Delete(element) scans from index 0 and removes the FIRST match, not
  // necessarily the intended occurrence when duplicates are present -- this
  // is the same first-match contract that produces the documented XSTACK
  // Pop() ordering bug; here it is simply the container's stated behavior.
  XVECTOR<int> vector;
  vector.Add(5);
  vector.Add(3);
  vector.Add(5);

  EXPECT_TRUE(vector.Delete(5));

  EXPECT_EQ(vector.GetSize(), (XDWORD)2);
  EXPECT_EQ(vector.Get(0), 3);
  EXPECT_EQ(vector.Get(1), 5);

  EXPECT_FALSE(vector.Delete(999));
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, DeleteIndexAndDeleteLast)
{
  XVECTOR<int> vector;
  vector.Add(1);
  vector.Add(2);
  vector.Add(3);

  EXPECT_TRUE(vector.DeleteIndex(1));
  EXPECT_EQ(vector.GetSize(), (XDWORD)2);
  EXPECT_EQ(vector.Get(0), 1);
  EXPECT_EQ(vector.Get(1), 3);

  EXPECT_TRUE(vector.DeleteLast());
  EXPECT_EQ(vector.GetSize(), (XDWORD)1);
  EXPECT_EQ(vector.Get(0), 1);

  EXPECT_FALSE(vector.DeleteIndex(50));
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, DeleteAllEmptiesVector)
{
  XVECTOR<int> vector;
  vector.Add(1);
  vector.Add(2);

  EXPECT_TRUE(vector.DeleteAll());
  EXPECT_TRUE(vector.IsEmpty());
  EXPECT_EQ(vector.GetSize(), (XDWORD)0);

  // DeleteAll() on an already-empty vector reports failure (array==NULL guard).
  EXPECT_FALSE(vector.DeleteAll());
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, SwapElements)
{
  XVECTOR<int> vector;
  vector.Add(1);
  vector.Add(2);
  vector.Add(3);

  EXPECT_TRUE(vector.Swap(0, 2));
  EXPECT_EQ(vector.Get(0), 3);
  EXPECT_EQ(vector.Get(2), 1);

  EXPECT_FALSE(vector.Swap(0, 50));
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, ResizeGrowsAndShrinks)
{
  XVECTOR<int> vector;
  vector.Add(1);
  vector.Add(2);

  EXPECT_TRUE(vector.Resize(4));
  EXPECT_EQ(vector.GetSize(), (XDWORD)4);
  EXPECT_EQ(vector.Get(2), 0);   // grown via Add(0)
  EXPECT_EQ(vector.Get(3), 0);

  EXPECT_TRUE(vector.Resize(1));
  EXPECT_EQ(vector.GetSize(), (XDWORD)1);
  EXPECT_EQ(vector.Get(0), 1);

  // Resizing to the current size is explicitly rejected (XVector.h line 90-93).
  EXPECT_FALSE(vector.Resize(1));
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, ResizeForcesInternalReallocationAndKeepsValuesConsistent)
{
  // Force ResizeAdd()'s realloc/memcpy growth path with a tiny addinlimit so
  // more than one grow happens across a handful of Adds.
  XVECTOR<int> vector;
  vector.SetAddInLimit(2);

  for(int c = 0; c < 10; c++)
    {
      EXPECT_TRUE(vector.Add(c));
    }

  EXPECT_EQ(vector.GetSize(), (XDWORD)10);
  for(int c = 0; c < 10; c++)
    {
      EXPECT_EQ(vector.Get(c), c);
    }
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, CopyOfPointerElementsSharesUnderlyingObjects)
{
  // Copy() is implemented via a raw memcpy of the backing T[] array
  // (XVector.h line 431), not per-element copy construction. For a pointer
  // element type this simply duplicates the pointer VALUES (which is the
  // expected/harmless shallow-copy semantics for a vector-of-pointers) --
  // both vectors end up referencing the very same XSTRING objects.
  XSTRING stringa("hello");
  XSTRING stringb("world");

  XVECTOR<XSTRING*> origin;
  origin.Add(&stringa);
  origin.Add(&stringb);

  XVECTOR<XSTRING*> copy;
  EXPECT_TRUE(copy.Copy(&origin));

  ASSERT_EQ(copy.GetSize(), origin.GetSize());
  EXPECT_EQ(copy.Get(0), origin.Get(0));   // same pointer, not a distinct clone
  EXPECT_EQ(copy.Get(1), origin.Get(1));

  // NOTE (known concern, not exercised here to avoid undefined behavior):
  // per the analysis report, Copy()/ResizeAdd()/ResizeRemove() use raw
  // memcpy/memmove on the element bytes rather than copy-construction/
  // destruction. For a VALUE (non-pointer) owning type such as plain
  // XSTRING, this can leave two vectors' elements sharing one heap buffer
  // after a growth-triggering Add() or a Copy(), which use-after-frees or
  // double-frees once both vectors are destroyed. This is not exercised
  // as a live assertion here because it is genuine memory corruption (would
  // make the whole suite's outcome depend on heap layout/ASAN), but it is a
  // real, verifiable design flaw worth the team's attention (XVector.h lines
  // 431, 452, 501).
}


TEST(UNITTESTS_XVECTOR_CLASSNAME, DeleteContentsFreesPointerElements)
{
  XVECTOR<int*> vector;
  vector.Add(GEN_NEW int(1));
  vector.Add(GEN_NEW int(2));

  EXPECT_TRUE(vector.DeleteContents());
  EXPECT_EQ(vector.GetSize(), (XDWORD)0);

  // No-op (returns false) once already emptied.
  EXPECT_FALSE(vector.DeleteContents());
}


}
#endif

