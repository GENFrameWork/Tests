/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XMemory_Control.cpp
*
* @class      XUTILS_UNITTESTS_XMEMORY_CONTROL
* @brief      XUtils unit tests for XMemory_Control class
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

#include "XUtils_UnitTests_XMemory_Control.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XMemory_Control.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


// NOTE: XMEMORY_CONTROL (and the global `XMemory_Control` object it declares) only exists when
// XMEMORY_CONTROL_ACTIVE is defined - this is the current desktop test build's configuration
// (confirmed via the build's compiler -D flags), so these tests are safe to compile here. If this
// build is ever reconfigured without XMEMORY_CONTROL_ACTIVE, this whole file must be skipped, the
// same way XFEEDBACK_CONTROL was for XFEEDBACK_CONTROL_ACTIVE.
#ifdef GOOGLETEST_ACTIVE
#ifdef XMEMORY_CONTROL_ACTIVE
namespace TEST_XMEMORY_CONTROL
{


TEST(UNITTEST_XMEMORY_CONTROL_CLASSNAME, ActivateTogglesIsActiveAndReportsNoChange)
{
  bool originalstate = XMemory_Control.IsActive();

  // Activate() documents returning false when the requested state equals the current state.
  EXPECT_FALSE(XMemory_Control.Activate(originalstate));
  EXPECT_EQ(XMemory_Control.IsActive(), originalstate);

  // A real state change must succeed and be reflected by IsActive().
  EXPECT_TRUE(XMemory_Control.Activate(!originalstate));
  EXPECT_EQ(XMemory_Control.IsActive(), !originalstate);

  // Restore the original global state so later tests are unaffected.
  XMemory_Control.Activate(originalstate);
  EXPECT_EQ(XMemory_Control.IsActive(), originalstate);
}


TEST(UNITTEST_XMEMORY_CONTROL_CLASSNAME, AssignZeroSizeReturnsNull)
{
  bool originalstate = XMemory_Control.IsActive();

  EXPECT_EQ(XMemory_Control.Assign(0, __FILE__, __LINE__), (void*)NULL);

  EXPECT_EQ(XMemory_Control.IsActive(), originalstate);
}


TEST(UNITTEST_XMEMORY_CONTROL_CLASSNAME, FreeNullIsSafeNoOp)
{
  XDWORD usedbefore    = XMemory_Control.GetUsed();
  XDWORD nassignsbefore = XMemory_Control.GetNAssigns();

  XMemory_Control.Free(NULL);

  EXPECT_EQ(XMemory_Control.GetUsed(), usedbefore);
  EXPECT_EQ(XMemory_Control.GetNAssigns(), nassignsbefore);
}


TEST(UNITTEST_XMEMORY_CONTROL_CLASSNAME, AssignAndFreeTrackUsageWhileActive)
{
  bool originalstate = XMemory_Control.IsActive();
  if(!originalstate) XMemory_Control.Activate(true);

  XDWORD usedbefore     = XMemory_Control.GetUsed();
  XDWORD nassignsbefore = XMemory_Control.GetNAssigns();

  void* block = XMemory_Control.Assign(64, __FILE__, __LINE__);
  EXPECT_NE(block, (void*)NULL);

  EXPECT_EQ(XMemory_Control.GetUsed(), usedbefore + 64);
  EXPECT_EQ(XMemory_Control.GetNAssigns(), nassignsbefore + 1);

  XMemory_Control.Free(block);

  EXPECT_EQ(XMemory_Control.GetUsed(), usedbefore);
  EXPECT_EQ(XMemory_Control.GetNAssigns(), nassignsbefore);

  // Restore original activation state exactly as found.
  if(!originalstate) XMemory_Control.Activate(false);
  EXPECT_EQ(XMemory_Control.IsActive(), originalstate);
}


TEST(UNITTEST_XMEMORY_CONTROL_CLASSNAME, DisplayAllIsSafeAndAlwaysReportsTrue)
{
  // DisplayAll's implementation (XMemory_Control.cpp) computes a leak count internally but its
  // final `return true;` is unconditional - the return value never actually reflects whether
  // leaks were found. This test captures that real (if surprising) behavior rather than the
  // return value's apparent intent.
  EXPECT_TRUE(XMemory_Control.DisplayAll(false));
  EXPECT_TRUE(XMemory_Control.DisplayAll(true));
}


}
#endif
#endif
