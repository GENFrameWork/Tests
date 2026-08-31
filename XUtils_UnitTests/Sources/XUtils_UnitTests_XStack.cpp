/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XStack.cpp
*
* @class      XUTILS_UNITTESTS_XSTACK
* @brief      XUtils unit tests for XStack class
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

#include "XUtils_UnitTests_XStack.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XStack.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XSTACK
{


TEST(UNITTEST_XSTACK_CLASSNAME, ConstructorIsEmpty)
{
  XSTACK<int> stack;

  EXPECT_TRUE(stack.IsEmpty());
  EXPECT_EQ(stack.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XSTACK_CLASSNAME, PushTopAndSize)
{
  XSTACK<int> stack;

  stack.Push(10);
  EXPECT_FALSE(stack.IsEmpty());
  EXPECT_EQ(stack.GetSize(), (XDWORD)1);
  EXPECT_EQ(stack.Top(), 10);

  stack.Push(20);
  EXPECT_EQ(stack.GetSize(), (XDWORD)2);
  EXPECT_EQ(stack.Top(), 20);
}


TEST(UNITTEST_XSTACK_CLASSNAME, PushAndPopLIFOOrderDistinctValues)
{
  XSTACK<int> stack;

  stack.Push(1);
  stack.Push(2);
  stack.Push(3);

  EXPECT_EQ(stack.Pop(), 3);
  EXPECT_EQ(stack.Pop(), 2);
  EXPECT_EQ(stack.Pop(), 1);
  EXPECT_TRUE(stack.IsEmpty());
}


TEST(UNITTEST_XSTACK_CLASSNAME, ClearEmptiesStack)
{
  // Clear() calls DeleteContents() (see XStack.h), which assumes T is a
  // pointer type (it does `if(element) delete element`) -- instantiating
  // XSTACK<int> and calling Clear() fails to compile, since `delete` on a
  // plain `int` is ill-formed. So this test uses a pointer element type,
  // matching the constraint Clear() actually imposes.
  XSTACK<int*> stack;

  stack.Push(GEN_NEW int(1));
  stack.Push(GEN_NEW int(2));
  stack.Push(GEN_NEW int(3));

  stack.Clear();

  EXPECT_TRUE(stack.IsEmpty());
  EXPECT_EQ(stack.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XSTACK_CLASSNAME, GetVectorEscapeHatch)
{
  XSTACK<int> stack;
  stack.Push(42);

  XVECTOR<int>* vector = stack.GetVector();

  EXPECT_NE((void*)vector, (void*)NULL);
  EXPECT_EQ(vector->GetSize(), (XDWORD)1);
  EXPECT_EQ(vector->GetLast(), 42);
}


TEST(UNITTEST_XSTACK_CLASSNAME, PopWithDuplicateValuesPreservesLIFOOrder)
{
  // FIXED (previously a known bug, now confirmed corrected in XStack.h Pop()): Pop() used to find
  // the true top via stack.GetLast() but then remove it from the backing XVECTOR via
  // stack.Delete(element), which deletes the FIRST element equal to `element` rather than the true
  // top index -- with duplicate values this silently corrupted LIFO order. Pop() now removes the
  // top via stack.DeleteLast() instead, which always targets the correct index regardless of
  // duplicate values. Verified here: after pushing 5, 3, 5 the array is [5,3,5]; popping now
  // correctly yields 5, 3, 5 in true LIFO order.
  XSTACK<int> stack;

  stack.Push(5);
  stack.Push(3);
  stack.Push(5);

  EXPECT_EQ(stack.Pop(), 5);
  EXPECT_EQ(stack.Pop(), 3);
  EXPECT_EQ(stack.Pop(), 5);
  EXPECT_TRUE(stack.IsEmpty());
}


}
#endif

