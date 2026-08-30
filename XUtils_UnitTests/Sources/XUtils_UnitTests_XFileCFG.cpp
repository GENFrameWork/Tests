/**-------------------------------------------------------------------------------------------------------------------
*
* @file       XUtils_UnitTests_XFileCFG.cpp
*
* @class      XUTILS_UNITTESTS_XFILECFG
* @brief      XUtils unit tests for XFILECFG class
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

#include "XUtils_UnitTests_XFileCFG.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include <stdio.h>
#include <string.h>

#include "XFactory.h"
#include "XFileCFG.h"
#include "XFileINI.h"
#include "XPath.h"
#include "XFile.h"
#include "XString.h"
#include "XVariant.h"
#include "XVector.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


#ifdef GOOGLETEST_ACTIVE
namespace TEST_XFILECFG
{


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         static void RemoveIfExists(XPATH& xpath)
* @brief      Best-effort scratch-file cleanup via the real XFILE factory.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
static void RemoveIfExists(XPATH& xpath)
{
  XFILE* xfile = GEN_XFACTORY.Create_File();
  if(xfile)
    {
      if(xfile->Exist(xpath)) xfile->Erase(xpath);
      GEN_XFACTORY.Delete_File(xfile);
    }
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @class      TESTCFG_MINIMAL
* @brief      Minimal XFILECFG subclass exercising the fixed Ini<T>() lifecycle
*             (DoVariableMapping -> DoDefault -> Load -> LoadReadjustment -> Save), the way a real
*             application would: DoVariableMapping() declares the config values, DoDefault() gives
*             them their initial defaults.
* @ingroup    UNIT TEST
*
* --------------------------------------------------------------------------------------------------------------------*/
class TESTCFG_MINIMAL : public XFILECFG
{
  public:

    TESTCFG_MINIMAL() : XFILECFG(NULL)
    {
      intvalue    = 0;
      stringvalue.Empty();
    }

    bool DoVariableMapping()
    {
      AddValue(XFILECFG_VALUETYPE_INT   , __L("GENERAL"), __L("Count") , &intvalue);
      AddValue(XFILECFG_VALUETYPE_STRING, __L("GENERAL"), __L("Name")  , &stringvalue);
      return true;
    }

    bool DoDefault()
    {
      intvalue    = 42;
      stringvalue = __L("defaultname");
      return true;
    }

    int     intvalue;
    XSTRING stringvalue;
};


TEST(UNITTEST_XFILECFG_CLASSNAME, ValueGetSetTypeGroupIDAndGenericValue)
{
  XFILECFGVALUE value;

  EXPECT_EQ(value.GetType(), XFILECFG_VALUETYPE_UNKNOWN);
  EXPECT_TRUE(value.SetType(XFILECFG_VALUETYPE_INT));
  EXPECT_EQ(value.GetType(), XFILECFG_VALUETYPE_INT);

  ASSERT_TRUE(value.GetGroup() != NULL);
  value.GetGroup()->Set(__L("MYGROUP"));
  EXPECT_FALSE(value.GetGroup()->Compare(__L("MYGROUP"), false));

  ASSERT_TRUE(value.GetID() != NULL);
  value.GetID()->Set(__L("MYID"));
  EXPECT_FALSE(value.GetID()->Compare(__L("MYID"), false));

  int backing = 123;
  EXPECT_TRUE(value.SetValue((void*)&backing));
  EXPECT_EQ(value.GetValue(), (void*)&backing);
  EXPECT_EQ(*(int*)value.GetValue(), 123);
}


TEST(UNITTEST_XFILECFG_CLASSNAME, ValueSecuenceMetadataGetSet)
{
  XFILECFGVALUE value;

  value.SetMinSecuences(2);
  EXPECT_EQ(value.GetMinSecuences(), (XDWORD)2);

  value.SetMaxSecuences(10);
  EXPECT_EQ(value.GetMaxSecuences(), (XDWORD)10);

  // Default is XFILECFG_INVALIDINDEXSECUENCE (-1) until explicitly set.
  EXPECT_EQ(value.GetIndexSecuence(), XFILECFG_INVALIDINDEXSECUENCE);
  value.SetIndexSecuence(3);
  EXPECT_EQ(value.GetIndexSecuence(), 3);

  value.SetNSecuences(7);
  EXPECT_EQ(value.GetNSecuences(), (XDWORD)7);

  ASSERT_TRUE(value.GetRemarkText() != NULL);
  value.GetRemarkText()->Set(__L("a remark"));
  EXPECT_FALSE(value.GetRemarkText()->Compare(__L("a remark"), false));

  value.SetRemarkXPos(5);
  EXPECT_EQ(value.GetRemarkXPos(), (XDWORD)5);

  int dummyvector = 0;
  value.SetValuesVector((void*)&dummyvector);
  EXPECT_EQ(value.GetValuesVector(), (void*)&dummyvector);

  value.SetModeRemoteMix(XFILECFG_MODEREMOTEMIX_NOTDELADDKEYS);
  EXPECT_EQ(value.GetModeRemoteMix(), XFILECFG_MODEREMOTEMIX_NOTDELADDKEYS);
}


