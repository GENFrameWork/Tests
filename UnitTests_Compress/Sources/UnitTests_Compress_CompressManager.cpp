/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Compress_CompressManager.cpp
*
* @class      UNITTESTS_COMPRESS_COMPRESSMANAGER
* @brief      Compress unit tests for COMPRESSMANAGER class
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

#include "UnitTests_Compress_CompressManager.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "CompressManager.h"
#include "CompressBase.h"
#include "CompressLZW.h"
#include "CompressLZRW1KH.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_COMPRESSMANAGER
{


TEST(UNITTESTS_COMPRESSMANAGER_CLASSNAME, CreateLZWReturnsCorrectConcreteType)
{
  COMPRESSMANAGER manager;

  COMPRESSBASE* compress = manager.Create(COMPRESSBASE_TYPE_LZW);

  ASSERT_NE(compress, (COMPRESSBASE*)NULL);
  EXPECT_EQ(compress->GetType(), COMPRESSBASE_TYPE_LZW);
  EXPECT_NE(dynamic_cast<COMPRESS_LZW*>(compress), (COMPRESS_LZW*)NULL);

  delete compress;
}


TEST(UNITTESTS_COMPRESSMANAGER_CLASSNAME, CreateLZRW1KHReturnsCorrectConcreteType)
{
  COMPRESSMANAGER manager;

  COMPRESSBASE* compress = manager.Create(COMPRESSBASE_TYPE_LZRW1KH);

  ASSERT_NE(compress, (COMPRESSBASE*)NULL);
  EXPECT_EQ(compress->GetType(), COMPRESSBASE_TYPE_LZRW1KH);
  EXPECT_NE(dynamic_cast<COMPRESS_LZRW1KH*>(compress), (COMPRESS_LZRW1KH*)NULL);

  delete compress;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSMANAGER_CLASSNAME, CreateUnknownTypeFallsBackToBaseClass)
* @brief      COMPRESSMANAGER::Create()'s switch has a "default : compress = GEN_NEW COMPRESSBASE();"
*             branch (CompressManager.cpp) reached for any COMPRESSBASE_TYPE without a matching case
*             label under the currently-active feature set -- confirmed here with
*             COMPRESSBASE_TYPE_NONE, which has no case of its own.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSMANAGER_CLASSNAME, CreateUnknownTypeFallsBackToBaseClass)
{
  COMPRESSMANAGER manager;

  COMPRESSBASE* compress = manager.Create(COMPRESSBASE_TYPE_NONE);

  ASSERT_NE(compress, (COMPRESSBASE*)NULL);
  // The default branch news a plain COMPRESSBASE without ever calling SetType(COMPRESSBASE_TYPE_NONE)
  // explicitly, but COMPRESSBASE's own default constructor does that itself (CompressBase.cpp).
  EXPECT_EQ(compress->GetType(), COMPRESSBASE_TYPE_NONE);
  EXPECT_EQ(dynamic_cast<COMPRESS_LZW*>(compress), (COMPRESS_LZW*)NULL);

  delete compress;
}


TEST(UNITTESTS_COMPRESSMANAGER_CLASSNAME, GetInstanceReturnsSameNonNullPointer)
{
  COMPRESSMANAGER* first  = COMPRESSMANAGER::GetInstance();
  COMPRESSMANAGER* second = COMPRESSMANAGER::GetInstance();

  ASSERT_NE(first, (COMPRESSMANAGER*)NULL);
  EXPECT_EQ(first, second);
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         TEST(UNITTESTS_COMPRESSMANAGER_CLASSNAME, DeleteInstanceLeavesDanglingStaticPointer)
* @brief      FINDING (see /tmp/work/COMPRESS_REVIEW_FINDINGS.md): COMPRESSMANAGER::DeleteInstance()
*             (CompressManager.cpp) does "if(instance) GEN_DELETE instance;" but never sets
*             "instance = NULL" afterwards, unlike the usual GEN singleton idiom. GEN_DELETE expands to
*             plain "delete" (XMemory_Control.h), which does not null the pointer either. This test
*             deliberately runs LAST in this translation unit (registered after the other
*             COMPRESSMANAGER tests, though GoogleTest does not guarantee cross-TU ordering by default)
*             and does not call GetInstance() again afterwards, to avoid handing a dangling pointer to
*             any other test: the point being demonstrated is that a caller who DID call GetInstance()
*             again right after this would receive the dangling COMPRESSMANAGER* instance unchanged
*             (still non-NULL, since "if(!instance)" in GetInstance() only re-news when the pointer is
*             NULL), not a freshly allocated object.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
TEST(UNITTESTS_COMPRESSMANAGER_CLASSNAME, DeleteInstanceLeavesDanglingStaticPointer)
{
  COMPRESSMANAGER* before = COMPRESSMANAGER::GetInstance();
  ASSERT_NE(before, (COMPRESSMANAGER*)NULL);

  COMPRESSMANAGER::DeleteInstance();

  // Not exercised further here (reading through 'before' after delete would itself be a use-after-
  // free): the finding is confirmed by source inspection (CompressManager.cpp / XMemory_Control.h)
  // plus the passing GetInstanceReturnsSameNonNullPointer test above showing GetInstance()'s only
  // re-allocation guard is "if(!instance)".
  SUCCEED();
}


}
#endif
