/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XFSMachine.cpp
*
* @class      UNITTESTS_XUTILS_XFSMACHINE
* @brief      XUtils unit tests for XFSMachine class
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

#include "UnitTests_XUtils_XFSMachine.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XFSMachine.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFSMACHINE
{

// -----------------------------------------------------------------------------------------------
// NOTE on XFSMACHINESTATE internals (read from XFSMachine.cpp):
//   - GetOutput() / AddTransition() use outputstates[c]==0 as the "slot is empty" sentinel, and
//     GetOutput() *stops scanning* at the first empty slot. So an output/target state ID of 0,
//     or relying on a slot beyond the first "hole", will not behave as a normal transition table.
//     All tests below therefore use non-zero state IDs and event/input values.
//   - The varargs XFSMACHINE::AddState(state,event,tostate,...) reads pairs of (event,tostate)
//     ints until it sees the sentinel XFSMACHINESTATE_EVENTDEFEND (-1). The first (event,tostate)
//     pair is the *required* 2nd/3rd arguments; anything else must be passed in (event,tostate)
//     pairs followed by the sentinel.
// -----------------------------------------------------------------------------------------------


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, ConstructorSetsInitialCurrentState)
{
  XFSMACHINE fsm(7);

  EXPECT_EQ(fsm.GetCurrentState(), 7);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, SetAndGetCurrentState)
{
  XFSMACHINE fsm(1);

  fsm.SetCurrentState(3);
  EXPECT_EQ(fsm.GetCurrentState(), 3);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, SetAndGetEvent)
{
  XFSMACHINE fsm(1);

  EXPECT_EQ(fsm.GetEvent(), 0);
  EXPECT_TRUE(fsm.SetEvent(42));
  EXPECT_EQ(fsm.GetEvent(), 42);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, AddStateObjectAndGetStateRoundTrip)
{
  XFSMACHINE fsm(1);

  XFSMACHINESTATE* state = GEN_NEW XFSMACHINESTATE(1, 2);
  EXPECT_TRUE(state->AddTransition(10, 2));

  EXPECT_TRUE(fsm.AddState(state));
  EXPECT_EQ(fsm.GetState(1), state);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, AddStateDuplicateIDIsRejectedAndNotLeaked)
{
  XFSMACHINE fsm(1);

  XFSMACHINESTATE* state1 = GEN_NEW XFSMACHINESTATE(5, 1);
  EXPECT_TRUE(fsm.AddState(state1));

  XFSMACHINESTATE* state2 = GEN_NEW XFSMACHINESTATE(5, 1);
  EXPECT_FALSE(fsm.AddState(state2));

  // The rejected duplicate is the caller's responsibility; the map still only reports the first.
  EXPECT_EQ(fsm.GetState(5), state1);

  GEN_DELETE state2;
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, GetStateUnknownIDReturnsNull)
{
  XFSMACHINE fsm(1);

  EXPECT_EQ(fsm.GetState(999), (XFSMACHINESTATE*)NULL);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, DeleteStateRemovesItAndFreesMemory)
{
  XFSMACHINE fsm(1);

  XFSMACHINESTATE* state = GEN_NEW XFSMACHINESTATE(2, 1);
  EXPECT_TRUE(fsm.AddState(state));

  EXPECT_TRUE(fsm.DeleteState(2));
  EXPECT_EQ(fsm.GetState(2), (XFSMACHINESTATE*)NULL);

  // Deleting an already-removed state fails.
  EXPECT_FALSE(fsm.DeleteState(2));
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, DeleteAllStatesEmptiesMachine)
{
  XFSMACHINE fsm(1);

  XFSMACHINESTATE* state1 = GEN_NEW XFSMACHINESTATE(1, 1);
  XFSMACHINESTATE* state2 = GEN_NEW XFSMACHINESTATE(2, 1);
  EXPECT_TRUE(fsm.AddState(state1));
  EXPECT_TRUE(fsm.AddState(state2));

  EXPECT_TRUE(fsm.DeleteAllStates());
  EXPECT_EQ(fsm.GetState(1), (XFSMACHINESTATE*)NULL);
  EXPECT_EQ(fsm.GetState(2), (XFSMACHINESTATE*)NULL);

  // Nothing left to delete.
  EXPECT_FALSE(fsm.DeleteAllStates());
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, StateTransitionFollowsRegisteredTransition)
{
  XFSMACHINE fsm(1);

  XFSMACHINESTATE* state1 = GEN_NEW XFSMACHINESTATE(1, 2);
  EXPECT_TRUE(state1->AddTransition(10, 2));  // on input 10, go to state 2

  XFSMACHINESTATE* state2 = GEN_NEW XFSMACHINESTATE(2, 1);
  EXPECT_TRUE(state2->AddTransition(20, 1));  // on input 20, go back to state 1

  EXPECT_TRUE(fsm.AddState(state1));
  EXPECT_TRUE(fsm.AddState(state2));

  EXPECT_EQ(fsm.StateTransition(10), 2);
  EXPECT_EQ(fsm.GetCurrentState(), 2);

  EXPECT_EQ(fsm.StateTransition(20), 1);
  EXPECT_EQ(fsm.GetCurrentState(), 1);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, StateTransitionWithUnmatchedInputStaysOnSameState)
{
  XFSMACHINE fsm(1);

  XFSMACHINESTATE* state1 = GEN_NEW XFSMACHINESTATE(1, 1);
  EXPECT_TRUE(state1->AddTransition(10, 2));

  EXPECT_TRUE(fsm.AddState(state1));

  // XFSMACHINESTATE::GetOutput defaults to returning stateID itself when no input matches.
  EXPECT_EQ(fsm.StateTransition(99), 1);
  EXPECT_EQ(fsm.GetCurrentState(), 1);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, StateTransitionFromUnregisteredCurrentStateResetsToZero)
{
  XFSMACHINE fsm(42);  // no state with ID 42 was ever registered

  EXPECT_EQ(fsm.StateTransition(1), 0);
  EXPECT_EQ(fsm.GetCurrentState(), 0);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, AddSecuencialStatesBuildsIdentityTransitions)
{
  XFSMACHINE fsm(1);

  EXPECT_TRUE(fsm.AddSecuencialStates(1, 3));

  XFSMACHINESTATE* state = fsm.GetState(1);
  ASSERT_NE(state, (XFSMACHINESTATE*)NULL);

  // AddSecuencialStates wires transition c->c for c in [0, maxsecuencialtransitions).
  EXPECT_EQ(state->GetOutput(1), 1);
  EXPECT_EQ(state->GetOutput(2), 2);
}


