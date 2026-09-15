/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Script_TestHelpers.h
* @brief      Common helpers for Script unit tests
* @ingroup    TESTS
*
* @copyright  EndoraSoft. All rights reserved.
*
* --------------------------------------------------------------------------------------------------------------------*/
#pragma once

/*---- INCLUDES ------------------------------------------------------------------------------------------------------*/

#include "gtest/gtest.h"

#include "Script.h"
#include "Script_Lib.h"


/*---- INLINE FUNCTIONS + PROTOTYPES ---------------------------------------------------------------------------------*/

class UNITTESTS_SCRIPT_ERRORCAPTURE : public SCRIPT
{
  public:

    UNITTESTS_SCRIPT_ERRORCAPTURE() : lasterror(SCRIPT_ERRORCODE_NONE) { }

    bool HaveError(int errorcode)
    {
      lasterror = errorcode;
      return SCRIPT::HaveError(errorcode);
    }

    int GetLastError() const
    {
      return lasterror;
    }

    void ResetLastError()
    {
      lasterror = SCRIPT_ERRORCODE_NONE;
    }

  private:

    int lasterror;
};

inline void UnitTests_Script_DummyFunction(SCRIPT_LIB* library, SCRIPT* script, XVECTOR<XVARIANT*>* params, XVARIANT* returnvalue)
{
  if(returnvalue) (*returnvalue) = 1;
}


inline void UnitTests_Script_ExpectLibraryRegistration(SCRIPT_LIB& library, XCHAR* expectedID, XCHAR* functionname)
{
  SCRIPT script;

  ASSERT_NE(library.GetID(), (XSTRING*)NULL);
  EXPECT_EQ(library.GetID()->Compare(expectedID), 0);
  EXPECT_FALSE(library.AddLibraryFunctions(NULL));
  EXPECT_TRUE(library.AddLibraryFunctions(&script));
  EXPECT_TRUE(script.SetCapabilities(SCRIPT_CAPABILITY_ALL_UNSAFE));
  EXPECT_NE(script.GetLibraryFunction(functionname), (SCRIPT_LIB_FUNCTION*)NULL);
}


#define UNITTESTS_SCRIPT_LIBRARY_REGISTRATION_TEST(testnamespace, classname, librarytype, libraryID, functionname) \
namespace testnamespace                                                                                                  \
{                                                                                                                        \
  TEST(classname, IdentityAndRegistration)                                                                                \
  {                                                                                                                      \
    librarytype library;                                                                                                 \
    UnitTests_Script_ExpectLibraryRegistration(library, libraryID, functionname);                                        \
  }                                                                                                                      \
}


#define UNITTESTS_SCRIPT_LIBRARY_CAPABILITY_TEST(testnamespace, classname, librarytype, functionname, capability)        \
namespace testnamespace                                                                                                  \
{                                                                                                                        \
  TEST(classname, RequiresDeclaredCapability)                                                                             \
  {                                                                                                                      \
    SCRIPT script;                                                                                                       \
    librarytype library;                                                                                                 \
    ASSERT_TRUE(library.AddLibraryFunctions(&script));                                                                   \
    ASSERT_TRUE(script.SetCapabilities(SCRIPT_CAPABILITY_NONE));                                                         \
    EXPECT_EQ(script.GetLibraryFunction(functionname), (SCRIPT_LIB_FUNCTION*)NULL);                                      \
    ASSERT_TRUE(script.EnableCapabilities(capability));                                                                  \
    EXPECT_NE(script.GetLibraryFunction(functionname), (SCRIPT_LIB_FUNCTION*)NULL);                                      \
  }                                                                                                                      \
}