TEST(UNITTEST_XFILECFG_CLASSNAME, AddValueGetValueAndGetCFGValueForEveryValueType)
{
  XFILECFG cfg;

  int     intbacking     = 10;
  XWORD   maskbacking     = 0x00AB;
  float   floatbacking   = 3.5f;
  XSTRING stringbacking  = __L("hello");
  bool    boolbacking    = true;

  ASSERT_TRUE(cfg.AddValue(XFILECFG_VALUETYPE_INT    , __L("G"), __L("IntKey")   , &intbacking)    != NULL);
  ASSERT_TRUE(cfg.AddValue(XFILECFG_VALUETYPE_MASK   , __L("G"), __L("MaskKey")  , &maskbacking)   != NULL);
  ASSERT_TRUE(cfg.AddValue(XFILECFG_VALUETYPE_FLOAT  , __L("G"), __L("FloatKey") , &floatbacking)  != NULL);
  ASSERT_TRUE(cfg.AddValue(XFILECFG_VALUETYPE_STRING , __L("G"), __L("StrKey")   , &stringbacking) != NULL);
  ASSERT_TRUE(cfg.AddValue(XFILECFG_VALUETYPE_BOOLEAN, __L("G"), __L("BoolKey")  , &boolbacking)   != NULL);

  ASSERT_TRUE(cfg.GetValues() != NULL);
  EXPECT_EQ(cfg.GetValues()->GetSize(), (XDWORD)5);

  XVARIANT* vint = cfg.GetValue(__L("G"), __L("IntKey"));
  ASSERT_TRUE(vint != NULL);
  EXPECT_EQ((int)(*vint), 10);
  GEN_DELETE vint;

  XVARIANT* vmask = cfg.GetValue(__L("G"), __L("MaskKey"));
  ASSERT_TRUE(vmask != NULL);
  EXPECT_EQ((XWORD)(*vmask), (XWORD)0x00AB);
  GEN_DELETE vmask;

  XVARIANT* vfloat = cfg.GetValue(__L("G"), __L("FloatKey"));
  ASSERT_TRUE(vfloat != NULL);
  EXPECT_FLOAT_EQ((float)(*vfloat), 3.5f);
  GEN_DELETE vfloat;

  XVARIANT* vstr = cfg.GetValue(__L("G"), __L("StrKey"));
  ASSERT_TRUE(vstr != NULL);
  XCHAR* readback = (XCHAR*)(*vstr);
  EXPECT_STREQ(readback, __L("hello"));
  GEN_DELETE vstr;

  XVARIANT* vbool = cfg.GetValue(__L("G"), __L("BoolKey"));
  ASSERT_TRUE(vbool != NULL);
  EXPECT_EQ((bool)(*vbool), true);
  GEN_DELETE vbool;

  // Unknown group/ID must yield NULL, not garbage.
  EXPECT_TRUE(cfg.GetValue(__L("G"), __L("NoSuchKey")) == (XVARIANT*)NULL);
  EXPECT_TRUE(cfg.GetCFGValue(__L("G"), __L("NoSuchKey")) == (XFILECFGVALUE*)NULL);

  XFILECFGVALUE* cfgvalue = cfg.GetCFGValue(__L("G"), __L("IntKey"));
  ASSERT_TRUE(cfgvalue != NULL);
  EXPECT_EQ(cfgvalue->GetType(), XFILECFG_VALUETYPE_INT);

  cfg.DeleteAllValues();
}


