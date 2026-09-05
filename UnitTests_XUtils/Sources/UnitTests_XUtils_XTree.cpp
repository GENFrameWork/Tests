/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XTree.cpp
*
* @class      UNITTESTS_XUTILS_XTREE
* @brief      XUtils unit tests for XTREE class
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

#include "UnitTests_XUtils_XTree.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XTree.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XTREE
{


// NOTE on element type: XTREE_NODE<T>'s destructor unconditionally calls
// DeleteContents() -> DeleteContent(), whose body is `if(!data) return
// false; GEN_DELETE data; data = NULL;` (XTree.h lines 142-150). For a
// plain value T (e.g. plain int) this fails to compile the moment ANY
// XTREE_NODE<int> is ever destructed (`delete data;` on a non-pointer is
// ill-formed) -- confirmed directly with a standalone compile. So every
// test below uses T = int* (heap-allocated ints) so the node's implicit
// destructor path actually compiles and runs.
typedef int* ELEM;


TEST(UNITTESTS_XTREE_CLASSNAME, ConstructorDefaultIsEmpty)
{
  XTREE<ELEM> tree;

  EXPECT_TRUE(tree.GetRoot() == NULL);
  EXPECT_EQ(tree.GetNNodes(), (XDWORD)0);
}


TEST(UNITTESTS_XTREE_CLASSNAME, ConstructorWithRootNodeCountsOneNode)
{
  XTREE_NODE<ELEM>* root = new XTREE_NODE<ELEM>(new int(1));
  XTREE<ELEM> tree(root);

  EXPECT_EQ(tree.GetRoot(), root);
  EXPECT_EQ(tree.GetNNodes(), (XDWORD)1);
  EXPECT_FALSE(root->HasChildren());
  EXPECT_EQ(root->GetNChildren(), 0);
}


TEST(UNITTESTS_XTREE_CLASSNAME, AddChildBuildsHierarchyAndCountsAllNodes)
{
  XTREE_NODE<ELEM>* root = new XTREE_NODE<ELEM>(new int(1));
  XTREE_NODE<ELEM>* c1   = new XTREE_NODE<ELEM>(new int(2));
  XTREE_NODE<ELEM>* c2   = new XTREE_NODE<ELEM>(new int(3));
  XTREE_NODE<ELEM>* gc   = new XTREE_NODE<ELEM>(new int(4));

  root->AddChild(c1);
  root->AddChild(c2);
  c1->AddChild(gc);

  XTREE<ELEM> tree(root);

  EXPECT_TRUE(root->HasChildren());
  EXPECT_EQ(root->GetNChildren(), 2);
  EXPECT_EQ(root->GetChild(0), c1);
  EXPECT_EQ(root->GetChild(1), c2);
  EXPECT_EQ(c1->GetChild(0), gc);
  EXPECT_EQ(tree.GetNNodes(), (XDWORD)4);

  // AddChild wires the parent pointer back
  EXPECT_EQ(c1->GetParent(), root);
  EXPECT_EQ(gc->GetParent(), c1);
}


TEST(UNITTESTS_XTREE_CLASSNAME, InsertChildPlacesAtGivenIndex)
{
  XTREE_NODE<ELEM>* root = new XTREE_NODE<ELEM>(new int(1));
  XTREE_NODE<ELEM>* c1   = new XTREE_NODE<ELEM>(new int(2));
  XTREE_NODE<ELEM>* c2   = new XTREE_NODE<ELEM>(new int(3));

  root->AddChild(c2);
  root->InsertChild(0, c1);

  EXPECT_EQ(root->GetNChildren(), 2);
  EXPECT_EQ(root->GetChild(0), c1);
  EXPECT_EQ(root->GetChild(1), c2);
  EXPECT_EQ(c1->GetParent(), root);

  XTREE<ELEM> tree(root);
}


TEST(UNITTESTS_XTREE_CLASSNAME, GetLevelReflectsDepthFromRoot)
{
  XTREE_NODE<ELEM>* root = new XTREE_NODE<ELEM>(new int(1));
  XTREE_NODE<ELEM>* c1   = new XTREE_NODE<ELEM>(new int(2));
  XTREE_NODE<ELEM>* gc   = new XTREE_NODE<ELEM>(new int(3));

  root->AddChild(c1);
  c1->AddChild(gc);

  EXPECT_EQ(root->GetLevel(), 0);
  EXPECT_EQ(c1->GetLevel(), 1);
  EXPECT_EQ(gc->GetLevel(), 2);

  XTREE<ELEM> tree(root);
}


TEST(UNITTESTS_XTREE_CLASSNAME, IteratorTraversesPreOrder)
{
  // Layout:      1
  //             / \
  //            2   3
  //            |
  //            4
  XTREE_NODE<ELEM>* root = new XTREE_NODE<ELEM>(new int(1));
  XTREE_NODE<ELEM>* c1   = new XTREE_NODE<ELEM>(new int(2));
  XTREE_NODE<ELEM>* c2   = new XTREE_NODE<ELEM>(new int(3));
  XTREE_NODE<ELEM>* gc   = new XTREE_NODE<ELEM>(new int(4));

  root->AddChild(c1);
  root->AddChild(c2);
  c1->AddChild(gc);

  XTREE<ELEM> tree(root);

  XTREE_NODE_ITERATOR<ELEM> it  = tree.Begin();
  XTREE_NODE_ITERATOR<ELEM> end = tree.End();

  int visited[8];
  int count = 0;
  while(it != end)
    {
      visited[count++] = *(*it);
      ++it;
    }

  ASSERT_EQ(count, 4);
  EXPECT_EQ(visited[0], 1);
  EXPECT_EQ(visited[1], 2);
  EXPECT_EQ(visited[2], 4);
  EXPECT_EQ(visited[3], 3);
}


TEST(UNITTESTS_XTREE_CLASSNAME, IteratorOperatorBoolReflectsCurrentNode)
{
  XTREE_NODE<ELEM>* root = new XTREE_NODE<ELEM>(new int(1));
  XTREE<ELEM> tree(root);

  XTREE_NODE_ITERATOR<ELEM> it = tree.Begin();
  EXPECT_TRUE((bool)it);

  ++it;
  EXPECT_FALSE((bool)it);
  EXPECT_TRUE(it == tree.End());
}


TEST(UNITTESTS_XTREE_CLASSNAME, IteratorCopyAssignmentDuplicatesTraversalPosition)
{
  XTREE_NODE<ELEM>* root = new XTREE_NODE<ELEM>(new int(1));
  XTREE_NODE<ELEM>* c1   = new XTREE_NODE<ELEM>(new int(2));
  XTREE_NODE<ELEM>* c2   = new XTREE_NODE<ELEM>(new int(3));

  root->AddChild(c1);
  root->AddChild(c2);

  XTREE<ELEM> tree(root);

  XTREE_NODE_ITERATOR<ELEM> it = tree.Begin();
  ++it; // now positioned at c1, with c2 still pending on the internal stack

  XTREE_NODE_ITERATOR<ELEM> copy(it);
  EXPECT_TRUE(copy == it);

  // Both the original and the copy should independently finish the
  // remaining traversal (c2) the same way.
  ++it;
  ++copy;
  EXPECT_TRUE(it == copy);
  EXPECT_TRUE(it == tree.End());
}


// NOTE (XTree.h line 295): XTREE_NODE_ITERATOR::operator-> is confirmed
// broken -- `return (current?&current->data():current);` tries to CALL
// `data` (a private plain data member, not a method) and additionally
// returns mismatched types (T* vs XTREE_NODE<T>*) on its two ternary
// branches. Any code that writes `it->something` fails to compile
// (verified directly: even the syntactically simplest possible use,
// `*(it.operator->())`, is a hard compile error -- "'data' is a private
// member" and "called object type is not a function"). operator* (used
// throughout this file as `*(*it)`) is unaffected and works correctly.
// Deliberately not exercised here.


TEST(UNITTESTS_XTREE_CLASSNAME, DelChildRemovesLeafAndUpdatesCounts)
{
  XTREE_NODE<ELEM>* root = new XTREE_NODE<ELEM>(new int(1));
  XTREE_NODE<ELEM>* c1   = new XTREE_NODE<ELEM>(new int(2));
  XTREE_NODE<ELEM>* c2   = new XTREE_NODE<ELEM>(new int(3));

  root->AddChild(c1);
  root->AddChild(c2);

  XTREE<ELEM> tree(root);
  EXPECT_EQ(tree.GetNNodes(), (XDWORD)3);

  EXPECT_TRUE(root->DelChild(c1));

  EXPECT_EQ(root->GetNChildren(), 1);
  EXPECT_EQ(root->GetChild(0), c2);
  EXPECT_EQ(tree.GetNNodes(), (XDWORD)2);

  EXPECT_FALSE(root->DelChild(NULL));
}


TEST(UNITTESTS_XTREE_CLASSNAME, DeleteContentsFreesDataAndClearsChildren)
{
  XTREE_NODE<ELEM>* root = new XTREE_NODE<ELEM>(new int(1));
  XTREE_NODE<ELEM>* c1   = new XTREE_NODE<ELEM>(new int(2));
  XTREE_NODE<ELEM>* gc   = new XTREE_NODE<ELEM>(new int(3));

  root->AddChild(c1);
  c1->AddChild(gc);

  XTREE<ELEM> tree(root);

  EXPECT_TRUE(tree.DeleteContents());

  // The root node itself survives (DeleteContents only frees its DATA and
  // its descendant node structures), but its data pointer is now NULL and
  // its child subtree has been fully torn down and detached.
  EXPECT_TRUE(root->GetData() == NULL);
  EXPECT_EQ(root->GetNChildren(), 0);
  EXPECT_TRUE(tree.GetRoot() == root);

  // XTREE_NODE::DeleteContents() (XTree.h lines 152-168) always
  // `return true;` unconditionally -- it never surfaces whether the
  // nested children.DeleteContents() actually found anything to free, so
  // calling it again on an already-empty node still reports true.
  EXPECT_TRUE(root->DeleteContents());
}


TEST(UNITTESTS_XTREE_CLASSNAME, DeleteContentsOnEmptyTreeReturnsFalse)
{
  XTREE<ELEM> tree;
  EXPECT_FALSE(tree.DeleteContents());
  EXPECT_FALSE(tree.DeleteAll());
}


TEST(UNITTESTS_XTREE_CLASSNAME, DeleteAllDetachesChildrenFromRoot)
{
  // KNOWN CONCERN (XTree.h lines 170-182): XTREE_NODE::DeleteAll() recurses
  // into every child calling child->DeleteAll() and finally
  // `children.DeleteAll()` -- but XVECTOR::DeleteAll() (XVector.h lines
  // 293-307) only frees the vector's internal pointer ARRAY storage, it
  // never GEN_DELETEs the XTREE_NODE objects the pointers refer to. Unlike
  // DeleteContents() (which explicitly frees each child node via
  // XVECTOR::DeleteContents()), DeleteAll() as shipped appears to LEAK
  // every descendant node object rather than freeing them -- it only
  // resets the bookkeeping (GetNChildren() correctly reports 0 afterwards)
  // without releasing the underlying node memory. This test documents the
  // observable (post-condition) behavior only; the leak itself isn't
  // detectable from a plain gtest assertion.
  XTREE_NODE<ELEM>* root = new XTREE_NODE<ELEM>(new int(1));
  XTREE_NODE<ELEM>* c1   = new XTREE_NODE<ELEM>(new int(2));

  root->AddChild(c1);

  XTREE<ELEM> tree(root);
  EXPECT_TRUE(tree.DeleteAll());

  EXPECT_EQ(root->GetNChildren(), 0);
  EXPECT_TRUE(tree.GetRoot() == root);

  // Free root's own data explicitly (it was never touched by DeleteAll())
  // so this test doesn't itself leak beyond the bug already documented
  // above.
  root->DeleteContent();
}


TEST(UNITTESTS_XTREE_CLASSNAME, SetRootReplacesExistingRoot)
{
  XTREE_NODE<ELEM>* root1 = new XTREE_NODE<ELEM>(new int(1));
  XTREE<ELEM> tree(root1);

  XTREE_NODE<ELEM>* root2 = new XTREE_NODE<ELEM>(new int(2));
  tree.SetRoot(root2);

  EXPECT_EQ(tree.GetRoot(), root2);
  EXPECT_EQ(tree.GetNNodes(), (XDWORD)1);
}


}
#endif
