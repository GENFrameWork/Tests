/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XList.cpp
*
* @class      XUTILS_UNITTESTS_XLIST
* @brief      XUtils unit tests for XLIST class
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

#include "XUtils_UnitTests_XList.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XList.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XLIST
{


TEST(UNITTEST_XLIST_CLASSNAME, ConstructorIsEmpty)
{
  XLIST<int> list;

  EXPECT_TRUE(list.IsEmpty());
  EXPECT_EQ(list.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XLIST_CLASSNAME, AddAndGetElement)
{
  XLIST<int> list;

  EXPECT_TRUE(list.Add(1));
  EXPECT_TRUE(list.Add(2));
  EXPECT_TRUE(list.Add(3));

  EXPECT_EQ(list.GetSize(), (XDWORD)3);
  EXPECT_EQ(list.Get(0), 1);
  EXPECT_EQ(list.Get(1), 2);
  EXPECT_EQ(list.Get(2), 3);
  EXPECT_EQ(list.GetFirst(), 1);
  EXPECT_EQ(list.GetLast(), 3);
}


TEST(UNITTEST_XLIST_CLASSNAME, GetOutOfRangeReturnsDefaultValue)
{
  XLIST<int> list;
  list.Add(1);

  EXPECT_EQ(list.Get(5), 0);
}


TEST(UNITTEST_XLIST_CLASSNAME, AddRejectsDuplicatesWhenNotMulti)
{
  XLIST<int> list;
  list.SetIsMulti(false);

  EXPECT_TRUE(list.Add(7));
  EXPECT_FALSE(list.Add(7));
  EXPECT_EQ(list.GetSize(), (XDWORD)1);
}


TEST(UNITTEST_XLIST_CLASSNAME, AddAllowsDuplicatesByDefault)
{
  XLIST<int> list;

  EXPECT_TRUE(list.Add(7));
  EXPECT_TRUE(list.Add(7));
  EXPECT_EQ(list.GetSize(), (XDWORD)2);
}


TEST(UNITTEST_XLIST_CLASSNAME, FindExistingAndMissingElement)
{
  XLIST<int> list;
  list.Add(10);
  list.Add(20);
  list.Add(30);

  EXPECT_EQ(list.Find(20), 1);
  EXPECT_EQ(list.Find(999), NOTFOUND);

  XLISTDATA<int>* data = list.FindData(20);
  ASSERT_NE((void*)data, (void*)NULL);
  EXPECT_EQ(data->data, 20);
  EXPECT_EQ(list.FindData(999), (XLISTDATA<int>*)NULL);
}


TEST(UNITTEST_XLIST_CLASSNAME, SetOverwritesExistingElement)
{
  XLIST<int> list;
  list.Add(1);
  list.Add(2);

  EXPECT_TRUE(list.Set(1, 99));
  EXPECT_EQ(list.Get(1), 99);

  EXPECT_FALSE(list.Set(50, 0));
}


TEST(UNITTEST_XLIST_CLASSNAME, InsertAtMiddleByIndex)
{
  XLIST<int> list;
  list.Add(1);
  list.Add(2);
  list.Add(4);

  EXPECT_TRUE(list.Insert((XDWORD)1, 99));

  EXPECT_EQ(list.GetSize(), (XDWORD)4);
  EXPECT_EQ(list.Get(0), 1);
  EXPECT_EQ(list.Get(1), 99);
  EXPECT_EQ(list.Get(2), 2);
  EXPECT_EQ(list.Get(3), 4);
}


TEST(UNITTEST_XLIST_CLASSNAME, InsertAtIndexEqualToSizeIsRejected)
{
  // Unlike XVECTOR::Insert (which clamps an out-of-range index down to
  // append), XLIST::Insert(XDWORD,...) rejects any index >= nelements
  // outright (XList.h line 363) -- it cannot be used to append; only
  // Add()/InsertNext() can append to an XLIST.
  XLIST<int> list;
  list.Add(1);
  list.Add(2);

  EXPECT_FALSE(list.Insert(list.GetSize(), 3));
  EXPECT_EQ(list.GetSize(), (XDWORD)2);
}


TEST(UNITTEST_XLIST_CLASSNAME, InsertPreviousAndNextByNodePointer)
{
  XLIST<int> list;
  list.Add(1);
  list.Add(3);

  XLISTDATA<int>* second = list.FindData(3);
  ASSERT_NE((void*)second, (void*)NULL);

  EXPECT_TRUE(list.InsertPrevious(second, 2));
  EXPECT_EQ(list.GetSize(), (XDWORD)3);
  EXPECT_EQ(list.Get(1), 2);

  XLISTDATA<int>* first = list.FindData(1);
  ASSERT_NE((void*)first, (void*)NULL);

  EXPECT_TRUE(list.InsertNext(first, 0));
  EXPECT_EQ(list.GetSize(), (XDWORD)4);
  EXPECT_EQ(list.Get(1), 0);
}


TEST(UNITTEST_XLIST_CLASSNAME, DeleteByValueRemovesFirstMatch)
{
  XLIST<int> list;
  list.Add(5);
  list.Add(3);
  list.Add(5);

  EXPECT_TRUE(list.Delete(5));

  EXPECT_EQ(list.GetSize(), (XDWORD)2);
  EXPECT_EQ(list.Get(0), 3);
  EXPECT_EQ(list.Get(1), 5);

  EXPECT_FALSE(list.Delete(999));
}


TEST(UNITTEST_XLIST_CLASSNAME, DeleteByNodePointer)
{
  XLIST<int> list;
  list.Add(1);
  list.Add(2);
  list.Add(3);

  XLISTDATA<int>* middle = list.FindData(2);
  ASSERT_NE((void*)middle, (void*)NULL);

  EXPECT_TRUE(list.Delete(middle));
  EXPECT_EQ(list.GetSize(), (XDWORD)2);
  EXPECT_EQ(list.Get(0), 1);
  EXPECT_EQ(list.Get(1), 3);
}


TEST(UNITTEST_XLIST_CLASSNAME, DeleteIndexAndDeleteLast)
{
  XLIST<int> list;
  list.Add(1);
  list.Add(2);
  list.Add(3);

  EXPECT_TRUE(list.DeleteIndex(1));
  EXPECT_EQ(list.GetSize(), (XDWORD)2);
  EXPECT_EQ(list.Get(0), 1);
  EXPECT_EQ(list.Get(1), 3);

  EXPECT_TRUE(list.DeleteLast());
  EXPECT_EQ(list.GetSize(), (XDWORD)1);
  EXPECT_EQ(list.Get(0), 1);

  EXPECT_FALSE(list.DeleteIndex(50));
}


TEST(UNITTEST_XLIST_CLASSNAME, DeleteAllEmptiesList)
{
  XLIST<int> list;
  list.Add(1);
  list.Add(2);

  EXPECT_TRUE(list.DeleteAll());
  EXPECT_TRUE(list.IsEmpty());
  EXPECT_EQ(list.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XLIST_CLASSNAME, SwapElements)
{
  XLIST<int> list;
  list.Add(1);
  list.Add(2);
  list.Add(3);

  EXPECT_TRUE(list.Swap(0, 2));
  EXPECT_EQ(list.Get(0), 3);
  EXPECT_EQ(list.Get(2), 1);

  EXPECT_FALSE(list.Swap(0, 50));
}


TEST(UNITTEST_XLIST_CLASSNAME, ResizeGrowsWithDefaultConstructedElements)
{
  XLIST<int> list;
  list.Add(1);
  list.Add(2);

  EXPECT_TRUE(list.Resize(4));
  EXPECT_EQ(list.GetSize(), (XDWORD)4);
  EXPECT_EQ(list.Get(2), 0);
  EXPECT_EQ(list.Get(3), 0);
}


TEST(UNITTEST_XLIST_CLASSNAME, ResizeShrinksFromTheEnd)
{
  XLIST<int> list;
  list.Add(1);
  list.Add(2);
  list.Add(3);

  EXPECT_TRUE(list.Resize(1));
  EXPECT_EQ(list.GetSize(), (XDWORD)1);
  EXPECT_EQ(list.Get(0), 1);
}


TEST(UNITTEST_XLIST_CLASSNAME, ResizeContentsOnlySupportsShrinking)
{
  // Unlike XVECTOR::ResizeContents (grow or shrink), XLIST::ResizeContents
  // explicitly refuses newsize >= nelements (XList.h line 651).
  XLIST<int> list;
  list.Add(1);
  list.Add(2);
  list.Add(3);

  EXPECT_FALSE(list.ResizeContents((XDWORD)5));
  EXPECT_FALSE(list.ResizeContents((XDWORD)3));

  EXPECT_TRUE(list.ResizeContents((XDWORD)1));
  EXPECT_EQ(list.GetSize(), (XDWORD)1);
  EXPECT_EQ(list.Get(0), 1);
}


TEST(UNITTEST_XLIST_CLASSNAME, DeleteContentsFreesPointerElements)
{
  XLIST<int*> list;
  list.Add(GEN_NEW int(1));
  list.Add(GEN_NEW int(2));

  EXPECT_TRUE(list.DeleteContents());
  EXPECT_EQ(list.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XLIST_CLASSNAME, IteratorTraversalVisitsAllElementsInOrder)
{
  XLIST<int> list;
  list.Add(10);
  list.Add(20);
  list.Add(30);

  XLIST<int>::XITERATOR it;
  it = list.Begin();
  XLIST<int>::XITERATOR itend;
  itend = list.End();

  int sum   = 0;
  int count = 0;
  while(it != itend)
    {
      sum += *it;
      count++;
      ++it;
    }

  EXPECT_EQ(count, 3);
  EXPECT_EQ(sum, 60);
}


TEST(UNITTEST_XLIST_CLASSNAME, AssignmentOperatorAppendsInsteadOfReplacing)
{
  // KNOWN BUG (XList.h lines 161-173): operator=(XLIST<T>&) never clears
  // *this before copying rhs's elements over -- assigning into a non-empty
  // list APPENDS rhs's contents rather than replacing them, violating the
  // usual C++ assignment-operator contract (after `a = b;`, `a` should equal
  // `b`, not `a`'s-old-contents-followed-by-`b`). This test documents the
  // actual (buggy) behavior.
  XLIST<int> lista;
  lista.Add(1);
  lista.Add(2);

  XLIST<int> listb;
  listb.Add(3);
  listb.Add(4);

  lista = listb;

  EXPECT_EQ(lista.GetSize(), (XDWORD)4);   // expected correct size would be 2
  EXPECT_EQ(lista.Get(0), 1);
  EXPECT_EQ(lista.Get(1), 2);
  EXPECT_EQ(lista.Get(2), 3);
  EXPECT_EQ(lista.Get(3), 4);
}


// NOTE on two further confirmed issues NOT exercised here (both would crash
// or fail to build rather than fail an assertion, per direct verification
// against this header):
//  - GetData(XDWORD index): its out-of-range guard clause is `return T();`
//    (copy-pasted from the sibling Get() method) even though GetData's own
//    return type is XLISTDATA<T>*, not T -- for any T without an implicit
//    conversion to XLISTDATA<T>* (i.e. every ordinary T), simply CALLING
//    GetData() at all fails to compile (verified directly: XLIST<int>::
//    GetData(5) is a hard compiler error, not merely an out-of-range
//    runtime concern) -- XList.h lines 321-326.
//  - Insert(XLISTDATA<T>* position, T element) with position==NULL on a
//    non-empty list: the `if(position == NULL) { Add(element); }` branch
//    has no `return` at its end, so control falls through into
//    `position->prev` a few lines later and dereferences the null pointer
//    -- XList.h lines 417-420 vs. 443. This is a guaranteed crash, not
//    something to assert on in a shared test binary.


}
#endif

