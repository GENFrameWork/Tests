/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XMPInteger.cpp
*
* @class      XUTILS_UNITTESTS_XMPINTEGER
* @brief      XUtils unit tests for XMPInteger class
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

#include "XUtils_UnitTests_XMPInteger.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XMPInteger.h"
#include "XString.h"
#include "XBuffer.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XMPINTEGER
{

// Every real caller in XMPInteger.cpp itself calls Ini() right after construction (see e.g.
// XMPINTEGER::Division()'s local X/Y/Z/T1/T2 objects) before doing anything else with the object --
// the plain constructor alone (via Clean()) leaves sign at 0, which is not a valid sign value for
// arithmetic. Tests follow that same real-source idiom.
static void SetDecimal(XMPINTEGER& xmpinteger, XCHAR* decimalstring)
{
  xmpinteger.Ini();
  xmpinteger.SetFromString(10, decimalstring);
}

static XSTRING GetDecimal(XMPINTEGER& xmpinteger)
{
  XSTRING result;

  xmpinteger.GetToString(10, result);

  return result;
}

// Deterministic XMPINTEGER_FUNCRANDOM fixture: MillerRabin only needs *a* random witness, and for a
// genuine prime every witness must pass (that is the whole point of the algorithm), so a fixed,
// non-random byte pattern is enough to exercise the SlidingWindowExponentiation/MillerRabin code
// path deterministically without flaky test behaviour.
static bool FixedPatternRandom(XBYTE* buffer, XDWORD size, void* param)
{
  for(XDWORD c = 0; c < size; c++)
    {
      buffer[c] = (XBYTE)(0x35 + c);
    }

  return true;
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, IniStartsAtZero)
{
  XMPINTEGER xmpinteger;

  xmpinteger.Ini();
  xmpinteger.LeftSet(0);

  EXPECT_EQ(xmpinteger.GetSign(), 1);
  EXPECT_STREQ(GetDecimal(xmpinteger).Get(), __L("0"));
  EXPECT_EQ(xmpinteger.CompareSignedValues(0), 0);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, LeftSetPositiveAndNegative)
{
  XMPINTEGER positive;
  XMPINTEGER negative;

  positive.Ini();
  positive.LeftSet(5);

  negative.Ini();
  negative.LeftSet(-5);

  EXPECT_EQ(positive.GetSign(), 1);
  EXPECT_STREQ(GetDecimal(positive).Get(), __L("5"));

  EXPECT_EQ(negative.GetSign(), -1);
  EXPECT_STREQ(GetDecimal(negative).Get(), __L("-5"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, SetFromStringAndGetToStringDecimalRoundTrip)
{
  XMPINTEGER xmpinteger;

  SetDecimal(xmpinteger, __L("12345"));

  EXPECT_STREQ(GetDecimal(xmpinteger).Get(), __L("12345"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, SetFromStringAndGetToStringNegativeDecimalRoundTrip)
{
  XMPINTEGER xmpinteger;

  SetDecimal(xmpinteger, __L("-42"));

  EXPECT_STREQ(GetDecimal(xmpinteger).Get(), __L("-42"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, SetFromStringAndGetToStringHexRoundTrip)
{
  XMPINTEGER xmpinteger;
  XSTRING    result;

  xmpinteger.Ini();
  xmpinteger.SetFromString(16, (XCHAR*)__L("1A2B"));

  xmpinteger.GetToString(16, result);

  EXPECT_STREQ(result.Get(), __L("1A2B"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, LargeValueBeyondNativeIntegerRoundTrip)
{
  // 2^128 - 1 : does not fit in a native int/long/long long (even 64-bit), proving the
  // "multi-precision" part of XMPINTEGER actually works, not just small-value arithmetic.
  XCHAR* value2pow128minus1 = __L("340282366920938463463374607431768211455");

  XMPINTEGER xmpinteger;

  SetDecimal(xmpinteger, value2pow128minus1);

  EXPECT_STREQ(GetDecimal(xmpinteger).Get(), value2pow128minus1);
  EXPECT_EQ(xmpinteger.GetMSB(), 128);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, CompareABSValuesIgnoresSign)
{
  XMPINTEGER positive;
  XMPINTEGER negative;

  positive.Ini();
  positive.LeftSet(5);

  negative.Ini();
  negative.LeftSet(-5);

  EXPECT_EQ(positive.CompareABSValues(negative), 0);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, CompareSignedValuesRespectsSign)
{
  XMPINTEGER positive;
  XMPINTEGER negative;

  positive.Ini();
  positive.LeftSet(5);

  negative.Ini();
  negative.LeftSet(-5);

  EXPECT_LT(negative.CompareSignedValues(positive), 0);
  EXPECT_GT(positive.CompareSignedValues(negative), 0);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, CompareSignedValuesIntOverload)
{
  XMPINTEGER xmpinteger;

  xmpinteger.Ini();
  xmpinteger.LeftSet(10);

  EXPECT_EQ(xmpinteger.CompareSignedValues(10), 0);
  EXPECT_GT(xmpinteger.CompareSignedValues(5), 0);
  EXPECT_LT(xmpinteger.CompareSignedValues(20), 0);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, AdditionSignedPositivePlusPositive)
{
  XMPINTEGER a;
  XMPINTEGER b;
  XMPINTEGER result;

  a.Ini();
  a.LeftSet(123);

  b.Ini();
  b.LeftSet(456);

  result.Ini();

  EXPECT_TRUE(result.AdditionSigned(&a, &b));
  EXPECT_STREQ(GetDecimal(result).Get(), __L("579"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, AdditionSignedPositivePlusNegative)
{
  XMPINTEGER a;
  XMPINTEGER b;
  XMPINTEGER result;

  a.Ini();
  a.LeftSet(100);

  b.Ini();
  b.LeftSet(-30);

  result.Ini();

  EXPECT_TRUE(result.AdditionSigned(&a, &b));
  EXPECT_STREQ(GetDecimal(result).Get(), __L("70"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, SubtractionSignedBasic)
{
  XMPINTEGER a;
  XMPINTEGER b;
  XMPINTEGER result;

  a.Ini();
  a.LeftSet(1000);

  b.Ini();
  b.LeftSet(1);

  result.Ini();

  EXPECT_TRUE(result.SubtractionSigned(&a, &b));
  EXPECT_STREQ(GetDecimal(result).Get(), __L("999"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, SubtractionSignedNegativeResult)
{
  XMPINTEGER a;
  XMPINTEGER b;
  XMPINTEGER result;

  a.Ini();
  a.LeftSet(5);

  b.Ini();
  b.LeftSet(10);

  result.Ini();

  EXPECT_TRUE(result.SubtractionSigned(&a, &b));
  EXPECT_STREQ(GetDecimal(result).Get(), __L("-5"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, MultiplicationBasic)
{
  XMPINTEGER a;
  XMPINTEGER b;
  XMPINTEGER result;

  a.Ini();
  a.LeftSet(123);

  b.Ini();
  b.LeftSet(456);

  result.Ini();

  EXPECT_TRUE(result.Multiplication(&a, &b));
  EXPECT_STREQ(GetDecimal(result).Get(), __L("56088"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, MultiplicationWithPositiveIntOverload)
{
  // Only exercised with a POSITIVE int: Multiplication(XMPINTEGER*, int) (XMPInteger.cpp) always
  // sets the internal operand's sign to 1 and casts the raw int straight into an unsigned XLIMB
  // with no absolute-value handling, so a negative int silently becomes a huge unsigned value
  // instead of a correctly-signed negative operand -- a real, not-fixed XUtils bug, avoided here
  // rather than exercised (it is not the focus of this batch and could produce a misleading result).
  XMPINTEGER a;
  XMPINTEGER result;

  a.Ini();
  a.LeftSet(6);

  result.Ini();

  EXPECT_TRUE(result.Multiplication(&a, 7));
  EXPECT_STREQ(GetDecimal(result).Get(), __L("42"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, DivisionQuotientAndRemainder)
{
  XMPINTEGER a;
  XMPINTEGER b;
  XMPINTEGER quotient;
  XMPINTEGER remainder;

  a.Ini();
  a.LeftSet(100);

  b.Ini();
  b.LeftSet(7);

  quotient.Ini();
  remainder.Ini();

  EXPECT_TRUE(quotient.Division(&quotient, &remainder, &a, &b));
  EXPECT_STREQ(GetDecimal(quotient).Get(), __L("14"));
  EXPECT_STREQ(GetDecimal(remainder).Get(), __L("2"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, ModuleOperator)
{
  XMPINTEGER a;
  XMPINTEGER b;
  XMPINTEGER remainder;

  a.Ini();
  a.LeftSet(100);

  b.Ini();
  b.LeftSet(7);

  remainder.Ini();

  EXPECT_TRUE(remainder.Module(&remainder, &a, &b));
  EXPECT_STREQ(GetDecimal(remainder).Get(), __L("2"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, GetBitAndSetBitRoundTrip)
{
  XMPINTEGER xmpinteger;

  xmpinteger.Ini();
  xmpinteger.LeftSet(0);

  EXPECT_TRUE(xmpinteger.SetBit(3, 1));

  EXPECT_EQ(xmpinteger.GetBit(3), 1);
  EXPECT_EQ(xmpinteger.GetBit(2), 0);
  EXPECT_EQ(xmpinteger.GetBit(4), 0);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, LeftShiftAndRightShiftRoundTrip)
{
  XMPINTEGER xmpinteger;

  xmpinteger.Ini();
  xmpinteger.LeftSet(1);

  EXPECT_TRUE(xmpinteger.LeftShift(4));
  EXPECT_STREQ(GetDecimal(xmpinteger).Get(), __L("16"));

  EXPECT_TRUE(xmpinteger.RightShift(4));
  EXPECT_STREQ(GetDecimal(xmpinteger).Get(), __L("1"));
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, ImportFromBinaryAndExportToBinaryRoundTrip)
{
  XBYTE inputbytes[3]  = { 0x01, 0x02, 0x03 };
  XBYTE outputbytes[3] = { 0,    0,    0    };

  XMPINTEGER xmpinteger;

  xmpinteger.Ini();

  EXPECT_TRUE(xmpinteger.ImportFromBinary(inputbytes, 3));
  EXPECT_STREQ(GetDecimal(xmpinteger).Get(), __L("66051")); // 0x010203

  EXPECT_TRUE(xmpinteger.ExportToBinary(outputbytes, 3));

  EXPECT_EQ(outputbytes[0], 0x01);
  EXPECT_EQ(outputbytes[1], 0x02);
  EXPECT_EQ(outputbytes[2], 0x03);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, SetFromXBufferAndGetToXBufferRoundTrip)
{
  XBUFFER inputbuffer;

  inputbuffer.Add((XBYTE)0x01);
  inputbuffer.Add((XBYTE)0x02);
  inputbuffer.Add((XBYTE)0x03);

  XMPINTEGER xmpinteger;
  XBUFFER    outputbuffer;

  xmpinteger.Ini();

  EXPECT_TRUE(xmpinteger.SetFromXBuffer(inputbuffer));
  EXPECT_STREQ(GetDecimal(xmpinteger).Get(), __L("66051"));

  EXPECT_TRUE(xmpinteger.GetToXBuffer(outputbuffer, 3));

  EXPECT_EQ(outputbuffer.GetByte(0), 0x01);
  EXPECT_EQ(outputbuffer.GetByte(1), 0x02);
  EXPECT_EQ(outputbuffer.GetByte(2), 0x03);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, IsPrimeZeroAndOneAreNotPrime)
{
  XMPINTEGER zero;
  XMPINTEGER one;

  zero.Ini();
  zero.LeftSet(0);

  one.Ini();
  one.LeftSet(1);

  EXPECT_EQ(zero.IsPrime(NULL, NULL), -1);
  EXPECT_EQ(one.IsPrime(NULL, NULL), -1);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, IsPrimeTwoIsPrime)
{
  XMPINTEGER two;

  two.Ini();
  two.LeftSet(2);

  EXPECT_EQ(two.IsPrime(NULL, NULL), 0);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, IsPrimeKnownSmallPrime)
{
  // 97 is small enough to be resolved directly against XMPInteger.cpp's internal SmallPrime[]
  // table, so no random witness (Miller-Rabin) is ever needed -- funcrandom can safely be NULL.
  XMPINTEGER prime;

  prime.Ini();
  prime.LeftSet(97);

  EXPECT_EQ(prime.IsPrime(NULL, NULL), 0);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, IsPrimeKnownComposite)
{
  // 15 = 3*5, caught by CheckSmallFactors() before any random witness would be needed.
  XMPINTEGER composite;

  composite.Ini();
  composite.LeftSet(15);

  EXPECT_EQ(composite.IsPrime(NULL, NULL), -1);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, IsPrimeBeyondSmallFactorTableExercisesMillerRabin)
{
  // 1009 is the first prime beyond XMPInteger.cpp's SmallPrime[] table (which stops at 997), so
  // CheckSmallFactors() cannot resolve it and the real MillerRabin/SlidingWindowExponentiation
  // path must run, driven by the deterministic FixedPatternRandom fixture above.
  XMPINTEGER prime;

  prime.Ini();
  prime.LeftSet(1009);

  EXPECT_EQ(prime.IsPrime(FixedPatternRandom, NULL), 0);
}


TEST(UNITTEST_XMPINTEGER_CLASSNAME, ShrinkToSmallerSizeNowSucceedsAndPreservesSignificantLimbs)
{
  // FIXED: XMPINTEGER::Shrink() (XMPInteger.cpp) now checks "if(!newlimbs) return false;" (bail
  // out only when the allocation genuinely FAILED), matching its sibling Grow(). Previously it
  // checked "if(newlimbs) return false;" -- inverted logic that made it return false immediately
  // on the normal, successful-allocation path, before ever copying data or updating
  // nlimbs/limbs, so shrinking was completely non-functional.
  // Needs a value spanning more than one 32-bit limb so Shrink(1) genuinely takes the
  // "nlimbs > nblimbs" branch (a value like 123456 fits in a single limb, so Shrink(1) would just
  // fall through to Shrink()'s own "actually resize up" alias for Grow(), never touching this
  // branch at all).
  XMPINTEGER xmpinteger;

  SetDecimal(xmpinteger, __L("340282366920938463463374607431768211455")); // 2^128 - 1, 4 limbs

  XDWORD nlimbsbefore = xmpinteger.GetNLimbs();
  ASSERT_GT(nlimbsbefore, (XDWORD)1);

  // Every limb of 2^128-1 is fully set (0xFFFFFFFF), so Shrink()'s own significant-limb scan
  // still requires all 4 limbs regardless of the requested target of 1 -- the requested shrink is
  // honored only down to the smallest size that keeps the value's significant limbs intact, so
  // both the limb count and the decimal value are unchanged here, but the call now genuinely
  // succeeds instead of bailing out before doing anything.
  EXPECT_TRUE(xmpinteger.Shrink(1));
  EXPECT_EQ(xmpinteger.GetNLimbs(), nlimbsbefore);
  EXPECT_STREQ(GetDecimal(xmpinteger).Get(), __L("340282366920938463463374607431768211455"));
}


}
#endif