TEST(UNITTEST_XFILECFG_CLASSNAME, SetValueThroughXVariantUpdatesBackingStorage)
{
  XFILECFG cfg;

  int     intbacking    = 1;
  XSTRING stringbacking = __L("old");

  XFILECFGVALUE* intcfg = cfg.AddValue(XFILECFG_VALUETYPE_INT, __L("G"), __L("IntKey"), &intbacking);
  ASSERT_TRUE(intcfg != NULL);

  XFILECFGVALUE* strcfg = cfg.AddValue(XFILECFG_VALUETYPE_STRING, __L("G"), __L("StrKey"), &stringbacking);
  ASSERT_TRUE(strcfg != NULL);

  XVARIANT newint(999);
  EXPECT_TRUE(cfg.SetValue(intcfg, &newint));
  EXPECT_EQ(intbacking, 999);

  XVARIANT newstr(__L("newvalue"));
  EXPECT_TRUE(cfg.SetValue(strcfg, &newstr));
  EXPECT_FALSE(stringbacking.Compare(__L("newvalue"), false));

  // NULL arguments must fail cleanly, not crash.
  EXPECT_FALSE(cfg.SetValue(NULL, &newint));
  EXPECT_FALSE(cfg.SetValue(intcfg, NULL));

  cfg.DeleteAllValues();
}


TEST(UNITTEST_XFILECFG_CLASSNAME, DelCFGValueAndDeleteAllValues)
{
  XFILECFG cfg;

  int intbacking = 1;
  cfg.AddValue(XFILECFG_VALUETYPE_INT, __L("G"), __L("A"), &intbacking);
  cfg.AddValue(XFILECFG_VALUETYPE_INT, __L("G"), __L("B"), &intbacking);

  ASSERT_EQ(cfg.GetValues()->GetSize(), (XDWORD)2);

  EXPECT_TRUE(cfg.DelCFGValue(__L("G"), __L("A")));
  EXPECT_EQ(cfg.GetValues()->GetSize(), (XDWORD)1);
  EXPECT_TRUE(cfg.GetCFGValue(__L("G"), __L("A")) == (XFILECFGVALUE*)NULL);

  // Deleting an already-gone key must fail cleanly.
  EXPECT_FALSE(cfg.DelCFGValue(__L("G"), __L("A")));

  EXPECT_TRUE(cfg.DeleteAllValues());
  EXPECT_EQ(cfg.GetValues()->GetSize(), (XDWORD)0);
  EXPECT_FALSE(cfg.DeleteAllValues()); // nothing left
}


TEST(UNITTEST_XFILECFG_CLASSNAME, AddRemarkAndGetRemarks)
{
  XFILECFG cfg;

  EXPECT_TRUE(cfg.AddRemark(__L("GENERAL"), __L("a whole-line remark"), 0, 0));
  EXPECT_TRUE(cfg.AddRemark(__L("GENERAL"), __L("SomeKey"), __L("an in-key remark"), 0, 1));

  ASSERT_TRUE(cfg.GetRemarks() != NULL);
  EXPECT_EQ(cfg.GetRemarks()->GetSize(), (XDWORD)2);

  EXPECT_TRUE(cfg.DeleteAllRemarks());
  EXPECT_EQ(cfg.GetRemarks()->GetSize(), (XDWORD)0);
}


