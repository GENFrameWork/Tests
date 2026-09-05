/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XOrderedList.cpp
*
* @class      UNITTESTS_XUTILS_XORDEREDLIST
* @brief      XUtils unit tests for XORDEREDLIST class
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

#include "UnitTests_XUtils_XOrderedList.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XOrderedList.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XORDEREDLIST
{


// NOTE on the comparator contract (XOrderedList.h lines 53-83): the
// XCOMPARATOR<T> abstract base class (Compare(T*, T*)) is decorative/
// mismatched dead scaffolding -- XORDEREDLIST::Add actually calls
// `comparator.Compare(element, current->data)` with T BY VALUE (not T*),
// so a real Compare-type does not derive from XCOMPARATOR at all, it just
// needs a method `int Compare(T a, T b)`. Confirmed directly: a class that
// really implements XCOMPARATOR<T> (pointer signature) will not compile
// as the Compare template argument here.
//
// FIXED (previously a known bug, now confirmed corrected): Add() used to
// use a `switch` on the three-way result with only cases 0 and 1 handled
// (any other value, including the standard "-1 means a<b", silently fell
// through to "keep scanning") and inserted BEFORE `current` on result==1,
// the reverse of the usual strcmp-style convention. Add() now does a plain
// `if(result < 0) return this->Insert(current, element);` -- the standard,
// intuitive convention: Compare(a, b) returns negative when a belongs
// before b (a < b for ascending order), 0 for an exact-duplicate reject,
// and any positive value to keep scanning.
class INTCOMPARATOR_ASCENDING
{
  public:
    int Compare(int a, int b)
    {
      if(a == b) return 0;
      return (a < b) ? -1 : 1;
    }
};


// A comparator that returns a value outside the only two meaningful cases
// (0 and negative) to exercise Add()'s fallback for any other, non-negative
// result: `if(result < 0)` is false for 2, so it always falls through to
// `current = current->next;` ("keep scanning"), which for a comparator
// that ALWAYS returns 2 means every Add() ends up scanning to the tail
// and appending there. (This particular fallback path is unchanged by the
// fix above, since 2 was never one of the previously-mishandled values in
// either implementation.)
class ALWAYS_KEEP_SCANNING_COMPARATOR
{
  public:
    int Compare(int a, int b)
    {
      (void)a; (void)b;
      return 2;
    }
};


TEST(UNITTESTS_XORDEREDLIST_CLASSNAME, ConstructorIsEmpty)
{
  XORDEREDLIST<int, INTCOMPARATOR_ASCENDING> list;

  EXPECT_TRUE(list.IsEmpty());
  EXPECT_EQ(list.GetSize(), (XDWORD)0);
}


TEST(UNITTESTS_XORDEREDLIST_CLASSNAME, AddKeepsElementsInAscendingOrder)
{
  XORDEREDLIST<int, INTCOMPARATOR_ASCENDING> list;

  EXPECT_TRUE(list.Add(5));
  EXPECT_TRUE(list.Add(1));
  EXPECT_TRUE(list.Add(9));
  EXPECT_TRUE(list.Add(3));
  EXPECT_TRUE(list.Add(2));

  ASSERT_EQ(list.GetSize(), (XDWORD)5);
  EXPECT_EQ(list.Get(0), 1);
  EXPECT_EQ(list.Get(1), 2);
  EXPECT_EQ(list.Get(2), 3);
  EXPECT_EQ(list.Get(3), 5);
  EXPECT_EQ(list.Get(4), 9);
}


TEST(UNITTESTS_XORDEREDLIST_CLASSNAME, AddOfNewSmallestAndLargestValues)
{
  XORDEREDLIST<int, INTCOMPARATOR_ASCENDING> list;

  list.Add(5);
  list.Add(10);

  list.Add(1);  // new smallest -> must become the head
  list.Add(20); // new largest  -> must become the tail

  ASSERT_EQ(list.GetSize(), (XDWORD)4);
  EXPECT_EQ(list.GetFirst(), 1);
  EXPECT_EQ(list.GetLast(), 20);
}


TEST(UNITTESTS_XORDEREDLIST_CLASSNAME, AddRejectsExactDuplicate)
{
  XORDEREDLIST<int, INTCOMPARATOR_ASCENDING> list;

  EXPECT_TRUE(list.Add(7));
  EXPECT_FALSE(list.Add(7));

  EXPECT_EQ(list.GetSize(), (XDWORD)1);
}


TEST(UNITTESTS_XORDEREDLIST_CLASSNAME, FindLocatesInsertedElementAndReportsMissingOne)
{
  XORDEREDLIST<int, INTCOMPARATOR_ASCENDING> list;

  list.Add(5);
  list.Add(1);
  list.Add(3);

  EXPECT_EQ(list.Find(3), 1);           // sorted order is 1,3,5 -> index 1
  EXPECT_EQ(list.Find(999), NOTFOUND);
}


TEST(UNITTESTS_XORDEREDLIST_CLASSNAME, DeleteRemovesElementAndPreservesOrder)
{
  XORDEREDLIST<int, INTCOMPARATOR_ASCENDING> list;

  list.Add(5);
  list.Add(1);
  list.Add(3);
  list.Add(9);

  EXPECT_TRUE(list.Delete(3));

  ASSERT_EQ(list.GetSize(), (XDWORD)3);
  EXPECT_EQ(list.Get(0), 1);
  EXPECT_EQ(list.Get(1), 5);
  EXPECT_EQ(list.Get(2), 9);

  EXPECT_FALSE(list.Delete(999));
}


TEST(UNITTESTS_XORDEREDLIST_CLASSNAME, DeleteAllEmptiesList)
{
  XORDEREDLIST<int, INTCOMPARATOR_ASCENDING> list;

  list.Add(1);
  list.Add(2);

  EXPECT_TRUE(list.DeleteAll());
  EXPECT_TRUE(list.IsEmpty());
  EXPECT_EQ(list.GetSize(), (XDWORD)0);
}


TEST(UNITTESTS_XORDEREDLIST_CLASSNAME, ComparatorResultOutsideZeroOneFallsThroughToKeepScanning)
{
  XORDEREDLIST<int, ALWAYS_KEEP_SCANNING_COMPARATOR> list;

  EXPECT_TRUE(list.Add(5));
  EXPECT_TRUE(list.Add(1));
  EXPECT_TRUE(list.Add(9));

  // Every Add() scans past every existing element (comparator always
  // returns 2, never 0 or 1) and falls out of the loop to the plain
  // XLIST<T>::Add() append -- so elements land in INSERTION order, not
  // sorted order, documenting the switch's no-default fallback behavior.
  ASSERT_EQ(list.GetSize(), (XDWORD)3);
  EXPECT_EQ(list.Get(0), 5);
  EXPECT_EQ(list.Get(1), 1);
  EXPECT_EQ(list.Get(2), 9);
}


TEST(UNITTESTS_XORDEREDLIST_CLASSNAME, IteratorTraversalVisitsAllElementsInSortedOrder)
{
  XORDEREDLIST<int, INTCOMPARATOR_ASCENDING> list;

  list.Add(30);
  list.Add(10);
  list.Add(20);

  XORDEREDLIST<int, INTCOMPARATOR_ASCENDING>::XITERATOR it;
  it = list.Begin();
  XORDEREDLIST<int, INTCOMPARATOR_ASCENDING>::XITERATOR itend;
  itend = list.End();

  int prev = -1;
  int count = 0;
  bool sorted = true;
  while(it != itend)
    {
      if(*it < prev) sorted = false;
      prev = *it;
      count++;
      ++it;
    }

  EXPECT_EQ(count, 3);
  EXPECT_TRUE(sorted);
}


}
#endif
