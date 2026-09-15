/**-------------------------------------------------------------------------------------------------------------------
* @file       UnitTests_Script_ScriptCache.cpp
* @brief      Unit tests for SCRIPT_CACHE
* @ingroup    TESTS
* --------------------------------------------------------------------------------------------------------------------*/
#include "GEN_Defines.h"
#include "UnitTests_Script_ScriptCache.h"
#include "UnitTests_Script_TestHelpers.h"
#include "Script_Cache.h"
#include "GEN_Control.h"

#if defined(GOOGLETEST_ACTIVE) && defined(SCRIPT_CACHE_ACTIVE)
namespace TEST_SCRIPTCACHE
{

TEST(UNITTESTS_SCRIPTCACHE_CLASSNAME, IdentifierIsDeterministic)
{
  SCRIPT_CACHE& cache = SCRIPT_CACHE::GetInstance();
  XSTRING key(__L("same-key"));

  EXPECT_EQ(cache.GenerateID(key), cache.GenerateID(key));
  EXPECT_NE(cache.GenerateID(key), (XDWORD)0);
}


TEST(UNITTESTS_SCRIPTCACHE_CLASSNAME, AddGetSetDeleteLifecycle)
{
  SCRIPT_CACHE& cache = SCRIPT_CACHE::GetInstance();
  XSTRING key(__L("unit-cache-entry"));
  XSTRING value(__L("first"));
  XSTRING replacement(__L("second"));
  XDWORD id = cache.GenerateID(key);

  cache.Cache_Del(id);
  ASSERT_TRUE(cache.Cache_Add(id, &value, key));
  ASSERT_NE(cache.Cache_Get(id, key), (XSTRING*)NULL);
  EXPECT_EQ(cache.Cache_Get(id, key)->Compare(__L("first")), 0);

  EXPECT_TRUE(cache.Cache_Set(id, &replacement));
  EXPECT_EQ(cache.Cache_Get(id)->Compare(__L("second")), 0);
  EXPECT_EQ(cache.Cache_Get(id, key), (XSTRING*)NULL);
  EXPECT_TRUE(cache.Cache_Del(id));
  EXPECT_EQ(cache.Cache_Get(id), (XSTRING*)NULL);
}


TEST(UNITTESTS_SCRIPTCACHE_CLASSNAME, ListKeyUsesEveryOrderedName)
{
  SCRIPT_CACHE& cache = SCRIPT_CACHE::GetInstance();
  XSTRING first(__L("one.g"));
  XSTRING secondA(__L("two.g"));
  XSTRING secondB(__L("other.g"));
  XVECTOR<XSTRING*> listA;
  XVECTOR<XSTRING*> listB;
  XSTRING keyA;
  XSTRING keyB;

  listA.Add(&first);
  listA.Add(&secondA);
  listB.Add(&first);
  listB.Add(&secondB);

  ASSERT_TRUE(cache.GenerateListKey(&listA, keyA));
  ASSERT_TRUE(cache.GenerateListKey(&listB, keyB));
  EXPECT_NE(keyA.Compare(keyB), 0);
}

}
#endif
