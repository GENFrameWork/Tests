/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XInterpolator.cpp
*
* @class      XUTILS_UNITTESTS_XINTERPOLATOR
* @brief      XUtils unit tests for XInterpolator class
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

#include "XUtils_UnitTests_XInterpolator.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XInterpolator.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XINTERPOLATOR
{

TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, ConstructorDefaultsToAbsoluteType)
{
  XINTERPOLATOR interpolator;

  EXPECT_EQ(interpolator.GetType(), XINTERPOLATOR_TYPE_ABSOLUTE);
  EXPECT_EQ(interpolator.GetFactorType(), XINTERPOLATOR_FACTOR_LINEAR);
  EXPECT_EQ(interpolator.GetMask(), (XDWORD)XINTERPOLATOR_MASK_ALL);
  EXPECT_EQ(interpolator.GetLimitFlags(), (XINTERPOLATOR_LIMITS)XINTERPOLATOR_LIMITS_NONE);
  EXPECT_FLOAT_EQ(interpolator.GetCarry(), 0.0f);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, ConstructorWithExplicitType)
{
  XINTERPOLATOR interpolator(XINTERPOLATOR_TYPE_RELATIVE);

  EXPECT_EQ(interpolator.GetType(), XINTERPOLATOR_TYPE_RELATIVE);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, SetTypeAndGetType)
{
  XINTERPOLATOR interpolator;

  interpolator.SetType(XINTERPOLATOR_TYPE_LIMIT);

  EXPECT_EQ(interpolator.GetType(), XINTERPOLATOR_TYPE_LIMIT);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, SetModeAndGetMode)
{
  XINTERPOLATOR interpolator;

  interpolator.SetMode(XINTERPOLATOR_LIMITMODE_BOTHWAYS);

  EXPECT_EQ(interpolator.GetMode(), XINTERPOLATOR_LIMITMODE_BOTHWAYS);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, SetAndGetBatchAccessor)
{
  XINTERPOLATOR interpolator;
  XDWORD        current;
  XDWORD        target;
  float         speed;

  interpolator.Set(10, 20, 1.5f);
  interpolator.Get(current, target, speed);

  EXPECT_EQ(current, (XDWORD)10);
  EXPECT_EQ(target,  (XDWORD)20);
  EXPECT_FLOAT_EQ(speed, 1.5f);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, SetCurrentAndSetTargetAgreeOnTarget)
{
  // The report flags two different-looking "set target" entry points -- the batch Set() and the
  // standalone SetTarget() -- both mutating the same 'target' member; verify they do not disagree.
  XINTERPOLATOR interpolator;

  interpolator.Set(0, 50, 1.0f);
  EXPECT_EQ(interpolator.GetTarget(), (XDWORD)50);

  interpolator.SetTarget(75);
  EXPECT_EQ(interpolator.GetTarget(), (XDWORD)75);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, SetCurrentClampedByMaximunAndMinimunLimits)
{
  XINTERPOLATOR interpolator;

  interpolator.SetMultiplicator(1);
  interpolator.SetMaximun(100);
  interpolator.SetMinimun(10);
  interpolator.SetLimitFlags(XINTERPOLATOR_LIMITS_RANGE);

  interpolator.SetCurrent(500);
  EXPECT_EQ(interpolator.GetCurrent(), (XDWORD)100);

  interpolator.SetCurrent(1);
  EXPECT_EQ(interpolator.GetCurrent(), (XDWORD)10);

  interpolator.SetCurrent(50);
  EXPECT_EQ(interpolator.GetCurrent(), (XDWORD)50);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, SetTargetClampedByMaximunAndMinimunLimits)
{
  XINTERPOLATOR interpolator;

  interpolator.SetMaximun(100);
  interpolator.SetMinimun(10);
  interpolator.SetLimitFlags(XINTERPOLATOR_LIMITS_RANGE);

  interpolator.SetTarget(500);
  EXPECT_EQ(interpolator.GetTarget(), (XDWORD)100);

  interpolator.SetTarget(1);
  EXPECT_EQ(interpolator.GetTarget(), (XDWORD)10);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, GetAndSetMaximunAndMinimun)
{
  // Deliberately replicating the house misspelling "Maximun"/"Minimun" -- this is the real,
  // shipped public API and must be used verbatim, not "corrected".
  XINTERPOLATOR interpolator;

  interpolator.SetMaximun(42);
  interpolator.SetMinimun(7);

  EXPECT_EQ(interpolator.GetMaximun(), (XDWORD)42);
  EXPECT_EQ(interpolator.GetMinimun(), (XDWORD)7);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, GetAndSetMultiplicator)
{
  XINTERPOLATOR interpolator;

  interpolator.SetMultiplicator(4);

  EXPECT_EQ(interpolator.GetMultiplicator(), (XDWORD)4);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, GetAndSetFactorType)
{
  XINTERPOLATOR interpolator;

  interpolator.SetFactorType(XINTERPOLATOR_FACTOR_RELATIVE);

  EXPECT_EQ(interpolator.GetFactorType(), XINTERPOLATOR_FACTOR_RELATIVE);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, GetAndSetLimitFlags)
{
  XINTERPOLATOR interpolator;

  interpolator.SetLimitFlags(XINTERPOLATOR_LIMITS_MAXIMUN);

  EXPECT_EQ(interpolator.GetLimitFlags(), (XINTERPOLATOR_LIMITS)XINTERPOLATOR_LIMITS_MAXIMUN);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, SetMaskAndGetMask)
{
  XINTERPOLATOR interpolator;

  EXPECT_TRUE(interpolator.SetMask(XINTERPOLATOR_MASK_CURRENT | XINTERPOLATOR_MASK_TARGET));

  EXPECT_EQ(interpolator.GetMask(), (XDWORD)(XINTERPOLATOR_MASK_CURRENT | XINTERPOLATOR_MASK_TARGET));
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, GetCarryAndSetCarry)
{
  XINTERPOLATOR interpolator;

  interpolator.SetCarry(0.25f);

  EXPECT_FLOAT_EQ(interpolator.GetCarry(), 0.25f);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, CopyFromAndCopyToAreSymmetric)
{
  XINTERPOLATOR source(XINTERPOLATOR_TYPE_LIMIT);
  XINTERPOLATOR destination;

  source.SetMode(XINTERPOLATOR_LIMITMODE_INCREMENTAL);
  source.Set(30, 90, 2.0f);
  source.SetMaximun(200);
  source.SetMinimun(5);
  source.SetLimitFlags(XINTERPOLATOR_LIMITS_RANGE);
  source.SetFactorType(XINTERPOLATOR_FACTOR_RELATIVE);

  EXPECT_TRUE(destination.CopyFrom(source));

  EXPECT_EQ(destination.GetType(), XINTERPOLATOR_TYPE_LIMIT);
  EXPECT_EQ(destination.GetMode(), XINTERPOLATOR_LIMITMODE_INCREMENTAL);
  EXPECT_EQ(destination.GetTarget(), (XDWORD)90);
  EXPECT_EQ(destination.GetMaximun(), (XDWORD)200);
  EXPECT_EQ(destination.GetMinimun(), (XDWORD)5);
  EXPECT_EQ(destination.GetFactorType(), XINTERPOLATOR_FACTOR_RELATIVE);

  XINTERPOLATOR roundtrip;

  EXPECT_TRUE(source.CopyTo(roundtrip));

  EXPECT_EQ(roundtrip.GetType(), XINTERPOLATOR_TYPE_LIMIT);
  EXPECT_EQ(roundtrip.GetTarget(), (XDWORD)90);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, OperatorAssignCopiesState)
{
  XINTERPOLATOR source(XINTERPOLATOR_TYPE_RELATIVE);
  XINTERPOLATOR destination;

  source.Set(1, 2, 3.0f);

  destination = source;

  EXPECT_EQ(destination.GetType(), XINTERPOLATOR_TYPE_RELATIVE);
  EXPECT_EQ(destination.GetTarget(), (XDWORD)2);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, UpdateAbsoluteClampsCurrentDownToTarget)
{
  XINTERPOLATOR interpolator(XINTERPOLATOR_TYPE_ABSOLUTE);

  interpolator.Set(100, 40, 0.0f);

  EXPECT_TRUE(interpolator.Update(0));

  EXPECT_EQ(interpolator.GetCurrent(), (XDWORD)40);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, UpdateAbsoluteLeavesCurrentBelowTargetUnchanged)
{
  // Source note: XINTERPOLATOR::Update()'s ABSOLUTE/RELATIVE branch also has a dead
  // "if(current < 0) current = 0;" check (XInterpolator.cpp) -- 'current' is an unsigned XDWORD,
  // so that comparison can never be true; not exercised here since it can never trigger.
  XINTERPOLATOR interpolator(XINTERPOLATOR_TYPE_ABSOLUTE);

  interpolator.Set(10, 40, 0.0f);

  EXPECT_TRUE(interpolator.Update(0));

  EXPECT_EQ(interpolator.GetCurrent(), (XDWORD)10);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, UpdateLimitIncrementalSnapsToTargetWhenReached)
{
  XINTERPOLATOR interpolator(XINTERPOLATOR_TYPE_LIMIT);

  interpolator.SetFactorType(XINTERPOLATOR_FACTOR_NONE);
  interpolator.SetMode(XINTERPOLATOR_LIMITMODE_INCREMENTAL);
  interpolator.Set(10, 5, 0.0f);

  EXPECT_TRUE(interpolator.Update(0));

  EXPECT_EQ(interpolator.GetCurrent(), (XDWORD)5);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, UpdateLimitDecrementalSnapsToTargetWhenReached)
{
  XINTERPOLATOR interpolator(XINTERPOLATOR_TYPE_LIMIT);

  interpolator.SetFactorType(XINTERPOLATOR_FACTOR_NONE);
  interpolator.SetMode(XINTERPOLATOR_LIMITMODE_DECREMENTAL);
  interpolator.Set(5, 10, 0.0f);

  EXPECT_TRUE(interpolator.Update(0));

  EXPECT_EQ(interpolator.GetCurrent(), (XDWORD)10);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, InterpolateLinearReachesMidpointThenTarget)
{
  XINTERPOLATOR interpolator(XINTERPOLATOR_TYPE_LIMIT);

  interpolator.SetFactorType(XINTERPOLATOR_FACTOR_LINEAR);
  interpolator.SetMode(XINTERPOLATOR_LIMITMODE_INCREMENTAL);
  interpolator.Set(0, 100, 50.0f);

  // fdelta = delta/100.0 -> delta=100 gives fdelta=1.0, inc = speed*fdelta = 50 -> midpoint.
  EXPECT_TRUE(interpolator.Update(100));
  EXPECT_EQ(interpolator.GetCurrent(), (XDWORD)50);

  // A second identical tick reaches (and clamps at) the target.
  EXPECT_TRUE(interpolator.Update(100));
  EXPECT_EQ(interpolator.GetCurrent(), (XDWORD)100);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, InterpolateLinearWithZeroDeltaLeavesCurrentUnchanged)
{
  XINTERPOLATOR interpolator(XINTERPOLATOR_TYPE_LIMIT);

  interpolator.SetFactorType(XINTERPOLATOR_FACTOR_LINEAR);
  interpolator.SetMode(XINTERPOLATOR_LIMITMODE_INCREMENTAL);
  interpolator.Set(0, 100, 50.0f);

  EXPECT_TRUE(interpolator.Update(0));
  EXPECT_EQ(interpolator.GetCurrent(), (XDWORD)0);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, SerializeAndDeSerializeBufferRoundTrip)
{
  XINTERPOLATOR source(XINTERPOLATOR_TYPE_LIMIT);
  XBUFFER       buffer;

  source.SetMode(XINTERPOLATOR_LIMITMODE_BOTHWAYS);
  source.Set(11, 22, 3.5f);
  source.SetMaximun(99);
  source.SetMinimun(1);
  source.SetMultiplicator(2);
  source.SetFactorType(XINTERPOLATOR_FACTOR_RELATIVE);
  source.SetMask(XINTERPOLATOR_MASK_ALL);

  EXPECT_TRUE(source.DeSerialize(&buffer));

  XINTERPOLATOR destination;

  destination.SetMask(XINTERPOLATOR_MASK_ALL);

  EXPECT_TRUE(destination.Serialize(&buffer));

  EXPECT_EQ(destination.GetTarget(), (XDWORD)22);
  EXPECT_FLOAT_EQ(destination.GetSpeed(), 3.5f);
  EXPECT_EQ(destination.GetMaximun(), (XDWORD)99);
  EXPECT_EQ(destination.GetMinimun(), (XDWORD)1);
  EXPECT_EQ(destination.GetMultiplicator(), (XDWORD)2);
  EXPECT_EQ(destination.GetFactorType(), XINTERPOLATOR_FACTOR_RELATIVE);
}


TEST(UNITTEST_XINTERPOLATOR_CLASSNAME, SerializeThroughBaseXSerializablePointerDoesNotUseBufferMethod)
{
  // Source concern (analysis report): XINTERPOLATOR::Serialize(XBUFFER*)/DeSerialize(XBUFFER*)
  // const are a separate, non-virtual mechanism from the inherited XSERIALIZABLE::Serialize()
  // (no-args, virtual) -- calling through a base XSERIALIZABLE* invokes the EMPTY base stub, not
  // this class's real buffer-based implementation. The base stub (XSerializable.cpp) returns
  // false whenever no XSERIALIZATIONMETHOD has been attached, which is the case here -- proving
  // the shadowing is real, not merely theoretical.
  XINTERPOLATOR   interpolator(XINTERPOLATOR_TYPE_ABSOLUTE);
  XSERIALIZABLE*  baseptr = &interpolator;

  EXPECT_FALSE(baseptr->Serialize());
}


}
#endif