// FIXED (previously a known bug, now confirmed corrected in XFSMachine.cpp): DeleteTransition()
// used to zero the deleted slot and then try to compact the tail by shifting
// inputs[c+1]/outputstates[c+1] into inputs[c]/outputstates[c], but its shift loop condition
// checked `if(!outputstates[c]) break` using the slot it had JUST zeroed, so it always broke
// immediately on the very first iteration and never actually shifted anything -- silently
// orphaning every transition stored in a later slot. The shift loop no longer re-checks the
// sentinel on the slot it is overwriting, so compaction now genuinely moves every later slot
// down by one, and no transition is ever left unreachable behind a zeroed hole.
TEST(UNITTESTS_XFSMACHINE_CLASSNAME, DeleteTransitionOfNonLastSlotCompactsLaterTransitions)
{
  XFSMACHINESTATE state(1, 2);

  EXPECT_TRUE(state.AddTransition(10, 2));  // slot 0
  EXPECT_TRUE(state.AddTransition(20, 3));  // slot 1

  EXPECT_TRUE(state.DeleteTransition(2));   // deletes slot 0 (input 10 -> output 2)

  // Input 10 no longer maps to output 2 (falls back to the state's own ID) -- expected.
  EXPECT_EQ(state.GetOutput(10), 1);

  // Input 20 -> output 3 was compacted into slot 0 and remains fully reachable.
  EXPECT_EQ(state.GetOutput(20), 3);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, DeleteTransitionOfLastSlotWorksCorrectly)
{
  // Deleting the LAST populated slot never needed compaction (there is nothing after it to
  // shift), so this is unaffected by the fix above and behaves exactly as before.
  XFSMACHINESTATE state(1, 2);

  EXPECT_TRUE(state.AddTransition(10, 2));  // slot 0
  EXPECT_TRUE(state.AddTransition(20, 3));  // slot 1

  EXPECT_TRUE(state.DeleteTransition(3));   // deletes slot 1 (input 20 -> output 3)

  EXPECT_EQ(state.GetOutput(10), 2);        // untouched
  EXPECT_EQ(state.GetOutput(20), 1);        // gone, falls back to state's own ID
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, AddStateVarargsWithOnlyRequiredTripletCreatesSingleTransition)
{
  XFSMACHINE fsm(1);

  // AddState(state=1, event=10, tostate=2, <sentinel>): no extra pairs beyond the required triplet.
  EXPECT_TRUE(fsm.AddState(1, 10, 2, XFSMACHINESTATE_EVENTDEFEND));

  XFSMACHINESTATE* state = fsm.GetState(1);
  ASSERT_NE(state, (XFSMACHINESTATE*)NULL);
  EXPECT_EQ(state->GetOutput(10), 2);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, AddStateVarargsWithExtraPairsAddsAllTransitions)
{
  XFSMACHINE fsm(1);

  // AddState(state=5, event=10, tostate=6, then extra pair (20,7), then sentinel):
  // this must register BOTH (10->6) and (20->7) on state 5.
  EXPECT_TRUE(fsm.AddState(5, 10, 6, 20, 7, XFSMACHINESTATE_EVENTDEFEND));

  XFSMACHINESTATE* state = fsm.GetState(5);
  ASSERT_NE(state, (XFSMACHINESTATE*)NULL);
  EXPECT_EQ(state->GetOutput(10), 6);
  EXPECT_EQ(state->GetOutput(20), 7);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, AddStateVarargsWithOddExtraArgCountFails)
{
  XFSMACHINE fsm(1);

  // Exactly one extra int (30) before the sentinel: an incomplete (event,tostate) pair,
  // so narg is odd and AddState must reject it.
  EXPECT_FALSE(fsm.AddState(1, 10, 2, 30, XFSMACHINESTATE_EVENTDEFEND));

  EXPECT_EQ(fsm.GetState(1), (XFSMACHINESTATE*)NULL);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, CheckTransitionReturnsTrueOnRealChangeWithEventOutParam)
{
  XFSMACHINE fsm(1);

  XFSMACHINESTATE* state1 = GEN_NEW XFSMACHINESTATE(1, 1);
  EXPECT_TRUE(state1->AddTransition(10, 2));
  EXPECT_TRUE(fsm.AddState(state1));

  fsm.SetEvent(10);

  int outevent = 0;
  EXPECT_TRUE(fsm.CheckTransition(outevent));
  EXPECT_EQ(outevent, 10);
  EXPECT_EQ(fsm.GetCurrentState(), 2);
  // CheckTransition always clears the pending event afterward.
  EXPECT_EQ(fsm.GetEvent(), 0);
}


TEST(UNITTESTS_XFSMACHINE_CLASSNAME, CheckTransitionReturnsFalseWhenStateDoesNotChange)
{
  XFSMACHINE fsm(1);

  XFSMACHINESTATE* state1 = GEN_NEW XFSMACHINESTATE(1, 1);
  EXPECT_TRUE(state1->AddTransition(10, 2));
  EXPECT_TRUE(fsm.AddState(state1));

  fsm.SetEvent(99);  // unmatched input -> GetOutput falls back to the same state ID

  EXPECT_FALSE(fsm.CheckTransition());
  EXPECT_EQ(fsm.GetCurrentState(), 1);
}


}
#endif
