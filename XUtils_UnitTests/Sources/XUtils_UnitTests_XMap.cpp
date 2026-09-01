/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XMap.cpp
*
* @class      XUTILS_UNITTESTS_XMAP
* @brief      XUtils unit tests for XMAP class
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

#include "XUtils_UnitTests_XMap.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XMap.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XMAP
{


TEST(UNITTEST_XMAP_CLASSNAME, ConstructorIsEmpty)
{
  XMAP<int,int> map;

  EXPECT_TRUE(map.IsEmpty());
  EXPECT_EQ(map.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XMAP_CLASSNAME, AddAndGetByKey)
{
  XMAP<int,int> map;

  EXPECT_TRUE(map.Add(1, 100));
  EXPECT_TRUE(map.Add(2, 200));

  EXPECT_EQ(map.GetSize(), (XDWORD)2);
  EXPECT_EQ(map.Get(1), 100);
  EXPECT_EQ(map.Get(2), 200);
}


TEST(UNITTEST_XMAP_CLASSNAME, GetMissingKeyReturnsZeroCastElement)
{
  // Get() on a not-found key returns (ELEMENT)0 (XMap.h line 132) -- only
  // valid for ELEMENT types constructible/castable from the literal 0.
  XMAP<int,int> map;
  map.Add(1, 100);

  EXPECT_EQ(map.Get(999), 0);
}


TEST(UNITTEST_XMAP_CLASSNAME, OperatorBracketDelegatesToGet)
{
  XMAP<int,int> map;
  map.Add(5, 555);

  EXPECT_EQ(map[5], 555);
}


TEST(UNITTEST_XMAP_CLASSNAME, GetKeyElementByIndex)
{
  XMAP<int,int> map;
  map.Add(1, 100);
  map.Add(2, 200);

  EXPECT_EQ(map.GetKey(0), 1);
  EXPECT_EQ(map.GetElement(0), 100);
  EXPECT_EQ(map.FastGetKey(1), 2);
  EXPECT_EQ(map.FastGetElement(1), 200);
}


TEST(UNITTEST_XMAP_CLASSNAME, FindReturnsIndexOfKey)
{
  XMAP<int,int> map;
  map.Add(10, 1);
  map.Add(20, 2);

  EXPECT_EQ(map.Find(20), 1);
  EXPECT_EQ(map.Find(999), NOTFOUND);
}


TEST(UNITTEST_XMAP_CLASSNAME, KeysAreUniqueByDefault)
{
  // The ctor sets keys.SetIsMulti(false) (XMap.h line 57) -- a duplicate key
  // Add() is therefore rejected outright, and since Add() returns false
  // before elements.Add() ever runs, the two parallel vectors stay in sync.
  XMAP<int,int> map;

  EXPECT_TRUE(map.Add(1, 100));
  EXPECT_FALSE(map.Add(1, 200));

  EXPECT_EQ(map.GetSize(), (XDWORD)1);
  EXPECT_EQ(map.CountKey(1), 1);
}


TEST(UNITTEST_XMAP_CLASSNAME, SetIsMultiAllowsDuplicateKeys)
{
  XMAP<int,int> map;
  map.SetIsMulti(true);

  EXPECT_TRUE(map.Add(1, 100));
  EXPECT_TRUE(map.Add(1, 200));

  EXPECT_EQ(map.GetSize(), (XDWORD)2);
  EXPECT_EQ(map.CountKey(1), 2);
}


TEST(UNITTEST_XMAP_CLASSNAME, SetOverwritesElementForExistingKey)
{
  XMAP<int,int> map;
  map.Add(1, 100);

  EXPECT_TRUE(map.Set(1, 999));
  EXPECT_EQ(map.Get(1), 999);

  EXPECT_FALSE(map.Set(50, 0));
}


TEST(UNITTEST_XMAP_CLASSNAME, InsertAtSpecificIndex)
{
  XMAP<int,int> map;
  map.Add(1, 100);
  map.Add(2, 200);

  EXPECT_TRUE(map.Insert(0, 5, 555));

  EXPECT_EQ(map.GetSize(), (XDWORD)3);
  EXPECT_EQ(map.GetKey(0), 5);
  EXPECT_EQ(map.GetElement(0), 555);
}


TEST(UNITTEST_XMAP_CLASSNAME, DeleteByKeyRemovesBothParallelEntries)
{
  XMAP<int,int> map;
  map.Add(1, 100);
  map.Add(2, 200);

  EXPECT_TRUE(map.Delete(1));

  EXPECT_EQ(map.GetSize(), (XDWORD)1);
  EXPECT_EQ(map.keys.GetSize(), map.elements.GetSize());
  EXPECT_EQ(map.GetKey(0), 2);

  EXPECT_FALSE(map.Delete(999));
}


TEST(UNITTEST_XMAP_CLASSNAME, DeleteByKeyAndElementPair)
{
  XMAP<int,int> map;
  map.SetIsMulti(true);
  map.Add(1, 100);
  map.Add(1, 200);

  EXPECT_TRUE(map.Delete(1, 200));

  EXPECT_EQ(map.GetSize(), (XDWORD)1);
  EXPECT_EQ(map.GetElement(0), 100);
}


TEST(UNITTEST_XMAP_CLASSNAME, DeleteAllEmptiesMap)
{
  XMAP<int,int> map;
  map.Add(1, 100);
  map.Add(2, 200);

  EXPECT_TRUE(map.DeleteAll());
  EXPECT_TRUE(map.IsEmpty());
  EXPECT_EQ(map.GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XMAP_CLASSNAME, PublicKeysAndElementsMembersCanDesynchronize)
{
  // keys/elements are public members, not encapsulated (XMap.h lines 218-219)
  // -- external code can bypass Add()/Delete() entirely and manipulate one
  // vector without the other, breaking the class's implicit "same size"
  // invariant. This documents that gap rather than a specific method bug.
  XMAP<int,int> map;
  map.Add(1, 100);

  map.keys.Add(2);   // elements not updated to match

  EXPECT_NE(map.keys.GetSize(), map.elements.GetSize());
  EXPECT_EQ(map.GetSize(), (XDWORD)2);   // GetSize() reports keys.GetSize() only
}


TEST(UNITTEST_XMAP_CLASSNAME, AddInLimitGetterAndSetter)
{
  XMAP<int,int> map;

  EXPECT_TRUE(map.SetAddInLimit(4));
  EXPECT_EQ(map.GetAddInLimit(), 4);
}


// NOTE: XMAP's private CreateArraySize(int) (XMap.h lines 228-236) calls
// keys.CreateArraySize()/elements.CreateArraySize() -- but XVECTOR<T> has no
// such method at all. It is unreachable dead code today (private, and never
// called from within XMap.h itself), so it does not block compiling or
// testing XMAP as shipped; it would only become a build error if some future
// change started calling it. Not exercised here since it is not reachable.


}
#endif

