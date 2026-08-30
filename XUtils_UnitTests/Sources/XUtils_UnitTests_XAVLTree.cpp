/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XAVLTree.cpp
*
* @class      XUTILS_UNITTESTS_XAVLTREE
* @brief      XUtils unit tests for XAVLTREE class
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

#include "XUtils_UnitTests_XAVLTree.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XAVLTree.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XAVLTREE
{


// Recursively checks that every node's AVL |balance| stays within {-1,0,1}
// (XAVLNODE<K>'s `key`/`height`/`balance`/`left`/`right`/`parent` members
// are all public, so this is directly walkable from outside the class).
static bool CheckBalanceInvariant(XAVLNODE<int>* node)
{
  if(!node) return true;

  if(node->balance < -1 || node->balance > 1) return false;

  return CheckBalanceInvariant(node->left) && CheckBalanceInvariant(node->right);
}


// Recursively collects an in-order walk of the tree into a flat array to
// verify the BST ordering invariant after inserts/deletes in different
// orders.
static void InOrderCollect(XAVLNODE<int>* node, int* out, int* count)
{
  if(!node) return;

  InOrderCollect(node->left, out, count);
  out[(*count)++] = node->key;
  InOrderCollect(node->right, out, count);
}


TEST(UNITTEST_XAVLTREE_CLASSNAME, ConstructorDefaultIsEmpty)
{
  XAVLTREE<int> tree;

  EXPECT_TRUE(tree.GetRoot() == NULL);
  EXPECT_EQ(tree.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XAVLTREE_CLASSNAME, AddAndInOrderTraversalIsSortedAscending)
{
  XAVLTREE<int> tree;
  int values[] = {50, 30, 70, 20, 40, 60, 80, 10, 90, 25};

  for(int v : values) tree.Add(v);

  EXPECT_EQ(tree.GetSize(), (XDWORD)10);

  XAVLTREE<int>::XITERATOR it;
  it = tree.Begin();
  XAVLTREE<int>::XITERATOR end;
  end = tree.End();

  int prev = -999999;
  int count = 0;
  bool sorted = true;
  while(it != end)
    {
      int v = *it;
      if(v < prev) sorted = false;
      prev = v;
      count++;
      ++it;
    }

  EXPECT_EQ(count, 10);
  EXPECT_TRUE(sorted);
}


TEST(UNITTEST_XAVLTREE_CLASSNAME, BalanceFactorStaysWithinRangeAscendingInserts)
{
  // Inserting an already-sorted ascending run is the classic worst case
  // for a plain (non-rebalancing) BST -- this specifically exercises the
  // AVL rotation logic.
  XAVLTREE<int> tree;
  for(int i = 1; i <= 31; i++) tree.Add(i);

  EXPECT_EQ(tree.GetSize(), (XDWORD)31);
  EXPECT_TRUE(CheckBalanceInvariant(tree.GetRoot()));

  int flat[64];
  int count = 0;
  InOrderCollect(tree.GetRoot(), flat, &count);

  ASSERT_EQ(count, 31);
  for(int i = 0; i < 31; i++) EXPECT_EQ(flat[i], i + 1);
}


TEST(UNITTEST_XAVLTREE_CLASSNAME, BalanceFactorStaysWithinRangeDescendingInserts)
{
  XAVLTREE<int> tree;
  for(int i = 31; i >= 1; i--) tree.Add(i);

  EXPECT_EQ(tree.GetSize(), (XDWORD)31);
  EXPECT_TRUE(CheckBalanceInvariant(tree.GetRoot()));

  int flat[64];
  int count = 0;
  InOrderCollect(tree.GetRoot(), flat, &count);

  ASSERT_EQ(count, 31);
  for(int i = 0; i < 31; i++) EXPECT_EQ(flat[i], i + 1);
}


TEST(UNITTEST_XAVLTREE_CLASSNAME, BalanceFactorStaysWithinRangeRandomishInserts)
{
  XAVLTREE<int> tree;
  int values[] = {17, 3, 42, 8, 91, 25, 6, 55, 12, 77, 1, 33, 60, 5, 48};
  int n = (int)(sizeof(values) / sizeof(values[0]));

  for(int i = 0; i < n; i++) tree.Add(values[i]);

  EXPECT_EQ(tree.GetSize(), (XDWORD)n);
  EXPECT_TRUE(CheckBalanceInvariant(tree.GetRoot()));

  int flat[64];
  int count = 0;
  InOrderCollect(tree.GetRoot(), flat, &count);

  ASSERT_EQ(count, n);
  for(int i = 1; i < count; i++) EXPECT_TRUE(flat[i - 1] < flat[i]);
}


TEST(UNITTEST_XAVLTREE_CLASSNAME, GetFindsExistingKey)
{
  XAVLTREE<int> tree;
  tree.Add(50);
  tree.Add(30);
  tree.Add(70);

  EXPECT_EQ(tree.Get(30), 30);
  EXPECT_EQ(tree.Get(70), 70);
}


TEST(UNITTEST_XAVLTREE_CLASSNAME, GetForMissingKeyReturnsDefaultConstructedValue)
{
  // KNOWN AMBIGUITY (XAVLTree.h line 293, `return K();`): Get() cannot
  // distinguish "key not present" from "key present with a value that
  // happens to equal K()" -- for K=int, a miss and a stored 0 are
  // indistinguishable through Get() alone. Find() (tested below) is the
  // only reliable presence check.
  XAVLTREE<int> tree;
  tree.Add(50);

  EXPECT_EQ(tree.Get(999), 0);
}


TEST(UNITTEST_XAVLTREE_CLASSNAME, FindReturnsIndexForExistingAndNotFoundForMissing)
{
  XAVLTREE<int> tree;
  tree.Add(50);
  tree.Add(30);
  tree.Add(70);

  EXPECT_EQ(tree.Find(50), 0);   // root always matches at index 0
  EXPECT_NE(tree.Find(30), NOTFOUND);
  EXPECT_EQ(tree.Find(999), NOTFOUND);
}


TEST(UNITTEST_XAVLTREE_CLASSNAME, MultiModeAllowsDuplicatesAndGetMultipleReturnsAll)
{
  // Default ctor argument is `multi = true`.
  XAVLTREE<int> tree;
  tree.Add(5);
  tree.Add(5);
  tree.Add(5);
  tree.Add(9);

  EXPECT_EQ(tree.GetSize(), (XDWORD)4);

  XLIST<int> matches = tree.GetMultiple(5);
  EXPECT_EQ(matches.GetSize(), (XDWORD)3);
}


TEST(UNITTEST_XAVLTREE_CLASSNAME, NonMultiModeRejectsDuplicateKeyButAddReturnValueIsMisleading)
{
  // KNOWN BUG (XAVLTree.h lines 164-170): Add() unconditionally
  // `return true;` regardless of whether Insert() actually inserted
  // anything -- in non-multi mode, Insert() silently no-ops (`return
  // NULL;`) on a duplicate key without touching `root`/`nelements`, yet
  // Add() still reports success. The tree's SIZE correctly reflects that
  // nothing was added; only the boolean return value lies.
  XAVLTREE<int> tree(false);

  bool firstAdd  = tree.Add(5);
  bool secondAdd = tree.Add(5); // duplicate, silently rejected internally

  EXPECT_TRUE(firstAdd);
  EXPECT_TRUE(secondAdd);              // documents the misleading "true"
  EXPECT_EQ(tree.GetSize(), (XDWORD)1); // but only one node actually exists
}


// NOTE (XAVLTree.h lines 341-357): both Delete(const K&) and
// Delete(XITERATOR) are confirmed HARD COMPILE ERRORS as shipped -- both
// call a lowercase `remove(...)` that is never defined anywhere in this
// class (only `Remove(XAVLNODE<K>*)` and `Remove(XAVLNODE<K>*, const K&)`,
// capitalized, exist, and neither is ever called). Unqualified lookup
// instead resolves `remove` to the C standard library's global
// `::remove(const char*)` (from <cstdio>, "delete this file"), which does
// not match either call site's argument list/count -- confirmed directly:
//   XAVLTree.h:348: error: no matching function for call to 'remove'
//     note: candidate function not viable: requires single argument
//     '__filename', but 2 arguments were provided
// Per the hard rule against fixing XUtils source, Delete is not exercised
// anywhere in this file.

// NOTE (XAVLTree.h line 682): the copy constructor and operator= (which
// both funnel through the protected `Copy(XAVLNODE<K>* node)` helper) are
// ALSO confirmed HARD COMPILE ERRORS as shipped -- `Copy` does
// `this->Add(node->element);` but XAVLNODE<K> has no `element` member at
// all (only `key`, `height`, `balance`, `left`, `right`, `parent`) --
// confirmed directly:
//   XAVLTree.h:682: error: no member named 'element' in 'XAVLNODE<int>'
// So neither the copy constructor nor operator= can be exercised; not
// tested here.


}
#endif
