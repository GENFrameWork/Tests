/**-------------------------------------------------------------------------------------------------------------------
*
* @file       UnitTests_Compress.cpp
*
* @class      UNITTESTS_COMPRESS
* @brief      Compress unit tests application
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

#include "UnitTests_Compress.h"

#ifdef GOOGLETEST_ACTIVE
#include "gtest/gtest.h"
#endif

#include "VersionFrameWork.h"

#include "XTranslation_GEN.h"
#include "XTranslation.h"

#include "XThreadListNonPreemptive.h"


/*---- PRECOMPILATION INCLUDES ---------------------------------------------------------------------------------------*/

#include "GEN_Control.h"


/*---- GENERAL VARIABLE ----------------------------------------------------------------------------------------------*/

APPLICATIONCREATEINSTANCE(UNITTESTS_COMPRESS, unittests)


/*---- CLASS MEMBERS -------------------------------------------------------------------------------------------------*/


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UNITTESTS_COMPRESS::UNITTESTS_COMPRESS()
* @brief      Constructor of class.
* @ingroup    UNIT TEST
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
UNITTESTS_COMPRESS::UNITTESTS_COMPRESS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         UNITTESTS_COMPRESS::~UNITTESTS_COMPRESS()
* @brief      Destructor of class.
* @ingroup    UNIT TEST
*
* @return     Does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
UNITTESTS_COMPRESS::~UNITTESTS_COMPRESS()
{
  Clean();
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS_COMPRESS::AppProc_Ini()
* @brief      Initializes the application process.
* @ingroup    UNIT TEST
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS_COMPRESS::AppProc_Ini()
{
  GEN_SET_VERSION(APPLICATION_NAMEAPP, APPLICATION_NAMEFILE, APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR, APPLICATION_OWNER, APPLICATION_YEAROFCREATION)

  XTRACE_SETAPPLICATIONNAME(APPLICATION_NAMEAPP);
  XTRACE_SETAPPLICATIONVERSION(APPLICATION_VERSION, APPLICATION_SUBVERSION, APPLICATION_SUBVERSIONERR);

  GEN_XPATHSMANAGER.AdjustRootPathDefault(APPLICATION_DIRECTORYMAIN);

  GEN_XPATHSMANAGER.CreateAllPathSectionOnDisk();

  XTRACE_ADDTARGET(XTRACE_TYPE_NET, GEN_XTRACE_NET_DEFAULT_01);
  XTRACE_ADDTARGET(XTRACE_TYPE_NET, __L("*:10001"));

  XTRACE_CLEARSCREEN;
  XTRACE_CLEARMSGSSTATUS;

  XSTRING SO_ID;
  GEN_XSYSTEM.GetOperativeSystemID(SO_ID);

  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("Application ROOT path: %s"),  GEN_XPATHSMANAGER.GetPathSection(XPATHSMANAGERSECTIONTYPE_ROOT)->xpath->Get());
  XTRACE_PRINTCOLOR(XTRACE_COLOR_BLUE, __L("S.O. version: %s"), SO_ID.Get());

  { XPATH xpathsection;
    XPATH xpath;
    GEN_XPATHSMANAGER.GetPathOfSection(XPATHSMANAGERSECTIONTYPE_ROOT, xpathsection);
    xpath.Create(3 , xpathsection.Get(),  APPLICATION_NAMEFILE, XTRANSLATION_NAMEFILEEXT);

    if(!GEN_XTRANSLATION.Ini(xpath))
      {
        return false;
      }

    GEN_XTRANSLATION.SetActual(XLANGUAGE_ISO_639_3_CODE_ENG);
  }

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS_COMPRESS::AppProc_FirstUpdate()
* @brief      Executes the first application update.
* @ingroup    UNIT TEST
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS_COMPRESS::AppProc_FirstUpdate()
{
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS_COMPRESS::AppProc_Update()
* @brief      Executes the application update cycle.
* @ingroup    UNIT TEST
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS_COMPRESS::AppProc_Update()
{
  return false;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS_COMPRESS::AppProc_LastUpdate()
* @brief      App Proc Last Update.
* @ingroup    UNIT TEST
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS_COMPRESS::AppProc_LastUpdate()
{
  // Test-only fix (GEN untouched): APPFLOWBASE::End() (APPFlowBase.cpp) only calls AppProc_End()
  // when AppProc_LastUpdate() returns true ("status = AppProc_LastUpdate(); if(status) { status =
  // AppProc_End(); }") -- this method used to unconditionally "return false;", which silently made
  // AppProc_End() below dead code for this whole test binary (it was NEVER invoked, on any
  // platform). Returning true here is what makes the cleanup added in AppProc_End() actually run
  // before MainProc's own Factorys_End()/XMEMORY_CONTROL_DISPLAYMEMORYLEAKS, which is what a real
  // GEN application (rather than this test harness) naturally benefits from since it doesn't
  // shortcut its own AppProc_LastUpdate(). Same documented fix as UnitTests_XUtils.cpp.
  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         bool UNITTESTS_COMPRESS::AppProc_End()
* @brief      Ends the application process.
* @ingroup    UNIT TEST
*
* @return     bool : true if it is successful.
*
* --------------------------------------------------------------------------------------------------------------------*/
bool UNITTESTS_COMPRESS::AppProc_End()
{
  // FIXED (test-side, GEN untouched): eliminates one of the two persistent "NOT FREE MEMORY
  // RESOURCES" leaks reported at shutdown (the XThreadListNonPreemptive.cpp block).
  //
  // Root cause (confirmed by reading MainProcWINDOWS.cpp/MainProcLINUX.cpp, same as
  // UnitTests_XUtils.cpp's documented finding): XTHREADLISTNONPREEMPTIVE is a lazily-created
  // singleton, and neither MAINPROCWINDOWS::Factorys_End() nor MAINPROCLINUX::Factorys_End() --
  // the real GEN shutdown sequence that runs right before XMEMORY_CONTROL_DISPLAYMEMORYLEAKS --
  // ever call XTHREADLISTNONPREEMPTIVE::DelInstance(). This is the same genuine GEN gap already
  // reported by UnitTests_XUtils (not fixed there, since that means touching GEN). We tear it
  // down from our own application-level shutdown hook instead: DelInstance() is a safe, idempotent
  // public API call.
  XTHREADLISTNONPREEMPTIVE::DelInstance();

  return true;
}


/**-------------------------------------------------------------------------------------------------------------------
*
* @fn         void UNITTESTS_COMPRESS::Clean()
* @brief      Cleans the object internal state.
* @ingroup    UNIT TEST
*
* @return     void : does not return anything.
*
* --------------------------------------------------------------------------------------------------------------------*/
void UNITTESTS_COMPRESS::Clean()
{

}