TEST(UNITTEST_XFILECFG_CLASSNAME, SaveThenLoadRoundTripsIntAndStringValuesThroughARealFile)
{
  XPATH xpath(__L("/tmp/xutils_unittests_xfilecfg_roundtrip.ini"));
  RemoveIfExists(xpath);

  {
    XFILECFG writer;

    int     intbacking    = 77;
    XSTRING stringbacking = __L("roundtripvalue");

    ASSERT_TRUE(writer.AddValue(XFILECFG_VALUETYPE_INT   , __L("GENERAL"), __L("Count"), &intbacking)    != NULL);
    ASSERT_TRUE(writer.AddValue(XFILECFG_VALUETYPE_STRING, __L("GENERAL"), __L("Name") , &stringbacking) != NULL);

    EXPECT_TRUE(writer.Save(xpath));
  }

  {
    XFILECFG reader;

    int     intbacking    = 0;
    XSTRING stringbacking = __L("");

    ASSERT_TRUE(reader.AddValue(XFILECFG_VALUETYPE_INT   , __L("GENERAL"), __L("Count"), &intbacking)    != NULL);
    ASSERT_TRUE(reader.AddValue(XFILECFG_VALUETYPE_STRING, __L("GENERAL"), __L("Name") , &stringbacking) != NULL);

    EXPECT_TRUE(reader.Load(xpath));

    EXPECT_EQ(intbacking, 77);
    EXPECT_FALSE(stringbacking.Compare(__L("roundtripvalue"), false));
  }

  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILECFG_CLASSNAME, IniLifecycleCreatesFileWithDefaultsOnFirstRunDespiteReturningFalse)
{
  // Drives the full fixed Ini<T>() lifecycle (DoVariableMapping -> DoDefault -> Load ->
  // LoadReadjustment -> Save) through a minimal real subclass, against a file that does not exist
  // yet -- exactly the "first run creates the file with its defaults" scenario the template method
  // is designed for.
  //
  // Real, concrete XUtils behavior worth documenting explicitly (traced with a debugger, not
  // assumed): Ini<T>()'s own overall bool return value is `Load() && Save()`, but on a genuinely
  // first run Load() ALWAYS returns false here, even though it does everything it is supposed to
  // do (opens/creates the file, finds no matching keys yet so every value keeps its just-applied
  // DoDefault(), then closes the file again) -- because XFILEINI::Close() (XFileINI.cpp:774)
  // returns `Serialization(false) && XFILETXT::Close()`, and Serialization(false) calls
  // ConvertToLines() (XFileINI.cpp:1618), whose very first line is `if(sections.IsEmpty())
  // return false;`. A brand-new file that Load() never wrote anything into (nothing was read
  // from disk, and Load() itself never calls WriteValue()) still has zero sections at that point,
  // so closing it during Load() always fails. Save() succeeds afterward only because by the time
  // IT closes fileini, DeleteAllSections()+WriteValue() have already populated real section/key
  // content. Net effect: Ini<T>() reports false on every single first run, even on complete
  // success -- a caller who only checks Ini<T>()'s return value cannot use it to distinguish
  // "first run, everything defaulted and saved correctly" from a genuine failure.
  XPATH xpath(__L("/tmp/xutils_unittests_xfilecfg_ini_lifecycle.ini"));
  RemoveIfExists(xpath);

  {
    TESTCFG_MINIMAL cfg;
    *cfg.GetPathFile() = xpath;

    EXPECT_FALSE(cfg.Ini<int>());

    EXPECT_EQ(cfg.intvalue, 42);
    EXPECT_FALSE(cfg.stringvalue.Compare(__L("defaultname"), false));
  }

  // The file must now exist on disk with the defaults persisted by Save().
  {
    XFILEINI verify;
    ASSERT_TRUE(verify.Open(xpath, true));

    XSTRING value;
    ASSERT_TRUE(verify.ReadValue(__L("GENERAL"), __L("Count"), value));
    EXPECT_EQ(value.ConvertToInt(), 42);

    ASSERT_TRUE(verify.ReadValue(__L("GENERAL"), __L("Name"), value));
    EXPECT_FALSE(value.Compare(__L("defaultname"), false));

    verify.Close();
  }

  RemoveIfExists(xpath);
}


TEST(UNITTEST_XFILECFG_CLASSNAME, AddValueSecuenceGeneratesMinCountKeysOnAFreshEmptyFile)
{
  // On a fresh file with none of the sequence keys present yet, GetCountKeys() (which underlies
  // AddValueSecuence<T>) finds zero existing matches, so the sequence falls back to mincount.
  XPATH xpath(__L("/tmp/xutils_unittests_xfilecfg_secuence.ini"));
  RemoveIfExists(xpath);

  XFILECFG cfg;
  *cfg.GetPathFile() = xpath;

  // GetCountKeys()/AddValueSecuence<T> both need fileini open against a real (even if empty) file.
  ASSERT_TRUE(cfg.IniFile(xpath));

  XVECTOR<int*> values;
  int nkeys = 0;

  XFILECFGVALUE* first = cfg.AddValueSecuence<int>(XFILECFG_VALUETYPE_INT, __L("GENERAL"), __L("Key"),
                                                    NULL, 3, 10, values, nkeys);

  EXPECT_EQ(nkeys, 3); // mincount, since the file had none of these keys yet
  ASSERT_TRUE(first != NULL);
  EXPECT_EQ(values.GetSize(), (XDWORD)3);

  // Keys must be named "Key1".."Key3" (mask==NULL -> "%s%d") and share metadata/backing vector.
  for(int c=1; c<=3; c++)
    {
      XSTRING key;
      key.Format(__L("Key%d"), c);

      XFILECFGVALUE* cfgvalue = cfg.GetCFGValue(__L("GENERAL"), key.Get());
      ASSERT_TRUE(cfgvalue != NULL) << "missing key index " << c;

      EXPECT_EQ(cfgvalue->GetIndexSecuence(), c);
      EXPECT_EQ(cfgvalue->GetMinSecuences(), (XDWORD)3);
      EXPECT_EQ(cfgvalue->GetMaxSecuences(), (XDWORD)10);
      EXPECT_EQ(cfgvalue->GetNSecuences(), (XDWORD)3);
      EXPECT_EQ(cfgvalue->GetValuesVector(), (void*)&values);
    }

  cfg.EndFile();
  cfg.DeleteAllValues();
  RemoveIfExists(xpath);
}


} // namespace TEST_XFILECFG
#endif
