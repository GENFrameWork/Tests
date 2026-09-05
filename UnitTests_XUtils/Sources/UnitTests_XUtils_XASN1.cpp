/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_XUtils_XASN1.cpp
*
* @class      UNITTESTS_XUTILS_XASN1
* @brief      XUtils unit tests for XASN1 class
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

#include "UnitTests_XUtils_XASN1.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "XASN1.h"
#include "XBER.h"
#include "XBER_XEvent.h"
#include "XObserver.h"
#include "XBuffer.h"
#include "XString.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XASN1
{

// Minimal concrete XOBSERVER used to confirm XASN1::Decode() actually publishes
// XBERXEVENT_TYPE_DECODE_START/DECODE_END events (via the transient XBER it builds internally)
// through its XSUBJECT base, rather than only returning a bare bool.
class COUNTINGOBSERVER : public XOBSERVER
{
  public:

    COUNTINGOBSERVER() { count = 0; }

    void HandleEvent(XEVENT* event) override
    {
      count++;
    }

    int count;
};


TEST(UNITTESTS_XASN1_CLASSNAME, GetOIDPropertyKnownLookupReturnsDescriptionAndConstructedFlag)
{
  XASN1_OID_PROPERTY* property = XASN1::GetOIDProperty((XCHAR*)__L("2.16.840.1.101.3.4.2.1"));

  ASSERT_NE((void*)property, (void*)NULL);
  EXPECT_STREQ(property->description, __L("sha256"));
  EXPECT_FALSE(property->isconstructed);
}


TEST(UNITTESTS_XASN1_CLASSNAME, GetOIDPropertyUnknownOIDReturnsNull)
{
  XASN1_OID_PROPERTY* property = XASN1::GetOIDProperty((XCHAR*)__L("9.9.9.9.9.9"));

  EXPECT_EQ((void*)property, (void*)NULL);
}


TEST(UNITTESTS_XASN1_CLASSNAME, GetOIDPropertyDescriptionKnownAndUnknown)
{
  XCHAR* known   = XASN1::GetOIDPropertyDescription((XCHAR*)__L("1.3.14.3.2.26"));
  XCHAR* unknown = XASN1::GetOIDPropertyDescription((XCHAR*)__L("9.9.9.9.9.9"));

  ASSERT_NE((void*)known, (void*)NULL);
  EXPECT_STREQ(known, __L("sha1"));
  EXPECT_EQ((void*)unknown, (void*)NULL);
}


TEST(UNITTESTS_XASN1_CLASSNAME, DecodeEmptyBufferReturnsFalse)
{
  XASN1   asn1;
  XBUFFER databin;

  EXPECT_FALSE(asn1.Decode(databin));
}


TEST(UNITTESTS_XASN1_CLASSNAME, DecodeValidBERIntegerReturnsTrue)
{
  // Build a real, wire-correct BER encoding via XBER itself (INTEGER 5 -> 02 01 05) and feed it
  // back through XASN1::Decode() -- this is the "encode with XBER, decode with XASN1" pairing the
  // analysis report calls out (XASN1 decodes atop XBER).
  XBER    ber;
  XBUFFER databin;

  ber.SetINTEGER((XDWORD)5);
  ber.GetDump(databin);

  XASN1 asn1;

  EXPECT_TRUE(asn1.Decode(databin));
}


TEST(UNITTESTS_XASN1_CLASSNAME, DecodeMalformedLongFormLengthReturnsFalse)
{
  // Long-form length byte (top bit set) declaring 5 length-of-length bytes, which
  // XBER::CalculeSize() explicitly rejects (sizeofsize > 4).
  XBUFFER databin;

  databin.Add((XBYTE)0x02); // INTEGER tag
  databin.Add((XBYTE)0x85); // long form, 5 following length bytes -- invalid

  XASN1 asn1;

  EXPECT_FALSE(asn1.Decode(databin));
}


TEST(UNITTESTS_XASN1_CLASSNAME, DecodePublishesStartAndEndEventsToObserver)
{
  XBER    ber;
  XBUFFER databin;

  ber.SetINTEGER((XDWORD)5);
  ber.GetDump(databin);

  XASN1           asn1;
  COUNTINGOBSERVER observer;

  EXPECT_TRUE(asn1.Decode(databin, &observer));

  // At least DECODE_START and DECODE_END must have reached the observer.
  EXPECT_GE(observer.count, 2);
}


}
#endif
